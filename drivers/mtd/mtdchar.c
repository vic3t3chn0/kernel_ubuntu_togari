/*
 * Copyright © 1999-2010 David Woodhouse <dwmw2@infradead.org>
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
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include <linux/device.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/err.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/mutex.h>
#include <linux/backing-dev.h>
#include <linux/compat.h>
#include <linux/mount.h>
#include <linux/blkpg.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/magic.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/partitions.h>
#include <linux/mtd/map.h>
#include <linux/mtd/partitions.h>

#include <asm/uaccess.h>

static DEFINE_MUTEX(mtd_mutex);

/*
 * Data structure to hold the pointer to the mtd device as well
 * as mode information of various use cases.
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <linux/mtd/mtd.h>
#include <linux/mtd/partitions.h>
#include <linux/mtd/map.h>

#include <asm/uaccess.h>

#define MTD_INODE_FS_MAGIC 0x11307854
static DEFINE_MUTEX(mtd_mutex);
static struct vfsmount *mtd_inode_mnt __read_mostly;

/*
 * Data structure to hold the pointer to the mtd device as well
 * as mode information ofr various use cases.
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
struct mtd_file_info {
	struct mtd_info *mtd;
	struct inode *ino;
	enum mtd_file_modes mode;
};

<<<<<<< HEAD
<<<<<<< HEAD
static loff_t mtdchar_lseek(struct file *file, loff_t offset, int orig)
=======
static loff_t mtd_lseek (struct file *file, loff_t offset, int orig)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static loff_t mtd_lseek (struct file *file, loff_t offset, int orig)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	struct mtd_file_info *mfi = file->private_data;
	struct mtd_info *mtd = mfi->mtd;

	switch (orig) {
	case SEEK_SET:
		break;
	case SEEK_CUR:
		offset += file->f_pos;
		break;
	case SEEK_END:
		offset += mtd->size;
		break;
	default:
		return -EINVAL;
	}

	if (offset >= 0 && offset <= mtd->size)
		return file->f_pos = offset;

	return -EINVAL;
}

<<<<<<< HEAD
<<<<<<< HEAD
static int count;
static struct vfsmount *mnt;
static struct file_system_type mtd_inodefs_type;

static int mtdchar_open(struct inode *inode, struct file *file)
=======


static int mtd_open(struct inode *inode, struct file *file)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======


static int mtd_open(struct inode *inode, struct file *file)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	int minor = iminor(inode);
	int devnum = minor >> 1;
	int ret = 0;
	struct mtd_info *mtd;
	struct mtd_file_info *mfi;
	struct inode *mtd_ino;

<<<<<<< HEAD
<<<<<<< HEAD
	pr_debug("MTD_open\n");
=======
	DEBUG(MTD_DEBUG_LEVEL0, "MTD_open\n");
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	DEBUG(MTD_DEBUG_LEVEL0, "MTD_open\n");
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	/* You can't open the RO devices RW */
	if ((file->f_mode & FMODE_WRITE) && (minor & 1))
		return -EACCES;

<<<<<<< HEAD
<<<<<<< HEAD
	ret = simple_pin_fs(&mtd_inodefs_type, &mnt, &count);
	if (ret)
		return ret;

=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	mutex_lock(&mtd_mutex);
	mtd = get_mtd_device(NULL, devnum);

	if (IS_ERR(mtd)) {
		ret = PTR_ERR(mtd);
		goto out;
	}

	if (mtd->type == MTD_ABSENT) {
<<<<<<< HEAD
<<<<<<< HEAD
		ret = -ENODEV;
		goto out1;
	}

	mtd_ino = iget_locked(mnt->mnt_sb, devnum);
	if (!mtd_ino) {
		ret = -ENOMEM;
		goto out1;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		put_mtd_device(mtd);
		ret = -ENODEV;
		goto out;
	}

	mtd_ino = iget_locked(mtd_inode_mnt->mnt_sb, devnum);
	if (!mtd_ino) {
		put_mtd_device(mtd);
		ret = -ENOMEM;
		goto out;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}
	if (mtd_ino->i_state & I_NEW) {
		mtd_ino->i_private = mtd;
		mtd_ino->i_mode = S_IFCHR;
		mtd_ino->i_data.backing_dev_info = mtd->backing_dev_info;
		unlock_new_inode(mtd_ino);
	}
	file->f_mapping = mtd_ino->i_mapping;

	/* You can't open it RW if it's not a writeable device */
	if ((file->f_mode & FMODE_WRITE) && !(mtd->flags & MTD_WRITEABLE)) {
<<<<<<< HEAD
<<<<<<< HEAD
		ret = -EACCES;
		goto out2;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		iput(mtd_ino);
		put_mtd_device(mtd);
		ret = -EACCES;
		goto out;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}

	mfi = kzalloc(sizeof(*mfi), GFP_KERNEL);
	if (!mfi) {
<<<<<<< HEAD
<<<<<<< HEAD
		ret = -ENOMEM;
		goto out2;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		iput(mtd_ino);
		put_mtd_device(mtd);
		ret = -ENOMEM;
		goto out;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}
	mfi->ino = mtd_ino;
	mfi->mtd = mtd;
	file->private_data = mfi;
<<<<<<< HEAD
<<<<<<< HEAD
	mutex_unlock(&mtd_mutex);
	return 0;

out2:
	iput(mtd_ino);
out1:
	put_mtd_device(mtd);
out:
	mutex_unlock(&mtd_mutex);
	simple_release_fs(&mnt, &count);
	return ret;
} /* mtdchar_open */

/*====================================================================*/

static int mtdchar_close(struct inode *inode, struct file *file)
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

out:
	mutex_unlock(&mtd_mutex);
	return ret;
} /* mtd_open */

/*====================================================================*/

static int mtd_close(struct inode *inode, struct file *file)
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	struct mtd_file_info *mfi = file->private_data;
	struct mtd_info *mtd = mfi->mtd;

<<<<<<< HEAD
<<<<<<< HEAD
	pr_debug("MTD_close\n");

	/* Only sync if opened RW */
	if ((file->f_mode & FMODE_WRITE))
		mtd_sync(mtd);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	DEBUG(MTD_DEBUG_LEVEL0, "MTD_close\n");

	/* Only sync if opened RW */
	if ((file->f_mode & FMODE_WRITE) && mtd->sync)
		mtd->sync(mtd);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	iput(mfi->ino);

	put_mtd_device(mtd);
	file->private_data = NULL;
	kfree(mfi);
<<<<<<< HEAD
<<<<<<< HEAD
	simple_release_fs(&mnt, &count);

	return 0;
} /* mtdchar_close */
=======

	return 0;
} /* mtd_close */
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======

	return 0;
} /* mtd_close */
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/* Back in June 2001, dwmw2 wrote:
 *
 *   FIXME: This _really_ needs to die. In 2.5, we should lock the
 *   userspace buffer down and use it directly with readv/writev.
 *
 * The implementation below, using mtd_kmalloc_up_to, mitigates
 * allocation failures when the system is under low-memory situations
 * or if memory is highly fragmented at the cost of reducing the
 * performance of the requested transfer due to a smaller buffer size.
 *
 * A more complex but more memory-efficient implementation based on
 * get_user_pages and iovecs to cover extents of those pages is a
 * longer-term goal, as intimated by dwmw2 above. However, for the
 * write case, this requires yet more complex head and tail transfer
 * handling when those head and tail offsets and sizes are such that
 * alignment requirements are not met in the NAND subdriver.
 */

