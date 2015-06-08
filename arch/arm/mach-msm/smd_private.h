/* arch/arm/mach-msm/smd_private.h
 *
 * Copyright (C) 2007 Google, Inc.
<<<<<<< HEAD
 * Copyright (c) 2007-2013, The Linux Foundation. All rights reserved.
=======
<<<<<<< HEAD
 * Copyright (c) 2007-2013, The Linux Foundation. All rights reserved.
=======
 * Copyright (c) 2007 QUALCOMM Incorporated
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
#ifndef _ARCH_ARM_MACH_MSM_MSM_SMD_PRIVATE_H_
#define _ARCH_ARM_MACH_MSM_MSM_SMD_PRIVATE_H_

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <linux/types.h>
#include <linux/spinlock.h>
#include <linux/errno.h>
#include <linux/remote_spinlock.h>
#include <linux/platform_device.h>
#include <linux/interrupt.h>
#include <mach/msm_smsm.h>
#include <mach/msm_smd.h>
<<<<<<< HEAD
=======
=======
#include <linux/platform_device.h>
#include <linux/spinlock.h>
#include <linux/list.h>
#include <linux/io.h>

#include <mach/msm_iomap.h>

struct smem_heap_info {
	unsigned initialized;
	unsigned free_offset;
	unsigned heap_remaining;
	unsigned reserved;
};

struct smem_heap_entry {
	unsigned allocated;
	unsigned offset;
	unsigned size;
	unsigned reserved;
};

struct smem_proc_comm {
	unsigned command;
	unsigned status;
	unsigned data1;
	unsigned data2;
};
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#define PC_APPS  0
#define PC_MODEM 1

<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
#define VERSION_SMD       0
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#define VERSION_QDSP6     4
#define VERSION_APPS_SBL  6
#define VERSION_MODEM_SBL 7
#define VERSION_APPS      8
#define VERSION_MODEM     9
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#define VERSION_DSPS      10

#if defined(CONFIG_MSM_SMD_PKG4)
struct smsm_interrupt_info {
	uint32_t aArm_en_mask;
	uint32_t aArm_interrupts_pending;
	uint32_t aArm_wakeup_reason;
	uint32_t aArm_rpc_prog;
	uint32_t aArm_rpc_proc;
	char aArm_smd_port_name[20];
	uint32_t aArm_gpio_info;
};
#elif defined(CONFIG_MSM_SMD_PKG3)
struct smsm_interrupt_info {
  uint32_t aArm_en_mask;
  uint32_t aArm_interrupts_pending;
  uint32_t aArm_wakeup_reason;
};
#elif !defined(CONFIG_MSM_SMD)
/* Don't trigger the error */
#else
#error No SMD Package Specified; aborting
<<<<<<< HEAD
=======
=======

struct smem_shared {
	struct smem_proc_comm proc_comm[4];
	unsigned version[32];
	struct smem_heap_info heap_info;
	struct smem_heap_entry heap_toc[512];
};

#define SMSM_V1_SIZE		(sizeof(unsigned) * 8)
#define SMSM_V2_SIZE		(sizeof(unsigned) * 4)

#ifdef CONFIG_MSM_SMD_PKG3
struct smsm_interrupt_info {
	uint32_t interrupt_mask;
	uint32_t pending_interrupts;
	uint32_t wakeup_reason;
};
#else
#define DEM_MAX_PORT_NAME_LEN (20)
struct msm_dem_slave_data {
	uint32_t sleep_time;
	uint32_t interrupt_mask;
	uint32_t resources_used;
	uint32_t reserved1;

	uint32_t wakeup_reason;
	uint32_t pending_interrupts;
	uint32_t rpc_prog;
	uint32_t rpc_proc;
	char     smd_port_name[DEM_MAX_PORT_NAME_LEN];
	uint32_t reserved2;
};
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#endif

