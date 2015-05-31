/*
 * Persistent Storage - platform driver interface parts.
 *
 * Copyright (C) 2010 Intel Corporation <tony.luck@intel.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <linux/atomic.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/kmsg_dump.h>
#include <linux/module.h>
#include <linux/pstore.h>
#include <linux/string.h>
<<<<<<< HEAD
#include <linux/timer.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/hardirq.h>
#include <linux/workqueue.h>
=======
#include <linux/slab.h>
#include <linux/uaccess.h>
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

#include "internal.h"

/*
<<<<<<< HEAD
 * We defer making "oops" entries appear in pstore - see
 * whether the system is actually still running well enough
 * to let someone see the entry
 */
#define	PSTORE_INTERVAL	(60 * HZ)

static int pstore_new_entry;

static void pstore_timefunc(unsigned long);
static DEFINE_TIMER(pstore_timer, pstore_timefunc, 0, 0);

static void pstore_dowork(struct work_struct *);
static DECLARE_WORK(pstore_work, pstore_dowork);

/*
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
 * pstore_lock just protects "psinfo" during
 * calls to pstore_register()
 */
static DEFINE_SPINLOCK(pstore_lock);
static struct pstore_info *psinfo;

<<<<<<< HEAD
static char *backend;

=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
/* How much of the console log to snapshot */
static unsigned long kmsg_bytes = 10240;

void pstore_set_kmsg_bytes(int bytes)
{
	kmsg_bytes = bytes;
}

/* Tag each group of saved records with a sequence number */
static int	oopscount;

<<<<<<< HEAD
static const char *get_reason_str(enum kmsg_dump_reason reason)
{
	switch (reason) {
	case KMSG_DUMP_PANIC:
		return "Panic";
	case KMSG_DUMP_OOPS:
		return "Oops";
	case KMSG_DUMP_EMERG:
		return "Emergency";
	case KMSG_DUMP_RESTART:
		return "Restart";
	case KMSG_DUMP_HALT:
		return "Halt";
	case KMSG_DUMP_POWEROFF:
		return "Poweroff";
	default:
		return "Unknown";
	}
}
=======
static char *reason_str[] = {
	"Oops", "Panic", "Kexec", "Restart", "Halt", "Poweroff", "Emergency"
};
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

/*
 * callback from kmsg_dump. (s2,l2) has the most recently
 * written bytes, older bytes are in (s1,l1). Save as much
 * as we can from the end of the buffer.
 */
static void pstore_dump(struct kmsg_dumper *dumper,
	    enum kmsg_dump_reason reason,
	    const char *s1, unsigned long l1,
	    const char *s2, unsigned long l2)
{
	unsigned long	s1_start, s2_start;
	unsigned long	l1_cpy, l2_cpy;
	unsigned long	size, total = 0;
<<<<<<< HEAD
	char		*dst;
	const char	*why;
	u64		id;
	int		hsize, ret;
	unsigned int	part = 1;
	unsigned long	flags = 0;
	int		is_locked = 0;

	why = get_reason_str(reason);

	if (in_nmi()) {
		is_locked = spin_trylock(&psinfo->buf_lock);
		if (!is_locked)
			pr_err("pstore dump routine blocked in NMI, may corrupt error record\n");
	} else
		spin_lock_irqsave(&psinfo->buf_lock, flags);
	oopscount++;
	while (total < kmsg_bytes) {
		dst = psinfo->buf;
		hsize = sprintf(dst, "%s#%d Part%d\n", why, oopscount, part);
=======
	char		*dst, *why;
	u64		id;
	int		hsize, part = 1;

	if (reason < ARRAY_SIZE(reason_str))
		why = reason_str[reason];
	else
		why = "Unknown";

	mutex_lock(&psinfo->buf_mutex);
	oopscount++;
	while (total < kmsg_bytes) {
		dst = psinfo->buf;
		hsize = sprintf(dst, "%s#%d Part%d\n", why, oopscount, part++);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		size = psinfo->bufsize - hsize;
		dst += hsize;

		l2_cpy = min(l2, size);
		l1_cpy = min(l1, size - l2_cpy);

		if (l1_cpy + l2_cpy == 0)
			break;

		s2_start = l2 - l2_cpy;
		s1_start = l1 - l1_cpy;

		memcpy(dst, s1 + s1_start, l1_cpy);
		memcpy(dst + l1_cpy, s2 + s2_start, l2_cpy);

<<<<<<< HEAD
		ret = psinfo->write(PSTORE_TYPE_DMESG, reason, &id, part,
				   hsize + l1_cpy + l2_cpy, psinfo);
		if (ret == 0 && reason == KMSG_DUMP_OOPS && pstore_is_mounted())
			pstore_new_entry = 1;
		l1 -= l1_cpy;
		l2 -= l2_cpy;
		total += l1_cpy + l2_cpy;
		part++;
	}
	if (in_nmi()) {
		if (is_locked)
			spin_unlock(&psinfo->buf_lock);
	} else
		spin_unlock_irqrestore(&psinfo->buf_lock, flags);
=======
		id = psinfo->write(PSTORE_TYPE_DMESG, hsize + l1_cpy + l2_cpy);
		if (reason == KMSG_DUMP_OOPS && pstore_is_mounted())
			pstore_mkfile(PSTORE_TYPE_DMESG, psinfo->name, id,
				      psinfo->buf, hsize + l1_cpy + l2_cpy,
				      CURRENT_TIME, psinfo->erase);
		l1 -= l1_cpy;
		l2 -= l2_cpy;
		total += l1_cpy + l2_cpy;
	}
	mutex_unlock(&psinfo->buf_mutex);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
}

