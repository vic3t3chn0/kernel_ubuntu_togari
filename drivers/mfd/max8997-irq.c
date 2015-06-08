/*
<<<<<<< HEAD
<<<<<<< HEAD
 * max8997-irq.c - Interrupt controller support for MAX8997
 *
 * Copyright (C) 2011 Samsung Electronics Co.Ltd
 * MyungJoo Ham <myungjoo.ham@samsung.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * This driver is based on max8998-irq.c
 */

#include <linux/err.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <linux/mfd/max8997.h>
#include <linux/mfd/max8997-private.h>

static const u8 max8997_mask_reg[] = {
	[PMIC_INT1] = MAX8997_REG_INT1MSK,
	[PMIC_INT2] = MAX8997_REG_INT2MSK,
	[PMIC_INT3] = MAX8997_REG_INT3MSK,
	[PMIC_INT4] = MAX8997_REG_INT4MSK,
	[FUEL_GAUGE] = MAX8997_REG_INVALID,
	[MUIC_INT1] = MAX8997_MUIC_REG_INTMASK1,
	[MUIC_INT2] = MAX8997_MUIC_REG_INTMASK2,
	[MUIC_INT3] = MAX8997_MUIC_REG_INTMASK3,
	[GPIO_LOW] = MAX8997_REG_INVALID,
	[GPIO_HI] = MAX8997_REG_INVALID,
	[FLASH_STATUS] = MAX8997_REG_INVALID,
};

static struct i2c_client *get_i2c(struct max8997_dev *max8997,
				enum max8997_irq_source src)
{
	switch (src) {
	case PMIC_INT1 ... PMIC_INT4:
		return max8997->i2c;
	case FUEL_GAUGE:
		return NULL;
	case MUIC_INT1 ... MUIC_INT3:
		return max8997->muic;
	case GPIO_LOW ... GPIO_HI:
		return max8997->i2c;
	case FLASH_STATUS:
		return max8997->i2c;
	default:
		return ERR_PTR(-EINVAL);
	}
}

struct max8997_irq_data {
	int mask;
	enum max8997_irq_source group;
};

#define DECLARE_IRQ(idx, _group, _mask)		\
	[(idx)] = { .group = (_group), .mask = (_mask) }
