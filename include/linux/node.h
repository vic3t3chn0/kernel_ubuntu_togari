/*
 * include/linux/node.h - generic node definition
 *
 * This is mainly for topological representation. We define the 
 * basic 'struct node' here, which can be embedded in per-arch 
 * definitions of processors.
 *
 * Basic handling of the devices is done in drivers/base/node.c
 * and system devices are handled in drivers/base/sys.c. 
 *
 * Nodes are exported via driverfs in the class/node/devices/
 * directory. 
 */
#ifndef _LINUX_NODE_H_
#define _LINUX_NODE_H_

<<<<<<< HEAD
#include <linux/device.h>
=======
<<<<<<< HEAD
#include <linux/device.h>
=======
#include <linux/sysdev.h>
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <linux/cpumask.h>
#include <linux/workqueue.h>

struct node {
<<<<<<< HEAD
	struct device	dev;
=======
<<<<<<< HEAD
	struct device	dev;
=======
	struct sys_device	sysdev;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#if defined(CONFIG_MEMORY_HOTPLUG_SPARSE) && defined(CONFIG_HUGETLBFS)
	struct work_struct	node_work;
#endif
};

struct memory_block;
extern struct node node_devices[];
typedef  void (*node_registration_func_t)(struct node *);

extern int register_node(struct node *, int, struct node *);
extern void unregister_node(struct node *node);
#ifdef CONFIG_NUMA
extern int register_one_node(int nid);
extern void unregister_one_node(int nid);
extern int register_cpu_under_node(unsigned int cpu, unsigned int nid);
extern int unregister_cpu_under_node(unsigned int cpu, unsigned int nid);
extern int register_mem_sect_under_node(struct memory_block *mem_blk,
						int nid);
extern int unregister_mem_sect_under_nodes(struct memory_block *mem_blk,
					   unsigned long phys_index);

#ifdef CONFIG_HUGETLBFS
extern void register_hugetlbfs_with_node(node_registration_func_t doregister,
					 node_registration_func_t unregister);
#endif
#else
static inline int register_one_node(int nid)
{
	return 0;
}
static inline int unregister_one_node(int nid)
{
	return 0;
}
static inline int register_cpu_under_node(unsigned int cpu, unsigned int nid)
{
	return 0;
}
static inline int unregister_cpu_under_node(unsigned int cpu, unsigned int nid)
{
	return 0;
}
static inline int register_mem_sect_under_node(struct memory_block *mem_blk,
							int nid)
{
	return 0;
}
static inline int unregister_mem_sect_under_nodes(struct memory_block *mem_blk,
						  unsigned long phys_index)
{
	return 0;
}

static inline void register_hugetlbfs_with_node(node_registration_func_t reg,
						node_registration_func_t unreg)
{
}
#endif

<<<<<<< HEAD
#define to_node(device) container_of(device, struct node, dev)
=======
<<<<<<< HEAD
#define to_node(device) container_of(device, struct node, dev)
=======
#define to_node(sys_device) container_of(sys_device, struct node, sysdev)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#endif /* _LINUX_NODE_H_ */