#define SZ_DIAG_ERR_MSG 0xC8
#define ID_DIAG_ERR_MSG SMEM_DIAG_ERR_MESSAGE
#define ID_SMD_CHANNELS SMEM_SMD_BASE_ID
#define ID_SHARED_STATE SMEM_SMSM_SHARED_STATE
#define ID_CH_ALLOC_TBL SMEM_CHANNEL_ALLOC_TBL

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#define SMD_SS_CLOSED            0x00000000
#define SMD_SS_OPENING           0x00000001
#define SMD_SS_OPENED            0x00000002
#define SMD_SS_FLUSHING          0x00000003
#define SMD_SS_CLOSING           0x00000004
#define SMD_SS_RESET             0x00000005
#define SMD_SS_RESET_OPENING     0x00000006

#define SMD_BUF_SIZE             8192
#define SMD_CHANNELS             64
#define SMD_HEADER_SIZE          20

/* 'type' field of smd_alloc_elm structure
 * has the following breakup
 * bits 0-7   -> channel type
 * bits 8-11  -> xfer type
 * bits 12-31 -> reserved
 */
struct smd_alloc_elm {
	char name[20];
	uint32_t cid;
	uint32_t type;
	uint32_t ref_count;
};

#define SMD_CHANNEL_TYPE(x) ((x) & 0x000000FF)
#define SMD_XFER_TYPE(x)    (((x) & 0x00000F00) >> 8)

<<<<<<< HEAD
=======
=======
#define SMSM_INIT		0x00000001
#define SMSM_SMDINIT		0x00000008
#define SMSM_RPCINIT		0x00000020
#define SMSM_RESET		0x00000040
#define SMSM_RSA		0x00000080
#define SMSM_RUN		0x00000100
#define SMSM_PWRC		0x00000200
#define SMSM_TIMEWAIT		0x00000400
#define SMSM_TIMEINIT		0x00000800
#define SMSM_PWRC_EARLY_EXIT	0x00001000
#define SMSM_WFPI		0x00002000
#define SMSM_SLEEP		0x00004000
#define SMSM_SLEEPEXIT		0x00008000
#define SMSM_APPS_REBOOT	0x00020000
#define SMSM_SYSTEM_POWER_DOWN	0x00040000
#define SMSM_SYSTEM_REBOOT	0x00080000
#define SMSM_SYSTEM_DOWNLOAD	0x00100000
#define SMSM_PWRC_SUSPEND	0x00200000
#define SMSM_APPS_SHUTDOWN	0x00400000
#define SMSM_SMD_LOOPBACK	0x00800000
#define SMSM_RUN_QUIET		0x01000000
#define SMSM_MODEM_WAIT		0x02000000
#define SMSM_MODEM_BREAK	0x04000000
#define SMSM_MODEM_CONTINUE	0x08000000
#define SMSM_UNKNOWN		0x80000000

#define SMSM_WKUP_REASON_RPC	0x00000001
#define SMSM_WKUP_REASON_INT	0x00000002
#define SMSM_WKUP_REASON_GPIO	0x00000004
#define SMSM_WKUP_REASON_TIMER	0x00000008
#define SMSM_WKUP_REASON_ALARM	0x00000010
#define SMSM_WKUP_REASON_RESET	0x00000020

#ifdef CONFIG_ARCH_MSM7X00A
enum smsm_state_item {
	SMSM_STATE_APPS = 1,
	SMSM_STATE_MODEM = 3,
	SMSM_STATE_COUNT,
};
#else
enum smsm_state_item {
	SMSM_STATE_APPS,
	SMSM_STATE_MODEM,
	SMSM_STATE_HEXAGON,
	SMSM_STATE_APPS_DEM,
	SMSM_STATE_MODEM_DEM,
	SMSM_STATE_QDSP6_DEM,
	SMSM_STATE_POWER_MASTER_DEM,
	SMSM_STATE_TIME_MASTER_DEM,
	SMSM_STATE_COUNT,
};
#endif

void *smem_alloc(unsigned id, unsigned size);
int smsm_change_state(enum smsm_state_item item, uint32_t clear_mask, uint32_t set_mask);
uint32_t smsm_get_state(enum smsm_state_item item);
int smsm_set_sleep_duration(uint32_t delay);
void smsm_print_sleep_info(void);

#define SMEM_NUM_SMD_CHANNELS        64

