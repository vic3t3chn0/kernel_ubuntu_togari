<<<<<<< HEAD
<<<<<<< HEAD
/* Copyright (c) 2008-2013, The Linux Foundation. All rights reserved.
=======
/* Copyright (c) 2008-2010, Code Aurora Forum. All rights reserved.
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
/* Copyright (c) 2008-2010, Code Aurora Forum. All rights reserved.
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef DIAGMEM_H
#define DIAGMEM_H
#include "diagchar.h"

<<<<<<< HEAD
<<<<<<< HEAD
extern mempool_t *diag_pools_array[NUM_MEMORY_POOLS];

=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
void *diagmem_alloc(struct diagchar_dev *driver, int size, int pool_type);
void diagmem_free(struct diagchar_dev *driver, void *buf, int pool_type);
void diagmem_init(struct diagchar_dev *driver);
void diagmem_exit(struct diagchar_dev *driver, int pool_type);
<<<<<<< HEAD
<<<<<<< HEAD
#ifdef CONFIG_DIAGFWD_BRIDGE_CODE
void diagmem_hsic_init(int index);
#endif
=======

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======

>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#endif
