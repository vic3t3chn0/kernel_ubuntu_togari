#ifndef _VME_BRIDGE_H_
#define _VME_BRIDGE_H_

#define VME_CRCSR_BUF_SIZE (508*1024)
<<<<<<< HEAD
<<<<<<< HEAD
=======
#define VME_SLOTS_MAX 32
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
#define VME_SLOTS_MAX 32
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/*
 * Resource structures
 */
struct vme_master_resource {
	struct list_head list;
	struct vme_bridge *parent;
	/*
	 * We are likely to need to access the VME bus in interrupt context, so
	 * protect master routines with a spinlock rather than a mutex.
	 */
	spinlock_t lock;
	int locked;
	int number;
<<<<<<< HEAD
<<<<<<< HEAD
	u32 address_attr;
	u32 cycle_attr;
	u32 width_attr;
=======
	vme_address_t address_attr;
	vme_cycle_t cycle_attr;
	vme_width_t width_attr;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	vme_address_t address_attr;
	vme_cycle_t cycle_attr;
	vme_width_t width_attr;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct resource bus_resource;
	void __iomem *kern_base;
};

struct vme_slave_resource {
	struct list_head list;
	struct vme_bridge *parent;
	struct mutex mtx;
	int locked;
	int number;
<<<<<<< HEAD
<<<<<<< HEAD
	u32 address_attr;
	u32 cycle_attr;
=======
	vme_address_t address_attr;
	vme_cycle_t cycle_attr;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	vme_address_t address_attr;
	vme_cycle_t cycle_attr;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

struct vme_dma_pattern {
	u32 pattern;
<<<<<<< HEAD
<<<<<<< HEAD
	u32 type;
=======
	vme_pattern_t type;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	vme_pattern_t type;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

struct vme_dma_pci {
	dma_addr_t address;
};

struct vme_dma_vme {
	unsigned long long address;
<<<<<<< HEAD
<<<<<<< HEAD
	u32 aspace;
	u32 cycle;
	u32 dwidth;
=======
	vme_address_t aspace;
	vme_cycle_t cycle;
	vme_width_t dwidth;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	vme_address_t aspace;
	vme_cycle_t cycle;
	vme_width_t dwidth;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

struct vme_dma_list {
	struct list_head list;
	struct vme_dma_resource *parent;
	struct list_head entries;
	struct mutex mtx;
};

struct vme_dma_resource {
	struct list_head list;
	struct vme_bridge *parent;
	struct mutex mtx;
	int locked;
	int number;
	struct list_head pending;
	struct list_head running;
<<<<<<< HEAD
<<<<<<< HEAD
	u32 route_attr;
=======
	vme_dma_route_t route_attr;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	vme_dma_route_t route_attr;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

struct vme_lm_resource {
	struct list_head list;
	struct vme_bridge *parent;
	struct mutex mtx;
	int locked;
	int number;
	int monitors;
};

struct vme_bus_error {
	struct list_head list;
	unsigned long long address;
	u32 attributes;
};

struct vme_callback {
	void (*func)(int, int, void*);
	void *priv_data;
};

struct vme_irq {
	int count;
	struct vme_callback callback[255];
};

/* Allow 16 characters for name (including null character) */
#define VMENAMSIZ 16

/* This structure stores all the information about one bridge
 * The structure should be dynamically allocated by the driver and one instance
 * of the structure should be present for each VME chip present in the system.
<<<<<<< HEAD
<<<<<<< HEAD
=======
 *
 * Currently we assume that all chips are PCI-based
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 *
 * Currently we assume that all chips are PCI-based
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
struct vme_bridge {
	char name[VMENAMSIZ];
	int num;
	struct list_head master_resources;
	struct list_head slave_resources;
	struct list_head dma_resources;
	struct list_head lm_resources;

	struct list_head vme_errors;	/* List for errors generated on VME */
<<<<<<< HEAD
<<<<<<< HEAD
	struct list_head devices;	/* List of devices on this bridge */

