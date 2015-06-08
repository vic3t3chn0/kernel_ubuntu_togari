/*
 * linux/drivers/video/omap2/dss/overlay.c
 *
 * Copyright (C) 2009 Nokia Corporation
 * Author: Tomi Valkeinen <tomi.valkeinen@nokia.com>
 *
 * Some code and ideas taken from drivers/video/omap/ driver
 * by Imre Deak.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#define DSS_SUBSYS_NAME "OVERLAY"

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/err.h>
#include <linux/sysfs.h>
#include <linux/kobject.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/slab.h>

#include <video/omapdss.h>
#include <plat/cpu.h>

#include "dss.h"
#include "dss_features.h"

static int num_overlays;
<<<<<<< HEAD
static struct omap_overlay *overlays;
=======
static struct list_head overlay_list;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0

static ssize_t overlay_name_show(struct omap_overlay *ovl, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "%s\n", ovl->name);
}

static ssize_t overlay_manager_show(struct omap_overlay *ovl, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "%s\n",
			ovl->manager ? ovl->manager->name : "<none>");
}

static ssize_t overlay_manager_store(struct omap_overlay *ovl, const char *buf,
		size_t size)
{
	int i, r;
	struct omap_overlay_manager *mgr = NULL;
	struct omap_overlay_manager *old_mgr;
	int len = size;

	if (buf[size-1] == '\n')
		--len;

	if (len > 0) {
		for (i = 0; i < omap_dss_get_num_overlay_managers(); ++i) {
			mgr = omap_dss_get_overlay_manager(i);

			if (sysfs_streq(buf, mgr->name))
				break;

			mgr = NULL;
		}
	}

	if (len > 0 && mgr == NULL)
		return -EINVAL;

	if (mgr)
		DSSDBG("manager %s found\n", mgr->name);

	if (mgr == ovl->manager)
		return size;

	old_mgr = ovl->manager;

<<<<<<< HEAD
	r = dispc_runtime_get();
	if (r)
		return r;

=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	/* detach old manager */
	if (old_mgr) {
		r = ovl->unset_manager(ovl);
		if (r) {
			DSSERR("detach failed\n");
<<<<<<< HEAD
			goto err;
=======
			return r;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
		}

		r = old_mgr->apply(old_mgr);
		if (r)
<<<<<<< HEAD
			goto err;
=======
			return r;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	}

	if (mgr) {
		r = ovl->set_manager(ovl, mgr);
		if (r) {
			DSSERR("Failed to attach overlay\n");
<<<<<<< HEAD
			goto err;
=======
			return r;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
		}

		r = mgr->apply(mgr);
		if (r)
<<<<<<< HEAD
			goto err;
	}

	dispc_runtime_put();

	return size;

err:
	dispc_runtime_put();
	return r;
=======
			return r;
	}

	return size;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
}

static ssize_t overlay_input_size_show(struct omap_overlay *ovl, char *buf)
{
<<<<<<< HEAD
	struct omap_overlay_info info;

	ovl->get_overlay_info(ovl, &info);

	return snprintf(buf, PAGE_SIZE, "%d,%d\n",
			info.width, info.height);
=======
	return snprintf(buf, PAGE_SIZE, "%d,%d\n",
			ovl->info.width, ovl->info.height);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
}

static ssize_t overlay_screen_width_show(struct omap_overlay *ovl, char *buf)
{
<<<<<<< HEAD
	struct omap_overlay_info info;

	ovl->get_overlay_info(ovl, &info);

	return snprintf(buf, PAGE_SIZE, "%d\n", info.screen_width);
=======
	return snprintf(buf, PAGE_SIZE, "%d\n", ovl->info.screen_width);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
}

static ssize_t overlay_position_show(struct omap_overlay *ovl, char *buf)
{
<<<<<<< HEAD
	struct omap_overlay_info info;

	ovl->get_overlay_info(ovl, &info);

	return snprintf(buf, PAGE_SIZE, "%d,%d\n",
			info.pos_x, info.pos_y);
=======
	return snprintf(buf, PAGE_SIZE, "%d,%d\n",
			ovl->info.pos_x, ovl->info.pos_y);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
}

