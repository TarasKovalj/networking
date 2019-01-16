#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 10

int tret[N];                          //thread returned ID
int tret_main;
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
  tret_main = pthread_create(&thread_main, NULL, (void *) main_thread_func, NULL);

  for (int z = 0; z < N; z++) {
    pthread_mutex_lock(&mutex[z]);
    tret[z] = pthread_create(&thread[z], NULL, (void *) thread_func, &param[z]);
	  printf("Thread%d is created\n", z);
  }

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
    // do something
    pthread_mutex_unlock(&mutex_main);  //enable to proceed main thread
  }
}

void main_thread_func()
{
  pthread_mutex_lock(&mutex_main);
  while(1)
  {
    //Enable threads in some order
    pthread_mutex_unlock(&mutex[0]);
    pthread_mutex_lock(&mutex_main);  //need to wait end of thread1

    pthread_mutex_unlock(&mutex[7]);
    pthread_mutex_lock(&mutex_main);

    pthread_mutex_unlock(&mutex[8]);
    pthread_mutex_lock(&mutex_main);

    sleep(1);
  }
}
