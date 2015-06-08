/*******************************************************************************
 * Filename:  target_core_file.c
 *
 * This file contains the Storage Engine <-> FILEIO transport specific functions
 *
 * Copyright (c) 2005 PyX Technologies, Inc.
 * Copyright (c) 2005-2006 SBE, Inc.  All Rights Reserved.
 * Copyright (c) 2007-2010 Rising Tide Systems
 * Copyright (c) 2008-2010 Linux-iSCSI.org
 *
 * Nicholas A. Bellinger <nab@kernel.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 ******************************************************************************/

<<<<<<< HEAD
<<<<<<< HEAD
=======
#include <linux/version.h>
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
#include <linux/version.h>
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <linux/string.h>
#include <linux/parser.h>
#include <linux/timer.h>
#include <linux/blkdev.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/module.h>
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <scsi/scsi.h>
#include <scsi/scsi_host.h>

#include <target/target_core_base.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include <target/target_core_backend.h>

#include "target_core_file.h"

=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <target/target_core_device.h>
#include <target/target_core_transport.h>

#include "target_core_file.h"

#if 1
#define DEBUG_FD_CACHE(x...) printk(x)
#else
#define DEBUG_FD_CACHE(x...)
#endif

#if 1
#define DEBUG_FD_FUA(x...) printk(x)
#else
#define DEBUG_FD_FUA(x...)
#endif

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static struct se_subsystem_api fileio_template;

/*	fd_attach_hba(): (Part of se_subsystem_api_t template)
 *
 *
 */
