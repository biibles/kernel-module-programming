#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

//총 생성해야할 프로세스 수
#define TOTALFORK 5 

int main(void) 
{
	pid_t pid[TOTALFORK];
	int runProcess = 0; //생성한 프로세스 수
	int state;

	while (runProcess < TOTALFORK) 
	{ 
		//pid = wait(&state); 
		pid[runProcess] = fork();

		//음수일 경우 fork 생성 에러.
		if (pid[runProcess] < 0) 
		{
			return -1;
		} 
		else if(pid[runProcess] == 0) //자식 프로세스
		{
			printf("child  %ld\n", (long)getpid());
			exit(0);
		} 
		else //부모 프로세스
		{ 
			printf("\nparent %ld\n", (long)getpid());
			sleep(1);
		}
		runProcess++;
	}
	return 0;
}
