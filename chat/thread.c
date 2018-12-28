#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int main()
{
    printf("Thread_test \n");
	printf("wait data... \n");
	
	pthread_t thread1, thread2;	// thread struct
	int tret1, tret2;							// thread return
	
	void thread1_func(void)
	{
		while(1)
		{
			printf("Thread1 \n");
			sleep(1);
		}
	}
		
	void thread2_func(void)
	{
		while(1)
		{
			printf("Thread2 \n");
			sleep(1);
		}
	}
	
	tret1 = pthread_create(&thread1, NULL, (void *) thread1_func, NULL);
	tret2 = pthread_create(&thread2, NULL, (void *) thread2_func, NULL);
	printf("%#x\n", tret1);
	printf("%#x\n", tret2);
	pthread_join( thread1, NULL);
	pthread_join( thread2, NULL);
}
