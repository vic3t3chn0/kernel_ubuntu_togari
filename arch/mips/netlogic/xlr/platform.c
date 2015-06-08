/*
 * Copyright 2011, Netlogic Microsystems.
 * Copyright 2004, Matt Porter <mporter@kernel.crashing.org>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/resource.h>
#include <linux/serial_8250.h>
#include <linux/serial_reg.h>

<<<<<<< HEAD
#include <asm/netlogic/haldefs.h>
=======
<<<<<<< HEAD
#include <asm/netlogic/haldefs.h>
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <asm/netlogic/xlr/iomap.h>
#include <asm/netlogic/xlr/pic.h>
#include <asm/netlogic/xlr/xlr.h>

unsigned int nlm_xlr_uart_in(struct uart_port *p, int offset)
{
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	uint64_t uartbase;
	unsigned int value;

	/* sign extend to 64 bits, if needed */
	uartbase = (uint64_t)(long)p->membase;
	value = nlm_read_reg(uartbase, offset);
<<<<<<< HEAD
=======
=======
	nlm_reg_t *mmio;
	unsigned int value;

	/* XLR uart does not need any mapping of regs */
	mmio = (nlm_reg_t *)(p->membase + (offset << p->regshift));
	value = netlogic_read_reg(mmio, 0);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	/* See XLR/XLS errata */
	if (offset == UART_MSR)
		value ^= 0xF0;
	else if (offset == UART_MCR)
		value ^= 0x3;

	return value;
}

void nlm_xlr_uart_out(struct uart_port *p, int offset, int value)
{
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	uint64_t uartbase;

	/* sign extend to 64 bits, if needed */
	uartbase = (uint64_t)(long)p->membase;
<<<<<<< HEAD
=======
=======
	nlm_reg_t *mmio;

	/* XLR uart does not need any mapping of regs */
	mmio = (nlm_reg_t *)(p->membase + (offset << p->regshift));
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	/* See XLR/XLS errata */
	if (offset == UART_MSR)
		value ^= 0xF0;
	else if (offset == UART_MCR)
		value ^= 0x3;

<<<<<<< HEAD
	nlm_write_reg(uartbase, offset, value);
=======
<<<<<<< HEAD
	nlm_write_reg(uartbase, offset, value);
=======
	netlogic_write_reg(mmio, 0, value);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

#define PORT(_irq)					\
	{						\
		.irq		= _irq,			\
		.regshift	= 2,			\
		.iotype		= UPIO_MEM32,		\
		.flags		= (UPF_SKIP_TEST |	\
			 UPF_FIXED_TYPE | UPF_BOOT_AUTOCONF),\
		.uartclk	= PIC_CLKS_PER_SEC,	\
		.type		= PORT_16550A,		\
		.serial_in	= nlm_xlr_uart_in,	\
		.serial_out	= nlm_xlr_uart_out,	\
	}

static struct plat_serial8250_port xlr_uart_data[] = {
	PORT(PIC_UART_0_IRQ),
	PORT(PIC_UART_1_IRQ),
	{},
};

static struct platform_device uart_device = {
	.name		= "serial8250",
	.id		= PLAT8250_DEV_PLATFORM,
	.dev = {
		.platform_data = xlr_uart_data,
	},
};

static int __init nlm_uart_init(void)
{
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	unsigned long uartbase;

	uartbase = (unsigned long)nlm_mmio_base(NETLOGIC_IO_UART_0_OFFSET);
	xlr_uart_data[0].membase = (void __iomem *)uartbase;
	xlr_uart_data[0].mapbase = CPHYSADDR(uartbase);

	uartbase = (unsigned long)nlm_mmio_base(NETLOGIC_IO_UART_1_OFFSET);
	xlr_uart_data[1].membase = (void __iomem *)uartbase;
	xlr_uart_data[1].mapbase = CPHYSADDR(uartbase);
<<<<<<< HEAD
=======
=======
	nlm_reg_t *mmio;

	mmio = netlogic_io_mmio(NETLOGIC_IO_UART_0_OFFSET);
	xlr_uart_data[0].membase = (void __iomem *)mmio;
	xlr_uart_data[0].mapbase = CPHYSADDR((unsigned long)mmio);

	mmio = netlogic_io_mmio(NETLOGIC_IO_UART_1_OFFSET);
	xlr_uart_data[1].membase = (void __iomem *)mmio;
	xlr_uart_data[1].mapbase = CPHYSADDR((unsigned long)mmio);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return platform_device_register(&uart_device);
}

arch_initcall(nlm_uart_init);
