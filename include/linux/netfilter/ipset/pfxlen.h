#ifndef _PFXLEN_H
#define _PFXLEN_H

#include <asm/byteorder.h>
<<<<<<< HEAD
#include <linux/netfilter.h>
#include <net/tcp.h>
=======
#include <linux/netfilter.h> 
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

/* Prefixlen maps, by Jan Engelhardt  */
extern const union nf_inet_addr ip_set_netmask_map[];
extern const union nf_inet_addr ip_set_hostmask_map[];

static inline __be32
ip_set_netmask(u8 pfxlen)
{
	return ip_set_netmask_map[pfxlen].ip;
}

static inline const __be32 *
ip_set_netmask6(u8 pfxlen)
{
	return &ip_set_netmask_map[pfxlen].ip6[0];
}

static inline u32
ip_set_hostmask(u8 pfxlen)
{
	return (__force u32) ip_set_hostmask_map[pfxlen].ip;
}

static inline const __be32 *
ip_set_hostmask6(u8 pfxlen)
{
	return &ip_set_hostmask_map[pfxlen].ip6[0];
}

<<<<<<< HEAD
extern u32 ip_set_range_to_cidr(u32 from, u32 to, u8 *cidr);

#define ip_set_mask_from_to(from, to, cidr)	\
do {						\
	from &= ip_set_hostmask(cidr);		\
	to = from | ~ip_set_hostmask(cidr);	\
} while (0)

=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
#endif /*_PFXLEN_H */
