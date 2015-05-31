#include <linux/ceph/ceph_debug.h>

#include "super.h"
#include "mds_client.h"

#include <linux/ceph/decode.h>

#include <linux/xattr.h>
#include <linux/slab.h>

<<<<<<< HEAD
#define XATTR_CEPH_PREFIX "ceph."
#define XATTR_CEPH_PREFIX_LEN (sizeof (XATTR_CEPH_PREFIX) - 1)

static bool ceph_is_valid_xattr(const char *name)
{
	return !strncmp(name, XATTR_CEPH_PREFIX, XATTR_CEPH_PREFIX_LEN) ||
=======
static bool ceph_is_valid_xattr(const char *name)
{
	return !strncmp(name, "ceph.", 5) ||
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	       !strncmp(name, XATTR_SECURITY_PREFIX,
			XATTR_SECURITY_PREFIX_LEN) ||
	       !strncmp(name, XATTR_TRUSTED_PREFIX, XATTR_TRUSTED_PREFIX_LEN) ||
	       !strncmp(name, XATTR_USER_PREFIX, XATTR_USER_PREFIX_LEN);
}

/*
 * These define virtual xattrs exposing the recursive directory
 * statistics and layout metadata.
 */
<<<<<<< HEAD
struct ceph_vxattr {
	char *name;
	size_t name_size;	/* strlen(name) + 1 (for '\0') */
	size_t (*getxattr_cb)(struct ceph_inode_info *ci, char *val,
			      size_t size);
	bool readonly;
=======
struct ceph_vxattr_cb {
	bool readonly;
	char *name;
	size_t (*getxattr_cb)(struct ceph_inode_info *ci, char *val,
			      size_t size);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
};

/* directories */

<<<<<<< HEAD
static size_t ceph_vxattrcb_dir_entries(struct ceph_inode_info *ci, char *val,
=======
static size_t ceph_vxattrcb_entries(struct ceph_inode_info *ci, char *val,
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
					size_t size)
{
	return snprintf(val, size, "%lld", ci->i_files + ci->i_subdirs);
}

<<<<<<< HEAD
static size_t ceph_vxattrcb_dir_files(struct ceph_inode_info *ci, char *val,
=======
static size_t ceph_vxattrcb_files(struct ceph_inode_info *ci, char *val,
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
				      size_t size)
{
	return snprintf(val, size, "%lld", ci->i_files);
}

<<<<<<< HEAD
static size_t ceph_vxattrcb_dir_subdirs(struct ceph_inode_info *ci, char *val,
=======
static size_t ceph_vxattrcb_subdirs(struct ceph_inode_info *ci, char *val,
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
					size_t size)
{
	return snprintf(val, size, "%lld", ci->i_subdirs);
}

<<<<<<< HEAD
static size_t ceph_vxattrcb_dir_rentries(struct ceph_inode_info *ci, char *val,
=======
static size_t ceph_vxattrcb_rentries(struct ceph_inode_info *ci, char *val,
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
					 size_t size)
{
	return snprintf(val, size, "%lld", ci->i_rfiles + ci->i_rsubdirs);
}

<<<<<<< HEAD
static size_t ceph_vxattrcb_dir_rfiles(struct ceph_inode_info *ci, char *val,
=======
static size_t ceph_vxattrcb_rfiles(struct ceph_inode_info *ci, char *val,
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
				       size_t size)
{
	return snprintf(val, size, "%lld", ci->i_rfiles);
}

<<<<<<< HEAD
static size_t ceph_vxattrcb_dir_rsubdirs(struct ceph_inode_info *ci, char *val,
=======
static size_t ceph_vxattrcb_rsubdirs(struct ceph_inode_info *ci, char *val,
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
					 size_t size)
{
	return snprintf(val, size, "%lld", ci->i_rsubdirs);
}

<<<<<<< HEAD
static size_t ceph_vxattrcb_dir_rbytes(struct ceph_inode_info *ci, char *val,
=======
static size_t ceph_vxattrcb_rbytes(struct ceph_inode_info *ci, char *val,
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
				       size_t size)
{
	return snprintf(val, size, "%lld", ci->i_rbytes);
}

<<<<<<< HEAD
static size_t ceph_vxattrcb_dir_rctime(struct ceph_inode_info *ci, char *val,
				       size_t size)
{
	return snprintf(val, size, "%ld.09%ld", (long)ci->i_rctime.tv_sec,
			(long)ci->i_rctime.tv_nsec);
}

#define CEPH_XATTR_NAME(_type, _name)	XATTR_CEPH_PREFIX #_type "." #_name

#define XATTR_NAME_CEPH(_type, _name) \
		{ \
			.name = CEPH_XATTR_NAME(_type, _name), \
			.name_size = sizeof (CEPH_XATTR_NAME(_type, _name)), \
			.getxattr_cb = ceph_vxattrcb_ ## _type ## _ ## _name, \
			.readonly = true, \
		}

static struct ceph_vxattr ceph_dir_vxattrs[] = {
	XATTR_NAME_CEPH(dir, entries),
	XATTR_NAME_CEPH(dir, files),
	XATTR_NAME_CEPH(dir, subdirs),
	XATTR_NAME_CEPH(dir, rentries),
	XATTR_NAME_CEPH(dir, rfiles),
	XATTR_NAME_CEPH(dir, rsubdirs),
	XATTR_NAME_CEPH(dir, rbytes),
	XATTR_NAME_CEPH(dir, rctime),
	{ 0 }	/* Required table terminator */
};
static size_t ceph_dir_vxattrs_name_size;	/* total size of all names */

/* files */

static size_t ceph_vxattrcb_file_layout(struct ceph_inode_info *ci, char *val,
=======
static size_t ceph_vxattrcb_rctime(struct ceph_inode_info *ci, char *val,
				       size_t size)
{
	return snprintf(val, size, "%ld.%ld", (long)ci->i_rctime.tv_sec,
			(long)ci->i_rctime.tv_nsec);
}

static struct ceph_vxattr_cb ceph_dir_vxattrs[] = {
	{ true, "ceph.dir.entries", ceph_vxattrcb_entries},
	{ true, "ceph.dir.files", ceph_vxattrcb_files},
	{ true, "ceph.dir.subdirs", ceph_vxattrcb_subdirs},
	{ true, "ceph.dir.rentries", ceph_vxattrcb_rentries},
	{ true, "ceph.dir.rfiles", ceph_vxattrcb_rfiles},
	{ true, "ceph.dir.rsubdirs", ceph_vxattrcb_rsubdirs},
	{ true, "ceph.dir.rbytes", ceph_vxattrcb_rbytes},
	{ true, "ceph.dir.rctime", ceph_vxattrcb_rctime},
	{ true, NULL, NULL }
};

/* files */

static size_t ceph_vxattrcb_layout(struct ceph_inode_info *ci, char *val,
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
				   size_t size)
{
	int ret;

	ret = snprintf(val, size,
		"chunk_bytes=%lld\nstripe_count=%lld\nobject_size=%lld\n",
		(unsigned long long)ceph_file_layout_su(ci->i_layout),
		(unsigned long long)ceph_file_layout_stripe_count(ci->i_layout),
		(unsigned long long)ceph_file_layout_object_size(ci->i_layout));
<<<<<<< HEAD

	if (ceph_file_layout_pg_preferred(ci->i_layout) >= 0) {
		val += ret;
		size -= ret;
		ret += snprintf(val, size, "preferred_osd=%lld\n",
			    (unsigned long long)ceph_file_layout_pg_preferred(
				    ci->i_layout));
	}

	return ret;
}

static struct ceph_vxattr ceph_file_vxattrs[] = {
	XATTR_NAME_CEPH(file, layout),
	/* The following extended attribute name is deprecated */
	{
		.name = XATTR_CEPH_PREFIX "layout",
		.name_size = sizeof (XATTR_CEPH_PREFIX "layout"),
		.getxattr_cb = ceph_vxattrcb_file_layout,
		.readonly = true,
	},
	{ 0 }	/* Required table terminator */
};
static size_t ceph_file_vxattrs_name_size;	/* total size of all names */

static struct ceph_vxattr *ceph_inode_vxattrs(struct inode *inode)
=======
	if (ceph_file_layout_pg_preferred(ci->i_layout))
		ret += snprintf(val + ret, size, "preferred_osd=%lld\n",
			    (unsigned long long)ceph_file_layout_pg_preferred(
				    ci->i_layout));
	return ret;
}

static struct ceph_vxattr_cb ceph_file_vxattrs[] = {
	{ true, "ceph.layout", ceph_vxattrcb_layout},
	{ NULL, NULL }
};

static struct ceph_vxattr_cb *ceph_inode_vxattrs(struct inode *inode)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
{
	if (S_ISDIR(inode->i_mode))
		return ceph_dir_vxattrs;
	else if (S_ISREG(inode->i_mode))
		return ceph_file_vxattrs;
	return NULL;
}

<<<<<<< HEAD
static size_t ceph_vxattrs_name_size(struct ceph_vxattr *vxattrs)
{
	if (vxattrs == ceph_dir_vxattrs)
		return ceph_dir_vxattrs_name_size;
	if (vxattrs == ceph_file_vxattrs)
		return ceph_file_vxattrs_name_size;
	BUG();

	return 0;
}

/*
 * Compute the aggregate size (including terminating '\0') of all
 * virtual extended attribute names in the given vxattr table.
 */
static size_t __init vxattrs_name_size(struct ceph_vxattr *vxattrs)
{
	struct ceph_vxattr *vxattr;
	size_t size = 0;

	for (vxattr = vxattrs; vxattr->name; vxattr++)
		size += vxattr->name_size;

	return size;
}

/* Routines called at initialization and exit time */

void __init ceph_xattr_init(void)
{
	ceph_dir_vxattrs_name_size = vxattrs_name_size(ceph_dir_vxattrs);
	ceph_file_vxattrs_name_size = vxattrs_name_size(ceph_file_vxattrs);
}

void ceph_xattr_exit(void)
{
	ceph_dir_vxattrs_name_size = 0;
	ceph_file_vxattrs_name_size = 0;
}

static struct ceph_vxattr *ceph_match_vxattr(struct inode *inode,
						const char *name)
{
	struct ceph_vxattr *vxattr = ceph_inode_vxattrs(inode);

	if (vxattr) {
		while (vxattr->name) {
			if (!strcmp(vxattr->name, name))
				return vxattr;
			vxattr++;
		}
	}

=======
static struct ceph_vxattr_cb *ceph_match_vxattr(struct ceph_vxattr_cb *vxattr,
						const char *name)
{
	do {
		if (strcmp(vxattr->name, name) == 0)
			return vxattr;
		vxattr++;
	} while (vxattr->name);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	return NULL;
}

static int __set_xattr(struct ceph_inode_info *ci,
			   const char *name, int name_len,
			   const char *val, int val_len,
			   int dirty,
			   int should_free_name, int should_free_val,
			   struct ceph_inode_xattr **newxattr)
{
	struct rb_node **p;
	struct rb_node *parent = NULL;
	struct ceph_inode_xattr *xattr = NULL;
	int c;
	int new = 0;

	p = &ci->i_xattrs.index.rb_node;
	while (*p) {
		parent = *p;
		xattr = rb_entry(parent, struct ceph_inode_xattr, node);
		c = strncmp(name, xattr->name, min(name_len, xattr->name_len));
		if (c < 0)
			p = &(*p)->rb_left;
		else if (c > 0)
			p = &(*p)->rb_right;
		else {
			if (name_len == xattr->name_len)
				break;
			else if (name_len < xattr->name_len)
				p = &(*p)->rb_left;
			else
				p = &(*p)->rb_right;
		}
		xattr = NULL;
	}

	if (!xattr) {
		new = 1;
		xattr = *newxattr;
		xattr->name = name;
		xattr->name_len = name_len;
		xattr->should_free_name = should_free_name;

		ci->i_xattrs.count++;
		dout("__set_xattr count=%d\n", ci->i_xattrs.count);
	} else {
		kfree(*newxattr);
		*newxattr = NULL;
		if (xattr->should_free_val)
			kfree((void *)xattr->val);

		if (should_free_name) {
			kfree((void *)name);
			name = xattr->name;
		}
		ci->i_xattrs.names_size -= xattr->name_len;
		ci->i_xattrs.vals_size -= xattr->val_len;
	}
	ci->i_xattrs.names_size += name_len;
	ci->i_xattrs.vals_size += val_len;
	if (val)
		xattr->val = val;
	else
		xattr->val = "";

	xattr->val_len = val_len;
	xattr->dirty = dirty;
	xattr->should_free_val = (val && should_free_val);

	if (new) {
		rb_link_node(&xattr->node, parent, p);
		rb_insert_color(&xattr->node, &ci->i_xattrs.index);
		dout("__set_xattr_val p=%p\n", p);
	}

	dout("__set_xattr_val added %llx.%llx xattr %p %s=%.*s\n",
	     ceph_vinop(&ci->vfs_inode), xattr, name, val_len, val);

	return 0;
}

static struct ceph_inode_xattr *__get_xattr(struct ceph_inode_info *ci,
			   const char *name)
{
	struct rb_node **p;
	struct rb_node *parent = NULL;
	struct ceph_inode_xattr *xattr = NULL;
	int name_len = strlen(name);
	int c;

	p = &ci->i_xattrs.index.rb_node;
	while (*p) {
		parent = *p;
		xattr = rb_entry(parent, struct ceph_inode_xattr, node);
		c = strncmp(name, xattr->name, xattr->name_len);
		if (c == 0 && name_len > xattr->name_len)
			c = 1;
		if (c < 0)
			p = &(*p)->rb_left;
		else if (c > 0)
			p = &(*p)->rb_right;
		else {
			dout("__get_xattr %s: found %.*s\n", name,
			     xattr->val_len, xattr->val);
			return xattr;
		}
	}

	dout("__get_xattr %s: not found\n", name);

	return NULL;
}

static void __free_xattr(struct ceph_inode_xattr *xattr)
{
	BUG_ON(!xattr);

	if (xattr->should_free_name)
		kfree((void *)xattr->name);
	if (xattr->should_free_val)
		kfree((void *)xattr->val);

	kfree(xattr);
}

static int __remove_xattr(struct ceph_inode_info *ci,
			  struct ceph_inode_xattr *xattr)
{
	if (!xattr)
		return -EOPNOTSUPP;

	rb_erase(&xattr->node, &ci->i_xattrs.index);

	if (xattr->should_free_name)
		kfree((void *)xattr->name);
	if (xattr->should_free_val)
		kfree((void *)xattr->val);

	ci->i_xattrs.names_size -= xattr->name_len;
	ci->i_xattrs.vals_size -= xattr->val_len;
	ci->i_xattrs.count--;
	kfree(xattr);

	return 0;
}

static int __remove_xattr_by_name(struct ceph_inode_info *ci,
			   const char *name)
{
	struct rb_node **p;
	struct ceph_inode_xattr *xattr;
	int err;

	p = &ci->i_xattrs.index.rb_node;
	xattr = __get_xattr(ci, name);
	err = __remove_xattr(ci, xattr);
	return err;
}

static char *__copy_xattr_names(struct ceph_inode_info *ci,
				char *dest)
{
	struct rb_node *p;
	struct ceph_inode_xattr *xattr = NULL;

	p = rb_first(&ci->i_xattrs.index);
	dout("__copy_xattr_names count=%d\n", ci->i_xattrs.count);

	while (p) {
		xattr = rb_entry(p, struct ceph_inode_xattr, node);
		memcpy(dest, xattr->name, xattr->name_len);
		dest[xattr->name_len] = '\0';

		dout("dest=%s %p (%s) (%d/%d)\n", dest, xattr, xattr->name,
		     xattr->name_len, ci->i_xattrs.names_size);

		dest += xattr->name_len + 1;
		p = rb_next(p);
	}

	return dest;
}

void __ceph_destroy_xattrs(struct ceph_inode_info *ci)
{
	struct rb_node *p, *tmp;
	struct ceph_inode_xattr *xattr = NULL;

	p = rb_first(&ci->i_xattrs.index);

	dout("__ceph_destroy_xattrs p=%p\n", p);

	while (p) {
		xattr = rb_entry(p, struct ceph_inode_xattr, node);
		tmp = p;
		p = rb_next(tmp);
		dout("__ceph_destroy_xattrs next p=%p (%.*s)\n", p,
		     xattr->name_len, xattr->name);
		rb_erase(tmp, &ci->i_xattrs.index);

		__free_xattr(xattr);
	}

	ci->i_xattrs.names_size = 0;
	ci->i_xattrs.vals_size = 0;
	ci->i_xattrs.index_version = 0;
	ci->i_xattrs.count = 0;
	ci->i_xattrs.index = RB_ROOT;
}

static int __build_xattrs(struct inode *inode)
<<<<<<< HEAD
	__releases(ci->i_ceph_lock)
	__acquires(ci->i_ceph_lock)
=======
	__releases(inode->i_lock)
	__acquires(inode->i_lock)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
{
	u32 namelen;
	u32 numattr = 0;
	void *p, *end;
	u32 len;
	const char *name, *val;
	struct ceph_inode_info *ci = ceph_inode(inode);
	int xattr_version;
	struct ceph_inode_xattr **xattrs = NULL;
	int err = 0;
	int i;

	dout("__build_xattrs() len=%d\n",
	     ci->i_xattrs.blob ? (int)ci->i_xattrs.blob->vec.iov_len : 0);

	if (ci->i_xattrs.index_version >= ci->i_xattrs.version)
		return 0; /* already built */

	__ceph_destroy_xattrs(ci);

start:
	/* updated internal xattr rb tree */
	if (ci->i_xattrs.blob && ci->i_xattrs.blob->vec.iov_len > 4) {
		p = ci->i_xattrs.blob->vec.iov_base;
		end = p + ci->i_xattrs.blob->vec.iov_len;
		ceph_decode_32_safe(&p, end, numattr, bad);
		xattr_version = ci->i_xattrs.version;
<<<<<<< HEAD
		spin_unlock(&ci->i_ceph_lock);
=======
		spin_unlock(&inode->i_lock);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

		xattrs = kcalloc(numattr, sizeof(struct ceph_xattr *),
				 GFP_NOFS);
		err = -ENOMEM;
		if (!xattrs)
			goto bad_lock;
		memset(xattrs, 0, numattr*sizeof(struct ceph_xattr *));
		for (i = 0; i < numattr; i++) {
			xattrs[i] = kmalloc(sizeof(struct ceph_inode_xattr),
					    GFP_NOFS);
			if (!xattrs[i])
				goto bad_lock;
		}

<<<<<<< HEAD
		spin_lock(&ci->i_ceph_lock);
=======
		spin_lock(&inode->i_lock);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		if (ci->i_xattrs.version != xattr_version) {
			/* lost a race, retry */
			for (i = 0; i < numattr; i++)
				kfree(xattrs[i]);
			kfree(xattrs);
			goto start;
		}
		err = -EIO;
		while (numattr--) {
			ceph_decode_32_safe(&p, end, len, bad);
			namelen = len;
			name = p;
			p += len;
			ceph_decode_32_safe(&p, end, len, bad);
			val = p;
			p += len;

			err = __set_xattr(ci, name, namelen, val, len,
					  0, 0, 0, &xattrs[numattr]);

			if (err < 0)
				goto bad;
		}
		kfree(xattrs);
	}
	ci->i_xattrs.index_version = ci->i_xattrs.version;
	ci->i_xattrs.dirty = false;

	return err;
bad_lock:
<<<<<<< HEAD
	spin_lock(&ci->i_ceph_lock);
=======
	spin_lock(&inode->i_lock);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
bad:
	if (xattrs) {
		for (i = 0; i < numattr; i++)
			kfree(xattrs[i]);
		kfree(xattrs);
	}
	ci->i_xattrs.names_size = 0;
	return err;
}

static int __get_required_blob_size(struct ceph_inode_info *ci, int name_size,
				    int val_size)
{
	/*
	 * 4 bytes for the length, and additional 4 bytes per each xattr name,
	 * 4 bytes per each value
	 */
	int size = 4 + ci->i_xattrs.count*(4 + 4) +
			     ci->i_xattrs.names_size +
			     ci->i_xattrs.vals_size;
	dout("__get_required_blob_size c=%d names.size=%d vals.size=%d\n",
	     ci->i_xattrs.count, ci->i_xattrs.names_size,
	     ci->i_xattrs.vals_size);

	if (name_size)
		size += 4 + 4 + name_size + val_size;

	return size;
}

/*
 * If there are dirty xattrs, reencode xattrs into the prealloc_blob
 * and swap into place.
 */
void __ceph_build_xattrs_blob(struct ceph_inode_info *ci)
{
	struct rb_node *p;
	struct ceph_inode_xattr *xattr = NULL;
	void *dest;

	dout("__build_xattrs_blob %p\n", &ci->vfs_inode);
	if (ci->i_xattrs.dirty) {
		int need = __get_required_blob_size(ci, 0, 0);

		BUG_ON(need > ci->i_xattrs.prealloc_blob->alloc_len);

		p = rb_first(&ci->i_xattrs.index);
		dest = ci->i_xattrs.prealloc_blob->vec.iov_base;

		ceph_encode_32(&dest, ci->i_xattrs.count);
		while (p) {
			xattr = rb_entry(p, struct ceph_inode_xattr, node);

			ceph_encode_32(&dest, xattr->name_len);
			memcpy(dest, xattr->name, xattr->name_len);
			dest += xattr->name_len;
			ceph_encode_32(&dest, xattr->val_len);
			memcpy(dest, xattr->val, xattr->val_len);
			dest += xattr->val_len;

			p = rb_next(p);
		}

		/* adjust buffer len; it may be larger than we need */
		ci->i_xattrs.prealloc_blob->vec.iov_len =
			dest - ci->i_xattrs.prealloc_blob->vec.iov_base;

		if (ci->i_xattrs.blob)
			ceph_buffer_put(ci->i_xattrs.blob);
		ci->i_xattrs.blob = ci->i_xattrs.prealloc_blob;
		ci->i_xattrs.prealloc_blob = NULL;
		ci->i_xattrs.dirty = false;
		ci->i_xattrs.version++;
	}
}

ssize_t ceph_getxattr(struct dentry *dentry, const char *name, void *value,
		      size_t size)
{
	struct inode *inode = dentry->d_inode;
	struct ceph_inode_info *ci = ceph_inode(inode);
<<<<<<< HEAD
	int err;
	struct ceph_inode_xattr *xattr;
	struct ceph_vxattr *vxattr = NULL;
=======
	struct ceph_vxattr_cb *vxattrs = ceph_inode_vxattrs(inode);
	int err;
	struct ceph_inode_xattr *xattr;
	struct ceph_vxattr_cb *vxattr = NULL;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

	if (!ceph_is_valid_xattr(name))
		return -ENODATA;

	/* let's see if a virtual xattr was requested */
<<<<<<< HEAD
	vxattr = ceph_match_vxattr(inode, name);

	spin_lock(&ci->i_ceph_lock);
=======
	if (vxattrs)
		vxattr = ceph_match_vxattr(vxattrs, name);

	spin_lock(&inode->i_lock);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	dout("getxattr %p ver=%lld index_ver=%lld\n", inode,
	     ci->i_xattrs.version, ci->i_xattrs.index_version);

	if (__ceph_caps_issued_mask(ci, CEPH_CAP_XATTR_SHARED, 1) &&
	    (ci->i_xattrs.index_version >= ci->i_xattrs.version)) {
		goto get_xattr;
	} else {
<<<<<<< HEAD
		spin_unlock(&ci->i_ceph_lock);
=======
		spin_unlock(&inode->i_lock);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		/* get xattrs from mds (if we don't already have them) */
		err = ceph_do_getattr(inode, CEPH_STAT_CAP_XATTR);
		if (err)
			return err;
	}

<<<<<<< HEAD
	spin_lock(&ci->i_ceph_lock);
=======
	spin_lock(&inode->i_lock);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

	if (vxattr && vxattr->readonly) {
		err = vxattr->getxattr_cb(ci, value, size);
		goto out;
	}

	err = __build_xattrs(inode);
	if (err < 0)
		goto out;

get_xattr:
	err = -ENODATA;  /* == ENOATTR */
	xattr = __get_xattr(ci, name);
	if (!xattr) {
		if (vxattr)
			err = vxattr->getxattr_cb(ci, value, size);
		goto out;
	}

	err = -ERANGE;
	if (size && size < xattr->val_len)
		goto out;

	err = xattr->val_len;
	if (size == 0)
		goto out;

	memcpy(value, xattr->val, xattr->val_len);

out:
<<<<<<< HEAD
	spin_unlock(&ci->i_ceph_lock);
=======
	spin_unlock(&inode->i_lock);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	return err;
}

ssize_t ceph_listxattr(struct dentry *dentry, char *names, size_t size)
{
	struct inode *inode = dentry->d_inode;
	struct ceph_inode_info *ci = ceph_inode(inode);
<<<<<<< HEAD
	struct ceph_vxattr *vxattrs = ceph_inode_vxattrs(inode);
=======
	struct ceph_vxattr_cb *vxattrs = ceph_inode_vxattrs(inode);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	u32 vir_namelen = 0;
	u32 namelen;
	int err;
	u32 len;
	int i;

<<<<<<< HEAD
	spin_lock(&ci->i_ceph_lock);
=======
	spin_lock(&inode->i_lock);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	dout("listxattr %p ver=%lld index_ver=%lld\n", inode,
	     ci->i_xattrs.version, ci->i_xattrs.index_version);

	if (__ceph_caps_issued_mask(ci, CEPH_CAP_XATTR_SHARED, 1) &&
	    (ci->i_xattrs.index_version >= ci->i_xattrs.version)) {
		goto list_xattr;
	} else {
<<<<<<< HEAD
		spin_unlock(&ci->i_ceph_lock);
=======
		spin_unlock(&inode->i_lock);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		err = ceph_do_getattr(inode, CEPH_STAT_CAP_XATTR);
		if (err)
			return err;
	}

<<<<<<< HEAD
	spin_lock(&ci->i_ceph_lock);
=======
	spin_lock(&inode->i_lock);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

	err = __build_xattrs(inode);
	if (err < 0)
		goto out;

list_xattr:
<<<<<<< HEAD
	/*
	 * Start with virtual dir xattr names (if any) (including
	 * terminating '\0' characters for each).
	 */
	vir_namelen = ceph_vxattrs_name_size(vxattrs);

=======
	vir_namelen = 0;
	/* include virtual dir xattrs */
	if (vxattrs)
		for (i = 0; vxattrs[i].name; i++)
			vir_namelen += strlen(vxattrs[i].name) + 1;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	/* adding 1 byte per each variable due to the null termination */
	namelen = vir_namelen + ci->i_xattrs.names_size + ci->i_xattrs.count;
	err = -ERANGE;
	if (size && namelen > size)
		goto out;

	err = namelen;
	if (size == 0)
		goto out;

	names = __copy_xattr_names(ci, names);

	/* virtual xattr names, too */
	if (vxattrs)
		for (i = 0; vxattrs[i].name; i++) {
			len = sprintf(names, "%s", vxattrs[i].name);
			names += len + 1;
		}

out:
<<<<<<< HEAD
	spin_unlock(&ci->i_ceph_lock);
=======
	spin_unlock(&inode->i_lock);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	return err;
}

static int ceph_sync_setxattr(struct dentry *dentry, const char *name,
			      const char *value, size_t size, int flags)
{
	struct ceph_fs_client *fsc = ceph_sb_to_client(dentry->d_sb);
	struct inode *inode = dentry->d_inode;
	struct ceph_inode_info *ci = ceph_inode(inode);
<<<<<<< HEAD
	struct inode *parent_inode;
=======
	struct inode *parent_inode = dentry->d_parent->d_inode;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	struct ceph_mds_request *req;
	struct ceph_mds_client *mdsc = fsc->mdsc;
	int err;
	int i, nr_pages;
	struct page **pages = NULL;
	void *kaddr;

	/* copy value into some pages */
	nr_pages = calc_pages_for(0, size);
	if (nr_pages) {
		pages = kmalloc(sizeof(pages[0])*nr_pages, GFP_NOFS);
		if (!pages)
			return -ENOMEM;
		err = -ENOMEM;
		for (i = 0; i < nr_pages; i++) {
			pages[i] = __page_cache_alloc(GFP_NOFS);
			if (!pages[i]) {
				nr_pages = i;
				goto out;
			}
			kaddr = kmap(pages[i]);
			memcpy(kaddr, value + i*PAGE_CACHE_SIZE,
			       min(PAGE_CACHE_SIZE, size-i*PAGE_CACHE_SIZE));
		}
	}

	dout("setxattr value=%.*s\n", (int)size, value);

	/* do request */
	req = ceph_mdsc_create_request(mdsc, CEPH_MDS_OP_SETXATTR,
				       USE_AUTH_MDS);
	if (IS_ERR(req)) {
		err = PTR_ERR(req);
		goto out;
	}
	req->r_inode = inode;
	ihold(inode);
	req->r_inode_drop = CEPH_CAP_XATTR_SHARED;
	req->r_num_caps = 1;
	req->r_args.setxattr.flags = cpu_to_le32(flags);
	req->r_path2 = kstrdup(name, GFP_NOFS);

	req->r_pages = pages;
	req->r_num_pages = nr_pages;
	req->r_data_len = size;

	dout("xattr.ver (before): %lld\n", ci->i_xattrs.version);
<<<<<<< HEAD
	parent_inode = ceph_get_dentry_parent_inode(dentry);
	err = ceph_mdsc_do_request(mdsc, parent_inode, req);
	iput(parent_inode);
=======
	err = ceph_mdsc_do_request(mdsc, parent_inode, req);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	ceph_mdsc_put_request(req);
	dout("xattr.ver (after): %lld\n", ci->i_xattrs.version);

out:
	if (pages) {
		for (i = 0; i < nr_pages; i++)
			__free_page(pages[i]);
		kfree(pages);
	}
	return err;
}

int ceph_setxattr(struct dentry *dentry, const char *name,
		  const void *value, size_t size, int flags)
{
	struct inode *inode = dentry->d_inode;
<<<<<<< HEAD
	struct ceph_vxattr *vxattr;
	struct ceph_inode_info *ci = ceph_inode(inode);
	int issued;
	int err;
	int dirty;
=======
	struct ceph_inode_info *ci = ceph_inode(inode);
	struct ceph_vxattr_cb *vxattrs = ceph_inode_vxattrs(inode);
	int err;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	int name_len = strlen(name);
	int val_len = size;
	char *newname = NULL;
	char *newval = NULL;
	struct ceph_inode_xattr *xattr = NULL;
<<<<<<< HEAD
	int required_blob_size;
=======
	int issued;
	int required_blob_size;
	int dirty;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

	if (ceph_snap(inode) != CEPH_NOSNAP)
		return -EROFS;

	if (!ceph_is_valid_xattr(name))
		return -EOPNOTSUPP;

<<<<<<< HEAD
	vxattr = ceph_match_vxattr(inode, name);
	if (vxattr && vxattr->readonly)
		return -EOPNOTSUPP;
=======
	if (vxattrs) {
		struct ceph_vxattr_cb *vxattr =
			ceph_match_vxattr(vxattrs, name);
		if (vxattr && vxattr->readonly)
			return -EOPNOTSUPP;
	}
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

	/* preallocate memory for xattr name, value, index node */
	err = -ENOMEM;
	newname = kmemdup(name, name_len + 1, GFP_NOFS);
	if (!newname)
		goto out;

	if (val_len) {
<<<<<<< HEAD
		newval = kmemdup(value, val_len, GFP_NOFS);
		if (!newval)
			goto out;
=======
		newval = kmalloc(val_len + 1, GFP_NOFS);
		if (!newval)
			goto out;
		memcpy(newval, value, val_len);
		newval[val_len] = '\0';
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	}

	xattr = kmalloc(sizeof(struct ceph_inode_xattr), GFP_NOFS);
	if (!xattr)
		goto out;

<<<<<<< HEAD
	spin_lock(&ci->i_ceph_lock);
retry:
	issued = __ceph_caps_issued(ci, NULL);
	dout("setxattr %p issued %s\n", inode, ceph_cap_string(issued));
=======
	spin_lock(&inode->i_lock);
retry:
	issued = __ceph_caps_issued(ci, NULL);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	if (!(issued & CEPH_CAP_XATTR_EXCL))
		goto do_sync;
	__build_xattrs(inode);

	required_blob_size = __get_required_blob_size(ci, name_len, val_len);

	if (!ci->i_xattrs.prealloc_blob ||
	    required_blob_size > ci->i_xattrs.prealloc_blob->alloc_len) {
<<<<<<< HEAD
		struct ceph_buffer *blob;

		spin_unlock(&ci->i_ceph_lock);
=======
		struct ceph_buffer *blob = NULL;

		spin_unlock(&inode->i_lock);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		dout(" preaallocating new blob size=%d\n", required_blob_size);
		blob = ceph_buffer_new(required_blob_size, GFP_NOFS);
		if (!blob)
			goto out;
<<<<<<< HEAD
		spin_lock(&ci->i_ceph_lock);
=======
		spin_lock(&inode->i_lock);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		if (ci->i_xattrs.prealloc_blob)
			ceph_buffer_put(ci->i_xattrs.prealloc_blob);
		ci->i_xattrs.prealloc_blob = blob;
		goto retry;
	}

<<<<<<< HEAD
	err = __set_xattr(ci, newname, name_len, newval,
			  val_len, 1, 1, 1, &xattr);

	dirty = __ceph_mark_dirty_caps(ci, CEPH_CAP_XATTR_EXCL);
	ci->i_xattrs.dirty = true;
	inode->i_ctime = CURRENT_TIME;

	spin_unlock(&ci->i_ceph_lock);
=======
	dout("setxattr %p issued %s\n", inode, ceph_cap_string(issued));
	err = __set_xattr(ci, newname, name_len, newval,
			  val_len, 1, 1, 1, &xattr);
	dirty = __ceph_mark_dirty_caps(ci, CEPH_CAP_XATTR_EXCL);
	ci->i_xattrs.dirty = true;
	inode->i_ctime = CURRENT_TIME;
	spin_unlock(&inode->i_lock);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	if (dirty)
		__mark_inode_dirty(inode, dirty);
	return err;

do_sync:
<<<<<<< HEAD
	spin_unlock(&ci->i_ceph_lock);
=======
	spin_unlock(&inode->i_lock);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	err = ceph_sync_setxattr(dentry, name, value, size, flags);
out:
	kfree(newname);
	kfree(newval);
	kfree(xattr);
	return err;
}

static int ceph_send_removexattr(struct dentry *dentry, const char *name)
{
	struct ceph_fs_client *fsc = ceph_sb_to_client(dentry->d_sb);
	struct ceph_mds_client *mdsc = fsc->mdsc;
	struct inode *inode = dentry->d_inode;
<<<<<<< HEAD
	struct inode *parent_inode;
=======
	struct inode *parent_inode = dentry->d_parent->d_inode;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	struct ceph_mds_request *req;
	int err;

	req = ceph_mdsc_create_request(mdsc, CEPH_MDS_OP_RMXATTR,
				       USE_AUTH_MDS);
	if (IS_ERR(req))
		return PTR_ERR(req);
	req->r_inode = inode;
	ihold(inode);
	req->r_inode_drop = CEPH_CAP_XATTR_SHARED;
	req->r_num_caps = 1;
	req->r_path2 = kstrdup(name, GFP_NOFS);

<<<<<<< HEAD
	parent_inode = ceph_get_dentry_parent_inode(dentry);
	err = ceph_mdsc_do_request(mdsc, parent_inode, req);
	iput(parent_inode);
=======
	err = ceph_mdsc_do_request(mdsc, parent_inode, req);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	ceph_mdsc_put_request(req);
	return err;
}

int ceph_removexattr(struct dentry *dentry, const char *name)
{
	struct inode *inode = dentry->d_inode;
<<<<<<< HEAD
	struct ceph_vxattr *vxattr;
	struct ceph_inode_info *ci = ceph_inode(inode);
	int issued;
	int err;
	int required_blob_size;
=======
	struct ceph_inode_info *ci = ceph_inode(inode);
	struct ceph_vxattr_cb *vxattrs = ceph_inode_vxattrs(inode);
	int issued;
	int err;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	int dirty;

	if (ceph_snap(inode) != CEPH_NOSNAP)
		return -EROFS;

	if (!ceph_is_valid_xattr(name))
		return -EOPNOTSUPP;

<<<<<<< HEAD
	vxattr = ceph_match_vxattr(inode, name);
	if (vxattr && vxattr->readonly)
		return -EOPNOTSUPP;

	err = -ENOMEM;
	spin_lock(&ci->i_ceph_lock);
retry:
=======
	if (vxattrs) {
		struct ceph_vxattr_cb *vxattr =
			ceph_match_vxattr(vxattrs, name);
		if (vxattr && vxattr->readonly)
			return -EOPNOTSUPP;
	}

	spin_lock(&inode->i_lock);
	__build_xattrs(inode);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	issued = __ceph_caps_issued(ci, NULL);
	dout("removexattr %p issued %s\n", inode, ceph_cap_string(issued));

	if (!(issued & CEPH_CAP_XATTR_EXCL))
		goto do_sync;
<<<<<<< HEAD
	__build_xattrs(inode);

	required_blob_size = __get_required_blob_size(ci, 0, 0);

	if (!ci->i_xattrs.prealloc_blob ||
	    required_blob_size > ci->i_xattrs.prealloc_blob->alloc_len) {
		struct ceph_buffer *blob;

		spin_unlock(&ci->i_ceph_lock);
		dout(" preaallocating new blob size=%d\n", required_blob_size);
		blob = ceph_buffer_new(required_blob_size, GFP_NOFS);
		if (!blob)
			goto out;
		spin_lock(&ci->i_ceph_lock);
		if (ci->i_xattrs.prealloc_blob)
			ceph_buffer_put(ci->i_xattrs.prealloc_blob);
		ci->i_xattrs.prealloc_blob = blob;
		goto retry;
	}

	err = __remove_xattr_by_name(ceph_inode(inode), name);

	dirty = __ceph_mark_dirty_caps(ci, CEPH_CAP_XATTR_EXCL);
	ci->i_xattrs.dirty = true;
	inode->i_ctime = CURRENT_TIME;
	spin_unlock(&ci->i_ceph_lock);
=======

	err = __remove_xattr_by_name(ceph_inode(inode), name);
	dirty = __ceph_mark_dirty_caps(ci, CEPH_CAP_XATTR_EXCL);
	ci->i_xattrs.dirty = true;
	inode->i_ctime = CURRENT_TIME;

	spin_unlock(&inode->i_lock);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	if (dirty)
		__mark_inode_dirty(inode, dirty);
	return err;
do_sync:
<<<<<<< HEAD
	spin_unlock(&ci->i_ceph_lock);
	err = ceph_send_removexattr(dentry, name);
out:
=======
	spin_unlock(&inode->i_lock);
	err = ceph_send_removexattr(dentry, name);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	return err;
}

