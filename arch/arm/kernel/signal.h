/*
 *  linux/arch/arm/kernel/signal.h
 *
 *  Copyright (C) 2005-2009 Russell King.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#define KERN_SIGRETURN_CODE	(CONFIG_VECTORS_BASE + 0x00000500)
#define KERN_RESTART_CODE	(KERN_SIGRETURN_CODE + sizeof(sigreturn_codes))

<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
extern const unsigned long sigreturn_codes[7];
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
extern const unsigned long syscall_restart_code[2];
