/* Multi Thread.
 * Thread id는 다르나, 같은 변수를 사용 하여 count ++.
 */

#include <stdio.h>  
#include <unistd.h>  
#include <pthread.h>  

int g_count = 0; 
pthread_mutex_t  mutex = PTHREAD_MUTEX_INITIALIZER;

void* counting_thread(void *data) 
{ 
	pid_t pid = getpid();
	pthread_t tid = pthread_self();
	printf("[%s] pid:%u, tid:%u\n", (char*)data, (unsigned int)pid, (unsigned int)tid);

	int i = 0;
	pthread_mutex_lock(&mutex); 
	while (i < 3)
	{
		printf("[%s] : %d\n", (char*)data, g_count);
		g_count ++; 
		i ++;
	}
	pthread_mutex_unlock(&mutex);
	/*
	for (i = 0; i < 3; i++) 
	{
		//trhead 잠금.
		printf("[%s] : %d\n", (char*)data, g_count);
		g_count ++; 
	} */
} 

int main() 
{ 
	pthread_t p_thread[2]; 
	int thread_id; 
	
	thread_id = pthread_create(&p_thread[0], NULL, counting_thread, (void*)"Thread1"); 
	thread_id = pthread_create(&p_thread[1], NULL, counting_thread, (void*)"Thread2"); 

	int status; 
	pthread_join(p_thread[0], (void *) &status); 
	pthread_join(p_thread[1], (void *) &status); 

	status = pthread_mutex_destroy(&mutex); 
	printf("status = %d.    programing is end\n", status); 
	
	return 0; 
} 
