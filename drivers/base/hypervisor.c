/*
 * hypervisor.c - /sys/hypervisor subsystem.
 *
 * Copyright (C) IBM Corp. 2006
 * Copyright (C) 2007 Greg Kroah-Hartman <gregkh@suse.de>
 * Copyright (C) 2007 Novell Inc.
 *
 * This file is released under the GPLv2
 */

#include <linux/kobject.h>
#include <linux/device.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/export.h>
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include "base.h"

struct kobject *hypervisor_kobj;
EXPORT_SYMBOL_GPL(hypervisor_kobj);

int __init hypervisor_init(void)
{
	hypervisor_kobj = kobject_create_and_add("hypervisor", NULL);
	if (!hypervisor_kobj)
		return -ENOMEM;
	return 0;
}
