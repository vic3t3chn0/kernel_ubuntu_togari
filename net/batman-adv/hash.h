/*
<<<<<<< HEAD
 * Copyright (C) 2006-2012 B.A.T.M.A.N. contributors:
=======
<<<<<<< HEAD
 * Copyright (C) 2006-2012 B.A.T.M.A.N. contributors:
=======
 * Copyright (C) 2006-2011 B.A.T.M.A.N. contributors:
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * Simon Wunderlich, Marek Lindner
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

#ifndef _NET_BATMAN_ADV_HASH_H_
#define _NET_BATMAN_ADV_HASH_H_

#include <linux/list.h>

/* callback to a compare function.  should
 * compare 2 element datas for their keys,
 * return 0 if same and not 0 if not
 * same */
<<<<<<< HEAD
typedef int (*hashdata_compare_cb)(const struct hlist_node *, const void *);
=======
<<<<<<< HEAD
typedef int (*hashdata_compare_cb)(const struct hlist_node *, const void *);
=======
typedef int (*hashdata_compare_cb)(struct hlist_node *, void *);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/* the hashfunction, should return an index
 * based on the key in the data of the first
 * argument and the size the second */
<<<<<<< HEAD
typedef uint32_t (*hashdata_choose_cb)(const void *, uint32_t);
=======
<<<<<<< HEAD
typedef uint32_t (*hashdata_choose_cb)(const void *, uint32_t);
=======
typedef int (*hashdata_choose_cb)(void *, int);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
typedef void (*hashdata_free_cb)(struct hlist_node *, void *);

struct hashtable_t {
	struct hlist_head *table;   /* the hashtable itself with the buckets */
	spinlock_t *list_locks;     /* spinlock for each hash list entry */
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	uint32_t size;		    /* size of hashtable */
};

/* allocates and clears the hash */
struct hashtable_t *hash_new(uint32_t size);
<<<<<<< HEAD
=======
=======
	int size;		    /* size of hashtable */
};

/* allocates and clears the hash */
struct hashtable_t *hash_new(int size);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/* free only the hashtable and the hash itself. */
void hash_destroy(struct hashtable_t *hash);

/* remove the hash structure. if hashdata_free_cb != NULL, this function will be
 * called to remove the elements inside of the hash.  if you don't remove the
 * elements, memory might be leaked. */
static inline void hash_delete(struct hashtable_t *hash,
			       hashdata_free_cb free_cb, void *arg)
{
	struct hlist_head *head;
	struct hlist_node *node, *node_tmp;
	spinlock_t *list_lock; /* spinlock to protect write access */
<<<<<<< HEAD
	uint32_t i;
=======
<<<<<<< HEAD
	uint32_t i;
=======
	int i;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	for (i = 0; i < hash->size; i++) {
		head = &hash->table[i];
		list_lock = &hash->list_locks[i];

		spin_lock_bh(list_lock);
		hlist_for_each_safe(node, node_tmp, head) {
			hlist_del_rcu(node);

			if (free_cb)
				free_cb(node, arg);
		}
		spin_unlock_bh(list_lock);
	}

	hash_destroy(hash);
}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/**
 *	hash_add - adds data to the hashtable
 *	@hash: storage hash table
 *	@compare: callback to determine if 2 hash elements are identical
 *	@choose: callback calculating the hash index
 *	@data: data passed to the aforementioned callbacks as argument
 *	@data_node: to be added element
 *
 *	Returns 0 on success, 1 if the element already is in the hash
 *	and -1 on error.
 */

static inline int hash_add(struct hashtable_t *hash,
			   hashdata_compare_cb compare,
			   hashdata_choose_cb choose,
			   const void *data, struct hlist_node *data_node)
{
	uint32_t index;
	int ret = -1;
<<<<<<< HEAD
=======
=======
/* adds data to the hashtable. returns 0 on success, -1 on error */
static inline int hash_add(struct hashtable_t *hash,
			   hashdata_compare_cb compare,
			   hashdata_choose_cb choose,
			   void *data, struct hlist_node *data_node)
{
	int index;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct hlist_head *head;
	struct hlist_node *node;
	spinlock_t *list_lock; /* spinlock to protect write access */

	if (!hash)
<<<<<<< HEAD
		goto out;
=======
<<<<<<< HEAD
		goto out;
=======
		goto err;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	index = choose(data, hash->size);
	head = &hash->table[index];
	list_lock = &hash->list_locks[index];

	rcu_read_lock();
	__hlist_for_each_rcu(node, head) {
		if (!compare(node, data))
			continue;

<<<<<<< HEAD
		ret = 1;
=======
<<<<<<< HEAD
		ret = 1;
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		goto err_unlock;
	}
	rcu_read_unlock();

	/* no duplicate found in list, add new element */
	spin_lock_bh(list_lock);
	hlist_add_head_rcu(data_node, head);
	spin_unlock_bh(list_lock);

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	ret = 0;
	goto out;

err_unlock:
	rcu_read_unlock();
out:
	return ret;
<<<<<<< HEAD
=======
=======
	return 0;

err_unlock:
	rcu_read_unlock();
err:
	return -1;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

/* removes data from hash, if found. returns pointer do data on success, so you
 * can remove the used structure yourself, or NULL on error .  data could be the
 * structure you use with just the key filled, we just need the key for
 * comparing. */
static inline void *hash_remove(struct hashtable_t *hash,
				hashdata_compare_cb compare,
				hashdata_choose_cb choose, void *data)
{
<<<<<<< HEAD
	uint32_t index;
=======
<<<<<<< HEAD
	uint32_t index;
=======
	size_t index;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct hlist_node *node;
	struct hlist_head *head;
	void *data_save = NULL;

	index = choose(data, hash->size);
	head = &hash->table[index];

	spin_lock_bh(&hash->list_locks[index]);
	hlist_for_each(node, head) {
		if (!compare(node, data))
			continue;

		data_save = node;
		hlist_del_rcu(node);
		break;
	}
	spin_unlock_bh(&hash->list_locks[index]);

	return data_save;
}

#endif /* _NET_BATMAN_ADV_HASH_H_ */
