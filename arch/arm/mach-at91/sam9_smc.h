/*
 * linux/arch/arm/mach-at91/sam9_smc.
 *
 * Copyright (C) 2008 Andrew Victor
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

<<<<<<< HEAD
extern void __init at91sam9_ioremap_smc(int id, u32 addr);
=======
<<<<<<< HEAD
extern void __init at91sam9_ioremap_smc(int id, u32 addr);
=======
struct sam9_smc_config {
	/* Setup register */
	u8 ncs_read_setup;
	u8 nrd_setup;
	u8 ncs_write_setup;
	u8 nwe_setup;

	/* Pulse register */
	u8 ncs_read_pulse;
	u8 nrd_pulse;
	u8 ncs_write_pulse;
	u8 nwe_pulse;

	/* Cycle register */
	u16 read_cycle;
	u16 write_cycle;

	/* Mode register */
	u32 mode;
	u8 tdf_cycles:4;
};

extern void __init sam9_smc_configure(int cs, struct sam9_smc_config* config);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
