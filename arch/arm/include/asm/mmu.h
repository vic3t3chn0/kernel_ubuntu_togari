#ifndef __ARM_MMU_H
#define __ARM_MMU_H

#ifdef CONFIG_MMU

typedef struct {
#ifdef CONFIG_CPU_HAS_ASID
	unsigned int id;
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	raw_spinlock_t id_lock;
#endif
	unsigned int kvm_seq;
	unsigned long	sigpage;
<<<<<<< HEAD
=======
=======
	spinlock_t id_lock;
#endif
	unsigned int kvm_seq;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
} mm_context_t;

#ifdef CONFIG_CPU_HAS_ASID
#define ASID(mm)	((mm)->context.id & 255)

/* init_mm.context.id_lock should be initialized. */
#define INIT_MM_CONTEXT(name)                                                 \
<<<<<<< HEAD
	.context.id_lock    = __RAW_SPIN_LOCK_UNLOCKED(name.context.id_lock),
=======
<<<<<<< HEAD
	.context.id_lock    = __RAW_SPIN_LOCK_UNLOCKED(name.context.id_lock),
=======
	.context.id_lock    = __SPIN_LOCK_UNLOCKED(name.context.id_lock),
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#else
#define ASID(mm)	(0)
#endif

#else

/*
 * From nommu.h:
 *  Copyright (C) 2002, David McCullough <davidm@snapgear.com>
 *  modified for 2.6 by Hyok S. Choi <hyok.choi@samsung.com>
 */
typedef struct {
	unsigned long		end_brk;
} mm_context_t;

#endif

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/*
 * switch_mm() may do a full cache flush over the context switch,
 * so enable interrupts over the context switch to avoid high
 * latency.
 */
#define __ARCH_WANT_INTERRUPTS_ON_CTXSW

<<<<<<< HEAD
=======
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#endif
