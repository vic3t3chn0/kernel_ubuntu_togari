#ifndef _ARCH_ARM_MACH_MSM_MDM_IOCTLS_H
#define _ARXH_ARM_MACH_MSM_MDM_IOCTLS_H


#define CHARM_CODE		0xCC
#define WAKE_CHARM		_IO(CHARM_CODE, 1)
#define RESET_CHARM		_IO(CHARM_CODE, 2)
#define CHECK_FOR_BOOT		_IOR(CHARM_CODE, 3, int)
#define WAIT_FOR_BOOT		_IO(CHARM_CODE, 4)
#define NORMAL_BOOT_DONE	_IOW(CHARM_CODE, 5, int)
#define RAM_DUMP_DONE		_IOW(CHARM_CODE, 6, int)
#define WAIT_FOR_RESTART	_IOR(CHARM_CODE, 7, int)
<<<<<<< HEAD
#define GET_DLOAD_STATUS	_IOR(CHARM_CODE, 8, int)
#define IMAGE_UPGRADE		_IOW(CHARM_CODE, 9, int)
#define SHUTDOWN_CHARM		_IOW(CHARM_CODE, 10, int)
=======
<<<<<<< HEAD
#define GET_DLOAD_STATUS	_IOR(CHARM_CODE, 8, int)
#define IMAGE_UPGRADE		_IOW(CHARM_CODE, 9, int)
#define SHUTDOWN_CHARM		_IOW(CHARM_CODE, 10, int)
=======
#define SILENT_RESET_CONTROL	_IOR(CHARM_CODE, 8, int)
#define AUTOPM_LOCK		_IOW(CHARM_CODE, 9, int)
#define GET_BOOT_PROTOCOL	_IOW(CHARM_CODE, 10, int)
#define GET_FORCE_RAMDUMP	_IOW(CHARM_CODE, 11, int)
#define WAIT_FOR_ERROR		_IOW(CHARM_CODE, 12, int)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

enum charm_boot_type {
	CHARM_NORMAL_BOOT = 0,
	CHARM_RAM_DUMPS,
};

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
enum image_upgrade_type {
	APQ_CONTROLLED_UPGRADE = 0,
	MDM_CONTROLLED_UPGRADE,
};
<<<<<<< HEAD
=======
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#endif
