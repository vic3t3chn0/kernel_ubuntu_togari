#ifndef _ASM_SCORE_BUG_H
#define _ASM_SCORE_BUG_H

#include <asm-generic/bug.h>

<<<<<<< HEAD
struct pt_regs;
extern void __die(const char *, struct pt_regs *, const char *,
	const char *, unsigned long) __attribute__((noreturn));
extern void __die_if_kernel(const char *, struct pt_regs *, const char *,
	const char *, unsigned long);

#define die(msg, regs)							\
	__die(msg, regs, __FILE__ ":", __func__, __LINE__)
#define die_if_kernel(msg, regs)					\
	__die_if_kernel(msg, regs, __FILE__ ":", __func__, __LINE__)

=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
#endif /* _ASM_SCORE_BUG_H */
