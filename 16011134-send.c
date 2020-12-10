#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

//argv[1] : PID(receive side)
//argv[2] : data
int main(int argc, char **argv)
{
	union sigval sv;

	sv.sival_int = atoi(argv[2]); //int data
	sigqueue(atoi(argv[1]), SIGTSTP, sv);
}

