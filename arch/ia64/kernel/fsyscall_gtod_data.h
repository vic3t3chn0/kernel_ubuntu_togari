/*
 * (c) Copyright 2007 Hewlett-Packard Development Company, L.P.
 *        Contributed by Peter Keilty <peter.keilty@hp.com>
 *
 * fsyscall gettimeofday data
 */

struct fsyscall_gtod_data_t {
<<<<<<< HEAD
	seqcount_t	seq;
=======
<<<<<<< HEAD
	seqcount_t	seq;
=======
	seqlock_t	lock;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct timespec	wall_time;
	struct timespec monotonic_time;
	cycle_t		clk_mask;
	u32		clk_mult;
	u32		clk_shift;
	void		*clk_fsys_mmio;
	cycle_t		clk_cycle_last;
} ____cacheline_aligned;

struct itc_jitter_data_t {
	int		itc_jitter;
	cycle_t		itc_lastcycle;
} ____cacheline_aligned;

