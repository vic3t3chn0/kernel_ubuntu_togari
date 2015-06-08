/*
 * QLogic Fibre Channel HBA Driver
 * Copyright (c)  2003-2011 QLogic Corporation
 *
 * See LICENSE.qla2xxx for copyright and licensing details.
 */
#include "qla_def.h"

#include <linux/kthread.h>
#include <linux/vmalloc.h>
#include <linux/slab.h>
#include <linux/delay.h>

static int qla24xx_vport_disable(struct fc_vport *, bool);

/* SYSFS attributes --------------------------------------------------------- */

static ssize_t
qla2x00_sysfs_read_fw_dump(struct file *filp, struct kobject *kobj,
			   struct bin_attribute *bin_attr,
			   char *buf, loff_t off, size_t count)
{
	struct scsi_qla_host *vha = shost_priv(dev_to_shost(container_of(kobj,
	    struct device, kobj)));
	struct qla_hw_data *ha = vha->hw;
<<<<<<< HEAD
<<<<<<< HEAD
	int rval = 0;
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (ha->fw_dump_reading == 0)
		return 0;

<<<<<<< HEAD
<<<<<<< HEAD
	if (IS_QLA82XX(ha)) {
		if (off < ha->md_template_size) {
			rval = memory_read_from_buffer(buf, count,
			    &off, ha->md_tmplt_hdr, ha->md_template_size);
			return rval;
		}
		off -= ha->md_template_size;
		rval = memory_read_from_buffer(buf, count,
		    &off, ha->md_dump, ha->md_dump_size);
		return rval;
	} else
		return memory_read_from_buffer(buf, count, &off, ha->fw_dump,
=======
	return memory_read_from_buffer(buf, count, &off, ha->fw_dump,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	return memory_read_from_buffer(buf, count, &off, ha->fw_dump,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
					ha->fw_dump_len);
}

static ssize_t
qla2x00_sysfs_write_fw_dump(struct file *filp, struct kobject *kobj,
			    struct bin_attribute *bin_attr,
			    char *buf, loff_t off, size_t count)
{
	struct scsi_qla_host *vha = shost_priv(dev_to_shost(container_of(kobj,
	    struct device, kobj)));
	struct qla_hw_data *ha = vha->hw;
	int reading;

<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (IS_QLA82XX(ha)) {
		DEBUG2(qla_printk(KERN_INFO, ha,
			"Firmware dump not supported for ISP82xx\n"));
		return count;
	}

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (off != 0)
		return (0);

	reading = simple_strtol(buf, NULL, 10);
	switch (reading) {
	case 0:
		if (!ha->fw_dump_reading)
			break;

<<<<<<< HEAD
<<<<<<< HEAD
		ql_log(ql_log_info, vha, 0x705d,
		    "Firmware dump cleared on (%ld).\n", vha->host_no);

		if (IS_QLA82XX(vha->hw)) {
			qla82xx_md_free(vha);
			qla82xx_md_prep(vha);
		}
=======
		qla_printk(KERN_INFO, ha,
		    "Firmware dump cleared on (%ld).\n", vha->host_no);

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		qla_printk(KERN_INFO, ha,
		    "Firmware dump cleared on (%ld).\n", vha->host_no);

>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		ha->fw_dump_reading = 0;
		ha->fw_dumped = 0;
		break;
	case 1:
		if (ha->fw_dumped && !ha->fw_dump_reading) {
			ha->fw_dump_reading = 1;

<<<<<<< HEAD
<<<<<<< HEAD
			ql_log(ql_log_info, vha, 0x705e,
=======
			qla_printk(KERN_INFO, ha,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			qla_printk(KERN_INFO, ha,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			    "Raw firmware dump ready for read on (%ld).\n",
			    vha->host_no);
		}
		break;
	case 2:
		qla2x00_alloc_fw_dump(vha);
		break;
	case 3:
<<<<<<< HEAD
<<<<<<< HEAD
		if (IS_QLA82XX(ha)) {
			qla82xx_idc_lock(ha);
			qla82xx_set_reset_owner(vha);
			qla82xx_idc_unlock(ha);
		} else
			qla2x00_system_error(vha);
		break;
	case 4:
		if (IS_QLA82XX(ha)) {
			if (ha->md_tmplt_hdr)
				ql_dbg(ql_dbg_user, vha, 0x705b,
				    "MiniDump supported with this firmware.\n");
			else
				ql_dbg(ql_dbg_user, vha, 0x709d,
				    "MiniDump not supported with this firmware.\n");
		}
		break;
	case 5:
		if (IS_QLA82XX(ha))
			set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
		break;
	}
	return count;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		qla2x00_system_error(vha);
		break;
	}
	return (count);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static struct bin_attribute sysfs_fw_dump_attr = {
	.attr = {
		.name = "fw_dump",
		.mode = S_IRUSR | S_IWUSR,
	},
	.size = 0,
	.read = qla2x00_sysfs_read_fw_dump,
	.write = qla2x00_sysfs_write_fw_dump,
};

static ssize_t
qla2x00_sysfs_read_nvram(struct file *filp, struct kobject *kobj,
			 struct bin_attribute *bin_attr,
			 char *buf, loff_t off, size_t count)
{
	struct scsi_qla_host *vha = shost_priv(dev_to_shost(container_of(kobj,
	    struct device, kobj)));
	struct qla_hw_data *ha = vha->hw;

	if (!capable(CAP_SYS_ADMIN))
		return 0;

	if (IS_NOCACHE_VPD_TYPE(ha))
		ha->isp_ops->read_optrom(vha, ha->nvram, ha->flt_region_nvram << 2,
		    ha->nvram_size);
	return memory_read_from_buffer(buf, count, &off, ha->nvram,
					ha->nvram_size);
}

static ssize_t
qla2x00_sysfs_write_nvram(struct file *filp, struct kobject *kobj,
			  struct bin_attribute *bin_attr,
			  char *buf, loff_t off, size_t count)
{
	struct scsi_qla_host *vha = shost_priv(dev_to_shost(container_of(kobj,
	    struct device, kobj)));
	struct qla_hw_data *ha = vha->hw;
	uint16_t	cnt;

	if (!capable(CAP_SYS_ADMIN) || off != 0 || count != ha->nvram_size ||
	    !ha->isp_ops->write_nvram)
<<<<<<< HEAD
<<<<<<< HEAD
		return -EINVAL;
=======
		return 0;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		return 0;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	/* Checksum NVRAM. */
	if (IS_FWI2_CAPABLE(ha)) {
		uint32_t *iter;
		uint32_t chksum;

		iter = (uint32_t *)buf;
		chksum = 0;
		for (cnt = 0; cnt < ((count >> 2) - 1); cnt++)
			chksum += le32_to_cpu(*iter++);
		chksum = ~chksum + 1;
		*iter = cpu_to_le32(chksum);
	} else {
		uint8_t *iter;
		uint8_t chksum;

		iter = (uint8_t *)buf;
		chksum = 0;
		for (cnt = 0; cnt < count - 1; cnt++)
			chksum += *iter++;
		chksum = ~chksum + 1;
		*iter = chksum;
	}

	if (qla2x00_wait_for_hba_online(vha) != QLA_SUCCESS) {
<<<<<<< HEAD
<<<<<<< HEAD
		ql_log(ql_log_warn, vha, 0x705f,
=======
		qla_printk(KERN_WARNING, ha,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		qla_printk(KERN_WARNING, ha,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		    "HBA not online, failing NVRAM update.\n");
		return -EAGAIN;
	}

	/* Write NVRAM. */
	ha->isp_ops->write_nvram(vha, (uint8_t *)buf, ha->nvram_base, count);
	ha->isp_ops->read_nvram(vha, (uint8_t *)ha->nvram, ha->nvram_base,
	    count);

<<<<<<< HEAD
<<<<<<< HEAD
	ql_dbg(ql_dbg_user, vha, 0x7060,
	    "Setting ISP_ABORT_NEEDED\n");
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	/* NVRAM settings take effect immediately. */
	set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
	qla2xxx_wake_dpc(vha);
	qla2x00_wait_for_chip_reset(vha);

<<<<<<< HEAD
<<<<<<< HEAD
	return count;
=======
	return (count);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	return (count);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static struct bin_attribute sysfs_nvram_attr = {
	.attr = {
		.name = "nvram",
		.mode = S_IRUSR | S_IWUSR,
	},
	.size = 512,
	.read = qla2x00_sysfs_read_nvram,
	.write = qla2x00_sysfs_write_nvram,
};

static ssize_t
qla2x00_sysfs_read_optrom(struct file *filp, struct kobject *kobj,
			  struct bin_attribute *bin_attr,
			  char *buf, loff_t off, size_t count)
{
	struct scsi_qla_host *vha = shost_priv(dev_to_shost(container_of(kobj,
	    struct device, kobj)));
	struct qla_hw_data *ha = vha->hw;

	if (ha->optrom_state != QLA_SREADING)
		return 0;

	return memory_read_from_buffer(buf, count, &off, ha->optrom_buffer,
					ha->optrom_region_size);
}

static ssize_t
qla2x00_sysfs_write_optrom(struct file *filp, struct kobject *kobj,
			   struct bin_attribute *bin_attr,
			   char *buf, loff_t off, size_t count)
{
	struct scsi_qla_host *vha = shost_priv(dev_to_shost(container_of(kobj,
	    struct device, kobj)));
	struct qla_hw_data *ha = vha->hw;

	if (ha->optrom_state != QLA_SWRITING)
		return -EINVAL;
	if (off > ha->optrom_region_size)
		return -ERANGE;
	if (off + count > ha->optrom_region_size)
		count = ha->optrom_region_size - off;

	memcpy(&ha->optrom_buffer[off], buf, count);

	return count;
}

static struct bin_attribute sysfs_optrom_attr = {
	.attr = {
		.name = "optrom",
		.mode = S_IRUSR | S_IWUSR,
	},
	.size = 0,
	.read = qla2x00_sysfs_read_optrom,
	.write = qla2x00_sysfs_write_optrom,
};

static ssize_t
qla2x00_sysfs_write_optrom_ctl(struct file *filp, struct kobject *kobj,
			       struct bin_attribute *bin_attr,
			       char *buf, loff_t off, size_t count)
{
	struct scsi_qla_host *vha = shost_priv(dev_to_shost(container_of(kobj,
	    struct device, kobj)));
	struct qla_hw_data *ha = vha->hw;

	uint32_t start = 0;
	uint32_t size = ha->optrom_size;
	int val, valid;

	if (off)
<<<<<<< HEAD
<<<<<<< HEAD
		return -EINVAL;

	if (unlikely(pci_channel_offline(ha->pdev)))
		return -EAGAIN;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return 0;

	if (unlikely(pci_channel_offline(ha->pdev)))
		return 0;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (sscanf(buf, "%d:%x:%x", &val, &start, &size) < 1)
		return -EINVAL;
	if (start > ha->optrom_size)
		return -EINVAL;

	switch (val) {
	case 0:
		if (ha->optrom_state != QLA_SREADING &&
		    ha->optrom_state != QLA_SWRITING)
<<<<<<< HEAD
<<<<<<< HEAD
			return -EINVAL;

		ha->optrom_state = QLA_SWAITING;

		ql_dbg(ql_dbg_user, vha, 0x7061,
		    "Freeing flash region allocation -- 0x%x bytes.\n",
		    ha->optrom_region_size);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			break;

		ha->optrom_state = QLA_SWAITING;

		DEBUG2(qla_printk(KERN_INFO, ha,
		    "Freeing flash region allocation -- 0x%x bytes.\n",
		    ha->optrom_region_size));
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

		vfree(ha->optrom_buffer);
		ha->optrom_buffer = NULL;
		break;
	case 1:
		if (ha->optrom_state != QLA_SWAITING)
<<<<<<< HEAD
<<<<<<< HEAD
			return -EINVAL;
=======
			break;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			break;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

		ha->optrom_region_start = start;
		ha->optrom_region_size = start + size > ha->optrom_size ?
		    ha->optrom_size - start : size;

		ha->optrom_state = QLA_SREADING;
		ha->optrom_buffer = vmalloc(ha->optrom_region_size);
		if (ha->optrom_buffer == NULL) {
<<<<<<< HEAD
<<<<<<< HEAD
			ql_log(ql_log_warn, vha, 0x7062,
=======
			qla_printk(KERN_WARNING, ha,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			qla_printk(KERN_WARNING, ha,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			    "Unable to allocate memory for optrom retrieval "
			    "(%x).\n", ha->optrom_region_size);

			ha->optrom_state = QLA_SWAITING;
<<<<<<< HEAD
<<<<<<< HEAD
			return -ENOMEM;
		}

		if (qla2x00_wait_for_hba_online(vha) != QLA_SUCCESS) {
			ql_log(ql_log_warn, vha, 0x7063,
			    "HBA not online, failing NVRAM update.\n");
			return -EAGAIN;
		}

		ql_dbg(ql_dbg_user, vha, 0x7064,
		    "Reading flash region -- 0x%x/0x%x.\n",
		    ha->optrom_region_start, ha->optrom_region_size);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			return count;
		}

		if (qla2x00_wait_for_hba_online(vha) != QLA_SUCCESS) {
			qla_printk(KERN_WARNING, ha,
				"HBA not online, failing NVRAM update.\n");
			return -EAGAIN;
		}

		DEBUG2(qla_printk(KERN_INFO, ha,
		    "Reading flash region -- 0x%x/0x%x.\n",
		    ha->optrom_region_start, ha->optrom_region_size));
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

		memset(ha->optrom_buffer, 0, ha->optrom_region_size);
		ha->isp_ops->read_optrom(vha, ha->optrom_buffer,
		    ha->optrom_region_start, ha->optrom_region_size);
		break;
	case 2:
		if (ha->optrom_state != QLA_SWAITING)
<<<<<<< HEAD
<<<<<<< HEAD
			return -EINVAL;
=======
			break;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			break;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

		/*
		 * We need to be more restrictive on which FLASH regions are
		 * allowed to be updated via user-space.  Regions accessible
		 * via this method include:
		 *
		 * ISP21xx/ISP22xx/ISP23xx type boards:
		 *
		 * 	0x000000 -> 0x020000 -- Boot code.
		 *
		 * ISP2322/ISP24xx type boards:
		 *
		 * 	0x000000 -> 0x07ffff -- Boot code.
		 * 	0x080000 -> 0x0fffff -- Firmware.
		 *
		 * ISP25xx type boards:
		 *
		 * 	0x000000 -> 0x07ffff -- Boot code.
		 * 	0x080000 -> 0x0fffff -- Firmware.
		 * 	0x120000 -> 0x12ffff -- VPD and HBA parameters.
		 */
		valid = 0;
		if (ha->optrom_size == OPTROM_SIZE_2300 && start == 0)
			valid = 1;
		else if (start == (ha->flt_region_boot * 4) ||
		    start == (ha->flt_region_fw * 4))
			valid = 1;
<<<<<<< HEAD
<<<<<<< HEAD
		else if (IS_QLA24XX_TYPE(ha) || IS_QLA25XX(ha)
			|| IS_CNA_CAPABLE(ha) || IS_QLA2031(ha))
			valid = 1;
		if (!valid) {
			ql_log(ql_log_warn, vha, 0x7065,
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		else if (IS_QLA25XX(ha) || IS_QLA8XXX_TYPE(ha))
			valid = 1;
		if (!valid) {
			qla_printk(KERN_WARNING, ha,
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			    "Invalid start region 0x%x/0x%x.\n", start, size);
			return -EINVAL;
		}

		ha->optrom_region_start = start;
		ha->optrom_region_size = start + size > ha->optrom_size ?
		    ha->optrom_size - start : size;

		ha->optrom_state = QLA_SWRITING;
		ha->optrom_buffer = vmalloc(ha->optrom_region_size);
		if (ha->optrom_buffer == NULL) {
<<<<<<< HEAD
<<<<<<< HEAD
			ql_log(ql_log_warn, vha, 0x7066,
			    "Unable to allocate memory for optrom update "
			    "(%x)\n", ha->optrom_region_size);

			ha->optrom_state = QLA_SWAITING;
			return -ENOMEM;
		}

		ql_dbg(ql_dbg_user, vha, 0x7067,
		    "Staging flash region write -- 0x%x/0x%x.\n",
		    ha->optrom_region_start, ha->optrom_region_size);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			qla_printk(KERN_WARNING, ha,
			    "Unable to allocate memory for optrom update "
			    "(%x).\n", ha->optrom_region_size);

			ha->optrom_state = QLA_SWAITING;
			return count;
		}

		DEBUG2(qla_printk(KERN_INFO, ha,
		    "Staging flash region write -- 0x%x/0x%x.\n",
		    ha->optrom_region_start, ha->optrom_region_size));
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

		memset(ha->optrom_buffer, 0, ha->optrom_region_size);
		break;
	case 3:
		if (ha->optrom_state != QLA_SWRITING)
<<<<<<< HEAD
<<<<<<< HEAD
			return -EINVAL;

		if (qla2x00_wait_for_hba_online(vha) != QLA_SUCCESS) {
			ql_log(ql_log_warn, vha, 0x7068,
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			break;

		if (qla2x00_wait_for_hba_online(vha) != QLA_SUCCESS) {
			qla_printk(KERN_WARNING, ha,
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			    "HBA not online, failing flash update.\n");
			return -EAGAIN;
		}

<<<<<<< HEAD
<<<<<<< HEAD
		ql_dbg(ql_dbg_user, vha, 0x7069,
		    "Writing flash region -- 0x%x/0x%x.\n",
		    ha->optrom_region_start, ha->optrom_region_size);
=======
		DEBUG2(qla_printk(KERN_INFO, ha,
		    "Writing flash region -- 0x%x/0x%x.\n",
		    ha->optrom_region_start, ha->optrom_region_size));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		DEBUG2(qla_printk(KERN_INFO, ha,
		    "Writing flash region -- 0x%x/0x%x.\n",
		    ha->optrom_region_start, ha->optrom_region_size));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

		ha->isp_ops->write_optrom(vha, ha->optrom_buffer,
		    ha->optrom_region_start, ha->optrom_region_size);
		break;
	default:
<<<<<<< HEAD
<<<<<<< HEAD
		return -EINVAL;
=======
		count = -EINVAL;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		count = -EINVAL;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}
	return count;
}

static struct bin_attribute sysfs_optrom_ctl_attr = {
	.attr = {
		.name = "optrom_ctl",
		.mode = S_IWUSR,
	},
	.size = 0,
	.write = qla2x00_sysfs_write_optrom_ctl,
};

static ssize_t
qla2x00_sysfs_read_vpd(struct file *filp, struct kobject *kobj,
		       struct bin_attribute *bin_attr,
		       char *buf, loff_t off, size_t count)
{
	struct scsi_qla_host *vha = shost_priv(dev_to_shost(container_of(kobj,
	    struct device, kobj)));
	struct qla_hw_data *ha = vha->hw;

	if (unlikely(pci_channel_offline(ha->pdev)))
<<<<<<< HEAD
<<<<<<< HEAD
		return -EAGAIN;

	if (!capable(CAP_SYS_ADMIN))
		return -EINVAL;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return 0;

	if (!capable(CAP_SYS_ADMIN))
		return 0;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (IS_NOCACHE_VPD_TYPE(ha))
		ha->isp_ops->read_optrom(vha, ha->vpd, ha->flt_region_vpd << 2,
		    ha->vpd_size);
	return memory_read_from_buffer(buf, count, &off, ha->vpd, ha->vpd_size);
}

static ssize_t
qla2x00_sysfs_write_vpd(struct file *filp, struct kobject *kobj,
			struct bin_attribute *bin_attr,
			char *buf, loff_t off, size_t count)
{
	struct scsi_qla_host *vha = shost_priv(dev_to_shost(container_of(kobj,
	    struct device, kobj)));
	struct qla_hw_data *ha = vha->hw;
	uint8_t *tmp_data;

	if (unlikely(pci_channel_offline(ha->pdev)))
		return 0;

	if (!capable(CAP_SYS_ADMIN) || off != 0 || count != ha->vpd_size ||
	    !ha->isp_ops->write_nvram)
		return 0;

	if (qla2x00_wait_for_hba_online(vha) != QLA_SUCCESS) {
<<<<<<< HEAD
<<<<<<< HEAD
		ql_log(ql_log_warn, vha, 0x706a,
=======
		qla_printk(KERN_WARNING, ha,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		qla_printk(KERN_WARNING, ha,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		    "HBA not online, failing VPD update.\n");
		return -EAGAIN;
	}

	/* Write NVRAM. */
	ha->isp_ops->write_nvram(vha, (uint8_t *)buf, ha->vpd_base, count);
	ha->isp_ops->read_nvram(vha, (uint8_t *)ha->vpd, ha->vpd_base, count);

	/* Update flash version information for 4Gb & above. */
	if (!IS_FWI2_CAPABLE(ha))
<<<<<<< HEAD
<<<<<<< HEAD
		return -EINVAL;

	tmp_data = vmalloc(256);
	if (!tmp_data) {
		ql_log(ql_log_warn, vha, 0x706b,
		    "Unable to allocate memory for VPD information update.\n");
		return -ENOMEM;
	}
	ha->isp_ops->get_flash_version(vha, tmp_data);
	vfree(tmp_data);

=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		goto done;

	tmp_data = vmalloc(256);
	if (!tmp_data) {
		qla_printk(KERN_WARNING, ha,
		    "Unable to allocate memory for VPD information update.\n");
		goto done;
	}
	ha->isp_ops->get_flash_version(vha, tmp_data);
	vfree(tmp_data);
done:
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return count;
}

static struct bin_attribute sysfs_vpd_attr = {
	.attr = {
		.name = "vpd",
		.mode = S_IRUSR | S_IWUSR,
	},
	.size = 0,
	.read = qla2x00_sysfs_read_vpd,
	.write = qla2x00_sysfs_write_vpd,
};

static ssize_t
qla2x00_sysfs_read_sfp(struct file *filp, struct kobject *kobj,
		       struct bin_attribute *bin_attr,
		       char *buf, loff_t off, size_t count)
{
	struct scsi_qla_host *vha = shost_priv(dev_to_shost(container_of(kobj,
	    struct device, kobj)));
	struct qla_hw_data *ha = vha->hw;
	uint16_t iter, addr, offset;
	int rval;

	if (!capable(CAP_SYS_ADMIN) || off != 0 || count != SFP_DEV_SIZE * 2)
		return 0;

	if (ha->sfp_data)
		goto do_read;

	ha->sfp_data = dma_pool_alloc(ha->s_dma_pool, GFP_KERNEL,
	    &ha->sfp_data_dma);
	if (!ha->sfp_data) {
<<<<<<< HEAD
<<<<<<< HEAD
		ql_log(ql_log_warn, vha, 0x706c,
=======
		qla_printk(KERN_WARNING, ha,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		qla_printk(KERN_WARNING, ha,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		    "Unable to allocate memory for SFP read-data.\n");
		return 0;
	}

do_read:
	memset(ha->sfp_data, 0, SFP_BLOCK_SIZE);
	addr = 0xa0;
	for (iter = 0, offset = 0; iter < (SFP_DEV_SIZE * 2) / SFP_BLOCK_SIZE;
	    iter++, offset += SFP_BLOCK_SIZE) {
		if (iter == 4) {
			/* Skip to next device address. */
			addr = 0xa2;
			offset = 0;
		}

		rval = qla2x00_read_sfp(vha, ha->sfp_data_dma, ha->sfp_data,
		    addr, offset, SFP_BLOCK_SIZE, 0);
		if (rval != QLA_SUCCESS) {
<<<<<<< HEAD
<<<<<<< HEAD
			ql_log(ql_log_warn, vha, 0x706d,
			    "Unable to read SFP data (%x/%x/%x).\n", rval,
			    addr, offset);

			return -EIO;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			qla_printk(KERN_WARNING, ha,
			    "Unable to read SFP data (%x/%x/%x).\n", rval,
			    addr, offset);
			count = 0;
			break;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		}
		memcpy(buf, ha->sfp_data, SFP_BLOCK_SIZE);
		buf += SFP_BLOCK_SIZE;
	}

	return count;
}

static struct bin_attribute sysfs_sfp_attr = {
	.attr = {
		.name = "sfp",
		.mode = S_IRUSR | S_IWUSR,
	},
	.size = SFP_DEV_SIZE * 2,
	.read = qla2x00_sysfs_read_sfp,
};

static ssize_t
qla2x00_sysfs_write_reset(struct file *filp, struct kobject *kobj,
			struct bin_attribute *bin_attr,
			char *buf, loff_t off, size_t count)
{
	struct scsi_qla_host *vha = shost_priv(dev_to_shost(container_of(kobj,
	    struct device, kobj)));
	struct qla_hw_data *ha = vha->hw;
	struct scsi_qla_host *base_vha = pci_get_drvdata(ha->pdev);
	int type;

	if (off != 0)
<<<<<<< HEAD
<<<<<<< HEAD
		return -EINVAL;
=======
		return 0;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		return 0;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	type = simple_strtol(buf, NULL, 10);
	switch (type) {
	case 0x2025c:
<<<<<<< HEAD
<<<<<<< HEAD
		ql_log(ql_log_info, vha, 0x706e,
		    "Issuing ISP reset.\n");

		scsi_block_requests(vha->host);
		set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
		if (IS_QLA82XX(ha)) {
			qla82xx_idc_lock(ha);
			qla82xx_set_reset_owner(vha);
			qla82xx_idc_unlock(ha);
		}
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		qla_printk(KERN_INFO, ha,
		    "Issuing ISP reset on (%ld).\n", vha->host_no);

		scsi_block_requests(vha->host);
		set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		qla2xxx_wake_dpc(vha);
		qla2x00_wait_for_chip_reset(vha);
		scsi_unblock_requests(vha->host);
		break;
	case 0x2025d:
		if (!IS_QLA81XX(ha))
<<<<<<< HEAD
<<<<<<< HEAD
			return -EPERM;

		ql_log(ql_log_info, vha, 0x706f,
		    "Issuing MPI reset.\n");
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			break;

		qla_printk(KERN_INFO, ha,
		    "Issuing MPI reset on (%ld).\n", vha->host_no);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

		/* Make sure FC side is not in reset */
		qla2x00_wait_for_hba_online(vha);

		/* Issue MPI reset */
		scsi_block_requests(vha->host);
		if (qla81xx_restart_mpi_firmware(vha) != QLA_SUCCESS)
<<<<<<< HEAD
<<<<<<< HEAD
			ql_log(ql_log_warn, vha, 0x7070,
			    "MPI reset failed.\n");
=======
			qla_printk(KERN_WARNING, ha,
			    "MPI reset failed on (%ld).\n", vha->host_no);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			qla_printk(KERN_WARNING, ha,
			    "MPI reset failed on (%ld).\n", vha->host_no);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		scsi_unblock_requests(vha->host);
		break;
	case 0x2025e:
		if (!IS_QLA82XX(ha) || vha != base_vha) {
<<<<<<< HEAD
<<<<<<< HEAD
			ql_log(ql_log_info, vha, 0x7071,
			    "FCoE ctx reset no supported.\n");
			return -EPERM;
		}

		ql_log(ql_log_info, vha, 0x7072,
		    "Issuing FCoE ctx reset.\n");
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			qla_printk(KERN_INFO, ha,
			    "FCoE ctx reset not supported for host%ld.\n",
			    vha->host_no);
			return count;
		}

		qla_printk(KERN_INFO, ha,
		    "Issuing FCoE CTX reset on host%ld.\n", vha->host_no);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		set_bit(FCOE_CTX_RESET_NEEDED, &vha->dpc_flags);
		qla2xxx_wake_dpc(vha);
		qla2x00_wait_for_fcoe_ctx_reset(vha);
		break;
	}
	return count;
}

static struct bin_attribute sysfs_reset_attr = {
	.attr = {
		.name = "reset",
		.mode = S_IWUSR,
	},
	.size = 0,
	.write = qla2x00_sysfs_write_reset,
};

static ssize_t
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
qla2x00_sysfs_write_edc(struct file *filp, struct kobject *kobj,
			struct bin_attribute *bin_attr,
			char *buf, loff_t off, size_t count)
{
	struct scsi_qla_host *vha = shost_priv(dev_to_shost(container_of(kobj,
	    struct device, kobj)));
	struct qla_hw_data *ha = vha->hw;
	uint16_t dev, adr, opt, len;
	int rval;

	ha->edc_data_len = 0;

	if (!capable(CAP_SYS_ADMIN) || off != 0 || count < 8)
		return 0;

	if (!ha->edc_data) {
		ha->edc_data = dma_pool_alloc(ha->s_dma_pool, GFP_KERNEL,
		    &ha->edc_data_dma);
		if (!ha->edc_data) {
			DEBUG2(qla_printk(KERN_INFO, ha,
			    "Unable to allocate memory for EDC write.\n"));
			return 0;
		}
	}

	dev = le16_to_cpup((void *)&buf[0]);
	adr = le16_to_cpup((void *)&buf[2]);
	opt = le16_to_cpup((void *)&buf[4]);
	len = le16_to_cpup((void *)&buf[6]);

	if (!(opt & BIT_0))
		if (len == 0 || len > DMA_POOL_SIZE || len > count - 8)
			return -EINVAL;

	memcpy(ha->edc_data, &buf[8], len);

	rval = qla2x00_write_sfp(vha, ha->edc_data_dma, ha->edc_data,
	    dev, adr, len, opt);
	if (rval != QLA_SUCCESS) {
		DEBUG2(qla_printk(KERN_INFO, ha,
		    "Unable to write EDC (%x) %02x:%02x:%04x:%02x:%02x.\n",
		    rval, dev, adr, opt, len, buf[8]));
		return 0;
	}

	return count;
}

static struct bin_attribute sysfs_edc_attr = {
	.attr = {
		.name = "edc",
		.mode = S_IWUSR,
	},
	.size = 0,
	.write = qla2x00_sysfs_write_edc,
};

static ssize_t
qla2x00_sysfs_write_edc_status(struct file *filp, struct kobject *kobj,
			struct bin_attribute *bin_attr,
			char *buf, loff_t off, size_t count)
{
	struct scsi_qla_host *vha = shost_priv(dev_to_shost(container_of(kobj,
	    struct device, kobj)));
	struct qla_hw_data *ha = vha->hw;
	uint16_t dev, adr, opt, len;
	int rval;

	ha->edc_data_len = 0;

	if (!capable(CAP_SYS_ADMIN) || off != 0 || count < 8)
		return 0;

	if (!ha->edc_data) {
		ha->edc_data = dma_pool_alloc(ha->s_dma_pool, GFP_KERNEL,
		    &ha->edc_data_dma);
		if (!ha->edc_data) {
			DEBUG2(qla_printk(KERN_INFO, ha,
			    "Unable to allocate memory for EDC status.\n"));
			return 0;
		}
	}

	dev = le16_to_cpup((void *)&buf[0]);
	adr = le16_to_cpup((void *)&buf[2]);
	opt = le16_to_cpup((void *)&buf[4]);
	len = le16_to_cpup((void *)&buf[6]);

	if (!(opt & BIT_0))
		if (len == 0 || len > DMA_POOL_SIZE)
			return -EINVAL;

	memset(ha->edc_data, 0, len);
	rval = qla2x00_read_sfp(vha, ha->edc_data_dma, ha->edc_data,
			dev, adr, len, opt);
	if (rval != QLA_SUCCESS) {
		DEBUG2(qla_printk(KERN_INFO, ha,
		    "Unable to write EDC status (%x) %02x:%02x:%04x:%02x.\n",
		    rval, dev, adr, opt, len));
		return 0;
	}

	ha->edc_data_len = len;

	return count;
}

static ssize_t
qla2x00_sysfs_read_edc_status(struct file *filp, struct kobject *kobj,
			   struct bin_attribute *bin_attr,
			   char *buf, loff_t off, size_t count)
{
	struct scsi_qla_host *vha = shost_priv(dev_to_shost(container_of(kobj,
	    struct device, kobj)));
	struct qla_hw_data *ha = vha->hw;

	if (!capable(CAP_SYS_ADMIN) || off != 0 || count == 0)
		return 0;

	if (!ha->edc_data || ha->edc_data_len == 0 || ha->edc_data_len > count)
		return -EINVAL;

	memcpy(buf, ha->edc_data, ha->edc_data_len);

	return ha->edc_data_len;
}

static struct bin_attribute sysfs_edc_status_attr = {
	.attr = {
		.name = "edc_status",
		.mode = S_IRUSR | S_IWUSR,
	},
	.size = 0,
	.write = qla2x00_sysfs_write_edc_status,
	.read = qla2x00_sysfs_read_edc_status,
};

static ssize_t
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
qla2x00_sysfs_read_xgmac_stats(struct file *filp, struct kobject *kobj,
		       struct bin_attribute *bin_attr,
		       char *buf, loff_t off, size_t count)
{
	struct scsi_qla_host *vha = shost_priv(dev_to_shost(container_of(kobj,
	    struct device, kobj)));
	struct qla_hw_data *ha = vha->hw;
	int rval;
	uint16_t actual_size;

	if (!capable(CAP_SYS_ADMIN) || off != 0 || count > XGMAC_DATA_SIZE)
		return 0;

	if (ha->xgmac_data)
		goto do_read;

	ha->xgmac_data = dma_alloc_coherent(&ha->pdev->dev, XGMAC_DATA_SIZE,
	    &ha->xgmac_data_dma, GFP_KERNEL);
	if (!ha->xgmac_data) {
<<<<<<< HEAD
<<<<<<< HEAD
		ql_log(ql_log_warn, vha, 0x7076,
=======
		qla_printk(KERN_WARNING, ha,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		qla_printk(KERN_WARNING, ha,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		    "Unable to allocate memory for XGMAC read-data.\n");
		return 0;
	}

do_read:
	actual_size = 0;
	memset(ha->xgmac_data, 0, XGMAC_DATA_SIZE);

	rval = qla2x00_get_xgmac_stats(vha, ha->xgmac_data_dma,
	    XGMAC_DATA_SIZE, &actual_size);
	if (rval != QLA_SUCCESS) {
<<<<<<< HEAD
<<<<<<< HEAD
		ql_log(ql_log_warn, vha, 0x7077,
=======
		qla_printk(KERN_WARNING, ha,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		qla_printk(KERN_WARNING, ha,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		    "Unable to read XGMAC data (%x).\n", rval);
		count = 0;
	}

	count = actual_size > count ? count: actual_size;
	memcpy(buf, ha->xgmac_data, count);

	return count;
}

static struct bin_attribute sysfs_xgmac_stats_attr = {
	.attr = {
		.name = "xgmac_stats",
		.mode = S_IRUSR,
	},
	.size = 0,
	.read = qla2x00_sysfs_read_xgmac_stats,
};

static ssize_t
qla2x00_sysfs_read_dcbx_tlv(struct file *filp, struct kobject *kobj,
		       struct bin_attribute *bin_attr,
		       char *buf, loff_t off, size_t count)
{
	struct scsi_qla_host *vha = shost_priv(dev_to_shost(container_of(kobj,
	    struct device, kobj)));
	struct qla_hw_data *ha = vha->hw;
	int rval;
	uint16_t actual_size;

	if (!capable(CAP_SYS_ADMIN) || off != 0 || count > DCBX_TLV_DATA_SIZE)
		return 0;

	if (ha->dcbx_tlv)
		goto do_read;

	ha->dcbx_tlv = dma_alloc_coherent(&ha->pdev->dev, DCBX_TLV_DATA_SIZE,
	    &ha->dcbx_tlv_dma, GFP_KERNEL);
	if (!ha->dcbx_tlv) {
<<<<<<< HEAD
<<<<<<< HEAD
		ql_log(ql_log_warn, vha, 0x7078,
		    "Unable to allocate memory for DCBX TLV read-data.\n");
		return -ENOMEM;
=======
		qla_printk(KERN_WARNING, ha,
		    "Unable to allocate memory for DCBX TLV read-data.\n");
		return 0;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		qla_printk(KERN_WARNING, ha,
		    "Unable to allocate memory for DCBX TLV read-data.\n");
		return 0;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}

do_read:
	actual_size = 0;
	memset(ha->dcbx_tlv, 0, DCBX_TLV_DATA_SIZE);

	rval = qla2x00_get_dcbx_params(vha, ha->dcbx_tlv_dma,
	    DCBX_TLV_DATA_SIZE);
	if (rval != QLA_SUCCESS) {
<<<<<<< HEAD
<<<<<<< HEAD
		ql_log(ql_log_warn, vha, 0x7079,
		    "Unable to read DCBX TLV (%x).\n", rval);
		return -EIO;
=======
		qla_printk(KERN_WARNING, ha,
		    "Unable to read DCBX TLV data (%x).\n", rval);
		count = 0;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		qla_printk(KERN_WARNING, ha,
		    "Unable to read DCBX TLV data (%x).\n", rval);
		count = 0;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}

	memcpy(buf, ha->dcbx_tlv, count);

	return count;
}

static struct bin_attribute sysfs_dcbx_tlv_attr = {
	.attr = {
		.name = "dcbx_tlv",
		.mode = S_IRUSR,
	},
	.size = 0,
	.read = qla2x00_sysfs_read_dcbx_tlv,
};

static struct sysfs_entry {
	char *name;
	struct bin_attribute *attr;
	int is4GBp_only;
} bin_file_entries[] = {
	{ "fw_dump", &sysfs_fw_dump_attr, },
	{ "nvram", &sysfs_nvram_attr, },
	{ "optrom", &sysfs_optrom_attr, },
	{ "optrom_ctl", &sysfs_optrom_ctl_attr, },
	{ "vpd", &sysfs_vpd_attr, 1 },
	{ "sfp", &sysfs_sfp_attr, 1 },
	{ "reset", &sysfs_reset_attr, },
<<<<<<< HEAD
<<<<<<< HEAD
=======
	{ "edc", &sysfs_edc_attr, 2 },
	{ "edc_status", &sysfs_edc_status_attr, 2 },
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	{ "edc", &sysfs_edc_attr, 2 },
	{ "edc_status", &sysfs_edc_status_attr, 2 },
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	{ "xgmac_stats", &sysfs_xgmac_stats_attr, 3 },
	{ "dcbx_tlv", &sysfs_dcbx_tlv_attr, 3 },
	{ NULL },
};

void
qla2x00_alloc_sysfs_attr(scsi_qla_host_t *vha)
{
	struct Scsi_Host *host = vha->host;
	struct sysfs_entry *iter;
	int ret;

	for (iter = bin_file_entries; iter->name; iter++) {
		if (iter->is4GBp_only && !IS_FWI2_CAPABLE(vha->hw))
			continue;
		if (iter->is4GBp_only == 2 && !IS_QLA25XX(vha->hw))
			continue;
<<<<<<< HEAD
<<<<<<< HEAD
		if (iter->is4GBp_only == 3 && !(IS_CNA_CAPABLE(vha->hw)))
=======
		if (iter->is4GBp_only == 3 && !(IS_QLA8XXX_TYPE(vha->hw)))
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		if (iter->is4GBp_only == 3 && !(IS_QLA8XXX_TYPE(vha->hw)))
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			continue;

		ret = sysfs_create_bin_file(&host->shost_gendev.kobj,
		    iter->attr);
		if (ret)
<<<<<<< HEAD
<<<<<<< HEAD
			ql_log(ql_log_warn, vha, 0x00f3,
			    "Unable to create sysfs %s binary attribute (%d).\n",
			    iter->name, ret);
		else
			ql_dbg(ql_dbg_init, vha, 0x00f4,
			    "Successfully created sysfs %s binary attribure.\n",
			    iter->name);
=======
			qla_printk(KERN_INFO, vha->hw,
			    "Unable to create sysfs %s binary attribute "
			    "(%d).\n", iter->name, ret);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			qla_printk(KERN_INFO, vha->hw,
			    "Unable to create sysfs %s binary attribute "
			    "(%d).\n", iter->name, ret);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}
}

void
qla2x00_free_sysfs_attr(scsi_qla_host_t *vha)
{
	struct Scsi_Host *host = vha->host;
	struct sysfs_entry *iter;
	struct qla_hw_data *ha = vha->hw;

	for (iter = bin_file_entries; iter->name; iter++) {
		if (iter->is4GBp_only && !IS_FWI2_CAPABLE(ha))
			continue;
		if (iter->is4GBp_only == 2 && !IS_QLA25XX(ha))
			continue;
<<<<<<< HEAD
<<<<<<< HEAD
		if (iter->is4GBp_only == 3 && !(IS_CNA_CAPABLE(vha->hw)))
=======
		if (iter->is4GBp_only == 3 && !!(IS_QLA8XXX_TYPE(vha->hw)))
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		if (iter->is4GBp_only == 3 && !!(IS_QLA8XXX_TYPE(vha->hw)))
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			continue;

		sysfs_remove_bin_file(&host->shost_gendev.kobj,
		    iter->attr);
	}

	if (ha->beacon_blink_led == 1)
		ha->isp_ops->beacon_off(vha);
}

/* Scsi_Host attributes. */

static ssize_t
qla2x00_drvr_version_show(struct device *dev,
			  struct device_attribute *attr, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "%s\n", qla2x00_version_str);
}

static ssize_t
qla2x00_fw_version_show(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	struct qla_hw_data *ha = vha->hw;
	char fw_str[128];

	return snprintf(buf, PAGE_SIZE, "%s\n",
	    ha->isp_ops->fw_version_str(vha, fw_str));
}

static ssize_t
qla2x00_serial_num_show(struct device *dev, struct device_attribute *attr,
			char *buf)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	struct qla_hw_data *ha = vha->hw;
	uint32_t sn;

	if (IS_FWI2_CAPABLE(ha)) {
		qla2xxx_get_vpd_field(vha, "SN", buf, PAGE_SIZE);
		return snprintf(buf, PAGE_SIZE, "%s\n", buf);
	}

	sn = ((ha->serial0 & 0x1f) << 16) | (ha->serial2 << 8) | ha->serial1;
	return snprintf(buf, PAGE_SIZE, "%c%05d\n", 'A' + sn / 100000,
	    sn % 100000);
}

static ssize_t
qla2x00_isp_name_show(struct device *dev, struct device_attribute *attr,
		      char *buf)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	return snprintf(buf, PAGE_SIZE, "ISP%04X\n", vha->hw->pdev->device);
}

static ssize_t
qla2x00_isp_id_show(struct device *dev, struct device_attribute *attr,
		    char *buf)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	struct qla_hw_data *ha = vha->hw;
	return snprintf(buf, PAGE_SIZE, "%04x %04x %04x %04x\n",
	    ha->product_id[0], ha->product_id[1], ha->product_id[2],
	    ha->product_id[3]);
}

static ssize_t
qla2x00_model_name_show(struct device *dev, struct device_attribute *attr,
			char *buf)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	return snprintf(buf, PAGE_SIZE, "%s\n", vha->hw->model_number);
}

static ssize_t
qla2x00_model_desc_show(struct device *dev, struct device_attribute *attr,
			char *buf)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	return snprintf(buf, PAGE_SIZE, "%s\n",
	    vha->hw->model_desc ? vha->hw->model_desc : "");
}

static ssize_t
qla2x00_pci_info_show(struct device *dev, struct device_attribute *attr,
		      char *buf)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	char pci_info[30];

	return snprintf(buf, PAGE_SIZE, "%s\n",
	    vha->hw->isp_ops->pci_info_str(vha, pci_info));
}

static ssize_t
qla2x00_link_state_show(struct device *dev, struct device_attribute *attr,
			char *buf)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	struct qla_hw_data *ha = vha->hw;
	int len = 0;

	if (atomic_read(&vha->loop_state) == LOOP_DOWN ||
	    atomic_read(&vha->loop_state) == LOOP_DEAD ||
	    vha->device_flags & DFLG_NO_CABLE)
		len = snprintf(buf, PAGE_SIZE, "Link Down\n");
	else if (atomic_read(&vha->loop_state) != LOOP_READY ||
<<<<<<< HEAD
<<<<<<< HEAD
	    qla2x00_reset_active(vha))
=======
	    test_bit(ABORT_ISP_ACTIVE, &vha->dpc_flags) ||
	    test_bit(ISP_ABORT_NEEDED, &vha->dpc_flags))
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	    test_bit(ABORT_ISP_ACTIVE, &vha->dpc_flags) ||
	    test_bit(ISP_ABORT_NEEDED, &vha->dpc_flags))
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		len = snprintf(buf, PAGE_SIZE, "Unknown Link State\n");
	else {
		len = snprintf(buf, PAGE_SIZE, "Link Up - ");

		switch (ha->current_topology) {
		case ISP_CFG_NL:
			len += snprintf(buf + len, PAGE_SIZE-len, "Loop\n");
			break;
		case ISP_CFG_FL:
			len += snprintf(buf + len, PAGE_SIZE-len, "FL_Port\n");
			break;
		case ISP_CFG_N:
			len += snprintf(buf + len, PAGE_SIZE-len,
			    "N_Port to N_Port\n");
			break;
		case ISP_CFG_F:
			len += snprintf(buf + len, PAGE_SIZE-len, "F_Port\n");
			break;
		default:
			len += snprintf(buf + len, PAGE_SIZE-len, "Loop\n");
			break;
		}
	}
	return len;
}

static ssize_t
qla2x00_zio_show(struct device *dev, struct device_attribute *attr,
		 char *buf)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	int len = 0;

	switch (vha->hw->zio_mode) {
	case QLA_ZIO_MODE_6:
		len += snprintf(buf + len, PAGE_SIZE-len, "Mode 6\n");
		break;
	case QLA_ZIO_DISABLED:
		len += snprintf(buf + len, PAGE_SIZE-len, "Disabled\n");
		break;
	}
	return len;
}

static ssize_t
qla2x00_zio_store(struct device *dev, struct device_attribute *attr,
		  const char *buf, size_t count)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	struct qla_hw_data *ha = vha->hw;
	int val = 0;
	uint16_t zio_mode;

	if (!IS_ZIO_SUPPORTED(ha))
		return -ENOTSUPP;

	if (sscanf(buf, "%d", &val) != 1)
		return -EINVAL;

	if (val)
		zio_mode = QLA_ZIO_MODE_6;
	else
		zio_mode = QLA_ZIO_DISABLED;

	/* Update per-hba values and queue a reset. */
	if (zio_mode != QLA_ZIO_DISABLED || ha->zio_mode != QLA_ZIO_DISABLED) {
		ha->zio_mode = zio_mode;
		set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
	}
	return strlen(buf);
}

static ssize_t
qla2x00_zio_timer_show(struct device *dev, struct device_attribute *attr,
		       char *buf)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));

	return snprintf(buf, PAGE_SIZE, "%d us\n", vha->hw->zio_timer * 100);
}

static ssize_t
qla2x00_zio_timer_store(struct device *dev, struct device_attribute *attr,
			const char *buf, size_t count)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	int val = 0;
	uint16_t zio_timer;

	if (sscanf(buf, "%d", &val) != 1)
		return -EINVAL;
	if (val > 25500 || val < 100)
		return -ERANGE;

	zio_timer = (uint16_t)(val / 100);
	vha->hw->zio_timer = zio_timer;

	return strlen(buf);
}

static ssize_t
qla2x00_beacon_show(struct device *dev, struct device_attribute *attr,
		    char *buf)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	int len = 0;

	if (vha->hw->beacon_blink_led)
		len += snprintf(buf + len, PAGE_SIZE-len, "Enabled\n");
	else
		len += snprintf(buf + len, PAGE_SIZE-len, "Disabled\n");
	return len;
}

static ssize_t
qla2x00_beacon_store(struct device *dev, struct device_attribute *attr,
		     const char *buf, size_t count)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	struct qla_hw_data *ha = vha->hw;
	int val = 0;
	int rval;

	if (IS_QLA2100(ha) || IS_QLA2200(ha))
		return -EPERM;

	if (test_bit(ABORT_ISP_ACTIVE, &vha->dpc_flags)) {
<<<<<<< HEAD
<<<<<<< HEAD
		ql_log(ql_log_warn, vha, 0x707a,
=======
		qla_printk(KERN_WARNING, ha,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		qla_printk(KERN_WARNING, ha,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		    "Abort ISP active -- ignoring beacon request.\n");
		return -EBUSY;
	}

	if (sscanf(buf, "%d", &val) != 1)
		return -EINVAL;

	if (val)
		rval = ha->isp_ops->beacon_on(vha);
	else
		rval = ha->isp_ops->beacon_off(vha);

	if (rval != QLA_SUCCESS)
		count = 0;

	return count;
}

static ssize_t
qla2x00_optrom_bios_version_show(struct device *dev,
				 struct device_attribute *attr, char *buf)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	struct qla_hw_data *ha = vha->hw;
	return snprintf(buf, PAGE_SIZE, "%d.%02d\n", ha->bios_revision[1],
	    ha->bios_revision[0]);
}

static ssize_t
qla2x00_optrom_efi_version_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	struct qla_hw_data *ha = vha->hw;
	return snprintf(buf, PAGE_SIZE, "%d.%02d\n", ha->efi_revision[1],
	    ha->efi_revision[0]);
}

