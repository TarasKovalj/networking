#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void sleep(int x);

int main()
{
    printf("Thread_test \n");
	printf("wait data... \n");
	
	pthread_t thread1, thread2;	// thread struct
	int tret1, tret2;							// thread return
	
	void thread1_func(void)
	{
		char i;
		scanf("%c", &i);
		while(1)
		{
			scanf("%c", &i);
			printf("%c\n", i-32);
			//while(1);
			printf("Thread1 \n");
			sleep(1);
		}
	}
		
	void thread2_func(void)
	{
		while(1)
		{
			char i;
			//scanf("%c", &i);
			long int z = 0;
			//while(1)
			//{
				//scanf("%c", &i);
				//printf("%c\n", i-32);
				//if (z%100000000==500) printf("W\n");
				//z++;
			//}
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
