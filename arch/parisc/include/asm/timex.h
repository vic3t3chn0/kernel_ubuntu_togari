/*
 * linux/include/asm-parisc/timex.h
 *
 * PARISC architecture timex specifications
 */
#ifndef _ASMPARISC_TIMEX_H
#define _ASMPARISC_TIMEX_H

<<<<<<< HEAD
=======
#include <asm/system.h>
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

#define CLOCK_TICK_RATE	1193180 /* Underlying HZ */

typedef unsigned long cycles_t;

static inline cycles_t get_cycles (void)
{
	return mfctl(16);
}

#endif