<<<<<<< HEAD
<<<<<<< HEAD
static ssize_t mtdchar_read(struct file *file, char __user *buf, size_t count,
			loff_t *ppos)
{
	struct mtd_file_info *mfi = file->private_data;
	struct mtd_info *mtd = mfi->mtd;
	size_t retlen;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static ssize_t mtd_read(struct file *file, char __user *buf, size_t count,loff_t *ppos)
{
	struct mtd_file_info *mfi = file->private_data;
	struct mtd_info *mtd = mfi->mtd;
	size_t retlen=0;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	size_t total_retlen=0;
	int ret=0;
	int len;
	size_t size = count;
	char *kbuf;

<<<<<<< HEAD
<<<<<<< HEAD
	pr_debug("MTD_read\n");
=======
	DEBUG(MTD_DEBUG_LEVEL0,"MTD_read\n");
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	DEBUG(MTD_DEBUG_LEVEL0,"MTD_read\n");
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (*ppos + count > mtd->size)
		count = mtd->size - *ppos;

	if (!count)
		return 0;

	kbuf = mtd_kmalloc_up_to(mtd, &size);
	if (!kbuf)
		return -ENOMEM;

	while (count) {
		len = min_t(size_t, count, size);

		switch (mfi->mode) {
<<<<<<< HEAD
<<<<<<< HEAD
		case MTD_FILE_MODE_OTP_FACTORY:
			ret = mtd_read_fact_prot_reg(mtd, *ppos, len,
						     &retlen, kbuf);
			break;
		case MTD_FILE_MODE_OTP_USER:
			ret = mtd_read_user_prot_reg(mtd, *ppos, len,
						     &retlen, kbuf);
			break;
		case MTD_FILE_MODE_RAW:
		{
			struct mtd_oob_ops ops;

			ops.mode = MTD_OPS_RAW;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		case MTD_MODE_OTP_FACTORY:
			ret = mtd->read_fact_prot_reg(mtd, *ppos, len, &retlen, kbuf);
			break;
		case MTD_MODE_OTP_USER:
			ret = mtd->read_user_prot_reg(mtd, *ppos, len, &retlen, kbuf);
			break;
		case MTD_MODE_RAW:
		{
			struct mtd_oob_ops ops;

			ops.mode = MTD_OOB_RAW;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			ops.datbuf = kbuf;
			ops.oobbuf = NULL;
			ops.len = len;

<<<<<<< HEAD
<<<<<<< HEAD
			ret = mtd_read_oob(mtd, *ppos, &ops);
=======
			ret = mtd->read_oob(mtd, *ppos, &ops);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			ret = mtd->read_oob(mtd, *ppos, &ops);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			retlen = ops.retlen;
			break;
		}
		default:
<<<<<<< HEAD
<<<<<<< HEAD
			ret = mtd_read(mtd, *ppos, len, &retlen, kbuf);
		}
		/* Nand returns -EBADMSG on ECC errors, but it returns
		 * the data. For our userspace tools it is important
		 * to dump areas with ECC errors!
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			ret = mtd->read(mtd, *ppos, len, &retlen, kbuf);
		}
		/* Nand returns -EBADMSG on ecc errors, but it returns
		 * the data. For our userspace tools it is important
		 * to dump areas with ecc errors !
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		 * For kernel internal usage it also might return -EUCLEAN
		 * to signal the caller that a bitflip has occurred and has
		 * been corrected by the ECC algorithm.
		 * Userspace software which accesses NAND this way
		 * must be aware of the fact that it deals with NAND
		 */
<<<<<<< HEAD
<<<<<<< HEAD
		if (!ret || mtd_is_bitflip_or_eccerr(ret)) {
=======
		if (!ret || (ret == -EUCLEAN) || (ret == -EBADMSG)) {
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		if (!ret || (ret == -EUCLEAN) || (ret == -EBADMSG)) {
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			*ppos += retlen;
			if (copy_to_user(buf, kbuf, retlen)) {
				kfree(kbuf);
				return -EFAULT;
			}
			else
				total_retlen += retlen;

			count -= retlen;
			buf += retlen;
			if (retlen == 0)
				count = 0;
		}
		else {
			kfree(kbuf);
			return ret;
		}

	}

	kfree(kbuf);
	return total_retlen;
<<<<<<< HEAD
<<<<<<< HEAD
} /* mtdchar_read */

static ssize_t mtdchar_write(struct file *file, const char __user *buf, size_t count,
			loff_t *ppos)
=======
} /* mtd_read */

static ssize_t mtd_write(struct file *file, const char __user *buf, size_t count,loff_t *ppos)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
} /* mtd_read */

static ssize_t mtd_write(struct file *file, const char __user *buf, size_t count,loff_t *ppos)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	struct mtd_file_info *mfi = file->private_data;
	struct mtd_info *mtd = mfi->mtd;
	size_t size = count;
	char *kbuf;
	size_t retlen;
	size_t total_retlen=0;
	int ret=0;
	int len;

<<<<<<< HEAD
<<<<<<< HEAD
	pr_debug("MTD_write\n");
=======
	DEBUG(MTD_DEBUG_LEVEL0,"MTD_write\n");
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	DEBUG(MTD_DEBUG_LEVEL0,"MTD_write\n");
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (*ppos == mtd->size)
		return -ENOSPC;

	if (*ppos + count > mtd->size)
		count = mtd->size - *ppos;

	if (!count)
		return 0;

	kbuf = mtd_kmalloc_up_to(mtd, &size);
	if (!kbuf)
		return -ENOMEM;

	while (count) {
		len = min_t(size_t, count, size);

		if (copy_from_user(kbuf, buf, len)) {
			kfree(kbuf);
			return -EFAULT;
		}

		switch (mfi->mode) {
<<<<<<< HEAD
<<<<<<< HEAD
		case MTD_FILE_MODE_OTP_FACTORY:
			ret = -EROFS;
			break;
		case MTD_FILE_MODE_OTP_USER:
			ret = mtd_write_user_prot_reg(mtd, *ppos, len,
						      &retlen, kbuf);
			break;

		case MTD_FILE_MODE_RAW:
		{
			struct mtd_oob_ops ops;

			ops.mode = MTD_OPS_RAW;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		case MTD_MODE_OTP_FACTORY:
			ret = -EROFS;
			break;
		case MTD_MODE_OTP_USER:
			if (!mtd->write_user_prot_reg) {
				ret = -EOPNOTSUPP;
				break;
			}
			ret = mtd->write_user_prot_reg(mtd, *ppos, len, &retlen, kbuf);
			break;

		case MTD_MODE_RAW:
		{
			struct mtd_oob_ops ops;

			ops.mode = MTD_OOB_RAW;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			ops.datbuf = kbuf;
			ops.oobbuf = NULL;
			ops.ooboffs = 0;
			ops.len = len;

<<<<<<< HEAD
<<<<<<< HEAD
			ret = mtd_write_oob(mtd, *ppos, &ops);
=======
			ret = mtd->write_oob(mtd, *ppos, &ops);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			ret = mtd->write_oob(mtd, *ppos, &ops);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			retlen = ops.retlen;
			break;
		}

		default:
<<<<<<< HEAD
<<<<<<< HEAD
			ret = mtd_write(mtd, *ppos, len, &retlen, kbuf);
=======
			ret = (*(mtd->write))(mtd, *ppos, len, &retlen, kbuf);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			ret = (*(mtd->write))(mtd, *ppos, len, &retlen, kbuf);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		}
		if (!ret) {
			*ppos += retlen;
			total_retlen += retlen;
			count -= retlen;
			buf += retlen;
		}
		else {
			kfree(kbuf);
			return ret;
		}
	}

	kfree(kbuf);
	return total_retlen;
<<<<<<< HEAD
<<<<<<< HEAD
} /* mtdchar_write */
=======
} /* mtd_write */
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
} /* mtd_write */
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/*======================================================================

    IOCTL calls for getting device parameters.

======================================================================*/
static void mtdchar_erase_callback (struct erase_info *instr)
{
	wake_up((wait_queue_head_t *)instr->priv);
}

