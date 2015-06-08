/*
 * Stuff used by all variants of the driver
 *
 * Copyright (c) 2001 by Stefan Eilers,
 *                       Hansjoerg Lipp <hjlipp@web.de>,
 *                       Tilman Schmidt <tilman@imap.cc>.
 *
 * =====================================================================
 *	This program is free software; you can redistribute it and/or
 *	modify it under the terms of the GNU General Public License as
 *	published by the Free Software Foundation; either version 2 of
 *	the License, or (at your option) any later version.
 * =====================================================================
 */

#include "gigaset.h"

static ssize_t show_cidmode(struct device *dev,
			    struct device_attribute *attr, char *buf)
{
	struct cardstate *cs = dev_get_drvdata(dev);

	return sprintf(buf, "%u\n", cs->cidmode);
}

static ssize_t set_cidmode(struct device *dev, struct device_attribute *attr,
			   const char *buf, size_t count)
{
	struct cardstate *cs = dev_get_drvdata(dev);
	long int value;
	char *end;

	value = simple_strtol(buf, &end, 0);
	while (*end)
		if (!isspace(*end++))
			return -EINVAL;
	if (value < 0 || value > 1)
<<<<<<< HEAD
<<<<<<< HEAD
		return -EINVAL;
=======
			return -EINVAL;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			return -EINVAL;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (mutex_lock_interruptible(&cs->mutex))
		return -ERESTARTSYS;

	cs->waiting = 1;
	if (!gigaset_add_event(cs, &cs->at_state, EV_PROC_CIDMODE,
			       NULL, value, NULL)) {
		cs->waiting = 0;
		mutex_unlock(&cs->mutex);
		return -ENOMEM;
	}
	gigaset_schedule_event(cs);

	wait_event(cs->waitqueue, !cs->waiting);

	mutex_unlock(&cs->mutex);

	return count;
}

<<<<<<< HEAD
<<<<<<< HEAD
static DEVICE_ATTR(cidmode, S_IRUGO | S_IWUSR, show_cidmode, set_cidmode);
=======
static DEVICE_ATTR(cidmode, S_IRUGO|S_IWUSR, show_cidmode, set_cidmode);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static DEVICE_ATTR(cidmode, S_IRUGO|S_IWUSR, show_cidmode, set_cidmode);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/* free sysfs for device */
void gigaset_free_dev_sysfs(struct cardstate *cs)
{
	if (!cs->tty_dev)
		return;

	gig_dbg(DEBUG_INIT, "removing sysfs entries");
	device_remove_file(cs->tty_dev, &dev_attr_cidmode);
}

/* initialize sysfs for device */
void gigaset_init_dev_sysfs(struct cardstate *cs)
{
	if (!cs->tty_dev)
		return;

	gig_dbg(DEBUG_INIT, "setting up sysfs");
	if (device_create_file(cs->tty_dev, &dev_attr_cidmode))
		pr_err("could not create sysfs attribute\n");
}
