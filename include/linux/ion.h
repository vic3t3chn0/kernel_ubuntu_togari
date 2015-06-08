/*
 * include/linux/ion.h
 *
 * Copyright (C) 2011 Google, Inc.
<<<<<<< HEAD
 * Copyright (c) 2011-2013, The Linux Foundation. All rights reserved.
=======
<<<<<<< HEAD
 * Copyright (c) 2011-2013, The Linux Foundation. All rights reserved.
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
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

#ifndef _LINUX_ION_H
#define _LINUX_ION_H

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <linux/ioctl.h>
#include <linux/types.h>

struct ion_handle;
typedef struct ion_handle *ion_user_handle_t;

<<<<<<< HEAD
=======
=======
#include <linux/types.h>

struct ion_handle;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/**
 * enum ion_heap_types - list of all possible types of heaps
 * @ION_HEAP_TYPE_SYSTEM:	 memory allocated via vmalloc
 * @ION_HEAP_TYPE_SYSTEM_CONTIG: memory allocated via kmalloc
 * @ION_HEAP_TYPE_CARVEOUT:	 memory allocated from a prereserved
 * 				 carveout heap, allocations are physically
 * 				 contiguous
<<<<<<< HEAD
 * @ION_HEAP_END:		helper for iterating over heaps
=======
<<<<<<< HEAD
 * @ION_HEAP_END:		helper for iterating over heaps
=======
 * @ION_HEAP_END:		 helper for iterating over heaps
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
enum ion_heap_type {
	ION_HEAP_TYPE_SYSTEM,
	ION_HEAP_TYPE_SYSTEM_CONTIG,
	ION_HEAP_TYPE_CARVEOUT,
<<<<<<< HEAD
	ION_HEAP_TYPE_CHUNK,
	ION_HEAP_TYPE_CUSTOM, /* must be last so device specific heaps always
				 are at the end of this enum */
=======
<<<<<<< HEAD
	ION_HEAP_TYPE_CHUNK,
	ION_HEAP_TYPE_CUSTOM, /* must be last so device specific heaps always
				 are at the end of this enum */
=======
	ION_HEAP_TYPE_CUSTOM, /* must be last so device specific heaps always
				 are at the end of this enum */
#ifdef CONFIG_ION_EXYNOS
	ION_HEAP_TYPE_EXYNOS_CONTIG,
	ION_HEAP_TYPE_EXYNOS,
	ION_HEAP_TYPE_EXYNOS_USER,
#endif
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	ION_NUM_HEAPS,
};

#define ION_HEAP_SYSTEM_MASK		(1 << ION_HEAP_TYPE_SYSTEM)
#define ION_HEAP_SYSTEM_CONTIG_MASK	(1 << ION_HEAP_TYPE_SYSTEM_CONTIG)
#define ION_HEAP_CARVEOUT_MASK		(1 << ION_HEAP_TYPE_CARVEOUT)

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#define ION_NUM_HEAP_IDS		sizeof(unsigned int) * 8

/**
 * allocation flags - the lower 16 bits are used by core ion, the upper 16
 * bits are reserved for use by the heaps themselves.
 */
#define ION_FLAG_CACHED 1		/* mappings of this buffer should be
					   cached, ion will do cache
					   maintenance when the buffer is
					   mapped for dma */
#define ION_FLAG_CACHED_NEEDS_SYNC 2	/* mappings of this buffer will created
					   at mmap time, if this is set
					   caches must be managed manually */
#define ION_FLAG_FREED_FROM_SHRINKER 4	/* Skip any possible
					   heap-specific caching
					   mechanism (e.g. page
					   pools). Guarantees that any
					   buffer storage that came
					   from the system allocator
					   will be returned to the
					   system allocator. */

