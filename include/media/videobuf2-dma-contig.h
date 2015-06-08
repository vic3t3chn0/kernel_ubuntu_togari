/*
 * videobuf2-dma-coherent.h - DMA coherent memory allocator for videobuf2
 *
 * Copyright (C) 2010 Samsung Electronics
 *
 * Author: Pawel Osciak <pawel@osciak.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */

#ifndef _MEDIA_VIDEOBUF2_DMA_COHERENT_H
#define _MEDIA_VIDEOBUF2_DMA_COHERENT_H

#include <media/videobuf2-core.h>
#include <linux/dma-mapping.h>

static inline dma_addr_t
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
vb2_dma_contig_plane_dma_addr(struct vb2_buffer *vb, unsigned int plane_no)
{
	dma_addr_t *addr = vb2_plane_cookie(vb, plane_no);

	return *addr;
<<<<<<< HEAD
=======
=======
vb2_dma_contig_plane_paddr(struct vb2_buffer *vb, unsigned int plane_no)
{
	dma_addr_t *paddr = vb2_plane_cookie(vb, plane_no);

	return *paddr;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

void *vb2_dma_contig_init_ctx(struct device *dev);
void vb2_dma_contig_cleanup_ctx(void *alloc_ctx);

extern const struct vb2_mem_ops vb2_dma_contig_memops;

#endif
