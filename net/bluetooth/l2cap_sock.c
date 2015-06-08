/*
   BlueZ - Bluetooth protocol stack for Linux
<<<<<<< HEAD
   Copyright (c) 2000-2001, 2011-2012 The Linux Foundation.  All rights reserved.
=======
<<<<<<< HEAD
   Copyright (c) 2000-2001, 2011-2012 The Linux Foundation.  All rights reserved.
=======
   Copyright (C) 2000-2001 Qualcomm Incorporated
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
   Copyright (C) 2009-2010 Gustavo F. Padovan <gustavo@padovan.org>
   Copyright (C) 2010 Google Inc.

   Written 2000,2001 by Maxim Krasnyansky <maxk@qualcomm.com>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License version 2 as
   published by the Free Software Foundation;

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.
   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY
   CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES
   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS,
   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS
   SOFTWARE IS DISCLAIMED.
*/

/* Bluetooth L2CAP sockets. */

<<<<<<< HEAD
#include <linux/interrupt.h>
#include <linux/module.h>

=======
<<<<<<< HEAD
#include <linux/interrupt.h>
#include <linux/module.h>

=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <net/bluetooth/bluetooth.h>
#include <net/bluetooth/hci_core.h>
#include <net/bluetooth/l2cap.h>
#include <net/bluetooth/smp.h>
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <net/bluetooth/amp.h>

/* ---- L2CAP timers ---- */
static void l2cap_sock_timeout(unsigned long arg)
{
	struct sock *sk = (struct sock *) arg;
	int reason;

	BT_DBG("sock %p state %d", sk, sk->sk_state);

	bh_lock_sock(sk);

	if (sock_owned_by_user(sk)) {
		/* sk is owned by user. Try again later */
		l2cap_sock_set_timer(sk, HZ / 5);
		bh_unlock_sock(sk);
		sock_put(sk);
		return;
	}

	if (sk->sk_state == BT_CONNECTED || sk->sk_state == BT_CONFIG)
		reason = ECONNREFUSED;
	else if (sk->sk_state == BT_CONNECT &&
				l2cap_pi(sk)->sec_level != BT_SECURITY_SDP)
		reason = ECONNREFUSED;
	else
		reason = ETIMEDOUT;

	__l2cap_sock_close(sk, reason);

	bh_unlock_sock(sk);

	l2cap_sock_kill(sk);
	sock_put(sk);
}

void l2cap_sock_set_timer(struct sock *sk, long timeout)
{
	BT_DBG("sk %p state %d timeout %ld", sk, sk->sk_state, timeout);
	sk_reset_timer(sk, &sk->sk_timer, jiffies + timeout);
}

void l2cap_sock_clear_timer(struct sock *sk)
{
	BT_DBG("sock %p state %d", sk, sk->sk_state);
	sk_stop_timer(sk, &sk->sk_timer);
}

int l2cap_sock_le_params_valid(struct bt_le_params *le_params)
{
	if (!le_params || le_params->latency > BT_LE_LATENCY_MAX ||
			le_params->scan_window > BT_LE_SCAN_WINDOW_MAX ||
			le_params->scan_interval < BT_LE_SCAN_INTERVAL_MIN ||
			le_params->scan_window > le_params->scan_interval ||
			le_params->interval_min < BT_LE_CONN_INTERVAL_MIN ||
			le_params->interval_max > BT_LE_CONN_INTERVAL_MAX ||
			le_params->interval_min > le_params->interval_max ||
			le_params->supervision_timeout < BT_LE_SUP_TO_MIN ||
			le_params->supervision_timeout > BT_LE_SUP_TO_MAX) {
		return 0;
	}

	return 1;
}

int l2cap_sock_le_conn_update_params_valid(struct bt_le_params *le_params)
{
	if (!le_params || le_params->latency > BT_LE_LATENCY_MAX ||
			le_params->interval_min < BT_LE_CONN_INTERVAL_MIN ||
			le_params->interval_max > BT_LE_CONN_INTERVAL_MAX ||
			le_params->interval_min > le_params->interval_max ||
			le_params->supervision_timeout < BT_LE_SUP_TO_MIN ||
			le_params->supervision_timeout > BT_LE_SUP_TO_MAX) {
		return 0;
	}

	return 1;
}

static struct sock *__l2cap_get_sock_by_addr(__le16 psm, bdaddr_t *src)
{
	struct sock *sk;
	struct hlist_node *node;
	sk_for_each(sk, node, &l2cap_sk_list.head)
		if (l2cap_pi(sk)->sport == psm && !bacmp(&bt_sk(sk)->src, src))
			goto found;
	sk = NULL;
found:
	return sk;
}
<<<<<<< HEAD
=======
=======

static const struct proto_ops l2cap_sock_ops;
static void l2cap_sock_init(struct sock *sk, struct sock *parent);
static struct sock *l2cap_sock_alloc(struct net *net, struct socket *sock, int proto, gfp_t prio);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

static int l2cap_sock_bind(struct socket *sock, struct sockaddr *addr, int alen)
{
	struct sock *sk = sock->sk;
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
	struct l2cap_chan *chan = l2cap_pi(sk)->chan;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct sockaddr_l2 la;
	int len, err = 0;

	BT_DBG("sk %p", sk);

	if (!addr || addr->sa_family != AF_BLUETOOTH)
		return -EINVAL;

	memset(&la, 0, sizeof(la));
	len = min_t(unsigned int, sizeof(la), alen);
	memcpy(&la, addr, len);

	if (la.l2_cid && la.l2_psm)
		return -EINVAL;

	lock_sock(sk);

	if (sk->sk_state != BT_OPEN) {
		err = -EBADFD;
		goto done;
	}

	if (la.l2_psm) {
		__u16 psm = __le16_to_cpu(la.l2_psm);

		/* PSM must be odd and lsb of upper byte must be 0 */
		if ((psm & 0x0101) != 0x0001) {
			err = -EINVAL;
			goto done;
		}

		/* Restrict usage of well-known PSMs */
		if (psm < 0x1001 && !capable(CAP_NET_BIND_SERVICE)) {
			err = -EACCES;
			goto done;
		}
	}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	write_lock_bh(&l2cap_sk_list.lock);

	if (la.l2_psm && __l2cap_get_sock_by_addr(la.l2_psm, &la.l2_bdaddr)) {
		err = -EADDRINUSE;
	} else {
		/* Save source address */
		bacpy(&bt_sk(sk)->src, &la.l2_bdaddr);
		l2cap_pi(sk)->psm   = la.l2_psm;
		l2cap_pi(sk)->sport = la.l2_psm;
		sk->sk_state = BT_BOUND;

		if (__le16_to_cpu(la.l2_psm) == 0x0001 ||
					__le16_to_cpu(la.l2_psm) == 0x0003)
			l2cap_pi(sk)->sec_level = BT_SECURITY_SDP;
	}

	if (la.l2_cid)
		l2cap_pi(sk)->scid = la.l2_cid;

	write_unlock_bh(&l2cap_sk_list.lock);
<<<<<<< HEAD
=======
=======
	if (la.l2_cid)
		err = l2cap_add_scid(chan, la.l2_cid);
	else
		err = l2cap_add_psm(chan, &la.l2_bdaddr, la.l2_psm);

	if (err < 0)
		goto done;

	if (__le16_to_cpu(la.l2_psm) == 0x0001 ||
				__le16_to_cpu(la.l2_psm) == 0x0003)
		chan->sec_level = BT_SECURITY_SDP;

	bacpy(&bt_sk(sk)->src, &la.l2_bdaddr);

	chan->state = BT_BOUND;
	sk->sk_state = BT_BOUND;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

done:
	release_sock(sk);
	return err;
}

