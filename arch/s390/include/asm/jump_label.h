#ifndef _ASM_S390_JUMP_LABEL_H
#define _ASM_S390_JUMP_LABEL_H

#include <linux/types.h>

#define JUMP_LABEL_NOP_SIZE 6

#ifdef CONFIG_64BIT
#define ASM_PTR ".quad"
#define ASM_ALIGN ".balign 8"
#else
#define ASM_PTR ".long"
#define ASM_ALIGN ".balign 4"
#endif

<<<<<<< HEAD
static __always_inline bool arch_static_branch(struct static_key *key)
=======
<<<<<<< HEAD
static __always_inline bool arch_static_branch(struct static_key *key)
=======
static __always_inline bool arch_static_branch(struct jump_label_key *key)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	asm goto("0:	brcl 0,0\n"
		".pushsection __jump_table, \"aw\"\n"
		ASM_ALIGN "\n"
		ASM_PTR " 0b, %l[label], %0\n"
		".popsection\n"
		: : "X" (key) : : label);
	return false;
label:
	return true;
}

typedef unsigned long jump_label_t;

struct jump_entry {
	jump_label_t code;
	jump_label_t target;
	jump_label_t key;
};

#endif
