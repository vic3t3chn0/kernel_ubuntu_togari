#ifndef _LINUX_IRQ_WORK_H
#define _LINUX_IRQ_WORK_H

<<<<<<< HEAD
#include <linux/llist.h>

struct irq_work {
	unsigned long flags;
	struct llist_node llnode;
=======
struct irq_work {
	struct irq_work *next;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	void (*func)(struct irq_work *);
};

static inline
<<<<<<< HEAD
void init_irq_work(struct irq_work *work, void (*func)(struct irq_work *))
{
	work->flags = 0;
	work->func = func;
}

bool irq_work_queue(struct irq_work *work);
void irq_work_run(void);
void irq_work_sync(struct irq_work *work);
=======
void init_irq_work(struct irq_work *entry, void (*func)(struct irq_work *))
{
	entry->next = NULL;
	entry->func = func;
}

bool irq_work_queue(struct irq_work *entry);
void irq_work_run(void);
void irq_work_sync(struct irq_work *entry);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

#endif /* _LINUX_IRQ_WORK_H */
