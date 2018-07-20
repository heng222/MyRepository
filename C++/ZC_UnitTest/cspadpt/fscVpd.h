/*
* fscVpd.h - ControlSafe Computer Vital Product Data (VPD) Library public
*            definitions. User Applications in Core OS and Partition OS can
*            include this file to access the VPD.
*/
/*
* Copyright (c) 2014-2016 Artesyn Embedded Technologies, Inc. All Rights Reserved.
*
* This Source Code is furnished under License, and may not be
* copied or distributed without express written agreement.
*
* Copyright (c) 2013 Emerson Network Power - Embedded Computing, Inc.
*
*/

/*
* Modification History
* --------------------
* 01r,02aug16,kmr  PCR12508: make network mask length configurable
* 01q,26apr16,jvt  IR10239: PC-lint for non-CPU modules
* 01p,22jan16,kmr  Task 5725 Check return values for semLib routines
* 01o,19jan16,jvt  PCR4091 clean up remaining PC-lint findings
* 01n,07oct15,jvt  PCR4487: PC-lint for MISRA-C violations
* 01m,03Aug15,kmr  IR 3469: fscVpdDrvAliasShow does not display
*                           the last alias entry
* 01l,31jul15,kmr  PCR3437: FTR00071634 - code review inputs
* 01k,29jun15,kmr  PCR3437: Inventory API fscVpdInventoryGet()
* 01j,06may15,kmr  PCR2797: Alias configuration and proxyNet configuration
* 01i,14apr15,kmr  PCR2581: Operational Mode
* 01h,22mar15,kmr  PCR2293: IOU Ethernet Board specifics
* 01g,11feb15,jrd  PCR 2136 - added additional error defines (for bootline)
* 01f,20jan15,kmr  fix for Task 2235 - New VPD Layout
* 01e,06jan15,kmr  fixes from Task2139
* 01d,04oct14,kmr  fixes from IR1938 - MISRA-C Compliance
* 01c,13may14,kmr  fix for IR1219
* 01b,23apr14,kmr  fixes from FTR 66141
* 01a,06dec13,kmr  Initial version
*/


#ifndef __fscVpd_h__
#define __fscVpd_h__

