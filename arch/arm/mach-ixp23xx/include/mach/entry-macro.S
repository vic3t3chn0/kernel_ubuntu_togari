/*
 * arch/arm/mach-ixp23xx/include/mach/entry-macro.S
 */

<<<<<<< HEAD
		.macro  get_irqnr_preamble, base, tmp
		.endm

=======
<<<<<<< HEAD
		.macro  get_irqnr_preamble, base, tmp
		.endm

=======
		.macro	disable_fiq
		.endm

		.macro  get_irqnr_preamble, base, tmp
		.endm

		.macro  arch_ret_to_user, tmp1, tmp2
		.endm

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		.macro	get_irqnr_and_base, irqnr, irqstat, base, tmp
		ldr	\irqnr, =(IXP23XX_INTC_VIRT + IXP23XX_INTR_IRQ_ENC_ST_OFFSET)
		ldr	\irqnr, [\irqnr]	@ get interrupt number
		cmp	\irqnr, #0x0		@ spurious interrupt ?
		movne	\irqnr, \irqnr, lsr #2	@ skip unwanted low order bits
		subne	\irqnr, \irqnr, #1	@ convert to 0 based

#if 0
		cmp	\irqnr, #IRQ_IXP23XX_PCI_INT_RPH
		bne	1001f
		mov	\irqnr, #IRQ_IXP23XX_INTA

		ldr	\irqnr, =0xf5000030

		mov	\tmp, #(1<<26)
		tst	\irqnr, \tmp
		movne	\irqnr, #IRQ_IXP23XX_INTB

		mov	\tmp, #(1<<27)
		tst	\irqnr, \tmp
		movne	\irqnr, #IRQ_IXP23XX_INTA
1001:
#endif
		.endm
