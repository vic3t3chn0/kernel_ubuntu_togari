#include <linux/kernel.h>
#include <linux/gcd.h>
<<<<<<< HEAD
#include <linux/export.h>
=======
#include <linux/module.h>
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

/* Greatest common divisor */
unsigned long gcd(unsigned long a, unsigned long b)
{
	unsigned long r;

	if (a < b)
		swap(a, b);
<<<<<<< HEAD
=======

	if (!b)
		return a;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	while ((r = a % b) != 0) {
		a = b;
		b = r;
	}
	return b;
}
EXPORT_SYMBOL_GPL(gcd);
