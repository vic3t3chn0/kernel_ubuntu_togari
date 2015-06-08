#ifndef ASMARM_VGA_H
#define ASMARM_VGA_H

#include <linux/io.h>
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

extern unsigned long vga_base;

#define VGA_MAP_MEM(x,s)	(vga_base + (x))
<<<<<<< HEAD
=======
=======
#include <mach/hardware.h>

#define VGA_MAP_MEM(x,s)	(PCIMEM_BASE + (x))
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#define vga_readb(x)	(*((volatile unsigned char *)x))
#define vga_writeb(x,y)	(*((volatile unsigned char *)y) = (x))

#endif
