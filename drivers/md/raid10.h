#ifndef _RAID10_H
#define _RAID10_H

<<<<<<< HEAD
<<<<<<< HEAD
struct mirror_info {
	struct md_rdev	*rdev, *replacement;
	sector_t	head_position;
	int		recovery_disabled;	/* matches
						 * mddev->recovery_disabled
						 * when we shouldn't try
						 * recovering this device.
						 */
};

struct r10conf {
	struct mddev		*mddev;
	struct mirror_info	*mirrors;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
typedef struct mirror_info mirror_info_t;

struct mirror_info {
	mdk_rdev_t	*rdev;
	sector_t	head_position;
};

typedef struct r10bio_s r10bio_t;

struct r10_private_data_s {
	mddev_t			*mddev;
	mirror_info_t		*mirrors;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int			raid_disks;
	spinlock_t		device_lock;

	/* geometry */
<<<<<<< HEAD
<<<<<<< HEAD
	int			near_copies;  /* number of copies laid out
					       * raid0 style */
	int 			far_copies;   /* number of copies laid out
					       * at large strides across drives
					       */
	int			far_offset;   /* far_copies are offset by 1
					       * stripe instead of many
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int			near_copies;  /* number of copies laid out raid0 style */
	int 			far_copies;   /* number of copies laid out
					       * at large strides across drives
					       */
	int			far_offset;   /* far_copies are offset by 1 stripe
					       * instead of many
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
					       */
	int			copies;	      /* near_copies * far_copies.
					       * must be <= raid_disks
					       */
	sector_t		stride;	      /* distance between far copies.
					       * This is size / far_copies unless
					       * far_offset, in which case it is
					       * 1 stripe.
					       */

<<<<<<< HEAD
<<<<<<< HEAD
	sector_t		dev_sectors;  /* temp copy of
					       * mddev->dev_sectors */

	int			chunk_shift; /* shift from chunks to sectors */
	sector_t		chunk_mask;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	sector_t		dev_sectors;  /* temp copy of mddev->dev_sectors */

	int chunk_shift; /* shift from chunks to sectors */
	sector_t chunk_mask;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	struct list_head	retry_list;
	/* queue pending writes and submit them on unplug */
	struct bio_list		pending_bio_list;
<<<<<<< HEAD
<<<<<<< HEAD
	int			pending_count;

	spinlock_t		resync_lock;
	int			nr_pending;
	int			nr_waiting;
	int			nr_queued;
	int			barrier;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2


	spinlock_t		resync_lock;
	int nr_pending;
	int nr_waiting;
	int nr_queued;
	int barrier;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	sector_t		next_resync;
	int			fullsync;  /* set to 1 if a full sync is needed,
					    * (fresh device added).
					    * Cleared when a sync completes.
					    */
<<<<<<< HEAD
<<<<<<< HEAD
	int			have_replacement; /* There is at least one
						   * replacement device.
						   */
	wait_queue_head_t	wait_barrier;

	mempool_t		*r10bio_pool;
	mempool_t		*r10buf_pool;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	wait_queue_head_t	wait_barrier;

	mempool_t *r10bio_pool;
	mempool_t *r10buf_pool;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct page		*tmppage;

	/* When taking over an array from a different personality, we store
	 * the new thread here until we fully activate the array.
	 */
<<<<<<< HEAD
<<<<<<< HEAD
	struct md_thread	*thread;
};

=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct mdk_thread_s	*thread;
};

typedef struct r10_private_data_s conf_t;

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/*
 * this is our 'private' RAID10 bio.
 *
 * it contains information about what kind of IO operations were started
 * for this RAID10 operation, and about their status:
 */

<<<<<<< HEAD
<<<<<<< HEAD
struct r10bio {
=======
struct r10bio_s {
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
struct r10bio_s {
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	atomic_t		remaining; /* 'have we finished' count,
					    * used from IRQ handlers
					    */
	sector_t		sector;	/* virtual sector number */
	int			sectors;
	unsigned long		state;
<<<<<<< HEAD
<<<<<<< HEAD
	struct mddev		*mddev;
=======
	mddev_t			*mddev;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	mddev_t			*mddev;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	/*
	 * original bio going to /dev/mdx
	 */
	struct bio		*master_bio;
	/*
	 * if the IO is in READ direction, then this is where we read
	 */
	int			read_slot;

	struct list_head	retry_list;
	/*
	 * if the IO is in WRITE direction, then multiple bios are used,
	 * one for each copy.
	 * When resyncing we also use one for each copy.
	 * When reconstructing, we use 2 bios, one for read, one for write.
	 * We choose the number when they are allocated.
<<<<<<< HEAD
<<<<<<< HEAD
	 * We sometimes need an extra bio to write to the replacement.
	 */
	struct {
		struct bio	*bio;
		union {
			struct bio	*repl_bio; /* used for resync and
						    * writes */
			struct md_rdev	*rdev;	   /* used for reads
						    * (read_slot >= 0) */
		};
		sector_t	addr;
		int		devnum;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	 */
	struct {
		struct bio		*bio;
		sector_t addr;
		int devnum;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	} devs[0];
};

/* when we get a read error on a read-only array, we redirect to another
 * device without failing the first device, or trying to over-write to
 * correct the read error.  To keep track of bad blocks on a per-bio
 * level, we store IO_BLOCKED in the appropriate 'bios' pointer
 */
#define IO_BLOCKED ((struct bio*)1)
<<<<<<< HEAD
<<<<<<< HEAD
/* When we successfully write to a known bad-block, we need to remove the
 * bad-block marking which must be done from process context.  So we record
 * the success by setting devs[n].bio to IO_MADE_GOOD
 */
#define IO_MADE_GOOD ((struct bio *)2)

#define BIO_SPECIAL(bio) ((unsigned long)bio <= 2)

/* bits for r10bio.state */
enum r10bio_state {
	R10BIO_Uptodate,
	R10BIO_IsSync,
	R10BIO_IsRecover,
	R10BIO_Degraded,
/* Set ReadError on bios that experience a read error
 * so that raid10d knows what to do with them.
 */
	R10BIO_ReadError,
/* If a write for this request means we can clear some
 * known-bad-block records, we set this flag.
 */
	R10BIO_MadeGood,
	R10BIO_WriteError,
};
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/* bits for r10bio.state */
#define	R10BIO_Uptodate	0
#define	R10BIO_IsSync	1
#define	R10BIO_IsRecover 2
#define	R10BIO_Degraded 3
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#endif