static const struct max8997_irq_data max8997_irqs[] = {
	DECLARE_IRQ(MAX8997_PMICIRQ_PWRONR,	PMIC_INT1, 1 << 0),
	DECLARE_IRQ(MAX8997_PMICIRQ_PWRONF,	PMIC_INT1, 1 << 1),
	DECLARE_IRQ(MAX8997_PMICIRQ_PWRON1SEC,	PMIC_INT1, 1 << 3),
	DECLARE_IRQ(MAX8997_PMICIRQ_JIGONR,	PMIC_INT1, 1 << 4),
	DECLARE_IRQ(MAX8997_PMICIRQ_JIGONF,	PMIC_INT1, 1 << 5),
	DECLARE_IRQ(MAX8997_PMICIRQ_LOWBAT2,	PMIC_INT1, 1 << 6),
	DECLARE_IRQ(MAX8997_PMICIRQ_LOWBAT1,	PMIC_INT1, 1 << 7),

	DECLARE_IRQ(MAX8997_PMICIRQ_JIGR,	PMIC_INT2, 1 << 0),
	DECLARE_IRQ(MAX8997_PMICIRQ_JIGF,	PMIC_INT2, 1 << 1),
	DECLARE_IRQ(MAX8997_PMICIRQ_MR,		PMIC_INT2, 1 << 2),
	DECLARE_IRQ(MAX8997_PMICIRQ_DVS1OK,	PMIC_INT2, 1 << 3),
	DECLARE_IRQ(MAX8997_PMICIRQ_DVS2OK,	PMIC_INT2, 1 << 4),
	DECLARE_IRQ(MAX8997_PMICIRQ_DVS3OK,	PMIC_INT2, 1 << 5),
	DECLARE_IRQ(MAX8997_PMICIRQ_DVS4OK,	PMIC_INT2, 1 << 6),

	DECLARE_IRQ(MAX8997_PMICIRQ_CHGINS,	PMIC_INT3, 1 << 0),
	DECLARE_IRQ(MAX8997_PMICIRQ_CHGRM,	PMIC_INT3, 1 << 1),
	DECLARE_IRQ(MAX8997_PMICIRQ_DCINOVP,	PMIC_INT3, 1 << 2),
	DECLARE_IRQ(MAX8997_PMICIRQ_TOPOFFR,	PMIC_INT3, 1 << 3),
	DECLARE_IRQ(MAX8997_PMICIRQ_CHGRSTF,	PMIC_INT3, 1 << 5),
	DECLARE_IRQ(MAX8997_PMICIRQ_MBCHGTMEXPD,	PMIC_INT3, 1 << 7),

	DECLARE_IRQ(MAX8997_PMICIRQ_RTC60S,	PMIC_INT4, 1 << 0),
	DECLARE_IRQ(MAX8997_PMICIRQ_RTCA1,	PMIC_INT4, 1 << 1),
	DECLARE_IRQ(MAX8997_PMICIRQ_RTCA2,	PMIC_INT4, 1 << 2),
	DECLARE_IRQ(MAX8997_PMICIRQ_SMPL_INT,	PMIC_INT4, 1 << 3),
	DECLARE_IRQ(MAX8997_PMICIRQ_RTC1S,	PMIC_INT4, 1 << 4),
	DECLARE_IRQ(MAX8997_PMICIRQ_WTSR,	PMIC_INT4, 1 << 5),

	DECLARE_IRQ(MAX8997_MUICIRQ_ADCError,	MUIC_INT1, 1 << 2),
	DECLARE_IRQ(MAX8997_MUICIRQ_ADCLow,	MUIC_INT1, 1 << 1),
	DECLARE_IRQ(MAX8997_MUICIRQ_ADC,	MUIC_INT1, 1 << 0),

	DECLARE_IRQ(MAX8997_MUICIRQ_VBVolt,	MUIC_INT2, 1 << 4),
	DECLARE_IRQ(MAX8997_MUICIRQ_DBChg,	MUIC_INT2, 1 << 3),
	DECLARE_IRQ(MAX8997_MUICIRQ_DCDTmr,	MUIC_INT2, 1 << 2),
	DECLARE_IRQ(MAX8997_MUICIRQ_ChgDetRun,	MUIC_INT2, 1 << 1),
	DECLARE_IRQ(MAX8997_MUICIRQ_ChgTyp,	MUIC_INT2, 1 << 0),

	DECLARE_IRQ(MAX8997_MUICIRQ_OVP,	MUIC_INT3, 1 << 2),
};

=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * Interrupt controller support for MAX8997
 *
 * Copyright (C) 2010 Samsung Electronics Co.Ltd
 *
 * based on max8998-irq.c
 *
 *  <ms925.kim@samsung.com>
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 *
 */

#include <linux/device.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/mfd/max8997-private.h>
#include <linux/delay.h>

extern struct class *sec_class;

#define FLED1_FLT_BIT	(1<<0)
#define FLED2_FLT_BIT	(1<<1)
#define FLED_FLT_MASK	(FLED1_FLT_BIT | FLED2_FLT_BIT)

static u8 fled_status;

struct max8997_irq_data {
	int reg;
	int mask;
};

