#include <iostream>
// #include <vector>
#include <pthread.h>
// #include <thread>
// #include <mutex>
// #include <condition_variable>
// #include <future>
#include "Joiner.hpp"
#include "Parser.hpp"
//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
#define NUM_THREAD 47
//---------------------------------------------------------------------------
bool isstop = false;
uint64_t cnt_for_thread = 0;
QueryInfo* thread_arg[NUM_THREAD];
string* volatile thread_ret[NUM_THREAD];
// vector<thread> threads;
// vector<shared_future<void>> thread_ret(NUM_THREAD, NULL);
// mutex mutexes[NUM_THREAD];
// condition_variable cv[NUM_THREAD];
pthread_t threads[NUM_THREAD];
pthread_mutex_t mutexes[NUM_THREAD];
pthread_cond_t cv[NUM_THREAD];
Joiner joiner;
//---------------------------------------------------------------------------
void *thread_join(void* arg) {
   long tid = (long)arg;

   // thread_ret[tid].clear();
   thread_ret[tid] = (string *)-1;
   pthread_mutex_lock(&mutexes[tid]);
   pthread_cond_wait(&cv[tid], &mutexes[tid]);
   pthread_mutex_unlock(&mutexes[tid]);
   // unique_lock<mutex> lock(mutexes[tid]);
   // cv[tid].wait(lock);

   while (!isstop) {
      QueryInfo &i = *(thread_arg[tid]);
      string *result = new string(joiner.join(i));

      thread_ret[tid] = move(result);
      pthread_mutex_lock(&mutexes[tid]);
      // free(thread_arg[tid]);
      pthread_cond_wait(&cv[tid], &mutexes[tid]);
      pthread_mutex_unlock(&mutexes[tid]);
      // cv[tid].wait(lock);
      // lock.unlock();
   }

   return NULL;
}
//---------------------------------------------------------------------------
int main(int argc, char *argv[]) {
   string line;
   while (getline(cin, line)) {
      if (line == "Done")
         break;
      joiner.addRelation(line.c_str());
   }

   // Preparation phase (not timed)
   // Build histograms, indexes,...
   // threads.reserve(NUM_THREAD);

   for (long idx=0; idx<NUM_THREAD; ++idx) {
      mutexes[idx] = PTHREAD_MUTEX_INITIALIZER;
      cv[idx] = PTHREAD_COND_INITIALIZER;

      if (pthread_create(&threads[idx], 0, thread_join, (void*)idx) < 0) {
         printf("pthread_create error\n");
         return 0;
      }
      // auto ret = async(launch::async, thread_join, thread_cnt);
      // threads.emplace_back(thread(&thread_join, idx));
      // thread_ret[idx] = (string *)-1;
      // while (thread_ret[idx] != (string *)-1) {
      //    this_thread::yield();
      // }
   }
   
   while (getline(cin, line)) {
      if (line == "F") {
         for (long idx=0; idx < cnt_for_thread; ++idx) {
            // while (thread_ret[idx].empty()) ;
            while (thread_ret[idx] == (string *)-1) ;
            cout << *(thread_ret[idx]);
            thread_ret[idx] = (string *)-1;
            // free(thread_ret[idx]);
         }
         cnt_for_thread = 0;
         continue; // End of a batch
      }

      if (cnt_for_thread == NUM_THREAD) {
         for (long idx=0; idx < cnt_for_thread; ++idx) {
            while (thread_ret[idx] == (string *)-1) ;
            cout << *(thread_ret[idx]);
            thread_ret[idx] = (string *)-1;
            // free(thread_ret[idx]);
         }
         cnt_for_thread = 0;
      }

      QueryInfo *i = new QueryInfo();
      i->parseQuery(line);

      thread_arg[cnt_for_thread] = move(i);
      thread_ret[cnt_for_thread] = (string *)-1;

      // unique_lock<mutex> lock(mutexes[cnt_for_thread]);
      // cv[cnt_for_thread].notify_one();
      // lock.unlock();

      pthread_mutex_lock(&mutexes[cnt_for_thread]);
      pthread_cond_signal(&cv[cnt_for_thread]);
      pthread_mutex_unlock(&mutexes[cnt_for_thread]);
      cnt_for_thread++;
   }

   isstop = true;
   for (long idx=0; idx<NUM_THREAD; ++idx) {
      pthread_mutex_lock(&mutexes[idx]);
      pthread_cond_signal(&cv[idx]);
      pthread_mutex_unlock(&mutexes[idx]);
      pthread_join(threads[idx], NULL);
      // unique_lock<mutex> lock(mutexes[idx]);
      // cv[idx].notify_one();
      // lock.unlock();
      // threads[idx].join();
   }

   return 0;
}