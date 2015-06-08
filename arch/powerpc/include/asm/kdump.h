#ifndef _PPC64_KDUMP_H
#define _PPC64_KDUMP_H

#include <asm/page.h>

<<<<<<< HEAD
#define KDUMP_KERNELBASE	0x2000000
=======
<<<<<<< HEAD
#define KDUMP_KERNELBASE	0x2000000
=======
/*
 * If CONFIG_RELOCATABLE is enabled we can place the kdump kernel anywhere.
 * To keep enough space in the RMO for the first stage kernel on 64bit, we
 * place it at 64MB. If CONFIG_RELOCATABLE is not enabled we must place
 * the second stage at 32MB.
 */
#if defined(CONFIG_RELOCATABLE) && defined(CONFIG_PPC64)
#define KDUMP_KERNELBASE	0x4000000
#else
#define KDUMP_KERNELBASE	0x2000000
#endif
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/* How many bytes to reserve at zero for kdump. The reserve limit should
 * be greater or equal to the trampoline's end address.
 * Reserve to the end of the FWNMI area, see head_64.S */
#define KDUMP_RESERVE_LIMIT	0x10000 /* 64K */

#ifdef CONFIG_CRASH_DUMP

/*
 * On PPC64 translation is disabled during trampoline setup, so we use
 * physical addresses. Though on PPC32 translation is already enabled,
 * so we can't do the same. Luckily create_trampoline() creates relative
 * branches, so we can just add the PAGE_OFFSET and don't worry about it.
 */
#ifdef __powerpc64__
#define KDUMP_TRAMPOLINE_START	0x0100
#define KDUMP_TRAMPOLINE_END	0x3000
#else
#define KDUMP_TRAMPOLINE_START	(0x0100 + PAGE_OFFSET)
#define KDUMP_TRAMPOLINE_END	(0x3000 + PAGE_OFFSET)
#endif /* __powerpc64__ */

#define KDUMP_MIN_TCE_ENTRIES	2048

#endif /* CONFIG_CRASH_DUMP */

#ifndef __ASSEMBLY__

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#if defined(CONFIG_CRASH_DUMP) && !defined(CONFIG_NONSTATIC_KERNEL)
extern void reserve_kdump_trampoline(void);
extern void setup_kdump_trampoline(void);
#else
/* !CRASH_DUMP || !NONSTATIC_KERNEL */
<<<<<<< HEAD
=======
=======
#if defined(CONFIG_CRASH_DUMP) && !defined(CONFIG_RELOCATABLE)
extern void reserve_kdump_trampoline(void);
extern void setup_kdump_trampoline(void);
#else
/* !CRASH_DUMP || RELOCATABLE */
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static inline void reserve_kdump_trampoline(void) { ; }
static inline void setup_kdump_trampoline(void) { ; }
#endif

#endif /* __ASSEMBLY__ */

#endif /* __PPC64_KDUMP_H */
