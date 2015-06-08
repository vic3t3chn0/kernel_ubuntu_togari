/*
 * atomic32.c: 32-bit atomic_t implementation
 *
 * Copyright (C) 2004 Keith M Wesolowski
 * Copyright (C) 2007 Kyle McMartin
 * 
 * Based on asm-parisc/atomic.h Copyright (C) 2000 Philipp Rumpf
 */

<<<<<<< HEAD
#include <linux/atomic.h>
=======
<<<<<<< HEAD
#include <linux/atomic.h>
=======
#include <asm/atomic.h>
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <linux/spinlock.h>
#include <linux/module.h>

#ifdef CONFIG_SMP
#define ATOMIC_HASH_SIZE	4
#define ATOMIC_HASH(a)	(&__atomic_hash[(((unsigned long)a)>>8) & (ATOMIC_HASH_SIZE-1)])

spinlock_t __atomic_hash[ATOMIC_HASH_SIZE] = {
	[0 ... (ATOMIC_HASH_SIZE-1)] = __SPIN_LOCK_UNLOCKED(__atomic_hash)
};

#else /* SMP */

static DEFINE_SPINLOCK(dummy);
#define ATOMIC_HASH_SIZE	1
#define ATOMIC_HASH(a)		(&dummy)

#endif /* SMP */

int __atomic_add_return(int i, atomic_t *v)
{
	int ret;
	unsigned long flags;
	spin_lock_irqsave(ATOMIC_HASH(v), flags);

	ret = (v->counter += i);

	spin_unlock_irqrestore(ATOMIC_HASH(v), flags);
	return ret;
}
EXPORT_SYMBOL(__atomic_add_return);

int atomic_cmpxchg(atomic_t *v, int old, int new)
{
	int ret;
	unsigned long flags;

	spin_lock_irqsave(ATOMIC_HASH(v), flags);
	ret = v->counter;
	if (likely(ret == old))
		v->counter = new;

	spin_unlock_irqrestore(ATOMIC_HASH(v), flags);
	return ret;
}
EXPORT_SYMBOL(atomic_cmpxchg);

<<<<<<< HEAD
int __atomic_add_unless(atomic_t *v, int a, int u)
=======
<<<<<<< HEAD
int __atomic_add_unless(atomic_t *v, int a, int u)
=======
int atomic_add_unless(atomic_t *v, int a, int u)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	int ret;
	unsigned long flags;

	spin_lock_irqsave(ATOMIC_HASH(v), flags);
	ret = v->counter;
	if (ret != u)
		v->counter += a;
	spin_unlock_irqrestore(ATOMIC_HASH(v), flags);
<<<<<<< HEAD
	return ret;
}
EXPORT_SYMBOL(__atomic_add_unless);
=======
<<<<<<< HEAD
	return ret;
}
EXPORT_SYMBOL(__atomic_add_unless);
=======
	return ret != u;
}
EXPORT_SYMBOL(atomic_add_unless);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/* Atomic operations are already serializing */
void atomic_set(atomic_t *v, int i)
{
	unsigned long flags;

	spin_lock_irqsave(ATOMIC_HASH(v), flags);
	v->counter = i;
	spin_unlock_irqrestore(ATOMIC_HASH(v), flags);
}
EXPORT_SYMBOL(atomic_set);

unsigned long ___set_bit(unsigned long *addr, unsigned long mask)
{
	unsigned long old, flags;

	spin_lock_irqsave(ATOMIC_HASH(addr), flags);
	old = *addr;
	*addr = old | mask;
	spin_unlock_irqrestore(ATOMIC_HASH(addr), flags);

	return old & mask;
}
EXPORT_SYMBOL(___set_bit);

unsigned long ___clear_bit(unsigned long *addr, unsigned long mask)
{
	unsigned long old, flags;

	spin_lock_irqsave(ATOMIC_HASH(addr), flags);
	old = *addr;
	*addr = old & ~mask;
	spin_unlock_irqrestore(ATOMIC_HASH(addr), flags);

	return old & mask;
}
EXPORT_SYMBOL(___clear_bit);

unsigned long ___change_bit(unsigned long *addr, unsigned long mask)
{
	unsigned long old, flags;

	spin_lock_irqsave(ATOMIC_HASH(addr), flags);
	old = *addr;
	*addr = old ^ mask;
	spin_unlock_irqrestore(ATOMIC_HASH(addr), flags);

	return old & mask;
}
EXPORT_SYMBOL(___change_bit);

unsigned long __cmpxchg_u32(volatile u32 *ptr, u32 old, u32 new)
{
	unsigned long flags;
	u32 prev;

	spin_lock_irqsave(ATOMIC_HASH(ptr), flags);
	if ((prev = *ptr) == old)
		*ptr = new;
	spin_unlock_irqrestore(ATOMIC_HASH(ptr), flags);

	return (unsigned long)prev;
}
EXPORT_SYMBOL(__cmpxchg_u32);
