/*
 * linux/drivers/media/video/s5p-mfc/s5p_mfc_shm.c
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

<<<<<<< HEAD
<<<<<<< HEAD
#ifdef CONFIG_ARCH_EXYNOS4
#include <linux/dma-mapping.h>
#endif
#include <linux/io.h>
#include "s5p_mfc_common.h"
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <linux/io.h>

#include "s5p_mfc_common.h"

#include "s5p_mfc_mem.h"
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include "s5p_mfc_debug.h"

int s5p_mfc_init_shm(struct s5p_mfc_ctx *ctx)
{
	struct s5p_mfc_dev *dev = ctx->dev;
<<<<<<< HEAD
<<<<<<< HEAD
	void *shm_alloc_ctx = dev->alloc_ctx[MFC_BANK1_ALLOC_CTX];

	ctx->shm_alloc = vb2_dma_contig_memops.alloc(shm_alloc_ctx,
							SHARED_BUF_SIZE);
	if (IS_ERR(ctx->shm_alloc)) {
		mfc_err("failed to allocate shared memory\n");
		return PTR_ERR(ctx->shm_alloc);
	}
	/* shm_ofs only keeps the offset from base (port a) */
	ctx->shm_ofs = s5p_mfc_mem_cookie(shm_alloc_ctx, ctx->shm_alloc)
								- dev->bank1;
	BUG_ON(ctx->shm_ofs & ((1 << MFC_BANK1_ALIGN_ORDER) - 1));
	ctx->shm = vb2_dma_contig_memops.vaddr(ctx->shm_alloc);
	if (!ctx->shm) {
		vb2_dma_contig_memops.put(ctx->shm_alloc);
		ctx->shm_ofs = 0;
		ctx->shm_alloc = NULL;
		mfc_err("failed to virt addr of shared memory\n");
		return -ENOMEM;
	}
	memset((void *)ctx->shm, 0, SHARED_BUF_SIZE);
	wmb();
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct s5p_mfc_buf_size_v5 *buf_size = dev->variant->buf_size->buf;
	void *shm_alloc_ctx = dev->alloc_ctx[MFC_CMA_BANK1_ALLOC_CTX];

	ctx->shm.alloc = s5p_mfc_mem_alloc(shm_alloc_ctx, buf_size->shared_buf);
	if (IS_ERR(ctx->shm.alloc)) {
		mfc_err("failed to allocate shared memory\n");
		return PTR_ERR(ctx->shm.alloc);
	}

	/* shm_ofs only keeps the offset from base (port a) */
	ctx->shm.ofs = s5p_mfc_mem_cookie(shm_alloc_ctx, ctx->shm.alloc) - dev->port_a;
	ctx->shm.virt = s5p_mfc_mem_vaddr(shm_alloc_ctx, ctx->shm.alloc);
	if (!ctx->shm.virt) {
		s5p_mfc_mem_put(shm_alloc_ctx, ctx->shm.alloc);
		ctx->shm.ofs = 0;
		ctx->shm.alloc = NULL;

		mfc_err("failed to virt addr of shared memory\n");
		return -ENOMEM;
	}

	memset((void *)ctx->shm.virt, 0, buf_size->shared_buf);
	s5p_mfc_cache_clean(ctx->shm.alloc);

	mfc_debug(2, "shm info addr: 0x%08x, phys: 0x%08lx\n",
		 (unsigned int)ctx->shm.virt, ctx->shm.ofs);

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return 0;
}

