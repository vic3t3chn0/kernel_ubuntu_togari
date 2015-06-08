/*
 * CAPI encode/decode prototypes and defines
 *
 * Copyright (C) 1996 Universidade de Lisboa
<<<<<<< HEAD
<<<<<<< HEAD
 *
 * Written by Pedro Roque Marques (roque@di.fc.ul.pt)
 *
 * This software may be used and distributed according to the terms of
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * 
 * Written by Pedro Roque Marques (roque@di.fc.ul.pt)
 *
 * This software may be used and distributed according to the terms of 
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * the GNU General Public License, incorporated herein by reference.
 */

#ifndef CAPI_H
#define CAPI_H


#define REQ_CAUSE         0x01
#define REQ_DISPLAY       0x04
<<<<<<< HEAD
<<<<<<< HEAD
#define REQ_USER_TO_USER  0x08

#define AppInfoMask  REQ_CAUSE | REQ_DISPLAY | REQ_USER_TO_USER

/* Connection Setup */
extern int capi_conn_req(const char *calledPN, struct sk_buff **buf,
			 int proto);
extern int capi_decode_conn_conf(struct pcbit_chan *chan, struct sk_buff *skb,
				 int *complete);

extern int capi_decode_conn_ind(struct pcbit_chan *chan, struct sk_buff *skb,
				struct callb_data *info);
extern int capi_conn_resp(struct pcbit_chan *chan, struct sk_buff **skb);

extern int capi_conn_active_req(struct pcbit_chan *chan, struct sk_buff **skb);
extern int capi_decode_conn_actv_conf(struct pcbit_chan *chan,
				      struct sk_buff *skb);

extern int capi_decode_conn_actv_ind(struct pcbit_chan *chan,
				     struct sk_buff *skb);
extern int capi_conn_active_resp(struct pcbit_chan *chan,
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#define REQ_USER_TO_USER  0x08 

#define AppInfoMask  REQ_CAUSE|REQ_DISPLAY|REQ_USER_TO_USER 

/* Connection Setup */
extern int capi_conn_req(const char * calledPN, struct sk_buff **buf,
			 int proto);
extern int capi_decode_conn_conf(struct pcbit_chan * chan, struct sk_buff *skb,
				 int *complete); 

extern int capi_decode_conn_ind(struct pcbit_chan * chan, struct sk_buff *skb,
				struct callb_data *info);
extern int capi_conn_resp(struct pcbit_chan* chan, struct sk_buff **skb);

extern int capi_conn_active_req(struct pcbit_chan* chan, struct sk_buff **skb);
extern int capi_decode_conn_actv_conf(struct pcbit_chan * chan, 
				      struct sk_buff *skb);

extern int capi_decode_conn_actv_ind(struct pcbit_chan * chan, 
				     struct sk_buff *skb);
extern int capi_conn_active_resp(struct pcbit_chan* chan, 
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
				 struct sk_buff **skb);

/* Data */
extern int capi_select_proto_req(struct pcbit_chan *chan, struct sk_buff **skb,
				 int outgoing);
<<<<<<< HEAD
<<<<<<< HEAD
extern int capi_decode_sel_proto_conf(struct pcbit_chan *chan,
				      struct sk_buff *skb);

extern int capi_activate_transp_req(struct pcbit_chan *chan,
				    struct sk_buff **skb);
extern int capi_decode_actv_trans_conf(struct pcbit_chan *chan,
				       struct sk_buff *skb);

extern int capi_tdata_req(struct pcbit_chan *chan, struct sk_buff *skb);
extern int capi_tdata_resp(struct pcbit_chan *chan, struct sk_buff **skb);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
extern int capi_decode_sel_proto_conf(struct pcbit_chan *chan, 
				      struct sk_buff *skb);

extern int capi_activate_transp_req(struct pcbit_chan *chan, 
				    struct sk_buff **skb);
extern int capi_decode_actv_trans_conf(struct pcbit_chan *chan, 
				       struct sk_buff *skb);

extern int capi_tdata_req(struct pcbit_chan* chan, struct sk_buff *skb);
extern int capi_tdata_resp(struct pcbit_chan *chan, struct sk_buff ** skb);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/* Connection Termination */
extern int capi_disc_req(ushort callref, struct sk_buff **skb, u_char cause);

extern int capi_decode_disc_ind(struct pcbit_chan *chan, struct sk_buff *skb);
extern int capi_disc_resp(struct pcbit_chan *chan, struct sk_buff **skb);

#ifdef DEBUG
extern int capi_decode_debug_188(u_char *hdr, ushort hdrlen);
#endif

<<<<<<< HEAD
<<<<<<< HEAD
static inline struct pcbit_chan *
=======
static inline struct pcbit_chan * 
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static inline struct pcbit_chan * 
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
capi_channel(struct pcbit_dev *dev, struct sk_buff *skb)
{
	ushort callref;

<<<<<<< HEAD
<<<<<<< HEAD
	callref = *((ushort *)skb->data);
=======
	callref = *((ushort*) skb->data);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	callref = *((ushort*) skb->data);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	skb_pull(skb, 2);

	if (dev->b1->callref == callref)
		return dev->b1;
	else if (dev->b2->callref == callref)
		return dev->b2;

	return NULL;
}

#endif
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2






<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
