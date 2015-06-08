/*
 * linux/include/linux/sunrpc/stats.h
 *
 * Client statistics collection for SUN RPC
 *
 * Copyright (C) 1996 Olaf Kirch <okir@monad.swb.de>
 */

#ifndef _LINUX_SUNRPC_STATS_H
#define _LINUX_SUNRPC_STATS_H

#include <linux/proc_fs.h>

struct rpc_stat {
<<<<<<< HEAD
	const struct rpc_program *program;
=======
<<<<<<< HEAD
	const struct rpc_program *program;
=======
	struct rpc_program *	program;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	unsigned int		netcnt,
				netudpcnt,
				nettcpcnt,
				nettcpconn,
				netreconn;
	unsigned int		rpccnt,
				rpcretrans,
				rpcauthrefresh,
				rpcgarbage;
};

struct svc_stat {
	struct svc_program *	program;

	unsigned int		netcnt,
				netudpcnt,
				nettcpcnt,
				nettcpconn;
	unsigned int		rpccnt,
				rpcbadfmt,
				rpcbadauth,
				rpcbadclnt;
};

struct net;
#ifdef CONFIG_PROC_FS
int			rpc_proc_init(struct net *);
void			rpc_proc_exit(struct net *);
#else
static inline int rpc_proc_init(struct net *net)
{
	return 0;
}

static inline void rpc_proc_exit(struct net *net)
{
}
#endif

#ifdef MODULE
void			rpc_modcount(struct inode *, int);
#endif

#ifdef CONFIG_PROC_FS
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
struct proc_dir_entry *	rpc_proc_register(struct net *,struct rpc_stat *);
void			rpc_proc_unregister(struct net *,const char *);
void			rpc_proc_zero(const struct rpc_program *);
struct proc_dir_entry *	svc_proc_register(struct net *, struct svc_stat *,
					  const struct file_operations *);
void			svc_proc_unregister(struct net *, const char *);
<<<<<<< HEAD
=======
=======
struct proc_dir_entry *	rpc_proc_register(struct rpc_stat *);
void			rpc_proc_unregister(const char *);
void			rpc_proc_zero(struct rpc_program *);
struct proc_dir_entry *	svc_proc_register(struct svc_stat *,
					  const struct file_operations *);
void			svc_proc_unregister(const char *);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

void			svc_seq_show(struct seq_file *,
				     const struct svc_stat *);
#else

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static inline struct proc_dir_entry *rpc_proc_register(struct net *net, struct rpc_stat *s) { return NULL; }
static inline void rpc_proc_unregister(struct net *net, const char *p) {}
static inline void rpc_proc_zero(const struct rpc_program *p) {}

static inline struct proc_dir_entry *svc_proc_register(struct net *net, struct svc_stat *s,
						       const struct file_operations *f) { return NULL; }
static inline void svc_proc_unregister(struct net *net, const char *p) {}
<<<<<<< HEAD
=======
=======
static inline struct proc_dir_entry *rpc_proc_register(struct rpc_stat *s) { return NULL; }
static inline void rpc_proc_unregister(const char *p) {}
static inline void rpc_proc_zero(struct rpc_program *p) {}

static inline struct proc_dir_entry *svc_proc_register(struct svc_stat *s,
						       const struct file_operations *f) { return NULL; }
static inline void svc_proc_unregister(const char *p) {}
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

static inline void svc_seq_show(struct seq_file *seq,
				const struct svc_stat *st) {}
#endif

#endif /* _LINUX_SUNRPC_STATS_H */
