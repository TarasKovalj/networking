#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 10

int isFinished = 0;

pthread_t thread[N];                  //thread struct
pthread_t thread_main;

pthread_mutex_t mutex[N];             //mutexes
pthread_mutex_t mutex_main;
int param[N] = {0,1,2,3,4,5,6,7,8,9}; //parameter of threads

void sleep(int x);
void thread_func(int *);
void main_thread_func();

int main()
{
  pthread_create(&thread_main, NULL, (void *) main_thread_func, NULL);

  printf("\nPreess any key + ENTER to EXIT\n");
  if (getchar())
	isFinished = 1;

  pthread_join(thread_main, NULL);

  return 0;
}

void thread_func(int *parameter)
{
  int i;
  i = *parameter;

  while(!isFinished)
  {
    //lock himself
    pthread_mutex_lock(&mutex[i]);
    // do something

    printf("Thread%d is doing something...\n", i);

    pthread_mutex_unlock(&mutex_main);
  }

  printf("Thread%d is done\n", i);
}

void main_thread_func()
{
  // create threads
  /*for (int z = 0; z < N; z++) {
    pthread_mutex_lock(&mutex[z]);
    pthread_create(&thread[z], NULL, (void *) thread_func, &param[z]);
	  printf("Thread%d is created\n", z);
  }*/

  pthread_create(&thread[0], NULL, (void *) thread_func, &param[0]);
  pthread_create(&thread[7], NULL, (void *) thread_func, &param[7]);
  pthread_create(&thread[8], NULL, (void *) thread_func, &param[8]);
  pthread_create(&thread[5], NULL, (void *) thread_func, &param[5]);

  pthread_mutex_lock(&mutex_main);
  while(!isFinished)
  {
    //Enable threads in some order
    pthread_mutex_unlock(&mutex[0]);
    pthread_mutex_lock(&mutex_main);

    pthread_mutex_unlock(&mutex[7]);
    pthread_mutex_lock(&mutex_main);

    pthread_mutex_unlock(&mutex[8]);
    pthread_mutex_lock(&mutex_main);

    pthread_mutex_unlock(&mutex[5]);
    pthread_mutex_lock(&mutex_main);

    sleep(1);
  }


 for (int z = 0; z < N; z++)
 {
    pthread_mutex_unlock(&mutex[z]);
    pthread_join(thread[z], NULL);
 }

  printf("Main Thread is done\n");
}
