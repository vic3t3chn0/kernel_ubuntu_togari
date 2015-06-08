#include <asm/assembler.h>

/*
 * Interrupt handling.  Preserves r7, r8, r9
 */
	.macro	arch_irq_handler_default
<<<<<<< HEAD
	get_irqnr_preamble r6, lr
1:	get_irqnr_and_base r0, r2, r6, lr
=======
<<<<<<< HEAD
	get_irqnr_preamble r6, lr
1:	get_irqnr_and_base r0, r2, r6, lr
=======
	get_irqnr_preamble r5, lr
1:	get_irqnr_and_base r0, r6, r5, lr
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	movne	r1, sp
	@
	@ routine called with r0 = irq number, r1 = struct pt_regs *
	@
	adrne	lr, BSYM(1b)
	bne	asm_do_IRQ

#ifdef CONFIG_SMP
	/*
	 * XXX
	 *
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	 * this macro assumes that irqstat (r2) and base (r6) are
	 * preserved from get_irqnr_and_base above
	 */
	ALT_SMP(test_for_ipi r0, r2, r6, lr)
<<<<<<< HEAD
=======
=======
	 * this macro assumes that irqstat (r6) and base (r5) are
	 * preserved from get_irqnr_and_base above
	 */
	ALT_SMP(test_for_ipi r0, r6, r5, lr)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	ALT_UP_B(9997f)
	movne	r1, sp
	adrne	lr, BSYM(1b)
	bne	do_IPI
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======

#ifdef CONFIG_LOCAL_TIMERS
	test_for_ltirq r0, r6, r5, lr
	movne	r0, sp
	adrne	lr, BSYM(1b)
	bne	do_local_timer
#endif
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#endif
9997:
	.endm

	.macro	arch_irq_handler, symbol_name
	.align	5
	.global \symbol_name
\symbol_name:
<<<<<<< HEAD
	mov	r8, lr
	arch_irq_handler_default
	mov     pc, r8
=======
<<<<<<< HEAD
	mov	r8, lr
	arch_irq_handler_default
	mov     pc, r8
=======
	mov	r4, lr
	arch_irq_handler_default
	mov     pc, r4
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	.endm