static ssize_t overlay_position_store(struct omap_overlay *ovl,
		const char *buf, size_t size)
{
	int r;
	char *last;
	struct omap_overlay_info info;

	ovl->get_overlay_info(ovl, &info);

	info.pos_x = simple_strtoul(buf, &last, 10);
	++last;
	if (last - buf >= size)
		return -EINVAL;

	info.pos_y = simple_strtoul(last, &last, 10);

	r = ovl->set_overlay_info(ovl, &info);
	if (r)
		return r;

	if (ovl->manager) {
		r = ovl->manager->apply(ovl->manager);
		if (r)
			return r;
	}

	return size;
}

static ssize_t overlay_output_size_show(struct omap_overlay *ovl, char *buf)
{
<<<<<<< HEAD
	struct omap_overlay_info info;

	ovl->get_overlay_info(ovl, &info);

	return snprintf(buf, PAGE_SIZE, "%d,%d\n",
			info.out_width, info.out_height);
=======
	return snprintf(buf, PAGE_SIZE, "%d,%d\n",
			ovl->info.out_width, ovl->info.out_height);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
}

static ssize_t overlay_output_size_store(struct omap_overlay *ovl,
		const char *buf, size_t size)
{
	int r;
	char *last;
	struct omap_overlay_info info;

	ovl->get_overlay_info(ovl, &info);

	info.out_width = simple_strtoul(buf, &last, 10);
	++last;
	if (last - buf >= size)
		return -EINVAL;

	info.out_height = simple_strtoul(last, &last, 10);

	r = ovl->set_overlay_info(ovl, &info);
	if (r)
		return r;

	if (ovl->manager) {
		r = ovl->manager->apply(ovl->manager);
		if (r)
			return r;
	}

	return size;
}

static ssize_t overlay_enabled_show(struct omap_overlay *ovl, char *buf)
{
<<<<<<< HEAD
	return snprintf(buf, PAGE_SIZE, "%d\n", ovl->is_enabled(ovl));
=======
	return snprintf(buf, PAGE_SIZE, "%d\n", ovl->info.enabled);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
}

static ssize_t overlay_enabled_store(struct omap_overlay *ovl, const char *buf,
		size_t size)
{
<<<<<<< HEAD
	int r;
	bool enable;

	r = strtobool(buf, &enable);
	if (r)
		return r;

	if (enable)
		r = ovl->enable(ovl);
	else
		r = ovl->disable(ovl);

	if (r)
		return r;

	return size;
}

static ssize_t overlay_global_alpha_show(struct omap_overlay *ovl, char *buf)
{
=======
	int r, enable;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	struct omap_overlay_info info;

	ovl->get_overlay_info(ovl, &info);

<<<<<<< HEAD
	return snprintf(buf, PAGE_SIZE, "%d\n",
			info.global_alpha);
}

static ssize_t overlay_global_alpha_store(struct omap_overlay *ovl,
		const char *buf, size_t size)
{
	int r;
	u8 alpha;
	struct omap_overlay_info info;

	if ((ovl->caps & OMAP_DSS_OVL_CAP_GLOBAL_ALPHA) == 0)
		return -ENODEV;

	r = kstrtou8(buf, 0, &alpha);
	if (r)
		return r;

	ovl->get_overlay_info(ovl, &info);

	info.global_alpha = alpha;
=======
	r = kstrtoint(buf, 0, &enable);
	if (r)
		return r;

	info.enabled = !!enable;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0

	r = ovl->set_overlay_info(ovl, &info);
	if (r)
		return r;

	if (ovl->manager) {
		r = ovl->manager->apply(ovl->manager);
		if (r)
			return r;
	}

	return size;
}

<<<<<<< HEAD
static ssize_t overlay_pre_mult_alpha_show(struct omap_overlay *ovl,
		char *buf)
{
	struct omap_overlay_info info;

	ovl->get_overlay_info(ovl, &info);

	return snprintf(buf, PAGE_SIZE, "%d\n",
			info.pre_mult_alpha);
}

static ssize_t overlay_pre_mult_alpha_store(struct omap_overlay *ovl,
=======
static ssize_t overlay_global_alpha_show(struct omap_overlay *ovl, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "%d\n",
			ovl->info.global_alpha);
}

