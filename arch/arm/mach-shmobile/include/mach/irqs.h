#ifndef __ASM_MACH_IRQS_H
#define __ASM_MACH_IRQS_H

<<<<<<< HEAD
#include <linux/sh_intc.h>
=======
<<<<<<< HEAD
#include <linux/sh_intc.h>
=======
#define NR_IRQS         1024
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/* GIC */
#define gic_spi(nr)		((nr) + 32)

<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
/* INTCA */
#define evt2irq(evt)		(((evt) >> 5) - 16)
#define irq2evt(irq)		(((irq) + 16) << 5)

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/* INTCS */
#define INTCS_VECT_BASE		0x2200
#define INTCS_VECT(n, vect)	INTC_VECT((n), INTCS_VECT_BASE + (vect))
#define intcs_evt2irq(evt)	evt2irq(INTCS_VECT_BASE + (evt))

#endif /* __ASM_MACH_IRQS_H */
