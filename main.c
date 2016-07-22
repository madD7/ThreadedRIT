#include <pthread.h>
#include <stdio.h>
#include <stdint.h>

volatile uint32_t timerTicks=0;

void* tickInit()
{
	timerTicks = 0;

	while(1)
	{
		printf("%d\n", timerTicks++);
		sleep(1);
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