static ssize_t
qla2x00_optrom_fcode_version_show(struct device *dev,
				  struct device_attribute *attr, char *buf)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	struct qla_hw_data *ha = vha->hw;
	return snprintf(buf, PAGE_SIZE, "%d.%02d\n", ha->fcode_revision[1],
	    ha->fcode_revision[0]);
}

static ssize_t
qla2x00_optrom_fw_version_show(struct device *dev,
			       struct device_attribute *attr, char *buf)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	struct qla_hw_data *ha = vha->hw;
	return snprintf(buf, PAGE_SIZE, "%d.%02d.%02d %d\n",
	    ha->fw_revision[0], ha->fw_revision[1], ha->fw_revision[2],
	    ha->fw_revision[3]);
}

static ssize_t
qla2x00_optrom_gold_fw_version_show(struct device *dev,
    struct device_attribute *attr, char *buf)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	struct qla_hw_data *ha = vha->hw;

<<<<<<< HEAD
<<<<<<< HEAD
	if (!IS_QLA81XX(ha) && !IS_QLA83XX(ha))
=======
	if (!IS_QLA81XX(ha))
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	if (!IS_QLA81XX(ha))
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return snprintf(buf, PAGE_SIZE, "\n");

	return snprintf(buf, PAGE_SIZE, "%d.%02d.%02d (%d)\n",
	    ha->gold_fw_version[0], ha->gold_fw_version[1],
	    ha->gold_fw_version[2], ha->gold_fw_version[3]);
}

