#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void handler(int signo)
{
	psignal(signo, "Received signal: "); //print signal name
	sleep(1); //wait
}

int main(void)
{
	struct sigaction act;  //sigaction struct
	int cnt = 0;

	sigemptyset(&act.sa_mask); //remove all signal in sigset_t
	sigaddset(&act.sa_mask, SIGQUIT); //add signal SIGQUIT
	
	act.sa_flags = 0; //no option
	act.sa_handler = handler; //set function "handler" by action

	//if sigaction failed
	if(sigaction(SIGINT, &act, (struct sigaction *)NULL) < 0) {
		perror("sigaction : SIGINT was failed");
		exit(1);
	}
	if(sigaction(SIGTSTP, &act, (struct sigaction *)NULL) < 0) {
		perror("sigaction : SIGTSTP was failed");
		exit(1);
	}

	while(1) {
		printf("Waiting for signal to be received! Count:%d\n", cnt);
		cnt++;
		sleep(1);
	}
	fprintf(stderr,"\n");
	pause();

	return 0;
}
