#ifndef __ASM_SH_CLOCK_H
#define __ASM_SH_CLOCK_H

#include <linux/sh_clk.h>

/* Should be defined by processor-specific code */
<<<<<<< HEAD
void __deprecated arch_init_clk_ops(struct sh_clk_ops **, int type);
=======
<<<<<<< HEAD
void __deprecated arch_init_clk_ops(struct sh_clk_ops **, int type);
=======
void __deprecated arch_init_clk_ops(struct clk_ops **, int type);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
int __init arch_clk_init(void);

/* arch/sh/kernel/cpu/clock-cpg.c */
int __init __deprecated cpg_clk_init(void);

/* arch/sh/kernel/cpu/clock.c */
int clk_init(void);

#endif /* __ASM_SH_CLOCK_H */
