#ifndef __linux_video_edid_h__
#define __linux_video_edid_h__

<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
#if !defined(__KERNEL__) || defined(CONFIG_X86)

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
struct edid_info {
	unsigned char dummy[128];
};

#ifdef __KERNEL__
<<<<<<< HEAD
#ifdef CONFIG_X86
extern struct edid_info edid_info;
#endif
=======
<<<<<<< HEAD
#ifdef CONFIG_X86
extern struct edid_info edid_info;
#endif
=======
extern struct edid_info edid_info;
#endif /* __KERNEL__ */

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#endif

#endif /* __linux_video_edid_h__ */