#ifdef __KERNEL__
#include <linux/err.h>
#include <mach/ion.h>
<<<<<<< HEAD
=======
=======
#ifdef CONFIG_ION_EXYNOS
#define ION_HEAP_EXYNOS_MASK		(1 << ION_HEAP_TYPE_EXYNOS)
#define ION_HEAP_EXYNOS_CONTIG_MASK	(1 << ION_HEAP_TYPE_EXYNOS_CONTIG)
#define ION_HEAP_EXYNOS_USER_MASK	(1 << ION_HEAP_TYPE_EXYNOS_USER)
#define ION_EXYNOS_NONCACHE_MASK	(1 << (BITS_PER_LONG - 2))
#define ION_EXYNOS_WRITE_MASK		(1 << (BITS_PER_LONG - 1))
#endif

#ifdef __KERNEL__
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
struct ion_device;
struct ion_heap;
struct ion_mapper;
struct ion_client;
struct ion_buffer;

/* This should be removed some day when phys_addr_t's are fully
   plumbed in the kernel, and all instances of ion_phys_addr_t should
   be converted to phys_addr_t.  For the time being many kernel interfaces
   do not accept phys_addr_t's that would have to */
#define ion_phys_addr_t unsigned long

/**
 * struct ion_platform_heap - defines a heap in the given platform
 * @type:	type of the heap from ion_heap_type enum
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * @id:		unique identifier for heap.  When allocating higher numbers
 * 		will be allocated from first.  At allocation these are passed
 *		as a bit mask and therefore can not exceed ION_NUM_HEAP_IDS.
 * @name:	used for debug purposes
 * @base:	base address of heap in physical memory if applicable
 * @size:	size of the heap in bytes if applicable
 * @memory_type:Memory type used for the heap
 * @has_outer_cache:    set to 1 if outer cache is used, 0 otherwise.
 * @extra_data:	Extra data specific to each heap type
 * @priv:	heap private data
 * @align:	required alignment in physical memory if applicable
 * @priv:	private info passed from the board file
<<<<<<< HEAD
=======
=======
 * @id:		unique identifier for heap.  When allocating (lower numbers 
 * 		will be allocated from first)
 * @name:	used for debug purposes
 * @base:	base address of heap in physical memory if applicable
 * @size:	size of the heap in bytes if applicable
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * Provided by the board file.
 */
struct ion_platform_heap {
	enum ion_heap_type type;
	unsigned int id;
	const char *name;
	ion_phys_addr_t base;
	size_t size;
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	enum ion_memory_types memory_type;
	unsigned int has_outer_cache;
	void *extra_data;
	ion_phys_addr_t align;
	void *priv;
<<<<<<< HEAD
=======
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

/**
 * struct ion_platform_data - array of platform heaps passed from board file
<<<<<<< HEAD
 * @has_outer_cache:    set to 1 if outer cache is used, 0 otherwise.
 * @nr:    number of structures in the array
 * @heaps: array of platform_heap structions
=======
<<<<<<< HEAD
 * @has_outer_cache:    set to 1 if outer cache is used, 0 otherwise.
 * @nr:    number of structures in the array
 * @heaps: array of platform_heap structions
=======
 * @nr:		number of structures in the array
 * @heaps:	array of platform_heap structions
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * Provided by the board file in the form of platform data to a platform device.
 */
struct ion_platform_data {
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	unsigned int has_outer_cache;
	int nr;
	struct ion_platform_heap *heaps;
};

#ifdef CONFIG_ION

/**
 * ion_reserve() - reserve memory for ion heaps if applicable
 * @data:	platform data specifying starting physical address and
 *		size
 *
 * Calls memblock reserve to set aside memory for heaps that are
 * located at specific memory addresses or of specfic sizes not
 * managed by the kernel
 */
void ion_reserve(struct ion_platform_data *data);

/**
 * ion_client_create() -  allocate a client and returns it
 * @dev:		the global ion device
 * @heap_type_mask:	mask of heaps this client can allocate from
 * @name:		used for debugging
 */
struct ion_client *ion_client_create(struct ion_device *dev,
				     const char *name);
<<<<<<< HEAD
=======
=======
	int nr;
	struct ion_platform_heap heaps[];
};

/**
 * ion_client_create() -  allocate a client and returns it
 * @dev:	the global ion device
 * @heap_mask:	mask of heaps this client can allocate from
 * @name:	used for debugging
 */
