/* fscLib.h - ControlSafe common header file
*
* Copyright (c) 2014-2017, Artesyn Embedded Technologies, Inc. All Rights Reserved.
* This Source Code is furnished under License, and may not be
* copied or distributed without express written agreement.
*
* Copyright (c) 2013 Emerson Network Power - Embedded Computing, Inc.
*/

/*
* modification history
* --------------------
* 02c,27apr17,jap  FTR 15805: reserve definition for VMCTX hook
* 02b,20jan17,jap  add module definition for Safety Layer Library
* 02a,12feb16,wjs  IR8429: added not-supported
* 01z,03feb16,jvt  FTR8338: reworked FSC_ERROR macros
* 01y,15jan16,jap  PCR 5711: add Network Routing Interface driver
* 01x,08dec15,jap  FTR 7260 move MRAM_UNHEALTHY_CODE here
* 01w,29oct15,jvt  FTR5752: Issue 6389 - merge changes
* 01v,19oct15,jvt  PCR4487: PC-lint for MISRA-C violations
* 01u,30oct15,dwh  FTR6451 issues
* 01t,26oct15,wjs  redefined OS faults to support IR 5242
* 01s,09oct15,jap  IR 2867 -- remove definition of FSC_SWG_MODULE
* 01r,02oct15,jap  PCR 5255 -- set unique POST codes
* 01q,15sep15,kmr  PCR3590: Enhance PM API functions due to RTD re-design
* 01p,31jul15,kmr  PCR3437: FTR00071634 - code review inputs
* 01o,29jun15,kmr  PCR3497: Inventory API fscVpdInventoryGet()
* 01n,11jun15,jap  PCR 2261: sw gate define
* 01m,May2015,wjs  initial release of CAN-Eth driver
* 01l,25mar15,jap  added Safety Layer defines
* 01k,19mar15,wjs  PCR2473; align with FPGA v1.5
* 01j,06feb15,khb  added PM module
* 01i,19dec14,jrc  added error codes
* 01h,03dec14,wjs  added support for CAN-Eth driver
* 01g,02dec14,jap  Added new socket MSG flags
* 01f,20oct14,kmr  Added a comment for the
*                  Element Health OS Fault Codes FTR00067777
* 01e,21aug14,dta  added Logging define.
* 01d,17oct14,khb  rework for MISRA-C issues.
* 01c,20aug14,jrc  added PDRAM defines
* 01b,29apr14,jrc  fixes from FTR 66193, updated copyright
* 01a,20nov13,jrc  initial release.
*/

#ifndef __INCfsch
#define __INCfsch

