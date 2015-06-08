#ifndef __OF_ADDRESS_H
#define __OF_ADDRESS_H
#include <linux/ioport.h>
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <linux/errno.h>
#include <linux/of.h>

#ifdef CONFIG_OF_ADDRESS
extern u64 of_translate_address(struct device_node *np, const __be32 *addr);
extern bool of_can_translate_address(struct device_node *dev);
extern int of_address_to_resource(struct device_node *dev, int index,
				  struct resource *r);
extern struct device_node *of_find_matching_node_by_address(
					struct device_node *from,
					const struct of_device_id *matches,
					u64 base_address);
<<<<<<< HEAD
=======
=======
#include <linux/of.h>

extern u64 of_translate_address(struct device_node *np, const __be32 *addr);
extern int of_address_to_resource(struct device_node *dev, int index,
				  struct resource *r);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
extern void __iomem *of_iomap(struct device_node *device, int index);

/* Extract an address from a device, returns the region size and
 * the address space flags too. The PCI version uses a BAR number
 * instead of an absolute index
 */
extern const u32 *of_get_address(struct device_node *dev, int index,
			   u64 *size, unsigned int *flags);

#ifndef pci_address_to_pio
static inline unsigned long pci_address_to_pio(phys_addr_t addr) { return -1; }
#define pci_address_to_pio pci_address_to_pio
#endif

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#else /* CONFIG_OF_ADDRESS */
static inline int of_address_to_resource(struct device_node *dev, int index,
					 struct resource *r)
{
	return -EINVAL;
}
static inline struct device_node *of_find_matching_node_by_address(
					struct device_node *from,
					const struct of_device_id *matches,
					u64 base_address)
{
	return NULL;
}
static inline void __iomem *of_iomap(struct device_node *device, int index)
{
	return NULL;
}
static inline const u32 *of_get_address(struct device_node *dev, int index,
					u64 *size, unsigned int *flags)
{
	return NULL;
}
#endif /* CONFIG_OF_ADDRESS */


#if defined(CONFIG_OF_ADDRESS) && defined(CONFIG_PCI)
<<<<<<< HEAD
=======
=======
#ifdef CONFIG_PCI
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
extern const __be32 *of_get_pci_address(struct device_node *dev, int bar_no,
			       u64 *size, unsigned int *flags);
extern int of_pci_address_to_resource(struct device_node *dev, int bar,
				      struct resource *r);
<<<<<<< HEAD
#else /* CONFIG_OF_ADDRESS && CONFIG_PCI */
=======
<<<<<<< HEAD
#else /* CONFIG_OF_ADDRESS && CONFIG_PCI */
=======
#else /* CONFIG_PCI */
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static inline int of_pci_address_to_resource(struct device_node *dev, int bar,
				             struct resource *r)
{
	return -ENOSYS;
}

static inline const __be32 *of_get_pci_address(struct device_node *dev,
		int bar_no, u64 *size, unsigned int *flags)
{
	return NULL;
}
<<<<<<< HEAD
#endif /* CONFIG_OF_ADDRESS && CONFIG_PCI */
=======
<<<<<<< HEAD
#endif /* CONFIG_OF_ADDRESS && CONFIG_PCI */
=======
#endif /* CONFIG_PCI */

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#endif /* __OF_ADDRESS_H */

