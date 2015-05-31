/*
 * MTD partitioning layer definitions
 *
 * (C) 2000 Nicolas Pitre <nico@fluxnic.net>
 *
 * This code is GPL
 */

#ifndef MTD_PARTITIONS_H
#define MTD_PARTITIONS_H

#include <linux/types.h>


/*
 * Partition definition structure:
 *
 * An array of struct partition is passed along with a MTD object to
 * mtd_device_register() to create them.
 *
 * For each partition, these fields are available:
 * name: string that will be used to label the partition's MTD device.
 * size: the partition size; if defined as MTDPART_SIZ_FULL, the partition
 * 	will extend to the end of the master MTD device.
 * offset: absolute starting position within the master MTD device; if
 * 	defined as MTDPART_OFS_APPEND, the partition will start where the
<<<<<<< HEAD
 *	previous one ended; if MTDPART_OFS_NXTBLK, at the next erase block;
 *	if MTDPART_OFS_RETAIN, consume as much as possible, leaving size
 *	after the end of partition.
=======
 * 	previous one ended; if MTDPART_OFS_NXTBLK, at the next erase block.
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
 * mask_flags: contains flags that have to be masked (removed) from the
 * 	master MTD flag set for the corresponding MTD partition.
 * 	For example, to force a read-only partition, simply adding
 * 	MTD_WRITEABLE to the mask_flags will do the trick.
 *
 * Note: writeable partitions require their size and offset be
 * erasesize aligned (e.g. use MTDPART_OFS_NEXTBLK).
 */

struct mtd_partition {
	char *name;			/* identifier string */
	uint64_t size;			/* partition size */
	uint64_t offset;		/* offset within the master MTD space */
	uint32_t mask_flags;		/* master MTD flags to mask out for this partition */
	struct nand_ecclayout *ecclayout;	/* out of band layout for this partition (NAND only) */
};

<<<<<<< HEAD
#define MTDPART_OFS_RETAIN	(-3)
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
#define MTDPART_OFS_NXTBLK	(-2)
#define MTDPART_OFS_APPEND	(-1)
#define MTDPART_SIZ_FULL	(0)


struct mtd_info;
<<<<<<< HEAD
struct device_node;

/**
 * struct mtd_part_parser_data - used to pass data to MTD partition parsers.
 * @origin: for RedBoot, start address of MTD device
 * @of_node: for OF parsers, device node containing partitioning information
 */
struct mtd_part_parser_data {
	unsigned long origin;
	struct device_node *of_node;
};


void part_fill_badblockstats(struct mtd_info *mtd);
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

/*
 * Functions dealing with the various ways of partitioning the space
 */

struct mtd_part_parser {
	struct list_head list;
	struct module *owner;
	const char *name;
<<<<<<< HEAD
	int (*parse_fn)(struct mtd_info *, struct mtd_partition **,
			struct mtd_part_parser_data *);
=======
	int (*parse_fn)(struct mtd_info *, struct mtd_partition **, unsigned long);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
};

extern int register_mtd_parser(struct mtd_part_parser *parser);
extern int deregister_mtd_parser(struct mtd_part_parser *parser);
<<<<<<< HEAD
=======
extern int parse_mtd_partitions(struct mtd_info *master, const char **types,
				struct mtd_partition **pparts, unsigned long origin);

#define put_partition_parser(p) do { module_put((p)->owner); } while(0)

struct device;
struct device_node;

#ifdef CONFIG_MTD_OF_PARTS
int __devinit of_mtd_parse_partitions(struct device *dev,
                                      struct device_node *node,
                                      struct mtd_partition **pparts);
#else
static inline int of_mtd_parse_partitions(struct device *dev,
					  struct device_node *node,
					  struct mtd_partition **pparts)
{
	return 0;
}
#endif

#ifdef CONFIG_MTD_CMDLINE_PARTS
static inline int mtd_has_cmdlinepart(void) { return 1; }
#else
static inline int mtd_has_cmdlinepart(void) { return 0; }
#endif
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

int mtd_is_partition(struct mtd_info *mtd);
int mtd_add_partition(struct mtd_info *master, char *name,
		      long long offset, long long length);
int mtd_del_partition(struct mtd_info *master, int partno);

#endif