#ifdef __cplusplus
    extern "C" {
#endif /* __cplusplus */

/*
 * Artesyn defines section
 */

#define INCLUDE_SAFE_MODE
#define INCLUDE_MAINT_MODE

#define INCLUDE_MOS
#define INCLUDE_POS

#define INCLUDE_FSC_CPU
#define INCLUDE_FSC_SWM
#define INCLUDE_FSC_IOU_CAN
#define INCLUDE_FSC_IOU_RING

#define INCLUDE_VPD

/* Memory size based on board type */
#if defined (FSC_CPU_BOARD)
#define MEM_SIZE                    0x40000000U
#else
#define MEM_SIZE                    0x20000000U
#endif

/*
 * Typedefs that indicate size and signedness should be used in place of the
 * basic numerical types (MISRA 6.3). With resepect to type "char", there are
 * three distinct "char" types, (plain) "char", "signed char", and
 * "unsigned char". "signed char" and "unsigned char" shall be used for
 * numeric data and plain "char" shall be used for character data (MISRA 6.2).
 *
 * Numeric data (defined in .../vxworks653-2.4/target/h/types/vxTypesOld.h):
 *   typedef signed char     INT8;
 *   typedef unsigned char   UINT8;
 *   typedef unsigned char   UCHAR;
 *
 * Plain "char":
 */
typedef unsigned char   UINT8;
typedef char   CHAR;
typedef unsigned short int  UINT16;


/*
 * Artesyn defined error section.
 *
 * FSC_ERROR:        makes an error to return.
 * FSC_ERROR_MODULE: returns the module from the error.
 * FSC_ERROR_TYPE:   returns the error type from the error.
 */

typedef INT32 FSC_STATUS;

#define FSC_ERROR(module, error)        ((INT32)(module) + (INT32)(error))
#define FSC_ERROR_MODULE(error)         (((INT32)(error) / 0x10000) * 0x10000)
#define FSC_ERROR_TYPE(error)           (((INT32)(error) - ((INT32)0x8000000)) % 0x8000)

#define FSC_SUCCESSFUL                  0
#define FSC_UNSUCCESSFUL                (-1)

/* Error Modules */

#define FSC_CS_MODULE                   0x80010000U
#define FSC_DS_MODULE                   0x80020000U
#define FSC_FDT_MODULE                  0x80030000U
#define FSC_FHI_MODULE                  0x80040000U
#define FSC_FWU_MODULE                  0x80050000U
#define FSC_IP_MODULE                   0x80060000U
#define FSC_RC_MODULE                   0x80070000U
#define FSC_LHC_MODULE                  0x80080000U
#define FSC_VF_MODULE                   0x80090000U
#define FSC_MWD_MODULE                  0x800A0000U
#define FSC_RNG_MODULE                  0x800B0000U
#define FSC_PST_MODULE                  0x800C0000U
#define FSC_RTD_MODULE                  0x800D0000U
#define FSC_SFL_MODULE                  0x800E0000U
#define FSC_SM_MODULE                   0x800F0000U
#define FSC_SLG_MODULE                  0x80100000U
#define FSC_VL_MODULE                   0x80110000U
#define FSC_VPD_MODULE                  0x80120000U
#define FSC_FI_MODULE                   0x80130000U
#define FSC_PD_MODULE                   0x80140000U
#define FSC_LOG_MODULE                  0x80150000U
#define FSC_CE_MODULE                   0x80160000U
#define FSC_PM_MODULE                   0x80170000U
#define FSC_SL_MODULE                   0x80180000U
/* 0x80190000U reserved in <config.h> for FSC_SWG_MODULE */
#define FSC_NRI_MODULE					0x801A0000U
#define FSC_SLL_MODULE					0x801B0000U
/* 0x801C0000U reserved for FSC_VMCTXFIX in sysLib.c */

/* Errors Types */

#define FSC_NO_ERROR                    0x0000
#define FSC_BAD_FILEDESCRIPTOR          0x0001
#define FSC_DATA_ERROR                  0x0002
#define FSC_INVALID_ADDRESS             0x0003
#define FSC_INVALID_CRC                 0x0004
#define FSC_INVALID_DEVICE              0x0005
#define FSC_INVALID_IMAGE               0x0006
#define FSC_INVALID_MODULE              0x0008
#define FSC_INVALID_PARAMETER           0x0009
#define FSC_INVALID_PERMISSION          0x000A
#define FSC_INVALID_READ                0x000B
#define FSC_INVALID_SIZE                0x000C
#define FSC_INVALID_VERSION             0x000D
#define FSC_INVALID_WRITE               0x000E
#define FSC_NULL_POINTER                0x000F
#define FSC_OUT_OF_BOUNDS               0x0010
#define FSC_TIMED_OUT                   0x0011
#define FSC_UNASSIGNED                  0x0012
#define FSC_CFPGA_ERROR                 0x0013
#define FSC_VFPGA_ERROR                 0x0014
#define FSC_CONFIG_FAIL                 0x0015
#define FSC_IOCTL_USAGE_ERROR           0x0016
#define FSC_WD_WRONG_STATE              0x0017
#define FSC_INVALID_HEADER              0x0018
#define FSC_INVALID_STATE               0x0019
#define FSC_INVALID_CONDITION           0x001A
#define FSC_GPIO_ERROR                  0x001B
#define FSC_SPIREG_ERROR                0x001C
#define FSC_ERASE_ERROR                 0x001D
#define FSC_TASK_ERROR                  0x001E
#define FSC_NOT_SUPPORTED               0x001f


/* Element Health - OS Fault Codes */
/* These are the values passed to fscCsEhOsFaultSet() API.  */

#define FSC_EH_OSFLT_ERROR_CODE(section,group) ((UINT16)(((UINT16)((UINT16)(section) << 8U) & 0xff00U) | ((group) & 0x00ffU)))


/* OS Fault Code Blocks */

#define FSC_EH_OSFLT_GENERAL                (0x01U)
#define FSC_POST_EH_OSFLT_POST_EARLY        (0x0eU) /* 'e'arly */
#define FSC_POST_EH_OSFLT_POST_FULL         (0x0fU) /* 'f'ull */


/* OS Fault Codes - Errors */

#define FSC_EH_OSFLT_VPD_CRC_ERROR          (FSC_EH_OSFLT_ERROR_CODE(FSC_EH_OSFLT_GENERAL,0x01U))
#define FSC_EH_OSFLT_VFPGA_READ_ACCESS      (FSC_EH_OSFLT_ERROR_CODE(FSC_EH_OSFLT_GENERAL,0x02U))
#define FSC_EH_OSFLT_VFPGA_WRITE_ACCESS     (FSC_EH_OSFLT_ERROR_CODE(FSC_EH_OSFLT_GENERAL,0x03U))
#define FSC_EH_OSFLT_VFPGA_IVCPKTLOST_CFG   (FSC_EH_OSFLT_ERROR_CODE(FSC_EH_OSFLT_GENERAL,0x04U))
#define FSC_EH_OSFLT_VFPGA_IVCVTMISM_CFG    (FSC_EH_OSFLT_ERROR_CODE(FSC_EH_OSFLT_GENERAL,0x05U))
#define FSC_EH_OSFLT_VFPGA_LOAD_FAIL        (FSC_EH_OSFLT_ERROR_CODE(FSC_EH_OSFLT_GENERAL,0x06U))
#define FSC_EH_OSFLT_ECC_NOT_ENABLED        (FSC_EH_OSFLT_ERROR_CODE(FSC_EH_OSFLT_GENERAL,0x07U))
#define FSC_EH_OSFLT_DRAM_MBE               (FSC_EH_OSFLT_ERROR_CODE(FSC_EH_OSFLT_GENERAL,0x08U))
#define FSC_EH_OSFLT_FI_INIT_FAILED         (FSC_EH_OSFLT_ERROR_CODE(FSC_EH_OSFLT_GENERAL,0x09U))
#define FSC_EH_OSFLT_SYSTEM_RESET           (FSC_EH_OSFLT_ERROR_CODE(FSC_EH_OSFLT_GENERAL,0x0aU))
#define FSC_EH_OSFLT_PM_ERROR               (FSC_EH_OSFLT_ERROR_CODE(FSC_EH_OSFLT_GENERAL,0x0bU))
#define FSC_EH_OSFLT_DRIVER_INST_ERROR      (FSC_EH_OSFLT_ERROR_CODE(FSC_EH_OSFLT_GENERAL,0x0cU))
#define FSC_EH_OSFLT_SEMAPHORE_ERROR        (FSC_EH_OSFLT_ERROR_CODE(FSC_EH_OSFLT_GENERAL,0x0dU))
#define FSC_EH_OSFLT_RTMPHY_ERROR           (FSC_EH_OSFLT_ERROR_CODE(FSC_EH_OSFLT_GENERAL,0x0eU))
#define FSC_EH_OSFLT_MRAM_UNHEALTHY_CODE	(FSC_EH_OSFLT_ERROR_CODE(FSC_EH_OSFLT_GENERAL,0x0fU))

/* POST Internal error (0x0000) */

#define FSC_POST_EH_OSFLT_INTERNAL_ERROR	(0x0000U)

/* POST Early errors (reserved: 0x0E01 - 0x0EFF) */

#define FSC_POST_EH_OSFLT_MRAM_WP_ERROR     (FSC_EH_OSFLT_ERROR_CODE(FSC_POST_EH_OSFLT_POST_EARLY, 0x01U))
#define FSC_POST_EH_OSFLT_VFPGA_SETUP_ERROR (FSC_EH_OSFLT_ERROR_CODE(FSC_POST_EH_OSFLT_POST_EARLY, 0x02U))
#define FSC_POST_EH_OSFLT_FAILSAFE_WD_ERROR (FSC_EH_OSFLT_ERROR_CODE(FSC_POST_EH_OSFLT_POST_EARLY, 0x03U))
#define FSC_POST_EH_OSFLT_BOOT_WD_ERROR     (FSC_EH_OSFLT_ERROR_CODE(FSC_POST_EH_OSFLT_POST_EARLY, 0x04U))
#define FSC_POST_EH_OSFLT_BOARD_TYPE_ERROR  (FSC_EH_OSFLT_ERROR_CODE(FSC_POST_EH_OSFLT_POST_EARLY, 0x05U))
#define FSC_POST_EH_OSFLT_TIMEBASE_ERROR    (FSC_EH_OSFLT_ERROR_CODE(FSC_POST_EH_OSFLT_POST_EARLY, 0x06U))
#define FSC_POST_EH_OSFLT_RTMPRESENCE_ERROR (FSC_EH_OSFLT_ERROR_CODE(FSC_POST_EH_OSFLT_POST_EARLY, 0x07U))
#define FSC_POST_EH_OSFLT_CFPGA_VER_ERROR   (FSC_EH_OSFLT_ERROR_CODE(FSC_POST_EH_OSFLT_POST_EARLY, 0x08U))
#define FSC_POST_EH_OSFLT_CFPGA_DFLT_ERROR  (FSC_EH_OSFLT_ERROR_CODE(FSC_POST_EH_OSFLT_POST_EARLY, 0x09U))
#define FSC_POST_EH_OSFLT_CFPGA_ADDR_ERROR  (FSC_EH_OSFLT_ERROR_CODE(FSC_POST_EH_OSFLT_POST_EARLY, 0x0AU))
#define FSC_POST_EH_OSFLT_CFPGA_DATA_ERROR  (FSC_EH_OSFLT_ERROR_CODE(FSC_POST_EH_OSFLT_POST_EARLY, 0x0BU))
#define FSC_POST_EH_OSFLT_SOC_ERROR         (FSC_EH_OSFLT_ERROR_CODE(FSC_POST_EH_OSFLT_POST_EARLY, 0x0CU))
#define FSC_POST_EH_OSFLT_CFLTLOC_ERROR	    (FSC_EH_OSFLT_ERROR_CODE(FSC_POST_EH_OSFLT_POST_EARLY, 0x0DU))
#define FSC_POST_EH_OSFLT_VFLTLOC_ERROR     (FSC_EH_OSFLT_ERROR_CODE(FSC_POST_EH_OSFLT_POST_EARLY, 0x0EU))

/* POST Full errors (reserved: 0x0F01 - 0xFFF) */

#define FSC_POST_EH_OSFLT_GEOADDR_ERROR     (FSC_EH_OSFLT_ERROR_CODE(FSC_POST_EH_OSFLT_POST_FULL, 0x01U))
#define FSC_POST_EH_OSFLT_GEO_PAR_ERROR     (FSC_EH_OSFLT_ERROR_CODE(FSC_POST_EH_OSFLT_POST_FULL, 0x02U))
#define FSC_POST_EH_OSFLT_CFPGA_GRP_ERROR   (FSC_EH_OSFLT_ERROR_CODE(FSC_POST_EH_OSFLT_POST_FULL, 0x03U))
#define FSC_POST_EH_OSFLT_VFPGA_GRP_ERROR   (FSC_EH_OSFLT_ERROR_CODE(FSC_POST_EH_OSFLT_POST_FULL, 0x04U))
#define FSC_POST_EH_OSFLT_BCM_GRP_ERROR     (FSC_EH_OSFLT_ERROR_CODE(FSC_POST_EH_OSFLT_POST_FULL, 0x05U))
#define FSC_POST_EH_OSFLT_IOU_CAN_GRP_ERROR (FSC_EH_OSFLT_ERROR_CODE(FSC_POST_EH_OSFLT_POST_FULL, 0x06U))
#define FSC_POST_EH_OSFLT_SPI_GRP_ERROR     (FSC_EH_OSFLT_ERROR_CODE(FSC_POST_EH_OSFLT_POST_FULL, 0x07U))
#define FSC_POST_EH_OSFLT_L2CACHE_GRP_ERROR (FSC_EH_OSFLT_ERROR_CODE(FSC_POST_EH_OSFLT_POST_FULL, 0x08U))
#define FSC_POST_EH_OSFLT_FLASH_GRP_ERROR   (FSC_EH_OSFLT_ERROR_CODE(FSC_POST_EH_OSFLT_POST_FULL, 0x09U))
#define FSC_POST_EH_OSFLT_I2C_GRP_ERROR     (FSC_EH_OSFLT_ERROR_CODE(FSC_POST_EH_OSFLT_POST_FULL, 0x0AU))
#define FSC_POST_EH_OSFLT_TSEC_GRP_ERROR    (FSC_EH_OSFLT_ERROR_CODE(FSC_POST_EH_OSFLT_POST_FULL, 0x0BU))
#define FSC_POST_EH_OSFLT_DRAM_GRP_ERROR    (FSC_EH_OSFLT_ERROR_CODE(FSC_POST_EH_OSFLT_POST_FULL, 0x0CU))
#define FSC_POST_EH_OSFLT_MRAM0_GRP_ERROR   (FSC_EH_OSFLT_ERROR_CODE(FSC_POST_EH_OSFLT_POST_FULL, 0x0DU))
#define FSC_POST_EH_OSFLT_MRAM1_GRP_ERROR   (FSC_EH_OSFLT_ERROR_CODE(FSC_POST_EH_OSFLT_POST_FULL, 0x0EU))
#define FSC_POST_EH_OSFLT_PCI_GRP_ERROR     (FSC_EH_OSFLT_ERROR_CODE(FSC_POST_EH_OSFLT_POST_FULL, 0x0FU))
#define FSC_POST_EH_OSFLT_VFPGADIAG_ERROR   (FSC_EH_OSFLT_ERROR_CODE(FSC_POST_EH_OSFLT_POST_FULL, 0x10U))

/* Socket extensions - message flags */

#define MSG_FSC_IF	((UINT32)0x100000U)	/* message is "interference free" (default is "safety relevant") */
#define MSG_FSC_DA	((UINT32)0x200000U)	/* message exits CSP via dual-attached port (default is "single attached") */

#ifdef __cplusplus
    }
#endif /* __cplusplus */

#endif /* __INCfsch */
