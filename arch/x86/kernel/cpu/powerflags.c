/*
 * Strings for the various x86 power flags
 *
 * This file must not contain any executable code.
 */

#include <asm/cpufeature.h>

const char *const x86_power_flags[32] = {
	"ts",	/* temperature sensor */
	"fid",  /* frequency id control */
	"vid",  /* voltage id control */
	"ttp",  /* thermal trip */
	"tm",
	"stc",
	"100mhzsteps",
	"hwpstate",
	"",	/* tsc invariant mapped to constant_tsc */
<<<<<<< HEAD
	"cpb",  /* core performance boost */
	"eff_freq_ro", /* Readonly aperf/mperf */
=======
<<<<<<< HEAD
	"cpb",  /* core performance boost */
	"eff_freq_ro", /* Readonly aperf/mperf */
=======
		/* nothing */
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};