static ssize_t
qla2x00_total_isp_aborts_show(struct device *dev,
			      struct device_attribute *attr, char *buf)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	struct qla_hw_data *ha = vha->hw;
	return snprintf(buf, PAGE_SIZE, "%d\n",
	    ha->qla_stats.total_isp_aborts);
}

static ssize_t
qla24xx_84xx_fw_version_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	int rval = QLA_SUCCESS;
	uint16_t status[2] = {0, 0};
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	struct qla_hw_data *ha = vha->hw;

	if (!IS_QLA84XX(ha))
		return snprintf(buf, PAGE_SIZE, "\n");

	if (ha->cs84xx->op_fw_version == 0)
		rval = qla84xx_verify_chip(vha, status);

	if ((rval == QLA_SUCCESS) && (status[0] == 0))
		return snprintf(buf, PAGE_SIZE, "%u\n",
			(uint32_t)ha->cs84xx->op_fw_version);

	return snprintf(buf, PAGE_SIZE, "\n");
}

static ssize_t
qla2x00_mpi_version_show(struct device *dev, struct device_attribute *attr,
    char *buf)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	struct qla_hw_data *ha = vha->hw;

<<<<<<< HEAD
<<<<<<< HEAD
	if (!IS_QLA81XX(ha) && !IS_QLA8031(ha))
