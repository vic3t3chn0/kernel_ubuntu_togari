#ifdef __ASSEMBLY__

#include <asm/asm.h>

#ifdef CONFIG_SMP
	.macro LOCK_PREFIX
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
672:	lock
	.section .smp_locks,"a"
	.balign 4
	.long 672b - .
<<<<<<< HEAD
=======
=======
1:	lock
	.section .smp_locks,"a"
	.balign 4
	.long 1b - .
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	.previous
	.endm
#else
	.macro LOCK_PREFIX
	.endm
#endif

.macro altinstruction_entry orig alt feature orig_len alt_len
<<<<<<< HEAD
	.long \orig - .
	.long \alt - .
=======
<<<<<<< HEAD
	.long \orig - .
	.long \alt - .
=======
	.align 8
	.quad \orig
	.quad \alt
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	.word \feature
	.byte \orig_len
	.byte \alt_len
.endm

#endif  /*  __ASSEMBLY__  */