struct ion_client *ion_client_create(struct ion_device *dev,
				     unsigned int heap_mask, const char *name);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/**
 * ion_client_destroy() -  free's a client and all it's handles
 * @client:	the client
 *
 * Free the provided client and all it's resources including
 * any handles it is holding.
 */
void ion_client_destroy(struct ion_client *client);

/**
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * ion_alloc - allocate ion memory
 * @client:		the client
 * @len:		size of the allocation
 * @align:		requested allocation alignment, lots of hardware blocks
 *			have alignment requirements of some kind
 * @heap_id_mask:	mask of heaps to allocate from, if multiple bits are set
 *			heaps will be tried in order from highest to lowest
 *			id
 * @flags:		heap flags, the low 16 bits are consumed by ion, the
 *			high 16 bits are passed on to the respective heap and
 *			can be heap custom
<<<<<<< HEAD
=======
=======
 * ion_get_client() - obtain a user client from file descriptor from user
 * @fd:		the user client created by the request from user. This is
 *		passed from user.
 *
 * This function is requested by the device drivers that implement V4L2 and VB2
 * interfaces. Those device drivers just obtains virtual address of a buffer
 * even though it is allocated and mapped by ION. While they can retrieve the
 * handle of the buffer, they are unable to access it because they do not know
 * what client the handle belongs to.
 * Note that the client obtained by this function is not released until
 * ion_put_client() is called and the client is given.
 */
struct ion_client *ion_get_user_client(unsigned int fd_client);

/**
 * ion_put_client() - release the user client obtained by ion_get_client()
 * @client - The user client to release.
 */
void ion_put_user_client(struct ion_client *user_client);

/**
 * ion_alloc - allocate ion memory
 * @client:	the client
 * @len:	size of the allocation
 * @align:	requested allocation alignment, lots of hardware blocks have
 *		alignment requirements of some kind
 * @flags:	mask of heaps to allocate from, if multiple bits are set
 *		heaps will be tried in order from lowest to highest order bit
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * Allocate memory in one of the heaps provided in heap mask and return
 * an opaque handle to it.
 */
struct ion_handle *ion_alloc(struct ion_client *client, size_t len,
<<<<<<< HEAD
			     size_t align, unsigned int heap_id_mask,
			     unsigned int flags);
=======
<<<<<<< HEAD
			     size_t align, unsigned int heap_id_mask,
			     unsigned int flags);
=======
			     size_t align, unsigned int flags);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/**
 * ion_free - free a handle
 * @client:	the client
 * @handle:	the handle to free
 *
 * Free the provided handle.
 */
void ion_free(struct ion_client *client, struct ion_handle *handle);

/**
 * ion_phys - returns the physical address and len of a handle
 * @client:	the client
 * @handle:	the handle
 * @addr:	a pointer to put the address in
 * @len:	a pointer to put the length in
 *
 * This function queries the heap for a particular handle to get the
 * handle's physical address.  It't output is only correct if
 * a heap returns physically contiguous memory -- in other cases
<<<<<<< HEAD
 * this api should not be implemented -- ion_sg_table should be used
=======
<<<<<<< HEAD
 * this api should not be implemented -- ion_sg_table should be used
=======
 * this api should not be implemented -- ion_map_dma should be used
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * instead.  Returns -EINVAL if the handle is invalid.  This has
 * no implications on the reference counting of the handle --
 * the returned value may not be valid if the caller is not
 * holding a reference.
 */
int ion_phys(struct ion_client *client, struct ion_handle *handle,
	     ion_phys_addr_t *addr, size_t *len);

/**
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * ion_map_dma - return an sg_table describing a handle
 * @client:	the client
 * @handle:	the handle
 *
 * This function returns the sg_table describing
 * a particular ion handle.
 */
struct sg_table *ion_sg_table(struct ion_client *client,
			      struct ion_handle *handle);

/**
<<<<<<< HEAD
=======
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * ion_map_kernel - create mapping for the given handle
 * @client:	the client
 * @handle:	handle to map
 *
 * Map the given handle into the kernel and return a kernel address that
 * can be used to access this address.
 */
