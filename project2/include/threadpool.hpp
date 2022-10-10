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
class ThreadPool {
    public:
        ThreadPool(size_t num_threads);
        ~ThreadPool();

        template <class F>
        std::future<typename std::result_of<F(size_t)>::type> EnqueueJob(F &&f);

        bool done() const {
            return isdone;
        }

        void terminate() {
            isdone = true;
            cv.notify_all();
        }

        int getTotalCount() {
            int totalCount = 0;
            for (auto& cnt : updateCounts)
                totalCount += cnt;
            return totalCount;
        }

    private:
        size_t num_threads_;
        std::vector<std::thread> workers;
        std::mutex mtx;
        std::condition_variable cv;

        std::atomic<bool> isdone;

        std::queue<std::function<void(size_t)>> jobs;
        void work(size_t tid);

        std::vector<int> updateCounts;
};

ThreadPool::ThreadPool(size_t num_threads) : num_threads_(num_threads), isdone(false) {
  workers.reserve(num_threads_);
  updateCounts.assign(num_threads_, 0);
  for (size_t i = 0; i < num_threads_; ++i) {
    workers.emplace_back([this, i]() { this->work(i); });
  }
}

ThreadPool::~ThreadPool() {
  isdone = true;
  cv.notify_all();

  for (auto& t : this->workers) {
    cv.notify_all();
    t.join();
  }
}

template <class F>
std::future<typename std::result_of<F(size_t)>::type> ThreadPool::EnqueueJob(F &&f) {
    if (isdone) {
        throw std::runtime_error("ThreadPool finished");
    }

    using return_type = typename std::result_of<F(size_t)>::type(size_t);

    auto job = std::make_shared<std::packaged_task<return_type>>(
        std::forward<F>(f)
    );

    auto job_result_future = job->get_future();

    {
        std::lock_guard<std::mutex> lock(this->mtx);
        jobs.emplace([job](size_t tid) { (*job)(tid); });
    }

    this->cv.notify_one();

    return job_result_future;
}

void ThreadPool::work(size_t tid) {
    while (true) {
        std::function<void(size_t)> job = nullptr;
        std::unique_lock<std::mutex> lock(this->mtx);
        this->cv.wait(lock, [this] {
            return this->isdone || this->jobs.size();
        });

        if (this->isdone && this->jobs.empty())
            return;
        
        job = std::move(this->jobs.front());
        this->jobs.pop();
        updateCounts[tid]++;
        job(tid);
    }
}

}