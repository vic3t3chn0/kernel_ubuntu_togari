/*
 * Raw serio device providing access to a raw byte stream from underlying
 * serio port. Closely emulates behavior of pre-2.6 /dev/psaux device
 *
 * Copyright (c) 2004 Dmitry Torokhov
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 */

<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/kref.h>
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/poll.h>
#include <linux/module.h>
#include <linux/serio.h>
#include <linux/init.h>
#include <linux/major.h>
#include <linux/device.h>
#include <linux/miscdevice.h>
#include <linux/wait.h>
#include <linux/mutex.h>

#define DRIVER_DESC	"Raw serio driver"

MODULE_AUTHOR("Dmitry Torokhov <dtor@mail.ru>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

#define SERIO_RAW_QUEUE_LEN	64
struct serio_raw {
	unsigned char queue[SERIO_RAW_QUEUE_LEN];
	unsigned int tail, head;

	char name[16];
<<<<<<< HEAD
<<<<<<< HEAD
	struct kref kref;
	struct serio *serio;
	struct miscdevice dev;
	wait_queue_head_t wait;
	struct list_head client_list;
	struct list_head node;
	bool dead;
};

struct serio_raw_client {
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	unsigned int refcnt;
	struct serio *serio;
	struct miscdevice dev;
	wait_queue_head_t wait;
	struct list_head list;
	struct list_head node;
};

struct serio_raw_list {
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct fasync_struct *fasync;
	struct serio_raw *serio_raw;
	struct list_head node;
};

static DEFINE_MUTEX(serio_raw_mutex);
static LIST_HEAD(serio_raw_list);
<<<<<<< HEAD
<<<<<<< HEAD
=======
static unsigned int serio_raw_no;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static unsigned int serio_raw_no;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/*********************************************************************
 *             Interface with userspace (file operations)            *
 *********************************************************************/

static int serio_raw_fasync(int fd, struct file *file, int on)
{
<<<<<<< HEAD
<<<<<<< HEAD
	struct serio_raw_client *client = file->private_data;

	return fasync_helper(fd, file, on, &client->fasync);
=======
	struct serio_raw_list *list = file->private_data;

	return fasync_helper(fd, file, on, &list->fasync);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	struct serio_raw_list *list = file->private_data;

	return fasync_helper(fd, file, on, &list->fasync);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static struct serio_raw *serio_raw_locate(int minor)
{
	struct serio_raw *serio_raw;

	list_for_each_entry(serio_raw, &serio_raw_list, node) {
		if (serio_raw->dev.minor == minor)
			return serio_raw;
	}

	return NULL;
}

static int serio_raw_open(struct inode *inode, struct file *file)
{
	struct serio_raw *serio_raw;
<<<<<<< HEAD
<<<<<<< HEAD
	struct serio_raw_client *client;
	int retval;
=======
	struct serio_raw_list *list;
	int retval = 0;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	struct serio_raw_list *list;
	int retval = 0;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	retval = mutex_lock_interruptible(&serio_raw_mutex);
	if (retval)
		return retval;

	serio_raw = serio_raw_locate(iminor(inode));
	if (!serio_raw) {
		retval = -ENODEV;
		goto out;
	}

<<<<<<< HEAD
<<<<<<< HEAD
	if (serio_raw->dead) {
=======
	if (!serio_raw->serio) {
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	if (!serio_raw->serio) {
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		retval = -ENODEV;
		goto out;
	}

<<<<<<< HEAD
<<<<<<< HEAD
	client = kzalloc(sizeof(struct serio_raw_client), GFP_KERNEL);
	if (!client) {
=======
	list = kzalloc(sizeof(struct serio_raw_list), GFP_KERNEL);
	if (!list) {
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	list = kzalloc(sizeof(struct serio_raw_list), GFP_KERNEL);
	if (!list) {
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		retval = -ENOMEM;
		goto out;
	}

<<<<<<< HEAD
<<<<<<< HEAD
	client->serio_raw = serio_raw;
	file->private_data = client;

	kref_get(&serio_raw->kref);

	serio_pause_rx(serio_raw->serio);
	list_add_tail(&client->node, &serio_raw->client_list);
	serio_continue_rx(serio_raw->serio);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	list->serio_raw = serio_raw;
	file->private_data = list;

	serio_raw->refcnt++;
	list_add_tail(&list->node, &serio_raw->list);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

out:
	mutex_unlock(&serio_raw_mutex);
	return retval;
}

<<<<<<< HEAD
<<<<<<< HEAD
static void serio_raw_free(struct kref *kref)
{
	struct serio_raw *serio_raw =
			container_of(kref, struct serio_raw, kref);

	put_device(&serio_raw->serio->dev);
	kfree(serio_raw);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static int serio_raw_cleanup(struct serio_raw *serio_raw)
{
	if (--serio_raw->refcnt == 0) {
		misc_deregister(&serio_raw->dev);
		list_del_init(&serio_raw->node);
		kfree(serio_raw);

		return 1;
	}

	return 0;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static int serio_raw_release(struct inode *inode, struct file *file)
{
<<<<<<< HEAD
<<<<<<< HEAD
	struct serio_raw_client *client = file->private_data;
	struct serio_raw *serio_raw = client->serio_raw;

	serio_pause_rx(serio_raw->serio);
	list_del(&client->node);
	serio_continue_rx(serio_raw->serio);

	kfree(client);

	kref_put(&serio_raw->kref, serio_raw_free);

	return 0;
}

static bool serio_raw_fetch_byte(struct serio_raw *serio_raw, char *c)
{
	bool empty;

	serio_pause_rx(serio_raw->serio);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct serio_raw_list *list = file->private_data;
	struct serio_raw *serio_raw = list->serio_raw;

	mutex_lock(&serio_raw_mutex);

	serio_raw_cleanup(serio_raw);

	mutex_unlock(&serio_raw_mutex);
	return 0;
}

static int serio_raw_fetch_byte(struct serio_raw *serio_raw, char *c)
{
	unsigned long flags;
	int empty;

	spin_lock_irqsave(&serio_raw->serio->lock, flags);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	empty = serio_raw->head == serio_raw->tail;
	if (!empty) {
		*c = serio_raw->queue[serio_raw->tail];
		serio_raw->tail = (serio_raw->tail + 1) % SERIO_RAW_QUEUE_LEN;
	}

<<<<<<< HEAD
<<<<<<< HEAD
	serio_continue_rx(serio_raw->serio);
=======
	spin_unlock_irqrestore(&serio_raw->serio->lock, flags);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	spin_unlock_irqrestore(&serio_raw->serio->lock, flags);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return !empty;
}

<<<<<<< HEAD
<<<<<<< HEAD
static ssize_t serio_raw_read(struct file *file, char __user *buffer,
			      size_t count, loff_t *ppos)
{
	struct serio_raw_client *client = file->private_data;
	struct serio_raw *serio_raw = client->serio_raw;
	char uninitialized_var(c);
	ssize_t read = 0;
	int retval;

	if (serio_raw->dead)
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static ssize_t serio_raw_read(struct file *file, char __user *buffer, size_t count, loff_t *ppos)
{
	struct serio_raw_list *list = file->private_data;
	struct serio_raw *serio_raw = list->serio_raw;
	char uninitialized_var(c);
	ssize_t retval = 0;

	if (!serio_raw->serio)
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return -ENODEV;

	if (serio_raw->head == serio_raw->tail && (file->f_flags & O_NONBLOCK))
		return -EAGAIN;

<<<<<<< HEAD
<<<<<<< HEAD
	retval = wait_event_interruptible(serio_raw->wait,
			serio_raw->head != serio_raw->tail || serio_raw->dead);
	if (retval)
		return retval;

	if (serio_raw->dead)
		return -ENODEV;

	while (read < count && serio_raw_fetch_byte(serio_raw, &c)) {
		if (put_user(c, buffer++)) {
			retval = -EFAULT;
			break;
		}
		read++;
	}

	return read ?: retval;
}

static ssize_t serio_raw_write(struct file *file, const char __user *buffer,
			       size_t count, loff_t *ppos)
{
	struct serio_raw_client *client = file->private_data;
	struct serio_raw *serio_raw = client->serio_raw;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	retval = wait_event_interruptible(list->serio_raw->wait,
					  serio_raw->head != serio_raw->tail || !serio_raw->serio);
	if (retval)
		return retval;

	if (!serio_raw->serio)
		return -ENODEV;

	while (retval < count && serio_raw_fetch_byte(serio_raw, &c)) {
		if (put_user(c, buffer++))
			return -EFAULT;
		retval++;
	}

	return retval;
}

static ssize_t serio_raw_write(struct file *file, const char __user *buffer, size_t count, loff_t *ppos)
{
	struct serio_raw_list *list = file->private_data;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	ssize_t written = 0;
	int retval;
	unsigned char c;

	retval = mutex_lock_interruptible(&serio_raw_mutex);
	if (retval)
		return retval;

<<<<<<< HEAD
<<<<<<< HEAD
	if (serio_raw->dead) {
=======
	if (!list->serio_raw->serio) {
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	if (!list->serio_raw->serio) {
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		retval = -ENODEV;
		goto out;
	}

	if (count > 32)
		count = 32;

	while (count--) {
		if (get_user(c, buffer++)) {
			retval = -EFAULT;
			goto out;
		}
<<<<<<< HEAD
<<<<<<< HEAD
		if (serio_write(serio_raw->serio, c)) {
=======
		if (serio_write(list->serio_raw->serio, c)) {
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		if (serio_write(list->serio_raw->serio, c)) {
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			retval = -EIO;
			goto out;
		}
		written++;
<<<<<<< HEAD
<<<<<<< HEAD
	}

out:
	mutex_unlock(&serio_raw_mutex);
	return written ?: retval;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	};

out:
	mutex_unlock(&serio_raw_mutex);
	return written;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static unsigned int serio_raw_poll(struct file *file, poll_table *wait)
{
<<<<<<< HEAD
<<<<<<< HEAD
	struct serio_raw_client *client = file->private_data;
	struct serio_raw *serio_raw = client->serio_raw;
	unsigned int mask;

	poll_wait(file, &serio_raw->wait, wait);

	mask = serio_raw->dead ? POLLHUP | POLLERR : POLLOUT | POLLWRNORM;
	if (serio_raw->head != serio_raw->tail)
		mask |= POLLIN | POLLRDNORM;

	return mask;
}

static const struct file_operations serio_raw_fops = {
	.owner		= THIS_MODULE,
	.open		= serio_raw_open,
	.release	= serio_raw_release,
	.read		= serio_raw_read,
	.write		= serio_raw_write,
	.poll		= serio_raw_poll,
	.fasync		= serio_raw_fasync,
	.llseek		= noop_llseek,
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct serio_raw_list *list = file->private_data;

	poll_wait(file, &list->serio_raw->wait, wait);

	if (list->serio_raw->head != list->serio_raw->tail)
		return POLLIN | POLLRDNORM;

	return 0;
}

static const struct file_operations serio_raw_fops = {
	.owner =	THIS_MODULE,
	.open =		serio_raw_open,
	.release =	serio_raw_release,
	.read =		serio_raw_read,
	.write =	serio_raw_write,
	.poll =		serio_raw_poll,
	.fasync =	serio_raw_fasync,
	.llseek = noop_llseek,
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};


/*********************************************************************
<<<<<<< HEAD
<<<<<<< HEAD
 *                   Interface with serio port                       *
=======
 *                   Interface with serio port   	             *
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 *                   Interface with serio port   	             *
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *********************************************************************/

static irqreturn_t serio_raw_interrupt(struct serio *serio, unsigned char data,
					unsigned int dfl)
{
	struct serio_raw *serio_raw = serio_get_drvdata(serio);
<<<<<<< HEAD
<<<<<<< HEAD
	struct serio_raw_client *client;
	unsigned int head = serio_raw->head;

	/* we are holding serio->lock here so we are protected */
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct serio_raw_list *list;
	unsigned int head = serio_raw->head;

	/* we are holding serio->lock here so we are prootected */
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	serio_raw->queue[head] = data;
	head = (head + 1) % SERIO_RAW_QUEUE_LEN;
	if (likely(head != serio_raw->tail)) {
		serio_raw->head = head;
<<<<<<< HEAD
<<<<<<< HEAD
		list_for_each_entry(client, &serio_raw->client_list, node)
			kill_fasync(&client->fasync, SIGIO, POLL_IN);
=======
		list_for_each_entry(list, &serio_raw->list, node)
			kill_fasync(&list->fasync, SIGIO, POLL_IN);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		list_for_each_entry(list, &serio_raw->list, node)
			kill_fasync(&list->fasync, SIGIO, POLL_IN);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		wake_up_interruptible(&serio_raw->wait);
	}

	return IRQ_HANDLED;
}

static int serio_raw_connect(struct serio *serio, struct serio_driver *drv)
{
<<<<<<< HEAD
<<<<<<< HEAD
	static atomic_t serio_raw_no = ATOMIC_INIT(0);
	struct serio_raw *serio_raw;
	int err;

	serio_raw = kzalloc(sizeof(struct serio_raw), GFP_KERNEL);
	if (!serio_raw) {
		dev_dbg(&serio->dev, "can't allocate memory for a device\n");
		return -ENOMEM;
	}

	snprintf(serio_raw->name, sizeof(serio_raw->name),
		 "serio_raw%ld", (long)atomic_inc_return(&serio_raw_no) - 1);
	kref_init(&serio_raw->kref);
	INIT_LIST_HEAD(&serio_raw->client_list);
	init_waitqueue_head(&serio_raw->wait);

	serio_raw->serio = serio;
	get_device(&serio->dev);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct serio_raw *serio_raw;
	int err;

	if (!(serio_raw = kzalloc(sizeof(struct serio_raw), GFP_KERNEL))) {
		printk(KERN_ERR "serio_raw.c: can't allocate memory for a device\n");
		return -ENOMEM;
	}

	mutex_lock(&serio_raw_mutex);

	snprintf(serio_raw->name, sizeof(serio_raw->name), "serio_raw%d", serio_raw_no++);
	serio_raw->refcnt = 1;
	serio_raw->serio = serio;
	INIT_LIST_HEAD(&serio_raw->list);
	init_waitqueue_head(&serio_raw->wait);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	serio_set_drvdata(serio, serio_raw);

	err = serio_open(serio, drv);
	if (err)
<<<<<<< HEAD
<<<<<<< HEAD
		goto err_free;

	err = mutex_lock_killable(&serio_raw_mutex);
	if (err)
		goto err_close;

	list_add_tail(&serio_raw->node, &serio_raw_list);
	mutex_unlock(&serio_raw_mutex);
=======
		goto out_free;

	list_add_tail(&serio_raw->node, &serio_raw_list);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		goto out_free;

	list_add_tail(&serio_raw->node, &serio_raw_list);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	serio_raw->dev.minor = PSMOUSE_MINOR;
	serio_raw->dev.name = serio_raw->name;
	serio_raw->dev.parent = &serio->dev;
	serio_raw->dev.fops = &serio_raw_fops;

	err = misc_register(&serio_raw->dev);
	if (err) {
		serio_raw->dev.minor = MISC_DYNAMIC_MINOR;
		err = misc_register(&serio_raw->dev);
	}

	if (err) {
<<<<<<< HEAD
<<<<<<< HEAD
		dev_err(&serio->dev,
			"failed to register raw access device for %s\n",
			serio->phys);
		goto err_unlink;
	}

	dev_info(&serio->dev, "raw access enabled on %s (%s, minor %d)\n",
		 serio->phys, serio_raw->name, serio_raw->dev.minor);
	return 0;

err_unlink:
	list_del_init(&serio_raw->node);
err_close:
	serio_close(serio);
err_free:
	serio_set_drvdata(serio, NULL);
	kref_put(&serio_raw->kref, serio_raw_free);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		printk(KERN_INFO "serio_raw: failed to register raw access device for %s\n",
			serio->phys);
		goto out_close;
	}

	printk(KERN_INFO "serio_raw: raw access enabled on %s (%s, minor %d)\n",
		serio->phys, serio_raw->name, serio_raw->dev.minor);
	goto out;

out_close:
	serio_close(serio);
	list_del_init(&serio_raw->node);
out_free:
	serio_set_drvdata(serio, NULL);
	kfree(serio_raw);
out:
	mutex_unlock(&serio_raw_mutex);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return err;
}

static int serio_raw_reconnect(struct serio *serio)
{
	struct serio_raw *serio_raw = serio_get_drvdata(serio);
	struct serio_driver *drv = serio->drv;

	if (!drv || !serio_raw) {
<<<<<<< HEAD
<<<<<<< HEAD
		dev_dbg(&serio->dev,
			"reconnect request, but serio is disconnected, ignoring...\n");
=======
		printk(KERN_DEBUG "serio_raw: reconnect request, but serio is disconnected, ignoring...\n");
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		printk(KERN_DEBUG "serio_raw: reconnect request, but serio is disconnected, ignoring...\n");
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return -1;
	}

	/*
	 * Nothing needs to be done here, we just need this method to
	 * keep the same device.
	 */
	return 0;
}

<<<<<<< HEAD
<<<<<<< HEAD
/*
 * Wake up users waiting for IO so they can disconnect from
 * dead device.
 */
static void serio_raw_hangup(struct serio_raw *serio_raw)
{
	struct serio_raw_client *client;

	serio_pause_rx(serio_raw->serio);
	list_for_each_entry(client, &serio_raw->client_list, node)
		kill_fasync(&client->fasync, SIGIO, POLL_HUP);
	serio_continue_rx(serio_raw->serio);

	wake_up_interruptible(&serio_raw->wait);
}


static void serio_raw_disconnect(struct serio *serio)
{
	struct serio_raw *serio_raw = serio_get_drvdata(serio);

	misc_deregister(&serio_raw->dev);

	mutex_lock(&serio_raw_mutex);
	serio_raw->dead = true;
	list_del_init(&serio_raw->node);
	mutex_unlock(&serio_raw_mutex);

	serio_raw_hangup(serio_raw);

	serio_close(serio);
	kref_put(&serio_raw->kref, serio_raw_free);

	serio_set_drvdata(serio, NULL);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static void serio_raw_disconnect(struct serio *serio)
{
	struct serio_raw *serio_raw;

	mutex_lock(&serio_raw_mutex);

	serio_raw = serio_get_drvdata(serio);

	serio_close(serio);
	serio_set_drvdata(serio, NULL);

	serio_raw->serio = NULL;
	if (!serio_raw_cleanup(serio_raw))
		wake_up_interruptible(&serio_raw->wait);

	mutex_unlock(&serio_raw_mutex);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static struct serio_device_id serio_raw_serio_ids[] = {
	{
		.type	= SERIO_8042,
		.proto	= SERIO_ANY,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	},
	{
		.type	= SERIO_8042_XL,
		.proto	= SERIO_ANY,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	},
	{ 0 }
};

MODULE_DEVICE_TABLE(serio, serio_raw_serio_ids);

static struct serio_driver serio_raw_drv = {
	.driver		= {
		.name	= "serio_raw",
	},
	.description	= DRIVER_DESC,
	.id_table	= serio_raw_serio_ids,
	.interrupt	= serio_raw_interrupt,
	.connect	= serio_raw_connect,
	.reconnect	= serio_raw_reconnect,
	.disconnect	= serio_raw_disconnect,
<<<<<<< HEAD
<<<<<<< HEAD
	.manual_bind	= true,
=======
	.manual_bind	= 1,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	.manual_bind	= 1,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

static int __init serio_raw_init(void)
{
	return serio_register_driver(&serio_raw_drv);
}

static void __exit serio_raw_exit(void)
{
	serio_unregister_driver(&serio_raw_drv);
}

module_init(serio_raw_init);
module_exit(serio_raw_exit);
