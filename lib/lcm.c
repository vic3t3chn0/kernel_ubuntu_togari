#include <linux/kernel.h>
#include <linux/gcd.h>
<<<<<<< HEAD
#include <linux/export.h>
#include <linux/lcm.h>
=======
#include <linux/module.h>
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

/* Lowest common multiple */
unsigned long lcm(unsigned long a, unsigned long b)
{
	if (a && b)
		return (a * b) / gcd(a, b);
	else if (b)
		return b;

	return a;
}
EXPORT_SYMBOL_GPL(lcm);
