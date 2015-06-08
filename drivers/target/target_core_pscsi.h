#ifndef TARGET_CORE_PSCSI_H
#define TARGET_CORE_PSCSI_H

#define PSCSI_VERSION		"v4.0"
<<<<<<< HEAD
<<<<<<< HEAD
=======
#define PSCSI_VIRTUAL_HBA_DEPTH	2048
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
#define PSCSI_VIRTUAL_HBA_DEPTH	2048
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/* used in pscsi_find_alloc_len() */
#ifndef INQUIRY_DATA_SIZE
#define INQUIRY_DATA_SIZE	0x24
#endif

/* used in pscsi_add_device_to_list() */
#define PSCSI_DEFAULT_QUEUEDEPTH	1

#define PS_RETRY		5
#define PS_TIMEOUT_DISK		(15*HZ)
#define PS_TIMEOUT_OTHER	(500*HZ)

#include <linux/device.h>
#include <scsi/scsi_driver.h>
#include <scsi/scsi_device.h>
#include <linux/kref.h>
#include <linux/kobject.h>

struct pscsi_plugin_task {
	struct se_task pscsi_task;
<<<<<<< HEAD
<<<<<<< HEAD
=======
	unsigned char *pscsi_cdb;
	unsigned char __pscsi_cdb[TCM_MAX_COMMAND_SIZE];
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	unsigned char *pscsi_cdb;
	unsigned char __pscsi_cdb[TCM_MAX_COMMAND_SIZE];
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	unsigned char pscsi_sense[SCSI_SENSE_BUFFERSIZE];
	int	pscsi_direction;
	int	pscsi_result;
	u32	pscsi_resid;
<<<<<<< HEAD
<<<<<<< HEAD
	unsigned char pscsi_cdb[0];
=======
	struct request *pscsi_req;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	struct request *pscsi_req;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
} ____cacheline_aligned;

#define PDF_HAS_CHANNEL_ID	0x01
#define PDF_HAS_TARGET_ID	0x02
#define PDF_HAS_LUN_ID		0x04
#define PDF_HAS_VPD_UNIT_SERIAL 0x08
#define PDF_HAS_VPD_DEV_IDENT	0x10
#define PDF_HAS_VIRT_HOST_ID	0x20

struct pscsi_dev_virt {
	int	pdv_flags;
	int	pdv_host_id;
	int	pdv_channel_id;
	int	pdv_target_id;
	int	pdv_lun_id;
	struct block_device *pdv_bd;
	struct scsi_device *pdv_sd;
	struct se_hba *pdv_se_hba;
} ____cacheline_aligned;

typedef enum phv_modes {
<<<<<<< HEAD
<<<<<<< HEAD
	PHV_VIRTUAL_HOST_ID,
=======
	PHV_VIRUTAL_HOST_ID,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	PHV_VIRUTAL_HOST_ID,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	PHV_LLD_SCSI_HOST_NO
} phv_modes_t;

struct pscsi_hba_virt {
	int			phv_host_id;
	phv_modes_t		phv_mode;
	struct Scsi_Host	*phv_lld_host;
} ____cacheline_aligned;

#endif   /*** TARGET_CORE_PSCSI_H ***/
