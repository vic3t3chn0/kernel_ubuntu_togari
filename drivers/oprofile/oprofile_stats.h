/**
 * @file oprofile_stats.h
 *
 * @remark Copyright 2002 OProfile authors
 * @remark Read the file COPYING
 *
 * @author John Levon
 */

#ifndef OPROFILE_STATS_H
#define OPROFILE_STATS_H

<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/atomic.h>
=======
#include <asm/atomic.h>
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
#include <asm/atomic.h>
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

struct oprofile_stat_struct {
	atomic_t sample_lost_no_mm;
	atomic_t sample_lost_no_mapping;
	atomic_t bt_lost_no_mapping;
	atomic_t event_lost_overflow;
	atomic_t multiplex_counter;
};

extern struct oprofile_stat_struct oprofile_stats;

/* reset all stats to zero */
void oprofile_reset_stats(void);

struct super_block;
struct dentry;

/* create the stats/ dir */
void oprofile_create_stats_files(struct super_block *sb, struct dentry *root);

#endif /* OPROFILE_STATS_H */
