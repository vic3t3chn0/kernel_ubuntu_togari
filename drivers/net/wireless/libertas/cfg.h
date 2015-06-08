#ifndef __LBS_CFG80211_H__
#define __LBS_CFG80211_H__

struct device;
struct lbs_private;
struct regulatory_request;
struct wiphy;

struct wireless_dev *lbs_cfg_alloc(struct device *dev);
int lbs_cfg_register(struct lbs_private *priv);
void lbs_cfg_free(struct lbs_private *priv);

int lbs_reg_notifier(struct wiphy *wiphy,
		struct regulatory_request *request);

void lbs_send_disconnect_notification(struct lbs_private *priv);
void lbs_send_mic_failureevent(struct lbs_private *priv, u32 event);

<<<<<<< HEAD
<<<<<<< HEAD
void lbs_scan_done(struct lbs_private *priv);
void lbs_scan_deinit(struct lbs_private *priv);
int lbs_disconnect(struct lbs_private *priv, u16 reason);
=======
void lbs_scan_deinit(struct lbs_private *priv);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
void lbs_scan_deinit(struct lbs_private *priv);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#endif