static ssize_t overlay_global_alpha_store(struct omap_overlay *ovl,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
		const char *buf, size_t size)
{
	int r;
	u8 alpha;
	struct omap_overlay_info info;

<<<<<<< HEAD
	if ((ovl->caps & OMAP_DSS_OVL_CAP_PRE_MULT_ALPHA) == 0)
		return -ENODEV;

=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	r = kstrtou8(buf, 0, &alpha);
	if (r)
		return r;

	ovl->get_overlay_info(ovl, &info);

<<<<<<< HEAD
	info.pre_mult_alpha = alpha;
=======
	/* Video1 plane does not support global alpha
	 * to always make it 255 completely opaque
	 */
	if (!dss_has_feature(FEAT_GLOBAL_ALPHA_VID1) &&
			ovl->id == OMAP_DSS_VIDEO1)
		info.global_alpha = 255;
	else
		info.global_alpha = alpha;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0

	r = ovl->set_overlay_info(ovl, &info);
	if (r)
		return r;

	if (ovl->manager) {
		r = ovl->manager->apply(ovl->manager);
		if (r)
			return r;
	}

	return size;
}

<<<<<<< HEAD
static ssize_t overlay_zorder_show(struct omap_overlay *ovl, char *buf)
{
	struct omap_overlay_info info;

	ovl->get_overlay_info(ovl, &info);

	return snprintf(buf, PAGE_SIZE, "%d\n", info.zorder);
}

