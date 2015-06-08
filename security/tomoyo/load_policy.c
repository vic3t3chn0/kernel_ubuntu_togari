/*
 * security/tomoyo/load_policy.c
 *
<<<<<<< HEAD
 * Copyright (C) 2005-2011  NTT DATA CORPORATION
=======
<<<<<<< HEAD
 * Copyright (C) 2005-2011  NTT DATA CORPORATION
=======
 * Policy loader launcher for TOMOYO.
 *
 * Copyright (C) 2005-2010  NTT DATA CORPORATION
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */

#include "common.h"

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#ifndef CONFIG_SECURITY_TOMOYO_OMIT_USERSPACE_LOADER

/*
 * Path to the policy loader. (default = CONFIG_SECURITY_TOMOYO_POLICY_LOADER)
 */
static const char *tomoyo_loader;

/**
 * tomoyo_loader_setup - Set policy loader.
 *
 * @str: Program to use as a policy loader (e.g. /sbin/tomoyo-init ).
 *
 * Returns 0.
 */
static int __init tomoyo_loader_setup(char *str)
{
	tomoyo_loader = str;
	return 0;
}

__setup("TOMOYO_loader=", tomoyo_loader_setup);
<<<<<<< HEAD
=======
=======
/* path to policy loader */
static const char *tomoyo_loader = "/sbin/tomoyo-init";
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/**
 * tomoyo_policy_loader_exists - Check whether /sbin/tomoyo-init exists.
 *
 * Returns true if /sbin/tomoyo-init exists, false otherwise.
 */
static bool tomoyo_policy_loader_exists(void)
{
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct path path;
	if (!tomoyo_loader)
		tomoyo_loader = CONFIG_SECURITY_TOMOYO_POLICY_LOADER;
	if (kern_path(tomoyo_loader, LOOKUP_FOLLOW, &path)) {
		printk(KERN_INFO "Not activating Mandatory Access Control "
		       "as %s does not exist.\n", tomoyo_loader);
<<<<<<< HEAD
=======
=======
	/*
	 * Don't activate MAC if the policy loader doesn't exist.
	 * If the initrd includes /sbin/init but real-root-dev has not
	 * mounted on / yet, activating MAC will block the system since
	 * policies are not loaded yet.
	 * Thus, let do_execve() call this function every time.
	 */
	struct path path;

	if (kern_path(tomoyo_loader, LOOKUP_FOLLOW, &path)) {
		printk(KERN_INFO "Not activating Mandatory Access Control now "
		       "since %s doesn't exist.\n", tomoyo_loader);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return false;
	}
	path_put(&path);
	return true;
}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/*
 * Path to the trigger. (default = CONFIG_SECURITY_TOMOYO_ACTIVATION_TRIGGER)
 */
static const char *tomoyo_trigger;

/**
 * tomoyo_trigger_setup - Set trigger for activation.
 *
 * @str: Program to use as an activation trigger (e.g. /sbin/init ).
 *
 * Returns 0.
 */
static int __init tomoyo_trigger_setup(char *str)
{
	tomoyo_trigger = str;
	return 0;
}

__setup("TOMOYO_trigger=", tomoyo_trigger_setup);

<<<<<<< HEAD
=======
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/**
 * tomoyo_load_policy - Run external policy loader to load policy.
 *
 * @filename: The program about to start.
 *
 * This function checks whether @filename is /sbin/init , and if so
 * invoke /sbin/tomoyo-init and wait for the termination of /sbin/tomoyo-init
 * and then continues invocation of /sbin/init.
 * /sbin/tomoyo-init reads policy files in /etc/tomoyo/ directory and
 * writes to /sys/kernel/security/tomoyo/ interfaces.
 *
 * Returns nothing.
 */
void tomoyo_load_policy(const char *filename)
{
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	static bool done;
	char *argv[2];
	char *envp[3];

	if (tomoyo_policy_loaded || done)
		return;
	if (!tomoyo_trigger)
		tomoyo_trigger = CONFIG_SECURITY_TOMOYO_ACTIVATION_TRIGGER;
	if (strcmp(filename, tomoyo_trigger))
		return;
	if (!tomoyo_policy_loader_exists())
		return;
	done = true;
<<<<<<< HEAD
=======
=======
	char *argv[2];
	char *envp[3];

	if (tomoyo_policy_loaded)
		return;
	/*
	 * Check filename is /sbin/init or /sbin/tomoyo-start.
	 * /sbin/tomoyo-start is a dummy filename in case where /sbin/init can't
	 * be passed.
	 * You can create /sbin/tomoyo-start by
	 * "ln -s /bin/true /sbin/tomoyo-start".
	 */
	if (strcmp(filename, "/sbin/init") &&
	    strcmp(filename, "/sbin/tomoyo-start"))
		return;
	if (!tomoyo_policy_loader_exists())
		return;

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	printk(KERN_INFO "Calling %s to load policy. Please wait.\n",
	       tomoyo_loader);
	argv[0] = (char *) tomoyo_loader;
	argv[1] = NULL;
	envp[0] = "HOME=/";
	envp[1] = "PATH=/sbin:/bin:/usr/sbin:/usr/bin";
	envp[2] = NULL;
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	call_usermodehelper(argv[0], argv, envp, UMH_WAIT_PROC);
	tomoyo_check_profile();
}

#endif
<<<<<<< HEAD
=======
=======
	call_usermodehelper(argv[0], argv, envp, 1);
	tomoyo_check_profile();
}
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
