/*
 * arch/arm/mach-vt8500/include/mach/system.h
 *
 */
#include <asm/io.h>

/* PM Software Reset request register */
#define VT8500_PMSR_VIRT	0xf8130060

<<<<<<< HEAD
=======
static inline void arch_idle(void)
{
	cpu_do_idle();
}

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
static inline void arch_reset(char mode, const char *cmd)
{
	writel(1, VT8500_PMSR_VIRT);
}