static struct max8997_irq_data max8997_irqs[] = {
	[MAX8997_IRQ_PWRONR] = {
		.reg = 1,
		.mask = MAX8997_IRQ_PWRONR_MASK,
	},
	[MAX8997_IRQ_PWRONF] = {
		.reg = 1,
		.mask = MAX8997_IRQ_PWRONF_MASK,
	},
	[MAX8997_IRQ_PWRON1SEC] = {
		.reg = 1,
		.mask = MAX8997_IRQ_PWRON1SEC_MASK,
	},
	[MAX8997_IRQ_JIGONR] = {
		.reg = 1,
		.mask = MAX8997_IRQ_JIGONR_MASK,
	},
	[MAX8997_IRQ_JIGONF] = {
		.reg = 1,
		.mask = MAX8997_IRQ_JIGONF_MASK,
	},
	[MAX8997_IRQ_LOWBAT2] = {
		.reg = 1,
		.mask = MAX8997_IRQ_LOWBAT2_MASK,
	},
	[MAX8997_IRQ_LOWBAT1] = {
		.reg = 1,
		.mask = MAX8997_IRQ_LOWBAT1_MASK,
	},
	[MAX8997_IRQ_JIGR] = {
		.reg = 2,
		.mask = MAX8997_IRQ_JIGR_MASK,
	},
	[MAX8997_IRQ_JIGF] = {
		.reg = 2,
		.mask = MAX8997_IRQ_JIGF_MASK,
	},
	[MAX8997_IRQ_MR] = {
		.reg = 2,
		.mask = MAX8997_IRQ_MR_MASK,
	},
	[MAX8997_IRQ_DVS1OK] = {
		.reg = 2,
		.mask = MAX8997_IRQ_DVS1OK_MASK,
	},
	[MAX8997_IRQ_DVS2OK] = {
		.reg = 2,
		.mask = MAX8997_IRQ_DVS2OK_MASK,
	},
	[MAX8997_IRQ_DVS4OK] = {
		.reg = 2,
		.mask = MAX8997_IRQ_DVS4OK_MASK,
	},
	[MAX8997_IRQ_DVS5OK] = {
		.reg = 2,
		.mask = MAX8997_IRQ_DVS5OK_MASK,
	},
	[MAX8997_IRQ_CHGINS] = {
		.reg = 3,
		.mask = MAX8997_IRQ_CHGINS_MASK,
	},
	[MAX8997_IRQ_CHGRM] = {
		.reg = 3,
		.mask = MAX8997_IRQ_CHGRM_MASK,
	},
	[MAX8997_IRQ_DCINOVP] = {
		.reg = 3,
		.mask = MAX8997_IRQ_DCINOVP_MASK,
	},
	[MAX8997_IRQ_TOPOFF] = {
		.reg = 3,
		.mask = MAX8997_IRQ_TOPOFF_MASK,
	},
	[MAX8997_IRQ_CHGRSTF] = {
		.reg = 3,
		.mask = MAX8997_IRQ_CHGRSTF_MASK,
	},
	[MAX8997_IRQ_MBCHGTMEXPD] = {
		.reg = 3,
		.mask = MAX8997_IRQ_MBCHGTMEXPD_MASK,
	},
	[MAX8997_IRQ_RTC60S] = {
		.reg = 4,
		.mask = MAX8997_IRQ_RTC60S_MASK,
	},
	[MAX8997_IRQ_RTCA1] = {
		.reg = 4,
		.mask = MAX8997_IRQ_RTCA1_MASK,
	},
	[MAX8997_IRQ_RTCA2] = {
		.reg = 4,
		.mask = MAX8997_IRQ_RTCA2_MASK,
	},
	[MAX8997_IRQ_SMPL_INT] = {
		.reg = 4,
		.mask = MAX8997_IRQ_SMPL_INT_MASK,
	},
	[MAX8997_IRQ_RTC1S] = {
		.reg = 4,
		.mask = MAX8997_IRQ_RTC1S_MASK,
	},
	[MAX8997_IRQ_WTSR] = {
		.reg = 4,
		.mask = MAX8997_IRQ_WTSR_MASK,
	},
	[MAX8997_IRQ_ADC] = {
		.reg = 5,
		.mask = MAX8997_IRQ_ADC_MASK,
	},
	[MAX8997_IRQ_ADCLOW] = {
		.reg = 5,
		.mask = MAX8997_IRQ_ADCLOW_MASK,
	},
	[MAX8997_IRQ_ADCERR] = {
		.reg = 5,
		.mask = MAX8997_IRQ_ADCERR_MASK,
	},
	[MAX8997_IRQ_CHGTYP] = {
		.reg = 6,
		.mask = MAX8997_IRQ_CHGTYP_MASK,
	},
	[MAX8997_IRQ_CHGDETRUN] = {
		.reg = 6,
		.mask = MAX8997_IRQ_CHGDETRUN_MASK,
	},
	[MAX8997_IRQ_DCDTMR] = {
		.reg = 6,
		.mask = MAX8997_IRQ_DCDTMR_MASK,
	},
	[MAX8997_IRQ_DBCHG] = {
		.reg = 6,
		.mask = MAX8997_IRQ_DCDTMR_MASK,
	},
	[MAX8997_IRQ_VBVOLT] = {
		.reg = 6,
		.mask = MAX8997_IRQ_VBVOLT_MASK,
	},
	[MAX8997_IRQ_OVP] = {
		.reg = 7,
		.mask = MAX8997_IRQ_OVP_MASK,
	},
};