static int l2cap_sock_connect(struct socket *sock, struct sockaddr *addr, int alen, int flags)
{
	struct sock *sk = sock->sk;
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct sockaddr_l2 la;
	int len, err = 0;

	BT_DBG("sk %p type %d mode %d state %d", sk, sk->sk_type,
		l2cap_pi(sk)->mode, sk->sk_state);

	if (!addr || alen < sizeof(addr->sa_family) ||
		addr->sa_family != AF_BLUETOOTH)
<<<<<<< HEAD
=======
=======
	struct l2cap_chan *chan = l2cap_pi(sk)->chan;
	struct sockaddr_l2 la;
	int len, err = 0;

	BT_DBG("sk %p", sk);

	if (!addr || alen < sizeof(addr->sa_family) ||
	    addr->sa_family != AF_BLUETOOTH)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return -EINVAL;

	memset(&la, 0, sizeof(la));
	len = min_t(unsigned int, sizeof(la), alen);
	memcpy(&la, addr, len);

	if (la.l2_cid && la.l2_psm)
		return -EINVAL;

	lock_sock(sk);

<<<<<<< HEAD
	if ((sk->sk_type == SOCK_SEQPACKET || sk->sk_type == SOCK_STREAM)
		&& !(la.l2_psm || la.l2_cid || l2cap_pi(sk)->fixed_channel)) {
=======
<<<<<<< HEAD
	if ((sk->sk_type == SOCK_SEQPACKET || sk->sk_type == SOCK_STREAM)
		&& !(la.l2_psm || la.l2_cid || l2cap_pi(sk)->fixed_channel)) {
=======
	if (chan->chan_type == L2CAP_CHAN_CONN_ORIENTED
			&& !(la.l2_psm || la.l2_cid)) {
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		err = -EINVAL;
		goto done;
	}

<<<<<<< HEAD
	switch (l2cap_pi(sk)->mode) {
=======
<<<<<<< HEAD
	switch (l2cap_pi(sk)->mode) {
=======
	switch (chan->mode) {
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	case L2CAP_MODE_BASIC:
		break;
	case L2CAP_MODE_ERTM:
	case L2CAP_MODE_STREAMING:
		if (!disable_ertm)
			break;
		/* fall through */
	default:
		err = -ENOTSUPP;
		goto done;
	}

	switch (sk->sk_state) {
	case BT_CONNECT:
	case BT_CONNECT2:
	case BT_CONFIG:
		/* Already connecting */
		goto wait;

	case BT_CONNECTED:
		/* Already connected */
		err = -EISCONN;
		goto done;

	case BT_OPEN:
	case BT_BOUND:
		/* Can connect */
		break;

	default:
		err = -EBADFD;
		goto done;
	}

	/* PSM must be odd and lsb of upper byte must be 0 */
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if ((__le16_to_cpu(la.l2_psm) & 0x0101) != 0x0001 &&
		!l2cap_pi(sk)->fixed_channel &&
				sk->sk_type != SOCK_RAW && !la.l2_cid) {
		BT_DBG("Bad PSM 0x%x", (int)__le16_to_cpu(la.l2_psm));
<<<<<<< HEAD
=======
=======
	if ((__le16_to_cpu(la.l2_psm) & 0x0101) != 0x0001 && !la.l2_cid &&
					chan->chan_type != L2CAP_CHAN_RAW) {
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		err = -EINVAL;
		goto done;
	}

	/* Set destination address and psm */
	bacpy(&bt_sk(sk)->dst, &la.l2_bdaddr);
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	l2cap_pi(sk)->psm = la.l2_psm;
	l2cap_pi(sk)->dcid = la.l2_cid;

	err = l2cap_do_connect(sk);
<<<<<<< HEAD
=======
=======
	chan->psm = la.l2_psm;
	chan->dcid = la.l2_cid;

	err = l2cap_chan_connect(l2cap_pi(sk)->chan);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (err)
		goto done;

wait:
	err = bt_sock_wait_state(sk, BT_CONNECTED,
			sock_sndtimeo(sk, flags & O_NONBLOCK));
done:
<<<<<<< HEAD
	if (err)
		BT_ERR("failed %d", err);
=======
<<<<<<< HEAD
	if (err)
		BT_ERR("failed %d", err);
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	release_sock(sk);
	return err;
}

static int l2cap_sock_listen(struct socket *sock, int backlog)
{
	struct sock *sk = sock->sk;
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
	struct l2cap_chan *chan = l2cap_pi(sk)->chan;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int err = 0;

	BT_DBG("sk %p backlog %d", sk, backlog);

	lock_sock(sk);

	if ((sock->type != SOCK_SEQPACKET && sock->type != SOCK_STREAM)
			|| sk->sk_state != BT_BOUND) {
		err = -EBADFD;
		goto done;
	}

<<<<<<< HEAD
	switch (l2cap_pi(sk)->mode) {
=======
<<<<<<< HEAD
	switch (l2cap_pi(sk)->mode) {
=======
	switch (chan->mode) {
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	case L2CAP_MODE_BASIC:
		break;
	case L2CAP_MODE_ERTM:
	case L2CAP_MODE_STREAMING:
		if (!disable_ertm)
			break;
		/* fall through */
	default:
		err = -ENOTSUPP;
		goto done;
	}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (!l2cap_pi(sk)->psm && !l2cap_pi(sk)->scid) {
		bdaddr_t *src = &bt_sk(sk)->src;
		u16 psm;

		err = -EINVAL;

		write_lock_bh(&l2cap_sk_list.lock);

		for (psm = 0x1001; psm < 0x1100; psm += 2)
			if (!__l2cap_get_sock_by_addr(cpu_to_le16(psm), src)) {
				l2cap_pi(sk)->psm   = cpu_to_le16(psm);
				l2cap_pi(sk)->sport = cpu_to_le16(psm);
				err = 0;
				break;
			}

		write_unlock_bh(&l2cap_sk_list.lock);

		if (err < 0)
			goto done;
	}

	sk->sk_max_ack_backlog = backlog;
	sk->sk_ack_backlog = 0;
<<<<<<< HEAD
=======
=======
	sk->sk_max_ack_backlog = backlog;
	sk->sk_ack_backlog = 0;

	chan->state = BT_LISTEN;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	sk->sk_state = BT_LISTEN;

done:
	release_sock(sk);
	return err;
}

static int l2cap_sock_accept(struct socket *sock, struct socket *newsock, int flags)
{
	DECLARE_WAITQUEUE(wait, current);
	struct sock *sk = sock->sk, *nsk;
	long timeo;
	int err = 0;

	lock_sock_nested(sk, SINGLE_DEPTH_NESTING);

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (sk->sk_state != BT_LISTEN) {
		err = -EBADFD;
		goto done;
	}

<<<<<<< HEAD
=======
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	timeo = sock_rcvtimeo(sk, flags & O_NONBLOCK);

	BT_DBG("sk %p timeo %ld", sk, timeo);

	/* Wait for an incoming connection. (wake-one). */
	add_wait_queue_exclusive(sk_sleep(sk), &wait);
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	while (!(nsk = bt_accept_dequeue(sk, newsock))) {
		set_current_state(TASK_INTERRUPTIBLE);
		if (!timeo) {
			err = -EAGAIN;
			break;
		}

		release_sock(sk);
		timeo = schedule_timeout(timeo);
		lock_sock_nested(sk, SINGLE_DEPTH_NESTING);

		if (sk->sk_state != BT_LISTEN) {
			err = -EBADFD;
<<<<<<< HEAD
=======
=======
	while (1) {
		set_current_state(TASK_INTERRUPTIBLE);

		if (sk->sk_state != BT_LISTEN) {
			err = -EBADFD;
			break;
		}

		nsk = bt_accept_dequeue(sk, newsock);
		if (nsk)
			break;

		if (!timeo) {
			err = -EAGAIN;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			break;
		}

		if (signal_pending(current)) {
			err = sock_intr_errno(timeo);
			break;
		}
<<<<<<< HEAD
	}
	set_current_state(TASK_RUNNING);
=======
<<<<<<< HEAD
	}
	set_current_state(TASK_RUNNING);
=======

		release_sock(sk);
		timeo = schedule_timeout(timeo);
		lock_sock_nested(sk, SINGLE_DEPTH_NESTING);
	}
	__set_current_state(TASK_RUNNING);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	remove_wait_queue(sk_sleep(sk), &wait);

	if (err)
		goto done;

	newsock->state = SS_CONNECTED;

	BT_DBG("new socket %p", nsk);

done:
	release_sock(sk);
	return err;
}

static int l2cap_sock_getname(struct socket *sock, struct sockaddr *addr, int *len, int peer)
{
	struct sockaddr_l2 *la = (struct sockaddr_l2 *) addr;
	struct sock *sk = sock->sk;
<<<<<<< HEAD

	BT_DBG("sock %p, sk %p", sock, sk);

=======
<<<<<<< HEAD

	BT_DBG("sock %p, sk %p", sock, sk);

=======
	struct l2cap_chan *chan = l2cap_pi(sk)->chan;

	BT_DBG("sock %p, sk %p", sock, sk);

	memset(la, 0, sizeof(struct sockaddr_l2));
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	addr->sa_family = AF_BLUETOOTH;
	*len = sizeof(struct sockaddr_l2);

	if (peer) {
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		la->l2_psm = l2cap_pi(sk)->psm;
		bacpy(&la->l2_bdaddr, &bt_sk(sk)->dst);
		la->l2_cid = cpu_to_le16(l2cap_pi(sk)->dcid);
	} else {
		la->l2_psm = l2cap_pi(sk)->sport;
		bacpy(&la->l2_bdaddr, &bt_sk(sk)->src);
		la->l2_cid = cpu_to_le16(l2cap_pi(sk)->scid);
<<<<<<< HEAD
=======
=======
		la->l2_psm = chan->psm;
		bacpy(&la->l2_bdaddr, &bt_sk(sk)->dst);
		la->l2_cid = cpu_to_le16(chan->dcid);
	} else {
		la->l2_psm = chan->sport;
		bacpy(&la->l2_bdaddr, &bt_sk(sk)->src);
		la->l2_cid = cpu_to_le16(chan->scid);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}

	return 0;
}

static int l2cap_sock_getsockopt_old(struct socket *sock, int optname, char __user *optval, int __user *optlen)
{
	struct sock *sk = sock->sk;
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
	struct l2cap_chan *chan = l2cap_pi(sk)->chan;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct l2cap_options opts;
	struct l2cap_conninfo cinfo;
	int len, err = 0;
	u32 opt;

	BT_DBG("sk %p", sk);

	if (get_user(len, optlen))
		return -EFAULT;

	lock_sock(sk);

	switch (optname) {
	case L2CAP_OPTIONS:
		memset(&opts, 0, sizeof(opts));
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		opts.imtu     = l2cap_pi(sk)->imtu;
		opts.omtu     = l2cap_pi(sk)->omtu;
		opts.flush_to = l2cap_pi(sk)->flush_to;
		opts.mode     = l2cap_pi(sk)->mode;
		opts.fcs      = l2cap_pi(sk)->fcs;
		opts.max_tx   = l2cap_pi(sk)->max_tx;
		opts.txwin_size = l2cap_pi(sk)->tx_win;
<<<<<<< HEAD
=======
=======
		opts.imtu     = chan->imtu;
		opts.omtu     = chan->omtu;
		opts.flush_to = chan->flush_to;
		opts.mode     = chan->mode;
		opts.fcs      = chan->fcs;
		opts.max_tx   = chan->max_tx;
		opts.txwin_size = (__u16)chan->tx_win;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

		len = min_t(unsigned int, len, sizeof(opts));
		if (copy_to_user(optval, (char *) &opts, len))
			err = -EFAULT;

		break;

	case L2CAP_LM:
<<<<<<< HEAD
		switch (l2cap_pi(sk)->sec_level) {
=======
<<<<<<< HEAD
		switch (l2cap_pi(sk)->sec_level) {
=======
		switch (chan->sec_level) {
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		case BT_SECURITY_LOW:
			opt = L2CAP_LM_AUTH;
			break;
		case BT_SECURITY_MEDIUM:
			opt = L2CAP_LM_AUTH | L2CAP_LM_ENCRYPT;
			break;
		case BT_SECURITY_HIGH:
			opt = L2CAP_LM_AUTH | L2CAP_LM_ENCRYPT |
							L2CAP_LM_SECURE;
			break;
		default:
			opt = 0;
			break;
		}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		if (l2cap_pi(sk)->role_switch)
			opt |= L2CAP_LM_MASTER;

		if (l2cap_pi(sk)->force_reliable)
			opt |= L2CAP_LM_RELIABLE;

		if (l2cap_pi(sk)->flushable)
			opt |= L2CAP_LM_FLUSHABLE;

<<<<<<< HEAD
=======
=======
		if (chan->role_switch)
			opt |= L2CAP_LM_MASTER;

		if (chan->force_reliable)
			opt |= L2CAP_LM_RELIABLE;

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		if (put_user(opt, (u32 __user *) optval))
			err = -EFAULT;
		break;

	case L2CAP_CONNINFO:
		if (sk->sk_state != BT_CONNECTED &&
					!(sk->sk_state == BT_CONNECT2 &&
						bt_sk(sk)->defer_setup)) {
			err = -ENOTCONN;
			break;
		}

<<<<<<< HEAD
		cinfo.hci_handle = l2cap_pi(sk)->conn->hcon->handle;
		memcpy(cinfo.dev_class, l2cap_pi(sk)->conn->hcon->dev_class, 3);
=======
<<<<<<< HEAD
		cinfo.hci_handle = l2cap_pi(sk)->conn->hcon->handle;
		memcpy(cinfo.dev_class, l2cap_pi(sk)->conn->hcon->dev_class, 3);
=======
		memset(&cinfo, 0, sizeof(cinfo));
		cinfo.hci_handle = chan->conn->hcon->handle;
		memcpy(cinfo.dev_class, chan->conn->hcon->dev_class, 3);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

		len = min_t(unsigned int, len, sizeof(cinfo));
		if (copy_to_user(optval, (char *) &cinfo, len))
			err = -EFAULT;

		break;

	default:
		err = -ENOPROTOOPT;
		break;
	}

	release_sock(sk);
	return err;
}

static int l2cap_sock_getsockopt(struct socket *sock, int level, int optname, char __user *optval, int __user *optlen)
{
	struct sock *sk = sock->sk;
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
	struct l2cap_chan *chan = l2cap_pi(sk)->chan;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct bt_security sec;
	struct bt_power pwr;
	int len, err = 0;

	BT_DBG("sk %p", sk);

	if (level == SOL_L2CAP)
		return l2cap_sock_getsockopt_old(sock, optname, optval, optlen);

	if (level != SOL_BLUETOOTH)
		return -ENOPROTOOPT;

	if (get_user(len, optlen))
		return -EFAULT;

	lock_sock(sk);

	switch (optname) {
	case BT_SECURITY:
<<<<<<< HEAD
		if (sk->sk_type != SOCK_SEQPACKET && sk->sk_type != SOCK_STREAM
				&& sk->sk_type != SOCK_RAW) {
=======
<<<<<<< HEAD
		if (sk->sk_type != SOCK_SEQPACKET && sk->sk_type != SOCK_STREAM
				&& sk->sk_type != SOCK_RAW) {
=======
		if (chan->chan_type != L2CAP_CHAN_CONN_ORIENTED &&
					chan->chan_type != L2CAP_CHAN_RAW) {
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			err = -EINVAL;
			break;
		}

		memset(&sec, 0, sizeof(sec));
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		sec.level = l2cap_pi(sk)->sec_level;

		if (sk->sk_state == BT_CONNECTED) {
			sec.key_size = l2cap_pi(sk)->conn->hcon->enc_key_size;
			sec.level = l2cap_pi(sk)->conn->hcon->sec_level;
		}
<<<<<<< HEAD
=======
=======
		sec.level = chan->sec_level;

		if (sk->sk_state == BT_CONNECTED)
			sec.key_size = chan->conn->hcon->enc_key_size;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

		len = min_t(unsigned int, len, sizeof(sec));
		if (copy_to_user(optval, (char *) &sec, len))
			err = -EFAULT;

		break;

	case BT_DEFER_SETUP:
		if (sk->sk_state != BT_BOUND && sk->sk_state != BT_LISTEN) {
			err = -EINVAL;
			break;
		}

		if (put_user(bt_sk(sk)->defer_setup, (u32 __user *) optval))
			err = -EFAULT;

		break;

<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
	case BT_FLUSHABLE:
		if (put_user(chan->flushable, (u32 __user *) optval))
			err = -EFAULT;

		break;

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	case BT_POWER:
		if (sk->sk_type != SOCK_SEQPACKET && sk->sk_type != SOCK_STREAM
				&& sk->sk_type != SOCK_RAW) {
			err = -EINVAL;
			break;
		}

<<<<<<< HEAD
		pwr.force_active = l2cap_pi(sk)->force_active;
=======
<<<<<<< HEAD
		pwr.force_active = l2cap_pi(sk)->force_active;
=======
		pwr.force_active = chan->force_active;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

		len = min_t(unsigned int, len, sizeof(pwr));
		if (copy_to_user(optval, (char *) &pwr, len))
			err = -EFAULT;

		break;

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	case BT_AMP_POLICY:
		if (put_user(l2cap_pi(sk)->amp_pref, (u32 __user *) optval))
			err = -EFAULT;
		break;

	case BT_LE_PARAMS:
		if (l2cap_pi(sk)->scid != L2CAP_CID_LE_DATA) {
			err = -EINVAL;
			break;
		}

		if (copy_to_user(optval, (char *) &bt_sk(sk)->le_params,
						sizeof(bt_sk(sk)->le_params)))
			err = -EFAULT;
		break;

<<<<<<< HEAD
=======
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	default:
		err = -ENOPROTOOPT;
		break;
	}

	release_sock(sk);
	return err;
}

static int l2cap_sock_setsockopt_old(struct socket *sock, int optname, char __user *optval, unsigned int optlen)
{
	struct sock *sk = sock->sk;
<<<<<<< HEAD
	struct l2cap_options opts;
	int len, le_sock, err = 0;
=======
<<<<<<< HEAD
	struct l2cap_options opts;
	int len, le_sock, err = 0;
=======
	struct l2cap_chan *chan = l2cap_pi(sk)->chan;
	struct l2cap_options opts;
	int len, err = 0;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	u32 opt;

	BT_DBG("sk %p", sk);

	lock_sock(sk);

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	le_sock = l2cap_pi(sk)->scid == L2CAP_CID_LE_DATA;

	switch (optname) {
	case L2CAP_OPTIONS:
		if (sk->sk_state == BT_CONNECTED && !le_sock) {
<<<<<<< HEAD
=======
=======
	switch (optname) {
	case L2CAP_OPTIONS:
		if (sk->sk_state == BT_CONNECTED) {
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			err = -EINVAL;
			break;
		}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		opts.imtu     = l2cap_pi(sk)->imtu;
		opts.omtu     = l2cap_pi(sk)->omtu;
		opts.flush_to = l2cap_pi(sk)->flush_to;
		opts.mode     = l2cap_pi(sk)->mode;
		opts.fcs      = l2cap_pi(sk)->fcs;
		opts.max_tx   = l2cap_pi(sk)->max_tx;
		opts.txwin_size = l2cap_pi(sk)->tx_win;
<<<<<<< HEAD
=======
=======
		opts.imtu     = chan->imtu;
		opts.omtu     = chan->omtu;
		opts.flush_to = chan->flush_to;
		opts.mode     = chan->mode;
		opts.fcs      = chan->fcs;
		opts.max_tx   = chan->max_tx;
		opts.txwin_size = (__u16)chan->tx_win;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

		len = min_t(unsigned int, sizeof(opts), optlen);
		if (copy_from_user((char *) &opts, optval, len)) {
			err = -EFAULT;
			break;
		}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		if ((opts.imtu || opts.omtu) && le_sock &&
				(sk->sk_state == BT_CONNECTED)) {
			if (opts.imtu >= L2CAP_LE_DEFAULT_MTU)
				l2cap_pi(sk)->imtu = opts.imtu;
			if (opts.omtu >= L2CAP_LE_DEFAULT_MTU)
				l2cap_pi(sk)->omtu = opts.omtu;
			if (opts.imtu < L2CAP_LE_DEFAULT_MTU ||
					opts.omtu < L2CAP_LE_DEFAULT_MTU)
				err = -EINVAL;
			break;
		}

		if (opts.txwin_size < 1 ||
			opts.txwin_size > L2CAP_TX_WIN_MAX_EXTENDED) {
<<<<<<< HEAD
=======
=======
		if (opts.txwin_size > L2CAP_DEFAULT_TX_WINDOW) {
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			err = -EINVAL;
			break;
		}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		l2cap_pi(sk)->mode = opts.mode;
		switch (l2cap_pi(sk)->mode) {
		case L2CAP_MODE_BASIC:
			l2cap_pi(sk)->conf_state &= ~L2CAP_CONF_STATE2_DEVICE;
			break;
		case L2CAP_MODE_STREAMING:
			if (!disable_ertm) {
				/* No fallback to ERTM or Basic mode */
				l2cap_pi(sk)->conf_state |=
						L2CAP_CONF_STATE2_DEVICE;
				break;
			}
			err = -EINVAL;
			break;
		case L2CAP_MODE_ERTM:
<<<<<<< HEAD
=======
=======
		chan->mode = opts.mode;
		switch (chan->mode) {
		case L2CAP_MODE_BASIC:
			clear_bit(CONF_STATE2_DEVICE, &chan->conf_state);
			break;
		case L2CAP_MODE_ERTM:
		case L2CAP_MODE_STREAMING:
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			if (!disable_ertm)
				break;
			/* fall through */
		default:
			err = -EINVAL;
			break;
		}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		l2cap_pi(sk)->imtu = opts.imtu;
		l2cap_pi(sk)->omtu = opts.omtu;
		l2cap_pi(sk)->fcs  = opts.fcs;
		l2cap_pi(sk)->max_tx = opts.max_tx;
		l2cap_pi(sk)->tx_win = opts.txwin_size;
		l2cap_pi(sk)->flush_to = opts.flush_to;
<<<<<<< HEAD
=======
=======
		chan->imtu = opts.imtu;
		chan->omtu = opts.omtu;
		chan->fcs  = opts.fcs;
		chan->max_tx = opts.max_tx;
		chan->tx_win = (__u8)opts.txwin_size;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		break;

	case L2CAP_LM:
		if (get_user(opt, (u32 __user *) optval)) {
			err = -EFAULT;
			break;
		}

		if (opt & L2CAP_LM_AUTH)
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			l2cap_pi(sk)->sec_level = BT_SECURITY_LOW;
		if (opt & L2CAP_LM_ENCRYPT)
			l2cap_pi(sk)->sec_level = BT_SECURITY_MEDIUM;
		if (opt & L2CAP_LM_SECURE)
			l2cap_pi(sk)->sec_level = BT_SECURITY_HIGH;

		l2cap_pi(sk)->role_switch    = (opt & L2CAP_LM_MASTER);
		l2cap_pi(sk)->force_reliable = (opt & L2CAP_LM_RELIABLE);
		l2cap_pi(sk)->flushable = (opt & L2CAP_LM_FLUSHABLE);
<<<<<<< HEAD
=======
=======
			chan->sec_level = BT_SECURITY_LOW;
		if (opt & L2CAP_LM_ENCRYPT)
			chan->sec_level = BT_SECURITY_MEDIUM;
		if (opt & L2CAP_LM_SECURE)
			chan->sec_level = BT_SECURITY_HIGH;

		chan->role_switch    = (opt & L2CAP_LM_MASTER);
		chan->force_reliable = (opt & L2CAP_LM_RELIABLE);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		break;

	default:
		err = -ENOPROTOOPT;
		break;
	}

	release_sock(sk);
	return err;
}

static int l2cap_sock_setsockopt(struct socket *sock, int level, int optname, char __user *optval, unsigned int optlen)
{
	struct sock *sk = sock->sk;
<<<<<<< HEAD
	struct bt_security sec;
	struct bt_power pwr;
	struct bt_le_params le_params;
=======
<<<<<<< HEAD
	struct bt_security sec;
	struct bt_power pwr;
	struct bt_le_params le_params;
=======
	struct l2cap_chan *chan = l2cap_pi(sk)->chan;
	struct bt_security sec;
	struct bt_power pwr;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct l2cap_conn *conn;
	int len, err = 0;
	u32 opt;

	BT_DBG("sk %p", sk);

	if (level == SOL_L2CAP)
		return l2cap_sock_setsockopt_old(sock, optname, optval, optlen);

	if (level != SOL_BLUETOOTH)
		return -ENOPROTOOPT;

	lock_sock(sk);

	switch (optname) {
	case BT_SECURITY:
<<<<<<< HEAD
		if (sk->sk_type != SOCK_SEQPACKET && sk->sk_type != SOCK_STREAM
				&& sk->sk_type != SOCK_RAW) {
=======
<<<<<<< HEAD
		if (sk->sk_type != SOCK_SEQPACKET && sk->sk_type != SOCK_STREAM
				&& sk->sk_type != SOCK_RAW) {
=======
		if (chan->chan_type != L2CAP_CHAN_CONN_ORIENTED &&
					chan->chan_type != L2CAP_CHAN_RAW) {
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			err = -EINVAL;
			break;
		}

		sec.level = BT_SECURITY_LOW;

		len = min_t(unsigned int, sizeof(sec), optlen);
		if (copy_from_user((char *) &sec, optval, len)) {
			err = -EFAULT;
			break;
		}

		if (sec.level < BT_SECURITY_LOW ||
					sec.level > BT_SECURITY_HIGH) {
			err = -EINVAL;
			break;
		}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		l2cap_pi(sk)->sec_level = sec.level;

		conn = l2cap_pi(sk)->conn;
		if (conn && l2cap_pi(sk)->scid == L2CAP_CID_LE_DATA) {
<<<<<<< HEAD
=======
=======
		chan->sec_level = sec.level;

		conn = chan->conn;
		if (conn && chan->scid == L2CAP_CID_LE_DATA) {
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			if (!conn->hcon->out) {
				err = -EINVAL;
				break;
			}

			if (smp_conn_security(conn, sec.level))
				break;

			err = 0;
			sk->sk_state = BT_CONFIG;
		}
		break;

	case BT_DEFER_SETUP:
		if (sk->sk_state != BT_BOUND && sk->sk_state != BT_LISTEN) {
			err = -EINVAL;
			break;
		}

		if (get_user(opt, (u32 __user *) optval)) {
			err = -EFAULT;
			break;
		}

		bt_sk(sk)->defer_setup = opt;
		break;

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	case BT_POWER:
		if (sk->sk_type != SOCK_SEQPACKET && sk->sk_type != SOCK_STREAM
				&& sk->sk_type != SOCK_RAW) {
			err = -EINVAL;
			break;
		}

		pwr.force_active = 1;

		len = min_t(unsigned int, sizeof(pwr), optlen);
		if (copy_from_user((char *) &pwr, optval, len)) {
			err = -EFAULT;
			break;
		}
		l2cap_pi(sk)->force_active = pwr.force_active;
		break;

	case BT_AMP_POLICY:
<<<<<<< HEAD
=======
=======
	case BT_FLUSHABLE:
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		if (get_user(opt, (u32 __user *) optval)) {
			err = -EFAULT;
			break;
		}

<<<<<<< HEAD
		if ((opt > BT_AMP_POLICY_PREFER_AMP) ||
			((l2cap_pi(sk)->mode != L2CAP_MODE_ERTM) &&
			 (l2cap_pi(sk)->mode != L2CAP_MODE_STREAMING))) {
=======
<<<<<<< HEAD
		if ((opt > BT_AMP_POLICY_PREFER_AMP) ||
			((l2cap_pi(sk)->mode != L2CAP_MODE_ERTM) &&
			 (l2cap_pi(sk)->mode != L2CAP_MODE_STREAMING))) {
=======
		if (opt > BT_FLUSHABLE_ON) {
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			err = -EINVAL;
			break;
		}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		l2cap_pi(sk)->amp_pref = (u8) opt;
		BT_DBG("BT_AMP_POLICY now %d", opt);

		if ((sk->sk_state == BT_CONNECTED) &&
			(l2cap_pi(sk)->amp_move_role == L2CAP_AMP_MOVE_NONE))
			l2cap_amp_move_init(sk);

		break;

	case BT_FLUSHABLE:
		if (get_user(opt, (u32 __user *) optval)) {
			err = -EFAULT;
			break;
		}
		l2cap_pi(sk)->flushable = opt;

		break;

	case BT_LE_PARAMS:
		if (l2cap_pi(sk)->scid != L2CAP_CID_LE_DATA) {
<<<<<<< HEAD
=======
=======
		if (opt == BT_FLUSHABLE_OFF) {
			struct l2cap_conn *conn = chan->conn;
			/* proceed further only when we have l2cap_conn and
			   No Flush support in the LM */
			if (!conn || !lmp_no_flush_capable(conn->hcon->hdev)) {
				err = -EINVAL;
				break;
			}
		}

		chan->flushable = opt;
		break;

	case BT_POWER:
		if (chan->chan_type != L2CAP_CHAN_CONN_ORIENTED &&
					chan->chan_type != L2CAP_CHAN_RAW) {
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			err = -EINVAL;
			break;
		}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		if (copy_from_user((char *) &le_params, optval,
					sizeof(struct bt_le_params))) {
			err = -EFAULT;
			break;
		}

		conn = l2cap_pi(sk)->conn;
		if (!conn || !conn->hcon ||
				l2cap_pi(sk)->scid != L2CAP_CID_LE_DATA) {
			memcpy(&bt_sk(sk)->le_params, &le_params,
							sizeof(le_params));
			break;
		}

		if (!conn->hcon->out ||
				!l2cap_sock_le_conn_update_params_valid(
					&le_params)) {
			err = -EINVAL;
			break;
		}

		memcpy(&bt_sk(sk)->le_params, &le_params, sizeof(le_params));

		hci_le_conn_update(conn->hcon,
				le_params.interval_min,
				le_params.interval_max,
				le_params.latency,
				le_params.supervision_timeout);
<<<<<<< HEAD
=======
=======
		pwr.force_active = BT_POWER_FORCE_ACTIVE_ON;

		len = min_t(unsigned int, sizeof(pwr), optlen);
		if (copy_from_user((char *) &pwr, optval, len)) {
			err = -EFAULT;
			break;
		}
		chan->force_active = pwr.force_active;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		break;

	default:
		err = -ENOPROTOOPT;
		break;
	}

	release_sock(sk);
	return err;
}

static int l2cap_sock_sendmsg(struct kiocb *iocb, struct socket *sock, struct msghdr *msg, size_t len)
{
	struct sock *sk = sock->sk;
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct l2cap_pinfo *pi = l2cap_pi(sk);
	struct sk_buff *skb;
	struct sk_buff_head seg_queue;
	int err;
	u8 amp_id;
<<<<<<< HEAD
=======
=======
	struct l2cap_chan *chan = l2cap_pi(sk)->chan;
	int err;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	BT_DBG("sock %p, sk %p", sock, sk);

	err = sock_error(sk);
	if (err)
		return err;

	if (msg->msg_flags & MSG_OOB)
		return -EOPNOTSUPP;

	lock_sock(sk);

	if (sk->sk_state != BT_CONNECTED) {
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		err = -ENOTCONN;
		goto done;
	}

	/* Connectionless channel */
	if (sk->sk_type == SOCK_DGRAM) {
		skb = l2cap_create_connless_pdu(sk, msg, len);
		if (IS_ERR(skb)) {
			err = PTR_ERR(skb);
		} else {
			l2cap_do_send(sk, skb);
			err = len;
		}
		goto done;
	}

	switch (pi->mode) {
	case L2CAP_MODE_BASIC:
		/* Check outgoing MTU */
		if (len > pi->omtu) {
			err = -EMSGSIZE;
			goto done;
		}

		/* Create a basic PDU */
		skb = l2cap_create_basic_pdu(sk, msg, len);
		if (IS_ERR(skb)) {
			err = PTR_ERR(skb);
			goto done;
		}

		l2cap_do_send(sk, skb);
		err = len;
		break;

	case L2CAP_MODE_ERTM:
	case L2CAP_MODE_STREAMING:

		/* Check outgoing MTU */
		if (len > pi->omtu) {
			err = -EMSGSIZE;
			goto done;
		}

		__skb_queue_head_init(&seg_queue);

		/* Do segmentation before calling in to the state machine,
		 * since it's possible to block while waiting for memory
		 * allocation.
		 */
		amp_id = pi->amp_id;
		err = l2cap_segment_sdu(sk, &seg_queue, msg, len, 0);

		/* The socket lock is released while segmenting, so check
		 * that the socket is still connected
		 */
		if (sk->sk_state != BT_CONNECTED) {
			__skb_queue_purge(&seg_queue);
			err = -ENOTCONN;
		}

		if (err) {
			BT_DBG("Error %d, sk_sndbuf %d, sk_wmem_alloc %d",
				err, sk->sk_sndbuf,
				atomic_read(&sk->sk_wmem_alloc));
			break;
		}

		if (pi->amp_id != amp_id) {
			/* Channel moved while unlocked. Resegment. */
			err = l2cap_resegment_queue(sk, &seg_queue);

			if (err)
				break;
		}

		if (pi->mode != L2CAP_MODE_STREAMING)
			err = l2cap_ertm_tx(sk, 0, &seg_queue,
				L2CAP_ERTM_EVENT_DATA_REQUEST);
		else
			err = l2cap_strm_tx(sk, &seg_queue);
		if (!err)
			err = len;

		/* If the skbs were not queued for sending, they'll still be in
		 * seg_queue and need to be purged.
		 */
		__skb_queue_purge(&seg_queue);
		break;

	default:
		BT_DBG("bad state %1.1x", pi->mode);
		err = -EBADFD;
	}

done:
<<<<<<< HEAD
=======
=======
		release_sock(sk);
		return -ENOTCONN;
	}

	err = l2cap_chan_send(chan, msg, len);

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	release_sock(sk);
	return err;
}

static int l2cap_sock_recvmsg(struct kiocb *iocb, struct socket *sock, struct msghdr *msg, size_t len, int flags)
{
	struct sock *sk = sock->sk;
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
	struct l2cap_pinfo *pi = l2cap_pi(sk);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int err;

	lock_sock(sk);

	if (sk->sk_state == BT_CONNECT2 && bt_sk(sk)->defer_setup) {
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		struct l2cap_conn_rsp rsp;
		struct l2cap_conn *conn = l2cap_pi(sk)->conn;
		u8 buf[128];

		if (l2cap_pi(sk)->amp_id) {
			/* Physical link must be brought up before connection
			 * completes.
			 */
			amp_accept_physical(conn, l2cap_pi(sk)->amp_id, sk);
			release_sock(sk);
			return 0;
		}

		sk->sk_state = BT_CONFIG;

		rsp.scid   = cpu_to_le16(l2cap_pi(sk)->dcid);
		rsp.dcid   = cpu_to_le16(l2cap_pi(sk)->scid);
		rsp.result = cpu_to_le16(L2CAP_CR_SUCCESS);
		rsp.status = cpu_to_le16(L2CAP_CS_NO_INFO);
		l2cap_send_cmd(l2cap_pi(sk)->conn, l2cap_pi(sk)->ident,
					L2CAP_CONN_RSP, sizeof(rsp), &rsp);

		if (l2cap_pi(sk)->conf_state & L2CAP_CONF_REQ_SENT) {
			release_sock(sk);
			return 0;
		}

		l2cap_pi(sk)->conf_state |= L2CAP_CONF_REQ_SENT;
		l2cap_send_cmd(conn, l2cap_get_ident(conn), L2CAP_CONF_REQ,
				l2cap_build_conf_req(sk, buf), buf);
		l2cap_pi(sk)->num_conf_req++;

<<<<<<< HEAD
=======
=======
		sk->sk_state = BT_CONFIG;

		__l2cap_connect_rsp_defer(pi->chan);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		release_sock(sk);
		return 0;
	}

	release_sock(sk);

	if (sock->type == SOCK_STREAM)
		err = bt_sock_stream_recvmsg(iocb, sock, msg, len, flags);
	else
		err = bt_sock_recvmsg(iocb, sock, msg, len, flags);

<<<<<<< HEAD
	if (err >= 0)
		l2cap_ertm_recv_done(sk);

=======
<<<<<<< HEAD
	if (err >= 0)
		l2cap_ertm_recv_done(sk);

=======
	if (pi->chan->mode != L2CAP_MODE_ERTM)
		return err;

	/* Attempt to put pending rx data in the socket buffer */

	lock_sock(sk);

	if (!test_bit(CONN_LOCAL_BUSY, &pi->chan->conn_state))
		goto done;

	if (pi->rx_busy_skb) {
		if (!sock_queue_rcv_skb(sk, pi->rx_busy_skb))
			pi->rx_busy_skb = NULL;
		else
			goto done;
	}

	/* Restore data flow when half of the receive buffer is
	 * available.  This avoids resending large numbers of
	 * frames.
	 */
	if (atomic_read(&sk->sk_rmem_alloc) <= sk->sk_rcvbuf >> 1)
		l2cap_chan_busy(pi->chan, 0);

done:
	release_sock(sk);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return err;
}

/* Kill socket (only if zapped and orphan)
 * Must be called on unlocked socket.
 */
<<<<<<< HEAD
void l2cap_sock_kill(struct sock *sk)
=======
<<<<<<< HEAD
void l2cap_sock_kill(struct sock *sk)
=======
static void l2cap_sock_kill(struct sock *sk)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	if (!sock_flag(sk, SOCK_ZAPPED) || sk->sk_socket)
		return;

	BT_DBG("sk %p state %d", sk, sk->sk_state);

	/* Kill poor orphan */
<<<<<<< HEAD
	bt_sock_unlink(&l2cap_sk_list, sk);
=======
<<<<<<< HEAD
	bt_sock_unlink(&l2cap_sk_list, sk);
=======

	l2cap_chan_destroy(l2cap_pi(sk)->chan);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	sock_set_flag(sk, SOCK_DEAD);
	sock_put(sk);
}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/* Must be called on unlocked socket. */
static void l2cap_sock_close(struct sock *sk)
{
	l2cap_sock_clear_timer(sk);
	lock_sock(sk);
	__l2cap_sock_close(sk, ECONNRESET);
	release_sock(sk);
	l2cap_sock_kill(sk);
}

static void l2cap_sock_cleanup_listen(struct sock *parent)
{
	struct sock *sk;

	BT_DBG("parent %p", parent);

	/* Close not yet accepted channels */
	while ((sk = bt_accept_dequeue(parent, NULL)))
		l2cap_sock_close(sk);

	parent->sk_state = BT_CLOSED;
	sock_set_flag(parent, SOCK_ZAPPED);
}

void __l2cap_sock_close(struct sock *sk, int reason)
{
	struct l2cap_conn *conn = l2cap_pi(sk)->conn;

	BT_DBG("sk %p state %d socket %p", sk, sk->sk_state, sk->sk_socket);

	switch (sk->sk_state) {
	case BT_LISTEN:
		l2cap_sock_cleanup_listen(sk);
		break;

	case BT_CONNECTED:
	case BT_CONFIG:
		if ((sk->sk_type == SOCK_SEQPACKET ||
					sk->sk_type == SOCK_STREAM) &&
					conn->hcon->type == ACL_LINK) {
			l2cap_sock_set_timer(sk, sk->sk_sndtimeo);
			l2cap_send_disconn_req(conn, sk, reason);
		} else
			l2cap_chan_del(sk, reason);
		break;

	case BT_CONNECT2:
		if ((sk->sk_type == SOCK_SEQPACKET ||
					sk->sk_type == SOCK_STREAM) &&
					conn->hcon->type == ACL_LINK) {
			struct l2cap_conn_rsp rsp;
			__u16 result;

			if (bt_sk(sk)->defer_setup)
				result = L2CAP_CR_SEC_BLOCK;
			else
				result = L2CAP_CR_BAD_PSM;
			sk->sk_state = BT_DISCONN;

			rsp.scid   = cpu_to_le16(l2cap_pi(sk)->dcid);
			rsp.dcid   = cpu_to_le16(l2cap_pi(sk)->scid);
			rsp.result = cpu_to_le16(result);
			rsp.status = cpu_to_le16(L2CAP_CS_NO_INFO);
			l2cap_send_cmd(conn, l2cap_pi(sk)->ident,
					L2CAP_CONN_RSP, sizeof(rsp), &rsp);
		}

		l2cap_chan_del(sk, reason);
		break;

	case BT_CONNECT:
	case BT_DISCONN:
		l2cap_chan_del(sk, reason);
		break;

	default:
		sock_set_flag(sk, SOCK_ZAPPED);
		break;
	}
}

static int l2cap_sock_shutdown(struct socket *sock, int how)
{
	struct sock *sk = sock->sk;
<<<<<<< HEAD
=======
=======
static int l2cap_sock_shutdown(struct socket *sock, int how)
{
	struct sock *sk = sock->sk;
	struct l2cap_chan *chan = l2cap_pi(sk)->chan;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int err = 0;

	BT_DBG("sock %p, sk %p", sock, sk);

	if (!sk)
		return 0;

	lock_sock(sk);
	if (!sk->sk_shutdown) {
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

		if (l2cap_pi(sk)->mode == L2CAP_MODE_ERTM) {
			err = __l2cap_wait_ack(sk);
			l2cap_ertm_shutdown(sk);
		}

		sk->sk_shutdown = SHUTDOWN_MASK;
		l2cap_sock_clear_timer(sk);
		__l2cap_sock_close(sk, 0);
<<<<<<< HEAD
=======
=======
		if (chan->mode == L2CAP_MODE_ERTM)
			err = __l2cap_wait_ack(sk);

		sk->sk_shutdown = SHUTDOWN_MASK;
		l2cap_chan_close(chan, 0);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

		if (sock_flag(sk, SOCK_LINGER) && sk->sk_lingertime)
			err = bt_sock_wait_state(sk, BT_CLOSED,
							sk->sk_lingertime);
	}

	if (!err && sk->sk_err)
		err = -sk->sk_err;

	release_sock(sk);
	return err;
}

static int l2cap_sock_release(struct socket *sock)
{
	struct sock *sk = sock->sk;
<<<<<<< HEAD
	struct sock *sk2 = NULL;
=======
<<<<<<< HEAD
	struct sock *sk2 = NULL;
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int err;

	BT_DBG("sock %p, sk %p", sock, sk);

	if (!sk)
		return 0;

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	/* If this is an ATT socket, find it's matching server/client */
	if (l2cap_pi(sk)->scid == L2CAP_CID_LE_DATA)
		sk2 = l2cap_find_sock_by_fixed_cid_and_dir(L2CAP_CID_LE_DATA,
					&bt_sk(sk)->src, &bt_sk(sk)->dst,
					l2cap_pi(sk)->incoming ? 0 : 1);

	/* If matching socket found, request tear down */
	BT_DBG("sock:%p companion:%p", sk, sk2);
	if (sk2)
		l2cap_sock_set_timer(sk2, 1);

<<<<<<< HEAD
=======
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	err = l2cap_sock_shutdown(sock, 2);

	sock_orphan(sk);
	l2cap_sock_kill(sk);
	return err;
}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static void l2cap_sock_destruct(struct sock *sk)
{
	BT_DBG("sk %p", sk);

	skb_queue_purge(&sk->sk_receive_queue);
	skb_queue_purge(&sk->sk_write_queue);

	l2cap_ertm_destruct(sk);
}

static void set_default_config(struct l2cap_conf_prm *conf_prm)
{
	conf_prm->fcs = L2CAP_FCS_CRC16;
	conf_prm->flush_to = L2CAP_DEFAULT_FLUSH_TO;
}

void l2cap_sock_init(struct sock *sk, struct sock *parent)
{
	struct l2cap_pinfo *pi = l2cap_pi(sk);

	BT_DBG("sk %p parent %p", sk, parent);

	if (parent) {
		sk->sk_type = parent->sk_type;
		sk->sk_rcvbuf = parent->sk_rcvbuf;
		sk->sk_sndbuf = parent->sk_sndbuf;
		bt_sk(sk)->defer_setup = bt_sk(parent)->defer_setup;

		pi->imtu = l2cap_pi(parent)->imtu;
		pi->omtu = l2cap_pi(parent)->omtu;
		pi->conf_state = l2cap_pi(parent)->conf_state;
		pi->mode = l2cap_pi(parent)->mode;
		pi->fcs  = l2cap_pi(parent)->fcs;
		pi->max_tx = l2cap_pi(parent)->max_tx;
		pi->tx_win = l2cap_pi(parent)->tx_win;
		pi->sec_level = l2cap_pi(parent)->sec_level;
		pi->role_switch = l2cap_pi(parent)->role_switch;
		pi->force_reliable = l2cap_pi(parent)->force_reliable;
		pi->flushable = l2cap_pi(parent)->flushable;
		pi->force_active = l2cap_pi(parent)->force_active;
		pi->amp_pref = l2cap_pi(parent)->amp_pref;
	} else {
		pi->imtu = L2CAP_DEFAULT_MTU;
		pi->omtu = 0;
		if (!disable_ertm && sk->sk_type == SOCK_STREAM) {
			pi->mode = L2CAP_MODE_ERTM;
			pi->conf_state |= L2CAP_CONF_STATE2_DEVICE;
		} else {
			pi->mode = L2CAP_MODE_BASIC;
		}
		pi->reconf_state = L2CAP_RECONF_NONE;
		pi->max_tx = L2CAP_DEFAULT_MAX_TX;
		pi->fcs = L2CAP_FCS_CRC16;
		pi->tx_win = L2CAP_DEFAULT_TX_WINDOW;
		pi->sec_level = BT_SECURITY_LOW;
		pi->role_switch = 0;
		pi->force_reliable = 0;
		pi->flushable = 0;
		pi->force_active = 1;
		pi->amp_pref = BT_AMP_POLICY_REQUIRE_BR_EDR;
	}

	/* Default config options */
	sk->sk_backlog_rcv = l2cap_data_channel;
	pi->ampcon = NULL;
	pi->ampchan = NULL;
	pi->conf_len = 0;
	pi->flush_to = L2CAP_DEFAULT_FLUSH_TO;
	pi->scid = 0;
	pi->dcid = 0;
	pi->tx_win_max = L2CAP_TX_WIN_MAX_ENHANCED;
	pi->ack_win = pi->tx_win;
	pi->extended_control = 0;

	pi->local_conf.fcs = pi->fcs;
	pi->local_conf.flush_to = pi->flush_to;

	set_default_config(&pi->remote_conf);

	skb_queue_head_init(TX_QUEUE(sk));
	skb_queue_head_init(SREJ_QUEUE(sk));
<<<<<<< HEAD
=======
=======
static struct l2cap_chan *l2cap_sock_new_connection_cb(void *data)
{
	struct sock *sk, *parent = data;

	sk = l2cap_sock_alloc(sock_net(parent), NULL, BTPROTO_L2CAP,
								GFP_ATOMIC);
	if (!sk)
		return NULL;

	l2cap_sock_init(sk, parent);

	return l2cap_pi(sk)->chan;
}

static int l2cap_sock_recv_cb(void *data, struct sk_buff *skb)
{
	int err;
	struct sock *sk = data;
	struct l2cap_pinfo *pi = l2cap_pi(sk);

	if (pi->rx_busy_skb)
		return -ENOMEM;

	err = sock_queue_rcv_skb(sk, skb);

	/* For ERTM, handle one skb that doesn't fit into the recv
	 * buffer.  This is important to do because the data frames
	 * have already been acked, so the skb cannot be discarded.
	 *
	 * Notify the l2cap core that the buffer is full, so the
	 * LOCAL_BUSY state is entered and no more frames are
	 * acked and reassembled until there is buffer space
	 * available.
	 */
	if (err < 0 && pi->chan->mode == L2CAP_MODE_ERTM) {
		pi->rx_busy_skb = skb;
		l2cap_chan_busy(pi->chan, 1);
		err = 0;
	}

	return err;
}

static void l2cap_sock_close_cb(void *data)
{
	struct sock *sk = data;

	l2cap_sock_kill(sk);
}

static void l2cap_sock_state_change_cb(void *data, int state)
{
	struct sock *sk = data;

	sk->sk_state = state;
}

static struct l2cap_ops l2cap_chan_ops = {
	.name		= "L2CAP Socket Interface",
	.new_connection	= l2cap_sock_new_connection_cb,
	.recv		= l2cap_sock_recv_cb,
	.close		= l2cap_sock_close_cb,
	.state_change	= l2cap_sock_state_change_cb,
};

static void l2cap_sock_destruct(struct sock *sk)
{
	BT_DBG("sk %p", sk);

	if (l2cap_pi(sk)->rx_busy_skb) {
		kfree_skb(l2cap_pi(sk)->rx_busy_skb);
		l2cap_pi(sk)->rx_busy_skb = NULL;
	}

	skb_queue_purge(&sk->sk_receive_queue);
	skb_queue_purge(&sk->sk_write_queue);
}

static void l2cap_sock_init(struct sock *sk, struct sock *parent)
{
	struct l2cap_pinfo *pi = l2cap_pi(sk);
	struct l2cap_chan *chan = pi->chan;

	BT_DBG("sk %p", sk);

	if (parent) {
		struct l2cap_chan *pchan = l2cap_pi(parent)->chan;

		sk->sk_type = parent->sk_type;
		bt_sk(sk)->defer_setup = bt_sk(parent)->defer_setup;

		chan->chan_type = pchan->chan_type;
		chan->imtu = pchan->imtu;
		chan->omtu = pchan->omtu;
		chan->conf_state = pchan->conf_state;
		chan->mode = pchan->mode;
		chan->fcs  = pchan->fcs;
		chan->max_tx = pchan->max_tx;
		chan->tx_win = pchan->tx_win;
		chan->sec_level = pchan->sec_level;
		chan->role_switch = pchan->role_switch;
		chan->force_reliable = pchan->force_reliable;
		chan->flushable = pchan->flushable;
		chan->force_active = pchan->force_active;
	} else {

		switch (sk->sk_type) {
		case SOCK_RAW:
			chan->chan_type = L2CAP_CHAN_RAW;
			break;
		case SOCK_DGRAM:
			chan->chan_type = L2CAP_CHAN_CONN_LESS;
			break;
		case SOCK_SEQPACKET:
		case SOCK_STREAM:
			chan->chan_type = L2CAP_CHAN_CONN_ORIENTED;
			break;
		}

		chan->imtu = L2CAP_DEFAULT_MTU;
		chan->omtu = 0;
		if (!disable_ertm && sk->sk_type == SOCK_STREAM) {
			chan->mode = L2CAP_MODE_ERTM;
			set_bit(CONF_STATE2_DEVICE, &chan->conf_state);
		} else {
			chan->mode = L2CAP_MODE_BASIC;
		}
		chan->max_tx = L2CAP_DEFAULT_MAX_TX;
		chan->fcs  = L2CAP_FCS_CRC16;
		chan->tx_win = L2CAP_DEFAULT_TX_WINDOW;
		chan->sec_level = BT_SECURITY_LOW;
		chan->role_switch = 0;
		chan->force_reliable = 0;
		chan->flushable = BT_FLUSHABLE_OFF;
		chan->force_active = BT_POWER_FORCE_ACTIVE_ON;

	}

	/* Default config options */
	chan->flush_to = L2CAP_DEFAULT_FLUSH_TO;

	chan->data = sk;
	chan->ops = &l2cap_chan_ops;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static struct proto l2cap_proto = {
	.name		= "L2CAP",
	.owner		= THIS_MODULE,
	.obj_size	= sizeof(struct l2cap_pinfo)
};

<<<<<<< HEAD
struct sock *l2cap_sock_alloc(struct net *net, struct socket *sock, int proto, gfp_t prio)
{
	struct sock *sk;
=======
<<<<<<< HEAD
struct sock *l2cap_sock_alloc(struct net *net, struct socket *sock, int proto, gfp_t prio)
{
	struct sock *sk;
=======
static struct sock *l2cap_sock_alloc(struct net *net, struct socket *sock, int proto, gfp_t prio)
{
	struct sock *sk;
	struct l2cap_chan *chan;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	sk = sk_alloc(net, PF_BLUETOOTH, prio, &l2cap_proto);
	if (!sk)
		return NULL;

	sock_init_data(sock, sk);
	INIT_LIST_HEAD(&bt_sk(sk)->accept_q);

	sk->sk_destruct = l2cap_sock_destruct;
<<<<<<< HEAD
	sk->sk_sndtimeo = msecs_to_jiffies(L2CAP_CONN_TIMEOUT);
=======
<<<<<<< HEAD
	sk->sk_sndtimeo = msecs_to_jiffies(L2CAP_CONN_TIMEOUT);
=======
	sk->sk_sndtimeo = L2CAP_CONN_TIMEOUT;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	sock_reset_flag(sk, SOCK_ZAPPED);

	sk->sk_protocol = proto;
	sk->sk_state = BT_OPEN;

<<<<<<< HEAD
	setup_timer(&sk->sk_timer, l2cap_sock_timeout, (unsigned long) sk);

	bt_sock_link(&l2cap_sk_list, sk);
=======
<<<<<<< HEAD
	setup_timer(&sk->sk_timer, l2cap_sock_timeout, (unsigned long) sk);

	bt_sock_link(&l2cap_sk_list, sk);
=======
	chan = l2cap_chan_create(sk);
	if (!chan) {
		l2cap_sock_kill(sk);
		return NULL;
	}

	l2cap_pi(sk)->chan = chan;

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return sk;
}

static int l2cap_sock_create(struct net *net, struct socket *sock, int protocol,
			     int kern)
{
	struct sock *sk;

	BT_DBG("sock %p", sock);

	sock->state = SS_UNCONNECTED;

	if (sock->type != SOCK_SEQPACKET && sock->type != SOCK_STREAM &&
			sock->type != SOCK_DGRAM && sock->type != SOCK_RAW)
		return -ESOCKTNOSUPPORT;

	if (sock->type == SOCK_RAW && !kern && !capable(CAP_NET_RAW))
		return -EPERM;

	sock->ops = &l2cap_sock_ops;

	sk = l2cap_sock_alloc(net, sock, protocol, GFP_ATOMIC);
	if (!sk)
		return -ENOMEM;

	l2cap_sock_init(sk, NULL);
	return 0;
}

<<<<<<< HEAD
const struct proto_ops l2cap_sock_ops = {
=======
<<<<<<< HEAD
const struct proto_ops l2cap_sock_ops = {
=======
static const struct proto_ops l2cap_sock_ops = {
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	.family		= PF_BLUETOOTH,
	.owner		= THIS_MODULE,
	.release	= l2cap_sock_release,
	.bind		= l2cap_sock_bind,
	.connect	= l2cap_sock_connect,
	.listen		= l2cap_sock_listen,
	.accept		= l2cap_sock_accept,
	.getname	= l2cap_sock_getname,
	.sendmsg	= l2cap_sock_sendmsg,
	.recvmsg	= l2cap_sock_recvmsg,
	.poll		= bt_sock_poll,
	.ioctl		= bt_sock_ioctl,
	.mmap		= sock_no_mmap,
	.socketpair	= sock_no_socketpair,
	.shutdown	= l2cap_sock_shutdown,
	.setsockopt	= l2cap_sock_setsockopt,
	.getsockopt	= l2cap_sock_getsockopt
};

static const struct net_proto_family l2cap_sock_family_ops = {
	.family	= PF_BLUETOOTH,
	.owner	= THIS_MODULE,
	.create	= l2cap_sock_create,
};

int __init l2cap_init_sockets(void)
{
	int err;

	err = proto_register(&l2cap_proto, 0);
	if (err < 0)
		return err;

	err = bt_sock_register(BTPROTO_L2CAP, &l2cap_sock_family_ops);
	if (err < 0)
		goto error;

	BT_INFO("L2CAP socket layer initialized");

	return 0;

error:
	BT_ERR("L2CAP socket registration failed");
	proto_unregister(&l2cap_proto);
	return err;
}

void l2cap_cleanup_sockets(void)
{
	if (bt_sock_unregister(BTPROTO_L2CAP) < 0)
		BT_ERR("L2CAP socket unregistration failed");

	proto_unregister(&l2cap_proto);
}
