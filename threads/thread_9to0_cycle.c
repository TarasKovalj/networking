#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 10

int tret[N];                          //thread returned ID
pthread_t thread[N];                  //thread struct
pthread_mutex_t mutex[N];             //mutexes
int param[N] = {0,1,2,3,4,5,6,7,8,9}; //parameter of threads

void sleep(int x);
void thread_func(int *);

int main()
{
  for (int z = 0; z < N; z++) {
    pthread_mutex_lock(&mutex[z]);
    tret[z] = pthread_create(&thread[z], NULL, (void *) thread_func, &param[z]);
	  printf("Thread%d is created\n", z);
  }

  //start chain
  pthread_mutex_unlock(&mutex[9]);

  for (int z = 0; z < N; z++) {
    pthread_join(thread[z], NULL);
    printf("Thread%d is done\n", z);
  }
  return 0;
}

void thread_func(int *parameter)
{
  int i;
  i = *parameter;
  while(1)
  {
    //lock himself
    pthread_mutex_lock(&mutex[i]);
    printf("Thread%d \n", i);

    //unlock next mutex to preceed next thread
    if (i > 0)
      pthread_mutex_unlock(&mutex[i-1]);
    // start new cycle of threads
    // if that one is the finish thread (thread[0] is last one)
    else
      pthread_mutex_unlock(&mutex[9]);

    sleep(1);
  }
}
