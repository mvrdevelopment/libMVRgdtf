#pragma once
#include <boost/asio.hpp>
#include <thread>
#include <functional>
#include <mutex>

class TaskQueue {
public:
    explicit TaskQueue(boost::asio::io_context& ioContext);
    ~TaskQueue();

    void Start();
    void Stop();
    void AddTask(const std::function<void()>& task);

private:
    void ExecuteTask(const std::function<void()>& task);
    void WorkerThread();

    boost::asio::io_context& ioContext_;
    std::thread worker_;
    std::atomic<bool> running_;
    std::mutex mutex_;
};

