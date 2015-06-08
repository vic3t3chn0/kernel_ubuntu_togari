 /*
 * linux/arch/m68k/sun3/sun3ints.c -- Sun-3(x) Linux interrupt handling code
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the main directory of this archive
 * for more details.
 */

#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/kernel_stat.h>
#include <linux/interrupt.h>
#include <asm/segment.h>
#include <asm/intersil.h>
#include <asm/oplib.h>
#include <asm/sun3ints.h>
#include <asm/irq_regs.h>
#include <linux/seq_file.h>

extern void sun3_leds (unsigned char);

void sun3_disable_interrupts(void)
{
	sun3_disable_irq(0);
}

void sun3_enable_interrupts(void)
{
	sun3_enable_irq(0);
}

static int led_pattern[8] = {
       ~(0x80), ~(0x01),
       ~(0x40), ~(0x02),
       ~(0x20), ~(0x04),
       ~(0x10), ~(0x08)
};

volatile unsigned char* sun3_intreg;

void sun3_enable_irq(unsigned int irq)
{
	*sun3_intreg |=  (1 << irq);
}

void sun3_disable_irq(unsigned int irq)
{
	*sun3_intreg &= ~(1 << irq);
}

static irqreturn_t sun3_int7(int irq, void *dev_id)
{
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	unsigned int cnt;

	cnt = kstat_irqs_cpu(irq, 0);
	if (!(cnt % 2000))
		sun3_leds(led_pattern[cnt % 16000 / 2000]);
<<<<<<< HEAD
=======
=======
	*sun3_intreg |=  (1 << irq);
	if (!(kstat_cpu(0).irqs[irq] % 2000))
		sun3_leds(led_pattern[(kstat_cpu(0).irqs[irq] % 16000) / 2000]);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return IRQ_HANDLED;
}

static irqreturn_t sun3_int5(int irq, void *dev_id)
{
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	unsigned int cnt;

#ifdef CONFIG_SUN3
	intersil_clear();
#endif
<<<<<<< HEAD
=======
=======
#ifdef CONFIG_SUN3
	intersil_clear();
#endif
        *sun3_intreg |=  (1 << irq);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#ifdef CONFIG_SUN3
	intersil_clear();
#endif
	xtime_update(1);
	update_process_times(user_mode(get_irq_regs()));
<<<<<<< HEAD
	cnt = kstat_irqs_cpu(irq, 0);
	if (!(cnt % 20))
		sun3_leds(led_pattern[cnt % 160 / 20]);
=======
<<<<<<< HEAD
	cnt = kstat_irqs_cpu(irq, 0);
	if (!(cnt % 20))
		sun3_leds(led_pattern[cnt % 160 / 20]);
=======
        if (!(kstat_cpu(0).irqs[irq] % 20))
                sun3_leds(led_pattern[(kstat_cpu(0).irqs[irq] % 160) / 20]);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return IRQ_HANDLED;
}

static irqreturn_t sun3_vec255(int irq, void *dev_id)
{
//	intersil_clear();
	return IRQ_HANDLED;
}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static void sun3_irq_enable(struct irq_data *data)
{
    sun3_enable_irq(data->irq);
};

static void sun3_irq_disable(struct irq_data *data)
{
    sun3_disable_irq(data->irq);
};

static struct irq_chip sun3_irq_chip = {
	.name		= "sun3",
	.irq_startup	= m68k_irq_startup,
	.irq_shutdown	= m68k_irq_shutdown,
	.irq_enable	= sun3_irq_enable,
	.irq_disable	= sun3_irq_disable,
	.irq_mask	= sun3_irq_disable,
	.irq_unmask	= sun3_irq_enable,
<<<<<<< HEAD
=======
=======
static void sun3_inthandle(unsigned int irq, struct pt_regs *fp)
{
        *sun3_intreg &= ~(1 << irq);

	__m68k_handle_int(irq, fp);
}

static struct irq_controller sun3_irq_controller = {
	.name		= "sun3",
	.lock		= __SPIN_LOCK_UNLOCKED(sun3_irq_controller.lock),
	.startup	= m68k_irq_startup,
	.shutdown	= m68k_irq_shutdown,
	.enable		= sun3_enable_irq,
	.disable	= sun3_disable_irq,
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

void __init sun3_init_IRQ(void)
{
	*sun3_intreg = 1;

<<<<<<< HEAD
	m68k_setup_irq_controller(&sun3_irq_chip, handle_level_irq, IRQ_AUTO_1,
				  7);
	m68k_setup_user_interrupt(VEC_USER, 128);
=======
<<<<<<< HEAD
	m68k_setup_irq_controller(&sun3_irq_chip, handle_level_irq, IRQ_AUTO_1,
				  7);
	m68k_setup_user_interrupt(VEC_USER, 128);
=======
	m68k_setup_auto_interrupt(sun3_inthandle);
	m68k_setup_irq_controller(&sun3_irq_controller, IRQ_AUTO_1, 7);
	m68k_setup_user_interrupt(VEC_USER, 128, NULL);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (request_irq(IRQ_AUTO_5, sun3_int5, 0, "int5", NULL))
		pr_err("Couldn't register %s interrupt\n", "int5");
	if (request_irq(IRQ_AUTO_7, sun3_int7, 0, "int7", NULL))
		pr_err("Couldn't register %s interrupt\n", "int7");
	if (request_irq(IRQ_USER+127, sun3_vec255, 0, "vec255", NULL))
		pr_err("Couldn't register %s interrupt\n", "vec255");
}
