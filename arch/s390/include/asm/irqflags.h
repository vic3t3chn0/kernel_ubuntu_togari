/*
 *    Copyright IBM Corp. 2006,2010
 *    Author(s): Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#ifndef __ASM_IRQFLAGS_H
#define __ASM_IRQFLAGS_H

#include <linux/types.h>

/* store then OR system mask. */
#define __arch_local_irq_stosm(__or)					\
({									\
	unsigned long __mask;						\
	asm volatile(							\
		"	stosm	%0,%1"					\
		: "=Q" (__mask) : "i" (__or) : "memory");		\
	__mask;								\
})

/* store then AND system mask. */
#define __arch_local_irq_stnsm(__and)					\
({									\
	unsigned long __mask;						\
	asm volatile(							\
		"	stnsm	%0,%1"					\
		: "=Q" (__mask) : "i" (__and) : "memory");		\
	__mask;								\
})

/* set system mask. */
<<<<<<< HEAD
static inline notrace void __arch_local_irq_ssm(unsigned long flags)
=======
<<<<<<< HEAD
static inline notrace void __arch_local_irq_ssm(unsigned long flags)
=======
static inline void __arch_local_irq_ssm(unsigned long flags)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	asm volatile("ssm   %0" : : "Q" (flags) : "memory");
}

<<<<<<< HEAD
static inline notrace unsigned long arch_local_save_flags(void)
=======
<<<<<<< HEAD
static inline notrace unsigned long arch_local_save_flags(void)
=======
static inline unsigned long arch_local_save_flags(void)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	return __arch_local_irq_stosm(0x00);
}

<<<<<<< HEAD
static inline notrace unsigned long arch_local_irq_save(void)
=======
<<<<<<< HEAD
static inline notrace unsigned long arch_local_irq_save(void)
=======
static inline unsigned long arch_local_irq_save(void)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	return __arch_local_irq_stnsm(0xfc);
}

<<<<<<< HEAD
static inline notrace void arch_local_irq_disable(void)
=======
<<<<<<< HEAD
static inline notrace void arch_local_irq_disable(void)
=======
static inline void arch_local_irq_disable(void)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	arch_local_irq_save();
}

<<<<<<< HEAD
static inline notrace void arch_local_irq_enable(void)
=======
<<<<<<< HEAD
static inline notrace void arch_local_irq_enable(void)
=======
static inline void arch_local_irq_enable(void)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	__arch_local_irq_stosm(0x03);
}

<<<<<<< HEAD
static inline notrace void arch_local_irq_restore(unsigned long flags)
=======
<<<<<<< HEAD
static inline notrace void arch_local_irq_restore(unsigned long flags)
=======
static inline void arch_local_irq_restore(unsigned long flags)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	__arch_local_irq_ssm(flags);
}

<<<<<<< HEAD
static inline notrace bool arch_irqs_disabled_flags(unsigned long flags)
=======
<<<<<<< HEAD
static inline notrace bool arch_irqs_disabled_flags(unsigned long flags)
=======
static inline bool arch_irqs_disabled_flags(unsigned long flags)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	return !(flags & (3UL << (BITS_PER_LONG - 8)));
}

<<<<<<< HEAD
static inline notrace bool arch_irqs_disabled(void)
=======
<<<<<<< HEAD
static inline notrace bool arch_irqs_disabled(void)
=======
static inline bool arch_irqs_disabled(void)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	return arch_irqs_disabled_flags(arch_local_save_flags());
}

#endif /* __ASM_IRQFLAGS_H */
