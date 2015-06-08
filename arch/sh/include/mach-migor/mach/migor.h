#ifndef __ASM_SH_MIGOR_H
#define __ASM_SH_MIGOR_H

#define PORT_MSELCRA 0xa4050180
#define PORT_MSELCRB 0xa4050182
#define BSC_CS4BCR 0xfec10010
#define BSC_CS6ABCR 0xfec1001c
#define BSC_CS4WCR 0xfec10030

#include <video/sh_mobile_lcdc.h>

<<<<<<< HEAD
int migor_lcd_qvga_setup(void *sys_ops_handle,
=======
<<<<<<< HEAD
int migor_lcd_qvga_setup(void *sys_ops_handle,
=======
int migor_lcd_qvga_setup(void *board_data, void *sys_ops_handle,
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			 struct sh_mobile_lcdc_sys_bus_ops *sys_ops);

#endif /* __ASM_SH_MIGOR_H */
