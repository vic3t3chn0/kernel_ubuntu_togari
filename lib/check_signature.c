#include <linux/io.h>
<<<<<<< HEAD
#include <linux/export.h>
=======
<<<<<<< HEAD
#include <linux/export.h>
=======
#include <linux/module.h>
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/**
 *	check_signature		-	find BIOS signatures
 *	@io_addr: mmio address to check
 *	@signature:  signature block
 *	@length: length of signature
 *
 *	Perform a signature comparison with the mmio address io_addr. This
 *	address should have been obtained by ioremap.
 *	Returns 1 on a match.
 */

int check_signature(const volatile void __iomem *io_addr,
			const unsigned char *signature, int length)
{
	while (length--) {
		if (readb(io_addr) != *signature)
			return 0;
		io_addr++;
		signature++;
	}
	return 1;
}
EXPORT_SYMBOL(check_signature);
