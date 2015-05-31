/*
 * arch/sh/kernel/cpu/shmobile/cpuidle.c
 *
 * Cpuidle support code for SuperH Mobile
 *
 *  Copyright (C) 2009 Magnus Damm
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 */
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/io.h>
#include <linux/suspend.h>
#include <linux/cpuidle.h>
<<<<<<< HEAD
#include <linux/export.h>
#include <asm/suspend.h>
#include <asm/uaccess.h>
=======
#include <asm/suspend.h>
#include <asm/uaccess.h>
#include <asm/hwblk.h>
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

static unsigned long cpuidle_mode[] = {
	SUSP_SH_SLEEP, /* regular sleep mode */
	SUSP_SH_SLEEP | SUSP_SH_SF, /* sleep mode + self refresh */
	SUSP_SH_STANDBY | SUSP_SH_SF, /* software standby mode + self refresh */
};

static int cpuidle_sleep_enter(struct cpuidle_device *dev,
<<<<<<< HEAD
				struct cpuidle_driver *drv,
				int index)
{
	unsigned long allowed_mode = SUSP_SH_SLEEP;
	int requested_state = index;
=======
			       struct cpuidle_state *state)
{
	unsigned long allowed_mode = arch_hwblk_sleep_mode();
	ktime_t before, after;
	int requested_state = state - &dev->states[0];
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	int allowed_state;
	int k;

	/* convert allowed mode to allowed state */
	for (k = ARRAY_SIZE(cpuidle_mode) - 1; k > 0; k--)
		if (cpuidle_mode[k] == allowed_mode)
			break;

	allowed_state = k;

	/* take the following into account for sleep mode selection:
	 * - allowed_state: best mode allowed by hardware (clock deps)
	 * - requested_state: best mode allowed by software (latencies)
	 */
	k = min_t(int, allowed_state, requested_state);

<<<<<<< HEAD
	sh_mobile_call_standby(cpuidle_mode[k]);

	return k;
=======
	dev->last_state = &dev->states[k];
	before = ktime_get();
	sh_mobile_call_standby(cpuidle_mode[k]);
	after = ktime_get();
	return ktime_to_ns(ktime_sub(after, before)) >> 10;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
}

static struct cpuidle_device cpuidle_dev;
static struct cpuidle_driver cpuidle_driver = {
<<<<<<< HEAD
	.name			= "sh_idle",
	.owner			= THIS_MODULE,
	.en_core_tk_irqen	= 1,
=======
	.name =		"sh_idle",
	.owner =	THIS_MODULE,
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
};

void sh_mobile_setup_cpuidle(void)
{
	struct cpuidle_device *dev = &cpuidle_dev;
<<<<<<< HEAD
	struct cpuidle_driver *drv = &cpuidle_driver;
	struct cpuidle_state *state;
	int i;


	for (i = 0; i < CPUIDLE_STATE_MAX; i++) {
		drv->states[i].name[0] = '\0';
		drv->states[i].desc[0] = '\0';
=======
	struct cpuidle_state *state;
	int i;

	cpuidle_register_driver(&cpuidle_driver);

	for (i = 0; i < CPUIDLE_STATE_MAX; i++) {
		dev->states[i].name[0] = '\0';
		dev->states[i].desc[0] = '\0';
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	}

	i = CPUIDLE_DRIVER_STATE_START;

<<<<<<< HEAD
	state = &drv->states[i++];
=======
	state = &dev->states[i++];
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	snprintf(state->name, CPUIDLE_NAME_LEN, "C1");
	strncpy(state->desc, "SuperH Sleep Mode", CPUIDLE_DESC_LEN);
	state->exit_latency = 1;
	state->target_residency = 1 * 2;
	state->power_usage = 3;
	state->flags = 0;
	state->flags |= CPUIDLE_FLAG_TIME_VALID;
	state->enter = cpuidle_sleep_enter;

<<<<<<< HEAD
	drv->safe_state_index = i-1;

	if (sh_mobile_sleep_supported & SUSP_SH_SF) {
		state = &drv->states[i++];
=======
	dev->safe_state = state;

	if (sh_mobile_sleep_supported & SUSP_SH_SF) {
		state = &dev->states[i++];
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		snprintf(state->name, CPUIDLE_NAME_LEN, "C2");
		strncpy(state->desc, "SuperH Sleep Mode [SF]",
			CPUIDLE_DESC_LEN);
		state->exit_latency = 100;
		state->target_residency = 1 * 2;
		state->power_usage = 1;
		state->flags = 0;
		state->flags |= CPUIDLE_FLAG_TIME_VALID;
		state->enter = cpuidle_sleep_enter;
	}

	if (sh_mobile_sleep_supported & SUSP_SH_STANDBY) {
<<<<<<< HEAD
		state = &drv->states[i++];
=======
		state = &dev->states[i++];
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		snprintf(state->name, CPUIDLE_NAME_LEN, "C3");
		strncpy(state->desc, "SuperH Mobile Standby Mode [SF]",
			CPUIDLE_DESC_LEN);
		state->exit_latency = 2300;
		state->target_residency = 1 * 2;
		state->power_usage = 1;
		state->flags = 0;
		state->flags |= CPUIDLE_FLAG_TIME_VALID;
		state->enter = cpuidle_sleep_enter;
	}

<<<<<<< HEAD
	drv->state_count = i;
	dev->state_count = i;

	cpuidle_register_driver(&cpuidle_driver);

=======
	dev->state_count = i;

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	cpuidle_register_device(dev);
}
