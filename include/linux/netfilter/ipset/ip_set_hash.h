#ifndef __IP_SET_HASH_H
#define __IP_SET_HASH_H

/* Hash type specific error codes */
enum {
	/* Hash is full */
	IPSET_ERR_HASH_FULL = IPSET_ERR_TYPE_SPECIFIC,
	/* Null-valued element */
	IPSET_ERR_HASH_ELEM,
	/* Invalid protocol */
	IPSET_ERR_INVALID_PROTO,
	/* Protocol missing but must be specified */
	IPSET_ERR_MISSING_PROTO,
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	/* Range not supported */
	IPSET_ERR_HASH_RANGE_UNSUPPORTED,
	/* Invalid range */
	IPSET_ERR_HASH_RANGE,
<<<<<<< HEAD
=======
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

#ifdef __KERNEL__

#define IPSET_DEFAULT_HASHSIZE		1024
#define IPSET_MIMINAL_HASHSIZE		64
#define IPSET_DEFAULT_MAXELEM		65536
#define IPSET_DEFAULT_PROBES		4
#define IPSET_DEFAULT_RESIZE		100

#endif /* __KERNEL__ */

#endif /* __IP_SET_HASH_H */
