/*
 * Copyright (C) 2011 Samsung Electronics Co.Ltd
 * Authors: Joonyoung Shim <jy0922.shim@samsung.com>
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 *
 */

<<<<<<< HEAD
<<<<<<< HEAD
int exynos_plane_init(struct drm_device *dev, unsigned int nr);
int exynos_plane_set_zpos_ioctl(struct drm_device *dev, void *data,
				struct drm_file *file_priv);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
int exynos_plane_mode_set(struct drm_plane *plane, struct drm_crtc *crtc,
			  struct drm_framebuffer *fb, int crtc_x, int crtc_y,
			  unsigned int crtc_w, unsigned int crtc_h,
			  uint32_t src_x, uint32_t src_y,
			  uint32_t src_w, uint32_t src_h);
void exynos_plane_commit(struct drm_plane *plane);
void exynos_plane_dpms(struct drm_plane *plane, int mode);
struct drm_plane *exynos_plane_init(struct drm_device *dev,
				    unsigned int possible_crtcs, bool priv);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