#ifdef __cplusplus
extern "C" {
#endif

/* includes */
/*#include "vxWorks.h"*/

#include "fscLib.h"

/* defines */

/* Length of the Serial Number of the FRU
*  (front board or Rear Transmission Module (RTM))
*/

#define FSC_VPD_SERIAL_NUMBER_LEN (12U)

/* Length of the Production Date */

#define FSC_VPD_PRODUCTION_DATE_LEN (3U)

/* Length of Board Identifier */

#define FSC_VPD_BOARD_ID_LEN (32U)

/* Length of Assembly Number */

#define FSC_VPD_ASSEMBLY_NUMBER_LEN (16U)

/* Length of MAC address */

#define FSC_VPD_MAC_ADDR_LEN (6U)

/* Length of IP Subnet */

#define FSC_VPD_IP_SUBNET_LEN (4U)

/* Length of IP Subnet mask */

#define FSC_VPD_IP_SUBNET_MASK_LEN (1U)

#ifdef INCLUDE_FSCVPDDRV_MOS_CFG_API

/* Length of Config Data */

#define FSC_VPD_CONFIG_DATA_LEN (252U)

#endif /* INCLUDE_FSCVPDDRV_MOS_CFG_API */

#define FSC_VPD_CKSUM_LEN (4U)

/* Maximum length of the bootline */

#define FSC_VPD_BOOTLINE_MAX_LEN      (256U)

/* Maximum number of interface alias records */

#define FSC_VPD_MAX_ALIAS (20U)

/* FRU Identifier */

typedef enum fru_id
    {
    FSC_VPD_FRU_FB = 0,
    FSC_VPD_FRU_RTM,
    FSC_VPD_MAX_FRU
    } FSC_VPD_FRU_ID;

/* identifies the type of interface */

typedef enum interface_id
    {
    FSC_VPD_BACKPLANE_INTERFACE = 0,
    FSC_VPD_FRONTPANEL_INTERFACE,
    FSC_VPD_RTM_PORT0_INTERFACE,
    FSC_VPD_RTM_PORT1_INTERFACE,
    FSC_VPD_MAX_INTERFACE
    } FSC_VPD_INTF_ID;

/* IP Subnet default/subnet identifier */

typedef enum subnet_id
    {
    FSC_VPD_SUBNET_DEFAULT = 0,
    FSC_VPD_SUBNET_USER,
    FSC_VPD_SUBNET_FACTORY_DEFAULT,
    FSC_VPD_SUBNET_MAX_TYPE
    }FSC_VPD_SUBNET_ID;


typedef struct sNumberDetails
    {
    FSC_VPD_FRU_ID fruId;
    UINT8          sNumber[FSC_VPD_SERIAL_NUMBER_LEN];
    } FSC_VPD_SNUMBER_DATA;

typedef struct prodDateDetails
    {
    FSC_VPD_FRU_ID fruId;
    UINT8          prodDate[FSC_VPD_PRODUCTION_DATE_LEN];
    } FSC_VPD_PROD_DATE_DATA;

typedef struct boardIdDetails
    {
    FSC_VPD_FRU_ID fruId;
    UINT8          boardId[FSC_VPD_BOARD_ID_LEN];
    } FSC_VPD_BOARD_ID_DATA;

typedef struct asmNumberDetails
    {
    FSC_VPD_FRU_ID fruId;
    UINT8         asmNumber[FSC_VPD_ASSEMBLY_NUMBER_LEN];
    } FSC_VPD_ASM_NUMBER_DATA;

typedef struct macAddrDetails
    {
    FSC_VPD_INTF_ID intfId;
    UINT8         macAddr[FSC_VPD_MAC_ADDR_LEN];
    } FSC_VPD_MAC_ADDR_DATA;

typedef struct ipSubnetDetails
    {
    FSC_VPD_INTF_ID   intfId;
    FSC_VPD_SUBNET_ID subnetId;
    UINT8             subnet[FSC_VPD_IP_SUBNET_LEN];
    UINT8             subnetMaskLen;
    } FSC_VPD_IP_SUBNET_DATA;

typedef struct alias
    {
    UINT8 intfNum;
    UINT8 aliasNum;
    UINT32 ipAddr;
    UINT32 netMask;
    UINT32 bAddr;
    }FSC_VPD_INTF_ALIAS_ENTRY;

typedef struct vpdBoard
    {
    FSC_VPD_SNUMBER_DATA    sNumber[FSC_VPD_MAX_FRU];
    FSC_VPD_PROD_DATE_DATA  pDate[FSC_VPD_MAX_FRU];
    FSC_VPD_BOARD_ID_DATA   bdId[FSC_VPD_MAX_FRU];
    FSC_VPD_ASM_NUMBER_DATA asmNumber[FSC_VPD_MAX_FRU];
    FSC_VPD_MAC_ADDR_DATA   macAddr[FSC_VPD_MAX_INTERFACE];
    FSC_VPD_IP_SUBNET_DATA  ipSubnet[FSC_VPD_MAX_INTERFACE][FSC_VPD_SUBNET_MAX_TYPE];
    UINT32                  aliasCount;
    FSC_VPD_INTF_ALIAS_ENTRY alias[FSC_VPD_MAX_ALIAS];
    } FSC_VPD_BOARD_INVENTORY;

typedef struct vpdInventory
    {
    FSC_VPD_BOARD_INVENTORY master;
    FSC_VPD_BOARD_INVENTORY checker;
    } FSC_VPD_INVENTORY;

#ifdef INCLUDE_FSCVPDDRV_MOS_CFG_API
typedef struct cDataDetails
    {
    UINT8 cData[FSC_VPD_CONFIG_DATA_LEN];
    } FSC_VPD_CONFIG_DATA_DETAILS;
#endif /* INCLUDE_FSCVPDDRV_MOS_CFG_API */

/* VPD specific error codes */

#define FSC_VPD_ERR_BASE                    (0x00FF)
#define FSC_VPD_EEPROM_CKSUM_WR_FAILED      (FSC_VPD_ERR_BASE - 0x0001)
#define FSC_VPD_EEPROM_USRDATA_WR_FAILED    (FSC_VPD_ERR_BASE - 0x0002)
#define FSC_VPD_I2C_READ_FAIL               (FSC_VPD_ERR_BASE - 0x0003)
#define FSC_VPD_NO_RTM                      (FSC_VPD_ERR_BASE - 0x0004)
#define FSC_VPD_FB_VPD_ARRAY_OVERRUN		(FSC_VPD_ERR_BASE - 0x0005)
#define FSC_VPD_RTM_VPD_ARRAY_OVERRUN		(FSC_VPD_ERR_BASE - 0x0006)
#define FSC_VPD_EEPROM_UNLOCK_FAILED        (FSC_VPD_ERR_BASE - 0x0007)
#define FSC_VPD_EEPROM_LOCK_FAILED          (FSC_VPD_ERR_BASE - 0x0008)
#define FSC_VPD_INIT_FAILED                 (FSC_VPD_ERR_BASE - 0x0009)
#define FSC_VPD_DEV_INSTALL_NOT_DONE        (FSC_VPD_ERR_BASE - 0x000A)
#define FSC_VPD_DEV_ADD_FAILED              (FSC_VPD_ERR_BASE - 0x000B)
#define FSC_VPD_CKSUM_NO_MATCH              (FSC_VPD_ERR_BASE - 0x000C)
#define FSC_VPD_ECATCH_NO_MATCH             (FSC_VPD_ERR_BASE - 0x000D)
#define FSC_VPD_BOOTLINE_INVALID            (FSC_VPD_ERR_BASE - 0x000E)
#define FSC_VPD_BOOTLINE_STR_CONV_FAILED    (FSC_VPD_ERR_BASE - 0x000F)
#define FSC_VPD_BOOTLINE_SIZE_ERR           (FSC_VPD_ERR_BASE - 0x0010)
#define FSC_VPD_END_OF_TABLE                (FSC_VPD_ERR_BASE - 0x0011)
#define FSC_VPD_REC_NOT_FOUND               (FSC_VPD_ERR_BASE - 0x0012)
#define FSC_VPD_SEMCREATE_FAILED            (FSC_VPD_ERR_BASE - 0x0013)
#define FSC_VPD_SEMTAKE_FAILED              (FSC_VPD_ERR_BASE - 0x0014)
#define FSC_VPD_SEMGIVE_FAILED              (FSC_VPD_ERR_BASE - 0x0015)

/* retrives the serial number of the front board or the RTM */

FSC_STATUS fscVpdSerialNumberGet(FSC_VPD_SNUMBER_DATA* const sNumber);

/* retrieves the production date of the front board or the RTM */

FSC_STATUS fscVpdProductionDateGet(FSC_VPD_PROD_DATE_DATA* const pDate);

/* retrieves the Board Identifier of the front board or the RTM */

FSC_STATUS fscVpdBoardIdGet(FSC_VPD_BOARD_ID_DATA* const bdId);

/* retrieves the Assembly Number of the front board or the RTM */

FSC_STATUS fscVpdAssemblyNumberGet(FSC_VPD_ASM_NUMBER_DATA* const aNmbr);

/* retrieves the MAC address for the Ethernet controller connected
 * to the backplane or for the Ethernet controller connected to the
 * front panel of the front board.
 */

FSC_STATUS fscVpdMacAddressGet(FSC_VPD_MAC_ADDR_DATA* const macAddr);


/* retrieves the IP Subnet for the factory default or the user updated subnet
 * for the backplane or the front panel ethernet interface
 */

FSC_STATUS fscVpdIpSubnetGet(FSC_VPD_IP_SUBNET_DATA* const subnet);

FSC_STATUS fscVpdAliasGet
    (
    const UINT8 intfNum,
    const UINT8 aliasNum,
    UINT32 * const ipAddr,
    UINT32 * const netMask,
    UINT32 * const bAddr
    );

FSC_STATUS fscVpdAliasGetFirst
    (
    UINT8 * const firstIntfNum,
    UINT8 * const firstAliasNum,
    UINT32 * const firstIpAddr,
    UINT32 * const firstNetMask,
    UINT32 * const firstBAddr
    );

FSC_STATUS fscVpdAliasGetNext
    (
    const UINT8 intfNum,
    const UINT8 aliasNum,
    UINT8 * const nextIntfNum,
    UINT8 * const nextAliasNum,
    UINT32 * const nextIpAddr,
    UINT32 * const nextNetMask,
    UINT32 * const nextBAddr
    );

FSC_STATUS fscVpdAliasShow
    (
    INT32  options
    );


#ifndef FSC_OPERATIONAL_MODE
/*
 * gets the bootline
 */

FSC_STATUS fscVpdBootlineGet(CHAR bootLine[], const UINT32   bootLineLen,
                             const UINT32   offset);

/*
 * sets the bootline
 */

FSC_STATUS fscVpdBootlineSet(CHAR* const bootLine);

/* sets the IP Subnet for the factory default or the user updated subnet
 * for the backplane or the front panel ethernet interface
 */

FSC_STATUS fscVpdIpSubnetSet(FSC_VPD_IP_SUBNET_DATA* const subnet);

FSC_STATUS fscVpdAliasSet
    (
    const UINT8    intfNum,
    const UINT8    aliasNum,
    const UINT32   ipAddr,
    const UINT32   netMask,
    const UINT32   bAddr
    );

FSC_STATUS fscVpdAliasRowDelete
    (
    const UINT8 intfNum,
    const UINT8 aliasNum
    );

FSC_STATUS fscVpdAliasRowDeleteAll
    (
    void
    );
#endif  /* #ifndef FSC_OPERATIONAL_MODE */

#if ((defined FSC_OPERATIONAL_MODE) && (defined FSC_CPU_BOARD))
FSC_STATUS fscVpdInventoryGet
    (
    FSC_VPD_INVENTORY* const vpd
    );
#endif /* #if (defined FSC_OPERATIONAL_MODE) && (defined FSC_CPU_BOARD) */

#ifdef INCLUDE_FSCVPDDRV_MOS_CFG_API

/* retrieves the configuration data for the specified number of bytes */
/* this api is available only to the Core OS */

FSC_STATUS fscVpdConfigDataGet(FSC_VPD_CONFIG_DATA_DETAILS* const cData);

#endif /* INCLUDE_FSCVPDDRV_MOS_CFG_API */


#ifndef FSC_OPERATIONAL_MODE
#ifdef INCLUDE_FSCVPDDRV_MOS_CFG_API

/* sets the configuration data */
/* this api is available only to the Core OS */

FSC_STATUS fscVpdConfigDataSet(FSC_VPD_CONFIG_DATA_DETAILS* const cData);

#endif /* INCLUDE_FSCVPDDRV_MOS_CFG_API */
#endif /* FSC_OPERATIONAL_MODE */

#ifdef __cplusplus
}
#endif

#endif /* __fscVpd_h__ */
