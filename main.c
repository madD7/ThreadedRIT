#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <sys/time.h>
#include <math.h>
#include <inttypes.h>
#include <string.h>

volatile uint32_t timerTicks=0;

int compareTime(struct timespec *result, struct timespec t0, struct timespec t1)
{

}


void* tickInit()
{
	timerTicks = 0;
	uint32_t ms=0;
	time_t s;
	struct timespec ts;

	while(1)
	{
		clock_gettime(CLOCK_REALTIME, &ts);
		s = ts.tv_sec;
		ms = round(ts.tv_nsec/1.0e6);

		printf("sec=%lu ms=%lu nsec=%lu\n", (long)s, (long)ms, ts.tv_nsec);
		printf("timerticks=%d\n", timerTicks++);
		usleep(100000);
	}

	return NULL;
}

void timerhandler(int signum)
{
	printf("timerticks=%d\n", timerTicks++);
}


int main()
{
	struct itimerval timer;
	struct sigaction act;
	
	/* setup handler for SigAlrm */
	memset(&act, 0, sizeof(act));
	act.sa_handler = &timerhandler;
	sigaction(SIGVTALRM, &act, NULL);
	
	/* Setup interval timer */
	/* Timer is configured to expire after 5mSec */
	timer.it_value.tv_sec = 0;
	timer.it_value.tv_usec = 100000;

	/* 5mSec repetatively */
	timer.it_interval.tv_sec = 0;
	timer.it_interval.tv_usec = 100000;

	setitimer(ITIMER_VIRTUAL, &timer, NULL);

	while(1);

	return 0;
}







