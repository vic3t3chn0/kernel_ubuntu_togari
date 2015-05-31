#ifndef __WSP_H
#define __WSP_H

#include <asm/wsp.h>

<<<<<<< HEAD
/* Devtree compatible strings for major devices */
#define PCIE_COMPATIBLE     "ibm,wsp-pciex"

extern void wsp_setup_arch(void);
extern void wsp_setup_irq(void);
extern int wsp_probe_devices(void);
extern void wsp_halt(void);

=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
extern void wsp_setup_pci(void);
extern void scom_init_wsp(void);

extern void a2_setup_smp(void);
extern int a2_scom_startup_cpu(unsigned int lcpu, int thr_idx,
			       struct device_node *np);
<<<<<<< HEAD
extern int smp_a2_cpu_bootable(unsigned int nr);
extern int __devinit smp_a2_kick_cpu(int nr);

extern void opb_pic_init(void);

/* chroma specific managment */
extern void wsp_h8_restart(char *cmd);
extern void wsp_h8_power_off(void);
extern void __init wsp_setup_h8(void);
=======
int smp_a2_cpu_bootable(unsigned int nr);
int __devinit smp_a2_kick_cpu(int nr);

void opb_pic_init(void);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

#endif /*  __WSP_H */
