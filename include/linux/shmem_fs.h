#ifndef __SHMEM_FS_H
#define __SHMEM_FS_H

#include <linux/swap.h>
#include <linux/mempolicy.h>
#include <linux/pagemap.h>
#include <linux/percpu_counter.h>

/* inode in-kernel data */

<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
#define SHMEM_NR_DIRECT 16

#define SHMEM_SYMLINK_INLINE_LEN (SHMEM_NR_DIRECT * sizeof(swp_entry_t))

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
struct shmem_inode_info {
	spinlock_t		lock;
	unsigned long		flags;
	unsigned long		alloced;	/* data pages alloced to file */
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	union {
		unsigned long	swapped;	/* subtotal assigned to swap */
		char		*symlink;	/* unswappable short symlink */
	};
	struct shared_policy	policy;		/* NUMA memory alloc policy */
<<<<<<< HEAD
=======
=======
	unsigned long		swapped;	/* subtotal assigned to swap */
	unsigned long		next_index;	/* highest alloced index + 1 */
	struct shared_policy	policy;		/* NUMA memory alloc policy */
	struct page		*i_indirect;	/* top indirect blocks page */
	union {
		swp_entry_t	i_direct[SHMEM_NR_DIRECT]; /* first blocks */
		char		inline_symlink[SHMEM_SYMLINK_INLINE_LEN];
	};
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct list_head	swaplist;	/* chain of maybes on swap */
	struct list_head	xattr_list;	/* list of shmem_xattr */
	struct inode		vfs_inode;
};

struct shmem_sb_info {
	unsigned long max_blocks;   /* How many blocks are allowed */
	struct percpu_counter used_blocks;  /* How many are allocated */
	unsigned long max_inodes;   /* How many inodes are allowed */
	unsigned long free_inodes;  /* How many are left for allocation */
	spinlock_t stat_lock;	    /* Serialize shmem_sb_info changes */
	uid_t uid;		    /* Mount uid for root directory */
	gid_t gid;		    /* Mount gid for root directory */
<<<<<<< HEAD
	umode_t mode;		    /* Mount mode for root directory */
=======
<<<<<<< HEAD
	umode_t mode;		    /* Mount mode for root directory */
=======
	mode_t mode;		    /* Mount mode for root directory */
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct mempolicy *mpol;     /* default memory policy for mappings */
};

static inline struct shmem_inode_info *SHMEM_I(struct inode *inode)
{
	return container_of(inode, struct shmem_inode_info, vfs_inode);
}

/*
 * Functions in mm/shmem.c called directly from elsewhere:
 */
<<<<<<< HEAD
extern int shmem_init(void);
=======
<<<<<<< HEAD
extern int shmem_init(void);
=======
extern int init_tmpfs(void);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
extern int shmem_fill_super(struct super_block *sb, void *data, int silent);
extern struct file *shmem_file_setup(const char *name,
					loff_t size, unsigned long flags);
extern int shmem_zero_setup(struct vm_area_struct *);
extern int shmem_lock(struct file *file, int lock, struct user_struct *user);
<<<<<<< HEAD
extern void shmem_unlock_mapping(struct address_space *mapping);
=======
<<<<<<< HEAD
extern void shmem_unlock_mapping(struct address_space *mapping);
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
extern struct page *shmem_read_mapping_page_gfp(struct address_space *mapping,
					pgoff_t index, gfp_t gfp_mask);
extern void shmem_truncate_range(struct inode *inode, loff_t start, loff_t end);
extern int shmem_unuse(swp_entry_t entry, struct page *page);
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
extern void mem_cgroup_get_shmem_target(struct inode *inode, pgoff_t pgoff,
					struct page **pagep, swp_entry_t *ent);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

static inline struct page *shmem_read_mapping_page(
				struct address_space *mapping, pgoff_t index)
{
	return shmem_read_mapping_page_gfp(mapping, index,
					mapping_gfp_mask(mapping));
}

#endif