	/* Bridge Info - XXX Move to private structure? */
	struct device *parent;	/* Parent device (eg. pdev->dev for PCI) */
	void *driver_priv;	/* Private pointer for the bridge driver */
	struct list_head bus_list; /* list of VME buses */
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	/* Bridge Info - XXX Move to private structure? */
	struct device *parent;	/* Generic device struct (pdev->dev for PCI) */
	void *driver_priv;	/* Private pointer for the bridge driver */

	struct device dev[VME_SLOTS_MAX];	/* Device registered with
						 * device model on VME bus
						 */
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	/* Interrupt callbacks */
	struct vme_irq irq[7];
	/* Locking for VME irq callback configuration */
	struct mutex irq_mtx;

	/* Slave Functions */
	int (*slave_get) (struct vme_slave_resource *, int *,
		unsigned long long *, unsigned long long *, dma_addr_t *,
<<<<<<< HEAD
<<<<<<< HEAD
		u32 *, u32 *);
	int (*slave_set) (struct vme_slave_resource *, int, unsigned long long,
		unsigned long long, dma_addr_t, u32, u32);

	/* Master Functions */
	int (*master_get) (struct vme_master_resource *, int *,
		unsigned long long *, unsigned long long *, u32 *, u32 *,
		u32 *);
	int (*master_set) (struct vme_master_resource *, int,
		unsigned long long, unsigned long long,  u32, u32, u32);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		vme_address_t *, vme_cycle_t *);
	int (*slave_set) (struct vme_slave_resource *, int, unsigned long long,
		unsigned long long, dma_addr_t, vme_address_t, vme_cycle_t);

	/* Master Functions */
	int (*master_get) (struct vme_master_resource *, int *,
		unsigned long long *, unsigned long long *, vme_address_t *,
		vme_cycle_t *, vme_width_t *);
	int (*master_set) (struct vme_master_resource *, int,
		unsigned long long, unsigned long long,  vme_address_t,
		vme_cycle_t, vme_width_t);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	ssize_t (*master_read) (struct vme_master_resource *, void *, size_t,
		loff_t);
	ssize_t (*master_write) (struct vme_master_resource *, void *, size_t,
		loff_t);
	unsigned int (*master_rmw) (struct vme_master_resource *, unsigned int,
		unsigned int, unsigned int, loff_t);

	/* DMA Functions */
	int (*dma_list_add) (struct vme_dma_list *, struct vme_dma_attr *,
		struct vme_dma_attr *, size_t);
	int (*dma_list_exec) (struct vme_dma_list *);
	int (*dma_list_empty) (struct vme_dma_list *);

	/* Interrupt Functions */
	void (*irq_set) (struct vme_bridge *, int, int, int);
	int (*irq_generate) (struct vme_bridge *, int, int);

	/* Location monitor functions */
<<<<<<< HEAD
<<<<<<< HEAD
	int (*lm_set) (struct vme_lm_resource *, unsigned long long, u32, u32);
	int (*lm_get) (struct vme_lm_resource *, unsigned long long *, u32 *,
		u32 *);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int (*lm_set) (struct vme_lm_resource *, unsigned long long,
		vme_address_t, vme_cycle_t);
	int (*lm_get) (struct vme_lm_resource *, unsigned long long *,
		vme_address_t *, vme_cycle_t *);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int (*lm_attach) (struct vme_lm_resource *, int, void (*callback)(int));
	int (*lm_detach) (struct vme_lm_resource *, int);

	/* CR/CSR space functions */
	int (*slot_get) (struct vme_bridge *);
<<<<<<< HEAD
<<<<<<< HEAD

	/* Bridge parent interface */
	void *(*alloc_consistent)(struct device *dev, size_t size,
		dma_addr_t *dma);
	void (*free_consistent)(struct device *dev, size_t size,
		void *vaddr, dma_addr_t dma);
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

void vme_irq_handler(struct vme_bridge *, int, int);

int vme_register_bridge(struct vme_bridge *);
void vme_unregister_bridge(struct vme_bridge *);

#endif /* _VME_BRIDGE_H_ */
