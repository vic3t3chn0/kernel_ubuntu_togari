/*
 * Network block device - make block devices work over TCP
 *
 * Note that you can not swap over this thing, yet. Seems to work but
 * deadlocks sometimes - you can not swap over TCP in general.
 * 
 * Copyright 1997-2000, 2008 Pavel Machek <pavel@ucw.cz>
 * Parts copyright 2001 Steven Whitehouse <steve@chygwyn.com>
 *
 * This file is released under GPLv2 or later.
 *
 * (part of code stolen from loop.c)
 */

#include <linux/major.h>

#include <linux/blkdev.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/fs.h>
#include <linux/bio.h>
#include <linux/stat.h>
#include <linux/errno.h>
#include <linux/file.h>
#include <linux/ioctl.h>
#include <linux/mutex.h>
#include <linux/compiler.h>
#include <linux/err.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <net/sock.h>
#include <linux/net.h>
#include <linux/kthread.h>

#include <asm/uaccess.h>
<<<<<<< HEAD
<<<<<<< HEAD
=======
#include <asm/system.h>
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
#include <asm/system.h>
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <asm/types.h>

#include <linux/nbd.h>

<<<<<<< HEAD
<<<<<<< HEAD
#define NBD_MAGIC 0x68797548
=======
#define LO_MAGIC 0x68797548
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
#define LO_MAGIC 0x68797548
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#ifdef NDEBUG
#define dprintk(flags, fmt...)
#else /* NDEBUG */
#define dprintk(flags, fmt...) do { \
	if (debugflags & (flags)) printk(KERN_DEBUG fmt); \
} while (0)
#define DBG_IOCTL       0x0004
#define DBG_INIT        0x0010
#define DBG_EXIT        0x0020
#define DBG_BLKDEV      0x0100
#define DBG_RX          0x0200
#define DBG_TX          0x0400
static unsigned int debugflags;
#endif /* NDEBUG */

static unsigned int nbds_max = 16;
static struct nbd_device *nbd_dev;
static int max_part;

/*
 * Use just one lock (or at most 1 per NIC). Two arguments for this:
 * 1. Each NIC is essentially a synchronization point for all servers
 *    accessed through that NIC so there's no need to have more locks
 *    than NICs anyway.
 * 2. More locks lead to more "Dirty cache line bouncing" which will slow
 *    down each lock to the point where they're actually slower than just
 *    a single lock.
 * Thanks go to Jens Axboe and Al Viro for their LKML emails explaining this!
 */
static DEFINE_SPINLOCK(nbd_lock);

#ifndef NDEBUG
static const char *ioctl_cmd_to_ascii(int cmd)
{
	switch (cmd) {
	case NBD_SET_SOCK: return "set-sock";
	case NBD_SET_BLKSIZE: return "set-blksize";
	case NBD_SET_SIZE: return "set-size";
	case NBD_DO_IT: return "do-it";
	case NBD_CLEAR_SOCK: return "clear-sock";
	case NBD_CLEAR_QUE: return "clear-que";
	case NBD_PRINT_DEBUG: return "print-debug";
	case NBD_SET_SIZE_BLOCKS: return "set-size-blocks";
	case NBD_DISCONNECT: return "disconnect";
	case BLKROSET: return "set-read-only";
	case BLKFLSBUF: return "flush-buffer-cache";
	}
	return "unknown";
}

static const char *nbdcmd_to_ascii(int cmd)
{
	switch (cmd) {
	case  NBD_CMD_READ: return "read";
	case NBD_CMD_WRITE: return "write";
	case  NBD_CMD_DISC: return "disconnect";
	}
	return "invalid";
}
#endif /* NDEBUG */

static void nbd_end_request(struct request *req)
{
	int error = req->errors ? -EIO : 0;
	struct request_queue *q = req->q;
	unsigned long flags;

	dprintk(DBG_BLKDEV, "%s: request %p: %s\n", req->rq_disk->disk_name,
			req, error ? "failed" : "done");

	spin_lock_irqsave(q->queue_lock, flags);
	__blk_end_request_all(req, error);
	spin_unlock_irqrestore(q->queue_lock, flags);
}

<<<<<<< HEAD
<<<<<<< HEAD
static void sock_shutdown(struct nbd_device *nbd, int lock)
=======
static void sock_shutdown(struct nbd_device *lo, int lock)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static void sock_shutdown(struct nbd_device *lo, int lock)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	/* Forcibly shutdown the socket causing all listeners
	 * to error
	 *
	 * FIXME: This code is duplicated from sys_shutdown, but
	 * there should be a more generic interface rather than
	 * calling socket ops directly here */
	if (lock)
<<<<<<< HEAD
<<<<<<< HEAD
		mutex_lock(&nbd->tx_lock);
	if (nbd->sock) {
		dev_warn(disk_to_dev(nbd->disk), "shutting down socket\n");
		kernel_sock_shutdown(nbd->sock, SHUT_RDWR);
		nbd->sock = NULL;
	}
	if (lock)
		mutex_unlock(&nbd->tx_lock);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		mutex_lock(&lo->tx_lock);
	if (lo->sock) {
		printk(KERN_WARNING "%s: shutting down socket\n",
			lo->disk->disk_name);
		kernel_sock_shutdown(lo->sock, SHUT_RDWR);
		lo->sock = NULL;
	}
	if (lock)
		mutex_unlock(&lo->tx_lock);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static void nbd_xmit_timeout(unsigned long arg)
{
	struct task_struct *task = (struct task_struct *)arg;

	printk(KERN_WARNING "nbd: killing hung xmit (%s, pid: %d)\n",
		task->comm, task->pid);
	force_sig(SIGKILL, task);
}

