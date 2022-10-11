#pragma once
//---------------------------------------------------------------------------
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
//---------------------------------------------------------------------------
#include <functional>
#include <atomic>
//---------------------------------------------------------------------------
#include <vector>
#include <queue>
//---------------------------------------------------------------------------
namespace ThreadPool {
// class for managing threads, jobs and count for the project
class ThreadPool {
    public:
        ThreadPool(size_t num_threads);
        ~ThreadPool();

        template <class F>
        std::future<typename std::result_of<F(size_t)>::type> EnqueueJob(F &&f);

        // getter for stop flag
        bool done() const {
            return isdone;
        }

        // function to set stop flag and wake up all worker threads
        void terminate() {
            isdone = true;
            cv.notify_all();
        }

        // Sum all update count and return
        int getTotalCount() {
            int totalCount = 0;
            for (auto& cnt : updateCounts)
                totalCount += cnt;
            return totalCount;
        }

    private:
        size_t num_threads_;
        std::vector<std::thread> workers;

        // Mutex and Condition variable for job queue
        std::mutex mtx;
        std::condition_variable cv;

        std::atomic<bool> isdone;

        // Job queue and Work function for workers
        std::queue<std::function<void(size_t)>> jobs;
        void work(size_t tid);

        // Vector to store each thread's update count
        std::vector<int> updateCounts;
};
//---------------------------------------------------------------------------
ThreadPool::ThreadPool(size_t num_threads) : num_threads_(num_threads), isdone(false) {
    // Constructor for thread pool
    // Make threads in threadpool and initialize update counts
    workers.reserve(num_threads_);
    updateCounts.assign(num_threads_, 0);
    for (size_t i = 0; i < num_threads_; ++i) {
        // Set workers to do work()
        workers.emplace_back([this, i]() { this->work(i); });
    }
}
//---------------------------------------------------------------------------
ThreadPool::~ThreadPool() {
    // Destructor for thread pool
    // Set stop flag, wakeup all workers and join
    isdone = true;
    cv.notify_all();

    for (auto& t : this->workers) {
        cv.notify_all();
        t.join();
    }
}
//---------------------------------------------------------------------------
template <class F>
std::future<typename std::result_of<F(size_t)>::type> ThreadPool::EnqueueJob(F &&f) {
    // Add function to job queue with thread id
    // Remove other argument passing except thread id
    if (isdone) {
        throw std::runtime_error("ThreadPool finished");
    }

    using return_type = typename std::result_of<F(size_t)>::type(size_t);
    // Set job whose return type will be determined later with std::future
    auto job = std::make_shared<std::packaged_task<return_type>>(
        std::forward<F>(f)
    );
    // Get result from job when it is done in the future
    auto job_result_future = job->get_future();

    {
        // Add job into job queue with mutex
        std::lock_guard<std::mutex> lock(this->mtx);
        jobs.emplace([job](size_t tid) { (*job)(tid); });
    }

    // Wakeup worker to get job from queue and work
    this->cv.notify_one();

    return job_result_future;
}
//---------------------------------------------------------------------------
void ThreadPool::work(size_t tid) {
    // Work function for worker threads
    while (true) {
        // Function pointer to get job from queue
        std::function<void(size_t)> job = nullptr;
        // Set mutex for using condition variable
        std::unique_lock<std::mutex> lock(this->mtx);

        // Wait(sleep) until other thread wakes up with condition variable
        // Automatically wakes up when stop flag set or job queue has job to do
        this->cv.wait(lock, [this] {
            return this->isdone || this->jobs.size();
        });

        // When stop flag set and job queue is empty
        // Worker goes home and stop working
        if (this->isdone && this->jobs.empty())
            return;
        
        // Get oldest job from job queue
        job = std::move(this->jobs.front());
        this->jobs.pop();
        
        // Increase local update count when worker success to get job(update)
        updateCounts[tid]++;

        // Do job with parameter tid
        job(tid);
    }
}
//---------------------------------------------------------------------------
} // end of namespace