=======
	if (!IS_QLA81XX(ha))
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	if (!IS_QLA81XX(ha))
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return snprintf(buf, PAGE_SIZE, "\n");

	return snprintf(buf, PAGE_SIZE, "%d.%02d.%02d (%x)\n",
	    ha->mpi_version[0], ha->mpi_version[1], ha->mpi_version[2],
	    ha->mpi_capabilities);
}

static ssize_t
qla2x00_phy_version_show(struct device *dev, struct device_attribute *attr,
    char *buf)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	struct qla_hw_data *ha = vha->hw;

<<<<<<< HEAD
<<<<<<< HEAD
	if (!IS_QLA81XX(ha) && !IS_QLA83XX(ha))
=======
	if (!IS_QLA81XX(ha))
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	if (!IS_QLA81XX(ha))
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return snprintf(buf, PAGE_SIZE, "\n");

	return snprintf(buf, PAGE_SIZE, "%d.%02d.%02d\n",
	    ha->phy_version[0], ha->phy_version[1], ha->phy_version[2]);
}

static ssize_t
qla2x00_flash_block_size_show(struct device *dev,
			      struct device_attribute *attr, char *buf)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	struct qla_hw_data *ha = vha->hw;

	return snprintf(buf, PAGE_SIZE, "0x%x\n", ha->fdt_block_size);
}

