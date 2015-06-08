#!/bin/sh
# Needed for systems without gettext
<<<<<<< HEAD
$* -xc -o /dev/null - > /dev/null 2>&1 << EOF
=======
<<<<<<< HEAD
$* -xc -o /dev/null - > /dev/null 2>&1 << EOF
=======
$* -x c -o /dev/null - > /dev/null 2>&1 << EOF
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <libintl.h>
int main()
{
	gettext("");
	return 0;
}
EOF
if [ ! "$?" -eq "0"  ]; then
	echo -DKBUILD_NO_NLS;
fi

