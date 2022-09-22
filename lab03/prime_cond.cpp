#include <stdio.h>
#include <pthread.h>
#include <math.h>

#define NUM_THREAD 10

int thread_ret[NUM_THREAD];
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv=PTHREAD_COND_INITIALIZER;

int range_start;
int range_end;
bool isstop=false;

bool IsPrime(int n)
{
    if (n < 2)
    {
        return false;
    }

    for (int i = 2; i <= sqrt(n); i++)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}

void *ThreadFunc(void *arg)
{
    long tid = (long)arg;

    pthread_mutex_lock(&mutex);
    thread_ret[tid] = -1;
    pthread_cond_wait(&cv, &mutex);
    pthread_mutex_unlock(&mutex);

    while (!isstop) { 
        // Split range for this thread
        int start = range_start + ((range_end - range_start + 1) / NUM_THREAD) * tid;
        int end = range_start + ((range_end - range_start + 1) / NUM_THREAD) * (tid + 1);
        if (tid == NUM_THREAD - 1)
        {
            end = range_end + 1;
        }

        long cnt_prime = 0;
        for (int i = start; i < end; i++)
        {
            if (IsPrime(i))
            {
                cnt_prime++;
            }
        }

        thread_ret[tid] = cnt_prime;

        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cv, &mutex);
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main(void)
{
    pthread_t threads[NUM_THREAD];

    // Create threads to work
    for (long i = 0; i < NUM_THREAD; i++)
    {
        if (pthread_create(&threads[i], 0, ThreadFunc, (void *)i) < 0)
        {
            printf("pthread_create error!\n");
            return 0;
        }
        while (thread_ret[i] < 0)
            pthread_yield();
        // thread_ret[i] = -1;

    }

    while (1)
    {
        // Input range
        scanf("%d", &range_start);
        if (range_start == -1)
        {
            break;
        }
        scanf("%d", &range_end);

        pthread_mutex_lock(&mutex);
        pthread_cond_broadcast(&cv);
        pthread_mutex_unlock(&mutex);

        // Collect results
        int cnt_prime = 0;
        for (int i = 0; i < NUM_THREAD; i++)
        {
            while (thread_ret[i] < 0) 
                pthread_yield();
            cnt_prime += thread_ret[i];
            thread_ret[i] = -1;
        }
        printf("number of prime: %d\n", cnt_prime);
    }

    isstop = true;
    pthread_mutex_lock(&mutex);
    pthread_cond_broadcast(&cv);
    pthread_mutex_unlock(&mutex);
    // Wait threads end
    for (int i = 0; i < NUM_THREAD; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