static ssize_t
qla2x00_vlan_id_show(struct device *dev, struct device_attribute *attr,
    char *buf)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));

<<<<<<< HEAD
<<<<<<< HEAD
	if (!IS_CNA_CAPABLE(vha->hw))
=======
	if (!IS_QLA8XXX_TYPE(vha->hw))
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	if (!IS_QLA8XXX_TYPE(vha->hw))
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return snprintf(buf, PAGE_SIZE, "\n");

	return snprintf(buf, PAGE_SIZE, "%d\n", vha->fcoe_vlan_id);
}

static ssize_t
qla2x00_vn_port_mac_address_show(struct device *dev,
    struct device_attribute *attr, char *buf)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));

<<<<<<< HEAD
<<<<<<< HEAD
	if (!IS_CNA_CAPABLE(vha->hw))
=======
	if (!IS_QLA8XXX_TYPE(vha->hw))
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	if (!IS_QLA8XXX_TYPE(vha->hw))
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return snprintf(buf, PAGE_SIZE, "\n");

	return snprintf(buf, PAGE_SIZE, "%02x:%02x:%02x:%02x:%02x:%02x\n",
	    vha->fcoe_vn_port_mac[5], vha->fcoe_vn_port_mac[4],
	    vha->fcoe_vn_port_mac[3], vha->fcoe_vn_port_mac[2],
	    vha->fcoe_vn_port_mac[1], vha->fcoe_vn_port_mac[0]);
}

static ssize_t
qla2x00_fabric_param_show(struct device *dev, struct device_attribute *attr,
    char *buf)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));

	return snprintf(buf, PAGE_SIZE, "%d\n", vha->hw->switch_cap);
}

static ssize_t
qla2x00_thermal_temp_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	int rval = QLA_FUNCTION_FAILED;
	uint16_t temp, frac;

	if (!vha->hw->flags.thermal_supported)
		return snprintf(buf, PAGE_SIZE, "\n");

	temp = frac = 0;
<<<<<<< HEAD
<<<<<<< HEAD
	if (qla2x00_reset_active(vha))
		ql_log(ql_log_warn, vha, 0x707b,
		    "ISP reset active.\n");
	else if (!vha->hw->flags.eeh_busy)
		rval = qla2x00_get_thermal_temp(vha, &temp, &frac);
	if (rval != QLA_SUCCESS)
		return snprintf(buf, PAGE_SIZE, "\n");
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (test_bit(ABORT_ISP_ACTIVE, &vha->dpc_flags) ||
	    test_bit(ISP_ABORT_NEEDED, &vha->dpc_flags))
		DEBUG2_3_11(printk(KERN_WARNING
		    "%s(%ld): isp reset in progress.\n",
		    __func__, vha->host_no));
	else if (!vha->hw->flags.eeh_busy)
		rval = qla2x00_get_thermal_temp(vha, &temp, &frac);
	if (rval != QLA_SUCCESS)
		temp = frac = 0;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return snprintf(buf, PAGE_SIZE, "%d.%02d\n", temp, frac);
}

static ssize_t
qla2x00_fw_state_show(struct device *dev, struct device_attribute *attr,
    char *buf)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	int rval = QLA_FUNCTION_FAILED;
	uint16_t state[5];

<<<<<<< HEAD
<<<<<<< HEAD
	if (qla2x00_reset_active(vha))
		ql_log(ql_log_warn, vha, 0x707c,
		    "ISP reset active.\n");
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (test_bit(ABORT_ISP_ACTIVE, &vha->dpc_flags) ||
		test_bit(ISP_ABORT_NEEDED, &vha->dpc_flags))
		DEBUG2_3_11(printk("%s(%ld): isp reset in progress.\n",
			__func__, vha->host_no));
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	else if (!vha->hw->flags.eeh_busy)
		rval = qla2x00_get_firmware_state(vha, state);
	if (rval != QLA_SUCCESS)
		memset(state, -1, sizeof(state));

	return snprintf(buf, PAGE_SIZE, "0x%x 0x%x 0x%x 0x%x 0x%x\n", state[0],
	    state[1], state[2], state[3], state[4]);
}