static ssize_t overlay_zorder_store(struct omap_overlay *ovl,
		const char *buf, size_t size)
{
	int r;
	u8 zorder;
	struct omap_overlay_info info;

	if ((ovl->caps & OMAP_DSS_OVL_CAP_ZORDER) == 0)
		return -ENODEV;

	r = kstrtou8(buf, 0, &zorder);
=======
static ssize_t overlay_pre_mult_alpha_show(struct omap_overlay *ovl,
		char *buf)
{
	return snprintf(buf, PAGE_SIZE, "%d\n",
			ovl->info.pre_mult_alpha);
}

static ssize_t overlay_pre_mult_alpha_store(struct omap_overlay *ovl,
		const char *buf, size_t size)
{
	int r;
	u8 alpha;
	struct omap_overlay_info info;

	r = kstrtou8(buf, 0, &alpha);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	if (r)
		return r;

	ovl->get_overlay_info(ovl, &info);

<<<<<<< HEAD
	info.zorder = zorder;
=======
	/* only GFX and Video2 plane support pre alpha multiplied
	 * set zero for Video1 plane
	 */
	if (!dss_has_feature(FEAT_GLOBAL_ALPHA_VID1) &&
		ovl->id == OMAP_DSS_VIDEO1)
		info.pre_mult_alpha = 0;
	else
		info.pre_mult_alpha = alpha;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0

	r = ovl->set_overlay_info(ovl, &info);
	if (r)
		return r;

	if (ovl->manager) {
		r = ovl->manager->apply(ovl->manager);
		if (r)
			return r;
	}

	return size;
}

struct overlay_attribute {
	struct attribute attr;
	ssize_t (*show)(struct omap_overlay *, char *);
	ssize_t	(*store)(struct omap_overlay *, const char *, size_t);
};

#define OVERLAY_ATTR(_name, _mode, _show, _store) \
	struct overlay_attribute overlay_attr_##_name = \
	__ATTR(_name, _mode, _show, _store)

static OVERLAY_ATTR(name, S_IRUGO, overlay_name_show, NULL);
static OVERLAY_ATTR(manager, S_IRUGO|S_IWUSR,
		overlay_manager_show, overlay_manager_store);
static OVERLAY_ATTR(input_size, S_IRUGO, overlay_input_size_show, NULL);
static OVERLAY_ATTR(screen_width, S_IRUGO, overlay_screen_width_show, NULL);
static OVERLAY_ATTR(position, S_IRUGO|S_IWUSR,
		overlay_position_show, overlay_position_store);
static OVERLAY_ATTR(output_size, S_IRUGO|S_IWUSR,
		overlay_output_size_show, overlay_output_size_store);
static OVERLAY_ATTR(enabled, S_IRUGO|S_IWUSR,
		overlay_enabled_show, overlay_enabled_store);
static OVERLAY_ATTR(global_alpha, S_IRUGO|S_IWUSR,
		overlay_global_alpha_show, overlay_global_alpha_store);
static OVERLAY_ATTR(pre_mult_alpha, S_IRUGO|S_IWUSR,
		overlay_pre_mult_alpha_show,
		overlay_pre_mult_alpha_store);
<<<<<<< HEAD
static OVERLAY_ATTR(zorder, S_IRUGO|S_IWUSR,
		overlay_zorder_show, overlay_zorder_store);
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0

static struct attribute *overlay_sysfs_attrs[] = {
	&overlay_attr_name.attr,
	&overlay_attr_manager.attr,
	&overlay_attr_input_size.attr,
	&overlay_attr_screen_width.attr,
	&overlay_attr_position.attr,
	&overlay_attr_output_size.attr,
	&overlay_attr_enabled.attr,
	&overlay_attr_global_alpha.attr,
	&overlay_attr_pre_mult_alpha.attr,
<<<<<<< HEAD
	&overlay_attr_zorder.attr,
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	NULL
};

static ssize_t overlay_attr_show(struct kobject *kobj, struct attribute *attr,
		char *buf)
{
	struct omap_overlay *overlay;
	struct overlay_attribute *overlay_attr;

	overlay = container_of(kobj, struct omap_overlay, kobj);
	overlay_attr = container_of(attr, struct overlay_attribute, attr);

	if (!overlay_attr->show)
		return -ENOENT;

	return overlay_attr->show(overlay, buf);
}

static ssize_t overlay_attr_store(struct kobject *kobj, struct attribute *attr,
		const char *buf, size_t size)
{
	struct omap_overlay *overlay;
	struct overlay_attribute *overlay_attr;

	overlay = container_of(kobj, struct omap_overlay, kobj);
	overlay_attr = container_of(attr, struct overlay_attribute, attr);

	if (!overlay_attr->store)
		return -ENOENT;

	return overlay_attr->store(overlay, buf, size);
}

static const struct sysfs_ops overlay_sysfs_ops = {
	.show = overlay_attr_show,
	.store = overlay_attr_store,
};

static struct kobj_type overlay_ktype = {
	.sysfs_ops = &overlay_sysfs_ops,
	.default_attrs = overlay_sysfs_attrs,
};

<<<<<<< HEAD
=======
/* Check if overlay parameters are compatible with display */
int dss_check_overlay(struct omap_overlay *ovl, struct omap_dss_device *dssdev)
{
	struct omap_overlay_info *info;
	u16 outw, outh;
	u16 dw, dh;

	if (!dssdev)
		return 0;

	if (!ovl->info.enabled)
		return 0;

	info = &ovl->info;

	if (info->paddr == 0) {
		DSSDBG("check_overlay failed: paddr 0\n");
		return -EINVAL;
	}

	dssdev->driver->get_resolution(dssdev, &dw, &dh);

	DSSDBG("check_overlay %d: (%d,%d %dx%d -> %dx%d) disp (%dx%d)\n",
			ovl->id,
			info->pos_x, info->pos_y,
			info->width, info->height,
			info->out_width, info->out_height,
			dw, dh);

	if ((ovl->caps & OMAP_DSS_OVL_CAP_SCALE) == 0) {
		outw = info->width;
		outh = info->height;
	} else {
		if (info->out_width == 0)
			outw = info->width;
		else
			outw = info->out_width;

		if (info->out_height == 0)
			outh = info->height;
		else
			outh = info->out_height;
	}

	if (dw < info->pos_x + outw) {
		DSSDBG("check_overlay failed 1: %d < %d + %d\n",
				dw, info->pos_x, outw);
		return -EINVAL;
	}

	if (dh < info->pos_y + outh) {
		DSSDBG("check_overlay failed 2: %d < %d + %d\n",
				dh, info->pos_y, outh);
		return -EINVAL;
	}

	if ((ovl->supported_modes & info->color_mode) == 0) {
		DSSERR("overlay doesn't support mode %d\n", info->color_mode);
		return -EINVAL;
	}

	return 0;
}

static int dss_ovl_set_overlay_info(struct omap_overlay *ovl,
		struct omap_overlay_info *info)
{
	int r;
	struct omap_overlay_info old_info;

	old_info = ovl->info;
	ovl->info = *info;

	if (ovl->manager) {
		r = dss_check_overlay(ovl, ovl->manager->device);
		if (r) {
			ovl->info = old_info;
			return r;
		}
	}

	ovl->info_dirty = true;

	return 0;
}

static void dss_ovl_get_overlay_info(struct omap_overlay *ovl,
		struct omap_overlay_info *info)
{
	*info = ovl->info;
}

static int dss_ovl_wait_for_go(struct omap_overlay *ovl)
{
	return dss_mgr_wait_for_go_ovl(ovl);
}

static int omap_dss_set_manager(struct omap_overlay *ovl,
		struct omap_overlay_manager *mgr)
{
	if (!mgr)
		return -EINVAL;

	if (ovl->manager) {
		DSSERR("overlay '%s' already has a manager '%s'\n",
				ovl->name, ovl->manager->name);
		return -EINVAL;
	}

	if (ovl->info.enabled) {
		DSSERR("overlay has to be disabled to change the manager\n");
		return -EINVAL;
	}

	ovl->manager = mgr;

	dss_clk_enable(DSS_CLK_ICK | DSS_CLK_FCK);
	/* XXX: When there is an overlay on a DSI manual update display, and
	 * the overlay is first disabled, then moved to tv, and enabled, we
	 * seem to get SYNC_LOST_DIGIT error.
	 *
	 * Waiting doesn't seem to help, but updating the manual update display
	 * after disabling the overlay seems to fix this. This hints that the
	 * overlay is perhaps somehow tied to the LCD output until the output
	 * is updated.
	 *
	 * Userspace workaround for this is to update the LCD after disabling
	 * the overlay, but before moving the overlay to TV.
	 */
	dispc_set_channel_out(ovl->id, mgr->id);
	dss_clk_disable(DSS_CLK_ICK | DSS_CLK_FCK);

	return 0;
}

static int omap_dss_unset_manager(struct omap_overlay *ovl)
{
	int r;

	if (!ovl->manager) {
		DSSERR("failed to detach overlay: manager not set\n");
		return -EINVAL;
	}

	if (ovl->info.enabled) {
		DSSERR("overlay has to be disabled to unset the manager\n");
		return -EINVAL;
	}

	r = ovl->wait_for_go(ovl);
	if (r)
		return r;

	ovl->manager = NULL;

	return 0;
}

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
int omap_dss_get_num_overlays(void)
{
	return num_overlays;
}
EXPORT_SYMBOL(omap_dss_get_num_overlays);

struct omap_overlay *omap_dss_get_overlay(int num)
{
<<<<<<< HEAD
	if (num >= num_overlays)
		return NULL;

	return &overlays[num];
}
EXPORT_SYMBOL(omap_dss_get_overlay);

=======
	int i = 0;
	struct omap_overlay *ovl;

	list_for_each_entry(ovl, &overlay_list, list) {
		if (i++ == num)
			return ovl;
	}

	return NULL;
}
EXPORT_SYMBOL(omap_dss_get_overlay);

