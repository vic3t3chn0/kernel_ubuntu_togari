<<<<<<< HEAD
/* Copyright (c) 2011-2014, The Linux Foundation. All rights reserved.
=======
/* Copyright (c) 2011-2012, Code Aurora Forum. All rights reserved.
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/slab.h>
#include <linux/diagchar.h>
#include <linux/platform_device.h>
<<<<<<< HEAD
#include <linux/kmemleak.h>
#include <linux/delay.h>
#include "diagchar.h"
#include "diagfwd.h"
#include "diagfwd_cntl.h"
/* tracks which peripheral is undergoing SSR */
static uint16_t reg_dirty;
#define HDR_SIZ 8

void diag_clean_reg_fn(struct work_struct *work)
{
	struct diag_smd_info *smd_info = container_of(work,
						struct diag_smd_info,
						diag_notify_update_smd_work);
	if (!smd_info)
		return;

	pr_debug("diag: clean registration for peripheral: %d\n",
		smd_info->peripheral);

	reg_dirty |= smd_info->peripheral_mask;
	diag_clear_reg(smd_info->peripheral);
	reg_dirty ^= smd_info->peripheral_mask;

	/* Reset the feature mask flag */
	driver->rcvd_feature_mask[smd_info->peripheral] = 0;

	smd_info->notify_context = 0;
}

void diag_cntl_smd_work_fn(struct work_struct *work)
{
	struct diag_smd_info *smd_info = container_of(work,
						struct diag_smd_info,
						diag_general_smd_work);

	if (!smd_info || smd_info->type != SMD_CNTL_TYPE)
		return;

	if (smd_info->general_context == UPDATE_PERIPHERAL_STM_STATE) {
		if (driver->peripheral_supports_stm[smd_info->peripheral] ==
								ENABLE_STM) {
			int status = 0;
			int index = smd_info->peripheral;
			status = diag_send_stm_state(smd_info,
				(uint8_t)(driver->stm_state_requested[index]));
			if (status == 1)
				driver->stm_state[index] =
					driver->stm_state_requested[index];
		}
	}
	smd_info->general_context = 0;
}

void diag_cntl_stm_notify(struct diag_smd_info *smd_info, int action)
{
	if (!smd_info || smd_info->type != SMD_CNTL_TYPE)
		return;

	if (action == CLEAR_PERIPHERAL_STM_STATE)
		driver->peripheral_supports_stm[smd_info->peripheral] =
								DISABLE_STM;
}

static void process_stm_feature(struct diag_smd_info *smd_info,
			      uint8_t feature_mask)
{
	if (feature_mask & F_DIAG_OVER_STM) {
		driver->peripheral_supports_stm[smd_info->peripheral] =
								ENABLE_STM;
		smd_info->general_context = UPDATE_PERIPHERAL_STM_STATE;
		queue_work(driver->diag_cntl_wq,
				&(smd_info->diag_general_smd_work));
	} else {
		driver->peripheral_supports_stm[smd_info->peripheral] =
								DISABLE_STM;
	}
}

static void process_hdlc_encoding_feature(struct diag_smd_info *smd_info,
					uint8_t feature_mask)
{
	/*
	 * Check if apps supports hdlc encoding and the
	 * peripheral supports apps hdlc encoding
	 */
	if (driver->supports_apps_hdlc_encoding &&
		(feature_mask & F_DIAG_HDLC_ENCODE_IN_APPS_MASK)) {
		driver->smd_data[smd_info->peripheral].encode_hdlc =
						ENABLE_APPS_HDLC_ENCODING;
		if (driver->separate_cmdrsp[smd_info->peripheral] &&
			smd_info->peripheral < NUM_SMD_CMD_CHANNELS)
			driver->smd_cmd[smd_info->peripheral].encode_hdlc =
						ENABLE_APPS_HDLC_ENCODING;
	} else {
		driver->smd_data[smd_info->peripheral].encode_hdlc =
						DISABLE_APPS_HDLC_ENCODING;
		if (driver->separate_cmdrsp[smd_info->peripheral] &&
			smd_info->peripheral < NUM_SMD_CMD_CHANNELS)
			driver->smd_cmd[smd_info->peripheral].encode_hdlc =
						DISABLE_APPS_HDLC_ENCODING;
	}
}

