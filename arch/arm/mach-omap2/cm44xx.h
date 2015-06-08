/*
 * OMAP4 Clock Management (CM) definitions
 *
<<<<<<< HEAD
 * Copyright (C) 2007-2011 Texas Instruments, Inc.
=======
<<<<<<< HEAD
 * Copyright (C) 2007-2011 Texas Instruments, Inc.
=======
 * Copyright (C) 2007-2009 Texas Instruments, Inc.
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * Copyright (C) 2007-2009 Nokia Corporation
 *
 * Written by Paul Walmsley
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * OMAP4 has two separate CM blocks, CM1 and CM2.  This file contains
 * macros and function prototypes that are applicable to both.
 */
#ifndef __ARCH_ASM_MACH_OMAP2_CM44XX_H
#define __ARCH_ASM_MACH_OMAP2_CM44XX_H


#include "prcm-common.h"
#include "cm.h"

#define OMAP4_CM_CLKSTCTRL				0x0000
#define OMAP4_CM_STATICDEP				0x0004

<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
/* Function prototypes */
# ifndef __ASSEMBLER__

extern int omap4_cm_wait_module_ready(void __iomem *clkctrl_reg);

# endif
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#endif
