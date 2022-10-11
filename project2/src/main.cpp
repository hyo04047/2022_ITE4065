#include <iostream>
#include <chrono>
#include <random>
//---------------------------------------------------------------------------
#include "threadpool.hpp"
#include "snapshot.hpp"
//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
int main(int argc, char* argv[]) {
    // Argument passing for ./run N
    size_t n;
    n = atoi(argv[1]);

    // Constuct snapshot and threadpool with #threads
    Snapshot<int> snapshot(n);
    ThreadPool::ThreadPool pool(n);

    // Make a specific thread to take times for 1 minute
    thread time_check([&pool]() {
        // Sleep for exact 1 minute, then terminate thread pool
        this_thread::sleep_for(chrono::seconds(60));
        pool.terminate();
    });
    
    // Real random generator with uniform disribution
    // Not seudo random generator from crand
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(numeric_limits<int>::min(), numeric_limits<int>::max());

    // Keep adding job(updating value) until time thread finish after 1 minute
    while (!pool.done()){
        // Generate random numer
        int value = dis(gen);
        // Add job that update thread local value 
        // with tid and generated random number into job queue
        pool.EnqueueJob([&snapshot, value](size_t tid) {
            snapshot.update(value, tid);
        });
    }

    // When time is finished, print total update count to standard output
    cout << "Total Update Counts : " << pool.getTotalCount() << endl;
    // Join the thread for time counting
    time_check.join();

    return 0;
}