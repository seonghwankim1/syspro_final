#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sighandler(int signo, siginfo_t *si, void *context)
{
	if(si->si_code == SI_QUEUE) {
		printf("User RTS signal %d\n", si->si_pid);
		printf("Sig  Number %d\n", si->si_signo);
		printf("Studend ID is %d\n",si->si_value.sival_int);
		// check signal queueing
		getchar();
	}
	else   // Unix Standard Signal
		printf("Get none realtime signal %d\n", signo); 
}

int main()
{
	struct sigaction sigact;

	printf("My pid %d\n", getpid()); //print pid

	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = SA_SIGINFO; //set sa_flags
	sigact.sa_restorer  = NULL; 
	sigact.sa_sigaction = sighandler; //register signal handler 
	
	if (sigaction(SIGTSTP, &sigact, 0) == 1) {  //check SIGTSTP signal
		printf("can't catch SIGSTSTP\n");
		exit(0);
	}   
	while(1)
		sleep(1);   
}   
