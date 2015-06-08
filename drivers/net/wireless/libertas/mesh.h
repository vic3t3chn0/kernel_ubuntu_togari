/*
 * Contains all definitions needed for the Libertas' MESH implementation.
 */
#ifndef _LBS_MESH_H_
#define _LBS_MESH_H_


#include <net/iw_handler.h>
#include <net/lib80211.h>

#include "host.h"
<<<<<<< HEAD
<<<<<<< HEAD
#include "dev.h"

#ifdef CONFIG_LIBERTAS_MESH

struct net_device;

int lbs_init_mesh(struct lbs_private *priv);
void lbs_start_mesh(struct lbs_private *priv);
int lbs_deinit_mesh(struct lbs_private *priv);

void lbs_remove_mesh(struct lbs_private *priv);

static inline bool lbs_mesh_activated(struct lbs_private *priv)
{
	/* Mesh SSID is only programmed after successful init */
	return priv->mesh_ssid_len != 0;
}

int lbs_mesh_set_channel(struct lbs_private *priv, u8 channel);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#ifdef CONFIG_LIBERTAS_MESH

/* Mesh statistics */
struct lbs_mesh_stats {
	u32	fwd_bcast_cnt;		/* Fwd: Broadcast counter */
	u32	fwd_unicast_cnt;	/* Fwd: Unicast counter */
	u32	fwd_drop_ttl;		/* Fwd: TTL zero */
	u32	fwd_drop_rbt;		/* Fwd: Recently Broadcasted */
	u32	fwd_drop_noroute; 	/* Fwd: No route to Destination */
	u32	fwd_drop_nobuf;		/* Fwd: Run out of internal buffers */
	u32	drop_blind;		/* Rx:  Dropped by blinding table */
	u32	tx_failed_cnt;		/* Tx:  Failed transmissions */
};


struct net_device;
struct lbs_private;

int lbs_init_mesh(struct lbs_private *priv);
int lbs_deinit_mesh(struct lbs_private *priv);

int lbs_add_mesh(struct lbs_private *priv);
void lbs_remove_mesh(struct lbs_private *priv);

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/* Sending / Receiving */

struct rxpd;
struct txpd;

struct net_device *lbs_mesh_set_dev(struct lbs_private *priv,
	struct net_device *dev, struct rxpd *rxpd);
void lbs_mesh_set_txpd(struct lbs_private *priv,
	struct net_device *dev, struct txpd *txpd);


/* Command handling */

struct cmd_ds_command;
struct cmd_ds_mesh_access;
struct cmd_ds_mesh_config;

<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
int lbs_mesh_bt_add_del(struct lbs_private *priv, bool add, u8 *addr1);
int lbs_mesh_bt_reset(struct lbs_private *priv);
int lbs_mesh_bt_get_inverted(struct lbs_private *priv, bool *inverted);
int lbs_mesh_bt_set_inverted(struct lbs_private *priv, bool inverted);
int lbs_mesh_bt_get_entry(struct lbs_private *priv, u32 id, u8 *addr1);

int lbs_cmd_fwt_access(struct lbs_private *priv, u16 cmd_action,
			struct cmd_ds_fwt_access *cmd);

int lbs_mesh_access(struct lbs_private *priv, uint16_t cmd_action,
		    struct cmd_ds_mesh_access *cmd);
int lbs_mesh_config_send(struct lbs_private *priv,
			 struct cmd_ds_mesh_config *cmd,
			 uint16_t action, uint16_t type);
int lbs_mesh_config(struct lbs_private *priv, uint16_t enable, uint16_t chan);



/* Persistent configuration */

void lbs_persist_config_init(struct net_device *net);
void lbs_persist_config_remove(struct net_device *net);

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/* Ethtool statistics */

struct ethtool_stats;

void lbs_mesh_ethtool_get_stats(struct net_device *dev,
	struct ethtool_stats *stats, uint64_t *data);
int lbs_mesh_ethtool_get_sset_count(struct net_device *dev, int sset);
void lbs_mesh_ethtool_get_strings(struct net_device *dev,
	uint32_t stringset, uint8_t *s);


<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/* Accessors */

#define lbs_mesh_open(priv) (priv->mesh_open)
#define lbs_mesh_connected(priv) (priv->mesh_connect_status == LBS_CONNECTED)

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#else

#define lbs_init_mesh(priv)
#define lbs_deinit_mesh(priv)
<<<<<<< HEAD
<<<<<<< HEAD
#define lbs_start_mesh(priv)
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#define lbs_add_mesh(priv)
#define lbs_remove_mesh(priv)
#define lbs_mesh_set_dev(priv, dev, rxpd) (dev)
#define lbs_mesh_set_txpd(priv, dev, txpd)
<<<<<<< HEAD
<<<<<<< HEAD
#define lbs_mesh_set_channel(priv, channel) (0)
#define lbs_mesh_activated(priv) (false)
=======
#define lbs_mesh_config(priv, enable, chan)
#define lbs_mesh_open(priv) (0)
#define lbs_mesh_connected(priv) (0)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
#define lbs_mesh_config(priv, enable, chan)
#define lbs_mesh_open(priv) (0)
#define lbs_mesh_connected(priv) (0)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#endif



#endif