typedef enum {
	/* fixed items */
	SMEM_PROC_COMM = 0,
	SMEM_HEAP_INFO,
	SMEM_ALLOCATION_TABLE,
	SMEM_VERSION_INFO,
	SMEM_HW_RESET_DETECT,
	SMEM_AARM_WARM_BOOT,
	SMEM_DIAG_ERR_MESSAGE,
	SMEM_SPINLOCK_ARRAY,
	SMEM_MEMORY_BARRIER_LOCATION,

	/* dynamic items */
	SMEM_AARM_PARTITION_TABLE,
	SMEM_AARM_BAD_BLOCK_TABLE,
	SMEM_RESERVE_BAD_BLOCKS,
	SMEM_WM_UUID,
	SMEM_CHANNEL_ALLOC_TBL,
	SMEM_SMD_BASE_ID,
	SMEM_SMEM_LOG_IDX = SMEM_SMD_BASE_ID + SMEM_NUM_SMD_CHANNELS,
	SMEM_SMEM_LOG_EVENTS,
	SMEM_SMEM_STATIC_LOG_IDX,
	SMEM_SMEM_STATIC_LOG_EVENTS,
	SMEM_SMEM_SLOW_CLOCK_SYNC,
	SMEM_SMEM_SLOW_CLOCK_VALUE,
	SMEM_BIO_LED_BUF,
	SMEM_SMSM_SHARED_STATE,
	SMEM_SMSM_INT_INFO,
	SMEM_SMSM_SLEEP_DELAY,
	SMEM_SMSM_LIMIT_SLEEP,
	SMEM_SLEEP_POWER_COLLAPSE_DISABLED,
	SMEM_KEYPAD_KEYS_PRESSED,
	SMEM_KEYPAD_STATE_UPDATED,
	SMEM_KEYPAD_STATE_IDX,
	SMEM_GPIO_INT,
	SMEM_MDDI_LCD_IDX,
	SMEM_MDDI_HOST_DRIVER_STATE,
	SMEM_MDDI_LCD_DISP_STATE,
	SMEM_LCD_CUR_PANEL,
	SMEM_MARM_BOOT_SEGMENT_INFO,
	SMEM_AARM_BOOT_SEGMENT_INFO,
	SMEM_SLEEP_STATIC,
	SMEM_SCORPION_FREQUENCY,
	SMEM_SMD_PROFILES,
	SMEM_TSSC_BUSY,
	SMEM_HS_SUSPEND_FILTER_INFO,
	SMEM_BATT_INFO,
	SMEM_APPS_BOOT_MODE,
	SMEM_VERSION_FIRST,
	SMEM_VERSION_LAST = SMEM_VERSION_FIRST + 24,
	SMEM_OSS_RRCASN1_BUF1,
	SMEM_OSS_RRCASN1_BUF2,
	SMEM_ID_VENDOR0,
	SMEM_ID_VENDOR1,
	SMEM_ID_VENDOR2,
	SMEM_HW_SW_BUILD_ID,
	SMEM_SMD_BLOCK_PORT_BASE_ID,
	SMEM_SMD_BLOCK_PORT_PROC0_HEAP = SMEM_SMD_BLOCK_PORT_BASE_ID + SMEM_NUM_SMD_CHANNELS,
	SMEM_SMD_BLOCK_PORT_PROC1_HEAP = SMEM_SMD_BLOCK_PORT_PROC0_HEAP + SMEM_NUM_SMD_CHANNELS,
	SMEM_I2C_MUTEX = SMEM_SMD_BLOCK_PORT_PROC1_HEAP + SMEM_NUM_SMD_CHANNELS,
	SMEM_SCLK_CONVERSION,
	SMEM_SMD_SMSM_INTR_MUX,
	SMEM_SMSM_CPU_INTR_MASK,
	SMEM_APPS_DEM_SLAVE_DATA,
	SMEM_QDSP6_DEM_SLAVE_DATA,
	SMEM_CLKREGIM_BSP,
	SMEM_CLKREGIM_SOURCES,
	SMEM_SMD_FIFO_BASE_ID,
	SMEM_USABLE_RAM_PARTITION_TABLE = SMEM_SMD_FIFO_BASE_ID + SMEM_NUM_SMD_CHANNELS,
	SMEM_POWER_ON_STATUS_INFO,
	SMEM_DAL_AREA,
	SMEM_SMEM_LOG_POWER_IDX,
	SMEM_SMEM_LOG_POWER_WRAP,
	SMEM_SMEM_LOG_POWER_EVENTS,
	SMEM_ERR_CRASH_LOG,
	SMEM_ERR_F3_TRACE_LOG,
	SMEM_NUM_ITEMS,
} smem_mem_type;


