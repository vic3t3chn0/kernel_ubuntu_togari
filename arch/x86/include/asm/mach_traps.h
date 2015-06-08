/*
 *  Machine specific NMI handling for generic.
 *  Split out from traps.c by Osamu Tomita <tomita@cinet.co.jp>
 */
#ifndef _ASM_X86_MACH_DEFAULT_MACH_TRAPS_H
#define _ASM_X86_MACH_DEFAULT_MACH_TRAPS_H

#include <asm/mc146818rtc.h>

#define NMI_REASON_PORT		0x61

#define NMI_REASON_SERR		0x80
#define NMI_REASON_IOCHK	0x40
#define NMI_REASON_MASK		(NMI_REASON_SERR | NMI_REASON_IOCHK)

#define NMI_REASON_CLEAR_SERR	0x04
#define NMI_REASON_CLEAR_IOCHK	0x08
#define NMI_REASON_CLEAR_MASK	0x0f

<<<<<<< HEAD
static inline unsigned char default_get_nmi_reason(void)
=======
<<<<<<< HEAD
static inline unsigned char default_get_nmi_reason(void)
=======
static inline unsigned char get_nmi_reason(void)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	return inb(NMI_REASON_PORT);
}

static inline void reassert_nmi(void)
{
	int old_reg = -1;

	if (do_i_have_lock_cmos())
		old_reg = current_lock_cmos_reg();
	else
		lock_cmos(0); /* register doesn't matter here */
	outb(0x8f, 0x70);
	inb(0x71);		/* dummy */
	outb(0x0f, 0x70);
	inb(0x71);		/* dummy */
	if (old_reg >= 0)
		outb(old_reg, 0x70);
	else
		unlock_cmos();
}

#endif /* _ASM_X86_MACH_DEFAULT_MACH_TRAPS_H */