static DEVICE_ATTR(driver_version, S_IRUGO, qla2x00_drvr_version_show, NULL);
static DEVICE_ATTR(fw_version, S_IRUGO, qla2x00_fw_version_show, NULL);
static DEVICE_ATTR(serial_num, S_IRUGO, qla2x00_serial_num_show, NULL);
static DEVICE_ATTR(isp_name, S_IRUGO, qla2x00_isp_name_show, NULL);
static DEVICE_ATTR(isp_id, S_IRUGO, qla2x00_isp_id_show, NULL);
static DEVICE_ATTR(model_name, S_IRUGO, qla2x00_model_name_show, NULL);
static DEVICE_ATTR(model_desc, S_IRUGO, qla2x00_model_desc_show, NULL);
static DEVICE_ATTR(pci_info, S_IRUGO, qla2x00_pci_info_show, NULL);
static DEVICE_ATTR(link_state, S_IRUGO, qla2x00_link_state_show, NULL);
static DEVICE_ATTR(zio, S_IRUGO | S_IWUSR, qla2x00_zio_show, qla2x00_zio_store);
static DEVICE_ATTR(zio_timer, S_IRUGO | S_IWUSR, qla2x00_zio_timer_show,
		   qla2x00_zio_timer_store);
static DEVICE_ATTR(beacon, S_IRUGO | S_IWUSR, qla2x00_beacon_show,
		   qla2x00_beacon_store);
static DEVICE_ATTR(optrom_bios_version, S_IRUGO,
		   qla2x00_optrom_bios_version_show, NULL);
static DEVICE_ATTR(optrom_efi_version, S_IRUGO,
		   qla2x00_optrom_efi_version_show, NULL);
static DEVICE_ATTR(optrom_fcode_version, S_IRUGO,
		   qla2x00_optrom_fcode_version_show, NULL);
static DEVICE_ATTR(optrom_fw_version, S_IRUGO, qla2x00_optrom_fw_version_show,
		   NULL);
static DEVICE_ATTR(optrom_gold_fw_version, S_IRUGO,
    qla2x00_optrom_gold_fw_version_show, NULL);
static DEVICE_ATTR(84xx_fw_version, S_IRUGO, qla24xx_84xx_fw_version_show,
		   NULL);
static DEVICE_ATTR(total_isp_aborts, S_IRUGO, qla2x00_total_isp_aborts_show,
		   NULL);
static DEVICE_ATTR(mpi_version, S_IRUGO, qla2x00_mpi_version_show, NULL);
static DEVICE_ATTR(phy_version, S_IRUGO, qla2x00_phy_version_show, NULL);
static DEVICE_ATTR(flash_block_size, S_IRUGO, qla2x00_flash_block_size_show,
		   NULL);
static DEVICE_ATTR(vlan_id, S_IRUGO, qla2x00_vlan_id_show, NULL);
static DEVICE_ATTR(vn_port_mac_address, S_IRUGO,
		   qla2x00_vn_port_mac_address_show, NULL);
static DEVICE_ATTR(fabric_param, S_IRUGO, qla2x00_fabric_param_show, NULL);
static DEVICE_ATTR(fw_state, S_IRUGO, qla2x00_fw_state_show, NULL);
static DEVICE_ATTR(thermal_temp, S_IRUGO, qla2x00_thermal_temp_show, NULL);

struct device_attribute *qla2x00_host_attrs[] = {
	&dev_attr_driver_version,
	&dev_attr_fw_version,
	&dev_attr_serial_num,
	&dev_attr_isp_name,
	&dev_attr_isp_id,
	&dev_attr_model_name,
	&dev_attr_model_desc,
	&dev_attr_pci_info,
	&dev_attr_link_state,
	&dev_attr_zio,
	&dev_attr_zio_timer,
	&dev_attr_beacon,
	&dev_attr_optrom_bios_version,
	&dev_attr_optrom_efi_version,
	&dev_attr_optrom_fcode_version,
	&dev_attr_optrom_fw_version,
	&dev_attr_84xx_fw_version,
	&dev_attr_total_isp_aborts,
	&dev_attr_mpi_version,
	&dev_attr_phy_version,
	&dev_attr_flash_block_size,
	&dev_attr_vlan_id,
	&dev_attr_vn_port_mac_address,
	&dev_attr_fabric_param,
	&dev_attr_fw_state,
	&dev_attr_optrom_gold_fw_version,
	&dev_attr_thermal_temp,
	NULL,
};

/* Host attributes. */

static void
qla2x00_get_host_port_id(struct Scsi_Host *shost)
{
	scsi_qla_host_t *vha = shost_priv(shost);

	fc_host_port_id(shost) = vha->d_id.b.domain << 16 |
	    vha->d_id.b.area << 8 | vha->d_id.b.al_pa;
}

static void
qla2x00_get_host_speed(struct Scsi_Host *shost)
{
	struct qla_hw_data *ha = ((struct scsi_qla_host *)
					(shost_priv(shost)))->hw;
	u32 speed = FC_PORTSPEED_UNKNOWN;

	switch (ha->link_data_rate) {
	case PORT_SPEED_1GB:
		speed = FC_PORTSPEED_1GBIT;
		break;
	case PORT_SPEED_2GB:
		speed = FC_PORTSPEED_2GBIT;
		break;
	case PORT_SPEED_4GB:
		speed = FC_PORTSPEED_4GBIT;
		break;
	case PORT_SPEED_8GB:
		speed = FC_PORTSPEED_8GBIT;
		break;
	case PORT_SPEED_10GB:
		speed = FC_PORTSPEED_10GBIT;
		break;
<<<<<<< HEAD
<<<<<<< HEAD
	case PORT_SPEED_16GB:
		speed = FC_PORTSPEED_16GBIT;
		break;
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}
	fc_host_speed(shost) = speed;
}

static void
qla2x00_get_host_port_type(struct Scsi_Host *shost)
{
	scsi_qla_host_t *vha = shost_priv(shost);
	uint32_t port_type = FC_PORTTYPE_UNKNOWN;

	if (vha->vp_idx) {
		fc_host_port_type(shost) = FC_PORTTYPE_NPIV;
		return;
	}
	switch (vha->hw->current_topology) {
	case ISP_CFG_NL:
		port_type = FC_PORTTYPE_LPORT;
		break;
	case ISP_CFG_FL:
		port_type = FC_PORTTYPE_NLPORT;
		break;
	case ISP_CFG_N:
		port_type = FC_PORTTYPE_PTP;
		break;
	case ISP_CFG_F:
		port_type = FC_PORTTYPE_NPORT;
		break;
	}
	fc_host_port_type(shost) = port_type;
}

static void
qla2x00_get_starget_node_name(struct scsi_target *starget)
{
	struct Scsi_Host *host = dev_to_shost(starget->dev.parent);
	scsi_qla_host_t *vha = shost_priv(host);
	fc_port_t *fcport;
	u64 node_name = 0;

	list_for_each_entry(fcport, &vha->vp_fcports, list) {
		if (fcport->rport &&
		    starget->id == fcport->rport->scsi_target_id) {
			node_name = wwn_to_u64(fcport->node_name);
			break;
		}
	}

	fc_starget_node_name(starget) = node_name;
}

static void
qla2x00_get_starget_port_name(struct scsi_target *starget)
{
	struct Scsi_Host *host = dev_to_shost(starget->dev.parent);
	scsi_qla_host_t *vha = shost_priv(host);
	fc_port_t *fcport;
	u64 port_name = 0;

	list_for_each_entry(fcport, &vha->vp_fcports, list) {
		if (fcport->rport &&
		    starget->id == fcport->rport->scsi_target_id) {
			port_name = wwn_to_u64(fcport->port_name);
			break;
		}
	}

	fc_starget_port_name(starget) = port_name;
}

static void
qla2x00_get_starget_port_id(struct scsi_target *starget)
{
	struct Scsi_Host *host = dev_to_shost(starget->dev.parent);
	scsi_qla_host_t *vha = shost_priv(host);
	fc_port_t *fcport;
	uint32_t port_id = ~0U;

	list_for_each_entry(fcport, &vha->vp_fcports, list) {
		if (fcport->rport &&
		    starget->id == fcport->rport->scsi_target_id) {
			port_id = fcport->d_id.b.domain << 16 |
			    fcport->d_id.b.area << 8 | fcport->d_id.b.al_pa;
			break;
		}
	}

	fc_starget_port_id(starget) = port_id;
}

static void
qla2x00_set_rport_loss_tmo(struct fc_rport *rport, uint32_t timeout)
{
	if (timeout)
		rport->dev_loss_tmo = timeout;
	else
		rport->dev_loss_tmo = 1;
}

static void
qla2x00_dev_loss_tmo_callbk(struct fc_rport *rport)
{
	struct Scsi_Host *host = rport_to_shost(rport);
	fc_port_t *fcport = *(fc_port_t **)rport->dd_data;
	unsigned long flags;

	if (!fcport)
		return;

	/* Now that the rport has been deleted, set the fcport state to
	   FCS_DEVICE_DEAD */
	qla2x00_set_fcport_state(fcport, FCS_DEVICE_DEAD);

	/*
	 * Transport has effectively 'deleted' the rport, clear
	 * all local references.
	 */
	spin_lock_irqsave(host->host_lock, flags);
	fcport->rport = fcport->drport = NULL;
	*((fc_port_t **)rport->dd_data) = NULL;
	spin_unlock_irqrestore(host->host_lock, flags);

	if (test_bit(ABORT_ISP_ACTIVE, &fcport->vha->dpc_flags))
		return;

	if (unlikely(pci_channel_offline(fcport->vha->hw->pdev))) {
		qla2x00_abort_all_cmds(fcport->vha, DID_NO_CONNECT << 16);
		return;
	}
}

static void
qla2x00_terminate_rport_io(struct fc_rport *rport)
{
	fc_port_t *fcport = *(fc_port_t **)rport->dd_data;

	if (!fcport)
		return;

	if (test_bit(ABORT_ISP_ACTIVE, &fcport->vha->dpc_flags))
		return;

	if (unlikely(pci_channel_offline(fcport->vha->hw->pdev))) {
		qla2x00_abort_all_cmds(fcport->vha, DID_NO_CONNECT << 16);
		return;
	}
	/*
	 * At this point all fcport's software-states are cleared.  Perform any
	 * final cleanup of firmware resources (PCBs and XCBs).
	 */
	if (fcport->loop_id != FC_NO_LOOP_ID &&
<<<<<<< HEAD
<<<<<<< HEAD
	    !test_bit(UNLOADING, &fcport->vha->dpc_flags)) {
		if (IS_FWI2_CAPABLE(fcport->vha->hw))
			fcport->vha->hw->isp_ops->fabric_logout(fcport->vha,
			    fcport->loop_id, fcport->d_id.b.domain,
			    fcport->d_id.b.area, fcport->d_id.b.al_pa);
		else
			qla2x00_port_logout(fcport->vha, fcport);
	}
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	    !test_bit(UNLOADING, &fcport->vha->dpc_flags))
		fcport->vha->hw->isp_ops->fabric_logout(fcport->vha,
			fcport->loop_id, fcport->d_id.b.domain,
			fcport->d_id.b.area, fcport->d_id.b.al_pa);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static int
qla2x00_issue_lip(struct Scsi_Host *shost)
{
	scsi_qla_host_t *vha = shost_priv(shost);

	qla2x00_loop_reset(vha);
	return 0;
}

