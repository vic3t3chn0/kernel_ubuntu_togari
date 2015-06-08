/*
<<<<<<< HEAD
<<<<<<< HEAD

 * drivers/gpu/ion/ion.c
 *
 * Copyright (C) 2011 Google, Inc.
 * Copyright (c) 2011-2013, The Linux Foundation. All rights reserved.
=======
 * drivers/gpu/ion/ion.c
 *
 * Copyright (C) 2011 Google, Inc.
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 * drivers/gpu/ion/ion.c
 *
 * Copyright (C) 2011 Google, Inc.
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/device.h>
#include <linux/file.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/freezer.h>
#include <linux/fs.h>
#include <linux/anon_inodes.h>
#include <linux/ion.h>
#include <linux/kthread.h>
#include <linux/list.h>
#include <linux/list_sort.h>
#include <linux/memblock.h>
#include <linux/miscdevice.h>
#include <linux/export.h>
#include <linux/mm.h>
#include <linux/mm_types.h>
#include <linux/rbtree.h>
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <linux/fs.h>
#include <linux/anon_inodes.h>
#include <linux/ion.h>
#include <linux/list.h>
#include <linux/miscdevice.h>
#include <linux/mm.h>
#include <linux/mm_types.h>
#include <linux/rbtree.h>
#include <linux/sched.h>
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <linux/slab.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>
#include <linux/debugfs.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/dma-buf.h>
#include <linux/idr.h>
#include <linux/msm_ion.h>
#include <trace/events/kmem.h>


#include "ion_priv.h"
=======

#include "ion_priv.h"
#define DEBUG
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======

#include "ion_priv.h"
#define DEBUG
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/**
 * struct ion_device - the metadata of the ion device node
 * @dev:		the actual misc device
<<<<<<< HEAD
<<<<<<< HEAD
 * @buffers:		an rb tree of all the existing buffers
 * @buffer_lock:	lock protecting the tree of buffers
 * @lock:		rwsem protecting the tree of heaps and clients
=======
 * @buffers:	an rb tree of all the existing buffers
 * @lock:		lock protecting the buffers & heaps trees
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 * @buffers:	an rb tree of all the existing buffers
 * @lock:		lock protecting the buffers & heaps trees
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * @heaps:		list of all the heaps in the system
 * @user_clients:	list of all the clients created from userspace
 */
struct ion_device {
	struct miscdevice dev;
	struct rb_root buffers;
<<<<<<< HEAD
<<<<<<< HEAD
	struct mutex buffer_lock;
	struct rw_semaphore lock;
	struct plist_head heaps;
	long (*custom_ioctl) (struct ion_client *client, unsigned int cmd,
			      unsigned long arg);
	struct rb_root clients;
	struct dentry *debug_root;
	struct dentry *heaps_debug_root;
	struct dentry *clients_debug_root;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct mutex lock;
	struct rb_root heaps;
	long (*custom_ioctl) (struct ion_client *client, unsigned int cmd,
			      unsigned long arg);
	struct rb_root user_clients;
	struct rb_root kernel_clients;
	struct dentry *debug_root;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

/**
 * struct ion_client - a process/hw block local address space
<<<<<<< HEAD
<<<<<<< HEAD
 * @node:		node in the tree of all clients
 * @dev:		backpointer to ion device
 * @handles:		an rb tree of all the handles in this client
 * @idr:		an idr space for allocating handle ids
 * @lock:		lock protecting the tree of handles
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * @ref:		for reference counting the client
 * @node:		node in the tree of all clients
 * @dev:		backpointer to ion device
 * @handles:		an rb tree of all the handles in this client
 * @lock:		lock protecting the tree of handles
 * @heap_mask:		mask of all supported heaps
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * @name:		used for debugging
 * @task:		used for debugging
 *
 * A client represents a list of buffers this client may access.
 * The mutex stored here is used to protect both handles tree
 * as well as the handles themselves, and should be held while modifying either.
 */
struct ion_client {
<<<<<<< HEAD
<<<<<<< HEAD
	struct rb_node node;
	struct ion_device *dev;
	struct rb_root handles;
	struct idr idr;
	struct mutex lock;
	char *name;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct kref ref;
	struct rb_node node;
	struct ion_device *dev;
	struct rb_root handles;
	struct mutex lock;
	unsigned int heap_mask;
	const char *name;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct task_struct *task;
	pid_t pid;
	struct dentry *debug_root;
};

/**
 * ion_handle - a client local reference to a buffer
 * @ref:		reference count
 * @client:		back pointer to the client the buffer resides in
 * @buffer:		pointer to the buffer
 * @node:		node in the client's handle rbtree
 * @kmap_cnt:		count of times this client has mapped to kernel
<<<<<<< HEAD
<<<<<<< HEAD
 * @id:			client-unique id allocated by client->idr
=======
 * @dmap_cnt:		count of times this client has mapped for dma
 * @usermap_cnt:	count of times this client has mapped for userspace
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 * @dmap_cnt:		count of times this client has mapped for dma
 * @usermap_cnt:	count of times this client has mapped for userspace
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * Modifications to node, map_cnt or mapping should be protected by the
 * lock in the client.  Other fields are never changed after initialization.
 */
struct ion_handle {
	struct kref ref;
	struct ion_client *client;
	struct ion_buffer *buffer;
	struct rb_node node;
	unsigned int kmap_cnt;
<<<<<<< HEAD
<<<<<<< HEAD
	int id;
};

bool ion_buffer_fault_user_mappings(struct ion_buffer *buffer)
{
        return ((buffer->flags & ION_FLAG_CACHED) &&
                !(buffer->flags & ION_FLAG_CACHED_NEEDS_SYNC));
}

bool ion_buffer_cached(struct ion_buffer *buffer)
{
        return !!(buffer->flags & ION_FLAG_CACHED);
}

=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	unsigned int dmap_cnt;
	unsigned int usermap_cnt;
};

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/* this function should only be called while dev->lock is held */
static void ion_buffer_add(struct ion_device *dev,
			   struct ion_buffer *buffer)
{
	struct rb_node **p = &dev->buffers.rb_node;
	struct rb_node *parent = NULL;
	struct ion_buffer *entry;

	while (*p) {
		parent = *p;
		entry = rb_entry(parent, struct ion_buffer, node);

		if (buffer < entry) {
			p = &(*p)->rb_left;
		} else if (buffer > entry) {
			p = &(*p)->rb_right;
		} else {
			pr_err("%s: buffer already found.", __func__);
			BUG();
		}
	}

	rb_link_node(&buffer->node, parent, p);
	rb_insert_color(&buffer->node, &dev->buffers);
}

<<<<<<< HEAD
<<<<<<< HEAD
static int ion_buffer_alloc_dirty(struct ion_buffer *buffer);

=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/* this function should only be called while dev->lock is held */
static struct ion_buffer *ion_buffer_create(struct ion_heap *heap,
				     struct ion_device *dev,
				     unsigned long len,
				     unsigned long align,
				     unsigned long flags)
{
	struct ion_buffer *buffer;
<<<<<<< HEAD
<<<<<<< HEAD
	struct sg_table *table;
	struct scatterlist *sg;
	int i, ret;
=======
	int ret;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	int ret;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	buffer = kzalloc(sizeof(struct ion_buffer), GFP_KERNEL);
	if (!buffer)
		return ERR_PTR(-ENOMEM);

	buffer->heap = heap;
<<<<<<< HEAD
<<<<<<< HEAD
	buffer->flags = flags;
	kref_init(&buffer->ref);

	ret = heap->ops->allocate(heap, buffer, len, align, flags);

	if (ret) {
		if (!(heap->flags & ION_HEAP_FLAG_DEFER_FREE))
			goto err2;

		ion_heap_freelist_drain(heap, 0);
		ret = heap->ops->allocate(heap, buffer, len, align,
					  flags);
		if (ret)
			goto err2;
	}

	buffer->dev = dev;
	buffer->size = len;

	table = heap->ops->map_dma(heap, buffer);
	if (IS_ERR_OR_NULL(table)) {
		heap->ops->free(buffer);
		kfree(buffer);
		return ERR_PTR(PTR_ERR(table));
	}
	buffer->sg_table = table;
	if (ion_buffer_fault_user_mappings(buffer)) {
		for_each_sg(buffer->sg_table->sgl, sg, buffer->sg_table->nents,
			    i) {
			if (sg_dma_len(sg) == PAGE_SIZE)
				continue;
			pr_err("%s: cached mappings that will be faulted in "
			       "must have pagewise sg_lists\n", __func__);
			ret = -EINVAL;
			goto err;
		}

		ret = ion_buffer_alloc_dirty(buffer);
		if (ret)
			goto err;
	}

	buffer->dev = dev;
	buffer->size = len;
	INIT_LIST_HEAD(&buffer->vmas);
	mutex_init(&buffer->lock);
	/* this will set up dma addresses for the sglist -- it is not
	   technically correct as per the dma api -- a specific
	   device isn't really taking ownership here.  However, in practice on
	   our systems the only dma_address space is physical addresses.
	   Additionally, we can't afford the overhead of invalidating every
	   allocation via dma_map_sg. The implicit contract here is that
	   memory comming from the heaps is ready for dma, ie if it has a
	   cached mapping that mapping has been invalidated */
	for_each_sg(buffer->sg_table->sgl, sg, buffer->sg_table->nents, i) {
		if (sg_dma_address(sg) == 0)
			sg_dma_address(sg) = sg_phys(sg);
	}
	mutex_lock(&dev->buffer_lock);
	ion_buffer_add(dev, buffer);
	mutex_unlock(&dev->buffer_lock);
	return buffer;

err:
	heap->ops->unmap_dma(heap, buffer);
	heap->ops->free(buffer);
err2:
	kfree(buffer);
	return ERR_PTR(ret);
}

static void ion_delayed_unsecure(struct ion_buffer *buffer)
{
	if (buffer->heap->ops->unsecure_buffer)
		buffer->heap->ops->unsecure_buffer(buffer, 1);
}

void ion_buffer_destroy(struct ion_buffer *buffer)
{
	if (WARN_ON(buffer->kmap_cnt > 0))
		buffer->heap->ops->unmap_kernel(buffer->heap, buffer);
	buffer->heap->ops->unmap_dma(buffer->heap, buffer);

	ion_delayed_unsecure(buffer);
	buffer->heap->ops->free(buffer);
	if (buffer->flags & ION_FLAG_CACHED)
		kfree(buffer->dirty);
	kfree(buffer);
}

static void _ion_buffer_destroy(struct kref *kref)
{
	struct ion_buffer *buffer = container_of(kref, struct ion_buffer, ref);
	struct ion_heap *heap = buffer->heap;
	struct ion_device *dev = buffer->dev;

	mutex_lock(&dev->buffer_lock);
	rb_erase(&buffer->node, &dev->buffers);
	mutex_unlock(&dev->buffer_lock);

	if (heap->flags & ION_HEAP_FLAG_DEFER_FREE)
		ion_heap_freelist_add(heap, buffer);
	else
		ion_buffer_destroy(buffer);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	kref_init(&buffer->ref);

	ret = heap->ops->allocate(heap, buffer, len, align, flags);
	if (ret) {
		kfree(buffer);
		return ERR_PTR(ret);
	}
	buffer->dev = dev;
	buffer->size = len;
	mutex_init(&buffer->lock);
	ion_buffer_add(dev, buffer);
	return buffer;
}

