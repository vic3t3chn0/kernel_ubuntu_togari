#ifndef __ASM_SH_MOBILE_CEU_H__
#define __ASM_SH_MOBILE_CEU_H__

#define SH_CEU_FLAG_USE_8BIT_BUS	(1 << 0) /* use  8bit bus width */
#define SH_CEU_FLAG_USE_16BIT_BUS	(1 << 1) /* use 16bit bus width */
#define SH_CEU_FLAG_HSYNC_LOW		(1 << 2) /* default High if possible */
#define SH_CEU_FLAG_VSYNC_LOW		(1 << 3) /* default High if possible */

struct device;
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
struct resource;

struct sh_mobile_ceu_companion {
	u32		num_resources;
	struct resource	*resource;
	int		id;
	void		*platform_data;
};

struct sh_mobile_ceu_info {
	unsigned long flags;
	int max_width;
	int max_height;
	struct sh_mobile_ceu_companion *csi2;
<<<<<<< HEAD
=======
=======

struct sh_mobile_ceu_info {
	unsigned long flags;
	struct device *csi2_dev;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

#endif /* __ASM_SH_MOBILE_CEU_H__ */