static struct kmsg_dumper pstore_dumper = {
	.dump = pstore_dump,
};

/*
 * platform specific persistent storage driver registers with
 * us here. If pstore is already mounted, call the platform
 * read function right away to populate the file system. If not
 * then the pstore mount code will call us later to fill out
 * the file system.
 *
 * Register with kmsg_dump to save last part of console log on panic.
 */
int pstore_register(struct pstore_info *psi)
{
	struct module *owner = psi->owner;

	spin_lock(&pstore_lock);
	if (psinfo) {
		spin_unlock(&pstore_lock);
		return -EBUSY;
	}
<<<<<<< HEAD

	if (backend && strcmp(backend, psi->name)) {
		spin_unlock(&pstore_lock);
		return -EINVAL;
	}

	psinfo = psi;
	mutex_init(&psinfo->read_mutex);
=======
	psinfo = psi;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	spin_unlock(&pstore_lock);

	if (owner && !try_module_get(owner)) {
		psinfo = NULL;
		return -EINVAL;
	}

	if (pstore_is_mounted())
<<<<<<< HEAD
		pstore_get_records(0);

	kmsg_dump_register(&pstore_dumper);

	pstore_timer.expires = jiffies + PSTORE_INTERVAL;
	add_timer(&pstore_timer);

=======
		pstore_get_records();

	kmsg_dump_register(&pstore_dumper);

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	return 0;
}
EXPORT_SYMBOL_GPL(pstore_register);

/*
<<<<<<< HEAD
 * Read all the records from the persistent store. Create
 * files in our filesystem.  Don't warn about -EEXIST errors
 * when we are re-scanning the backing store looking to add new
 * error records.
 */
void pstore_get_records(int quiet)
{
	struct pstore_info *psi = psinfo;
	char			*buf = NULL;
=======
 * Read all the records from the persistent store. Create and
 * file files in our filesystem.
 */
void pstore_get_records(void)
{
	struct pstore_info *psi = psinfo;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	ssize_t			size;
	u64			id;
	enum pstore_type_id	type;
	struct timespec		time;
	int			failed = 0, rc;

	if (!psi)
		return;

<<<<<<< HEAD
	mutex_lock(&psi->read_mutex);
	if (psi->open && psi->open(psi))
		goto out;

	while ((size = psi->read(&id, &type, &time, &buf, psi)) > 0) {
		rc = pstore_mkfile(type, psi->name, id, buf, (size_t)size,
				  time, psi);
		kfree(buf);
		buf = NULL;
		if (rc && (rc != -EEXIST || !quiet))
			failed++;
	}
	if (psi->close)
		psi->close(psi);
out:
	mutex_unlock(&psi->read_mutex);
=======
	mutex_lock(&psinfo->buf_mutex);
	rc = psi->open(psi);
	if (rc)
		goto out;

	while ((size = psi->read(&id, &type, &time)) > 0) {
		if (pstore_mkfile(type, psi->name, id, psi->buf, (size_t)size,
				  time, psi->erase))
			failed++;
	}
	psi->close(psi);
out:
	mutex_unlock(&psinfo->buf_mutex);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

	if (failed)
		printk(KERN_WARNING "pstore: failed to load %d record(s) from '%s'\n",
		       failed, psi->name);
}

<<<<<<< HEAD
static void pstore_dowork(struct work_struct *work)
{
	pstore_get_records(1);
}

static void pstore_timefunc(unsigned long dummy)
{
	if (pstore_new_entry) {
		pstore_new_entry = 0;
		schedule_work(&pstore_work);
	}

	mod_timer(&pstore_timer, jiffies + PSTORE_INTERVAL);
}

module_param(backend, charp, 0444);
MODULE_PARM_DESC(backend, "Pstore backend to use");
=======
/*
 * Call platform driver to write a record to the
 * persistent store.
 */
int pstore_write(enum pstore_type_id type, char *buf, size_t size)
{
	u64	id;

	if (!psinfo)
		return -ENODEV;

	if (size > psinfo->bufsize)
		return -EFBIG;

	mutex_lock(&psinfo->buf_mutex);
	memcpy(psinfo->buf, buf, size);
	id = psinfo->write(type, size);
	if (pstore_is_mounted())
		pstore_mkfile(PSTORE_TYPE_DMESG, psinfo->name, id, psinfo->buf,
			      size, CURRENT_TIME, psinfo->erase);
	mutex_unlock(&psinfo->buf_mutex);

	return 0;
}
EXPORT_SYMBOL_GPL(pstore_write);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
