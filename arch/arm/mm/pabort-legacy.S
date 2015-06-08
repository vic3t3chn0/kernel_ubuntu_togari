#include <linux/linkage.h>
#include <asm/assembler.h>

/*
 * Function: legacy_pabort
 *
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * Params  : r2 = pt_regs
 *	   : r4 = address of aborted instruction
 *	   : r5 = psr for parent context
 *
 * Returns : r4 - r11, r13 preserved
<<<<<<< HEAD
=======
=======
 * Params  : r0 = address of aborted instruction
 *
 * Returns : r0 = address of abort
 *	   : r1 = Simulated IFSR with section translation fault status
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * Purpose : obtain information about current prefetch abort.
 */

	.align	5
ENTRY(legacy_pabort)
<<<<<<< HEAD
	mov	r0, r4
	mov	r1, #5
	b	do_PrefetchAbort
=======
<<<<<<< HEAD
	mov	r0, r4
	mov	r1, #5
	b	do_PrefetchAbort
=======
	mov	r1, #5
	mov	pc, lr
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
ENDPROC(legacy_pabort)
