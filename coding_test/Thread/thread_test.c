#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
 
void Error(const char *mes);
void *thread_func(void *arg);
 
int main()
{
	int state = 0;
	pthread_t t_id;

	state = pthread_create(&t_id,NULL,thread_func,NULL);
	if(state != 0)
		Error("pthread_create Errorn");

	printf("Create Thread ID : %u\n",t_id);
	sleep(3);

	return 0;
}

void *thread_func(void *arg)
{
	int i=0;
	for( i=0; i<3;i++)
	{
		sleep(2);
		printf("Thread Running!!\n");
	}
}

void Error(const char *mes)
{
	printf("%sn",mes);
	exit(0);
}
