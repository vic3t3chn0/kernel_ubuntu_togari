/*
  File: fs/ext3/acl.h

  (C) 2001 Andreas Gruenbacher, <a.gruenbacher@computer.org>
*/

#include <linux/posix_acl_xattr.h>

#define EXT3_ACL_VERSION	0x0001

typedef struct {
	__le16		e_tag;
	__le16		e_perm;
	__le32		e_id;
} ext3_acl_entry;

typedef struct {
	__le16		e_tag;
	__le16		e_perm;
} ext3_acl_entry_short;

typedef struct {
	__le32		a_version;
} ext3_acl_header;

static inline size_t ext3_acl_size(int count)
{
	if (count <= 4) {
		return sizeof(ext3_acl_header) +
		       count * sizeof(ext3_acl_entry_short);
	} else {
		return sizeof(ext3_acl_header) +
		       4 * sizeof(ext3_acl_entry_short) +
		       (count - 4) * sizeof(ext3_acl_entry);
	}
}

static inline int ext3_acl_count(size_t size)
{
	ssize_t s;
	size -= sizeof(ext3_acl_header);
	s = size - 4 * sizeof(ext3_acl_entry_short);
	if (s < 0) {
		if (size % sizeof(ext3_acl_entry_short))
			return -1;
		return size / sizeof(ext3_acl_entry_short);
	} else {
		if (s % sizeof(ext3_acl_entry))
			return -1;
		return s / sizeof(ext3_acl_entry) + 4;
	}
}

#ifdef CONFIG_EXT3_FS_POSIX_ACL

/* acl.c */
<<<<<<< HEAD
extern struct posix_acl *ext3_get_acl(struct inode *inode, int type);
=======
<<<<<<< HEAD
extern struct posix_acl *ext3_get_acl(struct inode *inode, int type);
=======
extern int ext3_check_acl (struct inode *, int, unsigned int);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
extern int ext3_acl_chmod (struct inode *);
extern int ext3_init_acl (handle_t *, struct inode *, struct inode *);

#else  /* CONFIG_EXT3_FS_POSIX_ACL */
#include <linux/sched.h>
<<<<<<< HEAD
#define ext3_get_acl NULL
=======
<<<<<<< HEAD
#define ext3_get_acl NULL
=======
#define ext3_check_acl NULL
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

static inline int
ext3_acl_chmod(struct inode *inode)
{
	return 0;
}

static inline int
ext3_init_acl(handle_t *handle, struct inode *inode, struct inode *dir)
{
	return 0;
}
#endif  /* CONFIG_EXT3_FS_POSIX_ACL */

