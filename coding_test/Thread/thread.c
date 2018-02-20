#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void *t_func(void *data)
{
	pid_t pid;           
	pthread_t tid;

	pid = getpid();
	tid = pthread_self();

	char* thread_name = (char*)data;
	int i = 0;

	while (i<3)
	{
		printf("[%s] pid:%u, tid:%x --- %d\n", thread_name, (unsigned int)pid, (unsigned int)tid, i);
		i++;
	}
}

int main()
{
	pthread_t p_thread[2];
	int thr_id;
	int status;
	char p1[] = "thread_1";
	char p2[] = "thread_2";
	char pM[] = "thread_m";

	thr_id = pthread_create(&p_thread[0], NULL, t_func, (void *)p1);

	//성공적으로 thread 생성.
	if (thr_id < 0)
	{
		perror("thread create error : ");
		exit(0);
	}

	thr_id = pthread_create(&p_thread[1], NULL, t_func, (void *)p2);
	if (thr_id < 0)
	{
		perror("thread create error : ");
		exit(0);
	}

	t_func((void *)pM);

	pthread_join(p_thread[0], (void **)&status);
	pthread_join(p_thread[1], (void **)&status);

	printf("종료.\n");

	return 0;
}

