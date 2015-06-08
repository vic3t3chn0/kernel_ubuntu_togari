#ifndef _MULTIPATH_H
#define _MULTIPATH_H

struct multipath_info {
<<<<<<< HEAD
<<<<<<< HEAD
	struct md_rdev	*rdev;
};

struct mpconf {
	struct mddev			*mddev;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	mdk_rdev_t	*rdev;
};

struct multipath_private_data {
	mddev_t			*mddev;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct multipath_info	*multipaths;
	int			raid_disks;
	spinlock_t		device_lock;
	struct list_head	retry_list;

	mempool_t		*pool;
};

<<<<<<< HEAD
<<<<<<< HEAD
=======
typedef struct multipath_private_data multipath_conf_t;

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
typedef struct multipath_private_data multipath_conf_t;

>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/*
 * this is our 'private' 'collective' MULTIPATH buffer head.
 * it contains information about what kind of IO operations were started
 * for this MULTIPATH operation, and about their status:
 */

struct multipath_bh {
<<<<<<< HEAD
<<<<<<< HEAD
	struct mddev			*mddev;
=======
	mddev_t			*mddev;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	mddev_t			*mddev;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct bio		*master_bio;
	struct bio		bio;
	int			path;
	struct list_head	retry_list;
};
#endif
