#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <sys/time.h>
#include <math.h>
#include <inttypes.h>
#include <string.h>
#include "timer.h"

volatile uint32_t timerTicks=0;

void timerHandler(void)
{
	printf("timerticks=%d\n", timerTicks++);
}

int main()
{
	if(timerInit(100, timerHandler))
	{
		printf("Error: Timer initialisation failed \n");
		return 1;
	}
	
	printf("Press 'Ctrl+C' to quit\n");
	
	while(1);

	return 0;
}







