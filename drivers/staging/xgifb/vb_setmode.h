#ifndef _VBSETMODE_
#define _VBSETMODE_

extern void InitTo330Pointer(unsigned char, struct vb_device_info *);
extern void XGI_UnLockCRT2(struct xgi_hw_device_info *HwDeviceExtension,
			   struct vb_device_info *);
extern void XGI_LockCRT2(struct xgi_hw_device_info *HwDeviceExtension,
			 struct vb_device_info *);
<<<<<<< HEAD
extern void XGI_DisplayOff(struct xgifb_video_info *,
			   struct xgi_hw_device_info *,
			   struct vb_device_info *);
extern void XGI_GetVBType(struct vb_device_info *);
extern void XGI_SenseCRT1(struct vb_device_info *);
extern unsigned char XGISetModeNew(struct xgifb_video_info *xgifb_info,
				   struct xgi_hw_device_info *HwDeviceExtension,
=======
extern void XGI_LongWait(struct vb_device_info *);
extern void XGI_SetCRT2ModeRegs(unsigned short ModeNo,
				struct xgi_hw_device_info *,
				struct vb_device_info *);
extern void XGI_DisableBridge(struct xgi_hw_device_info *HwDeviceExtension,
			      struct vb_device_info *);
extern void XGI_EnableBridge(struct xgi_hw_device_info *HwDeviceExtension,
			     struct vb_device_info *);
extern void XGI_DisplayOff(struct xgi_hw_device_info *,
			   struct vb_device_info *);
extern void XGI_DisplayOn(struct xgi_hw_device_info *,
			  struct vb_device_info *);
extern void XGI_GetVBType(struct vb_device_info *);
extern void XGI_SenseCRT1(struct vb_device_info *);
extern void XGI_GetVGAType(struct xgi_hw_device_info *HwDeviceExtension,
			   struct vb_device_info *);
extern void XGI_GetVBInfo(unsigned short ModeNo,
			  unsigned short ModeIdIndex,
			  struct xgi_hw_device_info *HwDeviceExtension,
			  struct vb_device_info *);
extern void XGI_GetTVInfo(unsigned short ModeNo,
			  unsigned short ModeIdIndex,
			  struct vb_device_info *);
extern unsigned short XGI_GetResInfo(unsigned short ModeNo,
				     unsigned short ModeIdIndex,
				     struct vb_device_info *pVBInfo);

extern unsigned char XGISetModeNew(struct xgi_hw_device_info *HwDeviceExtension,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
				   unsigned short ModeNo) ;

extern unsigned char XGI_SearchModeID(unsigned short ModeNo,
				      unsigned short *ModeIdIndex,
				      struct vb_device_info *);
<<<<<<< HEAD
extern unsigned char XGI_BridgeIsOn(struct vb_device_info *);
=======
extern unsigned char XGI_GetLCDInfo(unsigned short ModeNo,
				    unsigned short ModeIdIndex,
				    struct vb_device_info *);
extern unsigned char XGI_BridgeIsOn(struct vb_device_info *);

extern unsigned char
XGI_SetCRT2Group301(unsigned short ModeNo,
		    struct xgi_hw_device_info *HwDeviceExtension,
		    struct vb_device_info *);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
extern unsigned short XGI_GetRatePtrCRT2(struct xgi_hw_device_info *pXGIHWDE,
					 unsigned short ModeNo,
					 unsigned short ModeIdIndex,
					 struct vb_device_info *);

<<<<<<< HEAD
=======
extern void XGI_SetXG21FPBits(struct vb_device_info *pVBInfo);
extern void XGI_SetXG27FPBits(struct vb_device_info *pVBInfo);
extern void XGI_XG21BLSignalVDD(unsigned short tempbh,
				unsigned short tempbl,
				struct vb_device_info *pVBInfo);
extern void XGI_XG27BLSignalVDD(unsigned short tempbh,
				unsigned short tempbl,
				struct vb_device_info *pVBInfo);
extern void XGI_XG21SetPanelDelay(unsigned short tempbl,
				  struct vb_device_info *pVBInfo);
extern unsigned char XGI_XG21CheckLVDSMode(unsigned short ModeNo,
					   unsigned short ModeIdIndex,
					   struct vb_device_info *pVBInfo);
extern unsigned short XGI_GetLVDSOEMTableIndex(struct vb_device_info *pVBInfo);

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
#endif
