/*
 * arch/arm/mach-at91/include/mach/at91_st.h
 *
 * Copyright (C) 2005 Ivan Kokshaysky
 * Copyright (C) SAN People
 *
 * System Timer (ST) - System peripherals registers.
 * Based on AT91RM9200 datasheet revision E.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef AT91_ST_H
#define AT91_ST_H

<<<<<<< HEAD
#ifndef __ASSEMBLY__
extern void __iomem *at91_st_base;

#define at91_st_read(field) \
	__raw_readl(at91_st_base + field)

#define at91_st_write(field, value) \
	__raw_writel(value, at91_st_base + field);
#else
.extern at91_st_base
#endif

#define	AT91_ST_CR		0x00			/* Control Register */
#define 	AT91_ST_WDRST		(1 << 0)		/* Watchdog Timer Restart */

#define	AT91_ST_PIMR		0x04			/* Period Interval Mode Register */
#define		AT91_ST_PIV		(0xffff <<  0)		/* Period Interval Value */

#define	AT91_ST_WDMR		0x08			/* Watchdog Mode Register */
=======
#define	AT91_ST_CR		(AT91_ST + 0x00)	/* Control Register */
#define 	AT91_ST_WDRST		(1 << 0)		/* Watchdog Timer Restart */

#define	AT91_ST_PIMR		(AT91_ST + 0x04)	/* Period Interval Mode Register */
#define		AT91_ST_PIV		(0xffff <<  0)		/* Period Interval Value */

#define	AT91_ST_WDMR		(AT91_ST + 0x08)	/* Watchdog Mode Register */
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
#define		AT91_ST_WDV		(0xffff <<  0)		/* Watchdog Counter Value */
#define		AT91_ST_RSTEN		(1	<< 16)		/* Reset Enable */
#define		AT91_ST_EXTEN		(1	<< 17)		/* External Signal Assertion Enable */

<<<<<<< HEAD
#define	AT91_ST_RTMR		0x0c			/* Real-time Mode Register */
#define		AT91_ST_RTPRES		(0xffff <<  0)		/* Real-time Prescalar Value */

#define	AT91_ST_SR		0x10			/* Status Register */
=======
#define	AT91_ST_RTMR		(AT91_ST + 0x0c)	/* Real-time Mode Register */
#define		AT91_ST_RTPRES		(0xffff <<  0)		/* Real-time Prescalar Value */

#define	AT91_ST_SR		(AT91_ST + 0x10)	/* Status Register */
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
#define		AT91_ST_PITS		(1 << 0)		/* Period Interval Timer Status */
#define		AT91_ST_WDOVF		(1 << 1) 		/* Watchdog Overflow */
#define		AT91_ST_RTTINC		(1 << 2) 		/* Real-time Timer Increment */
#define		AT91_ST_ALMS		(1 << 3) 		/* Alarm Status */

<<<<<<< HEAD
#define	AT91_ST_IER		0x14			/* Interrupt Enable Register */
#define	AT91_ST_IDR		0x18			/* Interrupt Disable Register */
#define	AT91_ST_IMR		0x1c			/* Interrupt Mask Register */

#define	AT91_ST_RTAR		0x20			/* Real-time Alarm Register */
#define		AT91_ST_ALMV		(0xfffff << 0)		/* Alarm Value */

#define	AT91_ST_CRTR		0x24			/* Current Real-time Register */
=======
#define	AT91_ST_IER		(AT91_ST + 0x14)	/* Interrupt Enable Register */
#define	AT91_ST_IDR		(AT91_ST + 0x18)	/* Interrupt Disable Register */
#define	AT91_ST_IMR		(AT91_ST + 0x1c)	/* Interrupt Mask Register */

#define	AT91_ST_RTAR		(AT91_ST + 0x20)	/* Real-time Alarm Register */
#define		AT91_ST_ALMV		(0xfffff << 0)		/* Alarm Value */

#define	AT91_ST_CRTR		(AT91_ST + 0x24)	/* Current Real-time Register */
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
#define		AT91_ST_CRTV		(0xfffff << 0)		/* Current Real-Time Value */

#endif
