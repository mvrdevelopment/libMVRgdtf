#include "CTaskQueue.h"
#include <iostream>
#include <atomic>

TaskQueue::TaskQueue(boost::asio::io_context& ioContext)
    : ioContext_(ioContext), running_(false) {}

TaskQueue::~TaskQueue() {
    Stop();
}

void TaskQueue::Start() {
    if (running_.exchange(true)) return; 
    worker_ = std::thread(&TaskQueue::WorkerThread, this);
}

void TaskQueue::Stop() {
    {
        running_ = false;
        ioContext_.stop();
    }
    if (worker_.joinable()) {
        worker_.join();
    }
}

void TaskQueue::AddTask(const std::function<void()>& task) {

    boost::asio::post(ioContext_, [this, task]() { ExecuteTask(task); });
}

void TaskQueue::ExecuteTask(const std::function<void()>& task) {
    try {
        task();
    } catch (const std::exception& e) {
        std::cerr << "Exception in task: " << e.what() << std::endl;
    }
}

void TaskQueue::WorkerThread() {
    try {
        ioContext_.run();
    } catch (const std::exception& e) {
        std::cerr << "Exception in WorkerThread: " << e.what() << std::endl;
        Stop();
    }
}