#define SMD_SS_CLOSED		0x00000000
#define SMD_SS_OPENING		0x00000001
#define SMD_SS_OPENED		0x00000002
#define SMD_SS_FLUSHING		0x00000003
#define SMD_SS_CLOSING		0x00000004
#define SMD_SS_RESET		0x00000005
#define SMD_SS_RESET_OPENING	0x00000006

#define SMD_BUF_SIZE		8192
#define SMD_CHANNELS		64

#define SMD_HEADER_SIZE		20

struct smd_alloc_elm {
	char name[20];
	uint32_t cid;
	uint32_t ctype;
	uint32_t ref_count;
};

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
struct smd_half_channel {
	unsigned state;
	unsigned char fDSR;
	unsigned char fCTS;
	unsigned char fCD;
	unsigned char fRI;
	unsigned char fHEAD;
	unsigned char fTAIL;
	unsigned char fSTATE;
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	unsigned char fBLOCKREADINTR;
	unsigned tail;
	unsigned head;
};

struct smd_half_channel_word_access {
	unsigned state;
	unsigned fDSR;
	unsigned fCTS;
	unsigned fCD;
	unsigned fRI;
	unsigned fHEAD;
	unsigned fTAIL;
	unsigned fSTATE;
	unsigned fBLOCKREADINTR;
	unsigned tail;
	unsigned head;
};

struct smd_half_channel_access {
	void (*set_state)(volatile void __iomem *half_channel, unsigned data);
	unsigned (*get_state)(volatile void __iomem *half_channel);
	void (*set_fDSR)(volatile void __iomem *half_channel,
					unsigned char data);
	unsigned (*get_fDSR)(volatile void __iomem *half_channel);
	void (*set_fCTS)(volatile void __iomem *half_channel,
					unsigned char data);
	unsigned (*get_fCTS)(volatile void __iomem *half_channel);
	void (*set_fCD)(volatile void __iomem *half_channel,
					unsigned char data);
	unsigned (*get_fCD)(volatile void __iomem *half_channel);
	void (*set_fRI)(volatile void __iomem *half_channel,
					unsigned char data);
	unsigned (*get_fRI)(volatile void __iomem *half_channel);
	void (*set_fHEAD)(volatile void __iomem *half_channel,
					unsigned char data);
	unsigned (*get_fHEAD)(volatile void __iomem *half_channel);
	void (*set_fTAIL)(volatile void __iomem *half_channel,
					unsigned char data);
	unsigned (*get_fTAIL)(volatile void __iomem *half_channel);
	void (*set_fSTATE)(volatile void __iomem *half_channel,
					unsigned char data);
	unsigned (*get_fSTATE)(volatile void __iomem *half_channel);
	void (*set_fBLOCKREADINTR)(volatile void __iomem *half_channel,
					unsigned char data);
	unsigned (*get_fBLOCKREADINTR)(volatile void __iomem *half_channel);
	void (*set_tail)(volatile void __iomem *half_channel, unsigned data);
	unsigned (*get_tail)(volatile void __iomem *half_channel);
	void (*set_head)(volatile void __iomem *half_channel, unsigned data);
	unsigned (*get_head)(volatile void __iomem *half_channel);
};

int is_word_access_ch(unsigned ch_type);

struct smd_half_channel_access *get_half_ch_funcs(unsigned ch_type);

struct smd_channel {
	volatile void __iomem *send; /* some variant of smd_half_channel */
	volatile void __iomem *recv; /* some variant of smd_half_channel */
	unsigned char *send_data;
	unsigned char *recv_data;
	unsigned fifo_size;
	unsigned fifo_mask;
	struct list_head ch_list;

	unsigned current_packet;
	unsigned n;
	void *priv;
	void (*notify)(void *priv, unsigned flags);