/* Process the data read from the smd control channel */
int diag_process_smd_cntl_read_data(struct diag_smd_info *smd_info, void *buf,
								int total_recd)
{
	int data_len = 0, type = -1, count_bytes = 0, j, flag = 0;
	struct bindpkt_params_per_process *pkt_params =
		kzalloc(sizeof(struct bindpkt_params_per_process), GFP_KERNEL);
	struct diag_ctrl_msg *msg;
	struct cmd_code_range *range;
	struct bindpkt_params *temp;

	if (pkt_params == NULL) {
		pr_alert("diag: In %s, Memory allocation failure\n",
			__func__);
		return 0;
	}

	if (!smd_info) {
		pr_err("diag: In %s, No smd info. Not able to read.\n",
			__func__);
		kfree(pkt_params);
		return 0;
	}

	while (count_bytes + HDR_SIZ <= total_recd) {
		type = *(uint32_t *)(buf);
		data_len = *(uint32_t *)(buf + 4);
		if (type < DIAG_CTRL_MSG_REG ||
				 type > DIAG_CTRL_MSG_LAST) {
			pr_alert("diag: In %s, Invalid Msg type %d proc %d",
				 __func__, type, smd_info->peripheral);
			break;
		}
		if (data_len < 0 || data_len > total_recd) {
			pr_alert("diag: In %s, Invalid data len %d, total_recd: %d, proc %d",
				 __func__, data_len, total_recd,
				 smd_info->peripheral);
			break;
		}
		count_bytes = count_bytes+HDR_SIZ+data_len;
		if (type == DIAG_CTRL_MSG_REG && total_recd >= count_bytes) {
			msg = buf+HDR_SIZ;
			range = buf+HDR_SIZ+
					sizeof(struct diag_ctrl_msg);
			if (msg->count_entries == 0) {
				pr_debug("diag: In %s, received reg tbl with no entries\n",
								__func__);
				buf = buf + HDR_SIZ + data_len;
				continue;
			}
			pkt_params->count = msg->count_entries;
			pkt_params->params = kzalloc(pkt_params->count *
				sizeof(struct bindpkt_params), GFP_KERNEL);
			if (!pkt_params->params) {
				pr_alert("diag: In %s, Memory alloc fail for cmd_code: %d, subsys: %d\n",
						__func__, msg->cmd_code,
						msg->subsysid);
				buf = buf + HDR_SIZ + data_len;
				continue;
			}
			temp = pkt_params->params;
			for (j = 0; j < pkt_params->count; j++) {
				temp->cmd_code = msg->cmd_code;
				temp->subsys_id = msg->subsysid;
				temp->client_id = smd_info->peripheral;
				temp->proc_id = NON_APPS_PROC;
				temp->cmd_code_lo = range->cmd_code_lo;
				temp->cmd_code_hi = range->cmd_code_hi;
				range++;
				temp++;
			}
			flag = 1;
			/* peripheral undergoing SSR should not
			 * record new registration
			 */
			if (!(reg_dirty & smd_info->peripheral_mask))
				diagchar_ioctl(NULL, DIAG_IOCTL_COMMAND_REG,
						(unsigned long)pkt_params);
			else
				pr_err("diag: drop reg proc %d\n",
						smd_info->peripheral);
			kfree(pkt_params->params);
		} else if (type == DIAG_CTRL_MSG_FEATURE &&
				total_recd >= count_bytes) {
			uint8_t feature_mask = 0;
			int feature_mask_len = *(int *)(buf+8);
			if (feature_mask_len > 0) {
				int periph = smd_info->peripheral;
				driver->rcvd_feature_mask[smd_info->peripheral]
									= 1;
				feature_mask = *(uint8_t *)(buf+12);
				if (periph == MODEM_DATA)
					driver->log_on_demand_support =
						feature_mask &
					F_DIAG_LOG_ON_DEMAND_RSP_ON_MASTER;
				/*
				 * If apps supports separate cmd/rsp channels
				 * and the peripheral supports separate cmd/rsp
				 * channels
				 */
				if (driver->supports_separate_cmdrsp &&
					(feature_mask & F_DIAG_REQ_RSP_CHANNEL))
					driver->separate_cmdrsp[periph] =
							ENABLE_SEPARATE_CMDRSP;
				else
					driver->separate_cmdrsp[periph] =
							DISABLE_SEPARATE_CMDRSP;
				/*
				 * Check if apps supports hdlc encoding and the
				 * peripheral supports apps hdlc encoding
				 */
				process_hdlc_encoding_feature(smd_info,
								feature_mask);
				if (feature_mask_len > 1) {
					feature_mask = *(uint8_t *)(buf+13);
					process_stm_feature(smd_info,
								feature_mask);
				}
			}
			flag = 1;
		} else if (type != DIAG_CTRL_MSG_REG) {
			flag = 1;
		}
		buf = buf + HDR_SIZ + data_len;
	}
	kfree(pkt_params);

	return flag;
}