static struct fc_host_statistics *
qla2x00_get_fc_host_stats(struct Scsi_Host *shost)
{
	scsi_qla_host_t *vha = shost_priv(shost);
	struct qla_hw_data *ha = vha->hw;
	struct scsi_qla_host *base_vha = pci_get_drvdata(ha->pdev);
	int rval;
	struct link_statistics *stats;
	dma_addr_t stats_dma;
	struct fc_host_statistics *pfc_host_stat;

	pfc_host_stat = &ha->fc_host_stat;
	memset(pfc_host_stat, -1, sizeof(struct fc_host_statistics));

	if (test_bit(UNLOADING, &vha->dpc_flags))
		goto done;

	if (unlikely(pci_channel_offline(ha->pdev)))
		goto done;

	stats = dma_pool_alloc(ha->s_dma_pool, GFP_KERNEL, &stats_dma);
	if (stats == NULL) {
<<<<<<< HEAD
<<<<<<< HEAD
		ql_log(ql_log_warn, vha, 0x707d,
		    "Failed to allocate memory for stats.\n");
=======
		DEBUG2_3_11(printk("%s(%ld): Failed to allocate memory.\n",
		    __func__, base_vha->host_no));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		DEBUG2_3_11(printk("%s(%ld): Failed to allocate memory.\n",
		    __func__, base_vha->host_no));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		goto done;
	}
	memset(stats, 0, DMA_POOL_SIZE);

	rval = QLA_FUNCTION_FAILED;
	if (IS_FWI2_CAPABLE(ha)) {
		rval = qla24xx_get_isp_stats(base_vha, stats, stats_dma);
	} else if (atomic_read(&base_vha->loop_state) == LOOP_READY &&
<<<<<<< HEAD
<<<<<<< HEAD
	    !qla2x00_reset_active(vha) && !ha->dpc_active) {
=======
		    !test_bit(ABORT_ISP_ACTIVE, &base_vha->dpc_flags) &&
		    !test_bit(ISP_ABORT_NEEDED, &base_vha->dpc_flags) &&
		    !ha->dpc_active) {
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		    !test_bit(ABORT_ISP_ACTIVE, &base_vha->dpc_flags) &&
		    !test_bit(ISP_ABORT_NEEDED, &base_vha->dpc_flags) &&
		    !ha->dpc_active) {
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		/* Must be in a 'READY' state for statistics retrieval. */
		rval = qla2x00_get_link_status(base_vha, base_vha->loop_id,
						stats, stats_dma);
	}

	if (rval != QLA_SUCCESS)
		goto done_free;

	pfc_host_stat->link_failure_count = stats->link_fail_cnt;
	pfc_host_stat->loss_of_sync_count = stats->loss_sync_cnt;
	pfc_host_stat->loss_of_signal_count = stats->loss_sig_cnt;
	pfc_host_stat->prim_seq_protocol_err_count = stats->prim_seq_err_cnt;
	pfc_host_stat->invalid_tx_word_count = stats->inval_xmit_word_cnt;
	pfc_host_stat->invalid_crc_count = stats->inval_crc_cnt;
	if (IS_FWI2_CAPABLE(ha)) {
		pfc_host_stat->lip_count = stats->lip_cnt;
		pfc_host_stat->tx_frames = stats->tx_frames;
		pfc_host_stat->rx_frames = stats->rx_frames;
		pfc_host_stat->dumped_frames = stats->dumped_frames;
		pfc_host_stat->nos_count = stats->nos_rcvd;
	}
	pfc_host_stat->fcp_input_megabytes = ha->qla_stats.input_bytes >> 20;
	pfc_host_stat->fcp_output_megabytes = ha->qla_stats.output_bytes >> 20;

done_free:
        dma_pool_free(ha->s_dma_pool, stats, stats_dma);
done:
	return pfc_host_stat;
}

static void
qla2x00_get_host_symbolic_name(struct Scsi_Host *shost)
{
	scsi_qla_host_t *vha = shost_priv(shost);

	qla2x00_get_sym_node_name(vha, fc_host_symbolic_name(shost));
}

static void
qla2x00_set_host_system_hostname(struct Scsi_Host *shost)
{
	scsi_qla_host_t *vha = shost_priv(shost);

	set_bit(REGISTER_FDMI_NEEDED, &vha->dpc_flags);
}

static void
qla2x00_get_host_fabric_name(struct Scsi_Host *shost)
{
	scsi_qla_host_t *vha = shost_priv(shost);
	uint8_t node_name[WWN_SIZE] = { 0xFF, 0xFF, 0xFF, 0xFF, \
		0xFF, 0xFF, 0xFF, 0xFF};
	u64 fabric_name = wwn_to_u64(node_name);

	if (vha->device_flags & SWITCH_FOUND)
		fabric_name = wwn_to_u64(vha->fabric_node_name);

	fc_host_fabric_name(shost) = fabric_name;
}