static void omap_dss_add_overlay(struct omap_overlay *overlay)
{
	++num_overlays;
	list_add_tail(&overlay->list, &overlay_list);
}

static struct omap_overlay *dispc_overlays[MAX_DSS_OVERLAYS];

void dss_overlay_setup_dispc_manager(struct omap_overlay_manager *mgr)
{
	mgr->num_overlays = dss_feat_get_num_ovls();
	mgr->overlays = dispc_overlays;
}

#ifdef L4_EXAMPLE
static struct omap_overlay *l4_overlays[1];
void dss_overlay_setup_l4_manager(struct omap_overlay_manager *mgr)
{
	mgr->num_overlays = 1;
	mgr->overlays = l4_overlays;
}
#endif

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
void dss_init_overlays(struct platform_device *pdev)
{
	int i, r;

<<<<<<< HEAD
	num_overlays = dss_feat_get_num_ovls();

	overlays = kzalloc(sizeof(struct omap_overlay) * num_overlays,
			GFP_KERNEL);

	BUG_ON(overlays == NULL);

	for (i = 0; i < num_overlays; ++i) {
		struct omap_overlay *ovl = &overlays[i];
=======
	INIT_LIST_HEAD(&overlay_list);

	num_overlays = 0;

	for (i = 0; i < dss_feat_get_num_ovls(); ++i) {
		struct omap_overlay *ovl;
		ovl = kzalloc(sizeof(*ovl), GFP_KERNEL);

		BUG_ON(ovl == NULL);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0

		switch (i) {
		case 0:
			ovl->name = "gfx";
			ovl->id = OMAP_DSS_GFX;
<<<<<<< HEAD
=======
			ovl->caps = OMAP_DSS_OVL_CAP_DISPC;
			ovl->info.global_alpha = 255;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
			break;
		case 1:
			ovl->name = "vid1";
			ovl->id = OMAP_DSS_VIDEO1;
<<<<<<< HEAD
=======
			ovl->caps = OMAP_DSS_OVL_CAP_SCALE |
				OMAP_DSS_OVL_CAP_DISPC;
			ovl->info.global_alpha = 255;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
			break;
		case 2:
			ovl->name = "vid2";
			ovl->id = OMAP_DSS_VIDEO2;
<<<<<<< HEAD
			break;
		case 3:
			ovl->name = "vid3";
			ovl->id = OMAP_DSS_VIDEO3;
			break;
		}

		ovl->is_enabled = &dss_ovl_is_enabled;
		ovl->enable = &dss_ovl_enable;
		ovl->disable = &dss_ovl_disable;
		ovl->set_manager = &dss_ovl_set_manager;
		ovl->unset_manager = &dss_ovl_unset_manager;
		ovl->set_overlay_info = &dss_ovl_set_info;
		ovl->get_overlay_info = &dss_ovl_get_info;
		ovl->wait_for_go = &dss_mgr_wait_for_go_ovl;

		ovl->caps = dss_feat_get_overlay_caps(ovl->id);
		ovl->supported_modes =
			dss_feat_get_supported_color_modes(ovl->id);

		r = kobject_init_and_add(&ovl->kobj, &overlay_ktype,
				&pdev->dev.kobj, "overlay%d", i);

		if (r)
			DSSERR("failed to create sysfs file\n");
	}
=======
			ovl->caps = OMAP_DSS_OVL_CAP_SCALE |
				OMAP_DSS_OVL_CAP_DISPC;
			ovl->info.global_alpha = 255;
			break;
		}

		ovl->set_manager = &omap_dss_set_manager;
		ovl->unset_manager = &omap_dss_unset_manager;
		ovl->set_overlay_info = &dss_ovl_set_overlay_info;
		ovl->get_overlay_info = &dss_ovl_get_overlay_info;
		ovl->wait_for_go = &dss_ovl_wait_for_go;

		ovl->supported_modes =
			dss_feat_get_supported_color_modes(ovl->id);

		omap_dss_add_overlay(ovl);

		r = kobject_init_and_add(&ovl->kobj, &overlay_ktype,
				&pdev->dev.kobj, "overlay%d", i);

		if (r) {
			DSSERR("failed to create sysfs file\n");
			continue;
		}

		dispc_overlays[i] = ovl;
	}