void diag_update_proc_vote(uint16_t proc, uint8_t vote)
{
	mutex_lock(&driver->real_time_mutex);
	if (vote)
		driver->proc_active_mask |= proc;
	else {
		driver->proc_active_mask &= ~proc;
		driver->proc_rt_vote_mask |= proc;
	}
	mutex_unlock(&driver->real_time_mutex);
}

void diag_update_real_time_vote(uint16_t proc, uint8_t real_time)
{
	mutex_lock(&driver->real_time_mutex);
	if (real_time)
		driver->proc_rt_vote_mask |= proc;
	else
		driver->proc_rt_vote_mask &= ~proc;
	mutex_unlock(&driver->real_time_mutex);
}

#ifdef CONFIG_DIAG_OVER_USB
void diag_real_time_work_fn(struct work_struct *work)
{
	int temp_real_time = MODE_REALTIME, i;

	if (driver->proc_active_mask == 0) {
		/* There are no DCI or Memory Device processes. Diag should
		 * be in Real Time mode irrespective of USB connection
		 */
		temp_real_time = MODE_REALTIME;
	} else if (driver->proc_rt_vote_mask & driver->proc_active_mask) {
		/* Atleast one process is alive and is voting for Real Time
		 * data - Diag should be in real time mode irrespective of USB
		 * connection.
		 */
		temp_real_time = MODE_REALTIME;
	} else if (driver->usb_connected) {
		/* If USB is connected, check individual process. If Memory
		 * Device Mode is active, set the mode requested by Memory
		 * Device process. Set to realtime mode otherwise.
		 */
		if ((driver->proc_rt_vote_mask & DIAG_PROC_MEMORY_DEVICE) == 0)
			temp_real_time = MODE_NONREALTIME;
		else
			temp_real_time = MODE_REALTIME;
	} else {
		/* We come here if USB is not connected and the active
		 * processes are voting for Non realtime mode.
		 */
		temp_real_time = MODE_NONREALTIME;
	}

	if (temp_real_time != driver->real_time_mode) {
		for (i = 0; i < NUM_SMD_CONTROL_CHANNELS; i++)
			diag_send_diag_mode_update_by_smd(&driver->smd_cntl[i],
							temp_real_time);
	} else {
		pr_debug("diag: did not update real time mode, already in the req mode %d",
					temp_real_time);
	}
	if (driver->real_time_update_busy > 0)
		driver->real_time_update_busy--;
}
#else
void diag_real_time_work_fn(struct work_struct *work)
{
	int temp_real_time = MODE_REALTIME, i;

	if (driver->proc_active_mask == 0) {
		/* There are no DCI or Memory Device processes. Diag should
		 * be in Real Time mode.
		 */
		temp_real_time = MODE_REALTIME;
	} else if (!(driver->proc_rt_vote_mask & driver->proc_active_mask)) {
		/* No active process is voting for real time mode */
		temp_real_time = MODE_NONREALTIME;
	}

	if (temp_real_time != driver->real_time_mode) {
		for (i = 0; i < NUM_SMD_CONTROL_CHANNELS; i++)
			diag_send_diag_mode_update_by_smd(&driver->smd_cntl[i],
							temp_real_time);
	} else {
		pr_warn("diag: did not update real time mode, already in the req mode %d",
					temp_real_time);
	}
	if (driver->real_time_update_busy > 0)
		driver->real_time_update_busy--;
}
#endif

