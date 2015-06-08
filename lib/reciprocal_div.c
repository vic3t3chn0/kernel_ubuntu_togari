#include <asm/div64.h>
#include <linux/reciprocal_div.h>
<<<<<<< HEAD
#include <linux/export.h>
=======
<<<<<<< HEAD
#include <linux/export.h>
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

u32 reciprocal_value(u32 k)
{
	u64 val = (1LL << 32) + (k - 1);
	do_div(val, k);
	return (u32)val;
}
<<<<<<< HEAD
EXPORT_SYMBOL(reciprocal_value);
=======
<<<<<<< HEAD
EXPORT_SYMBOL(reciprocal_value);
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
