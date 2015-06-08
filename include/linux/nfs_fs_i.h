#ifndef _NFS_FS_I
#define _NFS_FS_I

<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
#include <asm/types.h>
#include <linux/list.h>
#include <linux/nfs.h>

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
struct nlm_lockowner;

/*
 * NFS lock info
 */
struct nfs_lock_info {
	u32		state;
	struct nlm_lockowner *owner;
	struct list_head list;
};

struct nfs4_lock_state;
struct nfs4_lock_info {
	struct nfs4_lock_state *owner;
};

#endif
