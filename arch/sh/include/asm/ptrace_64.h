#ifndef __ASM_SH_PTRACE_64_H
#define __ASM_SH_PTRACE_64_H

struct pt_regs {
	unsigned long long pc;
	unsigned long long sr;
	long long syscall_nr;
	unsigned long long regs[63];
	unsigned long long tregs[8];
	unsigned long long pad[2];
};

#ifdef __KERNEL__

#define MAX_REG_OFFSET		offsetof(struct pt_regs, tregs[7])
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static inline long regs_return_value(struct pt_regs *regs)
{
	return regs->regs[3];
}
<<<<<<< HEAD
=======
=======
#define regs_return_value(_regs)	((_regs)->regs[3])
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#endif /* __KERNEL__ */

#endif /* __ASM_SH_PTRACE_64_H */