void *ion_map_kernel(struct ion_client *client, struct ion_handle *handle);

/**
 * ion_unmap_kernel() - destroy a kernel mapping for a handle
 * @client:	the client
 * @handle:	handle to unmap
 */
void ion_unmap_kernel(struct ion_client *client, struct ion_handle *handle);

/**
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * ion_share_dma_buf() - share buffer as dma-buf
 * @client:	the client
 * @handle:	the handle
 */
struct dma_buf *ion_share_dma_buf(struct ion_client *client,
						struct ion_handle *handle);

/**
 * ion_share_dma_buf_fd() - given an ion client, create a dma-buf fd
 * @client:	the client
 * @handle:	the handle
 */
int ion_share_dma_buf_fd(struct ion_client *client, struct ion_handle *handle);

/**
 * ion_import_dma_buf() - given an dma-buf fd from the ion exporter get handle
 * @client:	the client
 * @fd:		the dma-buf fd
 *
 * Given an dma-buf fd that was allocated through ion via ion_share_dma_buf,
 * import that fd and return a handle representing it.  If a dma-buf from
 * another exporter is passed in this function will return ERR_PTR(-EINVAL)
 */
struct ion_handle *ion_import_dma_buf(struct ion_client *client, int fd);

#else
static inline void ion_reserve(struct ion_platform_data *data)
{

}

static inline struct ion_client *ion_client_create(struct ion_device *dev,
				     unsigned int heap_mask, const char *name)
{
	return ERR_PTR(-ENODEV);
}

static inline void ion_client_destroy(struct ion_client *client) { }

static inline struct ion_handle *ion_alloc(struct ion_client *client,
					size_t len, size_t align,
					unsigned int heap_mask,
					unsigned int flags)
{
	return ERR_PTR(-ENODEV);
}

static inline void ion_free(struct ion_client *client,
	struct ion_handle *handle) { }


static inline int ion_phys(struct ion_client *client,
	struct ion_handle *handle, ion_phys_addr_t *addr, size_t *len)
{
	return -ENODEV;
}

static inline struct sg_table *ion_sg_table(struct ion_client *client,
			      struct ion_handle *handle)
{
	return ERR_PTR(-ENODEV);
}

static inline void *ion_map_kernel(struct ion_client *client,
	struct ion_handle *handle)
{
	return ERR_PTR(-ENODEV);
}

static inline void ion_unmap_kernel(struct ion_client *client,
	struct ion_handle *handle) { }

static inline int ion_share_dma_buf(struct ion_client *client, struct ion_handle *handle)
{
	return -ENODEV;
}

static inline struct ion_handle *ion_import_dma_buf(struct ion_client *client, int fd)
{
	return ERR_PTR(-ENODEV);
}

static inline int ion_handle_get_flags(struct ion_client *client,
	struct ion_handle *handle, unsigned long *flags)
{
	return -ENODEV;
}

#endif /* CONFIG_ION */
<<<<<<< HEAD
=======
=======
 * ion_map_dma - create a dma mapping for a given handle
 * @client:	the client
 * @handle:	handle to map
 *
 * Return an sglist describing the given handle
 */
struct scatterlist *ion_map_dma(struct ion_client *client,
				struct ion_handle *handle);

/**
 * ion_unmap_dma() - destroy a dma mapping for a handle
 * @client:	the client
 * @handle:	handle to unmap
 */
void ion_unmap_dma(struct ion_client *client, struct ion_handle *handle);

/**
 * ion_share() - given a handle, obtain a buffer to pass to other clients
 * @client:	the client
 * @handle:	the handle to share
 *
 * Given a handle, return a buffer, which exists in a global name
 * space, and can be passed to other clients.  Should be passed into ion_import
 * to obtain a new handle for this buffer.
 *
 * NOTE: This function does do not an extra reference.  The burden is on the
 * caller to make sure the buffer doesn't go away while it's being passed to
 * another client.  That is, ion_free should not be called on this handle until
 * the buffer has been imported into the other client.
 */
struct ion_buffer *ion_share(struct ion_client *client,
			     struct ion_handle *handle);