	int (*read)(smd_channel_t *ch, void *data, int len, int user_buf);
	int (*write)(smd_channel_t *ch, const void *data, int len,
			int user_buf);
	int (*read_avail)(smd_channel_t *ch);
	int (*write_avail)(smd_channel_t *ch);
	int (*read_from_cb)(smd_channel_t *ch, void *data, int len,
			int user_buf);

	void (*update_state)(smd_channel_t *ch);
	unsigned last_state;
	void (*notify_other_cpu)(smd_channel_t *ch);

	char name[20];
	struct platform_device pdev;
	unsigned type;

	int pending_pkt_sz;

	char is_pkt_ch;

	/*
	 * private internal functions to access *send and *recv.
	 * never to be exported outside of smd
	 */
	struct smd_half_channel_access *half_ch;
};

extern spinlock_t smem_lock;


void smd_diag(void);

struct interrupt_stat {
	uint32_t smd_in_count;
	uint32_t smd_out_hardcode_count;
	uint32_t smd_out_config_count;
	uint32_t smd_interrupt_id;

	uint32_t smsm_in_count;
	uint32_t smsm_out_hardcode_count;
	uint32_t smsm_out_config_count;
	uint32_t smsm_interrupt_id;
};
extern struct interrupt_stat interrupt_stats[NUM_SMD_SUBSYSTEMS];

struct interrupt_config_item {
	/* must be initialized */
	irqreturn_t (*irq_handler)(int req, void *data);
	/* outgoing interrupt config (set from platform data) */
	uint32_t out_bit_pos;
	void __iomem *out_base;
	uint32_t out_offset;
	int irq_id;
};

enum {
	MSM_SMD_DEBUG = 1U << 0,
	MSM_SMSM_DEBUG = 1U << 1,
	MSM_SMD_INFO = 1U << 2,
	MSM_SMSM_INFO = 1U << 3,
	MSM_SMD_POWER_INFO = 1U << 4,
	MSM_SMSM_POWER_INFO = 1U << 5,
};

struct interrupt_config {
	struct interrupt_config_item smd;
	struct interrupt_config_item smsm;
};

struct edge_to_pid {
	uint32_t	local_pid;
	uint32_t	remote_pid;
	char		subsys_name[SMD_MAX_CH_NAME_LEN];
	bool		initialized;
};

extern void *smd_log_ctx;
extern int msm_smd_debug_mask;
extern int disable_smsm_reset_handshake;
extern bool smem_initialized_check(void);

extern irqreturn_t smd_modem_irq_handler(int irq, void *data);
extern irqreturn_t smsm_modem_irq_handler(int irq, void *data);
extern irqreturn_t smd_dsp_irq_handler(int irq, void *data);
extern irqreturn_t smsm_dsp_irq_handler(int irq, void *data);
extern irqreturn_t smd_dsps_irq_handler(int irq, void *data);
extern irqreturn_t smsm_dsps_irq_handler(int irq, void *data);
extern irqreturn_t smd_wcnss_irq_handler(int irq, void *data);
extern irqreturn_t smsm_wcnss_irq_handler(int irq, void *data);
extern irqreturn_t smd_rpm_irq_handler(int irq, void *data);

extern int msm_smd_driver_register(void);
extern void smd_post_init(bool is_legacy, unsigned remote_pid);
extern int smsm_post_init(void);

extern struct interrupt_config *smd_get_intr_config(uint32_t edge);
extern int smd_edge_to_remote_pid(uint32_t edge);
extern void smd_set_edge_subsys_name(uint32_t edge, const char *subsys_name);
extern void smd_set_edge_initialized(uint32_t edge);
extern void smd_cfg_smd_intr(uint32_t proc, uint32_t mask, void *ptr);
extern void smd_cfg_smsm_intr(uint32_t proc, uint32_t mask, void *ptr);
<<<<<<< HEAD
=======
=======
	unsigned char fUNUSED;
	unsigned tail;
	unsigned head;
} __attribute__(( aligned(4), packed ));

/* Only used on SMD package v3 on msm7201a */
struct smd_shared_v1 {
	struct smd_half_channel ch0;
	unsigned char data0[SMD_BUF_SIZE];
	struct smd_half_channel ch1;
	unsigned char data1[SMD_BUF_SIZE];
};

