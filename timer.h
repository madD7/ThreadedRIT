#ifndef __TIMER_H_
#define __TIMER_H_

#include <stdio.h>


#ifdef __linux__

#include <sys/time.h>
#include <signal.h>

#else
	/* this code only works on win2000, XP, Vista, 7 and up */
	/* win95, win98 and ME are not supported                */
	/* WINVER must have value 0x500 or higher               */
	#ifndef WINVER
		#define WINVER 0x500
	#endif

	#if WINVER < 0x500
		#error "WINVER is < 0x500, cannot compile for old windows versions"
	#endif

	#include <windows.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


int timerInit(int, void (*)(void));
void timerStop(void);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif


