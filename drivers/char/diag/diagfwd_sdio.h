<<<<<<< HEAD
<<<<<<< HEAD
/* Copyright (c) 2011, The Linux Foundation. All rights reserved.
=======
/* Copyright (c) 2011, Code Aurora Forum. All rights reserved.
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
/* Copyright (c) 2011, Code Aurora Forum. All rights reserved.
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

#ifndef DIAGFWD_SDIO_H
#define DIAGFWD_SDIO_H

#include <mach/sdio_al.h>
<<<<<<< HEAD
<<<<<<< HEAD
#define N_MDM_SDIO_WRITE	1 /* Upgrade to 2 with ping pong buffer */
#define N_MDM_SDIO_READ	1
=======
#define N_MDM_WRITE	1 /* Upgrade to 2 with ping pong buffer */
#define N_MDM_READ	1
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
#define N_MDM_WRITE	1 /* Upgrade to 2 with ping pong buffer */
#define N_MDM_READ	1
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

void diagfwd_sdio_init(void);
void diagfwd_sdio_exit(void);
int diagfwd_connect_sdio(void);
int diagfwd_disconnect_sdio(void);
int diagfwd_read_complete_sdio(void);
int diagfwd_write_complete_sdio(void);

#endif