/* Used on SMD package v4 */
struct smd_shared_v2 {
	struct smd_half_channel ch0;
	struct smd_half_channel ch1;
};

struct smd_channel {
	volatile struct smd_half_channel *send;
	volatile struct smd_half_channel *recv;
	unsigned char *send_data;
	unsigned char *recv_data;

	unsigned fifo_mask;
	unsigned fifo_size;
	unsigned current_packet;
	unsigned n;

	struct list_head ch_list;

	void *priv;
	void (*notify)(void *priv, unsigned flags);

	int (*read)(struct smd_channel *ch, void *data, int len);
	int (*write)(struct smd_channel *ch, const void *data, int len);
	int (*read_avail)(struct smd_channel *ch);
	int (*write_avail)(struct smd_channel *ch);

	void (*update_state)(struct smd_channel *ch);
	unsigned last_state;
	void (*notify_other_cpu)(void);
	unsigned type;

	char name[32];
	struct platform_device pdev;
};

#define SMD_TYPE_MASK		0x0FF
#define SMD_TYPE_APPS_MODEM	0x000
#define SMD_TYPE_APPS_DSP	0x001
#define SMD_TYPE_MODEM_DSP	0x002

#define SMD_KIND_MASK		0xF00
#define SMD_KIND_UNKNOWN	0x000
#define SMD_KIND_STREAM		0x100
#define SMD_KIND_PACKET		0x200

extern struct list_head smd_ch_closed_list;
extern struct list_head smd_ch_list_modem;
extern struct list_head smd_ch_list_dsp;

extern spinlock_t smd_lock;
extern spinlock_t smem_lock;

void *smem_find(unsigned id, unsigned size);
void *smem_item(unsigned id, unsigned *size);
uint32_t raw_smsm_get_state(enum smsm_state_item item);

extern void msm_init_last_radio_log(struct module *);

#ifdef CONFIG_MSM_SMD_PKG3
/*
 * This allocator assumes an SMD Package v3 which only exists on
 * MSM7x00 SoC's.
 */
static inline int _smd_alloc_channel(struct smd_channel *ch)
{
	struct smd_shared_v1 *shared1;

	shared1 = smem_alloc(ID_SMD_CHANNELS + ch->n, sizeof(*shared1));
	if (!shared1) {
		pr_err("smd_alloc_channel() cid %d does not exist\n", ch->n);
		return -1;
	}
	ch->send = &shared1->ch0;
	ch->recv = &shared1->ch1;
	ch->send_data = shared1->data0;
	ch->recv_data = shared1->data1;
	ch->fifo_size = SMD_BUF_SIZE;
	return 0;
}
#else
/*
 * This allocator assumes an SMD Package v4, the most common
 * and the default.
 */
static inline int _smd_alloc_channel(struct smd_channel *ch)
{
	struct smd_shared_v2 *shared2;
	void *buffer;
	unsigned buffer_sz;

	shared2 = smem_alloc(SMEM_SMD_BASE_ID + ch->n, sizeof(*shared2));
	buffer = smem_item(SMEM_SMD_FIFO_BASE_ID + ch->n, &buffer_sz);

	if (!buffer)
		return -1;

	/* buffer must be a power-of-two size */
	if (buffer_sz & (buffer_sz - 1))
		return -1;

	buffer_sz /= 2;
	ch->send = &shared2->ch0;
	ch->recv = &shared2->ch1;
	ch->send_data = buffer;
	ch->recv_data = buffer + buffer_sz;
	ch->fifo_size = buffer_sz;
	return 0;
}
#endif /* CONFIG_MSM_SMD_PKG3 */

#if defined(CONFIG_ARCH_MSM7X30)
static inline void msm_a2m_int(uint32_t irq)
{
	writel(1 << irq, MSM_GCC_BASE + 0x8);
}
#else
static inline void msm_a2m_int(uint32_t irq)
{
	writel(1, MSM_CSR_BASE + 0x400 + (irq * 4));
}
#endif /* CONFIG_ARCH_MSM7X30 */


>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#endif
