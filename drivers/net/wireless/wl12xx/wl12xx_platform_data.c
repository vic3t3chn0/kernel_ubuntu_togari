<<<<<<< HEAD
<<<<<<< HEAD
/*
 * This file is part of wl12xx
 *
 * Copyright (C) 2010-2011 Texas Instruments, Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 *
 */

=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <linux/module.h>
#include <linux/err.h>
#include <linux/wl12xx.h>

<<<<<<< HEAD
<<<<<<< HEAD
static struct wl12xx_platform_data *platform_data;
=======
static const struct wl12xx_platform_data *platform_data;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static const struct wl12xx_platform_data *platform_data;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

int __init wl12xx_set_platform_data(const struct wl12xx_platform_data *data)
{
	if (platform_data)
		return -EBUSY;
	if (!data)
		return -EINVAL;

	platform_data = kmemdup(data, sizeof(*data), GFP_KERNEL);
	if (!platform_data)
		return -ENOMEM;

	return 0;
}

<<<<<<< HEAD
<<<<<<< HEAD
struct wl12xx_platform_data *wl12xx_get_platform_data(void)
=======
const struct wl12xx_platform_data *wl12xx_get_platform_data(void)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
const struct wl12xx_platform_data *wl12xx_get_platform_data(void)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	if (!platform_data)
		return ERR_PTR(-ENODEV);

	return platform_data;
}
EXPORT_SYMBOL(wl12xx_get_platform_data);