/**
 * ion_import() - given an buffer in another client, import it
 * @client:	this blocks client
 * @buffer:	the buffer to import (as obtained from ion_share)
 *
 * Given a buffer, add it to the client and return the handle to use to refer
 * to it further.  This is called to share a handle from one kernel client to
 * another.
 */
struct ion_handle *ion_import(struct ion_client *client,
			      struct ion_buffer *buffer);

/**
 * ion_share_fd() - given a handle, obtain a buffer(fd) to pass to userspace
 * @client:	the client
 * @handle:	the handle to share
 *
 * Given a handle, return a fd of a buffer which can be passed to userspace.
 * Should be passed into userspace or ion_import_fd to obtain a new handle for
 * this buffer.
 */
int ion_share_fd(struct ion_client *client, struct ion_handle *handle);

/**
 * ion_import_fd() - given an fd obtained via ION_IOC_SHARE ioctl, import it
 * @client:	this blocks client
 * @fd:		the fd
 *
 * A helper function for drivers that will be recieving ion buffers shared
 * with them from userspace.  These buffers are represented by a file
 * descriptor obtained as the return from the ION_IOC_SHARE ioctl.
 * This function coverts that fd into the underlying buffer, and returns
 * the handle to use to refer to it further.
 */
struct ion_handle *ion_import_fd(struct ion_client *client, int fd);

/**
 * ion_import_uva() - given a virtual address from user, that is mmapped on an
 *                    fd obtained via ION_IOCTL_SHARE ioctl, import it
 * @client:    this blocks client
 * @uva:       virtual address in userspace.
 * @offset:	How many bytes are distant from the beginning of the ION buffer
 *
 * A helper function for drivers that will be recieving ion buffers shared
 * with them from userspace.  These buffers are represented by a virtual
 * address that is mmaped on a file descriptor obtained as the return from the
 * ION_IOC_SHARE ioctl.
 * This function does same job with ion_import_fd().
 */
struct ion_handle *ion_import_uva(struct ion_client *client, unsigned long uva,
								off_t *offset);

#ifdef CONFIG_ION_EXYNOS
struct ion_handle *ion_exynos_get_user_pages(struct ion_client *client,
			unsigned long uvaddr, size_t len, unsigned int flags);
#else
#include <linux/err.h>
static inline struct ion_handle *ion_exynos_get_user_pages(
				struct ion_client *client, unsigned long uvaddr,
				size_t len, unsigned int flags)
{
	return ERR_PTR(-ENOSYS);
}
#endif

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#endif /* __KERNEL__ */

/**
 * DOC: Ion Userspace API
 *
 * create a client by opening /dev/ion
 * most operations handled via following ioctls
 *
 */

/**
 * struct ion_allocation_data - metadata passed from userspace for allocations
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * @len:		size of the allocation
 * @align:		required alignment of the allocation
 * @heap_id_mask:	mask of heap ids to allocate from
 * @flags:		flags passed to heap
 * @handle:		pointer that will be populated with a cookie to use to 
 *			refer to this allocation
<<<<<<< HEAD
=======
=======
 * @len:	size of the allocation
 * @align:	required alignment of the allocation
 * @flags:	flags passed to heap
 * @handle:	pointer that will be populated with a cookie to use to refer
 *		to this allocation
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * Provided by userspace as an argument to the ioctl
 */
