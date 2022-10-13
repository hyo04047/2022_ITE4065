#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 10
#define NUM_INCREMENT 1000000

long global_cnt = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* thread_func(void* arg) {
  long local_cnt = 0;

  for (int i = 0; i < NUM_INCREMENT; i++) {
    pthread_mutex_lock(&mutex);
    global_cnt++;  // Increase global count value
    pthread_mutex_unlock(&mutex);
    local_cnt++;   // Increase local count value
  }

  return (void*)local_cnt;
}

int main(int argc, char* argv[]) {
  pthread_t threads[NUM_THREADS];

  // Create threads
  for (int i = 0; i < NUM_THREADS; i++) {
    if (pthread_create(&threads[i], 0, thread_func, NULL) < 0) {
      printf("error: pthread_create failed!\n");
      return 0;
    }
  }

  // Wait for the threads to end
  long ret;
  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], (void**)&ret);
    printf("[Thread] thread %ld: local count -> %ld\n", threads[i], ret);
  }
  printf("[Main] global count -> %ld\n", global_cnt);

  return 0;
}
