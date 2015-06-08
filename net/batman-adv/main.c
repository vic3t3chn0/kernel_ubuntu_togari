/*
<<<<<<< HEAD
 * Copyright (C) 2007-2012 B.A.T.M.A.N. contributors:
=======
<<<<<<< HEAD
 * Copyright (C) 2007-2012 B.A.T.M.A.N. contributors:
=======
 * Copyright (C) 2007-2011 B.A.T.M.A.N. contributors:
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * Marek Lindner, Simon Wunderlich
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA
 *
 */

#include "main.h"
#include "bat_sysfs.h"
#include "bat_debugfs.h"
#include "routing.h"
#include "send.h"
#include "originator.h"
#include "soft-interface.h"
#include "icmp_socket.h"
#include "translation-table.h"
#include "hard-interface.h"
#include "gateway_client.h"
#include "vis.h"
#include "hash.h"
<<<<<<< HEAD
#include "bat_algo.h"
=======
<<<<<<< HEAD
#include "bat_algo.h"
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2


/* List manipulations on hardif_list have to be rtnl_lock()'ed,
 * list traversals just rcu-locked */
struct list_head hardif_list;
<<<<<<< HEAD
char bat_routing_algo[20] = "BATMAN IV";
static struct hlist_head bat_algo_list;
=======
<<<<<<< HEAD
char bat_routing_algo[20] = "BATMAN IV";
static struct hlist_head bat_algo_list;
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

