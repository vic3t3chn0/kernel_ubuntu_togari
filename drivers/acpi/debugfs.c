/*
 * debugfs.c - ACPI debugfs interface to userspace.
 */

<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/export.h>
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <linux/init.h>
#include <linux/debugfs.h>
#include <acpi/acpi_drivers.h>

#define _COMPONENT		ACPI_SYSTEM_COMPONENT
ACPI_MODULE_NAME("debugfs");

struct dentry *acpi_debugfs_dir;
EXPORT_SYMBOL_GPL(acpi_debugfs_dir);

void __init acpi_debugfs_init(void)
{
	acpi_debugfs_dir = debugfs_create_dir("acpi", NULL);
}