void diag_send_diag_mode_update_by_smd(struct diag_smd_info *smd_info,
							int real_time)
{
	struct diag_ctrl_msg_diagmode diagmode;
	char buf[sizeof(struct diag_ctrl_msg_diagmode)];
	int msg_size = sizeof(struct diag_ctrl_msg_diagmode);
	int wr_size = -ENOMEM, retry_count = 0, timer;
	struct diag_smd_info *data = NULL;

	if (!smd_info || smd_info->type != SMD_CNTL_TYPE) {
		pr_err("diag: In %s, invalid channel info, smd_info: %p type: %d\n",
					__func__, smd_info,
					((smd_info) ? smd_info->type : -1));
		return;
	}

	if (smd_info->peripheral < MODEM_DATA ||
					smd_info->peripheral > WCNSS_DATA) {
		pr_err("diag: In %s, invalid peripheral %d\n", __func__,
							smd_info->peripheral);
		return;
	}

	data = &driver->smd_data[smd_info->peripheral];
	if (!data)
		return;

	mutex_lock(&driver->diag_cntl_mutex);
	diagmode.ctrl_pkt_id = DIAG_CTRL_MSG_DIAGMODE;
	diagmode.ctrl_pkt_data_len = 36;
	diagmode.version = 1;
	diagmode.sleep_vote = real_time ? 1 : 0;
	/*
	 * 0 - Disables real-time logging (to prevent
	 *     frequent APPS wake-ups, etc.).
	 * 1 - Enable real-time logging
	 */
	diagmode.real_time = real_time;
	diagmode.use_nrt_values = 0;
	diagmode.commit_threshold = 0;
	diagmode.sleep_threshold = 0;
	diagmode.sleep_time = 0;
	diagmode.drain_timer_val = 0;
	diagmode.event_stale_timer_val = 0;

	memcpy(buf, &diagmode, msg_size);

	if (smd_info->ch) {
		while (retry_count < 3) {
			mutex_lock(&smd_info->smd_ch_mutex);
			wr_size = smd_write(smd_info->ch, buf, msg_size);
			mutex_unlock(&smd_info->smd_ch_mutex);
			if (wr_size == -ENOMEM) {
				/*
				 * The smd channel is full. Delay while
				 * smd processes existing data and smd
				 * has memory become available. The delay
				 * of 2000 was determined empirically as
				 * best value to use.
				 */
				retry_count++;
				for (timer = 0; timer < 5; timer++)
					udelay(2000);
			} else {
				data =
				&driver->smd_data[smd_info->peripheral];
				driver->real_time_mode = real_time;
				break;
			}
		}
		if (wr_size != msg_size)
			pr_err("diag: proc %d fail feature update %d, tried %d",
				smd_info->peripheral,
				wr_size, msg_size);
	} else {
		pr_err("diag: ch invalid, feature update on proc %d\n",
				smd_info->peripheral);
	}
	process_lock_enabling(&data->nrt_lock, real_time);

	mutex_unlock(&driver->diag_cntl_mutex);
}

