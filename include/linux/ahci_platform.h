/*
 * AHCI SATA platform driver
 *
 * Copyright 2004-2005  Red Hat, Inc.
 *   Jeff Garzik <jgarzik@pobox.com>
 * Copyright 2010  MontaVista Software, LLC.
 *   Anton Vorontsov <avorontsov@ru.mvista.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 */

#ifndef _AHCI_PLATFORM_H
#define _AHCI_PLATFORM_H

#include <linux/compiler.h>

struct device;
struct ata_port_info;

struct ahci_platform_data {
	int (*init)(struct device *dev, void __iomem *addr);
	void (*exit)(struct device *dev);
<<<<<<< HEAD
	int (*suspend)(struct device *dev);
	int (*resume)(struct device *dev);
=======
<<<<<<< HEAD
	int (*suspend)(struct device *dev);
	int (*resume)(struct device *dev);
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	const struct ata_port_info *ata_port_info;
	unsigned int force_port_map;
	unsigned int mask_port_map;
};

#endif /* _AHCI_PLATFORM_H */