#ifdef L4_EXAMPLE
	{
		struct omap_overlay *ovl;
		ovl = kzalloc(sizeof(*ovl), GFP_KERNEL);

		BUG_ON(ovl == NULL);

		ovl->name = "l4";
		ovl->supported_modes = OMAP_DSS_COLOR_RGB24U;

		ovl->set_manager = &omap_dss_set_manager;
		ovl->unset_manager = &omap_dss_unset_manager;
		ovl->set_overlay_info = &dss_ovl_set_overlay_info;
		ovl->get_overlay_info = &dss_ovl_get_overlay_info;

		omap_dss_add_overlay(ovl);

		r = kobject_init_and_add(&ovl->kobj, &overlay_ktype,
				&pdev->dev.kobj, "overlayl4");

		if (r)
			DSSERR("failed to create sysfs file\n");

		l4_overlays[0] = ovl;
	}
#endif
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
}

/* connect overlays to the new device, if not already connected. if force
 * selected, connect always. */
void dss_recheck_connections(struct omap_dss_device *dssdev, bool force)
{
	int i;
	struct omap_overlay_manager *lcd_mgr;
	struct omap_overlay_manager *tv_mgr;
	struct omap_overlay_manager *lcd2_mgr = NULL;
	struct omap_overlay_manager *mgr = NULL;

	lcd_mgr = omap_dss_get_overlay_manager(OMAP_DSS_OVL_MGR_LCD);
	tv_mgr = omap_dss_get_overlay_manager(OMAP_DSS_OVL_MGR_TV);
	if (dss_has_feature(FEAT_MGR_LCD2))
		lcd2_mgr = omap_dss_get_overlay_manager(OMAP_DSS_OVL_MGR_LCD2);

	if (dssdev->channel == OMAP_DSS_CHANNEL_LCD2) {
		if (!lcd2_mgr->device || force) {
			if (lcd2_mgr->device)
				lcd2_mgr->unset_device(lcd2_mgr);
			lcd2_mgr->set_device(lcd2_mgr, dssdev);
			mgr = lcd2_mgr;
		}
	} else if (dssdev->type != OMAP_DISPLAY_TYPE_VENC
			&& dssdev->type != OMAP_DISPLAY_TYPE_HDMI) {
		if (!lcd_mgr->device || force) {
			if (lcd_mgr->device)
				lcd_mgr->unset_device(lcd_mgr);
			lcd_mgr->set_device(lcd_mgr, dssdev);
			mgr = lcd_mgr;
		}
	}

	if (dssdev->type == OMAP_DISPLAY_TYPE_VENC
			|| dssdev->type == OMAP_DISPLAY_TYPE_HDMI) {
		if (!tv_mgr->device || force) {
			if (tv_mgr->device)
				tv_mgr->unset_device(tv_mgr);
			tv_mgr->set_device(tv_mgr, dssdev);
			mgr = tv_mgr;
		}
	}

	if (mgr) {
<<<<<<< HEAD
		dispc_runtime_get();

=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
		for (i = 0; i < dss_feat_get_num_ovls(); i++) {
			struct omap_overlay *ovl;
			ovl = omap_dss_get_overlay(i);
			if (!ovl->manager || force) {
				if (ovl->manager)
<<<<<<< HEAD
					ovl->unset_manager(ovl);
				ovl->set_manager(ovl, mgr);
			}
		}

		dispc_runtime_put();
=======
					omap_dss_unset_manager(ovl);
				omap_dss_set_manager(ovl, mgr);
			}
		}
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	}
}

