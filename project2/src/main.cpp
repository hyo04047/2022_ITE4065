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
    size_t n;
    n = atoi(argv[1]);

    Snapshot<int> snapshot(n);
    ThreadPool::ThreadPool pool(n);

    thread time_check([&pool]() {
        this_thread::sleep_for(chrono::seconds(60));
        pool.terminate();
    });

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(numeric_limits<int>::min(), numeric_limits<int>::max());

    while (!pool.done()){
        int value = dis(gen);
        pool.EnqueueJob([&snapshot, value](size_t tid) {
            snapshot.update(value, tid);
        });
    }

    cout << "Total Update Counts : " << pool.getTotalCount() << endl;
    time_check.join();

    return 0;
}