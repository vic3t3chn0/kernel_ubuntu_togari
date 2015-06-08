/*
 * Copyright 2009 IBM Corporation.
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version
 *  2 of the License, or (at your option) any later version.
 */

#ifndef __ICS_H
#define __ICS_H

#define XIVE_ADDR_MASK		0x7FFULL

extern void wsp_init_irq(void);

extern int wsp_ics_alloc_irq(struct device_node *dn, int num);
extern void wsp_ics_free_irq(struct device_node *dn, unsigned int irq);

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#ifdef CONFIG_PCI_MSI
extern void wsp_ics_set_msi_chip(unsigned int irq);
extern void wsp_ics_set_std_chip(unsigned int irq);
#endif /* CONFIG_PCI_MSI */

<<<<<<< HEAD
=======
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#endif /* __ICS_H */