void dss_uninit_overlays(struct platform_device *pdev)
{
<<<<<<< HEAD
	int i;

	for (i = 0; i < num_overlays; ++i) {
		struct omap_overlay *ovl = &overlays[i];

		kobject_del(&ovl->kobj);
		kobject_put(&ovl->kobj);
	}

	kfree(overlays);
	overlays = NULL;
	num_overlays = 0;
}

int dss_ovl_simple_check(struct omap_overlay *ovl,
		const struct omap_overlay_info *info)
{
	if (info->paddr == 0) {
		DSSERR("check_overlay: paddr cannot be 0\n");
		return -EINVAL;
	}

	if ((ovl->caps & OMAP_DSS_OVL_CAP_SCALE) == 0) {
		if (info->out_width != 0 && info->width != info->out_width) {
			DSSERR("check_overlay: overlay %d doesn't support "
					"scaling\n", ovl->id);
			return -EINVAL;
		}

		if (info->out_height != 0 && info->height != info->out_height) {
			DSSERR("check_overlay: overlay %d doesn't support "
					"scaling\n", ovl->id);
			return -EINVAL;
		}
	}

	if ((ovl->supported_modes & info->color_mode) == 0) {
		DSSERR("check_overlay: overlay %d doesn't support mode %d\n",
				ovl->id, info->color_mode);
		return -EINVAL;
	}

	if (info->zorder >= omap_dss_get_num_overlays()) {
		DSSERR("check_overlay: zorder %d too high\n", info->zorder);
		return -EINVAL;
	}

	return 0;
}

int dss_ovl_check(struct omap_overlay *ovl,
		struct omap_overlay_info *info, struct omap_dss_device *dssdev)
{
	u16 outw, outh;
	u16 dw, dh;

	if (dssdev == NULL)
		return 0;

	dssdev->driver->get_resolution(dssdev, &dw, &dh);

	if ((ovl->caps & OMAP_DSS_OVL_CAP_SCALE) == 0) {
		outw = info->width;
		outh = info->height;
	} else {
		if (info->out_width == 0)
			outw = info->width;
		else
			outw = info->out_width;

		if (info->out_height == 0)
			outh = info->height;
		else
			outh = info->out_height;
	}

	if (dw < info->pos_x + outw) {
		DSSERR("overlay %d horizontally not inside the display area "
				"(%d + %d >= %d)\n",
				ovl->id, info->pos_x, outw, dw);
		return -EINVAL;
	}

	if (dh < info->pos_y + outh) {
		DSSERR("overlay %d vertically not inside the display area "
				"(%d + %d >= %d)\n",
				ovl->id, info->pos_y, outh, dh);
		return -EINVAL;
	}

	return 0;
}
=======
	struct omap_overlay *ovl;

	while (!list_empty(&overlay_list)) {
		ovl = list_first_entry(&overlay_list,
				struct omap_overlay, list);
		list_del(&ovl->list);
		kobject_del(&ovl->kobj);
		kobject_put(&ovl->kobj);
		kfree(ovl);
	}

	num_overlays = 0;
}

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
