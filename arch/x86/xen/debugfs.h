#ifndef _XEN_DEBUGFS_H
#define _XEN_DEBUGFS_H

struct dentry * __init xen_init_debugfs(void);

<<<<<<< HEAD
struct dentry *xen_debugfs_create_u32_array(const char *name, umode_t mode,
=======
<<<<<<< HEAD
struct dentry *xen_debugfs_create_u32_array(const char *name, umode_t mode,
=======
struct dentry *xen_debugfs_create_u32_array(const char *name, mode_t mode,
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
					    struct dentry *parent,
					    u32 *array, unsigned elements);

#endif /* _XEN_DEBUGFS_H */
