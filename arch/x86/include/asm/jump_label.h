#ifndef _ASM_X86_JUMP_LABEL_H
#define _ASM_X86_JUMP_LABEL_H

#ifdef __KERNEL__

#include <linux/types.h>
#include <asm/nops.h>
#include <asm/asm.h>

#define JUMP_LABEL_NOP_SIZE 5

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#define STATIC_KEY_INITIAL_NOP ".byte 0xe9 \n\t .long 0\n\t"

static __always_inline bool arch_static_branch(struct static_key *key)
{
	asm goto("1:"
		STATIC_KEY_INITIAL_NOP
<<<<<<< HEAD
=======
=======
#define JUMP_LABEL_INITIAL_NOP ".byte 0xe9 \n\t .long 0\n\t"

static __always_inline bool arch_static_branch(struct jump_label_key *key)
{
	asm goto("1:"
		JUMP_LABEL_INITIAL_NOP
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		".pushsection __jump_table,  \"aw\" \n\t"
		_ASM_ALIGN "\n\t"
		_ASM_PTR "1b, %l[l_yes], %c0 \n\t"
		".popsection \n\t"
		: :  "i" (key) : : l_yes);
	return false;
l_yes:
	return true;
}

#endif /* __KERNEL__ */

#ifdef CONFIG_X86_64
typedef u64 jump_label_t;
#else
typedef u32 jump_label_t;
#endif

struct jump_entry {
	jump_label_t code;
	jump_label_t target;
	jump_label_t key;
};

#endif
