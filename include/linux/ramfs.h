#ifndef _LINUX_RAMFS_H
#define _LINUX_RAMFS_H

struct inode *ramfs_get_inode(struct super_block *sb, const struct inode *dir,
<<<<<<< HEAD
	 umode_t mode, dev_t dev);
=======
<<<<<<< HEAD
	 umode_t mode, dev_t dev);
=======
	 int mode, dev_t dev);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
extern struct dentry *ramfs_mount(struct file_system_type *fs_type,
	 int flags, const char *dev_name, void *data);

#ifndef CONFIG_MMU
extern int ramfs_nommu_expand_for_mapping(struct inode *inode, size_t newsize);
extern unsigned long ramfs_nommu_get_unmapped_area(struct file *file,
						   unsigned long addr,
						   unsigned long len,
						   unsigned long pgoff,
						   unsigned long flags);

extern int ramfs_nommu_mmap(struct file *file, struct vm_area_struct *vma);
#endif

extern const struct file_operations ramfs_file_operations;
extern const struct vm_operations_struct generic_file_vm_ops;
extern int __init init_rootfs(void);

int ramfs_fill_super(struct super_block *sb, void *data, int silent);

#endif