static void ion_buffer_destroy(struct kref *kref)
{
	struct ion_buffer *buffer = container_of(kref, struct ion_buffer, ref);
	struct ion_device *dev = buffer->dev;

	if (WARN_ON(buffer->kmap_cnt > 0))
		buffer->heap->ops->unmap_kernel(buffer->heap, buffer);

	if (WARN_ON(buffer->dmap_cnt > 0))
		buffer->heap->ops->unmap_dma(buffer->heap, buffer);

	buffer->heap->ops->free(buffer);
	mutex_lock(&dev->lock);
	rb_erase(&buffer->node, &dev->buffers);
	mutex_unlock(&dev->lock);
	kfree(buffer);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static void ion_buffer_get(struct ion_buffer *buffer)
{
	kref_get(&buffer->ref);
}

static int ion_buffer_put(struct ion_buffer *buffer)
{
<<<<<<< HEAD
<<<<<<< HEAD
	return kref_put(&buffer->ref, _ion_buffer_destroy);
}

static void ion_buffer_add_to_handle(struct ion_buffer *buffer)
{
	mutex_lock(&buffer->lock);
	buffer->handle_count++;
	mutex_unlock(&buffer->lock);
}

static void ion_buffer_remove_from_handle(struct ion_buffer *buffer)
{
	/*
	 * when a buffer is removed from a handle, if it is not in
	 * any other handles, copy the taskcomm and the pid of the
	 * process it's being removed from into the buffer.  At this
	 * point there will be no way to track what processes this buffer is
	 * being used by, it only exists as a dma_buf file descriptor.
	 * The taskcomm and pid can provide a debug hint as to where this fd
	 * is in the system
	 */
	mutex_lock(&buffer->lock);
	buffer->handle_count--;
	BUG_ON(buffer->handle_count < 0);
	if (!buffer->handle_count) {
		struct task_struct *task;

		task = current->group_leader;
		get_task_comm(buffer->task_comm, task);
		buffer->pid = task_pid_nr(task);
	}
	mutex_unlock(&buffer->lock);
=======
	return kref_put(&buffer->ref, ion_buffer_destroy);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	return kref_put(&buffer->ref, ion_buffer_destroy);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static struct ion_handle *ion_handle_create(struct ion_client *client,
				     struct ion_buffer *buffer)
{
	struct ion_handle *handle;

	handle = kzalloc(sizeof(struct ion_handle), GFP_KERNEL);
	if (!handle)
		return ERR_PTR(-ENOMEM);
	kref_init(&handle->ref);
	rb_init_node(&handle->node);
	handle->client = client;
	ion_buffer_get(buffer);
<<<<<<< HEAD
<<<<<<< HEAD
	ion_buffer_add_to_handle(buffer);
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	handle->buffer = buffer;

	return handle;
}

<<<<<<< HEAD
<<<<<<< HEAD
static void ion_handle_kmap_put(struct ion_handle *);

static void ion_handle_destroy(struct kref *kref)
{
	struct ion_handle *handle = container_of(kref, struct ion_handle, ref);
	struct ion_client *client = handle->client;
	struct ion_buffer *buffer = handle->buffer;

	mutex_lock(&buffer->lock);
	while (handle->kmap_cnt)
		ion_handle_kmap_put(handle);
	mutex_unlock(&buffer->lock);

	idr_remove(&client->idr, handle->id);
	if (!RB_EMPTY_NODE(&handle->node))
		rb_erase(&handle->node, &client->handles);

	ion_buffer_remove_from_handle(buffer);
	ion_buffer_put(buffer);

=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static void ion_handle_destroy(struct kref *kref)
{
	struct ion_handle *handle = container_of(kref, struct ion_handle, ref);
	/* XXX Can a handle be destroyed while it's map count is non-zero?:
	   if (handle->map_cnt) unmap
	 */
	ion_buffer_put(handle->buffer);
	mutex_lock(&handle->client->lock);
	if (!RB_EMPTY_NODE(&handle->node))
		rb_erase(&handle->node, &handle->client->handles);
	mutex_unlock(&handle->client->lock);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	kfree(handle);
}

struct ion_buffer *ion_handle_buffer(struct ion_handle *handle)
{
	return handle->buffer;
}

static void ion_handle_get(struct ion_handle *handle)
{
	kref_get(&handle->ref);
}

<<<<<<< HEAD
<<<<<<< HEAD
int ion_handle_put(struct ion_handle *handle)
{
	struct ion_client *client = handle->client;
	int ret;

	mutex_lock(&client->lock);
	ret = kref_put(&handle->ref, ion_handle_destroy);
	mutex_unlock(&client->lock);

	return ret;
=======
static int ion_handle_put(struct ion_handle *handle)
{
	return kref_put(&handle->ref, ion_handle_destroy);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static int ion_handle_put(struct ion_handle *handle)
{
	return kref_put(&handle->ref, ion_handle_destroy);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static struct ion_handle *ion_handle_lookup(struct ion_client *client,
					    struct ion_buffer *buffer)
{
	struct rb_node *n;

	for (n = rb_first(&client->handles); n; n = rb_next(n)) {
		struct ion_handle *handle = rb_entry(n, struct ion_handle,
<<<<<<< HEAD
<<<<<<< HEAD
						   node);
=======
						     node);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
						     node);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		if (handle->buffer == buffer)
			return handle;
	}
	return NULL;
}

<<<<<<< HEAD
<<<<<<< HEAD
struct ion_handle *ion_handle_get_by_id(struct ion_client *client,
						int id)
{
	struct ion_handle *handle;

	mutex_lock(&client->lock);
	handle = idr_find(&client->idr, id);
	if (handle)
		ion_handle_get(handle);
	mutex_unlock(&client->lock);

	return handle ? handle : ERR_PTR(-EINVAL);
}

static bool ion_handle_validate(struct ion_client *client, struct ion_handle *handle)
{
	WARN_ON(!mutex_is_locked(&client->lock));
	return (idr_find(&client->idr, handle->id) == handle);
}

static int ion_handle_add(struct ion_client *client, struct ion_handle *handle)
{
	int rc;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static bool ion_handle_validate(struct ion_client *client, struct ion_handle *handle)
{
	struct rb_node *n = client->handles.rb_node;

	while (n) {
		struct ion_handle *handle_node = rb_entry(n, struct ion_handle,
							  node);
		if (handle < handle_node)
			n = n->rb_left;
		else if (handle > handle_node)
			n = n->rb_right;
		else
			return true;
	}
	return false;
}

static void ion_handle_add(struct ion_client *client, struct ion_handle *handle)
{
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct rb_node **p = &client->handles.rb_node;
	struct rb_node *parent = NULL;
	struct ion_handle *entry;

<<<<<<< HEAD
<<<<<<< HEAD
	do {
		int id;
		rc = idr_pre_get(&client->idr, GFP_KERNEL);
		if (!rc)
			return -ENOMEM;
		rc = idr_get_new_above(&client->idr, handle, 1, &id);
		handle->id = id;
	} while (rc == -EAGAIN);

	if (rc < 0)
		return rc;

=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	while (*p) {
		parent = *p;
		entry = rb_entry(parent, struct ion_handle, node);

		if (handle < entry)
			p = &(*p)->rb_left;
		else if (handle > entry)
			p = &(*p)->rb_right;
		else
			WARN(1, "%s: buffer already found.", __func__);
	}

	rb_link_node(&handle->node, parent, p);
	rb_insert_color(&handle->node, &client->handles);
<<<<<<< HEAD
<<<<<<< HEAD

	return 0;
}

struct ion_handle *ion_alloc(struct ion_client *client, size_t len,
			     size_t align, unsigned int heap_id_mask,
			     unsigned int flags)
{
	struct ion_handle *handle;
	struct ion_device *dev = client->dev;
	struct ion_buffer *buffer = NULL;
	struct ion_heap *heap;
	int ret;
	unsigned long secure_allocation = flags & ION_FLAG_SECURE;
	const unsigned int MAX_DBG_STR_LEN = 64;
	char dbg_str[MAX_DBG_STR_LEN];
	unsigned int dbg_str_idx = 0;

	dbg_str[0] = '\0';

	/*
	 * For now, we don't want to fault in pages individually since
	 * clients are already doing manual cache maintenance. In
	 * other words, the implicit caching infrastructure is in
	 * place (in code) but should not be used.
	 */
	flags |= ION_FLAG_CACHED_NEEDS_SYNC;

	pr_debug("%s: len %d align %d heap_id_mask %u flags %x\n", __func__,
		 len, align, heap_id_mask, flags);
	/*
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

struct ion_handle *ion_alloc(struct ion_client *client, size_t len,
			     size_t align, unsigned int flags)
{
	struct rb_node *n;
	struct ion_handle *handle;
	struct ion_device *dev = client->dev;
	struct ion_buffer *buffer = NULL;

	/*
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	 * traverse the list of heaps available in this system in priority
	 * order.  If the heap type is supported by the client, and matches the
	 * request of the caller allocate from it.  Repeat until allocate has
	 * succeeded or all heaps have been tried
	 */
	if (WARN_ON(!len))
		return ERR_PTR(-EINVAL);

	len = PAGE_ALIGN(len);

<<<<<<< HEAD
<<<<<<< HEAD
	down_read(&dev->lock);
	plist_for_each_entry(heap, &dev->heaps, node) {
		/* if the caller didn't specify this heap id */
		if (!((1 << heap->id) & heap_id_mask))
			continue;
		/* Do not allow un-secure heap if secure is specified */
		if (secure_allocation &&
		    !ion_heap_allow_secure_allocation(heap->type))
			continue;
		trace_ion_alloc_buffer_start(client->name, heap->name, len,
					     heap_id_mask, flags);
		buffer = ion_buffer_create(heap, dev, len, align, flags);
		trace_ion_alloc_buffer_end(client->name, heap->name, len,
					   heap_id_mask, flags);
		if (!IS_ERR_OR_NULL(buffer))
			break;

		trace_ion_alloc_buffer_fallback(client->name, heap->name, len,
					    heap_id_mask, flags,
					    PTR_ERR(buffer));
		if (dbg_str_idx < MAX_DBG_STR_LEN) {
			unsigned int len_left = MAX_DBG_STR_LEN-dbg_str_idx-1;
			int ret_value = snprintf(&dbg_str[dbg_str_idx],
						len_left, "%s ", heap->name);
			if (ret_value >= len_left) {
				/* overflow */
				dbg_str[MAX_DBG_STR_LEN-1] = '\0';
				dbg_str_idx = MAX_DBG_STR_LEN;
			} else if (ret_value >= 0) {
				dbg_str_idx += ret_value;
			} else {
				/* error */
				dbg_str[MAX_DBG_STR_LEN-1] = '\0';
			}
		}
	}
	up_read(&dev->lock);

	if (buffer == NULL) {
		trace_ion_alloc_buffer_fail(client->name, dbg_str, len,
					    heap_id_mask, flags, -ENODEV);
		return ERR_PTR(-ENODEV);
	}

	if (IS_ERR(buffer)) {
		trace_ion_alloc_buffer_fail(client->name, dbg_str, len,
					    heap_id_mask, flags,
					    PTR_ERR(buffer));
		pr_debug("ION is unable to allocate 0x%x bytes (alignment: "
			 "0x%x) from heap(s) %sfor client %s\n",
			len, align, dbg_str, client->name);
		return ERR_PTR(PTR_ERR(buffer));
	}
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	mutex_lock(&dev->lock);
	for (n = rb_first(&dev->heaps); n != NULL; n = rb_next(n)) {
		struct ion_heap *heap = rb_entry(n, struct ion_heap, node);
		/* if the client doesn't support this heap type */
		if (!((1 << heap->type) & client->heap_mask))
			continue;
		/* if the caller didn't specify this heap type */
		if (!((1 << heap->id) & flags))
			continue;
		buffer = ion_buffer_create(heap, dev, len, align, flags);
		if (!IS_ERR_OR_NULL(buffer))
			break;
	}
	mutex_unlock(&dev->lock);

	if (buffer == NULL)
		return ERR_PTR(-ENODEV);

	if (IS_ERR(buffer))
		return ERR_PTR(PTR_ERR(buffer));
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	handle = ion_handle_create(client, buffer);

	/*
	 * ion_buffer_create will create a buffer with a ref_cnt of 1,
	 * and ion_handle_create will take a second reference, drop one here
	 */
	ion_buffer_put(buffer);

<<<<<<< HEAD
<<<<<<< HEAD
	if (IS_ERR(handle))
		return handle;

	mutex_lock(&client->lock);
	ret = ion_handle_add(client, handle);
	mutex_unlock(&client->lock);
	if (ret) {
		ion_handle_put(handle);
		handle = ERR_PTR(ret);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (!IS_ERR_OR_NULL(handle)) {
		mutex_lock(&client->lock);
		ion_handle_add(client, handle);
		mutex_unlock(&client->lock);
	}

	return handle;
}

#ifdef CONFIG_ION_EXYNOS
struct ion_handle *ion_exynos_get_user_pages(struct ion_client *client,
			unsigned long uvaddr, size_t len, unsigned int flags)
{
	struct rb_node *n;
	struct ion_handle *handle;
	struct ion_device *dev = client->dev;
	struct ion_buffer *buffer = NULL;

	if (WARN_ON(!len))
		return ERR_PTR(-EINVAL);

	if (WARN_ON((flags & ~ION_EXYNOS_WRITE_MASK)
						!= ION_HEAP_EXYNOS_USER_MASK))
		return ERR_PTR(-ENOSYS);

	mutex_lock(&dev->lock);
	for (n = rb_first(&dev->heaps); n != NULL; n = rb_next(n)) {
		struct ion_heap *heap = rb_entry(n, struct ion_heap, node);
		/* if the client doesn't support this heap type */
		if (!((1 << heap->type) & client->heap_mask))
			continue;
		/* if the caller didn't specify this heap type */
		if (!((1 << heap->id) & flags))
			continue;
		buffer = ion_buffer_create(heap, dev, len, uvaddr, flags);
		if (!IS_ERR_OR_NULL(buffer))
			break;
	}
	mutex_unlock(&dev->lock);

	if (buffer == NULL)
		return ERR_PTR(-ENODEV);

	if (IS_ERR(buffer))
		return ERR_PTR(PTR_ERR(buffer));

	handle = ion_handle_create(client, buffer);

	/*
	 * ion_buffer_create will create a buffer with a ref_cnt of 1,
	 * and ion_handle_create will take a second reference, drop one here
	 */
	ion_buffer_put(buffer);

	if (!IS_ERR_OR_NULL(handle)) {
		mutex_lock(&client->lock);
		ion_handle_add(client, handle);
		mutex_unlock(&client->lock);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}

	return handle;
}
<<<<<<< HEAD
<<<<<<< HEAD
EXPORT_SYMBOL(ion_alloc);
=======
#endif /* CONFIG_ION_EXYNOS */
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
#endif /* CONFIG_ION_EXYNOS */
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

void ion_free(struct ion_client *client, struct ion_handle *handle)
{
	bool valid_handle;

	BUG_ON(client != handle->client);

	mutex_lock(&client->lock);
	valid_handle = ion_handle_validate(client, handle);
<<<<<<< HEAD
<<<<<<< HEAD
	if (!valid_handle) {
		WARN(1, "%s: invalid handle passed to free.\n", __func__);
		mutex_unlock(&client->lock);
		return;
	}
	mutex_unlock(&client->lock);
	ion_handle_put(handle);
}
EXPORT_SYMBOL(ion_free);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	mutex_unlock(&client->lock);

	if (!valid_handle) {
		WARN("%s: invalid handle passed to free.\n", __func__);
		return;
	}
	ion_handle_put(handle);
}

static void ion_client_get(struct ion_client *client);
static int ion_client_put(struct ion_client *client);

static bool _ion_map(int *buffer_cnt, int *handle_cnt)
{
	bool map;

	BUG_ON(*handle_cnt != 0 && *buffer_cnt == 0);

	if (*buffer_cnt)
		map = false;
	else
		map = true;
	if (*handle_cnt == 0)
		(*buffer_cnt)++;
	(*handle_cnt)++;
	return map;
}

static bool _ion_unmap(int *buffer_cnt, int *handle_cnt)
{
	BUG_ON(*handle_cnt == 0);
	(*handle_cnt)--;
	if (*handle_cnt != 0)
		return false;
	BUG_ON(*buffer_cnt == 0);
	(*buffer_cnt)--;
	if (*buffer_cnt == 0)
		return true;
	return false;
}
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

int ion_phys(struct ion_client *client, struct ion_handle *handle,
	     ion_phys_addr_t *addr, size_t *len)
{
	struct ion_buffer *buffer;
	int ret;

	mutex_lock(&client->lock);
	if (!ion_handle_validate(client, handle)) {
		mutex_unlock(&client->lock);
		return -EINVAL;
	}

	buffer = handle->buffer;

	if (!buffer->heap->ops->phys) {
		pr_err("%s: ion_phys is not implemented by this heap.\n",
		       __func__);
		mutex_unlock(&client->lock);
		return -ENODEV;
	}
	mutex_unlock(&client->lock);
	ret = buffer->heap->ops->phys(buffer->heap, buffer, addr, len);
	return ret;
}
<<<<<<< HEAD
<<<<<<< HEAD
EXPORT_SYMBOL(ion_phys);

static void *ion_buffer_kmap_get(struct ion_buffer *buffer)
{
	void *vaddr;

	if (buffer->kmap_cnt) {
		buffer->kmap_cnt++;
		return buffer->vaddr;
	}
	vaddr = buffer->heap->ops->map_kernel(buffer->heap, buffer);
	if (IS_ERR_OR_NULL(vaddr))
		return vaddr;
	buffer->vaddr = vaddr;
	buffer->kmap_cnt++;
	return vaddr;
}

static void *ion_handle_kmap_get(struct ion_handle *handle)
{
	struct ion_buffer *buffer = handle->buffer;
	void *vaddr;

	if (handle->kmap_cnt) {
		handle->kmap_cnt++;
		return buffer->vaddr;
	}
	vaddr = ion_buffer_kmap_get(buffer);
	if (IS_ERR_OR_NULL(vaddr))
		return vaddr;
	handle->kmap_cnt++;
	return vaddr;
}

static void ion_buffer_kmap_put(struct ion_buffer *buffer)
{
	buffer->kmap_cnt--;
	if (!buffer->kmap_cnt) {
		buffer->heap->ops->unmap_kernel(buffer->heap, buffer);
		buffer->vaddr = NULL;
	}
}

static void ion_handle_kmap_put(struct ion_handle *handle)
{
	struct ion_buffer *buffer = handle->buffer;

	handle->kmap_cnt--;
	if (!handle->kmap_cnt)
		ion_buffer_kmap_put(buffer);
}

void *ion_map_kernel(struct ion_client *client, struct ion_handle *handle)
{
	struct ion_buffer *buffer;
	void *vaddr;

	mutex_lock(&client->lock);
	if (!ion_handle_validate(client, handle)) {
		pr_err("%s: invalid handle passed to map_kernel.\n",
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

void *ion_map_kernel(struct ion_client *client, struct ion_handle *handle)
{
	struct ion_buffer *buffer;
	void *vaddr;

	mutex_lock(&client->lock);
	if (!ion_handle_validate(client, handle)) {
		pr_err("%s: invalid handle passed to map_kernel.\n",
		       __func__);
		mutex_unlock(&client->lock);
		return ERR_PTR(-EINVAL);
	}

	buffer = handle->buffer;
	mutex_lock(&buffer->lock);

	if (!handle->buffer->heap->ops->map_kernel) {
		pr_err("%s: map_kernel is not implemented by this heap.\n",
		       __func__);
		mutex_unlock(&buffer->lock);
		mutex_unlock(&client->lock);
		return ERR_PTR(-ENODEV);
	}

	if (_ion_map(&buffer->kmap_cnt, &handle->kmap_cnt)) {
		vaddr = buffer->heap->ops->map_kernel(buffer->heap, buffer);
		if (IS_ERR_OR_NULL(vaddr))
			_ion_unmap(&buffer->kmap_cnt, &handle->kmap_cnt);
		buffer->vaddr = vaddr;
	} else {
		vaddr = buffer->vaddr;
	}
	mutex_unlock(&buffer->lock);
	mutex_unlock(&client->lock);
	return vaddr;
}

struct scatterlist *ion_map_dma(struct ion_client *client,
				struct ion_handle *handle)
{
	struct ion_buffer *buffer;
	struct scatterlist *sglist;

	mutex_lock(&client->lock);
	if (!ion_handle_validate(client, handle)) {
		pr_err("%s: invalid handle passed to map_dma.\n",
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		       __func__);
		mutex_unlock(&client->lock);
		return ERR_PTR(-EINVAL);
	}
<<<<<<< HEAD
<<<<<<< HEAD

	buffer = handle->buffer;

	if (!handle->buffer->heap->ops->map_kernel) {
		pr_err("%s: map_kernel is not implemented by this heap.\n",
		       __func__);
		mutex_unlock(&client->lock);
		return ERR_PTR(-ENODEV);
	}

	mutex_lock(&buffer->lock);
	vaddr = ion_handle_kmap_get(handle);
	mutex_unlock(&buffer->lock);
	mutex_unlock(&client->lock);
	return vaddr;
}
EXPORT_SYMBOL(ion_map_kernel);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	buffer = handle->buffer;
	mutex_lock(&buffer->lock);

	if (!handle->buffer->heap->ops->map_dma) {
		pr_err("%s: map_kernel is not implemented by this heap.\n",
		       __func__);
		mutex_unlock(&buffer->lock);
		mutex_unlock(&client->lock);
		return ERR_PTR(-ENODEV);
	}
	if (_ion_map(&buffer->dmap_cnt, &handle->dmap_cnt)) {
		sglist = buffer->heap->ops->map_dma(buffer->heap, buffer);
		if (IS_ERR_OR_NULL(sglist))
			_ion_unmap(&buffer->dmap_cnt, &handle->dmap_cnt);
		buffer->sglist = sglist;
	} else {
		sglist = buffer->sglist;
	}
	mutex_unlock(&buffer->lock);
	mutex_unlock(&client->lock);
	return sglist;
}
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

void ion_unmap_kernel(struct ion_client *client, struct ion_handle *handle)
{
	struct ion_buffer *buffer;

	mutex_lock(&client->lock);
	buffer = handle->buffer;
	mutex_lock(&buffer->lock);
<<<<<<< HEAD
<<<<<<< HEAD
	ion_handle_kmap_put(handle);
	mutex_unlock(&buffer->lock);
	mutex_unlock(&client->lock);
}
EXPORT_SYMBOL(ion_unmap_kernel);

static int ion_debug_client_show(struct seq_file *s, void *unused)
{
	struct ion_client *client = s->private;
	struct rb_node *n;

	seq_printf(s, "%16.16s: %16.16s : %16.16s : %12.12s\n",
			"heap_name", "size_in_bytes", "handle refcount",
			"buffer");

	mutex_lock(&client->lock);
	for (n = rb_first(&client->handles); n; n = rb_next(n)) {
		struct ion_handle *handle = rb_entry(n, struct ion_handle,
						     node);

		seq_printf(s, "%16.16s: %16x : %16d : %12p",
				handle->buffer->heap->name,
				handle->buffer->size,
				atomic_read(&handle->ref.refcount),
				handle->buffer);

		seq_printf(s, "\n");
	}
	mutex_unlock(&client->lock);
	return 0;
}

static int ion_debug_client_open(struct inode *inode, struct file *file)
{
	return single_open(file, ion_debug_client_show, inode->i_private);
}

static const struct file_operations debug_client_fops = {
	.open = ion_debug_client_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

static bool startswith(const char *string, const char *prefix)
{
	size_t l1 = strlen(string);
	size_t l2 = strlen(prefix);
	return strncmp(string, prefix, min(l1, l2)) == 0;
}

static int ion_get_client_serial(const struct rb_root *root,
					const unsigned char *name)
{
	int serial = -1;
	struct rb_node *node;
	for (node = rb_first(root); node; node = rb_next(node)) {
		int n;
		char *serial_string;
		struct ion_client *client = rb_entry(node, struct ion_client,
						node);
		if (!startswith(client->name, name))
			continue;
		serial_string = strrchr(client->name, '-');
		if (!serial_string)
			continue;
		serial_string++;
		sscanf(serial_string, "%d", &n);
		serial = max(serial, n);
	}
	return serial + 1;
}

struct ion_client *ion_client_create(struct ion_device *dev,
				     const char *name)
{
	struct ion_client *client;
=======
	if (_ion_unmap(&buffer->kmap_cnt, &handle->kmap_cnt)) {
		buffer->heap->ops->unmap_kernel(buffer->heap, buffer);
		buffer->vaddr = NULL;
	}
	mutex_unlock(&buffer->lock);
	mutex_unlock(&client->lock);
}

void ion_unmap_dma(struct ion_client *client, struct ion_handle *handle)
{
	struct ion_buffer *buffer;

	mutex_lock(&client->lock);
	buffer = handle->buffer;
	mutex_lock(&buffer->lock);
	if (_ion_unmap(&buffer->dmap_cnt, &handle->dmap_cnt)) {
		buffer->heap->ops->unmap_dma(buffer->heap, buffer);
		buffer->sglist = NULL;
	}
	mutex_unlock(&buffer->lock);
	mutex_unlock(&client->lock);
}


struct ion_buffer *ion_share(struct ion_client *client,
				 struct ion_handle *handle)
{
	bool valid_handle;
=======
	if (_ion_unmap(&buffer->kmap_cnt, &handle->kmap_cnt)) {
		buffer->heap->ops->unmap_kernel(buffer->heap, buffer);
		buffer->vaddr = NULL;
	}
	mutex_unlock(&buffer->lock);
	mutex_unlock(&client->lock);
}

void ion_unmap_dma(struct ion_client *client, struct ion_handle *handle)
{
	struct ion_buffer *buffer;

	mutex_lock(&client->lock);
	buffer = handle->buffer;
	mutex_lock(&buffer->lock);
	if (_ion_unmap(&buffer->dmap_cnt, &handle->dmap_cnt)) {
		buffer->heap->ops->unmap_dma(buffer->heap, buffer);
		buffer->sglist = NULL;
	}
	mutex_unlock(&buffer->lock);
	mutex_unlock(&client->lock);
}


struct ion_buffer *ion_share(struct ion_client *client,
				 struct ion_handle *handle)
{
	bool valid_handle;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	mutex_lock(&client->lock);
	valid_handle = ion_handle_validate(client, handle);
	mutex_unlock(&client->lock);
	if (!valid_handle) {
		WARN("%s: invalid handle passed to share.\n", __func__);
		return ERR_PTR(-EINVAL);
	}

	/* do not take an extra reference here, the burden is on the caller
	 * to make sure the buffer doesn't go away while it's passing it
	 * to another client -- ion_free should not be called on this handle
	 * until the buffer has been imported into the other client
	 */
	return handle->buffer;
}

struct ion_handle *ion_import(struct ion_client *client,
			      struct ion_buffer *buffer)
{
	struct ion_handle *handle = NULL;

	mutex_lock(&client->lock);
	/* if a handle exists for this buffer just take a reference to it */
	handle = ion_handle_lookup(client, buffer);
	if (!IS_ERR_OR_NULL(handle)) {
		ion_handle_get(handle);
		goto end;
	}
	handle = ion_handle_create(client, buffer);
	if (IS_ERR_OR_NULL(handle))
		goto end;
	ion_handle_add(client, handle);
end:
	mutex_unlock(&client->lock);
	return handle;
}

static const struct file_operations ion_share_fops;

int ion_share_fd(struct ion_client *client, struct ion_handle *handle)
{
	int fd = get_unused_fd();
	struct file *filp;
	struct ion_buffer *buffer;

	if (fd < 0)
		return fd;

	buffer = ion_share(client, handle);
	if (IS_ERR(buffer))
		goto err;

	filp = anon_inode_getfile("ion_share_fd", &ion_share_fops, buffer,
				O_RDWR);
	if (IS_ERR_OR_NULL(filp))
		goto err;

	ion_buffer_get(buffer);
	fd_install(fd, filp);
	return fd;
err:
	put_unused_fd(fd);
	return -ENFILE;
}

struct ion_handle *ion_import_fd(struct ion_client *client, int fd)
{
	struct file *file = fget(fd);
	struct ion_handle *handle;

	if (!file) {
		pr_err("%s: imported fd not found in file table.\n", __func__);
		return ERR_PTR(-EINVAL);
	}
	if (file->f_op != &ion_share_fops) {
		pr_err("%s: imported file is not a shared ion file.\n",
		       __func__);
		handle = ERR_PTR(-EINVAL);
		goto end;
	}
	handle = ion_import(client, file->private_data);
end:
	fput(file);
	return handle;
}

struct ion_handle *ion_import_uva(struct ion_client *client, unsigned long uva,
								off_t *offset)
{
	struct vm_area_struct *vma;
	struct ion_handle *handle;

	vma = find_vma(current->mm, uva);
	if (!vma) {
		pr_err("%s: invalid importing address 0x%lx.\n", __func__, uva);
		return ERR_PTR(-EINVAL);
	}

	if (!vma->vm_file) {
		pr_debug("%s: imported address is not file-mapped\n", __func__);
		return ERR_PTR(-ENXIO);
	}

	if (vma->vm_file->f_op != &ion_share_fops) {
		pr_debug("%s: imported file is not a shared ion file.\n",
		__func__);
		return ERR_PTR(-ENXIO);
	}

	handle = ion_import(client, vma->vm_file->private_data);
	if (IS_ERR(handle))
		return handle;

	if (offset) {
		ion_phys_addr_t phys;

		*offset = vma->vm_pgoff << PAGE_SHIFT;

		if (is_linear_pfn_mapping(vma)) {
			/* if vma is VM_PFN_AT_MMAPed, vma->vm_pgoff indicates
			 * mapped physical address */
			size_t len;
			if (ion_phys(client, handle, &phys, &len))
				return ERR_PTR(-EINVAL);

			*offset -= phys;
		}
		*offset += uva - vma->vm_start;
	}

	return handle;
}

static int ion_debug_client_show(struct seq_file *s, void *unused)
{
	struct ion_client *client = s->private;
	struct rb_node *n;
	size_t sizes[ION_NUM_HEAPS] = {0};
	const char *names[ION_NUM_HEAPS] = {0};
	int i;

	mutex_lock(&client->lock);
	for (n = rb_first(&client->handles); n; n = rb_next(n)) {
		struct ion_handle *handle = rb_entry(n, struct ion_handle,
						     node);
		enum ion_heap_type type = handle->buffer->heap->type;

		if (!names[type])
			names[type] = handle->buffer->heap->name;
		sizes[type] += handle->buffer->size;
	}
	mutex_unlock(&client->lock);

	seq_printf(s, "%16.16s: %16.16s\n", "heap_name", "size_in_bytes");
	for (i = 0; i < ION_NUM_HEAPS; i++) {
		if (!names[i])
			continue;
		seq_printf(s, "%16.16s: %16u %d\n", names[i], sizes[i],
			   atomic_read(&client->ref.refcount));
	}
	return 0;
}

static int ion_debug_client_open(struct inode *inode, struct file *file)
{
	return single_open(file, ion_debug_client_show, inode->i_private);
}

static const struct file_operations debug_client_fops = {
	.open = ion_debug_client_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

static struct ion_client *ion_client_lookup(struct ion_device *dev,
					    struct task_struct *task)
{
	struct rb_node *n = dev->user_clients.rb_node;
	struct ion_client *client;

	mutex_lock(&dev->lock);
	while (n) {
		client = rb_entry(n, struct ion_client, node);
		if (task == client->task) {
			ion_client_get(client);
			mutex_unlock(&dev->lock);
			return client;
		} else if (task < client->task) {
			n = n->rb_left;
		} else if (task > client->task) {
			n = n->rb_right;
		}
	}
	mutex_unlock(&dev->lock);
	return NULL;
}

struct ion_client *ion_client_create(struct ion_device *dev,
				     unsigned int heap_mask,
				     const char *name)
{
	struct ion_client *client;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct task_struct *task;
	struct rb_node **p;
	struct rb_node *parent = NULL;
	struct ion_client *entry;
<<<<<<< HEAD
<<<<<<< HEAD
	pid_t pid;
	int name_len;
	int client_serial;

	if (!name) {
		pr_err("%s: Name cannot be null\n", __func__);
		return ERR_PTR(-EINVAL);
	}
	name_len = strnlen(name, 64);
	/* add some space to accommodate the serial number suffix */
	name_len = min(64, name_len + 11);
=======
	char debug_name[64];
	pid_t pid;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	char debug_name[64];
	pid_t pid;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	get_task_struct(current->group_leader);
	task_lock(current->group_leader);
	pid = task_pid_nr(current->group_leader);
	/* don't bother to store task struct for kernel threads,
	   they can't be killed anyway */
	if (current->group_leader->flags & PF_KTHREAD) {
		put_task_struct(current->group_leader);
		task = NULL;
	} else {
		task = current->group_leader;
	}
	task_unlock(current->group_leader);

<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	/* if this isn't a kernel thread, see if a client already
	   exists */
	if (task) {
		client = ion_client_lookup(dev, task);
		if (!IS_ERR_OR_NULL(client)) {
			put_task_struct(current->group_leader);
			return client;
		}
	}

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	client = kzalloc(sizeof(struct ion_client), GFP_KERNEL);
	if (!client) {
		if (task)
			put_task_struct(current->group_leader);
		return ERR_PTR(-ENOMEM);
	}

	client->dev = dev;
	client->handles = RB_ROOT;
<<<<<<< HEAD
<<<<<<< HEAD
	idr_init(&client->idr);
	mutex_init(&client->lock);

	client->name = kzalloc(name_len+1, GFP_KERNEL);
	if (!client->name) {
		put_task_struct(current->group_leader);
		kfree(client);
		return ERR_PTR(-ENOMEM);
	}

	client->task = task;
	client->pid = pid;

	down_write(&dev->lock);
	client_serial = ion_get_client_serial(&dev->clients, name);
	snprintf(client->name, name_len, "%s-%d", name, client_serial);
	p = &dev->clients.rb_node;
	while (*p) {
		parent = *p;
		entry = rb_entry(parent, struct ion_client, node);

		if (client < entry)
			p = &(*p)->rb_left;
		else if (client > entry)
			p = &(*p)->rb_right;
	}
	rb_link_node(&client->node, parent, p);
	rb_insert_color(&client->node, &dev->clients);


	client->debug_root = debugfs_create_file(client->name, 0664,
						dev->clients_debug_root,
						client, &debug_client_fops);
	if (!client->debug_root) {
		char buf[256], *path;
		path = dentry_path(dev->clients_debug_root, buf, 256);
		pr_err("Failed to created client debugfs at %s/%s\n",
			path, client->name);
	}

	up_write(&dev->lock);

	return client;
}
EXPORT_SYMBOL(ion_client_create);

void ion_client_destroy(struct ion_client *client)
{
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	mutex_init(&client->lock);
	client->name = name;
	client->heap_mask = heap_mask;
	client->task = task;
	client->pid = pid;
	kref_init(&client->ref);

	mutex_lock(&dev->lock);
	if (task) {
		p = &dev->user_clients.rb_node;
		while (*p) {
			parent = *p;
			entry = rb_entry(parent, struct ion_client, node);

			if (task < entry->task)
				p = &(*p)->rb_left;
			else if (task > entry->task)
				p = &(*p)->rb_right;
		}
		rb_link_node(&client->node, parent, p);
		rb_insert_color(&client->node, &dev->user_clients);
	} else {
		p = &dev->kernel_clients.rb_node;
		while (*p) {
			parent = *p;
			entry = rb_entry(parent, struct ion_client, node);

			if (client < entry)
				p = &(*p)->rb_left;
			else if (client > entry)
				p = &(*p)->rb_right;
		}
		rb_link_node(&client->node, parent, p);
		rb_insert_color(&client->node, &dev->kernel_clients);
	}

	snprintf(debug_name, 64, "%u", client->pid);
	client->debug_root = debugfs_create_file(debug_name, 0664,
						 dev->debug_root, client,
						 &debug_client_fops);
	mutex_unlock(&dev->lock);

	return client;
}

static void _ion_client_destroy(struct kref *kref)
{
	struct ion_client *client = container_of(kref, struct ion_client, ref);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct ion_device *dev = client->dev;
	struct rb_node *n;

	pr_debug("%s: %d\n", __func__, __LINE__);
	while ((n = rb_first(&client->handles))) {
		struct ion_handle *handle = rb_entry(n, struct ion_handle,
						     node);
		ion_handle_destroy(&handle->ref);
	}
<<<<<<< HEAD
<<<<<<< HEAD

	idr_remove_all(&client->idr);
	idr_destroy(&client->idr);

	down_write(&dev->lock);
	if (client->task)
		put_task_struct(client->task);
	rb_erase(&client->node, &dev->clients);
	debugfs_remove_recursive(client->debug_root);

	up_write(&dev->lock);

	kfree(client->name);
	kfree(client);
}
EXPORT_SYMBOL(ion_client_destroy);

int ion_handle_get_flags(struct ion_client *client, struct ion_handle *handle,
			unsigned long *flags)
{
	struct ion_buffer *buffer;

	mutex_lock(&client->lock);
	if (!ion_handle_validate(client, handle)) {
		pr_err("%s: invalid handle passed to %s.\n",
		       __func__, __func__);
		mutex_unlock(&client->lock);
		return -EINVAL;
	}
	buffer = handle->buffer;
	mutex_lock(&buffer->lock);
	*flags = buffer->flags;
	mutex_unlock(&buffer->lock);
	mutex_unlock(&client->lock);

	return 0;
}
EXPORT_SYMBOL(ion_handle_get_flags);

int ion_handle_get_size(struct ion_client *client, struct ion_handle *handle,
			unsigned long *size)
{
	struct ion_buffer *buffer;

	mutex_lock(&client->lock);
	if (!ion_handle_validate(client, handle)) {
		pr_err("%s: invalid handle passed to %s.\n",
		       __func__, __func__);
		mutex_unlock(&client->lock);
		return -EINVAL;
	}
	buffer = handle->buffer;
	mutex_lock(&buffer->lock);
	*size = buffer->size;
	mutex_unlock(&buffer->lock);
	mutex_unlock(&client->lock);

	return 0;
}
EXPORT_SYMBOL(ion_handle_get_size);

struct sg_table *ion_sg_table(struct ion_client *client,
			      struct ion_handle *handle)
{
	struct ion_buffer *buffer;
	struct sg_table *table;

	mutex_lock(&client->lock);
	if (!ion_handle_validate(client, handle)) {
		pr_err("%s: invalid handle passed to map_dma.\n",
		       __func__);
		mutex_unlock(&client->lock);
		return ERR_PTR(-EINVAL);
	}
	buffer = handle->buffer;
	table = buffer->sg_table;
	mutex_unlock(&client->lock);
	return table;
}
EXPORT_SYMBOL(ion_sg_table);

struct sg_table *ion_create_chunked_sg_table(phys_addr_t buffer_base,
					size_t chunk_size, size_t total_size)
{
	struct sg_table *table;
	int i, n_chunks, ret;
	struct scatterlist *sg;

	table = kzalloc(sizeof(struct sg_table), GFP_KERNEL);
	if (!table)
		return ERR_PTR(-ENOMEM);

	n_chunks = DIV_ROUND_UP(total_size, chunk_size);
	pr_debug("creating sg_table with %d chunks\n", n_chunks);

	ret = sg_alloc_table(table, n_chunks, GFP_KERNEL);
	if (ret)
		goto err0;

	for_each_sg(table->sgl, sg, table->nents, i) {
		dma_addr_t addr = buffer_base + i * chunk_size;
		sg_dma_address(sg) = addr;
		sg_dma_len(sg) = chunk_size;
	}

	return table;
err0:
	kfree(table);
	return ERR_PTR(ret);
}

static void ion_buffer_sync_for_device(struct ion_buffer *buffer,
				       struct device *dev,
				       enum dma_data_direction direction);

static struct sg_table *ion_map_dma_buf(struct dma_buf_attachment *attachment,
					enum dma_data_direction direction)
{
	struct dma_buf *dmabuf = attachment->dmabuf;
	struct ion_buffer *buffer = dmabuf->priv;

	ion_buffer_sync_for_device(buffer, attachment->dev, direction);
	return buffer->sg_table;
}

static void ion_unmap_dma_buf(struct dma_buf_attachment *attachment,
			      struct sg_table *table,
			      enum dma_data_direction direction)
{
}

static int ion_buffer_alloc_dirty(struct ion_buffer *buffer)
{
	unsigned long pages = buffer->sg_table->nents;
	unsigned long length = (pages + BITS_PER_LONG - 1)/BITS_PER_LONG;

	buffer->dirty = kzalloc(length * sizeof(unsigned long), GFP_KERNEL);
	if (!buffer->dirty)
		return -ENOMEM;
	return 0;
}

struct ion_vma_list {
	struct list_head list;
	struct vm_area_struct *vma;
};

static void ion_buffer_sync_for_device(struct ion_buffer *buffer,
				       struct device *dev,
				       enum dma_data_direction dir)
{
	struct scatterlist *sg;
	int i;
	struct ion_vma_list *vma_list;

	pr_debug("%s: syncing for device %s\n", __func__,
		 dev ? dev_name(dev) : "null");

	if (!ion_buffer_fault_user_mappings(buffer))
		return;

	mutex_lock(&buffer->lock);
	for_each_sg(buffer->sg_table->sgl, sg, buffer->sg_table->nents, i) {
		if (!test_bit(i, buffer->dirty))
			continue;
		dma_sync_sg_for_device(dev, sg, 1, dir);
		clear_bit(i, buffer->dirty);
	}
	list_for_each_entry(vma_list, &buffer->vmas, list) {
		struct vm_area_struct *vma = vma_list->vma;

		zap_page_range(vma, vma->vm_start, vma->vm_end - vma->vm_start,
			       NULL);
	}
	mutex_unlock(&buffer->lock);
}

int ion_vm_fault(struct vm_area_struct *vma, struct vm_fault *vmf)
{
	struct ion_buffer *buffer = vma->vm_private_data;
	struct scatterlist *sg;
	int i;

	mutex_lock(&buffer->lock);
	set_bit(vmf->pgoff, buffer->dirty);

	for_each_sg(buffer->sg_table->sgl, sg, buffer->sg_table->nents, i) {
		if (i != vmf->pgoff)
			continue;
		dma_sync_sg_for_cpu(NULL, sg, 1, DMA_BIDIRECTIONAL);
		vm_insert_page(vma, (unsigned long)vmf->virtual_address,
			       sg_page(sg));
		break;
	}
	mutex_unlock(&buffer->lock);
	return VM_FAULT_NOPAGE;
}

static void ion_vm_open(struct vm_area_struct *vma)
{
	struct ion_buffer *buffer = vma->vm_private_data;
	struct ion_vma_list *vma_list;

	vma_list = kmalloc(sizeof(struct ion_vma_list), GFP_KERNEL);
	if (!vma_list)
		return;
	vma_list->vma = vma;
	mutex_lock(&buffer->lock);
	list_add(&vma_list->list, &buffer->vmas);
	mutex_unlock(&buffer->lock);
	pr_debug("%s: adding %p\n", __func__, vma);
}

static void ion_vm_close(struct vm_area_struct *vma)
{
	struct ion_buffer *buffer = vma->vm_private_data;
	struct ion_vma_list *vma_list, *tmp;

	pr_debug("%s\n", __func__);
	mutex_lock(&buffer->lock);
	list_for_each_entry_safe(vma_list, tmp, &buffer->vmas, list) {
		if (vma_list->vma != vma)
			continue;
		list_del(&vma_list->list);
		kfree(vma_list);
		pr_debug("%s: deleting %p\n", __func__, vma);
		break;
	}
	mutex_unlock(&buffer->lock);

	if (buffer->heap->ops->unmap_user)
		buffer->heap->ops->unmap_user(buffer->heap, buffer);
}

struct vm_operations_struct ion_vma_ops = {
	.open = ion_vm_open,
	.close = ion_vm_close,
	.fault = ion_vm_fault,
};

static int ion_mmap(struct dma_buf *dmabuf, struct vm_area_struct *vma)
{
	struct ion_buffer *buffer = dmabuf->priv;
	int ret = 0;

	if (!buffer->heap->ops->map_user) {
		pr_err("%s: this heap does not define a method for mapping "
		       "to userspace\n", __func__);
		return -EINVAL;
	}

	if (ion_buffer_fault_user_mappings(buffer)) {
		vma->vm_private_data = buffer;
		vma->vm_ops = &ion_vma_ops;
		vma->vm_flags |= VM_MIXEDMAP;
		ion_vm_open(vma);
		return 0;
	}

	if (!(buffer->flags & ION_FLAG_CACHED))
		vma->vm_page_prot = pgprot_writecombine(vma->vm_page_prot);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	mutex_lock(&dev->lock);
	if (client->task) {
		rb_erase(&client->node, &dev->user_clients);
		put_task_struct(client->task);
	} else {
		rb_erase(&client->node, &dev->kernel_clients);
	}
	debugfs_remove_recursive(client->debug_root);
	mutex_unlock(&dev->lock);

	kfree(client);
}

static void ion_client_get(struct ion_client *client)
{
	kref_get(&client->ref);
}

static int ion_client_put(struct ion_client *client)
{
	return kref_put(&client->ref, _ion_client_destroy);
}

void ion_client_destroy(struct ion_client *client)
{
	ion_client_put(client);
}

struct ion_client *ion_get_user_client(unsigned int fd_client)
{
	struct file *file;
	struct ion_client *client = NULL;

	file = fget(fd_client);
	if (!file)
		return NULL;

	if (file->private_data) {
		client = file->private_data;
		client = ion_client_lookup(client->dev, current->group_leader);

		if (client && (file->private_data != client)) {
			ion_client_put(client);
			client = NULL;
		}

	}

	fput(file);

	if (client == NULL)
		pr_err("%s: not a valid file descriptor of user client for the"
			" current process\n", __func__);

	return client;
}

void ion_put_user_client(struct ion_client *user_client)
{
	ion_client_put(user_client);
}

static int ion_share_release(struct inode *inode, struct file* file)
{
	struct ion_buffer *buffer = file->private_data;

	pr_debug("%s: %d\n", __func__, __LINE__);
	/* drop the reference to the buffer -- this prevents the
	   buffer from going away because the client holding it exited
	   while it was being passed */
	ion_buffer_put(buffer);
	return 0;
}

static void ion_vma_open(struct vm_area_struct *vma)
{

	struct ion_buffer *buffer = vma->vm_file->private_data;
	struct ion_handle *handle = vma->vm_private_data;
	struct ion_client *client;

	pr_debug("%s: %d\n", __func__, __LINE__);
	/* check that the client still exists and take a reference so
	   it can't go away until this vma is closed */
	client = ion_client_lookup(buffer->dev, current->group_leader);
	if (IS_ERR_OR_NULL(client)) {
		vma->vm_private_data = NULL;
		return;
	}

	if (!ion_handle_validate(client, handle)) {
		ion_client_put(client);
		vma->vm_private_data = NULL;
		return;
	}

	ion_handle_get(handle);

	pr_debug("%s: %d client_cnt %d handle_cnt %d alloc_cnt %d\n",
		 __func__, __LINE__,
		 atomic_read(&client->ref.refcount),
		 atomic_read(&handle->ref.refcount),
		 atomic_read(&buffer->ref.refcount));
}

static void ion_vma_close(struct vm_area_struct *vma)
{
	struct ion_handle *handle = vma->vm_private_data;
	struct ion_buffer *buffer = vma->vm_file->private_data;
	struct ion_client *client;

	pr_debug("%s: %d\n", __func__, __LINE__);
	/* this indicates the client is gone, nothing to do here */
	if (!handle)
		return;
	client = handle->client;
	pr_debug("%s: %d client_cnt %d handle_cnt %d alloc_cnt %d\n",
		 __func__, __LINE__,
		 atomic_read(&client->ref.refcount),
		 atomic_read(&handle->ref.refcount),
		 atomic_read(&buffer->ref.refcount));
	ion_handle_put(handle);
	ion_client_put(client);
	pr_debug("%s: %d client_cnt %d handle_cnt %d alloc_cnt %d\n",
		 __func__, __LINE__,
		 atomic_read(&client->ref.refcount),
		 atomic_read(&handle->ref.refcount),
		 atomic_read(&buffer->ref.refcount));
}

static struct vm_operations_struct ion_vm_ops = {
	.open = ion_vma_open,
	.close = ion_vma_close,
};

static int ion_share_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct ion_buffer *buffer = file->private_data;
	unsigned long size = vma->vm_end - vma->vm_start;
	struct ion_client *client;
	struct ion_handle *handle;
	int ret;

	pr_debug("%s: %d\n", __func__, __LINE__);
	/* make sure the client still exists, it's possible for the client to
	   have gone away but the map/share fd still to be around, take
	   a reference to it so it can't go away while this mapping exists */
	client = ion_client_lookup(buffer->dev, current->group_leader);
	if (IS_ERR_OR_NULL(client)) {
		pr_err("%s: trying to mmap an ion handle in a process with no "
		       "ion client\n", __func__);
		return -EINVAL;
	}

	if (((vma->vm_pgoff << PAGE_SHIFT) >= buffer->size) ||
		(size > (buffer->size - (vma->vm_pgoff << PAGE_SHIFT)))) {
		pr_err("%s: trying to map larger area than handle has available"
		       "\n", __func__);
		ret = -EINVAL;
		goto err;
	}

	/* find the handle and take a reference to it */
	handle = ion_import(client, buffer);
	if (IS_ERR_OR_NULL(handle)) {
		ret = -EINVAL;
		goto err;
	}

	if (!handle->buffer->heap->ops->map_user) {
		pr_err("%s: this heap does not define a method for mapping "
		       "to userspace\n", __func__);
		ret = -EINVAL;
		goto err1;
	}
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	mutex_lock(&buffer->lock);
	/* now map it to userspace */
	ret = buffer->heap->ops->map_user(buffer->heap, buffer, vma);
	mutex_unlock(&buffer->lock);
<<<<<<< HEAD
<<<<<<< HEAD

	if (ret)
		pr_err("%s: failure mapping buffer to userspace\n",
		       __func__);

	return ret;
}

static void ion_dma_buf_release(struct dma_buf *dmabuf)
{
	struct ion_buffer *buffer = dmabuf->priv;
	ion_buffer_put(buffer);
}

static void *ion_dma_buf_kmap(struct dma_buf *dmabuf, unsigned long offset)
{
	struct ion_buffer *buffer = dmabuf->priv;
	return buffer->vaddr + offset * PAGE_SIZE;
}

static void ion_dma_buf_kunmap(struct dma_buf *dmabuf, unsigned long offset,
			       void *ptr)
{
	return;
}

static int ion_dma_buf_begin_cpu_access(struct dma_buf *dmabuf, size_t start,
					size_t len,
					enum dma_data_direction direction)
{
	struct ion_buffer *buffer = dmabuf->priv;
	void *vaddr;

	if (!buffer->heap->ops->map_kernel) {
		pr_err("%s: map kernel is not implemented by this heap.\n",
		       __func__);
		return -ENODEV;
	}

	mutex_lock(&buffer->lock);
	vaddr = ion_buffer_kmap_get(buffer);
	mutex_unlock(&buffer->lock);
	if (IS_ERR(vaddr))
		return PTR_ERR(vaddr);
	if (!vaddr)
		return -ENOMEM;
	return 0;
}

static void ion_dma_buf_end_cpu_access(struct dma_buf *dmabuf, size_t start,
				       size_t len,
				       enum dma_data_direction direction)
{
	struct ion_buffer *buffer = dmabuf->priv;

	mutex_lock(&buffer->lock);
	ion_buffer_kmap_put(buffer);
	mutex_unlock(&buffer->lock);
}

struct dma_buf_ops dma_buf_ops = {
	.map_dma_buf = ion_map_dma_buf,
	.unmap_dma_buf = ion_unmap_dma_buf,
	.mmap = ion_mmap,
	.release = ion_dma_buf_release,
	.begin_cpu_access = ion_dma_buf_begin_cpu_access,
	.end_cpu_access = ion_dma_buf_end_cpu_access,
	.kmap_atomic = ion_dma_buf_kmap,
	.kunmap_atomic = ion_dma_buf_kunmap,
	.kmap = ion_dma_buf_kmap,
	.kunmap = ion_dma_buf_kunmap,
};

struct dma_buf *ion_share_dma_buf(struct ion_client *client,
						struct ion_handle *handle)
{
	struct ion_buffer *buffer;
	struct dma_buf *dmabuf;
	bool valid_handle;

	mutex_lock(&client->lock);
	valid_handle = ion_handle_validate(client, handle);
	if (!valid_handle) {
		WARN(1, "%s: invalid handle passed to share.\n", __func__);
		mutex_unlock(&client->lock);
		return ERR_PTR(-EINVAL);
	}
	buffer = handle->buffer;
	ion_buffer_get(buffer);
	mutex_unlock(&client->lock);

	dmabuf = dma_buf_export(buffer, &dma_buf_ops, buffer->size, O_RDWR);
	if (IS_ERR(dmabuf)) {
		ion_buffer_put(buffer);
		return dmabuf;
	}

	return dmabuf;
}
EXPORT_SYMBOL(ion_share_dma_buf);

int ion_share_dma_buf_fd(struct ion_client *client, struct ion_handle *handle)
{
	struct dma_buf *dmabuf;
	int fd;

	dmabuf = ion_share_dma_buf(client, handle);
	if (IS_ERR(dmabuf))
		return PTR_ERR(dmabuf);

	fd = dma_buf_fd(dmabuf, O_CLOEXEC);
	if (fd < 0)
		dma_buf_put(dmabuf);

	return fd;
}
EXPORT_SYMBOL(ion_share_dma_buf_fd);

struct ion_handle *ion_import_dma_buf(struct ion_client *client, int fd)
{
	struct dma_buf *dmabuf;
	struct ion_buffer *buffer;
	struct ion_handle *handle;
	int ret;

	dmabuf = dma_buf_get(fd);
	if (IS_ERR_OR_NULL(dmabuf))
		return ERR_PTR(PTR_ERR(dmabuf));
	/* if this memory came from ion */

	if (dmabuf->ops != &dma_buf_ops) {
		pr_err("%s: can not import dmabuf from another exporter\n",
		       __func__);
		dma_buf_put(dmabuf);
		return ERR_PTR(-EINVAL);
	}
	buffer = dmabuf->priv;

	mutex_lock(&client->lock);
	/* if a handle exists for this buffer just take a reference to it */
	handle = ion_handle_lookup(client, buffer);
	if (!IS_ERR_OR_NULL(handle)) {
		ion_handle_get(handle);
		mutex_unlock(&client->lock);
		goto end;
	}
	mutex_unlock(&client->lock);

	handle = ion_handle_create(client, buffer);
	if (IS_ERR_OR_NULL(handle))
		goto end;

	mutex_lock(&client->lock);
	ret = ion_handle_add(client, handle);
	mutex_unlock(&client->lock);
	if (ret) {
		ion_handle_put(handle);
		handle = ERR_PTR(ret);
	}

end:
	dma_buf_put(dmabuf);
	return handle;
}
EXPORT_SYMBOL(ion_import_dma_buf);

static int ion_sync_for_device(struct ion_client *client, int fd)
{
	struct dma_buf *dmabuf;
	struct ion_buffer *buffer;

	dmabuf = dma_buf_get(fd);
	if (IS_ERR_OR_NULL(dmabuf))
		return PTR_ERR(dmabuf);

	/* if this memory came from ion */
	if (dmabuf->ops != &dma_buf_ops) {
		pr_err("%s: can not sync dmabuf from another exporter\n",
		       __func__);
		dma_buf_put(dmabuf);
		return -EINVAL;
	}
	buffer = dmabuf->priv;

	dma_sync_sg_for_device(NULL, buffer->sg_table->sgl,
			       buffer->sg_table->nents, DMA_BIDIRECTIONAL);
	dma_buf_put(dmabuf);
	return 0;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (ret) {
		pr_err("%s: failure mapping buffer to userspace\n",
		       __func__);
		goto err1;
	}

	vma->vm_ops = &ion_vm_ops;
	/* move the handle into the vm_private_data so we can access it from
	   vma_open/close */
	vma->vm_private_data = handle;
	pr_debug("%s: %d client_cnt %d handle_cnt %d alloc_cnt %d\n",
		 __func__, __LINE__,
		 atomic_read(&client->ref.refcount),
		 atomic_read(&handle->ref.refcount),
		 atomic_read(&buffer->ref.refcount));
	return 0;

err1:
	/* drop the reference to the handle */
	ion_handle_put(handle);
err:
	/* drop the reference to the client */
	ion_client_put(client);
	return ret;
}

static const struct file_operations ion_share_fops = {
	.owner		= THIS_MODULE,
	.release	= ion_share_release,
	.mmap		= ion_share_mmap,
};

static int ion_ioctl_share(struct file *parent, struct ion_client *client,
			   struct ion_handle *handle)
{
	int fd = get_unused_fd();
	struct file *file;

	if (fd < 0)
		return fd;

	file = anon_inode_getfile("ion_share_fd", &ion_share_fops,
				  handle->buffer, O_RDWR);
	if (IS_ERR_OR_NULL(file))
		goto err;
	ion_buffer_get(handle->buffer);
	fd_install(fd, file);

	return fd;

err:
	put_unused_fd(fd);
	return -ENFILE;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static long ion_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	struct ion_client *client = filp->private_data;

	switch (cmd) {
	case ION_IOC_ALLOC:
	{
		struct ion_allocation_data data;
<<<<<<< HEAD
<<<<<<< HEAD
		struct ion_handle *handle;

		if (copy_from_user(&data, (void __user *)arg, sizeof(data)))
			return -EFAULT;
		handle = ion_alloc(client, data.len, data.align,
					     data.heap_mask, data.flags);

		if (IS_ERR(handle))
			return PTR_ERR(handle);

		data.handle = (ion_user_handle_t)handle->id;

		if (copy_to_user((void __user *)arg, &data, sizeof(data))) {
			ion_free(client, handle);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

		if (copy_from_user(&data, (void __user *)arg, sizeof(data)))
			return -EFAULT;
		data.handle = ion_alloc(client, data.len, data.align,
					     data.flags);

		if (IS_ERR(data.handle))
			return PTR_ERR(data.handle);

		if (copy_to_user((void __user *)arg, &data, sizeof(data))) {
			ion_free(client, data.handle);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			return -EFAULT;
		}
		break;
	}
	case ION_IOC_FREE:
	{
		struct ion_handle_data data;
<<<<<<< HEAD
<<<<<<< HEAD
		struct ion_handle *handle;
=======
		bool valid;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		bool valid;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

		if (copy_from_user(&data, (void __user *)arg,
				   sizeof(struct ion_handle_data)))
			return -EFAULT;
<<<<<<< HEAD
<<<<<<< HEAD
		handle = ion_handle_get_by_id(client, (int)data.handle);
		if (IS_ERR(handle))
			return PTR_ERR(handle);
		ion_free(client, handle);
		ion_handle_put(handle);
		break;
	}
	case ION_IOC_SHARE:
	case ION_IOC_MAP:
	{
		struct ion_fd_data data;
		struct ion_handle *handle;
		if (copy_from_user(&data, (void __user *)arg, sizeof(data)))
			return -EFAULT;

		handle = ion_handle_get_by_id(client, (int)data.handle);
		if (IS_ERR(handle))
			return PTR_ERR(handle);
		data.fd = ion_share_dma_buf_fd(client, handle);
		ion_handle_put(handle);
		if (copy_to_user((void __user *)arg, &data, sizeof(data)))
			return -EFAULT;
		if (data.fd < 0)
			return data.fd;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		mutex_lock(&client->lock);
		valid = ion_handle_validate(client, data.handle);
		mutex_unlock(&client->lock);
		if (!valid)
			return -EINVAL;
		ion_free(client, data.handle);
		break;
	}
	case ION_IOC_MAP:
	case ION_IOC_SHARE:
	{
		struct ion_fd_data data;

		if (copy_from_user(&data, (void __user *)arg, sizeof(data)))
			return -EFAULT;
		mutex_lock(&client->lock);
		if (!ion_handle_validate(client, data.handle)) {
			pr_err("%s: invalid handle passed to share ioctl.\n",
			       __func__);
			mutex_unlock(&client->lock);
			return -EINVAL;
		}
		data.fd = ion_ioctl_share(filp, client, data.handle);
		mutex_unlock(&client->lock);
		if (copy_to_user((void __user *)arg, &data, sizeof(data)))
			return -EFAULT;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		break;
	}
	case ION_IOC_IMPORT:
	{
		struct ion_fd_data data;
<<<<<<< HEAD
<<<<<<< HEAD
		struct ion_handle *handle;
		int ret = 0;
		if (copy_from_user(&data, (void __user *)arg,
				   sizeof(struct ion_fd_data)))
			return -EFAULT;
		handle = ion_import_dma_buf(client, data.fd);
		if (IS_ERR(handle))
			ret = PTR_ERR(handle);
		else
			data.handle = (ion_user_handle_t)handle->id;

		if (copy_to_user((void __user *)arg, &data,
				 sizeof(struct ion_fd_data)))
			return -EFAULT;
		if (ret < 0)
			return ret;
		break;
	}
	case ION_IOC_SYNC:
	{
		struct ion_fd_data data;
		if (copy_from_user(&data, (void __user *)arg,
				   sizeof(struct ion_fd_data)))
			return -EFAULT;
		ion_sync_for_device(client, data.fd);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		if (copy_from_user(&data, (void __user *)arg,
				   sizeof(struct ion_fd_data)))
			return -EFAULT;

		data.handle = ion_import_fd(client, data.fd);
		if (IS_ERR(data.handle))
			data.handle = NULL;
		if (copy_to_user((void __user *)arg, &data,
				 sizeof(struct ion_fd_data)))
			return -EFAULT;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		break;
	}
	case ION_IOC_CUSTOM:
	{
		struct ion_device *dev = client->dev;
		struct ion_custom_data data;

		if (!dev->custom_ioctl)
			return -ENOTTY;
		if (copy_from_user(&data, (void __user *)arg,
				sizeof(struct ion_custom_data)))
			return -EFAULT;
		return dev->custom_ioctl(client, data.cmd, data.arg);
	}
<<<<<<< HEAD
<<<<<<< HEAD
	case ION_IOC_CLEAN_CACHES:
		return client->dev->custom_ioctl(client,
						ION_IOC_CLEAN_CACHES, arg);
	case ION_IOC_INV_CACHES:
		return client->dev->custom_ioctl(client,
						ION_IOC_INV_CACHES, arg);
	case ION_IOC_CLEAN_INV_CACHES:
		return client->dev->custom_ioctl(client,
						ION_IOC_CLEAN_INV_CACHES, arg);
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	default:
		return -ENOTTY;
	}
	return 0;
}

static int ion_release(struct inode *inode, struct file *file)
{
	struct ion_client *client = file->private_data;

	pr_debug("%s: %d\n", __func__, __LINE__);
<<<<<<< HEAD
<<<<<<< HEAD
	ion_client_destroy(client);
=======
	ion_client_put(client);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	ion_client_put(client);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return 0;
}

static int ion_open(struct inode *inode, struct file *file)
{
	struct miscdevice *miscdev = file->private_data;
	struct ion_device *dev = container_of(miscdev, struct ion_device, dev);
	struct ion_client *client;
<<<<<<< HEAD
<<<<<<< HEAD
	char debug_name[64];

	pr_debug("%s: %d\n", __func__, __LINE__);
	snprintf(debug_name, 64, "%u", task_pid_nr(current->group_leader));
	client = ion_client_create(dev, debug_name);
=======

	pr_debug("%s: %d\n", __func__, __LINE__);
	client = ion_client_create(dev, -1, "user");
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======

	pr_debug("%s: %d\n", __func__, __LINE__);
	client = ion_client_create(dev, -1, "user");
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (IS_ERR_OR_NULL(client))
		return PTR_ERR(client);
	file->private_data = client;

	return 0;
}

static const struct file_operations ion_fops = {
	.owner          = THIS_MODULE,
	.open           = ion_open,
	.release        = ion_release,
	.unlocked_ioctl = ion_ioctl,
};

static size_t ion_debug_heap_total(struct ion_client *client,
<<<<<<< HEAD
<<<<<<< HEAD
				   unsigned int id)
=======
				   enum ion_heap_type type)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
				   enum ion_heap_type type)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	size_t size = 0;
	struct rb_node *n;

	mutex_lock(&client->lock);
	for (n = rb_first(&client->handles); n; n = rb_next(n)) {
		struct ion_handle *handle = rb_entry(n,
						     struct ion_handle,
						     node);
<<<<<<< HEAD
<<<<<<< HEAD
		if (handle->buffer->heap->id == id)
=======
		if (handle->buffer->heap->type == type)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		if (handle->buffer->heap->type == type)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			size += handle->buffer->size;
	}
	mutex_unlock(&client->lock);
	return size;
}

<<<<<<< HEAD
<<<<<<< HEAD
/**
 * Create a mem_map of the heap.
 * @param s seq_file to log error message to.
 * @param heap The heap to create mem_map for.
 * @param mem_map The mem map to be created.
 */
void ion_debug_mem_map_create(struct seq_file *s, struct ion_heap *heap,
			      struct list_head *mem_map)
{
	struct ion_device *dev = heap->dev;
	struct rb_node *cnode;
	size_t size;
	struct ion_client *client;

	if (!heap->ops->phys)
		return;

	down_read(&dev->lock);
	for (cnode = rb_first(&dev->clients); cnode; cnode = rb_next(cnode)) {
		struct rb_node *hnode;
		client = rb_entry(cnode, struct ion_client, node);

		mutex_lock(&client->lock);
		for (hnode = rb_first(&client->handles);
		     hnode;
		     hnode = rb_next(hnode)) {
			struct ion_handle *handle = rb_entry(
				hnode, struct ion_handle, node);
			if (handle->buffer->heap == heap) {
				struct mem_map_data *data =
					kzalloc(sizeof(*data), GFP_KERNEL);
				if (!data)
					goto inner_error;
				heap->ops->phys(heap, handle->buffer,
							&(data->addr), &size);
				data->size = (unsigned long) size;
				data->addr_end = data->addr + data->size - 1;
				data->client_name = kstrdup(client->name,
							GFP_KERNEL);
				if (!data->client_name) {
					kfree(data);
					goto inner_error;
				}
				list_add(&data->node, mem_map);
			}
		}
		mutex_unlock(&client->lock);
	}
	up_read(&dev->lock);
	return;

inner_error:
	seq_puts(s,
		"ERROR: out of memory. Part of memory map will not be logged\n");
	mutex_unlock(&client->lock);
	up_read(&dev->lock);
}

/**
 * Free the memory allocated by ion_debug_mem_map_create
 * @param mem_map The mem map to free.
 */
static void ion_debug_mem_map_destroy(struct list_head *mem_map)
{
	if (mem_map) {
		struct mem_map_data *data, *tmp;
		list_for_each_entry_safe(data, tmp, mem_map, node) {
			list_del(&data->node);
			kfree(data->client_name);
			kfree(data);
		}
	}
}

static int mem_map_cmp(void *priv, struct list_head *a, struct list_head *b)
{
	struct mem_map_data *d1, *d2;
	d1 = list_entry(a, struct mem_map_data, node);
	d2 = list_entry(b, struct mem_map_data, node);
	if (d1->addr == d2->addr)
		return d1->size - d2->size;
	return d1->addr - d2->addr;
}

/**
 * Print heap debug information.
 * @param s seq_file to log message to.
 * @param heap pointer to heap that we will print debug information for.
 */
static void ion_heap_print_debug(struct seq_file *s, struct ion_heap *heap)
{
	if (heap->ops->print_debug) {
		struct list_head mem_map = LIST_HEAD_INIT(mem_map);
		ion_debug_mem_map_create(s, heap, &mem_map);
		list_sort(NULL, &mem_map, mem_map_cmp);
		heap->ops->print_debug(heap, s, &mem_map);
		ion_debug_mem_map_destroy(&mem_map);
	}
}

=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static int ion_debug_heap_show(struct seq_file *s, void *unused)
{
	struct ion_heap *heap = s->private;
	struct ion_device *dev = heap->dev;
	struct rb_node *n;
<<<<<<< HEAD
<<<<<<< HEAD
	size_t total_size = 0;
	size_t total_orphaned_size = 0;

	seq_printf(s, "%16.s %16.s %16.s\n", "client", "pid", "size");
	seq_printf(s, "----------------------------------------------------\n");

	down_read(&dev->lock);
	for (n = rb_first(&dev->clients); n; n = rb_next(n)) {
		struct ion_client *client = rb_entry(n, struct ion_client,
						     node);
		size_t size = ion_debug_heap_total(client, heap->id);
		if (!size)
			continue;
		if (client->task) {
			char task_comm[TASK_COMM_LEN];

			get_task_comm(task_comm, client->task);
			seq_printf(s, "%16.s %16u %16u\n", task_comm,
				   client->pid, size);
		} else {
			seq_printf(s, "%16.s %16u %16u\n", client->name,
				   client->pid, size);
		}
	}
	up_read(&dev->lock);
	seq_printf(s, "----------------------------------------------------\n");
	seq_printf(s, "orphaned allocations (info is from last known client):"
		   "\n");
	mutex_lock(&dev->buffer_lock);
	for (n = rb_first(&dev->buffers); n; n = rb_next(n)) {
		struct ion_buffer *buffer = rb_entry(n, struct ion_buffer,
						     node);
		if (buffer->heap->id != heap->id)
			continue;
		total_size += buffer->size;
		if (!buffer->handle_count) {
			seq_printf(s, "%16.s %16u %16u %d %d\n", buffer->task_comm,
				   buffer->pid, buffer->size, buffer->kmap_cnt,
				   atomic_read(&buffer->ref.refcount));
			total_orphaned_size += buffer->size;
		}
	}
	mutex_unlock(&dev->buffer_lock);
	seq_printf(s, "----------------------------------------------------\n");
	seq_printf(s, "%16.s %16u\n", "total orphaned",
		   total_orphaned_size);
	seq_printf(s, "%16.s %16u\n", "total ", total_size);
	seq_printf(s, "----------------------------------------------------\n");

	if (heap->debug_show)
		heap->debug_show(heap, s, unused);

	ion_heap_print_debug(s, heap);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	seq_printf(s, "%16.s %16.s %16.s\n", "client", "pid", "size");
	for (n = rb_first(&dev->user_clients); n; n = rb_next(n)) {
		struct ion_client *client = rb_entry(n, struct ion_client,
						     node);
		char task_comm[TASK_COMM_LEN];
		size_t size = ion_debug_heap_total(client, heap->type);
		if (!size)
			continue;

		get_task_comm(task_comm, client->task);
		seq_printf(s, "%16.s %16u %16u\n", task_comm, client->pid,
			   size);
	}

	for (n = rb_first(&dev->kernel_clients); n; n = rb_next(n)) {
		struct ion_client *client = rb_entry(n, struct ion_client,
						     node);
		size_t size = ion_debug_heap_total(client, heap->type);
		if (!size)
			continue;
		seq_printf(s, "%16.s %16u %16u\n", client->name, client->pid,
			   size);
	}
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return 0;
}

static int ion_debug_heap_open(struct inode *inode, struct file *file)
{
	return single_open(file, ion_debug_heap_show, inode->i_private);
}

static const struct file_operations debug_heap_fops = {
	.open = ion_debug_heap_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

<<<<<<< HEAD
<<<<<<< HEAD
#ifdef DEBUG_HEAP_SHRINKER
static int debug_shrink_set(void *data, u64 val)
{
        struct ion_heap *heap = data;
        struct shrink_control sc;
        int objs;

        sc.gfp_mask = -1;
        sc.nr_to_scan = 0;

        if (!val)
                return 0;

        objs = heap->shrinker.shrink(&heap->shrinker, &sc);
        sc.nr_to_scan = objs;

        heap->shrinker.shrink(&heap->shrinker, &sc);
        return 0;
}

static int debug_shrink_get(void *data, u64 *val)
{
        struct ion_heap *heap = data;
        struct shrink_control sc;
        int objs;

        sc.gfp_mask = -1;
        sc.nr_to_scan = 0;

        objs = heap->shrinker.shrink(&heap->shrinker, &sc);
        *val = objs;
        return 0;
}

DEFINE_SIMPLE_ATTRIBUTE(debug_shrink_fops, debug_shrink_get,
                        debug_shrink_set, "%llu\n");
#endif

void ion_device_add_heap(struct ion_device *dev, struct ion_heap *heap)
{
	struct dentry *debug_file;

	if (!heap->ops->allocate || !heap->ops->free || !heap->ops->map_dma ||
	    !heap->ops->unmap_dma)
		pr_err("%s: can not add heap with invalid ops struct.\n",
		       __func__);

	if (heap->flags & ION_HEAP_FLAG_DEFER_FREE)
		ion_heap_init_deferred_free(heap);

	heap->dev = dev;
	down_write(&dev->lock);
	/* use negative heap->id to reverse the priority -- when traversing
	   the list later attempt higher id numbers first */
	plist_node_init(&heap->node, -heap->id);
	plist_add(&heap->node, &dev->heaps);
	debug_file = debugfs_create_file(heap->name, 0664,
					dev->heaps_debug_root, heap,
					&debug_heap_fops);

	if (!debug_file) {
		char buf[256], *path;
		path = dentry_path(dev->heaps_debug_root, buf, 256);
		pr_err("Failed to created heap debugfs at %s/%s\n",
			path, heap->name);
	}

#ifdef DEBUG_HEAP_SHRINKER
	if (heap->shrinker.shrink) {
		char debug_name[64];

		snprintf(debug_name, 64, "%s_shrink", heap->name);
		debug_file = debugfs_create_file(
			debug_name, 0644, dev->heaps_debug_root, heap,
			&debug_shrink_fops);
		if (!debug_file) {
			char buf[256], *path;
			path = dentry_path(dev->heaps_debug_root, buf, 256);
			pr_err("Failed to created heap shrinker debugfs at %s/%s\n",
				path, debug_name);
		}
	}
#endif
	up_write(&dev->lock);
}

int ion_secure_handle(struct ion_client *client, struct ion_handle *handle,
			int version, void *data, int flags)
{
	int ret = -EINVAL;
	struct ion_heap *heap;
	struct ion_buffer *buffer;

	mutex_lock(&client->lock);
	if (!ion_handle_validate(client, handle)) {
		WARN(1, "%s: invalid handle passed to secure.\n", __func__);
		goto out_unlock;
	}

	buffer = handle->buffer;
	heap = buffer->heap;

	if (!ion_heap_allow_handle_secure(heap->type)) {
		pr_err("%s: cannot secure buffer from non secure heap\n",
			__func__);
		goto out_unlock;
	}

	BUG_ON(!buffer->heap->ops->secure_buffer);
	/*
	 * Protect the handle via the client lock to ensure we aren't
	 * racing with free
	 */
	ret = buffer->heap->ops->secure_buffer(buffer, version, data, flags);

out_unlock:
	mutex_unlock(&client->lock);
	return ret;
}

int ion_unsecure_handle(struct ion_client *client, struct ion_handle *handle)
{
	int ret = -EINVAL;
	struct ion_heap *heap;
	struct ion_buffer *buffer;

	mutex_lock(&client->lock);
	if (!ion_handle_validate(client, handle)) {
		WARN(1, "%s: invalid handle passed to secure.\n", __func__);
		goto out_unlock;
	}

	buffer = handle->buffer;
	heap = buffer->heap;

	if (!ion_heap_allow_handle_secure(heap->type)) {
		pr_err("%s: cannot secure buffer from non secure heap\n",
			__func__);
		goto out_unlock;
	}

	BUG_ON(!buffer->heap->ops->unsecure_buffer);
	/*
	 * Protect the handle via the client lock to ensure we aren't
	 * racing with free
	 */
	ret = buffer->heap->ops->unsecure_buffer(buffer, 0);

out_unlock:
	mutex_unlock(&client->lock);
	return ret;
}

int ion_secure_heap(struct ion_device *dev, int heap_id, int version,
			void *data)
{
	int ret_val = 0;
	struct ion_heap *heap;

	/*
	 * traverse the list of heaps available in this system
	 * and find the heap that is specified.
	 */
	down_write(&dev->lock);
	plist_for_each_entry(heap, &dev->heaps, node) {
		if (!ion_heap_allow_heap_secure(heap->type))
			continue;
		if (ION_HEAP(heap->id) != heap_id)
			continue;
		if (heap->ops->secure_heap)
			ret_val = heap->ops->secure_heap(heap, version, data);
		else
			ret_val = -EINVAL;
		break;
	}
	up_write(&dev->lock);
	return ret_val;
}
EXPORT_SYMBOL(ion_secure_heap);

int ion_walk_heaps(struct ion_client *client, int heap_id, void *data,
			int (*f)(struct ion_heap *heap, void *data))
{
	int ret_val = -EINVAL;
	struct ion_heap *heap;
	struct ion_device *dev = client->dev;
	/*
	 * traverse the list of heaps available in this system
	 * and find the heap that is specified.
	 */
	down_write(&dev->lock);
	plist_for_each_entry(heap, &dev->heaps, node) {
		if (ION_HEAP(heap->id) != heap_id)
			continue;
		ret_val = f(heap, data);
		break;
	}
	up_write(&dev->lock);
	return ret_val;
}
EXPORT_SYMBOL(ion_walk_heaps);

int ion_unsecure_heap(struct ion_device *dev, int heap_id, int version,
			void *data)
{
	int ret_val = 0;
	struct ion_heap *heap;

	/*
	 * traverse the list of heaps available in this system
	 * and find the heap that is specified.
	 */
	down_write(&dev->lock);
	plist_for_each_entry(heap, &dev->heaps, node) {
		if (!ion_heap_allow_heap_secure(heap->type))
			continue;
		if (ION_HEAP(heap->id) != heap_id)
			continue;
		if (heap->ops->secure_heap)
			ret_val = heap->ops->unsecure_heap(heap, version, data);
		else
			ret_val = -EINVAL;
		break;
	}
	up_write(&dev->lock);
	return ret_val;
}
EXPORT_SYMBOL(ion_unsecure_heap);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
void ion_device_add_heap(struct ion_device *dev, struct ion_heap *heap)
{
	struct rb_node **p = &dev->heaps.rb_node;
	struct rb_node *parent = NULL;
	struct ion_heap *entry;

	heap->dev = dev;
	mutex_lock(&dev->lock);
	while (*p) {
		parent = *p;
		entry = rb_entry(parent, struct ion_heap, node);

		if (heap->id < entry->id) {
			p = &(*p)->rb_left;
		} else if (heap->id > entry->id) {
			p = &(*p)->rb_right;
		} else {
			pr_err("%s: can not insert multiple heaps with "
				"id %d\n", __func__, heap->id);
			goto end;
		}
	}

	rb_link_node(&heap->node, parent, p);
	rb_insert_color(&heap->node, &dev->heaps);
	debugfs_create_file(heap->name, 0664, dev->debug_root, heap,
			    &debug_heap_fops);
end:
	mutex_unlock(&dev->lock);
}
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

struct ion_device *ion_device_create(long (*custom_ioctl)
				     (struct ion_client *client,
				      unsigned int cmd,
				      unsigned long arg))
{
	struct ion_device *idev;
	int ret;

	idev = kzalloc(sizeof(struct ion_device), GFP_KERNEL);
	if (!idev)
		return ERR_PTR(-ENOMEM);

	idev->dev.minor = MISC_DYNAMIC_MINOR;
	idev->dev.name = "ion";
	idev->dev.fops = &ion_fops;
	idev->dev.parent = NULL;
	ret = misc_register(&idev->dev);
	if (ret) {
		pr_err("ion: failed to register misc device.\n");
		return ERR_PTR(ret);
	}

	idev->debug_root = debugfs_create_dir("ion", NULL);
<<<<<<< HEAD
<<<<<<< HEAD
	if (!idev->debug_root) {
		pr_err("ion: failed to create debugfs root directory.\n");
		goto debugfs_done;
	}
	idev->heaps_debug_root = debugfs_create_dir("heaps", idev->debug_root);
	if (!idev->heaps_debug_root) {
		pr_err("ion: failed to create debugfs heaps directory.\n");
		goto debugfs_done;
	}
	idev->clients_debug_root = debugfs_create_dir("clients",
						idev->debug_root);
	if (!idev->clients_debug_root)
		pr_err("ion: failed to create debugfs clients directory.\n");

debugfs_done:

	idev->custom_ioctl = custom_ioctl;
	idev->buffers = RB_ROOT;
	mutex_init(&idev->buffer_lock);
	init_rwsem(&idev->lock);
	plist_head_init(&idev->heaps);
	idev->clients = RB_ROOT;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (IS_ERR_OR_NULL(idev->debug_root))
		pr_err("ion: failed to create debug files.\n");

	idev->custom_ioctl = custom_ioctl;
	idev->buffers = RB_ROOT;
	mutex_init(&idev->lock);
	idev->heaps = RB_ROOT;
	idev->user_clients = RB_ROOT;
	idev->kernel_clients = RB_ROOT;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return idev;
}

void ion_device_destroy(struct ion_device *dev)
{
	misc_deregister(&dev->dev);
<<<<<<< HEAD
<<<<<<< HEAD
	debugfs_remove_recursive(dev->debug_root);
	/* XXX need to free the heaps and clients ? */
	kfree(dev);
}

void __init ion_reserve(struct ion_platform_data *data)
{
	int i;

	for (i = 0; i < data->nr; i++) {
		if (data->heaps[i].size == 0)
			continue;

		if (data->heaps[i].base == 0) {
			phys_addr_t paddr;
			paddr = memblock_alloc_base(data->heaps[i].size,
						    data->heaps[i].align,
						    MEMBLOCK_ALLOC_ANYWHERE);
			if (!paddr) {
				pr_err("%s: error allocating memblock for "
				       "heap %d\n",
					__func__, i);
				continue;
			}
			data->heaps[i].base = paddr;
		} else {
			int ret = memblock_reserve(data->heaps[i].base,
					       data->heaps[i].size);
			if (ret)
				pr_err("memblock reserve of %x@%pa failed\n",
				       data->heaps[i].size,
				       &data->heaps[i].base);
		}
		pr_info("%s: %s reserved base %pa size %d\n", __func__,
			data->heaps[i].name,
			&data->heaps[i].base,
			data->heaps[i].size);
	}
}
=======
	/* XXX need to free the heaps and clients ? */
	kfree(dev);
}
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	/* XXX need to free the heaps and clients ? */
	kfree(dev);
}
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
