/*
 * Compressed RAM block device
 *
 * Copyright (C) 2008, 2009, 2010  Nitin Gupta
 *
 * This code is released using a dual license strategy: BSD/GPL
 * You can choose the licence that better fits your requirements.
 *
 * Released under the terms of 3-clause BSD License
 * Released under the terms of GNU General Public License Version 2.0
 *
 * Project home: http://compcache.googlecode.com
 */

#ifndef _ZRAM_DRV_H_
#define _ZRAM_DRV_H_

#include <linux/spinlock.h>
#include <linux/mutex.h>

<<<<<<< HEAD
<<<<<<< HEAD
#include "../zsmalloc/zsmalloc.h"
=======
#include "xvmalloc.h"
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
#include "xvmalloc.h"
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/*
 * Some arbitrary value. This is just to catch
 * invalid value for num_devices module parameter.
 */
static const unsigned max_num_devices = 32;

<<<<<<< HEAD
<<<<<<< HEAD
/*-- Configurable parameters */

=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/*
 * Stored at beginning of each compressed object.
 *
 * It stores back-reference to table entry which points to this
 * object. This is required to support memory defragmentation.
 */
struct zobj_header {
#if 0
	u32 table_idx;
#endif
};

/*-- Configurable parameters */

/* Default zram disk size: 25% of total RAM */
static const unsigned default_disksize_perc_ram = 25;

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/*
 * Pages that compress to size greater than this are stored
 * uncompressed in memory.
 */
<<<<<<< HEAD
<<<<<<< HEAD
static const size_t max_zpage_size = PAGE_SIZE / 10 * 9;

/*
 * NOTE: max_zpage_size must be less than or equal to:
 *   ZS_MAX_ALLOC_SIZE. Otherwise, zs_malloc() would
 * always return failure.
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static const unsigned max_zpage_size = PAGE_SIZE / 4 * 3;

/*
 * NOTE: max_zpage_size must be less than or equal to:
 *   XV_MAX_ALLOC_SIZE - sizeof(struct zobj_header)
 * otherwise, xv_malloc() would always return failure.
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */

/*-- End of configurable params */

#define SECTOR_SHIFT		9
#define SECTOR_SIZE		(1 << SECTOR_SHIFT)
#define SECTORS_PER_PAGE_SHIFT	(PAGE_SHIFT - SECTOR_SHIFT)
#define SECTORS_PER_PAGE	(1 << SECTORS_PER_PAGE_SHIFT)
<<<<<<< HEAD
<<<<<<< HEAD
#define ZRAM_LOGICAL_BLOCK_SHIFT 12
#define ZRAM_LOGICAL_BLOCK_SIZE	(1 << ZRAM_LOGICAL_BLOCK_SHIFT)
#define ZRAM_SECTOR_PER_LOGICAL_BLOCK	\
	(1 << (ZRAM_LOGICAL_BLOCK_SHIFT - SECTOR_SHIFT))

/* Flags for zram pages (table[page_no].flags) */
enum zram_pageflags {
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#define ZRAM_LOGICAL_BLOCK_SIZE	4096

/* Flags for zram pages (table[page_no].flags) */
enum zram_pageflags {
	/* Page is stored uncompressed */
	ZRAM_UNCOMPRESSED,

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	/* Page consists entirely of zeros */
	ZRAM_ZERO,

	__NR_ZRAM_PAGEFLAGS,
};

/*-- Data structures */

/* Allocated for each disk page */
struct table {
<<<<<<< HEAD
<<<<<<< HEAD
	unsigned long handle;
	u16 size;	/* object size (excluding header) */
	u8 count;	/* object ref count (not yet used) */
	u8 flags;
} __aligned(4);

/*
 * All 64bit fields should only be manipulated by 64bit atomic accessors.
 * All modifications to 32bit counter should be protected by zram->lock.
 */
struct zram_stats {
	atomic64_t compr_size;	/* compressed size of pages stored */
	atomic64_t num_reads;	/* failed + successful */
	atomic64_t num_writes;	/* --do-- */
	atomic64_t failed_reads;	/* should NEVER! happen */
	atomic64_t failed_writes;	/* can happen when memory is too low */
	atomic64_t invalid_io;	/* non-page-aligned I/O requests */
	atomic64_t notify_free;	/* no. of swap slot free notifications */
	u32 pages_zero;		/* no. of zero filled pages */
	u32 pages_stored;	/* no. of pages currently stored */
	u32 good_compress;	/* % of pages with compression ratio<=50% */
	u32 bad_compress;	/* % of pages with compression ratio>=75% */
};

struct zram_meta {
	void *compress_workmem;
	void *compress_buffer;
	struct table *table;
	struct zs_pool *mem_pool;
};

struct zram_slot_free {
	unsigned long index;
	struct zram_slot_free *next;
};

struct zram {
	struct zram_meta *meta;
	struct rw_semaphore lock; /* protect compression buffers, table,
				   * 32bit stat counters against concurrent
				   * notifications, reads and writes */

	struct work_struct free_work;  /* handle pending free request */
	struct zram_slot_free *slot_free_rq; /* list head of free request */

	struct request_queue *queue;
	struct gendisk *disk;
	int init_done;
	/* Prevent concurrent execution of device init, reset and R/W request */
	struct rw_semaphore init_lock;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct page *page;
	u16 offset;
	u8 count;	/* object ref count (not yet used) */
	u8 flags;
} __attribute__((aligned(4)));

struct zram_stats {
	u64 compr_size;		/* compressed size of pages stored */
	u64 num_reads;		/* failed + successful */
	u64 num_writes;		/* --do-- */
	u64 failed_reads;	/* should NEVER! happen */
	u64 failed_writes;	/* can happen when memory is too low */
	u64 invalid_io;		/* non-page-aligned I/O requests */
	u64 notify_free;	/* no. of swap slot free notifications */
	u32 pages_zero;		/* no. of zero filled pages */
	u32 pages_stored;	/* no. of pages currently stored */
	u32 good_compress;	/* % of pages with compression ratio<=50% */
	u32 pages_expand;	/* % of incompressible pages */
};

struct zram {
	struct xv_pool *mem_pool;
	void *compress_workmem;
	void *compress_buffer;
	struct table *table;
	spinlock_t stat64_lock;	/* protect 64-bit stats */
	struct mutex lock;	/* protect compression buffers against
				 * concurrent writes */
	struct request_queue *queue;
	struct gendisk *disk;
	int init_done;
	/* Prevent concurrent execution of device init and reset */
	struct mutex init_lock;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	/*
	 * This is the limit on amount of *uncompressed* worth of data
	 * we can store in a disk.
	 */
	u64 disksize;	/* bytes */
<<<<<<< HEAD
<<<<<<< HEAD
	spinlock_t slot_free_lock;

	struct zram_stats stats;
};
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	struct zram_stats stats;
};

extern struct zram *zram_devices;
extern unsigned int num_devices;
#ifdef CONFIG_SYSFS
extern struct attribute_group zram_disk_attr_group;
#endif

extern int zram_init_device(struct zram *zram);
extern void zram_reset_device(struct zram *zram);

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#endif
