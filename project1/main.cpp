#include <iostream>
#include <pthread.h>
#include "Joiner.hpp"
#include "Parser.hpp"
//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
#define NUM_THREAD 20
//---------------------------------------------------------------------------
bool isstop = false;
Joiner joiner;
// count for working thread
uint64_t cnt_for_thread = 0;
// array for store result of threads' computation
string* volatile thread_ret[NUM_THREAD];
// array for store input query
string inputline[NUM_THREAD];
// mutex and condition_variable for each thread
pthread_t threads[NUM_THREAD];
pthread_mutex_t mutexes[NUM_THREAD+1];
pthread_cond_t cv[NUM_THREAD+1];
//---------------------------------------------------------------------------
void *thread_join(void* arg) {
   // thread id
   long tid = (long)arg;

   // initialize result
   thread_ret[tid] = (string *)-1;
   // wait for query input
   pthread_mutex_lock(&mutexes[tid]);
   pthread_cond_wait(&cv[tid], &mutexes[tid]);
   pthread_mutex_unlock(&mutexes[tid]);

   while (!isstop) {
      QueryInfo *i = new QueryInfo();
      // get input and parse
      i->parseQuery(inputline[tid]);
      // join at thread
      string *result = new string(joiner.join(*i));
      // save result
      thread_ret[tid] = move(result);
      // if this thread is last thread,
      // wakeup main thread
      if (tid == (NUM_THREAD-1)) {
         pthread_mutex_lock(&mutexes[NUM_THREAD]);
         pthread_cond_signal(&cv[NUM_THREAD]);
         pthread_mutex_unlock(&mutexes[NUM_THREAD]);
      }
      // wait for next input
      pthread_mutex_lock(&mutexes[tid]);
      pthread_cond_wait(&cv[tid], &mutexes[tid]);
      pthread_mutex_unlock(&mutexes[tid]);
   }

   pthread_exit(NULL);
   // return NULL;
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

   for (long idx=0; idx<NUM_THREAD; ++idx) {
      // Initialize mutexes and condition variables
      mutexes[idx] = PTHREAD_MUTEX_INITIALIZER;
      cv[idx] = PTHREAD_COND_INITIALIZER;
      // Create threads
      if (pthread_create(&threads[idx], 0, thread_join, (void*)idx) < 0) {
         printf("pthread_create error\n");
         return 0;
      }
   }
   // Mutex and condition variable for main thread
   mutexes[NUM_THREAD] = PTHREAD_MUTEX_INITIALIZER;
   cv[NUM_THREAD] = PTHREAD_COND_INITIALIZER;
   
   while (getline(cin, line)) {
      if (line == "F") {
         // Flush results
         for (long idx=0; idx<cnt_for_thread; ++idx) {
            // Wait until threads finish
            while (thread_ret[idx] == (string *)-1) 
               pthread_yield();
            cout << *(thread_ret[idx]);
            // Reset result for next input
            thread_ret[idx] = (string *)-1;
         }
         cnt_for_thread = 0;
         continue; // End of a batch
      }
      // All thread received input and now working
      if (cnt_for_thread == NUM_THREAD) {
         // Wait for all thread finish
         pthread_mutex_lock(&mutexes[NUM_THREAD]);
         pthread_cond_wait(&cv[NUM_THREAD], &mutexes[NUM_THREAD]);
         pthread_mutex_unlock(&mutexes[NUM_THREAD]);
         // Flush results
         for (long idx=0; idx<cnt_for_thread; ++idx) {
            cout << *(thread_ret[idx]);
            thread_ret[idx] = (string *)-1;
         }
         cnt_for_thread = 0;
      }
      inputline[cnt_for_thread] = line;
      // Wakeup worker thread with input given
      pthread_mutex_lock(&mutexes[cnt_for_thread]);
      pthread_cond_signal(&cv[cnt_for_thread]);
      pthread_mutex_unlock(&mutexes[cnt_for_thread]);
      cnt_for_thread++;
   }
   // Set flag and Wakeup all thread and Join
   isstop = true;
   for (long idx=0; idx<NUM_THREAD; ++idx) {
      pthread_mutex_lock(&mutexes[idx]);
      pthread_cond_signal(&cv[idx]);
      pthread_mutex_unlock(&mutexes[idx]);
      pthread_join(threads[idx], NULL);
   }

   return 0;
}