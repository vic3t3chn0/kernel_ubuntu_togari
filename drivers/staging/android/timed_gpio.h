/* include/linux/timed_gpio.h
 *
 * Copyright (C) 2008 Google, Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
*/

#ifndef _LINUX_TIMED_GPIO_H
#define _LINUX_TIMED_GPIO_H

#define TIMED_GPIO_NAME "timed-gpio"

struct timed_gpio {
	const char *name;
<<<<<<< HEAD
<<<<<<< HEAD
	unsigned	gpio;
	int		max_timeout;
	u8		active_low;
};

struct timed_gpio_platform_data {
	int		num_gpios;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	unsigned 	gpio;
	int		max_timeout;
	u8 		active_low;
};

struct timed_gpio_platform_data {
	int 		num_gpios;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct timed_gpio *gpios;
};

#endif
