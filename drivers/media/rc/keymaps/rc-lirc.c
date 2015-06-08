/* rc-lirc.c - Empty dummy keytable, for use when its preferred to pass
 * all raw IR data to the lirc userspace decoder.
 *
 * Copyright (c) 2010 by Jarod Wilson <jarod@redhat.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <media/rc-core.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/module.h>
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

static struct rc_map_table lirc[] = {
	{ },
};

static struct rc_map_list lirc_map = {
	.map = {
		.scan    = lirc,
		.size    = ARRAY_SIZE(lirc),
		.rc_type = RC_TYPE_LIRC,
		.name    = RC_MAP_LIRC,
	}
};

static int __init init_rc_map_lirc(void)
{
	return rc_map_register(&lirc_map);
}

static void __exit exit_rc_map_lirc(void)
{
	rc_map_unregister(&lirc_map);
}

module_init(init_rc_map_lirc)
module_exit(exit_rc_map_lirc)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jarod Wilson <jarod@redhat.com>");
