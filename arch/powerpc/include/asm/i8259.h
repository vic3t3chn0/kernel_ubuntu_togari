#ifndef _ASM_POWERPC_I8259_H
#define _ASM_POWERPC_I8259_H
#ifdef __KERNEL__

#include <linux/irq.h>

extern void i8259_init(struct device_node *node, unsigned long intack_addr);
extern unsigned int i8259_irq(void);
<<<<<<< HEAD
extern struct irq_domain *i8259_get_host(void);
=======
<<<<<<< HEAD
extern struct irq_domain *i8259_get_host(void);
=======
extern struct irq_host *i8259_get_host(void);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#endif /* __KERNEL__ */
#endif /* _ASM_POWERPC_I8259_H */
