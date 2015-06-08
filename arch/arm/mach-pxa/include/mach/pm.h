/*
 * Copyright (c) 2005 Richard Purdie
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#include <linux/suspend.h>

struct pxa_cpu_pm_fns {
	int	save_count;
	void	(*save)(unsigned long *);
	void	(*restore)(unsigned long *);
	int	(*valid)(suspend_state_t state);
	void	(*enter)(suspend_state_t state);
	int	(*prepare)(void);
	void	(*finish)(void);
};

extern struct pxa_cpu_pm_fns *pxa_cpu_pm_fns;

/* sleep.S */
<<<<<<< HEAD
extern int pxa25x_finish_suspend(unsigned long);
extern int pxa27x_finish_suspend(unsigned long);
=======
<<<<<<< HEAD
extern int pxa25x_finish_suspend(unsigned long);
extern int pxa27x_finish_suspend(unsigned long);
=======
extern void pxa25x_cpu_suspend(unsigned int, long);
extern void pxa27x_cpu_suspend(unsigned int, long);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

extern int pxa_pm_enter(suspend_state_t state);
extern int pxa_pm_prepare(void);
extern void pxa_pm_finish(void);

/* NOTE: this is for PM debugging on Lubbock,  it's really a big
 * ugly, but let's keep the crap minimum here, instead of direct
 * accessing the LUBBOCK CPLD registers in arch/arm/mach-pxa/pm.c
 */
#ifdef CONFIG_ARCH_LUBBOCK
extern void lubbock_set_hexled(uint32_t value);
#else
#define lubbock_set_hexled(x)
#endif