#ifdef CONFIG_HAVE_MTD_OTP
static int otp_select_filemode(struct mtd_file_info *mfi, int mode)
{
	struct mtd_info *mtd = mfi->mtd;
<<<<<<< HEAD
<<<<<<< HEAD
	size_t retlen;
	int ret = 0;

	/*
	 * Make a fake call to mtd_read_fact_prot_reg() to check if OTP
	 * operations are supported.
	 */
	if (mtd_read_fact_prot_reg(mtd, -1, 0, &retlen, NULL) == -EOPNOTSUPP)
		return -EOPNOTSUPP;

	switch (mode) {
	case MTD_OTP_FACTORY:
		mfi->mode = MTD_FILE_MODE_OTP_FACTORY;
		break;
	case MTD_OTP_USER:
		mfi->mode = MTD_FILE_MODE_OTP_USER;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int ret = 0;

	switch (mode) {
	case MTD_OTP_FACTORY:
		if (!mtd->read_fact_prot_reg)
			ret = -EOPNOTSUPP;
		else
			mfi->mode = MTD_MODE_OTP_FACTORY;
		break;
	case MTD_OTP_USER:
		if (!mtd->read_fact_prot_reg)
			ret = -EOPNOTSUPP;
		else
			mfi->mode = MTD_MODE_OTP_USER;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		break;
	default:
		ret = -EINVAL;
	case MTD_OTP_OFF:
		break;
	}
	return ret;
}
#else
# define otp_select_filemode(f,m)	-EOPNOTSUPP
#endif

<<<<<<< HEAD
<<<<<<< HEAD
static int mtdchar_writeoob(struct file *file, struct mtd_info *mtd,
	uint64_t start, uint32_t length, void __user *ptr,
	uint32_t __user *retp)
{
	struct mtd_file_info *mfi = file->private_data;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static int mtd_do_writeoob(struct file *file, struct mtd_info *mtd,
	uint64_t start, uint32_t length, void __user *ptr,
	uint32_t __user *retp)
{
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct mtd_oob_ops ops;
	uint32_t retlen;
	int ret = 0;

	if (!(file->f_mode & FMODE_WRITE))
		return -EPERM;

	if (length > 4096)
		return -EINVAL;

<<<<<<< HEAD
<<<<<<< HEAD
	if (!mtd->_write_oob)
=======
	if (!mtd->write_oob)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	if (!mtd->write_oob)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		ret = -EOPNOTSUPP;
	else
		ret = access_ok(VERIFY_READ, ptr, length) ? 0 : -EFAULT;

	if (ret)
		return ret;

	ops.ooblen = length;
<<<<<<< HEAD
<<<<<<< HEAD
	ops.ooboffs = start & (mtd->writesize - 1);
	ops.datbuf = NULL;
	ops.mode = (mfi->mode == MTD_FILE_MODE_RAW) ? MTD_OPS_RAW :
		MTD_OPS_PLACE_OOB;
=======
	ops.ooboffs = start & (mtd->oobsize - 1);
	ops.datbuf = NULL;
	ops.mode = MTD_OOB_PLACE;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	ops.ooboffs = start & (mtd->oobsize - 1);
	ops.datbuf = NULL;
	ops.mode = MTD_OOB_PLACE;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (ops.ooboffs && ops.ooblen > (mtd->oobsize - ops.ooboffs))
		return -EINVAL;

	ops.oobbuf = memdup_user(ptr, length);
	if (IS_ERR(ops.oobbuf))
		return PTR_ERR(ops.oobbuf);

<<<<<<< HEAD
<<<<<<< HEAD
	start &= ~((uint64_t)mtd->writesize - 1);
	ret = mtd_write_oob(mtd, start, &ops);
=======
	start &= ~((uint64_t)mtd->oobsize - 1);
	ret = mtd->write_oob(mtd, start, &ops);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	start &= ~((uint64_t)mtd->oobsize - 1);
	ret = mtd->write_oob(mtd, start, &ops);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (ops.oobretlen > 0xFFFFFFFFU)
		ret = -EOVERFLOW;
	retlen = ops.oobretlen;
	if (copy_to_user(retp, &retlen, sizeof(length)))
		ret = -EFAULT;

	kfree(ops.oobbuf);
	return ret;
}

<<<<<<< HEAD
<<<<<<< HEAD
static int mtdchar_readoob(struct file *file, struct mtd_info *mtd,
	uint64_t start, uint32_t length, void __user *ptr,
	uint32_t __user *retp)
{
	struct mtd_file_info *mfi = file->private_data;
=======
static int mtd_do_readoob(struct mtd_info *mtd, uint64_t start,
	uint32_t length, void __user *ptr, uint32_t __user *retp)
{
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static int mtd_do_readoob(struct mtd_info *mtd, uint64_t start,
	uint32_t length, void __user *ptr, uint32_t __user *retp)
{
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct mtd_oob_ops ops;
	int ret = 0;

	if (length > 4096)
		return -EINVAL;

<<<<<<< HEAD
<<<<<<< HEAD
	if (!access_ok(VERIFY_WRITE, ptr, length))
		return -EFAULT;

	ops.ooblen = length;
	ops.ooboffs = start & (mtd->writesize - 1);
	ops.datbuf = NULL;
	ops.mode = (mfi->mode == MTD_FILE_MODE_RAW) ? MTD_OPS_RAW :
		MTD_OPS_PLACE_OOB;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (!mtd->read_oob)
		ret = -EOPNOTSUPP;
	else
		ret = access_ok(VERIFY_WRITE, ptr,
				length) ? 0 : -EFAULT;
	if (ret)
		return ret;

	ops.ooblen = length;
	ops.ooboffs = start & (mtd->oobsize - 1);
	ops.datbuf = NULL;
	ops.mode = MTD_OOB_PLACE;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (ops.ooboffs && ops.ooblen > (mtd->oobsize - ops.ooboffs))
		return -EINVAL;

	ops.oobbuf = kmalloc(length, GFP_KERNEL);
	if (!ops.oobbuf)
		return -ENOMEM;

<<<<<<< HEAD
<<<<<<< HEAD
	start &= ~((uint64_t)mtd->writesize - 1);
	ret = mtd_read_oob(mtd, start, &ops);
=======
	start &= ~((uint64_t)mtd->oobsize - 1);
	ret = mtd->read_oob(mtd, start, &ops);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	start &= ~((uint64_t)mtd->oobsize - 1);
	ret = mtd->read_oob(mtd, start, &ops);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (put_user(ops.oobretlen, retp))
		ret = -EFAULT;
	else if (ops.oobretlen && copy_to_user(ptr, ops.oobbuf,
					    ops.oobretlen))
		ret = -EFAULT;

	kfree(ops.oobbuf);
<<<<<<< HEAD
<<<<<<< HEAD

	/*
	 * NAND returns -EBADMSG on ECC errors, but it returns the OOB
	 * data. For our userspace tools it is important to dump areas
	 * with ECC errors!
	 * For kernel internal usage it also might return -EUCLEAN
	 * to signal the caller that a bitflip has occured and has
	 * been corrected by the ECC algorithm.
	 *
	 * Note: currently the standard NAND function, nand_read_oob_std,
	 * does not calculate ECC for the OOB area, so do not rely on
	 * this behavior unless you have replaced it with your own.
	 */
	if (mtd_is_bitflip_or_eccerr(ret))
		return 0;

=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return ret;
}

/*
 * Copies (and truncates, if necessary) data from the larger struct,
 * nand_ecclayout, to the smaller, deprecated layout struct,
<<<<<<< HEAD
<<<<<<< HEAD
 * nand_ecclayout_user. This is necessary only to support the deprecated
=======
 * nand_ecclayout_user. This is necessary only to suppport the deprecated
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 * nand_ecclayout_user. This is necessary only to suppport the deprecated
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * API ioctl ECCGETLAYOUT while allowing all new functionality to use
 * nand_ecclayout flexibly (i.e. the struct may change size in new
 * releases without requiring major rewrites).
 */
static int shrink_ecclayout(const struct nand_ecclayout *from,
		struct nand_ecclayout_user *to)
{
	int i;

	if (!from || !to)
		return -EINVAL;

	memset(to, 0, sizeof(*to));

	to->eccbytes = min((int)from->eccbytes, MTD_MAX_ECCPOS_ENTRIES);
	for (i = 0; i < to->eccbytes; i++)
		to->eccpos[i] = from->eccpos[i];

	for (i = 0; i < MTD_MAX_OOBFREE_ENTRIES; i++) {
		if (from->oobfree[i].length == 0 &&
				from->oobfree[i].offset == 0)
			break;
		to->oobavail += from->oobfree[i].length;
		to->oobfree[i] = from->oobfree[i];
	}

	return 0;
}

<<<<<<< HEAD
<<<<<<< HEAD
static int mtdchar_blkpg_ioctl(struct mtd_info *mtd,
=======
static int mtd_blkpg_ioctl(struct mtd_info *mtd,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static int mtd_blkpg_ioctl(struct mtd_info *mtd,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			   struct blkpg_ioctl_arg __user *arg)
{
	struct blkpg_ioctl_arg a;
	struct blkpg_partition p;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	if (copy_from_user(&a, arg, sizeof(struct blkpg_ioctl_arg)))
		return -EFAULT;

	if (copy_from_user(&p, a.data, sizeof(struct blkpg_partition)))
		return -EFAULT;

	switch (a.op) {
	case BLKPG_ADD_PARTITION:

		/* Only master mtd device must be used to add partitions */
		if (mtd_is_partition(mtd))
			return -EINVAL;

		return mtd_add_partition(mtd, p.devname, p.start, p.length);

	case BLKPG_DEL_PARTITION:

		if (p.pno < 0)
			return -EINVAL;

		return mtd_del_partition(mtd, p.pno);

	default:
		return -EINVAL;
	}
}

<<<<<<< HEAD
<<<<<<< HEAD
static int mtdchar_write_ioctl(struct mtd_info *mtd,
		struct mtd_write_req __user *argp)
{
	struct mtd_write_req req;
	struct mtd_oob_ops ops;
	void __user *usr_data, *usr_oob;
	int ret;

	if (copy_from_user(&req, argp, sizeof(req)) ||
			!access_ok(VERIFY_READ, req.usr_data, req.len) ||
			!access_ok(VERIFY_READ, req.usr_oob, req.ooblen))
		return -EFAULT;
	if (!mtd->_write_oob)
		return -EOPNOTSUPP;

	ops.mode = req.mode;
	ops.len = (size_t)req.len;
	ops.ooblen = (size_t)req.ooblen;
	ops.ooboffs = 0;

	usr_data = (void __user *)(uintptr_t)req.usr_data;
	usr_oob = (void __user *)(uintptr_t)req.usr_oob;

	if (req.usr_data) {
		ops.datbuf = memdup_user(usr_data, ops.len);
		if (IS_ERR(ops.datbuf))
			return PTR_ERR(ops.datbuf);
	} else {
		ops.datbuf = NULL;
	}

	if (req.usr_oob) {
		ops.oobbuf = memdup_user(usr_oob, ops.ooblen);
		if (IS_ERR(ops.oobbuf)) {
			kfree(ops.datbuf);
			return PTR_ERR(ops.oobbuf);
		}
	} else {
		ops.oobbuf = NULL;
	}

	ret = mtd_write_oob(mtd, (loff_t)req.start, &ops);

	kfree(ops.datbuf);
	kfree(ops.oobbuf);

	return ret;
}

static int mtdchar_ioctl(struct file *file, u_int cmd, u_long arg)
=======
static int mtd_ioctl(struct file *file, u_int cmd, u_long arg)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static int mtd_ioctl(struct file *file, u_int cmd, u_long arg)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	struct mtd_file_info *mfi = file->private_data;
	struct mtd_info *mtd = mfi->mtd;
	void __user *argp = (void __user *)arg;
	int ret = 0;
	u_long size;
	struct mtd_info_user info;

<<<<<<< HEAD
<<<<<<< HEAD
	pr_debug("MTD_ioctl\n");
=======
	DEBUG(MTD_DEBUG_LEVEL0, "MTD_ioctl\n");
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	DEBUG(MTD_DEBUG_LEVEL0, "MTD_ioctl\n");
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	size = (cmd & IOCSIZE_MASK) >> IOCSIZE_SHIFT;
	if (cmd & IOC_IN) {
		if (!access_ok(VERIFY_READ, argp, size))
			return -EFAULT;
	}
	if (cmd & IOC_OUT) {
		if (!access_ok(VERIFY_WRITE, argp, size))
			return -EFAULT;
	}

	switch (cmd) {
	case MEMGETREGIONCOUNT:
		if (copy_to_user(argp, &(mtd->numeraseregions), sizeof(int)))
			return -EFAULT;
		break;

	case MEMGETREGIONINFO:
	{
		uint32_t ur_idx;
		struct mtd_erase_region_info *kr;
		struct region_info_user __user *ur = argp;

		if (get_user(ur_idx, &(ur->regionindex)))
			return -EFAULT;

		if (ur_idx >= mtd->numeraseregions)
			return -EINVAL;

		kr = &(mtd->eraseregions[ur_idx]);

		if (put_user(kr->offset, &(ur->offset))
		    || put_user(kr->erasesize, &(ur->erasesize))
		    || put_user(kr->numblocks, &(ur->numblocks)))
			return -EFAULT;

		break;
	}

	case MEMGETINFO:
		memset(&info, 0, sizeof(info));
		info.type	= mtd->type;
		info.flags	= mtd->flags;
		info.size	= mtd->size;
		info.erasesize	= mtd->erasesize;
		info.writesize	= mtd->writesize;
		info.oobsize	= mtd->oobsize;
<<<<<<< HEAD
<<<<<<< HEAD
		/* The below field is obsolete */
		info.padding	= 0;
=======
		/* The below fields are obsolete */
		info.ecctype	= -1;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		/* The below fields are obsolete */
		info.ecctype	= -1;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		if (copy_to_user(argp, &info, sizeof(struct mtd_info_user)))
			return -EFAULT;
		break;

	case MEMERASE:
	case MEMERASE64:
	{
		struct erase_info *erase;

		if(!(file->f_mode & FMODE_WRITE))
			return -EPERM;

		erase=kzalloc(sizeof(struct erase_info),GFP_KERNEL);
		if (!erase)
			ret = -ENOMEM;
		else {
			wait_queue_head_t waitq;
			DECLARE_WAITQUEUE(wait, current);

			init_waitqueue_head(&waitq);

			if (cmd == MEMERASE64) {
				struct erase_info_user64 einfo64;

				if (copy_from_user(&einfo64, argp,
					    sizeof(struct erase_info_user64))) {
					kfree(erase);
					return -EFAULT;
				}
				erase->addr = einfo64.start;
				erase->len = einfo64.length;
			} else {
				struct erase_info_user einfo32;

				if (copy_from_user(&einfo32, argp,
					    sizeof(struct erase_info_user))) {
					kfree(erase);
					return -EFAULT;
				}
				erase->addr = einfo32.start;
				erase->len = einfo32.length;
			}
			erase->mtd = mtd;
			erase->callback = mtdchar_erase_callback;
			erase->priv = (unsigned long)&waitq;

			/*
			  FIXME: Allow INTERRUPTIBLE. Which means
			  not having the wait_queue head on the stack.

			  If the wq_head is on the stack, and we
			  leave because we got interrupted, then the
			  wq_head is no longer there when the
			  callback routine tries to wake us up.
			*/
<<<<<<< HEAD
<<<<<<< HEAD
			ret = mtd_erase(mtd, erase);
=======
			ret = mtd->erase(mtd, erase);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			ret = mtd->erase(mtd, erase);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			if (!ret) {
				set_current_state(TASK_UNINTERRUPTIBLE);
				add_wait_queue(&waitq, &wait);
				if (erase->state != MTD_ERASE_DONE &&
				    erase->state != MTD_ERASE_FAILED)
					schedule();
				remove_wait_queue(&waitq, &wait);
				set_current_state(TASK_RUNNING);

				ret = (erase->state == MTD_ERASE_FAILED)?-EIO:0;
			}
			kfree(erase);
		}
		break;
	}

	case MEMWRITEOOB:
	{
		struct mtd_oob_buf buf;
		struct mtd_oob_buf __user *buf_user = argp;

		/* NOTE: writes return length to buf_user->length */
		if (copy_from_user(&buf, argp, sizeof(buf)))
			ret = -EFAULT;
		else
<<<<<<< HEAD
<<<<<<< HEAD
			ret = mtdchar_writeoob(file, mtd, buf.start, buf.length,
=======
			ret = mtd_do_writeoob(file, mtd, buf.start, buf.length,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			ret = mtd_do_writeoob(file, mtd, buf.start, buf.length,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
				buf.ptr, &buf_user->length);
		break;
	}

	case MEMREADOOB:
	{
		struct mtd_oob_buf buf;
		struct mtd_oob_buf __user *buf_user = argp;

		/* NOTE: writes return length to buf_user->start */
		if (copy_from_user(&buf, argp, sizeof(buf)))
			ret = -EFAULT;
		else
<<<<<<< HEAD
<<<<<<< HEAD
			ret = mtdchar_readoob(file, mtd, buf.start, buf.length,
=======
			ret = mtd_do_readoob(mtd, buf.start, buf.length,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			ret = mtd_do_readoob(mtd, buf.start, buf.length,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
				buf.ptr, &buf_user->start);
		break;
	}

	case MEMWRITEOOB64:
	{
		struct mtd_oob_buf64 buf;
		struct mtd_oob_buf64 __user *buf_user = argp;

		if (copy_from_user(&buf, argp, sizeof(buf)))
			ret = -EFAULT;
		else
<<<<<<< HEAD
<<<<<<< HEAD
			ret = mtdchar_writeoob(file, mtd, buf.start, buf.length,
=======
			ret = mtd_do_writeoob(file, mtd, buf.start, buf.length,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			ret = mtd_do_writeoob(file, mtd, buf.start, buf.length,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
				(void __user *)(uintptr_t)buf.usr_ptr,
				&buf_user->length);
		break;
	}

	case MEMREADOOB64:
	{
		struct mtd_oob_buf64 buf;
		struct mtd_oob_buf64 __user *buf_user = argp;

		if (copy_from_user(&buf, argp, sizeof(buf)))
			ret = -EFAULT;
		else
<<<<<<< HEAD
<<<<<<< HEAD
			ret = mtdchar_readoob(file, mtd, buf.start, buf.length,
=======
			ret = mtd_do_readoob(mtd, buf.start, buf.length,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			ret = mtd_do_readoob(mtd, buf.start, buf.length,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
				(void __user *)(uintptr_t)buf.usr_ptr,
				&buf_user->length);
		break;
	}

<<<<<<< HEAD
<<<<<<< HEAD
	case MEMWRITE:
	{
		ret = mtdchar_write_ioctl(mtd,
		      (struct mtd_write_req __user *)arg);
		break;
	}

=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	case MEMLOCK:
	{
		struct erase_info_user einfo;

		if (copy_from_user(&einfo, argp, sizeof(einfo)))
			return -EFAULT;

<<<<<<< HEAD
<<<<<<< HEAD
		ret = mtd_lock(mtd, einfo.start, einfo.length);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		if (!mtd->lock)
			ret = -EOPNOTSUPP;
		else
			ret = mtd->lock(mtd, einfo.start, einfo.length);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		break;
	}

	case MEMUNLOCK:
	{
		struct erase_info_user einfo;

		if (copy_from_user(&einfo, argp, sizeof(einfo)))
			return -EFAULT;

<<<<<<< HEAD
<<<<<<< HEAD
		ret = mtd_unlock(mtd, einfo.start, einfo.length);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		if (!mtd->unlock)
			ret = -EOPNOTSUPP;
		else
			ret = mtd->unlock(mtd, einfo.start, einfo.length);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		break;
	}

	case MEMISLOCKED:
	{
		struct erase_info_user einfo;

		if (copy_from_user(&einfo, argp, sizeof(einfo)))
			return -EFAULT;

<<<<<<< HEAD
<<<<<<< HEAD
		ret = mtd_is_locked(mtd, einfo.start, einfo.length);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		if (!mtd->is_locked)
			ret = -EOPNOTSUPP;
		else
			ret = mtd->is_locked(mtd, einfo.start, einfo.length);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		break;
	}

	/* Legacy interface */
	case MEMGETOOBSEL:
	{
		struct nand_oobinfo oi;

		if (!mtd->ecclayout)
			return -EOPNOTSUPP;
		if (mtd->ecclayout->eccbytes > ARRAY_SIZE(oi.eccpos))
			return -EINVAL;

		oi.useecc = MTD_NANDECC_AUTOPLACE;
		memcpy(&oi.eccpos, mtd->ecclayout->eccpos, sizeof(oi.eccpos));
		memcpy(&oi.oobfree, mtd->ecclayout->oobfree,
		       sizeof(oi.oobfree));
		oi.eccbytes = mtd->ecclayout->eccbytes;

		if (copy_to_user(argp, &oi, sizeof(struct nand_oobinfo)))
			return -EFAULT;
		break;
	}

	case MEMGETBADBLOCK:
	{
		loff_t offs;

		if (copy_from_user(&offs, argp, sizeof(loff_t)))
			return -EFAULT;
<<<<<<< HEAD
<<<<<<< HEAD
		return mtd_block_isbad(mtd, offs);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		if (!mtd->block_isbad)
			ret = -EOPNOTSUPP;
		else
			return mtd->block_isbad(mtd, offs);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		break;
	}

	case MEMSETBADBLOCK:
	{
		loff_t offs;

		if (copy_from_user(&offs, argp, sizeof(loff_t)))
			return -EFAULT;
<<<<<<< HEAD
<<<<<<< HEAD
		return mtd_block_markbad(mtd, offs);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		if (!mtd->block_markbad)
			ret = -EOPNOTSUPP;
		else
			return mtd->block_markbad(mtd, offs);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		break;
	}

#ifdef CONFIG_HAVE_MTD_OTP
	case OTPSELECT:
	{
		int mode;
		if (copy_from_user(&mode, argp, sizeof(int)))
			return -EFAULT;

<<<<<<< HEAD
<<<<<<< HEAD
		mfi->mode = MTD_FILE_MODE_NORMAL;
=======
		mfi->mode = MTD_MODE_NORMAL;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		mfi->mode = MTD_MODE_NORMAL;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

		ret = otp_select_filemode(mfi, mode);

		file->f_pos = 0;
		break;
	}

	case OTPGETREGIONCOUNT:
	case OTPGETREGIONINFO:
	{
		struct otp_info *buf = kmalloc(4096, GFP_KERNEL);
		if (!buf)
			return -ENOMEM;
<<<<<<< HEAD
<<<<<<< HEAD
		switch (mfi->mode) {
		case MTD_FILE_MODE_OTP_FACTORY:
			ret = mtd_get_fact_prot_info(mtd, buf, 4096);
			break;
		case MTD_FILE_MODE_OTP_USER:
			ret = mtd_get_user_prot_info(mtd, buf, 4096);
			break;
		default:
			ret = -EINVAL;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		ret = -EOPNOTSUPP;
		switch (mfi->mode) {
		case MTD_MODE_OTP_FACTORY:
			if (mtd->get_fact_prot_info)
				ret = mtd->get_fact_prot_info(mtd, buf, 4096);
			break;
		case MTD_MODE_OTP_USER:
			if (mtd->get_user_prot_info)
				ret = mtd->get_user_prot_info(mtd, buf, 4096);
			break;
		default:
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			break;
		}
		if (ret >= 0) {
			if (cmd == OTPGETREGIONCOUNT) {
				int nbr = ret / sizeof(struct otp_info);
				ret = copy_to_user(argp, &nbr, sizeof(int));
			} else
				ret = copy_to_user(argp, buf, ret);
			if (ret)
				ret = -EFAULT;
		}
		kfree(buf);
		break;
	}

	case OTPLOCK:
	{
		struct otp_info oinfo;

<<<<<<< HEAD
<<<<<<< HEAD
		if (mfi->mode != MTD_FILE_MODE_OTP_USER)
			return -EINVAL;
		if (copy_from_user(&oinfo, argp, sizeof(oinfo)))
			return -EFAULT;
		ret = mtd_lock_user_prot_reg(mtd, oinfo.start, oinfo.length);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		if (mfi->mode != MTD_MODE_OTP_USER)
			return -EINVAL;
		if (copy_from_user(&oinfo, argp, sizeof(oinfo)))
			return -EFAULT;
		if (!mtd->lock_user_prot_reg)
			return -EOPNOTSUPP;
		ret = mtd->lock_user_prot_reg(mtd, oinfo.start, oinfo.length);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		break;
	}
#endif

<<<<<<< HEAD
<<<<<<< HEAD
	/* This ioctl is being deprecated - it truncates the ECC layout */
=======
	/* This ioctl is being deprecated - it truncates the ecc layout */
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	/* This ioctl is being deprecated - it truncates the ecc layout */
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	case ECCGETLAYOUT:
	{
		struct nand_ecclayout_user *usrlay;

		if (!mtd->ecclayout)
			return -EOPNOTSUPP;

		usrlay = kmalloc(sizeof(*usrlay), GFP_KERNEL);
		if (!usrlay)
			return -ENOMEM;

		shrink_ecclayout(mtd->ecclayout, usrlay);

		if (copy_to_user(argp, usrlay, sizeof(*usrlay)))
			ret = -EFAULT;
		kfree(usrlay);
		break;
	}

	case ECCGETSTATS:
	{
<<<<<<< HEAD
<<<<<<< HEAD
#ifdef CONFIG_MTD_LAZYECCSTATS
		part_fill_badblockstats(mtd);
#endif
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		if (copy_to_user(argp, &mtd->ecc_stats,
				 sizeof(struct mtd_ecc_stats)))
			return -EFAULT;
		break;
	}

	case MTDFILEMODE:
	{
		mfi->mode = 0;

		switch(arg) {
<<<<<<< HEAD
<<<<<<< HEAD
		case MTD_FILE_MODE_OTP_FACTORY:
		case MTD_FILE_MODE_OTP_USER:
			ret = otp_select_filemode(mfi, arg);
			break;

		case MTD_FILE_MODE_RAW:
			if (!mtd_has_oob(mtd))
				return -EOPNOTSUPP;
			mfi->mode = arg;

		case MTD_FILE_MODE_NORMAL:
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		case MTD_MODE_OTP_FACTORY:
		case MTD_MODE_OTP_USER:
			ret = otp_select_filemode(mfi, arg);
			break;

		case MTD_MODE_RAW:
			if (!mtd->read_oob || !mtd->write_oob)
				return -EOPNOTSUPP;
			mfi->mode = arg;

		case MTD_MODE_NORMAL:
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			break;
		default:
			ret = -EINVAL;
		}
		file->f_pos = 0;
		break;
	}

	case BLKPG:
	{
<<<<<<< HEAD
<<<<<<< HEAD
		ret = mtdchar_blkpg_ioctl(mtd,
=======
		ret = mtd_blkpg_ioctl(mtd,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		ret = mtd_blkpg_ioctl(mtd,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		      (struct blkpg_ioctl_arg __user *)arg);
		break;
	}

	case BLKRRPART:
	{
		/* No reread partition feature. Just return ok */
		ret = 0;
		break;
	}

	default:
		ret = -ENOTTY;
	}

	return ret;
} /* memory_ioctl */

<<<<<<< HEAD
<<<<<<< HEAD
static long mtdchar_unlocked_ioctl(struct file *file, u_int cmd, u_long arg)
=======
static long mtd_unlocked_ioctl(struct file *file, u_int cmd, u_long arg)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static long mtd_unlocked_ioctl(struct file *file, u_int cmd, u_long arg)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	int ret;

	mutex_lock(&mtd_mutex);
<<<<<<< HEAD
<<<<<<< HEAD
	ret = mtdchar_ioctl(file, cmd, arg);
=======
	ret = mtd_ioctl(file, cmd, arg);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	ret = mtd_ioctl(file, cmd, arg);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	mutex_unlock(&mtd_mutex);

	return ret;
}

#ifdef CONFIG_COMPAT

struct mtd_oob_buf32 {
	u_int32_t start;
	u_int32_t length;
	compat_caddr_t ptr;	/* unsigned char* */
};

#define MEMWRITEOOB32		_IOWR('M', 3, struct mtd_oob_buf32)
#define MEMREADOOB32		_IOWR('M', 4, struct mtd_oob_buf32)

<<<<<<< HEAD
<<<<<<< HEAD
static long mtdchar_compat_ioctl(struct file *file, unsigned int cmd,
=======
static long mtd_compat_ioctl(struct file *file, unsigned int cmd,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static long mtd_compat_ioctl(struct file *file, unsigned int cmd,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	unsigned long arg)
{
	struct mtd_file_info *mfi = file->private_data;
	struct mtd_info *mtd = mfi->mtd;
	void __user *argp = compat_ptr(arg);
	int ret = 0;

	mutex_lock(&mtd_mutex);

	switch (cmd) {
	case MEMWRITEOOB32:
	{
		struct mtd_oob_buf32 buf;
		struct mtd_oob_buf32 __user *buf_user = argp;

		if (copy_from_user(&buf, argp, sizeof(buf)))
			ret = -EFAULT;
		else
<<<<<<< HEAD
<<<<<<< HEAD
			ret = mtdchar_writeoob(file, mtd, buf.start,
=======
			ret = mtd_do_writeoob(file, mtd, buf.start,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			ret = mtd_do_writeoob(file, mtd, buf.start,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
				buf.length, compat_ptr(buf.ptr),
				&buf_user->length);
		break;
	}

	case MEMREADOOB32:
	{
		struct mtd_oob_buf32 buf;
		struct mtd_oob_buf32 __user *buf_user = argp;

		/* NOTE: writes return length to buf->start */
		if (copy_from_user(&buf, argp, sizeof(buf)))
			ret = -EFAULT;
		else
<<<<<<< HEAD
<<<<<<< HEAD
			ret = mtdchar_readoob(file, mtd, buf.start,
=======
			ret = mtd_do_readoob(mtd, buf.start,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			ret = mtd_do_readoob(mtd, buf.start,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
				buf.length, compat_ptr(buf.ptr),
				&buf_user->start);
		break;
	}
	default:
<<<<<<< HEAD
<<<<<<< HEAD
		ret = mtdchar_ioctl(file, cmd, (unsigned long)argp);
=======
		ret = mtd_ioctl(file, cmd, (unsigned long)argp);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		ret = mtd_ioctl(file, cmd, (unsigned long)argp);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}

	mutex_unlock(&mtd_mutex);

	return ret;
}

#endif /* CONFIG_COMPAT */

/*
 * try to determine where a shared mapping can be made
 * - only supported for NOMMU at the moment (MMU can't doesn't copy private
 *   mappings)
 */
#ifndef CONFIG_MMU
<<<<<<< HEAD
<<<<<<< HEAD
static unsigned long mtdchar_get_unmapped_area(struct file *file,
=======
static unsigned long mtd_get_unmapped_area(struct file *file,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static unsigned long mtd_get_unmapped_area(struct file *file,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
					   unsigned long addr,
					   unsigned long len,
					   unsigned long pgoff,
					   unsigned long flags)
{
	struct mtd_file_info *mfi = file->private_data;
	struct mtd_info *mtd = mfi->mtd;
<<<<<<< HEAD
<<<<<<< HEAD
	unsigned long offset;
	int ret;

	if (addr != 0)
		return (unsigned long) -EINVAL;

	if (len > mtd->size || pgoff >= (mtd->size >> PAGE_SHIFT))
		return (unsigned long) -EINVAL;

	offset = pgoff << PAGE_SHIFT;
	if (offset > mtd->size - len)
		return (unsigned long) -EINVAL;

	ret = mtd_get_unmapped_area(mtd, len, offset, flags);
	return ret == -EOPNOTSUPP ? -ENOSYS : ret;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (mtd->get_unmapped_area) {
		unsigned long offset;

		if (addr != 0)
			return (unsigned long) -EINVAL;

		if (len > mtd->size || pgoff >= (mtd->size >> PAGE_SHIFT))
			return (unsigned long) -EINVAL;

		offset = pgoff << PAGE_SHIFT;
		if (offset > mtd->size - len)
			return (unsigned long) -EINVAL;

		return mtd->get_unmapped_area(mtd, len, offset, flags);
	}

	/* can't map directly */
	return (unsigned long) -ENOSYS;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}
#endif

static inline unsigned long get_vm_size(struct vm_area_struct *vma)
{
	return vma->vm_end - vma->vm_start;
}

static inline resource_size_t get_vm_offset(struct vm_area_struct *vma)
{
	return (resource_size_t) vma->vm_pgoff << PAGE_SHIFT;
}

/*
 * Set a new vm offset.
 *
 * Verify that the incoming offset really works as a page offset,
 * and that the offset and size fit in a resource_size_t.
 */
static inline int set_vm_offset(struct vm_area_struct *vma, resource_size_t off)
{
	pgoff_t pgoff = off >> PAGE_SHIFT;
	if (off != (resource_size_t) pgoff << PAGE_SHIFT)
		return -EINVAL;
	if (off + get_vm_size(vma) - 1 < off)
		return -EINVAL;
	vma->vm_pgoff = pgoff;
	return 0;
}

/*
 * set up a mapping for shared memory segments
 */
<<<<<<< HEAD
<<<<<<< HEAD
static int mtdchar_mmap(struct file *file, struct vm_area_struct *vma)
=======
static int mtd_mmap(struct file *file, struct vm_area_struct *vma)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static int mtd_mmap(struct file *file, struct vm_area_struct *vma)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
#ifdef CONFIG_MMU
	struct mtd_file_info *mfi = file->private_data;
	struct mtd_info *mtd = mfi->mtd;
	struct map_info *map = mtd->priv;
<<<<<<< HEAD
<<<<<<< HEAD
	resource_size_t start, off;
	unsigned long len, vma_len;

	if (mtd->type == MTD_RAM || mtd->type == MTD_ROM) {
		off = get_vm_offset(vma);
		start = map->phys;
		len = PAGE_ALIGN((start & ~PAGE_MASK) + map->size);
		start &= PAGE_MASK;
		vma_len = get_vm_size(vma);

		/* Overflow in off+len? */
		if (vma_len + off < off)
			return -EINVAL;
		/* Does it fit in the mapping? */
		if (vma_len + off > len)
			return -EINVAL;

		off += start;
		/* Did that overflow? */
		if (off < start)
			return -EINVAL;
		if (set_vm_offset(vma, off) < 0)
			return -EINVAL;
		vma->vm_flags |= VM_IO | VM_RESERVED;

#ifdef pgprot_noncached
		if (file->f_flags & O_DSYNC || off >= __pa(high_memory))
			vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
#endif
		if (io_remap_pfn_range(vma, vma->vm_start, off >> PAGE_SHIFT,
				       vma->vm_end - vma->vm_start,
				       vma->vm_page_prot))
			return -EAGAIN;

		return 0;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

        /* This is broken because it assumes the MTD device is map-based
	   and that mtd->priv is a valid struct map_info.  It should be
	   replaced with something that uses the mtd_get_unmapped_area()
	   operation properly. */
	if (0 /*mtd->type == MTD_RAM || mtd->type == MTD_ROM*/) {
#ifdef pgprot_noncached
		if (file->f_flags & O_DSYNC || map->phys >= __pa(high_memory))
			vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
#endif
		return vm_iomap_memory(vma, map->phys, map->size);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}
	return -ENOSYS;
#else
	return vma->vm_flags & VM_SHARED ? 0 : -ENOSYS;
#endif
}

static const struct file_operations mtd_fops = {
	.owner		= THIS_MODULE,
<<<<<<< HEAD
<<<<<<< HEAD
	.llseek		= mtdchar_lseek,
	.read		= mtdchar_read,
	.write		= mtdchar_write,
	.unlocked_ioctl	= mtdchar_unlocked_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl	= mtdchar_compat_ioctl,
#endif
	.open		= mtdchar_open,
	.release	= mtdchar_close,
	.mmap		= mtdchar_mmap,
#ifndef CONFIG_MMU
	.get_unmapped_area = mtdchar_get_unmapped_area,
#endif
};

static const struct super_operations mtd_ops = {
	.drop_inode = generic_delete_inode,
	.statfs = simple_statfs,
};

static struct dentry *mtd_inodefs_mount(struct file_system_type *fs_type,
				int flags, const char *dev_name, void *data)
{
	return mount_pseudo(fs_type, "mtd_inode:", &mtd_ops, NULL, MTD_INODE_FS_MAGIC);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	.llseek		= mtd_lseek,
	.read		= mtd_read,
	.write		= mtd_write,
	.unlocked_ioctl	= mtd_unlocked_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl	= mtd_compat_ioctl,
#endif
	.open		= mtd_open,
	.release	= mtd_close,
	.mmap		= mtd_mmap,
#ifndef CONFIG_MMU
	.get_unmapped_area = mtd_get_unmapped_area,
#endif
};

static struct dentry *mtd_inodefs_mount(struct file_system_type *fs_type,
				int flags, const char *dev_name, void *data)
{
	return mount_pseudo(fs_type, "mtd_inode:", NULL, NULL, MTD_INODE_FS_MAGIC);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static struct file_system_type mtd_inodefs_type = {
       .name = "mtd_inodefs",
       .mount = mtd_inodefs_mount,
       .kill_sb = kill_anon_super,
};

<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static void mtdchar_notify_add(struct mtd_info *mtd)
{
}

static void mtdchar_notify_remove(struct mtd_info *mtd)
{
	struct inode *mtd_ino = ilookup(mtd_inode_mnt->mnt_sb, mtd->index);

	if (mtd_ino) {
		/* Destroy the inode if it exists */
		mtd_ino->i_nlink = 0;
		iput(mtd_ino);
	}
}

static struct mtd_notifier mtdchar_notifier = {
	.add = mtdchar_notify_add,
	.remove = mtdchar_notify_remove,
};

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static int __init init_mtdchar(void)
{
	int ret;

	ret = __register_chrdev(MTD_CHAR_MAJOR, 0, 1 << MINORBITS,
				   "mtd", &mtd_fops);
	if (ret < 0) {
		pr_notice("Can't allocate major number %d for "
				"Memory Technology Devices.\n", MTD_CHAR_MAJOR);
		return ret;
	}

	ret = register_filesystem(&mtd_inodefs_type);
	if (ret) {
		pr_notice("Can't register mtd_inodefs filesystem: %d\n", ret);
		goto err_unregister_chdev;
	}
<<<<<<< HEAD
<<<<<<< HEAD
	return ret;

=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	mtd_inode_mnt = kern_mount(&mtd_inodefs_type);
	if (IS_ERR(mtd_inode_mnt)) {
		ret = PTR_ERR(mtd_inode_mnt);
		pr_notice("Error mounting mtd_inodefs filesystem: %d\n", ret);
		goto err_unregister_filesystem;
	}
	register_mtd_user(&mtdchar_notifier);

	return ret;

err_unregister_filesystem:
	unregister_filesystem(&mtd_inodefs_type);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
err_unregister_chdev:
	__unregister_chrdev(MTD_CHAR_MAJOR, 0, 1 << MINORBITS, "mtd");
	return ret;
}

static void __exit cleanup_mtdchar(void)
{
<<<<<<< HEAD
<<<<<<< HEAD
=======
	unregister_mtd_user(&mtdchar_notifier);
	mntput(mtd_inode_mnt);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	unregister_mtd_user(&mtdchar_notifier);
	mntput(mtd_inode_mnt);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	unregister_filesystem(&mtd_inodefs_type);
	__unregister_chrdev(MTD_CHAR_MAJOR, 0, 1 << MINORBITS, "mtd");
}

module_init(init_mtdchar);
module_exit(cleanup_mtdchar);

MODULE_ALIAS_CHARDEV_MAJOR(MTD_CHAR_MAJOR);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("David Woodhouse <dwmw2@infradead.org>");
MODULE_DESCRIPTION("Direct character-device access to MTD devices");
MODULE_ALIAS_CHARDEV_MAJOR(MTD_CHAR_MAJOR);
