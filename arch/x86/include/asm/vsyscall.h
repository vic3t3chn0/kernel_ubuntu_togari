#ifndef _ASM_X86_VSYSCALL_H
#define _ASM_X86_VSYSCALL_H

enum vsyscall_num {
	__NR_vgettimeofday,
	__NR_vtime,
	__NR_vgetcpu,
};

#define VSYSCALL_START (-10UL << 20)
#define VSYSCALL_SIZE 1024
#define VSYSCALL_END (-2UL << 20)
#define VSYSCALL_MAPPED_PAGES 1
#define VSYSCALL_ADDR(vsyscall_nr) (VSYSCALL_START+VSYSCALL_SIZE*(vsyscall_nr))

#ifdef __KERNEL__
#include <linux/seqlock.h>

<<<<<<< HEAD
=======
/* Definitions for CONFIG_GENERIC_TIME definitions */
#define __vsyscall_fn \
	__attribute__ ((unused, __section__(".vsyscall_fn"))) notrace

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
#define VGETCPU_RDTSCP	1
#define VGETCPU_LSL	2

/* kernel space (writeable) */
extern int vgetcpu_mode;
extern struct timezone sys_tz;

#include <asm/vvar.h>

extern void map_vsyscall(void);

<<<<<<< HEAD
/*
 * Called on instruction fetch fault in vsyscall page.
 * Returns true if handled.
 */
extern bool emulate_vsyscall(struct pt_regs *regs, unsigned long address);

=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
#endif /* __KERNEL__ */

#endif /* _ASM_X86_VSYSCALL_H */
