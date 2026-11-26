//-----------------------------------------------------------------------------
//----- Copyright MVR Group
//-----------------------------------------------------------------------------
#pragma once

#include <algorithm>
#include <atomic>
#include <exception>
#include <mutex>
#include <system_error>
#include <thread>
#include <vector>

namespace VectorworksMVR
{
	namespace Parallel
	{
		// Number of worker threads to use for 'count' work items.
		inline size_t GetWorkerCount(size_t count, size_t maxThreads = 0)
		{
			size_t hw = std::thread::hardware_concurrency();
			if (hw == 0) { hw = 1; }
			if (maxThreads != 0) { hw = (std::min)(hw, maxThreads); }
			return (std::max)(size_t(1), (std::min)(hw, count));
		}

		// True while the current thread executes items of a ParallelFor. Nested ParallelFor calls then run
		// serially on the current thread instead of spawning workerCount^2 threads.
		inline bool& IsInsideParallelFor()
		{
			thread_local bool inside = false;
			return inside;
		}

		// Calls func(i) for every i in [0, count). Items are distributed dynamically across threads.
		// The calling thread participates. The first exception thrown by any item is rethrown
		// after all threads have finished; remaining items are skipped once an exception occurred.
		template <typename Func>
		void ParallelFor(size_t count, Func func, size_t maxThreads = 0)
		{
			if (count == 0) { return; }

			const size_t workerCount = GetWorkerCount(count, maxThreads);
			if (workerCount == 1 || IsInsideParallelFor())
			{
				for (size_t i = 0; i < count; ++i) { func(i); }
				return;
			}

			std::atomic<size_t>	next(0);
			std::atomic<bool>	failed(false);
			std::exception_ptr	firstException;
			std::mutex			exceptionMutex;

			auto worker = [&]()
			{
				struct SInsideGuard
				{
					bool fPrevious;
					SInsideGuard() : fPrevious(IsInsideParallelFor())	{ IsInsideParallelFor() = true; }
					~SInsideGuard()										{ IsInsideParallelFor() = fPrevious; }
				} insideGuard;

				for (;;)
				{
					if (failed.load()) { return; }
					size_t i = next.fetch_add(1);
					if (i >= count) { return; }
					try
					{
						func(i);
					}
					catch (...)
					{
						std::lock_guard<std::mutex> lock(exceptionMutex);
						if (!firstException) { firstException = std::current_exception(); }
						failed.store(true);
					}
				}
			};

			std::vector<std::thread> threads;
			threads.reserve(workerCount - 1);
			try
			{
				for (size_t t = 1; t < workerCount; ++t) { threads.emplace_back(worker); }
			}
			catch (const std::system_error&)
			{
				// Could not spawn more threads; continue with the ones we have.
			}
			worker();
			for (std::thread& th : threads) { th.join(); }

			if (firstException) { std::rethrow_exception(firstException); }
		}
	}
}
