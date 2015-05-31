#ifndef _SCSI_SCSI_DRIVER_H
#define _SCSI_SCSI_DRIVER_H

#include <linux/device.h>

struct module;
struct scsi_cmnd;
struct scsi_device;
struct request;
struct request_queue;


struct scsi_driver {
	struct module		*owner;
	struct device_driver	gendrv;

	void (*rescan)(struct device *);
	int (*done)(struct scsi_cmnd *);
<<<<<<< HEAD
	int (*eh_action)(struct scsi_cmnd *, unsigned char *, int, int);
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
};
#define to_scsi_driver(drv) \
	container_of((drv), struct scsi_driver, gendrv)

extern int scsi_register_driver(struct device_driver *);
#define scsi_unregister_driver(drv) \
	driver_unregister(drv);

extern int scsi_register_interface(struct class_interface *);
#define scsi_unregister_interface(intf) \
	class_interface_unregister(intf)

int scsi_setup_blk_pc_cmnd(struct scsi_device *sdev, struct request *req);
int scsi_setup_fs_cmnd(struct scsi_device *sdev, struct request *req);
int scsi_prep_state_check(struct scsi_device *sdev, struct request *req);
int scsi_prep_return(struct request_queue *q, struct request *req, int ret);
int scsi_prep_fn(struct request_queue *, struct request *);

#endif /* _SCSI_SCSI_DRIVER_H */
