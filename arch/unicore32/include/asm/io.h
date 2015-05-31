/*
 * linux/arch/unicore32/include/asm/io.h
 *
 * Code specific to PKUnity SoC and UniCore ISA
 *
 * Copyright (C) 2001-2010 GUAN Xue-tao
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef __UNICORE_IO_H__
#define __UNICORE_IO_H__

#ifdef __KERNEL__

#include <asm/byteorder.h>
#include <asm/memory.h>
<<<<<<< HEAD
=======
#include <asm/system.h>
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

#define PCI_IOBASE	PKUNITY_PCILIO_BASE
#include <asm-generic/io.h>

/*
 * __uc32_ioremap and __uc32_ioremap_cached takes CPU physical address.
 */
extern void __iomem *__uc32_ioremap(unsigned long, size_t);
extern void __iomem *__uc32_ioremap_cached(unsigned long, size_t);
extern void __uc32_iounmap(volatile void __iomem *addr);

/*
 * ioremap and friends.
 *
 * ioremap takes a PCI memory address, as specified in
<<<<<<< HEAD
 * Documentation/io-mapping.txt.
=======
 * Documentation/IO-mapping.txt.
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
 *
 */
#define ioremap(cookie, size)		__uc32_ioremap(cookie, size)
#define ioremap_cached(cookie, size)	__uc32_ioremap_cached(cookie, size)
<<<<<<< HEAD
#define ioremap_nocache(cookie, size)	__uc32_ioremap(cookie, size)
#define iounmap(cookie)			__uc32_iounmap(cookie)

=======
#define iounmap(cookie)			__uc32_iounmap(cookie)

/*
 * Convert a physical pointer to a virtual kernel pointer for /dev/mem
 * access
 */
#undef xlate_dev_mem_ptr
#define xlate_dev_mem_ptr(p)	__va(p)

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
#define HAVE_ARCH_PIO_SIZE
#define PIO_OFFSET		(unsigned int)(PCI_IOBASE)
#define PIO_MASK		(unsigned int)(IO_SPACE_LIMIT)
#define PIO_RESERVED		(PIO_OFFSET + PIO_MASK + 1)

#endif	/* __KERNEL__ */
#endif	/* __UNICORE_IO_H__ */
