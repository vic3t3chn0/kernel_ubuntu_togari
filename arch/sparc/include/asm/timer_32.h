/*
 * timer.h:  Definitions for the timer chips on the Sparc.
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 */


#ifndef _SPARC_TIMER_H
#define _SPARC_TIMER_H

<<<<<<< HEAD
#include <asm/cpu_type.h>  /* For SUN4M_NCPUS */
=======
<<<<<<< HEAD
#include <asm/cpu_type.h>  /* For SUN4M_NCPUS */
=======
#include <asm/system.h>  /* For SUN4M_NCPUS */
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <asm/btfixup.h>

extern __volatile__ unsigned int *master_l10_counter;

/* FIXME: Make do_[gs]ettimeofday btfixup calls */
<<<<<<< HEAD
struct timespec;
=======
<<<<<<< HEAD
struct timespec;
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
BTFIXUPDEF_CALL(int, bus_do_settimeofday, struct timespec *tv)
#define bus_do_settimeofday(tv) BTFIXUP_CALL(bus_do_settimeofday)(tv)

#endif /* !(_SPARC_TIMER_H) */
