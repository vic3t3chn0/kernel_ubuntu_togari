/*
 * Common corrected MCE threshold handler code:
 */
#include <linux/interrupt.h>
#include <linux/kernel.h>

#include <asm/irq_vectors.h>
#include <asm/apic.h>
#include <asm/idle.h>
#include <asm/mce.h>

static void default_threshold_interrupt(void)
{
	printk(KERN_ERR "Unexpected threshold interrupt at vector %x\n",
			 THRESHOLD_APIC_VECTOR);
}

void (*mce_threshold_vector)(void) = default_threshold_interrupt;

asmlinkage void smp_threshold_interrupt(void)
{
<<<<<<< HEAD
	irq_enter();
	exit_idle();
=======
<<<<<<< HEAD
	irq_enter();
	exit_idle();
=======
	exit_idle();
	irq_enter();
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	inc_irq_stat(irq_threshold_count);
	mce_threshold_vector();
	irq_exit();
	/* Ack only at the end to avoid potential reentry */
	ack_APIC_irq();
}