static void
qla2x00_get_host_port_state(struct Scsi_Host *shost)
{
	scsi_qla_host_t *vha = shost_priv(shost);
	struct scsi_qla_host *base_vha = pci_get_drvdata(vha->hw->pdev);

<<<<<<< HEAD
<<<<<<< HEAD
	if (!base_vha->flags.online) {
		fc_host_port_state(shost) = FC_PORTSTATE_OFFLINE;
		return;
	}

	switch (atomic_read(&base_vha->loop_state)) {
	case LOOP_UPDATE:
		fc_host_port_state(shost) = FC_PORTSTATE_DIAGNOSTICS;
		break;
	case LOOP_DOWN:
		if (test_bit(LOOP_RESYNC_NEEDED, &base_vha->dpc_flags))
			fc_host_port_state(shost) = FC_PORTSTATE_DIAGNOSTICS;
		else
			fc_host_port_state(shost) = FC_PORTSTATE_LINKDOWN;
		break;
	case LOOP_DEAD:
		fc_host_port_state(shost) = FC_PORTSTATE_LINKDOWN;
		break;
	case LOOP_READY:
		fc_host_port_state(shost) = FC_PORTSTATE_ONLINE;
		break;
	default:
		fc_host_port_state(shost) = FC_PORTSTATE_UNKNOWN;
		break;
	}
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (!base_vha->flags.online)
		fc_host_port_state(shost) = FC_PORTSTATE_OFFLINE;
	else if (atomic_read(&base_vha->loop_state) == LOOP_TIMEOUT)
		fc_host_port_state(shost) = FC_PORTSTATE_UNKNOWN;
	else
		fc_host_port_state(shost) = FC_PORTSTATE_ONLINE;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static int
qla24xx_vport_create(struct fc_vport *fc_vport, bool disable)
{
	int	ret = 0;
	uint8_t	qos = 0;
	scsi_qla_host_t *base_vha = shost_priv(fc_vport->shost);
	scsi_qla_host_t *vha = NULL;
	struct qla_hw_data *ha = base_vha->hw;
	uint16_t options = 0;
	int	cnt;
	struct req_que *req = ha->req_q_map[0];

	ret = qla24xx_vport_create_req_sanity_check(fc_vport);
	if (ret) {
<<<<<<< HEAD
<<<<<<< HEAD
		ql_log(ql_log_warn, vha, 0x707e,
		    "Vport sanity check failed, status %x\n", ret);
=======
		DEBUG15(printk("qla24xx_vport_create_req_sanity_check failed, "
		    "status %x\n", ret));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		DEBUG15(printk("qla24xx_vport_create_req_sanity_check failed, "
		    "status %x\n", ret));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return (ret);
	}

	vha = qla24xx_create_vhost(fc_vport);
	if (vha == NULL) {
<<<<<<< HEAD
<<<<<<< HEAD
		ql_log(ql_log_warn, vha, 0x707f, "Vport create host failed.\n");
=======
		DEBUG15(printk ("qla24xx_create_vhost failed, vha = %p\n",
		    vha));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		DEBUG15(printk ("qla24xx_create_vhost failed, vha = %p\n",
		    vha));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return FC_VPORT_FAILED;
	}
	if (disable) {
		atomic_set(&vha->vp_state, VP_OFFLINE);
		fc_vport_set_state(fc_vport, FC_VPORT_DISABLED);
	} else
		atomic_set(&vha->vp_state, VP_FAILED);

	/* ready to create vport */
<<<<<<< HEAD
<<<<<<< HEAD
	ql_log(ql_log_info, vha, 0x7080,
	    "VP entry id %d assigned.\n", vha->vp_idx);
=======
	qla_printk(KERN_INFO, vha->hw, "VP entry id %d assigned.\n",
							vha->vp_idx);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	qla_printk(KERN_INFO, vha->hw, "VP entry id %d assigned.\n",
							vha->vp_idx);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	/* initialized vport states */
	atomic_set(&vha->loop_state, LOOP_DOWN);
	vha->vp_err_state=  VP_ERR_PORTDWN;
	vha->vp_prev_err_state=  VP_ERR_UNKWN;
	/* Check if physical ha port is Up */
	if (atomic_read(&base_vha->loop_state) == LOOP_DOWN ||
	    atomic_read(&base_vha->loop_state) == LOOP_DEAD) {
		/* Don't retry or attempt login of this virtual port */
<<<<<<< HEAD
<<<<<<< HEAD
		ql_dbg(ql_dbg_user, vha, 0x7081,
		    "Vport loop state is not UP.\n");
=======
		DEBUG15(printk ("scsi(%ld): pport loop_state is not UP.\n",
		    base_vha->host_no));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		DEBUG15(printk ("scsi(%ld): pport loop_state is not UP.\n",
		    base_vha->host_no));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		atomic_set(&vha->loop_state, LOOP_DEAD);
		if (!disable)
			fc_vport_set_state(fc_vport, FC_VPORT_LINKDOWN);
	}

<<<<<<< HEAD
<<<<<<< HEAD
	if (IS_T10_PI_CAPABLE(ha) && ql2xenabledif) {
		if (ha->fw_attributes & BIT_4) {
			int prot = 0;
			vha->flags.difdix_supported = 1;
			ql_dbg(ql_dbg_user, vha, 0x7082,
			    "Registered for DIF/DIX type 1 and 3 protection.\n");
			if (ql2xenabledif == 1)
				prot = SHOST_DIX_TYPE0_PROTECTION;
			scsi_host_set_prot(vha->host,
			    prot | SHOST_DIF_TYPE1_PROTECTION
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if ((IS_QLA25XX(ha) || IS_QLA81XX(ha)) && ql2xenabledif) {
		if (ha->fw_attributes & BIT_4) {
			vha->flags.difdix_supported = 1;
			DEBUG18(qla_printk(KERN_INFO, ha,
			    "Registering for DIF/DIX type 1 and 3"
			    " protection.\n"));
			scsi_host_set_prot(vha->host,
			    SHOST_DIF_TYPE1_PROTECTION
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			    | SHOST_DIF_TYPE2_PROTECTION
			    | SHOST_DIF_TYPE3_PROTECTION
			    | SHOST_DIX_TYPE1_PROTECTION
			    | SHOST_DIX_TYPE2_PROTECTION
			    | SHOST_DIX_TYPE3_PROTECTION);
			scsi_host_set_guard(vha->host, SHOST_DIX_GUARD_CRC);
		} else
			vha->flags.difdix_supported = 0;
	}

	if (scsi_add_host_with_dma(vha->host, &fc_vport->dev,
				   &ha->pdev->dev)) {
<<<<<<< HEAD
<<<<<<< HEAD
		ql_dbg(ql_dbg_user, vha, 0x7083,
		    "scsi_add_host failure for VP[%d].\n", vha->vp_idx);
=======
		DEBUG15(printk("scsi(%ld): scsi_add_host failure for VP[%d].\n",
			vha->host_no, vha->vp_idx));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		DEBUG15(printk("scsi(%ld): scsi_add_host failure for VP[%d].\n",
			vha->host_no, vha->vp_idx));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		goto vport_create_failed_2;
	}

	/* initialize attributes */
	fc_host_dev_loss_tmo(vha->host) = ha->port_down_retry_count;
	fc_host_node_name(vha->host) = wwn_to_u64(vha->node_name);
	fc_host_port_name(vha->host) = wwn_to_u64(vha->port_name);
	fc_host_supported_classes(vha->host) =
		fc_host_supported_classes(base_vha->host);
	fc_host_supported_speeds(vha->host) =
		fc_host_supported_speeds(base_vha->host);

	qla24xx_vport_disable(fc_vport, disable);

	if (ha->flags.cpu_affinity_enabled) {
		req = ha->req_q_map[1];
<<<<<<< HEAD
<<<<<<< HEAD
		ql_dbg(ql_dbg_multiq, vha, 0xc000,
		    "Request queue %p attached with "
		    "VP[%d], cpu affinity =%d\n",
		    req, vha->vp_idx, ha->flags.cpu_affinity_enabled);
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		goto vport_queue;
	} else if (ql2xmaxqueues == 1 || !ha->npiv_info)
		goto vport_queue;
	/* Create a request queue in QoS mode for the vport */
	for (cnt = 0; cnt < ha->nvram_npiv_size; cnt++) {
		if (memcmp(ha->npiv_info[cnt].port_name, vha->port_name, 8) == 0
			&& memcmp(ha->npiv_info[cnt].node_name, vha->node_name,
					8) == 0) {
			qos = ha->npiv_info[cnt].q_qos;
			break;
		}
	}
<<<<<<< HEAD
<<<<<<< HEAD

=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (qos) {
		ret = qla25xx_create_req_que(ha, options, vha->vp_idx, 0, 0,
			qos);
		if (!ret)
<<<<<<< HEAD
<<<<<<< HEAD
			ql_log(ql_log_warn, vha, 0x7084,
			    "Can't create request queue for VP[%d]\n",
			    vha->vp_idx);
		else {
			ql_dbg(ql_dbg_multiq, vha, 0xc001,
			    "Request Que:%d Q0s: %d) created for VP[%d]\n",
			    ret, qos, vha->vp_idx);
			ql_dbg(ql_dbg_user, vha, 0x7085,
			    "Request Que:%d Q0s: %d) created for VP[%d]\n",
			    ret, qos, vha->vp_idx);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			qla_printk(KERN_WARNING, ha,
			"Can't create request queue for vp_idx:%d\n",
			vha->vp_idx);
		else {
			DEBUG2(qla_printk(KERN_INFO, ha,
			"Request Que:%d (QoS: %d) created for vp_idx:%d\n",
			ret, qos, vha->vp_idx));
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			req = ha->req_q_map[ret];
		}
	}

vport_queue:
	vha->req = req;
	return 0;

vport_create_failed_2:
	qla24xx_disable_vp(vha);
	qla24xx_deallocate_vp_id(vha);
	scsi_host_put(vha->host);
	return FC_VPORT_FAILED;
}

static int
qla24xx_vport_delete(struct fc_vport *fc_vport)
{
	scsi_qla_host_t *vha = fc_vport->dd_data;
	struct qla_hw_data *ha = vha->hw;
	uint16_t id = vha->vp_idx;

	while (test_bit(LOOP_RESYNC_ACTIVE, &vha->dpc_flags) ||
	    test_bit(FCPORT_UPDATE_NEEDED, &vha->dpc_flags))
		msleep(1000);

	qla24xx_disable_vp(vha);

	vha->flags.delete_progress = 1;

	fc_remove_host(vha->host);

	scsi_remove_host(vha->host);

	/* Allow timer to run to drain queued items, when removing vp */
	qla24xx_deallocate_vp_id(vha);

	if (vha->timer_active) {
		qla2x00_vp_stop_timer(vha);
<<<<<<< HEAD
<<<<<<< HEAD
		ql_dbg(ql_dbg_user, vha, 0x7086,
		    "Timer for the VP[%d] has stopped\n", vha->vp_idx);
	}

	/* No pending activities shall be there on the vha now */
	if (ql2xextended_error_logging & ql_dbg_user)
		msleep(random32()%10);  /* Just to see if something falls on
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		DEBUG15(printk(KERN_INFO "scsi(%ld): timer for the vport[%d]"
		" = %p has stopped\n", vha->host_no, vha->vp_idx, vha));
	}

	/* No pending activities shall be there on the vha now */
	DEBUG(msleep(random32()%10));  /* Just to see if something falls on
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
					* the net we have placed below */

	BUG_ON(atomic_read(&vha->vref_count));

	qla2x00_free_fcports(vha);

	mutex_lock(&ha->vport_lock);
	ha->cur_vport_count--;
	clear_bit(vha->vp_idx, ha->vp_idx_map);
	mutex_unlock(&ha->vport_lock);

	if (vha->req->id && !ha->flags.cpu_affinity_enabled) {
		if (qla25xx_delete_req_que(vha, vha->req) != QLA_SUCCESS)
<<<<<<< HEAD
<<<<<<< HEAD
			ql_log(ql_log_warn, vha, 0x7087,
			    "Queue delete failed.\n");
	}

	ql_log(ql_log_info, vha, 0x7088, "VP[%d] deleted.\n", id);
	scsi_host_put(vha->host);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			qla_printk(KERN_WARNING, ha,
				"Queue delete failed.\n");
	}

	scsi_host_put(vha->host);
	qla_printk(KERN_INFO, ha, "vport %d deleted\n", id);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return 0;
}

static int
qla24xx_vport_disable(struct fc_vport *fc_vport, bool disable)
{
	scsi_qla_host_t *vha = fc_vport->dd_data;

	if (disable)
		qla24xx_disable_vp(vha);
	else
		qla24xx_enable_vp(vha);

	return 0;
}

struct fc_function_template qla2xxx_transport_functions = {

	.show_host_node_name = 1,
	.show_host_port_name = 1,
	.show_host_supported_classes = 1,
	.show_host_supported_speeds = 1,

	.get_host_port_id = qla2x00_get_host_port_id,
	.show_host_port_id = 1,
	.get_host_speed = qla2x00_get_host_speed,
	.show_host_speed = 1,
	.get_host_port_type = qla2x00_get_host_port_type,
	.show_host_port_type = 1,
	.get_host_symbolic_name = qla2x00_get_host_symbolic_name,
	.show_host_symbolic_name = 1,
	.set_host_system_hostname = qla2x00_set_host_system_hostname,
	.show_host_system_hostname = 1,
	.get_host_fabric_name = qla2x00_get_host_fabric_name,
	.show_host_fabric_name = 1,
	.get_host_port_state = qla2x00_get_host_port_state,
	.show_host_port_state = 1,

	.dd_fcrport_size = sizeof(struct fc_port *),
	.show_rport_supported_classes = 1,

	.get_starget_node_name = qla2x00_get_starget_node_name,
	.show_starget_node_name = 1,
	.get_starget_port_name = qla2x00_get_starget_port_name,
	.show_starget_port_name = 1,
	.get_starget_port_id  = qla2x00_get_starget_port_id,
	.show_starget_port_id = 1,

	.set_rport_dev_loss_tmo = qla2x00_set_rport_loss_tmo,
	.show_rport_dev_loss_tmo = 1,

	.issue_fc_host_lip = qla2x00_issue_lip,
	.dev_loss_tmo_callbk = qla2x00_dev_loss_tmo_callbk,
	.terminate_rport_io = qla2x00_terminate_rport_io,
	.get_fc_host_stats = qla2x00_get_fc_host_stats,

	.vport_create = qla24xx_vport_create,
	.vport_disable = qla24xx_vport_disable,
	.vport_delete = qla24xx_vport_delete,
	.bsg_request = qla24xx_bsg_request,
	.bsg_timeout = qla24xx_bsg_timeout,
};

struct fc_function_template qla2xxx_transport_vport_functions = {

	.show_host_node_name = 1,
	.show_host_port_name = 1,
	.show_host_supported_classes = 1,

	.get_host_port_id = qla2x00_get_host_port_id,
	.show_host_port_id = 1,
	.get_host_speed = qla2x00_get_host_speed,
	.show_host_speed = 1,
	.get_host_port_type = qla2x00_get_host_port_type,
	.show_host_port_type = 1,
	.get_host_symbolic_name = qla2x00_get_host_symbolic_name,
	.show_host_symbolic_name = 1,
	.set_host_system_hostname = qla2x00_set_host_system_hostname,
	.show_host_system_hostname = 1,
	.get_host_fabric_name = qla2x00_get_host_fabric_name,
	.show_host_fabric_name = 1,
	.get_host_port_state = qla2x00_get_host_port_state,
	.show_host_port_state = 1,

	.dd_fcrport_size = sizeof(struct fc_port *),
	.show_rport_supported_classes = 1,

	.get_starget_node_name = qla2x00_get_starget_node_name,
	.show_starget_node_name = 1,
	.get_starget_port_name = qla2x00_get_starget_port_name,
	.show_starget_port_name = 1,
	.get_starget_port_id  = qla2x00_get_starget_port_id,
	.show_starget_port_id = 1,

	.set_rport_dev_loss_tmo = qla2x00_set_rport_loss_tmo,
	.show_rport_dev_loss_tmo = 1,

	.issue_fc_host_lip = qla2x00_issue_lip,
	.dev_loss_tmo_callbk = qla2x00_dev_loss_tmo_callbk,
	.terminate_rport_io = qla2x00_terminate_rport_io,
	.get_fc_host_stats = qla2x00_get_fc_host_stats,
	.bsg_request = qla24xx_bsg_request,
	.bsg_timeout = qla24xx_bsg_timeout,
};

void
qla2x00_init_host_attr(scsi_qla_host_t *vha)
{
	struct qla_hw_data *ha = vha->hw;
	u32 speed = FC_PORTSPEED_UNKNOWN;

	fc_host_dev_loss_tmo(vha->host) = ha->port_down_retry_count;
	fc_host_node_name(vha->host) = wwn_to_u64(vha->node_name);
	fc_host_port_name(vha->host) = wwn_to_u64(vha->port_name);
	fc_host_supported_classes(vha->host) = FC_COS_CLASS3;
	fc_host_max_npiv_vports(vha->host) = ha->max_npiv_vports;
	fc_host_npiv_vports_inuse(vha->host) = ha->cur_vport_count;

<<<<<<< HEAD
<<<<<<< HEAD
	if (IS_CNA_CAPABLE(ha))
=======
	if (IS_QLA8XXX_TYPE(ha))
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	if (IS_QLA8XXX_TYPE(ha))
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		speed = FC_PORTSPEED_10GBIT;
	else if (IS_QLA25XX(ha))
		speed = FC_PORTSPEED_8GBIT | FC_PORTSPEED_4GBIT |
		    FC_PORTSPEED_2GBIT | FC_PORTSPEED_1GBIT;
	else if (IS_QLA24XX_TYPE(ha))
		speed = FC_PORTSPEED_4GBIT | FC_PORTSPEED_2GBIT |
		    FC_PORTSPEED_1GBIT;
	else if (IS_QLA23XX(ha))
		speed = FC_PORTSPEED_2GBIT | FC_PORTSPEED_1GBIT;
	else
		speed = FC_PORTSPEED_1GBIT;
	fc_host_supported_speeds(vha->host) = speed;
}
