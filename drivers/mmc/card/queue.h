#ifndef MMC_QUEUE_H
#define MMC_QUEUE_H

struct request;
struct task_struct;

struct mmc_blk_request {
	struct mmc_request	mrq;
	struct mmc_command	sbc;
	struct mmc_command	cmd;
	struct mmc_command	stop;
	struct mmc_data		data;
};

enum mmc_packed_cmd {
	MMC_PACKED_NONE = 0,
<<<<<<< HEAD
<<<<<<< HEAD
	MMC_PACKED_WRITE,
=======
	MMC_PACKED_WR_HDR,
	MMC_PACKED_WRITE,
	MMC_PACKED_READ,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	MMC_PACKED_WR_HDR,
	MMC_PACKED_WRITE,
	MMC_PACKED_READ,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

struct mmc_queue_req {
	struct request		*req;
	struct mmc_blk_request	brq;
	struct scatterlist	*sg;
	char			*bounce_buf;
	struct scatterlist	*bounce_sg;
	unsigned int		bounce_sg_len;
	struct mmc_async_req	mmc_active;
	struct list_head	packed_list;
	u32			packed_cmd_hdr[128];
	unsigned int		packed_blocks;
	enum mmc_packed_cmd	packed_cmd;
<<<<<<< HEAD
<<<<<<< HEAD
	int		packed_retries;
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int		packed_fail_idx;
	u8		packed_num;
};

struct mmc_queue {
	struct mmc_card		*card;
	struct task_struct	*thread;
	struct semaphore	thread_sem;
	unsigned int		flags;
<<<<<<< HEAD
<<<<<<< HEAD
#define MMC_QUEUE_SUSPENDED		(1 << 0)
#define MMC_QUEUE_NEW_REQUEST		(1 << 1)
#define MMC_QUEUE_URGENT_REQUEST	(1 << 2)

=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int			(*issue_fn)(struct mmc_queue *, struct request *);
	void			*data;
	struct request_queue	*queue;
	struct mmc_queue_req	mqrq[2];
	struct mmc_queue_req	*mqrq_cur;
	struct mmc_queue_req	*mqrq_prev;
<<<<<<< HEAD
<<<<<<< HEAD
	bool			wr_packing_enabled;
	int			num_of_potential_packed_wr_reqs;
	int			num_wr_reqs_to_start_packing;
	bool			no_pack_for_random;
	int (*err_check_fn) (struct mmc_card *, struct mmc_async_req *);
	void (*packed_test_fn) (struct request_queue *, struct mmc_queue_req *);
=======
	/* Jiffies until which disable packed command. */
	unsigned long		nopacked_period;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	/* Jiffies until which disable packed command. */
	unsigned long		nopacked_period;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

extern int mmc_init_queue(struct mmc_queue *, struct mmc_card *, spinlock_t *,
			  const char *);
extern void mmc_cleanup_queue(struct mmc_queue *);
<<<<<<< HEAD
<<<<<<< HEAD
extern int mmc_queue_suspend(struct mmc_queue *, int);
=======
extern void mmc_queue_suspend(struct mmc_queue *);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
extern void mmc_queue_suspend(struct mmc_queue *);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
extern void mmc_queue_resume(struct mmc_queue *);

extern unsigned int mmc_queue_map_sg(struct mmc_queue *,
				     struct mmc_queue_req *);
extern void mmc_queue_bounce_pre(struct mmc_queue_req *);
extern void mmc_queue_bounce_post(struct mmc_queue_req *);

<<<<<<< HEAD
<<<<<<< HEAD
extern void print_mmc_packing_stats(struct mmc_card *card);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#define IS_RT_CLASS_REQ(x)     \
	(IOPRIO_PRIO_CLASS(req_get_ioprio(x)) == IOPRIO_CLASS_RT)

static inline void mmc_set_nopacked_period(struct mmc_queue *mq,
					unsigned long nopacked_jiffies)
{
	mq->nopacked_period = jiffies + nopacked_jiffies;
	smp_wmb();
}

static inline int mmc_is_nopacked_period(struct mmc_queue *mq)
{
	smp_rmb();
	return (int)time_is_after_jiffies(mq->nopacked_period);
}
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#endif