/*
 *  Send or receive packet.
 */
<<<<<<< HEAD
<<<<<<< HEAD
static int sock_xmit(struct nbd_device *nbd, int send, void *buf, int size,
		int msg_flags)
{
	struct socket *sock = nbd->sock;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static int sock_xmit(struct nbd_device *lo, int send, void *buf, int size,
		int msg_flags)
{
	struct socket *sock = lo->sock;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int result;
	struct msghdr msg;
	struct kvec iov;
	sigset_t blocked, oldset;

	if (unlikely(!sock)) {
<<<<<<< HEAD
<<<<<<< HEAD
		dev_err(disk_to_dev(nbd->disk),
			"Attempted %s on closed socket in sock_xmit\n",
			(send ? "send" : "recv"));
=======
		printk(KERN_ERR "%s: Attempted %s on closed socket in sock_xmit\n",
		       lo->disk->disk_name, (send ? "send" : "recv"));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		printk(KERN_ERR "%s: Attempted %s on closed socket in sock_xmit\n",
		       lo->disk->disk_name, (send ? "send" : "recv"));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return -EINVAL;
	}

	/* Allow interception of SIGKILL only
	 * Don't allow other signals to interrupt the transmission */
	siginitsetinv(&blocked, sigmask(SIGKILL));
	sigprocmask(SIG_SETMASK, &blocked, &oldset);

	do {
		sock->sk->sk_allocation = GFP_NOIO;
		iov.iov_base = buf;
		iov.iov_len = size;
		msg.msg_name = NULL;
		msg.msg_namelen = 0;
		msg.msg_control = NULL;
		msg.msg_controllen = 0;
		msg.msg_flags = msg_flags | MSG_NOSIGNAL;

		if (send) {
			struct timer_list ti;

<<<<<<< HEAD
<<<<<<< HEAD
			if (nbd->xmit_timeout) {
				init_timer(&ti);
				ti.function = nbd_xmit_timeout;
				ti.data = (unsigned long)current;
				ti.expires = jiffies + nbd->xmit_timeout;
				add_timer(&ti);
			}
			result = kernel_sendmsg(sock, &msg, &iov, 1, size);
			if (nbd->xmit_timeout)
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			if (lo->xmit_timeout) {
				init_timer(&ti);
				ti.function = nbd_xmit_timeout;
				ti.data = (unsigned long)current;
				ti.expires = jiffies + lo->xmit_timeout;
				add_timer(&ti);
			}
			result = kernel_sendmsg(sock, &msg, &iov, 1, size);
			if (lo->xmit_timeout)
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
				del_timer_sync(&ti);
		} else
			result = kernel_recvmsg(sock, &msg, &iov, 1, size,
						msg.msg_flags);

		if (signal_pending(current)) {
			siginfo_t info;
			printk(KERN_WARNING "nbd (pid %d: %s) got signal %d\n",
				task_pid_nr(current), current->comm,
				dequeue_signal_lock(current, &current->blocked, &info));
			result = -EINTR;
<<<<<<< HEAD
<<<<<<< HEAD
			sock_shutdown(nbd, !send);
=======
			sock_shutdown(lo, !send);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			sock_shutdown(lo, !send);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			break;
		}

		if (result <= 0) {
			if (result == 0)
				result = -EPIPE; /* short read */
			break;
		}
		size -= result;
		buf += result;
	} while (size > 0);

	sigprocmask(SIG_SETMASK, &oldset, NULL);

	return result;
}

<<<<<<< HEAD
<<<<<<< HEAD
static inline int sock_send_bvec(struct nbd_device *nbd, struct bio_vec *bvec,
=======
static inline int sock_send_bvec(struct nbd_device *lo, struct bio_vec *bvec,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static inline int sock_send_bvec(struct nbd_device *lo, struct bio_vec *bvec,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		int flags)
{
	int result;
	void *kaddr = kmap(bvec->bv_page);
<<<<<<< HEAD
<<<<<<< HEAD
	result = sock_xmit(nbd, 1, kaddr + bvec->bv_offset,
			   bvec->bv_len, flags);
=======
	result = sock_xmit(lo, 1, kaddr + bvec->bv_offset, bvec->bv_len, flags);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	result = sock_xmit(lo, 1, kaddr + bvec->bv_offset, bvec->bv_len, flags);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	kunmap(bvec->bv_page);
	return result;
}

/* always call with the tx_lock held */
<<<<<<< HEAD
<<<<<<< HEAD
static int nbd_send_req(struct nbd_device *nbd, struct request *req)
=======
static int nbd_send_req(struct nbd_device *lo, struct request *req)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static int nbd_send_req(struct nbd_device *lo, struct request *req)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	int result, flags;
	struct nbd_request request;
	unsigned long size = blk_rq_bytes(req);

	request.magic = htonl(NBD_REQUEST_MAGIC);
	request.type = htonl(nbd_cmd(req));
	request.from = cpu_to_be64((u64)blk_rq_pos(req) << 9);
	request.len = htonl(size);
	memcpy(request.handle, &req, sizeof(req));

	dprintk(DBG_TX, "%s: request %p: sending control (%s@%llu,%uB)\n",
<<<<<<< HEAD
<<<<<<< HEAD
			nbd->disk->disk_name, req,
			nbdcmd_to_ascii(nbd_cmd(req)),
			(unsigned long long)blk_rq_pos(req) << 9,
			blk_rq_bytes(req));
	result = sock_xmit(nbd, 1, &request, sizeof(request),
			(nbd_cmd(req) == NBD_CMD_WRITE) ? MSG_MORE : 0);
	if (result <= 0) {
		dev_err(disk_to_dev(nbd->disk),
			"Send control failed (result %d)\n", result);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			lo->disk->disk_name, req,
			nbdcmd_to_ascii(nbd_cmd(req)),
			(unsigned long long)blk_rq_pos(req) << 9,
			blk_rq_bytes(req));
	result = sock_xmit(lo, 1, &request, sizeof(request),
			(nbd_cmd(req) == NBD_CMD_WRITE) ? MSG_MORE : 0);
	if (result <= 0) {
		printk(KERN_ERR "%s: Send control failed (result %d)\n",
				lo->disk->disk_name, result);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		goto error_out;
	}

	if (nbd_cmd(req) == NBD_CMD_WRITE) {
		struct req_iterator iter;
		struct bio_vec *bvec;
		/*
		 * we are really probing at internals to determine
		 * whether to set MSG_MORE or not...
		 */
		rq_for_each_segment(bvec, req, iter) {
			flags = 0;
			if (!rq_iter_last(req, iter))
				flags = MSG_MORE;
			dprintk(DBG_TX, "%s: request %p: sending %d bytes data\n",
<<<<<<< HEAD
<<<<<<< HEAD
					nbd->disk->disk_name, req, bvec->bv_len);
			result = sock_send_bvec(nbd, bvec, flags);
			if (result <= 0) {
				dev_err(disk_to_dev(nbd->disk),
					"Send data failed (result %d)\n",
					result);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
					lo->disk->disk_name, req, bvec->bv_len);
			result = sock_send_bvec(lo, bvec, flags);
			if (result <= 0) {
				printk(KERN_ERR "%s: Send data failed (result %d)\n",
						lo->disk->disk_name, result);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
				goto error_out;
			}
		}
	}
	return 0;

error_out:
	return -EIO;
}

<<<<<<< HEAD
<<<<<<< HEAD
static struct request *nbd_find_request(struct nbd_device *nbd,
=======
static struct request *nbd_find_request(struct nbd_device *lo,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static struct request *nbd_find_request(struct nbd_device *lo,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
					struct request *xreq)
{
	struct request *req, *tmp;
	int err;

<<<<<<< HEAD
<<<<<<< HEAD
	err = wait_event_interruptible(nbd->active_wq, nbd->active_req != xreq);
	if (unlikely(err))
		goto out;

	spin_lock(&nbd->queue_lock);
	list_for_each_entry_safe(req, tmp, &nbd->queue_head, queuelist) {
		if (req != xreq)
			continue;
		list_del_init(&req->queuelist);
		spin_unlock(&nbd->queue_lock);
		return req;
	}
	spin_unlock(&nbd->queue_lock);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	err = wait_event_interruptible(lo->active_wq, lo->active_req != xreq);
	if (unlikely(err))
		goto out;

	spin_lock(&lo->queue_lock);
	list_for_each_entry_safe(req, tmp, &lo->queue_head, queuelist) {
		if (req != xreq)
			continue;
		list_del_init(&req->queuelist);
		spin_unlock(&lo->queue_lock);
		return req;
	}
	spin_unlock(&lo->queue_lock);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	err = -ENOENT;

out:
	return ERR_PTR(err);
}

<<<<<<< HEAD
<<<<<<< HEAD
static inline int sock_recv_bvec(struct nbd_device *nbd, struct bio_vec *bvec)
{
	int result;
	void *kaddr = kmap(bvec->bv_page);
	result = sock_xmit(nbd, 0, kaddr + bvec->bv_offset, bvec->bv_len,
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static inline int sock_recv_bvec(struct nbd_device *lo, struct bio_vec *bvec)
{
	int result;
	void *kaddr = kmap(bvec->bv_page);
	result = sock_xmit(lo, 0, kaddr + bvec->bv_offset, bvec->bv_len,
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			MSG_WAITALL);
	kunmap(bvec->bv_page);
	return result;
}

/* NULL returned = something went wrong, inform userspace */
<<<<<<< HEAD
<<<<<<< HEAD
static struct request *nbd_read_stat(struct nbd_device *nbd)
=======
static struct request *nbd_read_stat(struct nbd_device *lo)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static struct request *nbd_read_stat(struct nbd_device *lo)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	int result;
	struct nbd_reply reply;
	struct request *req;

	reply.magic = 0;
<<<<<<< HEAD
<<<<<<< HEAD
	result = sock_xmit(nbd, 0, &reply, sizeof(reply), MSG_WAITALL);
	if (result <= 0) {
		dev_err(disk_to_dev(nbd->disk),
			"Receive control failed (result %d)\n", result);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	result = sock_xmit(lo, 0, &reply, sizeof(reply), MSG_WAITALL);
	if (result <= 0) {
		printk(KERN_ERR "%s: Receive control failed (result %d)\n",
				lo->disk->disk_name, result);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		goto harderror;
	}

	if (ntohl(reply.magic) != NBD_REPLY_MAGIC) {
<<<<<<< HEAD
<<<<<<< HEAD
		dev_err(disk_to_dev(nbd->disk), "Wrong magic (0x%lx)\n",
=======
		printk(KERN_ERR "%s: Wrong magic (0x%lx)\n",
				lo->disk->disk_name,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		printk(KERN_ERR "%s: Wrong magic (0x%lx)\n",
				lo->disk->disk_name,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
				(unsigned long)ntohl(reply.magic));
		result = -EPROTO;
		goto harderror;
	}

<<<<<<< HEAD
<<<<<<< HEAD
	req = nbd_find_request(nbd, *(struct request **)reply.handle);
=======
	req = nbd_find_request(lo, *(struct request **)reply.handle);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	req = nbd_find_request(lo, *(struct request **)reply.handle);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (IS_ERR(req)) {
		result = PTR_ERR(req);
		if (result != -ENOENT)
			goto harderror;

<<<<<<< HEAD
<<<<<<< HEAD
		dev_err(disk_to_dev(nbd->disk), "Unexpected reply (%p)\n",
			reply.handle);
=======
		printk(KERN_ERR "%s: Unexpected reply (%p)\n",
				lo->disk->disk_name, reply.handle);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		printk(KERN_ERR "%s: Unexpected reply (%p)\n",
				lo->disk->disk_name, reply.handle);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		result = -EBADR;
		goto harderror;
	}

	if (ntohl(reply.error)) {
<<<<<<< HEAD
<<<<<<< HEAD
		dev_err(disk_to_dev(nbd->disk), "Other side returned error (%d)\n",
			ntohl(reply.error));
=======
		printk(KERN_ERR "%s: Other side returned error (%d)\n",
				lo->disk->disk_name, ntohl(reply.error));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		printk(KERN_ERR "%s: Other side returned error (%d)\n",
				lo->disk->disk_name, ntohl(reply.error));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		req->errors++;
		return req;
	}

	dprintk(DBG_RX, "%s: request %p: got reply\n",
<<<<<<< HEAD
<<<<<<< HEAD
			nbd->disk->disk_name, req);
=======
			lo->disk->disk_name, req);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			lo->disk->disk_name, req);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (nbd_cmd(req) == NBD_CMD_READ) {
		struct req_iterator iter;
		struct bio_vec *bvec;

		rq_for_each_segment(bvec, req, iter) {
<<<<<<< HEAD
<<<<<<< HEAD
			result = sock_recv_bvec(nbd, bvec);
			if (result <= 0) {
				dev_err(disk_to_dev(nbd->disk), "Receive data failed (result %d)\n",
					result);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			result = sock_recv_bvec(lo, bvec);
			if (result <= 0) {
				printk(KERN_ERR "%s: Receive data failed (result %d)\n",
						lo->disk->disk_name, result);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
				req->errors++;
				return req;
			}
			dprintk(DBG_RX, "%s: request %p: got %d bytes data\n",
<<<<<<< HEAD
<<<<<<< HEAD
				nbd->disk->disk_name, req, bvec->bv_len);
=======
				lo->disk->disk_name, req, bvec->bv_len);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
				lo->disk->disk_name, req, bvec->bv_len);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		}
	}
	return req;
harderror:
<<<<<<< HEAD
<<<<<<< HEAD
	nbd->harderror = result;
=======
	lo->harderror = result;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	lo->harderror = result;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return NULL;
}

static ssize_t pid_show(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	struct gendisk *disk = dev_to_disk(dev);

	return sprintf(buf, "%ld\n",
		(long) ((struct nbd_device *)disk->private_data)->pid);
}

static struct device_attribute pid_attr = {
	.attr = { .name = "pid", .mode = S_IRUGO},
	.show = pid_show,
};

<<<<<<< HEAD
<<<<<<< HEAD
static int nbd_do_it(struct nbd_device *nbd)
=======
static int nbd_do_it(struct nbd_device *lo)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static int nbd_do_it(struct nbd_device *lo)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	struct request *req;
	int ret;

<<<<<<< HEAD
<<<<<<< HEAD
	BUG_ON(nbd->magic != NBD_MAGIC);

	nbd->pid = task_pid_nr(current);
	ret = device_create_file(disk_to_dev(nbd->disk), &pid_attr);
	if (ret) {
		dev_err(disk_to_dev(nbd->disk), "device_create_file failed!\n");
		nbd->pid = 0;
		return ret;
	}

	while ((req = nbd_read_stat(nbd)) != NULL)
		nbd_end_request(req);

	device_remove_file(disk_to_dev(nbd->disk), &pid_attr);
	nbd->pid = 0;
	return 0;
}

static void nbd_clear_que(struct nbd_device *nbd)
{
	struct request *req;

	BUG_ON(nbd->magic != NBD_MAGIC);

	/*
	 * Because we have set nbd->sock to NULL under the tx_lock, all
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	BUG_ON(lo->magic != LO_MAGIC);

	lo->pid = current->pid;
	ret = sysfs_create_file(&disk_to_dev(lo->disk)->kobj, &pid_attr.attr);
	if (ret) {
		printk(KERN_ERR "nbd: sysfs_create_file failed!");
		lo->pid = 0;
		return ret;
	}

	while ((req = nbd_read_stat(lo)) != NULL)
		nbd_end_request(req);

	sysfs_remove_file(&disk_to_dev(lo->disk)->kobj, &pid_attr.attr);
	lo->pid = 0;
	return 0;
}

static void nbd_clear_que(struct nbd_device *lo)
{
	struct request *req;

	BUG_ON(lo->magic != LO_MAGIC);

	/*
	 * Because we have set lo->sock to NULL under the tx_lock, all
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	 * modifications to the list must have completed by now.  For
	 * the same reason, the active_req must be NULL.
	 *
	 * As a consequence, we don't need to take the spin lock while
	 * purging the list here.
	 */
<<<<<<< HEAD
<<<<<<< HEAD
	BUG_ON(nbd->sock);
	BUG_ON(nbd->active_req);

	while (!list_empty(&nbd->queue_head)) {
		req = list_entry(nbd->queue_head.next, struct request,
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	BUG_ON(lo->sock);
	BUG_ON(lo->active_req);

	while (!list_empty(&lo->queue_head)) {
		req = list_entry(lo->queue_head.next, struct request,
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
				 queuelist);
		list_del_init(&req->queuelist);
		req->errors++;
		nbd_end_request(req);
	}
}


<<<<<<< HEAD
<<<<<<< HEAD
static void nbd_handle_req(struct nbd_device *nbd, struct request *req)
=======
static void nbd_handle_req(struct nbd_device *lo, struct request *req)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static void nbd_handle_req(struct nbd_device *lo, struct request *req)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	if (req->cmd_type != REQ_TYPE_FS)
		goto error_out;

	nbd_cmd(req) = NBD_CMD_READ;
	if (rq_data_dir(req) == WRITE) {
		nbd_cmd(req) = NBD_CMD_WRITE;
<<<<<<< HEAD
<<<<<<< HEAD
		if (nbd->flags & NBD_READ_ONLY) {
			dev_err(disk_to_dev(nbd->disk),
				"Write on read-only\n");
=======
		if (lo->flags & NBD_READ_ONLY) {
			printk(KERN_ERR "%s: Write on read-only\n",
					lo->disk->disk_name);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		if (lo->flags & NBD_READ_ONLY) {
			printk(KERN_ERR "%s: Write on read-only\n",
					lo->disk->disk_name);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			goto error_out;
		}
	}

	req->errors = 0;

<<<<<<< HEAD
<<<<<<< HEAD
	mutex_lock(&nbd->tx_lock);
	if (unlikely(!nbd->sock)) {
		mutex_unlock(&nbd->tx_lock);
		dev_err(disk_to_dev(nbd->disk),
			"Attempted send on closed socket\n");
		goto error_out;
	}

	nbd->active_req = req;

	if (nbd_send_req(nbd, req) != 0) {
		dev_err(disk_to_dev(nbd->disk), "Request send failed\n");
		req->errors++;
		nbd_end_request(req);
	} else {
		spin_lock(&nbd->queue_lock);
		list_add(&req->queuelist, &nbd->queue_head);
		spin_unlock(&nbd->queue_lock);
	}

	nbd->active_req = NULL;
	mutex_unlock(&nbd->tx_lock);
	wake_up_all(&nbd->active_wq);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	mutex_lock(&lo->tx_lock);
	if (unlikely(!lo->sock)) {
		mutex_unlock(&lo->tx_lock);
		printk(KERN_ERR "%s: Attempted send on closed socket\n",
		       lo->disk->disk_name);
		goto error_out;
	}

	lo->active_req = req;

	if (nbd_send_req(lo, req) != 0) {
		printk(KERN_ERR "%s: Request send failed\n",
				lo->disk->disk_name);
		req->errors++;
		nbd_end_request(req);
	} else {
		spin_lock(&lo->queue_lock);
		list_add(&req->queuelist, &lo->queue_head);
		spin_unlock(&lo->queue_lock);
	}

	lo->active_req = NULL;
	mutex_unlock(&lo->tx_lock);
	wake_up_all(&lo->active_wq);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return;

error_out:
	req->errors++;
	nbd_end_request(req);
}

static int nbd_thread(void *data)
{
<<<<<<< HEAD
<<<<<<< HEAD
	struct nbd_device *nbd = data;
	struct request *req;

	set_user_nice(current, -20);
	while (!kthread_should_stop() || !list_empty(&nbd->waiting_queue)) {
		/* wait for something to do */
		wait_event_interruptible(nbd->waiting_wq,
					 kthread_should_stop() ||
					 !list_empty(&nbd->waiting_queue));

		/* extract request */
		if (list_empty(&nbd->waiting_queue))
			continue;

		spin_lock_irq(&nbd->queue_lock);
		req = list_entry(nbd->waiting_queue.next, struct request,
				 queuelist);
		list_del_init(&req->queuelist);
		spin_unlock_irq(&nbd->queue_lock);

		/* handle request */
		nbd_handle_req(nbd, req);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct nbd_device *lo = data;
	struct request *req;

	set_user_nice(current, -20);
	while (!kthread_should_stop() || !list_empty(&lo->waiting_queue)) {
		/* wait for something to do */
		wait_event_interruptible(lo->waiting_wq,
					 kthread_should_stop() ||
					 !list_empty(&lo->waiting_queue));

		/* extract request */
		if (list_empty(&lo->waiting_queue))
			continue;

		spin_lock_irq(&lo->queue_lock);
		req = list_entry(lo->waiting_queue.next, struct request,
				 queuelist);
		list_del_init(&req->queuelist);
		spin_unlock_irq(&lo->queue_lock);

		/* handle request */
		nbd_handle_req(lo, req);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}
	return 0;
}

/*
 * We always wait for result of write, for now. It would be nice to make it optional
 * in future
<<<<<<< HEAD
<<<<<<< HEAD
 * if ((rq_data_dir(req) == WRITE) && (nbd->flags & NBD_WRITE_NOCHK))
=======
 * if ((rq_data_dir(req) == WRITE) && (lo->flags & NBD_WRITE_NOCHK))
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 * if ((rq_data_dir(req) == WRITE) && (lo->flags & NBD_WRITE_NOCHK))
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *   { printk( "Warning: Ignoring result!\n"); nbd_end_request( req ); }
 */

static void do_nbd_request(struct request_queue *q)
{
	struct request *req;
	
	while ((req = blk_fetch_request(q)) != NULL) {
<<<<<<< HEAD
<<<<<<< HEAD
		struct nbd_device *nbd;
=======
		struct nbd_device *lo;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		struct nbd_device *lo;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

		spin_unlock_irq(q->queue_lock);

		dprintk(DBG_BLKDEV, "%s: request %p: dequeued (flags=%x)\n",
				req->rq_disk->disk_name, req, req->cmd_type);

<<<<<<< HEAD
<<<<<<< HEAD
		nbd = req->rq_disk->private_data;

		BUG_ON(nbd->magic != NBD_MAGIC);

		if (unlikely(!nbd->sock)) {
			dev_err(disk_to_dev(nbd->disk),
				"Attempted send on closed socket\n");
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		lo = req->rq_disk->private_data;

		BUG_ON(lo->magic != LO_MAGIC);

		if (unlikely(!lo->sock)) {
			printk(KERN_ERR "%s: Attempted send on closed socket\n",
				lo->disk->disk_name);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			req->errors++;
			nbd_end_request(req);
			spin_lock_irq(q->queue_lock);
			continue;
		}

<<<<<<< HEAD
<<<<<<< HEAD
		spin_lock_irq(&nbd->queue_lock);
		list_add_tail(&req->queuelist, &nbd->waiting_queue);
		spin_unlock_irq(&nbd->queue_lock);

		wake_up(&nbd->waiting_wq);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		spin_lock_irq(&lo->queue_lock);
		list_add_tail(&req->queuelist, &lo->waiting_queue);
		spin_unlock_irq(&lo->queue_lock);

		wake_up(&lo->waiting_wq);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

		spin_lock_irq(q->queue_lock);
	}
}

/* Must be called with tx_lock held */

<<<<<<< HEAD
<<<<<<< HEAD
static int __nbd_ioctl(struct block_device *bdev, struct nbd_device *nbd,
=======
static int __nbd_ioctl(struct block_device *bdev, struct nbd_device *lo,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static int __nbd_ioctl(struct block_device *bdev, struct nbd_device *lo,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		       unsigned int cmd, unsigned long arg)
{
	switch (cmd) {
	case NBD_DISCONNECT: {
		struct request sreq;

<<<<<<< HEAD
<<<<<<< HEAD
		dev_info(disk_to_dev(nbd->disk), "NBD_DISCONNECT\n");
=======
	        printk(KERN_INFO "%s: NBD_DISCONNECT\n", lo->disk->disk_name);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	        printk(KERN_INFO "%s: NBD_DISCONNECT\n", lo->disk->disk_name);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

		blk_rq_init(NULL, &sreq);
		sreq.cmd_type = REQ_TYPE_SPECIAL;
		nbd_cmd(&sreq) = NBD_CMD_DISC;
<<<<<<< HEAD
<<<<<<< HEAD
		if (!nbd->sock)
			return -EINVAL;
		nbd_send_req(nbd, &sreq);
=======
		if (!lo->sock)
			return -EINVAL;
		nbd_send_req(lo, &sreq);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		if (!lo->sock)
			return -EINVAL;
		nbd_send_req(lo, &sreq);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
                return 0;
	}
 
	case NBD_CLEAR_SOCK: {
		struct file *file;

<<<<<<< HEAD
<<<<<<< HEAD
		nbd->sock = NULL;
		file = nbd->file;
		nbd->file = NULL;
		nbd_clear_que(nbd);
		BUG_ON(!list_empty(&nbd->queue_head));
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		lo->sock = NULL;
		file = lo->file;
		lo->file = NULL;
		nbd_clear_que(lo);
		BUG_ON(!list_empty(&lo->queue_head));
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		if (file)
			fput(file);
		return 0;
	}

	case NBD_SET_SOCK: {
		struct file *file;
<<<<<<< HEAD
<<<<<<< HEAD
		if (nbd->file)
=======
		if (lo->file)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		if (lo->file)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			return -EBUSY;
		file = fget(arg);
		if (file) {
			struct inode *inode = file->f_path.dentry->d_inode;
			if (S_ISSOCK(inode->i_mode)) {
<<<<<<< HEAD
<<<<<<< HEAD
				nbd->file = file;
				nbd->sock = SOCKET_I(inode);
=======
				lo->file = file;
				lo->sock = SOCKET_I(inode);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
				lo->file = file;
				lo->sock = SOCKET_I(inode);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
				if (max_part > 0)
					bdev->bd_invalidated = 1;
				return 0;
			} else {
				fput(file);
			}
		}
		return -EINVAL;
	}

	case NBD_SET_BLKSIZE:
<<<<<<< HEAD
<<<<<<< HEAD
		nbd->blksize = arg;
		nbd->bytesize &= ~(nbd->blksize-1);
		bdev->bd_inode->i_size = nbd->bytesize;
		set_blocksize(bdev, nbd->blksize);
		set_capacity(nbd->disk, nbd->bytesize >> 9);
		return 0;

	case NBD_SET_SIZE:
		nbd->bytesize = arg & ~(nbd->blksize-1);
		bdev->bd_inode->i_size = nbd->bytesize;
		set_blocksize(bdev, nbd->blksize);
		set_capacity(nbd->disk, nbd->bytesize >> 9);
		return 0;

	case NBD_SET_TIMEOUT:
		nbd->xmit_timeout = arg * HZ;
		return 0;

	case NBD_SET_SIZE_BLOCKS:
		nbd->bytesize = ((u64) arg) * nbd->blksize;
		bdev->bd_inode->i_size = nbd->bytesize;
		set_blocksize(bdev, nbd->blksize);
		set_capacity(nbd->disk, nbd->bytesize >> 9);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		lo->blksize = arg;
		lo->bytesize &= ~(lo->blksize-1);
		bdev->bd_inode->i_size = lo->bytesize;
		set_blocksize(bdev, lo->blksize);
		set_capacity(lo->disk, lo->bytesize >> 9);
		return 0;

	case NBD_SET_SIZE:
		lo->bytesize = arg & ~(lo->blksize-1);
		bdev->bd_inode->i_size = lo->bytesize;
		set_blocksize(bdev, lo->blksize);
		set_capacity(lo->disk, lo->bytesize >> 9);
		return 0;

	case NBD_SET_TIMEOUT:
		lo->xmit_timeout = arg * HZ;
		return 0;

	case NBD_SET_SIZE_BLOCKS:
		lo->bytesize = ((u64) arg) * lo->blksize;
		bdev->bd_inode->i_size = lo->bytesize;
		set_blocksize(bdev, lo->blksize);
		set_capacity(lo->disk, lo->bytesize >> 9);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return 0;

	case NBD_DO_IT: {
		struct task_struct *thread;
		struct file *file;
		int error;

<<<<<<< HEAD
<<<<<<< HEAD
		if (nbd->pid)
			return -EBUSY;
		if (!nbd->file)
			return -EINVAL;

		mutex_unlock(&nbd->tx_lock);

		thread = kthread_create(nbd_thread, nbd, nbd->disk->disk_name);
		if (IS_ERR(thread)) {
			mutex_lock(&nbd->tx_lock);
			return PTR_ERR(thread);
		}
		wake_up_process(thread);
		error = nbd_do_it(nbd);
		kthread_stop(thread);

		mutex_lock(&nbd->tx_lock);
		if (error)
			return error;
		sock_shutdown(nbd, 0);
		file = nbd->file;
		nbd->file = NULL;
		nbd_clear_que(nbd);
		dev_warn(disk_to_dev(nbd->disk), "queue cleared\n");
		if (file)
			fput(file);
		nbd->bytesize = 0;
		bdev->bd_inode->i_size = 0;
		set_capacity(nbd->disk, 0);
		if (max_part > 0)
			ioctl_by_bdev(bdev, BLKRRPART, 0);
		return nbd->harderror;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		if (lo->pid)
			return -EBUSY;
		if (!lo->file)
			return -EINVAL;

		mutex_unlock(&lo->tx_lock);

		thread = kthread_create(nbd_thread, lo, "%s",
					lo->disk->disk_name);
		if (IS_ERR(thread)) {
			mutex_lock(&lo->tx_lock);
			return PTR_ERR(thread);
		}
		wake_up_process(thread);
		error = nbd_do_it(lo);
		kthread_stop(thread);

		mutex_lock(&lo->tx_lock);
		if (error)
			return error;
		sock_shutdown(lo, 0);
		file = lo->file;
		lo->file = NULL;
		nbd_clear_que(lo);
		printk(KERN_WARNING "%s: queue cleared\n", lo->disk->disk_name);
		if (file)
			fput(file);
		lo->bytesize = 0;
		bdev->bd_inode->i_size = 0;
		set_capacity(lo->disk, 0);
		if (max_part > 0)
			ioctl_by_bdev(bdev, BLKRRPART, 0);
		return lo->harderror;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}

	case NBD_CLEAR_QUE:
		/*
		 * This is for compatibility only.  The queue is always cleared
		 * by NBD_DO_IT or NBD_CLEAR_SOCK.
		 */
<<<<<<< HEAD
<<<<<<< HEAD
		BUG_ON(!nbd->sock && !list_empty(&nbd->queue_head));
		return 0;

	case NBD_PRINT_DEBUG:
		dev_info(disk_to_dev(nbd->disk),
			"next = %p, prev = %p, head = %p\n",
			nbd->queue_head.next, nbd->queue_head.prev,
			&nbd->queue_head);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		BUG_ON(!lo->sock && !list_empty(&lo->queue_head));
		return 0;

	case NBD_PRINT_DEBUG:
		printk(KERN_INFO "%s: next = %p, prev = %p, head = %p\n",
			bdev->bd_disk->disk_name,
			lo->queue_head.next, lo->queue_head.prev,
			&lo->queue_head);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return 0;
	}
	return -ENOTTY;
}

static int nbd_ioctl(struct block_device *bdev, fmode_t mode,
		     unsigned int cmd, unsigned long arg)
{
<<<<<<< HEAD
<<<<<<< HEAD
	struct nbd_device *nbd = bdev->bd_disk->private_data;
=======
	struct nbd_device *lo = bdev->bd_disk->private_data;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	struct nbd_device *lo = bdev->bd_disk->private_data;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int error;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

<<<<<<< HEAD
<<<<<<< HEAD
	BUG_ON(nbd->magic != NBD_MAGIC);

	/* Anyone capable of this syscall can do *real bad* things */
	dprintk(DBG_IOCTL, "%s: nbd_ioctl cmd=%s(0x%x) arg=%lu\n",
		nbd->disk->disk_name, ioctl_cmd_to_ascii(cmd), cmd, arg);

	mutex_lock(&nbd->tx_lock);
	error = __nbd_ioctl(bdev, nbd, cmd, arg);
	mutex_unlock(&nbd->tx_lock);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	BUG_ON(lo->magic != LO_MAGIC);

	/* Anyone capable of this syscall can do *real bad* things */
	dprintk(DBG_IOCTL, "%s: nbd_ioctl cmd=%s(0x%x) arg=%lu\n",
			lo->disk->disk_name, ioctl_cmd_to_ascii(cmd), cmd, arg);

	mutex_lock(&lo->tx_lock);
	error = __nbd_ioctl(bdev, lo, cmd, arg);
	mutex_unlock(&lo->tx_lock);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return error;
}

static const struct block_device_operations nbd_fops =
{
	.owner =	THIS_MODULE,
	.ioctl =	nbd_ioctl,
};

/*
 * And here should be modules and kernel interface 
 *  (Just smiley confuses emacs :-)
 */

static int __init nbd_init(void)
{
	int err = -ENOMEM;
	int i;
	int part_shift;

	BUILD_BUG_ON(sizeof(struct nbd_request) != 28);

	if (max_part < 0) {
<<<<<<< HEAD
<<<<<<< HEAD
		printk(KERN_ERR "nbd: max_part must be >= 0\n");
=======
		printk(KERN_CRIT "nbd: max_part must be >= 0\n");
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		printk(KERN_CRIT "nbd: max_part must be >= 0\n");
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return -EINVAL;
	}

	nbd_dev = kcalloc(nbds_max, sizeof(*nbd_dev), GFP_KERNEL);
	if (!nbd_dev)
		return -ENOMEM;

	part_shift = 0;
	if (max_part > 0) {
		part_shift = fls(max_part);

		/*
		 * Adjust max_part according to part_shift as it is exported
		 * to user space so that user can know the max number of
		 * partition kernel should be able to manage.
		 *
		 * Note that -1 is required because partition 0 is reserved
		 * for the whole disk.
		 */
		max_part = (1UL << part_shift) - 1;
	}

	if ((1UL << part_shift) > DISK_MAX_PARTS)
		return -EINVAL;

	if (nbds_max > 1UL << (MINORBITS - part_shift))
		return -EINVAL;

	for (i = 0; i < nbds_max; i++) {
		struct gendisk *disk = alloc_disk(1 << part_shift);
		if (!disk)
			goto out;
		nbd_dev[i].disk = disk;
		/*
		 * The new linux 2.5 block layer implementation requires
		 * every gendisk to have its very own request_queue struct.
		 * These structs are big so we dynamically allocate them.
		 */
		disk->queue = blk_init_queue(do_nbd_request, &nbd_lock);
		if (!disk->queue) {
			put_disk(disk);
			goto out;
		}
		/*
		 * Tell the block layer that we are not a rotational device
		 */
		queue_flag_set_unlocked(QUEUE_FLAG_NONROT, disk->queue);
	}

	if (register_blkdev(NBD_MAJOR, "nbd")) {
		err = -EIO;
		goto out;
	}

	printk(KERN_INFO "nbd: registered device at major %d\n", NBD_MAJOR);
	dprintk(DBG_INIT, "nbd: debugflags=0x%x\n", debugflags);

	for (i = 0; i < nbds_max; i++) {
		struct gendisk *disk = nbd_dev[i].disk;
		nbd_dev[i].file = NULL;
<<<<<<< HEAD
<<<<<<< HEAD
		nbd_dev[i].magic = NBD_MAGIC;
=======
		nbd_dev[i].magic = LO_MAGIC;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		nbd_dev[i].magic = LO_MAGIC;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		nbd_dev[i].flags = 0;
		INIT_LIST_HEAD(&nbd_dev[i].waiting_queue);
		spin_lock_init(&nbd_dev[i].queue_lock);
		INIT_LIST_HEAD(&nbd_dev[i].queue_head);
		mutex_init(&nbd_dev[i].tx_lock);
		init_waitqueue_head(&nbd_dev[i].active_wq);
		init_waitqueue_head(&nbd_dev[i].waiting_wq);
		nbd_dev[i].blksize = 1024;
		nbd_dev[i].bytesize = 0;
		disk->major = NBD_MAJOR;
		disk->first_minor = i << part_shift;
		disk->fops = &nbd_fops;
		disk->private_data = &nbd_dev[i];
		sprintf(disk->disk_name, "nbd%d", i);
		set_capacity(disk, 0);
		add_disk(disk);
	}

	return 0;
out:
	while (i--) {
		blk_cleanup_queue(nbd_dev[i].disk->queue);
		put_disk(nbd_dev[i].disk);
	}
	kfree(nbd_dev);
	return err;
}

static void __exit nbd_cleanup(void)
{
	int i;
	for (i = 0; i < nbds_max; i++) {
		struct gendisk *disk = nbd_dev[i].disk;
		nbd_dev[i].magic = 0;
		if (disk) {
			del_gendisk(disk);
			blk_cleanup_queue(disk->queue);
			put_disk(disk);
		}
	}
	unregister_blkdev(NBD_MAJOR, "nbd");
	kfree(nbd_dev);
	printk(KERN_INFO "nbd: unregistered device at major %d\n", NBD_MAJOR);
}

module_init(nbd_init);
module_exit(nbd_cleanup);

MODULE_DESCRIPTION("Network Block Device");
MODULE_LICENSE("GPL");

module_param(nbds_max, int, 0444);
MODULE_PARM_DESC(nbds_max, "number of network block devices to initialize (default: 16)");
module_param(max_part, int, 0444);
MODULE_PARM_DESC(max_part, "number of partitions per device (default: 0)");
#ifndef NDEBUG
module_param(debugflags, int, 0644);
MODULE_PARM_DESC(debugflags, "flags for controlling debug output");
#endif