static int fd_attach_hba(struct se_hba *hba, u32 host_id)
{
	struct fd_host *fd_host;

	fd_host = kzalloc(sizeof(struct fd_host), GFP_KERNEL);
<<<<<<< HEAD
<<<<<<< HEAD
	if (!fd_host) {
		pr_err("Unable to allocate memory for struct fd_host\n");
		return -ENOMEM;
=======
	if (!(fd_host)) {
		printk(KERN_ERR "Unable to allocate memory for struct fd_host\n");
		return -1;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	if (!(fd_host)) {
		printk(KERN_ERR "Unable to allocate memory for struct fd_host\n");
		return -1;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}

	fd_host->fd_host_id = host_id;

<<<<<<< HEAD
<<<<<<< HEAD
	hba->hba_ptr = fd_host;

	pr_debug("CORE_HBA[%d] - TCM FILEIO HBA Driver %s on Generic"
		" Target Core Stack %s\n", hba->hba_id, FD_VERSION,
		TARGET_CORE_MOD_VERSION);
	pr_debug("CORE_HBA[%d] - Attached FILEIO HBA: %u to Generic"
		" MaxSectors: %u\n",
		hba->hba_id, fd_host->fd_host_id, FD_MAX_SECTORS);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	atomic_set(&hba->left_queue_depth, FD_HBA_QUEUE_DEPTH);
	atomic_set(&hba->max_queue_depth, FD_HBA_QUEUE_DEPTH);
	hba->hba_ptr = (void *) fd_host;

	printk(KERN_INFO "CORE_HBA[%d] - TCM FILEIO HBA Driver %s on Generic"
		" Target Core Stack %s\n", hba->hba_id, FD_VERSION,
		TARGET_CORE_MOD_VERSION);
	printk(KERN_INFO "CORE_HBA[%d] - Attached FILEIO HBA: %u to Generic"
		" Target Core with TCQ Depth: %d MaxSectors: %u\n",
		hba->hba_id, fd_host->fd_host_id,
		atomic_read(&hba->max_queue_depth), FD_MAX_SECTORS);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return 0;
}

static void fd_detach_hba(struct se_hba *hba)
{
	struct fd_host *fd_host = hba->hba_ptr;

<<<<<<< HEAD
<<<<<<< HEAD
	pr_debug("CORE_HBA[%d] - Detached FILEIO HBA: %u from Generic"
=======
	printk(KERN_INFO "CORE_HBA[%d] - Detached FILEIO HBA: %u from Generic"
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	printk(KERN_INFO "CORE_HBA[%d] - Detached FILEIO HBA: %u from Generic"
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		" Target Core\n", hba->hba_id, fd_host->fd_host_id);

	kfree(fd_host);
	hba->hba_ptr = NULL;
}

static void *fd_allocate_virtdevice(struct se_hba *hba, const char *name)
{
	struct fd_dev *fd_dev;
<<<<<<< HEAD
<<<<<<< HEAD
	struct fd_host *fd_host = hba->hba_ptr;

	fd_dev = kzalloc(sizeof(struct fd_dev), GFP_KERNEL);
	if (!fd_dev) {
		pr_err("Unable to allocate memory for struct fd_dev\n");
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct fd_host *fd_host = (struct fd_host *) hba->hba_ptr;

	fd_dev = kzalloc(sizeof(struct fd_dev), GFP_KERNEL);
	if (!(fd_dev)) {
		printk(KERN_ERR "Unable to allocate memory for struct fd_dev\n");
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return NULL;
	}

	fd_dev->fd_host = fd_host;

<<<<<<< HEAD
<<<<<<< HEAD
	pr_debug("FILEIO: Allocated fd_dev for %p\n", name);
=======
	printk(KERN_INFO "FILEIO: Allocated fd_dev for %p\n", name);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	printk(KERN_INFO "FILEIO: Allocated fd_dev for %p\n", name);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return fd_dev;
}

/*	fd_create_virtdevice(): (Part of se_subsystem_api_t template)
 *
 *
 */
static struct se_device *fd_create_virtdevice(
	struct se_hba *hba,
	struct se_subsystem_dev *se_dev,
	void *p)
{
	char *dev_p = NULL;
	struct se_device *dev;
	struct se_dev_limits dev_limits;
	struct queue_limits *limits;
<<<<<<< HEAD
<<<<<<< HEAD
	struct fd_dev *fd_dev = p;
	struct fd_host *fd_host = hba->hba_ptr;
=======
	struct fd_dev *fd_dev = (struct fd_dev *) p;
	struct fd_host *fd_host = (struct fd_host *) hba->hba_ptr;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	struct fd_dev *fd_dev = (struct fd_dev *) p;
	struct fd_host *fd_host = (struct fd_host *) hba->hba_ptr;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	mm_segment_t old_fs;
	struct file *file;
	struct inode *inode = NULL;
	int dev_flags = 0, flags, ret = -EINVAL;

	memset(&dev_limits, 0, sizeof(struct se_dev_limits));

	old_fs = get_fs();
	set_fs(get_ds());
	dev_p = getname(fd_dev->fd_dev_name);
	set_fs(old_fs);

	if (IS_ERR(dev_p)) {
<<<<<<< HEAD
<<<<<<< HEAD
		pr_err("getname(%s) failed: %lu\n",
=======
		printk(KERN_ERR "getname(%s) failed: %lu\n",
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		printk(KERN_ERR "getname(%s) failed: %lu\n",
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			fd_dev->fd_dev_name, IS_ERR(dev_p));
		ret = PTR_ERR(dev_p);
		goto fail;
	}
#if 0
	if (di->no_create_file)
		flags = O_RDWR | O_LARGEFILE;
	else
		flags = O_RDWR | O_CREAT | O_LARGEFILE;
#else
	flags = O_RDWR | O_CREAT | O_LARGEFILE;
#endif
/*	flags |= O_DIRECT; */
	/*
	 * If fd_buffered_io=1 has not been set explicitly (the default),
	 * use O_SYNC to force FILEIO writes to disk.
	 */
	if (!(fd_dev->fbd_flags & FDBD_USE_BUFFERED_IO))
		flags |= O_SYNC;

	file = filp_open(dev_p, flags, 0600);
	if (IS_ERR(file)) {
<<<<<<< HEAD
<<<<<<< HEAD
		pr_err("filp_open(%s) failed\n", dev_p);
=======
		printk(KERN_ERR "filp_open(%s) failed\n", dev_p);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		printk(KERN_ERR "filp_open(%s) failed\n", dev_p);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		ret = PTR_ERR(file);
		goto fail;
	}
	if (!file || !file->f_dentry) {
<<<<<<< HEAD
<<<<<<< HEAD
		pr_err("filp_open(%s) failed\n", dev_p);
=======
		printk(KERN_ERR "filp_open(%s) failed\n", dev_p);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		printk(KERN_ERR "filp_open(%s) failed\n", dev_p);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		goto fail;
	}
	fd_dev->fd_file = file;
	/*
	 * If using a block backend with this struct file, we extract
	 * fd_dev->fd_[block,dev]_size from struct block_device.
	 *
	 * Otherwise, we use the passed fd_size= from configfs
	 */
	inode = file->f_mapping->host;
	if (S_ISBLK(inode->i_mode)) {
		struct request_queue *q;
<<<<<<< HEAD
<<<<<<< HEAD
		unsigned long long dev_size;
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		/*
		 * Setup the local scope queue_limits from struct request_queue->limits
		 * to pass into transport_add_device_to_core_hba() as struct se_dev_limits.
		 */
		q = bdev_get_queue(inode->i_bdev);
		limits = &dev_limits.limits;
		limits->logical_block_size = bdev_logical_block_size(inode->i_bdev);
		limits->max_hw_sectors = queue_max_hw_sectors(q);
		limits->max_sectors = queue_max_sectors(q);
		/*
		 * Determine the number of bytes from i_size_read() minus
		 * one (1) logical sector from underlying struct block_device
		 */
		fd_dev->fd_block_size = bdev_logical_block_size(inode->i_bdev);
<<<<<<< HEAD
<<<<<<< HEAD
		dev_size = (i_size_read(file->f_mapping->host) -
				       fd_dev->fd_block_size);

		pr_debug("FILEIO: Using size: %llu bytes from struct"
			" block_device blocks: %llu logical_block_size: %d\n",
			dev_size, div_u64(dev_size, fd_dev->fd_block_size),
			fd_dev->fd_block_size);
	} else {
		if (!(fd_dev->fbd_flags & FBDF_HAS_SIZE)) {
			pr_err("FILEIO: Missing fd_dev_size="
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		fd_dev->fd_dev_size = (i_size_read(file->f_mapping->host) -
				       fd_dev->fd_block_size);

		printk(KERN_INFO "FILEIO: Using size: %llu bytes from struct"
			" block_device blocks: %llu logical_block_size: %d\n",
			fd_dev->fd_dev_size,
			div_u64(fd_dev->fd_dev_size, fd_dev->fd_block_size),
			fd_dev->fd_block_size);
	} else {
		if (!(fd_dev->fbd_flags & FBDF_HAS_SIZE)) {
			printk(KERN_ERR "FILEIO: Missing fd_dev_size="
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
				" parameter, and no backing struct"
				" block_device\n");
			goto fail;
		}

		limits = &dev_limits.limits;
		limits->logical_block_size = FD_BLOCKSIZE;
		limits->max_hw_sectors = FD_MAX_SECTORS;
		limits->max_sectors = FD_MAX_SECTORS;
		fd_dev->fd_block_size = FD_BLOCKSIZE;
	}

	dev_limits.hw_queue_depth = FD_MAX_DEVICE_QUEUE_DEPTH;
	dev_limits.queue_depth = FD_DEVICE_QUEUE_DEPTH;

	dev = transport_add_device_to_core_hba(hba, &fileio_template,
<<<<<<< HEAD
<<<<<<< HEAD
				se_dev, dev_flags, fd_dev,
				&dev_limits, "FILEIO", FD_VERSION);
	if (!dev)
=======
				se_dev, dev_flags, (void *)fd_dev,
				&dev_limits, "FILEIO", FD_VERSION);
	if (!(dev))
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
				se_dev, dev_flags, (void *)fd_dev,
				&dev_limits, "FILEIO", FD_VERSION);
	if (!(dev))
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		goto fail;

	fd_dev->fd_dev_id = fd_host->fd_host_dev_id_count++;
	fd_dev->fd_queue_depth = dev->queue_depth;

<<<<<<< HEAD
<<<<<<< HEAD
	pr_debug("CORE_FILE[%u] - Added TCM FILEIO Device ID: %u at %s,"
=======
	printk(KERN_INFO "CORE_FILE[%u] - Added TCM FILEIO Device ID: %u at %s,"
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	printk(KERN_INFO "CORE_FILE[%u] - Added TCM FILEIO Device ID: %u at %s,"
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		" %llu total bytes\n", fd_host->fd_host_id, fd_dev->fd_dev_id,
			fd_dev->fd_dev_name, fd_dev->fd_dev_size);

	putname(dev_p);
	return dev;
fail:
	if (fd_dev->fd_file) {
		filp_close(fd_dev->fd_file, NULL);
		fd_dev->fd_file = NULL;
	}
	putname(dev_p);
	return ERR_PTR(ret);
}

/*	fd_free_device(): (Part of se_subsystem_api_t template)
 *
 *
 */
static void fd_free_device(void *p)
{
<<<<<<< HEAD
<<<<<<< HEAD
	struct fd_dev *fd_dev = p;
=======
	struct fd_dev *fd_dev = (struct fd_dev *) p;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	struct fd_dev *fd_dev = (struct fd_dev *) p;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (fd_dev->fd_file) {
		filp_close(fd_dev->fd_file, NULL);
		fd_dev->fd_file = NULL;
	}

	kfree(fd_dev);
}

static inline struct fd_request *FILE_REQ(struct se_task *task)
{
	return container_of(task, struct fd_request, fd_task);
}


static struct se_task *
<<<<<<< HEAD
<<<<<<< HEAD
fd_alloc_task(unsigned char *cdb)
=======
fd_alloc_task(struct se_cmd *cmd)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
fd_alloc_task(struct se_cmd *cmd)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	struct fd_request *fd_req;

	fd_req = kzalloc(sizeof(struct fd_request), GFP_KERNEL);
<<<<<<< HEAD
<<<<<<< HEAD
	if (!fd_req) {
		pr_err("Unable to allocate struct fd_request\n");
		return NULL;
	}

=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (!(fd_req)) {
		printk(KERN_ERR "Unable to allocate struct fd_request\n");
		return NULL;
	}

	fd_req->fd_dev = SE_DEV(cmd)->dev_ptr;

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return &fd_req->fd_task;
}

static int fd_do_readv(struct se_task *task)
{
	struct fd_request *req = FILE_REQ(task);
<<<<<<< HEAD
<<<<<<< HEAD
	struct se_device *se_dev = req->fd_task.task_se_cmd->se_dev;
	struct fd_dev *dev = se_dev->dev_ptr;
	struct file *fd = dev->fd_file;
	struct scatterlist *sg = task->task_sg;
	struct iovec *iov;
	mm_segment_t old_fs;
	loff_t pos = (task->task_lba *
		      se_dev->se_sub_dev->se_dev_attrib.block_size);
	int ret = 0, i;

	iov = kzalloc(sizeof(struct iovec) * task->task_sg_nents, GFP_KERNEL);
	if (!iov) {
		pr_err("Unable to allocate fd_do_readv iov[]\n");
		return -ENOMEM;
	}

	for_each_sg(task->task_sg, sg, task->task_sg_nents, i) {
		iov[i].iov_len = sg->length;
		iov[i].iov_base = sg_virt(sg);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct file *fd = req->fd_dev->fd_file;
	struct scatterlist *sg = task->task_sg;
	struct iovec *iov;
	mm_segment_t old_fs;
	loff_t pos = (task->task_lba * DEV_ATTRIB(task->se_dev)->block_size);
	int ret = 0, i;

	iov = kzalloc(sizeof(struct iovec) * task->task_sg_num, GFP_KERNEL);
	if (!(iov)) {
		printk(KERN_ERR "Unable to allocate fd_do_readv iov[]\n");
		return -1;
	}

	for (i = 0; i < task->task_sg_num; i++) {
		iov[i].iov_len = sg[i].length;
		iov[i].iov_base = sg_virt(&sg[i]);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}

	old_fs = get_fs();
	set_fs(get_ds());
<<<<<<< HEAD
<<<<<<< HEAD
	ret = vfs_readv(fd, &iov[0], task->task_sg_nents, &pos);
=======
	ret = vfs_readv(fd, &iov[0], task->task_sg_num, &pos);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	ret = vfs_readv(fd, &iov[0], task->task_sg_num, &pos);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	set_fs(old_fs);

	kfree(iov);
	/*
	 * Return zeros and GOOD status even if the READ did not return
	 * the expected virt_size for struct file w/o a backing struct
	 * block_device.
	 */
	if (S_ISBLK(fd->f_dentry->d_inode->i_mode)) {
		if (ret < 0 || ret != task->task_size) {
<<<<<<< HEAD
<<<<<<< HEAD
			pr_err("vfs_readv() returned %d,"
				" expecting %d for S_ISBLK\n", ret,
				(int)task->task_size);
			return (ret < 0 ? ret : -EINVAL);
		}
	} else {
		if (ret < 0) {
			pr_err("vfs_readv() returned %d for non"
				" S_ISBLK\n", ret);
			return ret;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			printk(KERN_ERR "vfs_readv() returned %d,"
				" expecting %d for S_ISBLK\n", ret,
				(int)task->task_size);
			return -1;
		}
	} else {
		if (ret < 0) {
			printk(KERN_ERR "vfs_readv() returned %d for non"
				" S_ISBLK\n", ret);
			return -1;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		}
	}

	return 1;
}

static int fd_do_writev(struct se_task *task)
{
	struct fd_request *req = FILE_REQ(task);
<<<<<<< HEAD
<<<<<<< HEAD
	struct se_device *se_dev = req->fd_task.task_se_cmd->se_dev;
	struct fd_dev *dev = se_dev->dev_ptr;
	struct file *fd = dev->fd_file;
	struct scatterlist *sg = task->task_sg;
	struct iovec *iov;
	mm_segment_t old_fs;
	loff_t pos = (task->task_lba *
		      se_dev->se_sub_dev->se_dev_attrib.block_size);
	int ret, i = 0;

	iov = kzalloc(sizeof(struct iovec) * task->task_sg_nents, GFP_KERNEL);
	if (!iov) {
		pr_err("Unable to allocate fd_do_writev iov[]\n");
		return -ENOMEM;
	}

	for_each_sg(task->task_sg, sg, task->task_sg_nents, i) {
		iov[i].iov_len = sg->length;
		iov[i].iov_base = sg_virt(sg);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct file *fd = req->fd_dev->fd_file;
	struct scatterlist *sg = task->task_sg;
	struct iovec *iov;
	mm_segment_t old_fs;
	loff_t pos = (task->task_lba * DEV_ATTRIB(task->se_dev)->block_size);
	int ret, i = 0;

	iov = kzalloc(sizeof(struct iovec) * task->task_sg_num, GFP_KERNEL);
	if (!(iov)) {
		printk(KERN_ERR "Unable to allocate fd_do_writev iov[]\n");
		return -1;
	}

	for (i = 0; i < task->task_sg_num; i++) {
		iov[i].iov_len = sg[i].length;
		iov[i].iov_base = sg_virt(&sg[i]);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}

	old_fs = get_fs();
	set_fs(get_ds());
<<<<<<< HEAD
<<<<<<< HEAD
	ret = vfs_writev(fd, &iov[0], task->task_sg_nents, &pos);
=======
	ret = vfs_writev(fd, &iov[0], task->task_sg_num, &pos);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	ret = vfs_writev(fd, &iov[0], task->task_sg_num, &pos);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	set_fs(old_fs);

	kfree(iov);

	if (ret < 0 || ret != task->task_size) {
<<<<<<< HEAD
<<<<<<< HEAD
		pr_err("vfs_writev() returned %d\n", ret);
		return (ret < 0 ? ret : -EINVAL);
=======
		printk(KERN_ERR "vfs_writev() returned %d\n", ret);
		return -1;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		printk(KERN_ERR "vfs_writev() returned %d\n", ret);
		return -1;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}

	return 1;
}

static void fd_emulate_sync_cache(struct se_task *task)
{
<<<<<<< HEAD
<<<<<<< HEAD
	struct se_cmd *cmd = task->task_se_cmd;
	struct se_device *dev = cmd->se_dev;
	struct fd_dev *fd_dev = dev->dev_ptr;
	int immed = (cmd->t_task_cdb[1] & 0x2);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct se_cmd *cmd = TASK_CMD(task);
	struct se_device *dev = cmd->se_dev;
	struct fd_dev *fd_dev = dev->dev_ptr;
	int immed = (cmd->t_task->t_task_cdb[1] & 0x2);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	loff_t start, end;
	int ret;

	/*
	 * If the Immediate bit is set, queue up the GOOD response
	 * for this SYNCHRONIZE_CACHE op
	 */
	if (immed)
		transport_complete_sync_cache(cmd, 1);

	/*
	 * Determine if we will be flushing the entire device.
	 */
<<<<<<< HEAD
<<<<<<< HEAD
	if (cmd->t_task_lba == 0 && cmd->data_length == 0) {
		start = 0;
		end = LLONG_MAX;
	} else {
		start = cmd->t_task_lba * dev->se_sub_dev->se_dev_attrib.block_size;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (cmd->t_task->t_task_lba == 0 && cmd->data_length == 0) {
		start = 0;
		end = LLONG_MAX;
	} else {
		start = cmd->t_task->t_task_lba * DEV_ATTRIB(dev)->block_size;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		if (cmd->data_length)
			end = start + cmd->data_length;
		else
			end = LLONG_MAX;
	}

	ret = vfs_fsync_range(fd_dev->fd_file, start, end, 1);
	if (ret != 0)
<<<<<<< HEAD
<<<<<<< HEAD
		pr_err("FILEIO: vfs_fsync_range() failed: %d\n", ret);
=======
		printk(KERN_ERR "FILEIO: vfs_fsync_range() failed: %d\n", ret);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		printk(KERN_ERR "FILEIO: vfs_fsync_range() failed: %d\n", ret);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (!immed)
		transport_complete_sync_cache(cmd, ret == 0);
}

/*
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * Tell TCM Core that we are capable of WriteCache emulation for
 * an underlying struct se_device.
 */
static int fd_emulated_write_cache(struct se_device *dev)
{
	return 1;
}

static int fd_emulated_dpo(struct se_device *dev)
{
	return 0;
}
/*
 * Tell TCM Core that we will be emulating Forced Unit Access (FUA) for WRITEs
 * for TYPE_DISK.
 */
static int fd_emulated_fua_write(struct se_device *dev)
{
	return 1;
}

static int fd_emulated_fua_read(struct se_device *dev)
{
	return 0;
}

/*
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * WRITE Force Unit Access (FUA) emulation on a per struct se_task
 * LBA range basis..
 */
static void fd_emulate_write_fua(struct se_cmd *cmd, struct se_task *task)
{
	struct se_device *dev = cmd->se_dev;
	struct fd_dev *fd_dev = dev->dev_ptr;
<<<<<<< HEAD
<<<<<<< HEAD
	loff_t start = task->task_lba * dev->se_sub_dev->se_dev_attrib.block_size;
	loff_t end = start + task->task_size;
	int ret;

	pr_debug("FILEIO: FUA WRITE LBA: %llu, bytes: %u\n",
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	loff_t start = task->task_lba * DEV_ATTRIB(dev)->block_size;
	loff_t end = start + task->task_size;
	int ret;

	DEBUG_FD_CACHE("FILEIO: FUA WRITE LBA: %llu, bytes: %u\n",
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			task->task_lba, task->task_size);

	ret = vfs_fsync_range(fd_dev->fd_file, start, end, 1);
	if (ret != 0)
<<<<<<< HEAD
<<<<<<< HEAD
		pr_err("FILEIO: vfs_fsync_range() failed: %d\n", ret);
=======
		printk(KERN_ERR "FILEIO: vfs_fsync_range() failed: %d\n", ret);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		printk(KERN_ERR "FILEIO: vfs_fsync_range() failed: %d\n", ret);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static int fd_do_task(struct se_task *task)
{
	struct se_cmd *cmd = task->task_se_cmd;
	struct se_device *dev = cmd->se_dev;
	int ret = 0;

	/*
	 * Call vectorized fileio functions to map struct scatterlist
	 * physical memory addresses to struct iovec virtual memory.
	 */
	if (task->task_data_direction == DMA_FROM_DEVICE) {
		ret = fd_do_readv(task);
	} else {
		ret = fd_do_writev(task);

		if (ret > 0 &&
<<<<<<< HEAD
<<<<<<< HEAD
		    dev->se_sub_dev->se_dev_attrib.emulate_write_cache > 0 &&
		    dev->se_sub_dev->se_dev_attrib.emulate_fua_write > 0 &&
		    (cmd->se_cmd_flags & SCF_FUA)) {
=======
		    DEV_ATTRIB(dev)->emulate_write_cache > 0 &&
		    DEV_ATTRIB(dev)->emulate_fua_write > 0 &&
		    T_TASK(cmd)->t_tasks_fua) {
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		    DEV_ATTRIB(dev)->emulate_write_cache > 0 &&
		    DEV_ATTRIB(dev)->emulate_fua_write > 0 &&
		    T_TASK(cmd)->t_tasks_fua) {
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			/*
			 * We might need to be a bit smarter here
			 * and return some sense data to let the initiator
			 * know the FUA WRITE cache sync failed..?
			 */
			fd_emulate_write_fua(cmd, task);
		}

	}

<<<<<<< HEAD
<<<<<<< HEAD
	if (ret < 0) {
		cmd->scsi_sense_reason = TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
		return ret;
	}
=======
	if (ret < 0)
		return ret;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	if (ret < 0)
		return ret;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (ret) {
		task->task_scsi_status = GOOD;
		transport_complete_task(task, 1);
	}
<<<<<<< HEAD
<<<<<<< HEAD
	return 0;
=======
	return PYX_TRANSPORT_SENT_TO_TRANSPORT;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	return PYX_TRANSPORT_SENT_TO_TRANSPORT;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

/*	fd_free_task(): (Part of se_subsystem_api_t template)
 *
 *
 */
static void fd_free_task(struct se_task *task)
{
	struct fd_request *req = FILE_REQ(task);

	kfree(req);
}

enum {
	Opt_fd_dev_name, Opt_fd_dev_size, Opt_fd_buffered_io, Opt_err
};

static match_table_t tokens = {
	{Opt_fd_dev_name, "fd_dev_name=%s"},
	{Opt_fd_dev_size, "fd_dev_size=%s"},
	{Opt_fd_buffered_io, "fd_buffered_io=%d"},
	{Opt_err, NULL}
};

static ssize_t fd_set_configfs_dev_params(
	struct se_hba *hba,
	struct se_subsystem_dev *se_dev,
	const char *page, ssize_t count)
{
	struct fd_dev *fd_dev = se_dev->se_dev_su_ptr;
	char *orig, *ptr, *arg_p, *opts;
	substring_t args[MAX_OPT_ARGS];
	int ret = 0, arg, token;

	opts = kstrdup(page, GFP_KERNEL);
	if (!opts)
		return -ENOMEM;

	orig = opts;

<<<<<<< HEAD
<<<<<<< HEAD
	while ((ptr = strsep(&opts, ",\n")) != NULL) {
=======
	while ((ptr = strsep(&opts, ",")) != NULL) {
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	while ((ptr = strsep(&opts, ",")) != NULL) {
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		if (!*ptr)
			continue;

		token = match_token(ptr, tokens, args);
		switch (token) {
		case Opt_fd_dev_name:
			arg_p = match_strdup(&args[0]);
			if (!arg_p) {
				ret = -ENOMEM;
				break;
			}
			snprintf(fd_dev->fd_dev_name, FD_MAX_DEV_NAME,
					"%s", arg_p);
			kfree(arg_p);
<<<<<<< HEAD
<<<<<<< HEAD
			pr_debug("FILEIO: Referencing Path: %s\n",
=======
			printk(KERN_INFO "FILEIO: Referencing Path: %s\n",
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			printk(KERN_INFO "FILEIO: Referencing Path: %s\n",
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
					fd_dev->fd_dev_name);
			fd_dev->fbd_flags |= FBDF_HAS_PATH;
			break;
		case Opt_fd_dev_size:
			arg_p = match_strdup(&args[0]);
			if (!arg_p) {
				ret = -ENOMEM;
				break;
			}
			ret = strict_strtoull(arg_p, 0, &fd_dev->fd_dev_size);
			kfree(arg_p);
			if (ret < 0) {
<<<<<<< HEAD
<<<<<<< HEAD
				pr_err("strict_strtoull() failed for"
						" fd_dev_size=\n");
				goto out;
			}
			pr_debug("FILEIO: Referencing Size: %llu"
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
				printk(KERN_ERR "strict_strtoull() failed for"
						" fd_dev_size=\n");
				goto out;
			}
			printk(KERN_INFO "FILEIO: Referencing Size: %llu"
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
					" bytes\n", fd_dev->fd_dev_size);
			fd_dev->fbd_flags |= FBDF_HAS_SIZE;
			break;
		case Opt_fd_buffered_io:
			match_int(args, &arg);
			if (arg != 1) {
<<<<<<< HEAD
<<<<<<< HEAD
				pr_err("bogus fd_buffered_io=%d value\n", arg);
=======
				printk(KERN_ERR "bogus fd_buffered_io=%d value\n", arg);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
				printk(KERN_ERR "bogus fd_buffered_io=%d value\n", arg);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
				ret = -EINVAL;
				goto out;
			}

<<<<<<< HEAD
<<<<<<< HEAD
			pr_debug("FILEIO: Using buffered I/O"
=======
			printk(KERN_INFO "FILEIO: Using buffered I/O"
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			printk(KERN_INFO "FILEIO: Using buffered I/O"
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
				" operations for struct fd_dev\n");

			fd_dev->fbd_flags |= FDBD_USE_BUFFERED_IO;
			break;
		default:
			break;
		}
	}

out:
	kfree(orig);
	return (!ret) ? count : ret;
}

static ssize_t fd_check_configfs_dev_params(struct se_hba *hba, struct se_subsystem_dev *se_dev)
{
<<<<<<< HEAD
<<<<<<< HEAD
	struct fd_dev *fd_dev = se_dev->se_dev_su_ptr;

	if (!(fd_dev->fbd_flags & FBDF_HAS_PATH)) {
		pr_err("Missing fd_dev_name=\n");
		return -EINVAL;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct fd_dev *fd_dev = (struct fd_dev *) se_dev->se_dev_su_ptr;

	if (!(fd_dev->fbd_flags & FBDF_HAS_PATH)) {
		printk(KERN_ERR "Missing fd_dev_name=\n");
		return -1;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}

	return 0;
}

static ssize_t fd_show_configfs_dev_params(
	struct se_hba *hba,
	struct se_subsystem_dev *se_dev,
	char *b)
{
	struct fd_dev *fd_dev = se_dev->se_dev_su_ptr;
	ssize_t bl = 0;

	bl = sprintf(b + bl, "TCM FILEIO ID: %u", fd_dev->fd_dev_id);
	bl += sprintf(b + bl, "        File: %s  Size: %llu  Mode: %s\n",
		fd_dev->fd_dev_name, fd_dev->fd_dev_size,
		(fd_dev->fbd_flags & FDBD_USE_BUFFERED_IO) ?
		"Buffered" : "Synchronous");
	return bl;
}

<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/*	fd_get_cdb(): (Part of se_subsystem_api_t template)
 *
 *
 */
static unsigned char *fd_get_cdb(struct se_task *task)
{
	struct fd_request *req = FILE_REQ(task);

	return req->fd_scsi_cdb;
}

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/*	fd_get_device_rev(): (Part of se_subsystem_api_t template)
 *
 *
 */
static u32 fd_get_device_rev(struct se_device *dev)
{
	return SCSI_SPC_2; /* Returns SPC-3 in Initiator Data */
}

/*	fd_get_device_type(): (Part of se_subsystem_api_t template)
 *
 *
 */
static u32 fd_get_device_type(struct se_device *dev)
{
	return TYPE_DISK;
}

static sector_t fd_get_blocks(struct se_device *dev)
{
	struct fd_dev *fd_dev = dev->dev_ptr;
<<<<<<< HEAD
<<<<<<< HEAD
	struct file *f = fd_dev->fd_file;
	struct inode *i = f->f_mapping->host;
	unsigned long long dev_size;
	/*
	 * When using a file that references an underlying struct block_device,
	 * ensure dev_size is always based on the current inode size in order
	 * to handle underlying block_device resize operations.
	 */
	if (S_ISBLK(i->i_mode))
		dev_size = (i_size_read(i) - fd_dev->fd_block_size);
	else
		dev_size = fd_dev->fd_dev_size;

	return div_u64(dev_size, dev->se_sub_dev->se_dev_attrib.block_size);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	unsigned long long blocks_long = div_u64(fd_dev->fd_dev_size,
			DEV_ATTRIB(dev)->block_size);

	return blocks_long;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static struct se_subsystem_api fileio_template = {
	.name			= "fileio",
	.owner			= THIS_MODULE,
	.transport_type		= TRANSPORT_PLUGIN_VHBA_PDEV,
<<<<<<< HEAD
<<<<<<< HEAD
	.write_cache_emulated	= 1,
	.fua_write_emulated	= 1,
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	.attach_hba		= fd_attach_hba,
	.detach_hba		= fd_detach_hba,
	.allocate_virtdevice	= fd_allocate_virtdevice,
	.create_virtdevice	= fd_create_virtdevice,
	.free_device		= fd_free_device,
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	.dpo_emulated		= fd_emulated_dpo,
	.fua_write_emulated	= fd_emulated_fua_write,
	.fua_read_emulated	= fd_emulated_fua_read,
	.write_cache_emulated	= fd_emulated_write_cache,
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	.alloc_task		= fd_alloc_task,
	.do_task		= fd_do_task,
	.do_sync_cache		= fd_emulate_sync_cache,
	.free_task		= fd_free_task,
	.check_configfs_dev_params = fd_check_configfs_dev_params,
	.set_configfs_dev_params = fd_set_configfs_dev_params,
	.show_configfs_dev_params = fd_show_configfs_dev_params,
<<<<<<< HEAD
<<<<<<< HEAD
=======
	.get_cdb		= fd_get_cdb,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	.get_cdb		= fd_get_cdb,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	.get_device_rev		= fd_get_device_rev,
	.get_device_type	= fd_get_device_type,
	.get_blocks		= fd_get_blocks,
};

static int __init fileio_module_init(void)
{
	return transport_subsystem_register(&fileio_template);
}

static void fileio_module_exit(void)
{
	transport_subsystem_release(&fileio_template);
}

MODULE_DESCRIPTION("TCM FILEIO subsystem plugin");
MODULE_AUTHOR("nab@Linux-iSCSI.org");
MODULE_LICENSE("GPL");

module_init(fileio_module_init);
module_exit(fileio_module_exit);