int diag_send_stm_state(struct diag_smd_info *smd_info,
			  uint8_t stm_control_data)
{
	struct diag_ctrl_msg_stm stm_msg;
	int msg_size = sizeof(struct diag_ctrl_msg_stm);
	int retry_count = 0;
	int wr_size = 0;
	int success = 0;

	if (!smd_info || (smd_info->type != SMD_CNTL_TYPE) ||
		(driver->peripheral_supports_stm[smd_info->peripheral] ==
								DISABLE_STM)) {
		return -EINVAL;
	}

	if (smd_info->ch) {
		stm_msg.ctrl_pkt_id = 21;
		stm_msg.ctrl_pkt_data_len = 5;
		stm_msg.version = 1;
		stm_msg.control_data = stm_control_data;
		while (retry_count < 3) {
			mutex_lock(&smd_info->smd_ch_mutex);
			wr_size = smd_write(smd_info->ch, &stm_msg, msg_size);
			mutex_unlock(&smd_info->smd_ch_mutex);
			if (wr_size == -ENOMEM) {
				/*
				 * The smd channel is full. Delay while
				 * smd processes existing data and smd
				 * has memory become available. The delay
				 * of 10000 was determined empirically as
				 * best value to use.
				 */
				retry_count++;
				usleep_range(10000, 10000);
			} else {
				success = 1;
				break;
			}
		}
		if (wr_size != msg_size) {
			pr_err("diag: In %s, proc %d fail STM update %d, tried %d",
				__func__, smd_info->peripheral, wr_size,
				msg_size);
			success = 0;
		}
	} else {
		pr_err("diag: In %s, ch invalid, STM update on proc %d\n",
				__func__, smd_info->peripheral);
	}
	return success;
=======
#include "diagchar.h"
#include "diagfwd.h"
#include "diagfwd_cntl.h"

#define HDR_SIZ 8

void diag_smd_cntl_notify(void *ctxt, unsigned event)
{
	int r1, r2;

	if (!(driver->ch_cntl))
		return;

	switch (event) {
	case SMD_EVENT_DATA:
		r1 = smd_read_avail(driver->ch_cntl);
		r2 = smd_cur_packet_size(driver->ch_cntl);
		if (r1 > 0 && r1 == r2)
			queue_work(driver->diag_wq,
				 &(driver->diag_read_smd_cntl_work));
		else
			pr_debug("diag: incomplete pkt on Modem CNTL ch\n");
		break;
	case SMD_EVENT_OPEN:
		queue_work(driver->diag_cntl_wq,
			 &(driver->diag_modem_mask_update_work));
		break;
	}
}

void diag_smd_qdsp_cntl_notify(void *ctxt, unsigned event)
{
	int r1, r2;

	if (!(driver->chqdsp_cntl))
		return;

	switch (event) {
	case SMD_EVENT_DATA:
		r1 = smd_read_avail(driver->chqdsp_cntl);
		r2 = smd_cur_packet_size(driver->chqdsp_cntl);
		if (r1 > 0 && r1 == r2)
			queue_work(driver->diag_wq,
				 &(driver->diag_read_smd_qdsp_cntl_work));
		else
			pr_debug("diag: incomplete pkt on LPASS CNTL ch\n");
		break;
	case SMD_EVENT_OPEN:
		queue_work(driver->diag_cntl_wq,
			 &(driver->diag_qdsp_mask_update_work));
		break;
	}
}

void diag_smd_wcnss_cntl_notify(void *ctxt, unsigned event)
{
	int r1, r2;

	if (!(driver->ch_wcnss_cntl))
		return;

	switch (event) {
	case SMD_EVENT_DATA:
		r1 = smd_read_avail(driver->ch_wcnss_cntl);
		r2 = smd_cur_packet_size(driver->ch_wcnss_cntl);
		if (r1 > 0 && r1 == r2)
			queue_work(driver->diag_wq,
				 &(driver->diag_read_smd_wcnss_cntl_work));
		else
			pr_debug("diag: incomplete pkt on WCNSS CNTL ch\n");
		break;
	case SMD_EVENT_OPEN:
		queue_work(driver->diag_cntl_wq,
			 &(driver->diag_wcnss_mask_update_work));
		break;
	}
}

static void diag_smd_cntl_send_req(int proc_num)
{
	int data_len = 0, type = -1, count_bytes = 0, j, r, flag = 0;
	struct bindpkt_params_per_process *pkt_params =
		 kzalloc(sizeof(struct bindpkt_params_per_process), GFP_KERNEL);
	struct diag_ctrl_msg *msg;
	struct cmd_code_range *range;
	struct bindpkt_params *temp;
	void *buf = NULL;
	smd_channel_t *smd_ch = NULL;

	if (pkt_params == NULL) {
		pr_alert("diag: Memory allocation failure\n");
		return;
	}

	if (proc_num == MODEM_PROC) {
		buf = driver->buf_in_cntl;
		smd_ch = driver->ch_cntl;
	} else if (proc_num == QDSP_PROC) {
		buf = driver->buf_in_qdsp_cntl;
		smd_ch = driver->chqdsp_cntl;
	} else if (proc_num == WCNSS_PROC) {
		buf = driver->buf_in_wcnss_cntl;
		smd_ch = driver->ch_wcnss_cntl;
	}

	if (!smd_ch || !buf) {
		kfree(pkt_params);
		return;
	}

	r = smd_read_avail(smd_ch);
	if (r > IN_BUF_SIZE) {
		if (r < MAX_IN_BUF_SIZE) {
			pr_err("diag: SMD CNTL sending pkt upto %d bytes", r);
			buf = krealloc(buf, r, GFP_KERNEL);
		} else {
			pr_err("diag: CNTL pkt > %d bytes", MAX_IN_BUF_SIZE);
			kfree(pkt_params);
			return;
		}
	}
	if (buf && r > 0) {
		smd_read(smd_ch, buf, r);
		while (count_bytes + HDR_SIZ <= r) {
			type = *(uint32_t *)(buf);
			data_len = *(uint32_t *)(buf + 4);
			if (type < DIAG_CTRL_MSG_REG ||
					 type > DIAG_CTRL_MSG_F3_MASK_V2) {
				pr_alert("diag: Invalid Msg type %d proc %d",
					 type, proc_num);
				break;
			}
			if (data_len < 0 || data_len > r) {
				pr_alert("diag: Invalid data len %d proc %d",
					 data_len, proc_num);
				break;
			}
			count_bytes = count_bytes+HDR_SIZ+data_len;
			if (type == DIAG_CTRL_MSG_REG && r >= count_bytes) {
				msg = buf+HDR_SIZ;
				range = buf+HDR_SIZ+
						sizeof(struct diag_ctrl_msg);
				pkt_params->count = msg->count_entries;
				temp = kzalloc(pkt_params->count * sizeof(struct
						 bindpkt_params), GFP_KERNEL);
				if (temp == NULL) {
					pr_alert("diag: Memory alloc fail\n");
					kfree(pkt_params);
					return;
				}
				for (j = 0; j < pkt_params->count; j++) {
					temp->cmd_code = msg->cmd_code;
					temp->subsys_id = msg->subsysid;
					temp->client_id = proc_num;
					temp->proc_id = proc_num;
					temp->cmd_code_lo = range->cmd_code_lo;
					temp->cmd_code_hi = range->cmd_code_hi;
					range++;
					temp++;
				}
				temp -= pkt_params->count;
				pkt_params->params = temp;
				flag = 1;
				diagchar_ioctl(NULL, DIAG_IOCTL_COMMAND_REG,
						 (unsigned long)pkt_params);
				kfree(temp);
			}
			buf = buf + HDR_SIZ + data_len;
		}
	}
	kfree(pkt_params);
	if (flag) {
		/* Poll SMD CNTL channels to check for data */
		if (proc_num == MODEM_PROC)
			diag_smd_cntl_notify(NULL, SMD_EVENT_DATA);
		else if (proc_num == QDSP_PROC)
			diag_smd_qdsp_cntl_notify(NULL, SMD_EVENT_DATA);
		else if (proc_num == WCNSS_PROC)
			diag_smd_wcnss_cntl_notify(NULL, SMD_EVENT_DATA);
	}
}

void diag_read_smd_cntl_work_fn(struct work_struct *work)
{
	diag_smd_cntl_send_req(MODEM_PROC);
}

void diag_read_smd_qdsp_cntl_work_fn(struct work_struct *work)
{
	diag_smd_cntl_send_req(QDSP_PROC);
}

void diag_read_smd_wcnss_cntl_work_fn(struct work_struct *work)
{
	diag_smd_cntl_send_req(WCNSS_PROC);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
}

static int diag_smd_cntl_probe(struct platform_device *pdev)
{
	int r = 0;
<<<<<<< HEAD
	int index = -1;
	const char *channel_name = NULL;

	/* open control ports only on 8960 & newer targets */
	if (chk_apps_only()) {
		if (pdev->id == SMD_APPS_MODEM) {
			index = MODEM_DATA;
			channel_name = "DIAG_CNTL";
		}
#if defined(CONFIG_MSM_N_WAY_SMD)
		else if (pdev->id == SMD_APPS_QDSP) {
			index = LPASS_DATA;
			channel_name = "DIAG_CNTL";
		}
#endif
		else if (pdev->id == SMD_APPS_WCNSS) {
			index = WCNSS_DATA;
			channel_name = "APPS_RIVA_CTRL";
		}

		if (index != -1) {
			r = smd_named_open_on_edge(channel_name,
				pdev->id,
				&driver->smd_cntl[index].ch,
				&driver->smd_cntl[index],
				diag_smd_notify);
			driver->smd_cntl[index].ch_save =
				driver->smd_cntl[index].ch;
		}
		pr_debug("diag: In %s, open SMD CNTL port, Id = %d, r = %d\n",
			__func__, pdev->id, r);
	}

=======

	/* open control ports only on 8960 & newer targets */
	if (chk_apps_only()) {
		if (pdev->id == SMD_APPS_MODEM)
			r = smd_open("DIAG_CNTL", &driver->ch_cntl, driver,
							diag_smd_cntl_notify);
		if (pdev->id == SMD_APPS_QDSP)
			r = smd_named_open_on_edge("DIAG_CNTL", SMD_APPS_QDSP
				, &driver->chqdsp_cntl, driver,
					 diag_smd_qdsp_cntl_notify);
		if (pdev->id == SMD_APPS_WCNSS)
			r = smd_named_open_on_edge("APPS_RIVA_CTRL",
				SMD_APPS_WCNSS, &driver->ch_wcnss_cntl,
					driver, diag_smd_wcnss_cntl_notify);
		pr_debug("diag: open CNTL port, ID = %d,r = %d\n", pdev->id, r);
	}
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	return 0;
}

static int diagfwd_cntl_runtime_suspend(struct device *dev)
{
	dev_dbg(dev, "pm_runtime: suspending...\n");
	return 0;
}

static int diagfwd_cntl_runtime_resume(struct device *dev)
{
	dev_dbg(dev, "pm_runtime: resuming...\n");
	return 0;
}

static const struct dev_pm_ops diagfwd_cntl_dev_pm_ops = {
	.runtime_suspend = diagfwd_cntl_runtime_suspend,
	.runtime_resume = diagfwd_cntl_runtime_resume,
};

static struct platform_driver msm_smd_ch1_cntl_driver = {

	.probe = diag_smd_cntl_probe,
	.driver = {
<<<<<<< HEAD
		.name = "DIAG_CNTL",
		.owner = THIS_MODULE,
		.pm   = &diagfwd_cntl_dev_pm_ops,
	},
=======
			.name = "DIAG_CNTL",
			.owner = THIS_MODULE,
			.pm   = &diagfwd_cntl_dev_pm_ops,
		   },
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
};

