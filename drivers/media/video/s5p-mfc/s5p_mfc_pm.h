/*
 * linux/drivers/media/video/s5p-mfc/s5p_mfc_pm.h
 *
<<<<<<< HEAD
 * Copyright (C) 2011 Samsung Electronics Co., Ltd.
=======
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
 *		http://www.samsung.com/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

<<<<<<< HEAD
#ifndef S5P_MFC_PM_H_
#define S5P_MFC_PM_H_
=======
#ifndef __S5P_MFC_PM_H
#define __S5P_MFC_PM_H __FILE__
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0

int s5p_mfc_init_pm(struct s5p_mfc_dev *dev);
void s5p_mfc_final_pm(struct s5p_mfc_dev *dev);

int s5p_mfc_clock_on(void);
void s5p_mfc_clock_off(void);
int s5p_mfc_power_on(void);
int s5p_mfc_power_off(void);
<<<<<<< HEAD

#endif /* S5P_MFC_PM_H_ */
=======
#ifdef CONFIG_ARCH_EXYNOS4
bool s5p_mfc_power_chk(void);
#endif

#endif /* __S5P_MFC_PM_H */
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
