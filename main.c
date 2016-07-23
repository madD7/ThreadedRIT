#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
#include <inttypes.h>

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





int main()
{
	pthread_t tidTimer;

	pthread_create(&tidTimer, NULL, &tickInit, NULL);

	while(1);

	return 0;
}