static struct platform_driver diag_smd_lite_cntl_driver = {

	.probe = diag_smd_cntl_probe,
	.driver = {
<<<<<<< HEAD
		.name = "APPS_RIVA_CTRL",
		.owner = THIS_MODULE,
		.pm   = &diagfwd_cntl_dev_pm_ops,
	},
=======
			.name = "APPS_RIVA_CTRL",
			.owner = THIS_MODULE,
			.pm   = &diagfwd_cntl_dev_pm_ops,
		   },
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
};

void diagfwd_cntl_init(void)
{
<<<<<<< HEAD
	int success;
	int i;

	reg_dirty = 0;
	driver->polling_reg_flag = 0;
	driver->log_on_demand_support = 1;
	driver->diag_cntl_wq = create_singlethread_workqueue("diag_cntl_wq");

	for (i = 0; i < NUM_SMD_CONTROL_CHANNELS; i++) {
		success = diag_smd_constructor(&driver->smd_cntl[i], i,
							SMD_CNTL_TYPE);
		if (!success)
			goto err;
	}

=======
	driver->polling_reg_flag = 0;
	driver->diag_cntl_wq = create_singlethread_workqueue("diag_cntl_wq");
	if (driver->buf_in_cntl == NULL) {
		driver->buf_in_cntl = kzalloc(IN_BUF_SIZE, GFP_KERNEL);
		if (driver->buf_in_cntl == NULL)
			goto err;
	}
	if (driver->buf_in_qdsp_cntl == NULL) {
		driver->buf_in_qdsp_cntl = kzalloc(IN_BUF_SIZE, GFP_KERNEL);
		if (driver->buf_in_qdsp_cntl == NULL)
			goto err;
	}
	if (driver->buf_in_wcnss_cntl == NULL) {
		driver->buf_in_wcnss_cntl = kzalloc(IN_BUF_SIZE, GFP_KERNEL);
		if (driver->buf_in_wcnss_cntl == NULL)
			goto err;
	}
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	platform_driver_register(&msm_smd_ch1_cntl_driver);
	platform_driver_register(&diag_smd_lite_cntl_driver);

	return;
err:
<<<<<<< HEAD
	pr_err("diag: Could not initialize diag buffers");

	for (i = 0; i < NUM_SMD_CONTROL_CHANNELS; i++)
		diag_smd_destructor(&driver->smd_cntl[i]);

	if (driver->diag_cntl_wq)
		destroy_workqueue(driver->diag_cntl_wq);
=======
		pr_err("diag: Could not initialize diag buffers");
		kfree(driver->buf_in_cntl);
		kfree(driver->buf_in_qdsp_cntl);
		kfree(driver->buf_in_wcnss_cntl);
		if (driver->diag_cntl_wq)
			destroy_workqueue(driver->diag_cntl_wq);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
}

void diagfwd_cntl_exit(void)
{
<<<<<<< HEAD
	int i;

	for (i = 0; i < NUM_SMD_CONTROL_CHANNELS; i++)
		diag_smd_destructor(&driver->smd_cntl[i]);

	destroy_workqueue(driver->diag_cntl_wq);
	destroy_workqueue(driver->diag_real_time_wq);

	platform_driver_unregister(&msm_smd_ch1_cntl_driver);
	platform_driver_unregister(&diag_smd_lite_cntl_driver);
=======
	smd_close(driver->ch_cntl);
	smd_close(driver->chqdsp_cntl);
	smd_close(driver->ch_wcnss_cntl);
	driver->ch_cntl = 0;
	driver->chqdsp_cntl = 0;
	driver->ch_wcnss_cntl = 0;
	destroy_workqueue(driver->diag_cntl_wq);
	platform_driver_unregister(&msm_smd_ch1_cntl_driver);
	platform_driver_unregister(&diag_smd_lite_cntl_driver);

	kfree(driver->buf_in_cntl);
	kfree(driver->buf_in_qdsp_cntl);
	kfree(driver->buf_in_wcnss_cntl);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
}