struct ion_allocation_data {
	size_t len;
	size_t align;
<<<<<<< HEAD
	unsigned int heap_mask;
	unsigned int flags;
	ion_user_handle_t handle;
=======
<<<<<<< HEAD
	unsigned int heap_mask;
	unsigned int flags;
	ion_user_handle_t handle;
=======
	unsigned int flags;
	struct ion_handle *handle;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

/**
 * struct ion_fd_data - metadata passed to/from userspace for a handle/fd pair
 * @handle:	a handle
 * @fd:		a file descriptor representing that handle
 *
 * For ION_IOC_SHARE or ION_IOC_MAP userspace populates the handle field with
 * the handle returned from ion alloc, and the kernel returns the file
 * descriptor to share or map in the fd field.  For ION_IOC_IMPORT, userspace
 * provides the file descriptor and the kernel returns the handle.
 */
struct ion_fd_data {
<<<<<<< HEAD
	ion_user_handle_t handle;
=======
<<<<<<< HEAD
	ion_user_handle_t handle;
=======
	struct ion_handle *handle;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int fd;
};

/**
 * struct ion_handle_data - a handle passed to/from the kernel
 * @handle:	a handle
 */
struct ion_handle_data {
<<<<<<< HEAD
	ion_user_handle_t handle;
=======
<<<<<<< HEAD
	ion_user_handle_t handle;
=======
	struct ion_handle *handle;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

/**
 * struct ion_custom_data - metadata passed to/from userspace for a custom ioctl
 * @cmd:	the custom ioctl function to call
 * @arg:	additional data to pass to the custom ioctl, typically a user
 *		pointer to a predefined structure
 *
 * This works just like the regular cmd and arg fields of an ioctl.
 */
struct ion_custom_data {
	unsigned int cmd;
	unsigned long arg;
};
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#define ION_IOC_MAGIC		'I'

/**
 * DOC: ION_IOC_ALLOC - allocate memory
 *
 * Takes an ion_allocation_data struct and returns it with the handle field
 * populated with the opaque handle for the allocation.
 */
#define ION_IOC_ALLOC		_IOWR(ION_IOC_MAGIC, 0, \
				      struct ion_allocation_data)

/**
 * DOC: ION_IOC_FREE - free memory
 *
 * Takes an ion_handle_data struct and frees the handle.
 */
#define ION_IOC_FREE		_IOWR(ION_IOC_MAGIC, 1, struct ion_handle_data)

/**
 * DOC: ION_IOC_MAP - get a file descriptor to mmap
 *
 * Takes an ion_fd_data struct with the handle field populated with a valid
 * opaque handle.  Returns the struct with the fd field set to a file
 * descriptor open in the current address space.  This file descriptor
 * can then be used as an argument to mmap.
 */
#define ION_IOC_MAP		_IOWR(ION_IOC_MAGIC, 2, struct ion_fd_data)

/**
 * DOC: ION_IOC_SHARE - creates a file descriptor to use to share an allocation
 *
 * Takes an ion_fd_data struct with the handle field populated with a valid
 * opaque handle.  Returns the struct with the fd field set to a file
 * descriptor open in the current address space.  This file descriptor
 * can then be passed to another process.  The corresponding opaque handle can
 * be retrieved via ION_IOC_IMPORT.
 */
#define ION_IOC_SHARE		_IOWR(ION_IOC_MAGIC, 4, struct ion_fd_data)

/**
 * DOC: ION_IOC_IMPORT - imports a shared file descriptor
 *
 * Takes an ion_fd_data struct with the fd field populated with a valid file
 * descriptor obtained from ION_IOC_SHARE and returns the struct with the handle
 * filed set to the corresponding opaque handle.
 */
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#define ION_IOC_IMPORT		_IOWR(ION_IOC_MAGIC, 5, struct ion_fd_data)

/**
 * DOC: ION_IOC_SYNC - syncs a shared file descriptors to memory
 *
 * Deprecated in favor of using the dma_buf api's correctly (syncing
 * will happend automatically when the buffer is mapped to a device).
 * If necessary should be used after touching a cached buffer from the cpu,
 * this will make the buffer in memory coherent.
 */
#define ION_IOC_SYNC		_IOWR(ION_IOC_MAGIC, 7, struct ion_fd_data)
<<<<<<< HEAD
=======
=======
#define ION_IOC_IMPORT		_IOWR(ION_IOC_MAGIC, 5, int)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/**
 * DOC: ION_IOC_CUSTOM - call architecture specific ion ioctl
 *
 * Takes the argument of the architecture specific ioctl to call and
 * passes appropriate userdata for that ioctl
 */
#define ION_IOC_CUSTOM		_IOWR(ION_IOC_MAGIC, 6, struct ion_custom_data)

<<<<<<< HEAD

=======
<<<<<<< HEAD

=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#endif /* _LINUX_ION_H */
