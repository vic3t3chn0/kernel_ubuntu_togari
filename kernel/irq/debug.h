/*
 * Debugging printout:
 */

#include <linux/kallsyms.h>

<<<<<<< HEAD
<<<<<<< HEAD
#define ___P(f) if (desc->status_use_accessors & f) printk("%14s set\n", #f)
#define ___PS(f) if (desc->istate & f) printk("%14s set\n", #f)
/* FIXME */
#define ___PD(f) do { } while (0)
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#define P(f) if (desc->status_use_accessors & f) printk("%14s set\n", #f)
#define PS(f) if (desc->istate & f) printk("%14s set\n", #f)
/* FIXME */
#define PD(f) do { } while (0)
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

static inline void print_irq_desc(unsigned int irq, struct irq_desc *desc)
{
	printk("irq %d, desc: %p, depth: %d, count: %d, unhandled: %d\n",
		irq, desc, desc->depth, desc->irq_count, desc->irqs_unhandled);
	printk("->handle_irq():  %p, ", desc->handle_irq);
	print_symbol("%s\n", (unsigned long)desc->handle_irq);
	printk("->irq_data.chip(): %p, ", desc->irq_data.chip);
	print_symbol("%s\n", (unsigned long)desc->irq_data.chip);
	printk("->action(): %p\n", desc->action);
	if (desc->action) {
		printk("->action->handler(): %p, ", desc->action->handler);
		print_symbol("%s\n", (unsigned long)desc->action->handler);
	}

<<<<<<< HEAD
<<<<<<< HEAD
	___P(IRQ_LEVEL);
	___P(IRQ_PER_CPU);
	___P(IRQ_NOPROBE);
	___P(IRQ_NOREQUEST);
	___P(IRQ_NOTHREAD);
	___P(IRQ_NOAUTOEN);

	___PS(IRQS_AUTODETECT);
	___PS(IRQS_REPLAY);
	___PS(IRQS_WAITING);
	___PS(IRQS_PENDING);

	___PD(IRQS_INPROGRESS);
	___PD(IRQS_DISABLED);
	___PD(IRQS_MASKED);
}

#undef ___P
#undef ___PS
#undef ___PD
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	P(IRQ_LEVEL);
	P(IRQ_PER_CPU);
	P(IRQ_NOPROBE);
	P(IRQ_NOREQUEST);
	P(IRQ_NOTHREAD);
	P(IRQ_NOAUTOEN);

	PS(IRQS_AUTODETECT);
	PS(IRQS_REPLAY);
	PS(IRQS_WAITING);
	PS(IRQS_PENDING);

	PD(IRQS_INPROGRESS);
	PD(IRQS_DISABLED);
	PD(IRQS_MASKED);
}

#undef P
#undef PS
#undef PD
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
