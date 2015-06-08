/*
 * arch/arm/mach-ixp23xx/include/mach/hardware.h
 *
 * Copyright (C) 2002-2004 Intel Corporation.
 * Copyricht (C) 2005 MontaVista Software, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Hardware definitions for IXP23XX based systems
 */

#ifndef __ASM_ARCH_HARDWARE_H
#define __ASM_ARCH_HARDWARE_H

/* PCI IO info */
<<<<<<< HEAD

#include "ixp23xx.h"

=======
<<<<<<< HEAD

#include "ixp23xx.h"

=======
#define PCIBIOS_MIN_IO		0x00000000
#define PCIBIOS_MIN_MEM		0xe0000000

#include "ixp23xx.h"

#define pcibios_assign_all_busses()	0

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/*
 * Platform helper functions
 */
#include "platform.h"

/*
 * Platform-specific headers
 */
#include "ixdp2351.h"


#endif
