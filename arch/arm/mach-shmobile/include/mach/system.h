#ifndef __ASM_ARCH_SYSTEM_H
#define __ASM_ARCH_SYSTEM_H

<<<<<<< HEAD
#include <asm/system_misc.h>

static inline void arch_reset(char mode, const char *cmd)
{
	soft_restart(0);
=======
static inline void arch_idle(void)
{
	cpu_do_idle();
}

static inline void arch_reset(char mode, const char *cmd)
{
	cpu_reset(0);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
}

#endif