unsigned char broadcast_addr[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

struct workqueue_struct *bat_event_workqueue;

static int __init batman_init(void)
{
	INIT_LIST_HEAD(&hardif_list);
<<<<<<< HEAD
	INIT_HLIST_HEAD(&bat_algo_list);

	bat_iv_init();
=======
<<<<<<< HEAD
	INIT_HLIST_HEAD(&bat_algo_list);

	bat_iv_init();
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	/* the name should not be longer than 10 chars - see
	 * http://lwn.net/Articles/23634/ */
	bat_event_workqueue = create_singlethread_workqueue("bat_events");

	if (!bat_event_workqueue)
		return -ENOMEM;

	bat_socket_init();
	debugfs_init();

	register_netdevice_notifier(&hard_if_notifier);

<<<<<<< HEAD
	pr_info("B.A.T.M.A.N. advanced %s (compatibility version %i) loaded\n",
		SOURCE_VERSION, COMPAT_VERSION);
=======
<<<<<<< HEAD
	pr_info("B.A.T.M.A.N. advanced %s (compatibility version %i) loaded\n",
		SOURCE_VERSION, COMPAT_VERSION);
=======
	pr_info("B.A.T.M.A.N. advanced %s%s (compatibility version %i) "
		"loaded\n", SOURCE_VERSION, REVISION_VERSION_STR,
		COMPAT_VERSION);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return 0;
}

static void __exit batman_exit(void)
{
	debugfs_destroy();
	unregister_netdevice_notifier(&hard_if_notifier);
	hardif_remove_interfaces();

	flush_workqueue(bat_event_workqueue);
	destroy_workqueue(bat_event_workqueue);
	bat_event_workqueue = NULL;

	rcu_barrier();
}

int mesh_init(struct net_device *soft_iface)
{
	struct bat_priv *bat_priv = netdev_priv(soft_iface);

	spin_lock_init(&bat_priv->forw_bat_list_lock);
	spin_lock_init(&bat_priv->forw_bcast_list_lock);
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	spin_lock_init(&bat_priv->tt_changes_list_lock);
	spin_lock_init(&bat_priv->tt_req_list_lock);
	spin_lock_init(&bat_priv->tt_roam_list_lock);
	spin_lock_init(&bat_priv->tt_buff_lock);
<<<<<<< HEAD
=======
=======
	spin_lock_init(&bat_priv->tt_lhash_lock);
	spin_lock_init(&bat_priv->tt_ghash_lock);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	spin_lock_init(&bat_priv->gw_list_lock);
	spin_lock_init(&bat_priv->vis_hash_lock);
	spin_lock_init(&bat_priv->vis_list_lock);
	spin_lock_init(&bat_priv->softif_neigh_lock);
	spin_lock_init(&bat_priv->softif_neigh_vid_lock);

	INIT_HLIST_HEAD(&bat_priv->forw_bat_list);
	INIT_HLIST_HEAD(&bat_priv->forw_bcast_list);
	INIT_HLIST_HEAD(&bat_priv->gw_list);
	INIT_HLIST_HEAD(&bat_priv->softif_neigh_vids);
<<<<<<< HEAD
	INIT_LIST_HEAD(&bat_priv->tt_changes_list);
	INIT_LIST_HEAD(&bat_priv->tt_req_list);
	INIT_LIST_HEAD(&bat_priv->tt_roam_list);
=======
<<<<<<< HEAD
	INIT_LIST_HEAD(&bat_priv->tt_changes_list);
	INIT_LIST_HEAD(&bat_priv->tt_req_list);
	INIT_LIST_HEAD(&bat_priv->tt_roam_list);
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (originator_init(bat_priv) < 1)
		goto err;

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (tt_init(bat_priv) < 1)
		goto err;

	tt_local_add(soft_iface, soft_iface->dev_addr, NULL_IFINDEX);
<<<<<<< HEAD
=======
=======
	if (tt_local_init(bat_priv) < 1)
		goto err;

	if (tt_global_init(bat_priv) < 1)
		goto err;

	tt_local_add(soft_iface, soft_iface->dev_addr);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (vis_init(bat_priv) < 1)
		goto err;

<<<<<<< HEAD
	atomic_set(&bat_priv->gw_reselect, 0);
=======
<<<<<<< HEAD
	atomic_set(&bat_priv->gw_reselect, 0);
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	atomic_set(&bat_priv->mesh_state, MESH_ACTIVE);
	goto end;

err:
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
	pr_err("Unable to allocate memory for mesh information structures: "
	       "out of mem ?\n");
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	mesh_free(soft_iface);
	return -1;

end:
	return 0;
}

void mesh_free(struct net_device *soft_iface)
{
	struct bat_priv *bat_priv = netdev_priv(soft_iface);

	atomic_set(&bat_priv->mesh_state, MESH_DEACTIVATING);

	purge_outstanding_packets(bat_priv, NULL);

	vis_quit(bat_priv);

	gw_node_purge(bat_priv);
	originator_free(bat_priv);

<<<<<<< HEAD
	tt_free(bat_priv);
=======
<<<<<<< HEAD
	tt_free(bat_priv);
=======
	tt_local_free(bat_priv);
	tt_global_free(bat_priv);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	softif_neigh_purge(bat_priv);

	atomic_set(&bat_priv->mesh_state, MESH_INACTIVE);
}

void inc_module_count(void)
{
	try_module_get(THIS_MODULE);
}

void dec_module_count(void)
{
	module_put(THIS_MODULE);
}

<<<<<<< HEAD
int is_my_mac(const uint8_t *addr)
{
	const struct hard_iface *hard_iface;
=======
<<<<<<< HEAD
int is_my_mac(const uint8_t *addr)
{
	const struct hard_iface *hard_iface;
=======
int is_my_mac(uint8_t *addr)
{
	struct hard_iface *hard_iface;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	rcu_read_lock();
	list_for_each_entry_rcu(hard_iface, &hardif_list, list) {
		if (hard_iface->if_status != IF_ACTIVE)
			continue;

		if (compare_eth(hard_iface->net_dev->dev_addr, addr)) {
			rcu_read_unlock();
			return 1;
		}
	}
	rcu_read_unlock();
	return 0;
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static struct bat_algo_ops *bat_algo_get(char *name)
{
	struct bat_algo_ops *bat_algo_ops = NULL, *bat_algo_ops_tmp;
	struct hlist_node *node;

	hlist_for_each_entry(bat_algo_ops_tmp, node, &bat_algo_list, list) {
		if (strcmp(bat_algo_ops_tmp->name, name) != 0)
			continue;

		bat_algo_ops = bat_algo_ops_tmp;
		break;
	}

	return bat_algo_ops;
}

int bat_algo_register(struct bat_algo_ops *bat_algo_ops)
{
	struct bat_algo_ops *bat_algo_ops_tmp;
	int ret = -1;

	bat_algo_ops_tmp = bat_algo_get(bat_algo_ops->name);
	if (bat_algo_ops_tmp) {
		pr_info("Trying to register already registered routing algorithm: %s\n",
			bat_algo_ops->name);
		goto out;
	}

	/* all algorithms must implement all ops (for now) */
	if (!bat_algo_ops->bat_ogm_init ||
	    !bat_algo_ops->bat_ogm_init_primary ||
	    !bat_algo_ops->bat_ogm_update_mac ||
	    !bat_algo_ops->bat_ogm_schedule ||
	    !bat_algo_ops->bat_ogm_emit ||
	    !bat_algo_ops->bat_ogm_receive) {
		pr_info("Routing algo '%s' does not implement required ops\n",
			bat_algo_ops->name);
		goto out;
	}

	INIT_HLIST_NODE(&bat_algo_ops->list);
	hlist_add_head(&bat_algo_ops->list, &bat_algo_list);
	ret = 0;

out:
	return ret;
}

int bat_algo_select(struct bat_priv *bat_priv, char *name)
{
	struct bat_algo_ops *bat_algo_ops;
	int ret = -1;

	bat_algo_ops = bat_algo_get(name);
	if (!bat_algo_ops)
		goto out;

	bat_priv->bat_algo_ops = bat_algo_ops;
	ret = 0;

out:
	return ret;
}

int bat_algo_seq_print_text(struct seq_file *seq, void *offset)
{
	struct bat_algo_ops *bat_algo_ops;
	struct hlist_node *node;

	seq_printf(seq, "Available routing algorithms:\n");

	hlist_for_each_entry(bat_algo_ops, node, &bat_algo_list, list) {
		seq_printf(seq, "%s\n", bat_algo_ops->name);
	}

	return 0;
}

static int param_set_ra(const char *val, const struct kernel_param *kp)
{
	struct bat_algo_ops *bat_algo_ops;

	bat_algo_ops = bat_algo_get((char *)val);
	if (!bat_algo_ops) {
		pr_err("Routing algorithm '%s' is not supported\n", val);
		return -EINVAL;
	}

	return param_set_copystring(val, kp);
}

static const struct kernel_param_ops param_ops_ra = {
	.set = param_set_ra,
	.get = param_get_string,
};

static struct kparam_string __param_string_ra = {
	.maxlen = sizeof(bat_routing_algo),
	.string = bat_routing_algo,
};

module_param_cb(routing_algo, &param_ops_ra, &__param_string_ra, 0644);
<<<<<<< HEAD
=======
=======

}

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
module_init(batman_init);
module_exit(batman_exit);

MODULE_LICENSE("GPL");

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_SUPPORTED_DEVICE(DRIVER_DEVICE);
<<<<<<< HEAD
MODULE_VERSION(SOURCE_VERSION);
=======
<<<<<<< HEAD
MODULE_VERSION(SOURCE_VERSION);
=======
#ifdef REVISION_VERSION
MODULE_VERSION(SOURCE_VERSION "-" REVISION_VERSION);
#else
MODULE_VERSION(SOURCE_VERSION);
#endif
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
