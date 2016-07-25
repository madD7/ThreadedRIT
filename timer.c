#include "timer.h"

void (*ptrTimerHandlerFunc)(void);

#ifdef __linux__

void timer_handler(int);
void __timerSigHandler(int);

struct itimerval timervalue;
struct sigaction newHandler, oldHandler;


int timerInit(int mSec, void (*pHandlerFunc)(void))
{
	/* Copy handler function pointer */
	ptrTimerHandlerFunc = pHandlerFunc;

	/* setup handler for SigAlrm */
	memset(&newHandler, 0, sizeof(newHandler));
	newHandler.sa_handler = &__timerSigHandler;
	newHandler.sa_flags = SA_NOMASK;
	if(sigaction(SIGALRM, &newHandler, &oldHandler))
	{
		printf("\nError: sigaction()\n");
		return(1);
	}
	
	/* Setup timer interval values */
	timervalue.it_value.tv_sec = mSec / 1000;
	timervalue.it_value.tv_usec = (mSec % 1000) * 1000;
	
	/* Setup repitition interval values */
	timervalue.it_interval.tv_sec = mSec / 1000;
	timervalue.it_interval.tv_usec = (mSec % 1000) * 1000;

	if(setitimer(ITIMER_REAL, &timervalue, NULL))
	{
		printf("\nError: setitimer()\n");
		return(1);
	}
	
	return(0);
}


void __timerSigHandler(int arg)
{
	ptrTimerHandlerFunc();
}


void timerStop(void)
{
	timervalue.it_interval.tv_sec = 0;
	timervalue.it_interval.tv_usec = 0;
	timervalue.it_value.tv_sec = 0;
	timervalue.it_value.tv_usec = 0;
	setitimer(ITIMER_REAL, &timervalue, NULL);

	sigaction(SIGALRM, &oldHandler, NULL);
}

#else

HANDLE win_timer;
VOID CALLBACK __timerSigHandler(PVOID, BOOLEAN);


int timerInit(int mSec, void (*pHandlerFunc)(void))
{
	/* Copy handler function pointer */
	ptrTimerHandlerFunc = pHandlerFunc;

	if(CreateTimerQueueTimer(&win_timer, NULL, (WAITORTIMERCALLBACK)__timerSigHandler, NULL, mSec, mSec, WT_EXECUTEINTIMERTHREAD) == 0)
	{
		printf("\nError: CreateTimerQueueTimer()\n");
		return(1);
	}

	return(0);
}


VOID CALLBACK __timerSigHandler(PVOID lpParameter, BOOLEAN TimerOrWaitFired)
{
	ptrTimerHandlerFunc();
}


void timerStop(void)
{
	DeleteTimerQueueTimer(NULL, win_timer, NULL);
	CloseHandle(win_timer);
}

#endif