static inline struct max8997_irq_data *
irq_to_max8997_irq(struct max8997_dev *max8997, int irq)
{
	return &max8997_irqs[irq - max8997->irq_base];
}

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static void max8997_irq_lock(struct irq_data *data)
{
	struct max8997_dev *max8997 = irq_get_chip_data(data->irq);

	mutex_lock(&max8997->irqlock);
}

static void max8997_irq_sync_unlock(struct irq_data *data)
{
	struct max8997_dev *max8997 = irq_get_chip_data(data->irq);
	int i;

<<<<<<< HEAD
<<<<<<< HEAD
	for (i = 0; i < MAX8997_IRQ_GROUP_NR; i++) {
		u8 mask_reg = max8997_mask_reg[i];
		struct i2c_client *i2c = get_i2c(max8997, i);

		if (mask_reg == MAX8997_REG_INVALID ||
				IS_ERR_OR_NULL(i2c))
			continue;
		max8997->irq_masks_cache[i] = max8997->irq_masks_cur[i];

		max8997_write_reg(i2c, max8997_mask_reg[i],
				max8997->irq_masks_cur[i]);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	for (i = 0; i < ARRAY_SIZE(max8997->irq_masks_cur); i++) {
		/*
		 * If there's been a change in the mask write it back
		 * to the hardware.
		 */
		if (max8997->irq_masks_cur[i] != max8997->irq_masks_cache[i]) {
			max8997->irq_masks_cache[i] = max8997->irq_masks_cur[i];
			if (i < MAX8997_NUM_IRQ_PMIC_REGS)
				max8997_write_reg(max8997->i2c,
						MAX8997_REG_IRQM1 + i,
						max8997->irq_masks_cur[i]);
			else
				max8997_write_reg(max8997->muic,
						MAX8997_MUIC_REG_INTMASK1 + i
						- MAX8997_NUM_IRQ_PMIC_REGS,
						~max8997->irq_masks_cur[i]);
		}
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}

	mutex_unlock(&max8997->irqlock);
}

<<<<<<< HEAD
<<<<<<< HEAD
static const inline struct max8997_irq_data *
irq_to_max8997_irq(struct max8997_dev *max8997, int irq)
{
	return &max8997_irqs[irq - max8997->irq_base];
}

static void max8997_irq_mask(struct irq_data *data)
{
	struct max8997_dev *max8997 = irq_get_chip_data(data->irq);
	const struct max8997_irq_data *irq_data = irq_to_max8997_irq(max8997,
								data->irq);

	max8997->irq_masks_cur[irq_data->group] |= irq_data->mask;
}

static void max8997_irq_unmask(struct irq_data *data)
{
	struct max8997_dev *max8997 = irq_get_chip_data(data->irq);
	const struct max8997_irq_data *irq_data = irq_to_max8997_irq(max8997,
								data->irq);

	max8997->irq_masks_cur[irq_data->group] &= ~irq_data->mask;
}

static struct irq_chip max8997_irq_chip = {
	.name			= "max8997",
	.irq_bus_lock		= max8997_irq_lock,
	.irq_bus_sync_unlock	= max8997_irq_sync_unlock,
	.irq_mask		= max8997_irq_mask,
	.irq_unmask		= max8997_irq_unmask,
};

#define MAX8997_IRQSRC_PMIC		(1 << 1)
#define MAX8997_IRQSRC_FUELGAUGE	(1 << 2)
#define MAX8997_IRQSRC_MUIC		(1 << 3)
#define MAX8997_IRQSRC_GPIO		(1 << 4)
#define MAX8997_IRQSRC_FLASH		(1 << 5)
static irqreturn_t max8997_irq_thread(int irq, void *data)
{
	struct max8997_dev *max8997 = data;
	u8 irq_reg[MAX8997_IRQ_GROUP_NR] = {};
	u8 irq_src;
	int ret;
	int i;

	ret = max8997_read_reg(max8997->i2c, MAX8997_REG_INTSRC, &irq_src);
	if (ret < 0) {
		dev_err(max8997->dev, "Failed to read interrupt source: %d\n",
				ret);
		return IRQ_NONE;
	}

	if (irq_src & MAX8997_IRQSRC_PMIC) {
		/* PMIC INT1 ~ INT4 */
		max8997_bulk_read(max8997->i2c, MAX8997_REG_INT1, 4,
				&irq_reg[PMIC_INT1]);
	}
	if (irq_src & MAX8997_IRQSRC_FUELGAUGE) {
		/*
		 * TODO: FUEL GAUGE
		 *
		 * This is to be supported by Max17042 driver. When
		 * an interrupt incurs here, it should be relayed to a
		 * Max17042 device that is connected (probably by
		 * platform-data). However, we do not have interrupt
		 * handling in Max17042 driver currently. The Max17042 IRQ
		 * driver should be ready to be used as a stand-alone device and
		 * a Max8997-dependent device. Because it is not ready in
		 * Max17042-side and it is not too critical in operating
		 * Max8997, we do not implement this in initial releases.
		 */
		irq_reg[FUEL_GAUGE] = 0;
	}
	if (irq_src & MAX8997_IRQSRC_MUIC) {
		/* MUIC INT1 ~ INT3 */
		max8997_bulk_read(max8997->muic, MAX8997_MUIC_REG_INT1, 3,
				&irq_reg[MUIC_INT1]);
	}
	if (irq_src & MAX8997_IRQSRC_GPIO) {
		/* GPIO Interrupt */
		u8 gpio_info[MAX8997_NUM_GPIO];

		irq_reg[GPIO_LOW] = 0;
		irq_reg[GPIO_HI] = 0;

		max8997_bulk_read(max8997->i2c, MAX8997_REG_GPIOCNTL1,
				MAX8997_NUM_GPIO, gpio_info);
		for (i = 0; i < MAX8997_NUM_GPIO; i++) {
			bool interrupt = false;

			switch (gpio_info[i] & MAX8997_GPIO_INT_MASK) {
			case MAX8997_GPIO_INT_BOTH:
				if (max8997->gpio_status[i] != gpio_info[i])
					interrupt = true;
				break;
			case MAX8997_GPIO_INT_RISE:
				if ((max8997->gpio_status[i] != gpio_info[i]) &&
				    (gpio_info[i] & MAX8997_GPIO_DATA_MASK))
					interrupt = true;
				break;
			case MAX8997_GPIO_INT_FALL:
				if ((max8997->gpio_status[i] != gpio_info[i]) &&
				    !(gpio_info[i] & MAX8997_GPIO_DATA_MASK))
					interrupt = true;
				break;
			default:
				break;
			}

			if (interrupt) {
				if (i < 8)
					irq_reg[GPIO_LOW] |= (1 << i);
				else
					irq_reg[GPIO_HI] |= (1 << (i - 8));
			}

		}
	}
	if (irq_src & MAX8997_IRQSRC_FLASH) {
		/* Flash Status Interrupt */
		ret = max8997_read_reg(max8997->i2c, MAX8997_REG_FLASHSTATUS,
				&irq_reg[FLASH_STATUS]);
	}

	/* Apply masking */
	for (i = 0; i < MAX8997_IRQ_GROUP_NR; i++)
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static void max8997_irq_unmask(struct irq_data *data)
{
	struct max8997_dev *max8997 = irq_get_chip_data(data->irq);
	struct max8997_irq_data *irq_data
		= irq_to_max8997_irq(max8997, data->irq);

	max8997->irq_masks_cur[irq_data->reg - 1] &= ~irq_data->mask;
}

static void max8997_irq_mask(struct irq_data *data)
{
	struct max8997_dev *max8997 = irq_get_chip_data(data->irq);
	struct max8997_irq_data *irq_data
		= irq_to_max8997_irq(max8997, data->irq);

	max8997->irq_masks_cur[irq_data->reg - 1] |= irq_data->mask;
}

static struct irq_chip max8997_irq_chip = {
	.name = "max8997",
	.irq_bus_lock = max8997_irq_lock,
	.irq_bus_sync_unlock = max8997_irq_sync_unlock,
	.irq_mask = max8997_irq_mask,
	.irq_unmask = max8997_irq_unmask,
};

static irqreturn_t max8997_irq_thread(int irq, void *data)
{
	struct max8997_dev *max8997 = data;
	u8 irq_src;
	u8 irq_flash;
	u8 irq_reg[MAX8997_NUM_IRQ_REGS];
	int ret;
	int i;

	ret = max8997_read_reg(max8997->i2c, MAX8997_REG_IRQ_SOURCE, &irq_src);

	if (ret < 0) {
		dev_err(max8997->dev, "Failed to read interrupt src"
				" register: %d\n", ret);
		return IRQ_NONE;
	}

	dev_info(max8997->dev, "%s: irq:%d, irq_src:0x%x\n", __func__,
			irq, irq_src);


	for (i = 0; i < MAX8997_NUM_IRQ_REGS; i++)
		irq_reg[i] = 0x0;

	if (irq_src & MAX8997_INTR_PMIC_MASK)
		ret = max8997_bulk_read(max8997->i2c, MAX8997_REG_IRQ1,
				MAX8997_NUM_IRQ_PMIC_REGS, irq_reg);
	else if (irq_src & MAX8997_INTR_MUIC_MASK)
		ret = max8997_bulk_read(max8997->muic, MAX8997_MUIC_REG_INT1,
				MAX8997_NUM_IRQ_MUIC_REGS,
				&irq_reg[MAX8997_NUM_IRQ_PMIC_REGS]);
	else if (irq_src & MAX8997_INTR_FLASH_MASK) {
		ret = max8997_read_reg(max8997->i2c, MAX8997_REG_FLASH_STATUS,
				&irq_flash);
		if (ret < 0)
			dev_err(max8997->dev, "%s: fail to read flash"
					" status: %d\n", __func__, ret);
		else {
			dev_info(max8997->dev, "%s: FLASH Interrupt: 0x%02x\n",
					__func__, irq_flash);
			fled_status = irq_flash & FLED_FLT_MASK;
		}
	} else if (irq_src & MAX8997_INTR_FUELGAUGE_MASK) {
		dev_warn(max8997->dev, "%s: Fuel Gauge interrupt\n", __func__);
		msleep(20);
	} else {
		dev_warn(max8997->dev, "Unused interrupt source: 0x%x\n",
				irq_src);
		return IRQ_NONE;
	}

	if (ret < 0) {
		dev_err(max8997->dev, "Failed to read interrupt register: %d\n",
				ret);
		return IRQ_NONE;
	}

	/* Apply masking */
	for (i = 0; i < MAX8997_NUM_IRQ_REGS; i++)
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		irq_reg[i] &= ~max8997->irq_masks_cur[i];

	/* Report */
	for (i = 0; i < MAX8997_IRQ_NR; i++) {
<<<<<<< HEAD
<<<<<<< HEAD
		if (irq_reg[max8997_irqs[i].group] & max8997_irqs[i].mask)
=======
		if (irq_reg[max8997_irqs[i].reg - 1] & max8997_irqs[i].mask)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		if (irq_reg[max8997_irqs[i].reg - 1] & max8997_irqs[i].mask)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			handle_nested_irq(max8997->irq_base + i);
	}

	return IRQ_HANDLED;
}

<<<<<<< HEAD
<<<<<<< HEAD
int max8997_irq_resume(struct max8997_dev *max8997)
{
	if (max8997->irq && max8997->irq_base)
		max8997_irq_thread(max8997->irq_base, max8997);
	return 0;
}

=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static ssize_t max8997_show_fled_state(struct device *dev,
					struct device_attribute *attr,
					char *buf)
{
	if (fled_status & FLED1_FLT_BIT)
		sprintf(buf, "LED1 FAULT\n");
	else if (fled_status & FLED2_FLT_BIT)
		sprintf(buf, "LED2 FAULT\n");
	else
		sprintf(buf, "LED OK\n");

	pr_info("%s: %s\n", __func__, buf);

	return strlen(buf);
}

static DEVICE_ATTR(fled_state, 0444, max8997_show_fled_state, NULL);

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
int max8997_irq_init(struct max8997_dev *max8997)
{
	int i;
	int cur_irq;
	int ret;
<<<<<<< HEAD
<<<<<<< HEAD
	u8 val;

	if (!max8997->irq) {
		dev_warn(max8997->dev, "No interrupt specified.\n");
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	u8 pmic_intm[MAX8997_NUM_IRQ_PMIC_REGS];
	u8 muic_intm[MAX8997_NUM_IRQ_MUIC_REGS];
	u8 pmic_id;
	struct device *fled_dev;

	if (!max8997->irq) {
		dev_warn(max8997->dev,
			 "No interrupt specified, no interrupts\n");
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		max8997->irq_base = 0;
		return 0;
	}

	if (!max8997->irq_base) {
<<<<<<< HEAD
<<<<<<< HEAD
		dev_err(max8997->dev, "No interrupt base specified.\n");
		return 0;
	}

	mutex_init(&max8997->irqlock);

	/* Mask individual interrupt sources */
	for (i = 0; i < MAX8997_IRQ_GROUP_NR; i++) {
		struct i2c_client *i2c;

		max8997->irq_masks_cur[i] = 0xff;
		max8997->irq_masks_cache[i] = 0xff;
		i2c = get_i2c(max8997, i);

		if (IS_ERR_OR_NULL(i2c))
			continue;
		if (max8997_mask_reg[i] == MAX8997_REG_INVALID)
			continue;

		max8997_write_reg(i2c, max8997_mask_reg[i], 0xff);
	}

	for (i = 0; i < MAX8997_NUM_GPIO; i++) {
		max8997->gpio_status[i] = (max8997_read_reg(max8997->i2c,
						MAX8997_REG_GPIOCNTL1 + i,
						&val)
					& MAX8997_GPIO_DATA_MASK) ?
					true : false;
	}

	/* Register with genirq */
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		dev_err(max8997->dev,
			"No interrupt base specified, no interrupts\n");
		return 0;
	}

	for (i = 0; i < MAX8997_NUM_IRQ_PMIC_REGS; i++)
		pmic_intm[i] = 0xff;

	for (i = 0; i < MAX8997_NUM_IRQ_MUIC_REGS; i++)
		muic_intm[i] = 0x00;

	mutex_init(&max8997->irqlock);

	ret = max8997_read_reg(max8997->i2c, MAX8997_REG_ID, &pmic_id);
	if (ret)
		dev_err(max8997->dev, "%s: fail to read PMIC ID(0x%X)\n",
				__func__, ret);
	else
		dev_info(max8997->dev, "%s: PMIC ID(0x%X)\n",
				__func__, pmic_id);

	/* Mask the individual interrupt sources */
	for (i = 0; i < MAX8997_NUM_IRQ_REGS; i++) {
		max8997->irq_masks_cur[i] = 0xff;
		max8997->irq_masks_cache[i] = 0xff;
	}

	ret = max8997_bulk_write(max8997->i2c, MAX8997_REG_IRQM1,
			MAX8997_NUM_IRQ_PMIC_REGS, pmic_intm);
	if (ret)
		dev_err(max8997->dev, "%s: fail to write PMIC IRQM(%d)\n",
				__func__, ret);

	ret = max8997_bulk_write(max8997->muic, MAX8997_MUIC_REG_INTMASK1,
			MAX8997_NUM_IRQ_MUIC_REGS, muic_intm);
	if (ret)
		dev_err(max8997->dev, "%s: fail to write MUIC IRQM(%d)\n",
				__func__, ret);

	/* Enable flash interrupts to debug flash over current issues
	 * refer MAX8997 I2C Registers: FLASH STATUS control register(0x6D)
	 * 0x01: FLED1_FLT : FLED1 status read back
	 * 0x02: FLED2_FLT : FLED2 status read back
	 */
	ret = max8997_write_reg(max8997->i2c, MAX8997_REG_FLASH_STATUS_MASK,
				0xfc);
	if (ret)
		dev_err(max8997->dev, "%s: fail to write FLASH IRQM(%d)\n",
				__func__, ret);

	fled_dev = device_create(sec_class, NULL, 0, NULL, "sec_fled");
	ret = device_create_file(fled_dev, &dev_attr_fled_state);
	if (ret)
		dev_err(fled_dev, "failed to create device file(fled_state)\n");

	/* register with genirq */
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	for (i = 0; i < MAX8997_IRQ_NR; i++) {
		cur_irq = i + max8997->irq_base;
		irq_set_chip_data(cur_irq, max8997);
		irq_set_chip_and_handler(cur_irq, &max8997_irq_chip,
<<<<<<< HEAD
<<<<<<< HEAD
				handle_edge_irq);
=======
					 handle_level_irq);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
					 handle_level_irq);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		irq_set_nested_thread(cur_irq, 1);
#ifdef CONFIG_ARM
		set_irq_flags(cur_irq, IRQF_VALID);
#else
		irq_set_noprobe(cur_irq);
#endif
	}

	ret = request_threaded_irq(max8997->irq, NULL, max8997_irq_thread,
<<<<<<< HEAD
<<<<<<< HEAD
			IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
			"max8997-irq", max8997);

	if (ret) {
		dev_err(max8997->dev, "Failed to request IRQ %d: %d\n",
				max8997->irq, ret);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
				   IRQF_TRIGGER_LOW | IRQF_ONESHOT,
				   "max8997-irq", max8997);
	if (ret) {
		dev_err(max8997->dev, "Failed to request IRQ %d: %d\n",
			max8997->irq, ret);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return ret;
	}

	if (!max8997->ono)
		return 0;

<<<<<<< HEAD
<<<<<<< HEAD
	ret = request_threaded_irq(max8997->ono, NULL, max8997_irq_thread,
			IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING |
			IRQF_ONESHOT, "max8997-ono", max8997);

	if (ret)
		dev_err(max8997->dev, "Failed to request ono-IRQ %d: %d\n",
				max8997->ono, ret);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	dev_dbg(max8997->dev, "%s: ono irq request\n", __func__);
	ret = request_threaded_irq(max8997->ono, NULL, max8997_irq_thread,
				   IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING |
				   IRQF_ONESHOT, "max8997-ono", max8997);
	if (ret) {
		dev_err(max8997->dev, "Failed to request IRQ %d: %d\n",
			max8997->ono, ret);
		return ret;
	}
	enable_irq_wake(max8997->ono);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return 0;
}

void max8997_irq_exit(struct max8997_dev *max8997)
{
	if (max8997->ono)
		free_irq(max8997->ono, max8997);

	if (max8997->irq)
		free_irq(max8997->irq, max8997);
}
