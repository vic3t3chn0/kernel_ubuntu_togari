#include <mach/hardware.h>
#include <asm/hardware/entry-macro-iomd.S>

	.equ	ioc_base_high, IOC_BASE & 0xff000000
	.equ	ioc_base_low, IOC_BASE & 0x00ff0000

	.macro  get_irqnr_preamble, base, tmp
	mov	\base, #ioc_base_high		@ point at IOC
	.if	ioc_base_low
	orr	\base, \base, #ioc_base_low
	.endif
	.endm
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======

	.macro  arch_ret_to_user, tmp1, tmp2
	.endm

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
