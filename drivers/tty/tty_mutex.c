#include <linux/tty.h>
#include <linux/module.h>
#include <linux/kallsyms.h>
#include <linux/semaphore.h>
#include <linux/sched.h>

/*
 * The 'big tty mutex'
 *
 * This mutex is taken and released by tty_lock() and tty_unlock(),
 * replacing the older big kernel lock.
 * It can no longer be taken recursively, and does not get
 * released implicitly while sleeping.
 *
 * Don't use in new code.
 */
static DEFINE_MUTEX(big_tty_mutex);
<<<<<<< HEAD
<<<<<<< HEAD
=======
struct task_struct *__big_tty_mutex_owner;
EXPORT_SYMBOL_GPL(__big_tty_mutex_owner);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
struct task_struct *__big_tty_mutex_owner;
EXPORT_SYMBOL_GPL(__big_tty_mutex_owner);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/*
 * Getting the big tty mutex.
 */
void __lockfunc tty_lock(void)
{
<<<<<<< HEAD
<<<<<<< HEAD
	mutex_lock(&big_tty_mutex);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct task_struct *task = current;

	WARN_ON(__big_tty_mutex_owner == task);

	mutex_lock(&big_tty_mutex);
	__big_tty_mutex_owner = task;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}
EXPORT_SYMBOL(tty_lock);

void __lockfunc tty_unlock(void)
{
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct task_struct *task = current;

	WARN_ON(__big_tty_mutex_owner != task);
	__big_tty_mutex_owner = NULL;

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	mutex_unlock(&big_tty_mutex);
}
EXPORT_SYMBOL(tty_unlock);
