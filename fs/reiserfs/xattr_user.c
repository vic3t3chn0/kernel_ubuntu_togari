<<<<<<< HEAD
#include "reiserfs.h"
=======
<<<<<<< HEAD
#include "reiserfs.h"
=======
#include <linux/reiserfs_fs.h>
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/pagemap.h>
#include <linux/xattr.h>
<<<<<<< HEAD
#include "xattr.h"
=======
<<<<<<< HEAD
#include "xattr.h"
=======
#include <linux/reiserfs_xattr.h>
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <asm/uaccess.h>

static int
user_get(struct dentry *dentry, const char *name, void *buffer, size_t size,
	 int handler_flags)
{

	if (strlen(name) < sizeof(XATTR_USER_PREFIX))
		return -EINVAL;
	if (!reiserfs_xattrs_user(dentry->d_sb))
		return -EOPNOTSUPP;
	return reiserfs_xattr_get(dentry->d_inode, name, buffer, size);
}

static int
user_set(struct dentry *dentry, const char *name, const void *buffer,
	 size_t size, int flags, int handler_flags)
{
	if (strlen(name) < sizeof(XATTR_USER_PREFIX))
		return -EINVAL;

	if (!reiserfs_xattrs_user(dentry->d_sb))
		return -EOPNOTSUPP;
	return reiserfs_xattr_set(dentry->d_inode, name, buffer, size, flags);
}

static size_t user_list(struct dentry *dentry, char *list, size_t list_size,
			const char *name, size_t name_len, int handler_flags)
{
	const size_t len = name_len + 1;

	if (!reiserfs_xattrs_user(dentry->d_sb))
		return 0;
	if (list && len <= list_size) {
		memcpy(list, name, name_len);
		list[name_len] = '\0';
	}
	return len;
}

const struct xattr_handler reiserfs_xattr_user_handler = {
	.prefix = XATTR_USER_PREFIX,
	.get = user_get,
	.set = user_set,
	.list = user_list,
};
