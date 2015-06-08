#include "headers.h"
<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/sort.h>
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/*
 * File Name: sort.c
 *
 * Author: Beceem Communications Pvt. Ltd
 *
 * Abstract: This file contains the routines sorting the classification rules.
 *
 * Copyright (c) 2007 Beceem Communications Pvt. Ltd
 */

<<<<<<< HEAD
<<<<<<< HEAD
static int compare_packet_info(void const *a, void const *b)
{
	PacketInfo const *pa = a;
	PacketInfo const *pb = b;

	if (!pa->bValid || !pb->bValid)
		return 0;

	return pa->u8TrafficPriority - pb->u8TrafficPriority;
}

VOID SortPackInfo(PMINI_ADAPTER Adapter)
{
	BCM_DEBUG_PRINT(Adapter, DBG_TYPE_OTHERS, CONN_MSG,
			DBG_LVL_ALL, "<=======");

	sort(Adapter->PackInfo, NO_OF_QUEUES, sizeof(PacketInfo),
		compare_packet_info, NULL);
}

static int compare_classifiers(void const *a, void const *b)
{
	S_CLASSIFIER_RULE const *pa = a;
	S_CLASSIFIER_RULE const *pb = b;

	if (!pa->bUsed || !pb->bUsed)
		return 0;

	return pa->u8ClassifierRulePriority - pb->u8ClassifierRulePriority;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
VOID SortPackInfo(PMINI_ADAPTER Adapter)
{
	UINT nIndex1;
	UINT nIndex2;

	BCM_DEBUG_PRINT( Adapter,DBG_TYPE_OTHERS, CONN_MSG, DBG_LVL_ALL, "<=======");

	for(nIndex1 = 0; nIndex1 < NO_OF_QUEUES -2 ; nIndex1++)
	{
		for(nIndex2 = nIndex1 + 1 ; nIndex2 < NO_OF_QUEUES -1  ; nIndex2++)
		{
			if(Adapter->PackInfo[nIndex1].bValid && Adapter->PackInfo[nIndex2].bValid)
			{
				if(Adapter->PackInfo[nIndex2].u8TrafficPriority <
						Adapter->PackInfo[nIndex1].u8TrafficPriority)
				{
					PacketInfo stTemppackInfo = Adapter->PackInfo[nIndex2];
					Adapter->PackInfo[nIndex2] = Adapter->PackInfo[nIndex1];
					Adapter->PackInfo[nIndex1] = stTemppackInfo;

				}
			}
		}
	}
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

VOID SortClassifiers(PMINI_ADAPTER Adapter)
{
<<<<<<< HEAD
<<<<<<< HEAD
	BCM_DEBUG_PRINT(Adapter, DBG_TYPE_OTHERS, CONN_MSG,
			DBG_LVL_ALL, "<=======");

	sort(Adapter->astClassifierTable, MAX_CLASSIFIERS,
		sizeof(S_CLASSIFIER_RULE), compare_classifiers, NULL);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	UINT nIndex1;
	UINT nIndex2;

	BCM_DEBUG_PRINT( Adapter,DBG_TYPE_OTHERS, CONN_MSG, DBG_LVL_ALL, "<=======");

	for(nIndex1 = 0; nIndex1 < MAX_CLASSIFIERS -1 ; nIndex1++)
	{
		for(nIndex2 = nIndex1 + 1 ; nIndex2 < MAX_CLASSIFIERS  ; nIndex2++)
		{
			if(Adapter->astClassifierTable[nIndex1].bUsed && Adapter->astClassifierTable[nIndex2].bUsed)
			{
				if(Adapter->astClassifierTable[nIndex2].u8ClassifierRulePriority <
					Adapter->astClassifierTable[nIndex1].u8ClassifierRulePriority)
				{
					S_CLASSIFIER_RULE stTempClassifierRule = Adapter->astClassifierTable[nIndex2];
					Adapter->astClassifierTable[nIndex2] = Adapter->astClassifierTable[nIndex1];
					Adapter->astClassifierTable[nIndex1] = stTempClassifierRule;

				}
			}
		}
	}
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}
