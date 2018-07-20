/* fscRtd.h - ControlSafe Computer Run Time Diagnostics */

/*
 * Copyright © 2015-2016, Artesyn Embedded Technologies, Inc. All Rights Reserved.
 * This Source Code is furnished under License, and may not be
 * copied or distributed without express written agreement.
 *
 */

/*
modification history
--------------------
01n,14jun16,kmr  IR11490: typedef of FSC_RTD_SDL_TEST inconsistent with 
                          rest of RTD in file fscRtd.h
01m,05may16,kmr  FTR10625: Fixes for the issues identified in the FTR
01l,29apr16,kmr  IR10083 : Method to Determine State of RTD and EOT Processes
01k,26jan16,khb  PCR-8054: Add WriteProtect NOR/VPD tests.
01j,11dec15,khb  FTR-7283: remove PHY tests, rename ETH to BCM.
01i,07dec15,khb  PCR-6557 new tests for SWM & CAN.
01h,01dec15,jvt  FTR-6821: undo fscRtdGroup and moved comment for FSC_RTD_TEST_RUN_t
01g,03nov15,jvt  PCR4487: PC-lint for MISRA-C violations
01f,23oct15,jrd  Post FTR72769 changes.
01e,16oct15,jrd  Task 5588: Added support for Safety Data Logger (temperature
                 sensor data storage).
01d,10oct15,kmr  Task 5350, final RTD clean-up
01c,21sep15,khb  PCR-4561 implement final RTD
01b,03aug15,khb  Add support for DLS mode.
01a,16jun15,khb  initial release, copied from fscPmDrv.
*/

#ifndef __INCfscRtdh
#define __INCfscRtdh

#ifdef __cplusplus
extern "C" {
#endif

/* typedefs */

/* RTD test result values - returned in the rtd_result field */

typedef enum fscTestStatus
    {
        FSC_TEST_STATUS_PASSED,
        FSC_TEST_STATUS_FAILED,
        FSC_TEST_STATUS_BUSY,
        FSC_TEST_STATUS_BYPASS,
        FSC_TEST_STATUS_NOTRUN
    } FSC_TEST_STATUS;

/* RTD groups numbers */

    typedef enum fscRtdGroup
    {
        FSC_RTD_CPU,
        FSC_RTD_MRAM,
        FSC_RTD_CFPGA,
        FSC_RTD_VFPGA,
        FSC_RTD_I2C,
        FSC_RTD_BCM,
        FSC_RTD_CAN,
        FSC_RTD_SDL,
        FSC_RTD_MAX_GROUP
    } FSC_RTD_GROUP;

/* Used for running RTD test, a group of tests, or requesting test status */

typedef struct
    {
        FSC_RTD_GROUP rtd_group;	/* specific group of tests */
        UINT32 rtd_test;	/* specific test within a group or bitmap for sets */
        FSC_TEST_STATUS rtd_result;	/* pass/fail result for each test in the group */
        UINT32 rtd_tstCode;	/* specific test failure code (FSC_ERROR) */
        UINT32 rtd_eot;		/* EOT (engine on time) timestamp in seconds */
    } FSC_RTD_TEST_RUN_t;

/* RTD sub-tests within a group - used with fscRtdTestStat calls */

    typedef enum fscRtdCpu
    {
        FSC_RTD_CpuPor,
        FSC_RTD_MAX_CPU_TEST
    } FSC_RTD_CPU_TEST;

    typedef enum fscRtdMram
    {
        FSC_RTD_MramDataLines0,
        FSC_RTD_MramByteEnables0,
#if defined (FSC_CPU_BOARD)
        FSC_RTD_MramDataLines1,
        FSC_RTD_MramByteEnables1,
#endif
        FSC_RTD_MAX_MRAM_TEST
    } FSC_RTD_MRAM_TEST;

    typedef enum fscRtdCfpga
    {
        FSC_RTD_CfpgaVersion,
        FSC_RTD_CfpgaGeoAddr,
        FSC_RTD_CfpgaGeoPar,
        FSC_RTD_CfpgaDataLines,
        FSC_RTD_CfpgaModHealthAB,
        FSC_RTD_CfpgaAppHWHealthAB,
        FSC_RTD_CfpgaWDTimerVerify,
        FSC_RTD_CfpgaCSModeVerify,
        FSC_RTD_CfpgaFltMaskVerify,
        FSC_RTD_CfpgaWalkAppHthA,
        FSC_RTD_CfpgaWalkAppHthB,
        FSC_RTD_CfpgaWalkHWHthA,
        FSC_RTD_CfpgaWalkHWHthB,
        FSC_RTD_CfpgaBootBank,
        FSC_RTD_CfpgaSysHealthVerify,
        FSC_RTD_CfpgaVerifySafeWD,
        FSC_RTD_CfpgaWrProtVerify,
        FSC_RTD_MAX_CFPGA_TEST
    } FSC_RTD_CFPGA_TEST;

    typedef enum fscRtdVfpga
    {
        FSC_RTD_VfpgaVersion,
        FSC_RTD_VfpgaOvcTc,
        FSC_RTD_VfpgaOvcPrc,
        FSC_RTD_VfpgaGtcAc,
        FSC_RTD_VfpgaSgCHth,
        FSC_RTD_VfpgaMRole,
        FSC_RTD_VfpgaGPWalk,
        FSC_RTD_VfpgaExpVals,
        FSC_RTD_VfpgaSfClas,
        FSC_RTD_VfpgaArbMode,
        FSC_RTD_VfpgaDcaStMc,
        FSC_RTD_VfpgaSrbStMc,
        FSC_RTD_VfpgaSgCmpOp,
        FSC_RTD_MAX_VFPGA_TEST
    } FSC_RTD_VFPGA_TEST;

    typedef enum fscRtdI2c
    {
        FSC_RTD_TempSensors,
        FSC_RTD_VoltMon,
        FSC_RTD_MAX_I2C_TEST
    } FSC_RTD_I2C_TEST;

#if defined (FSC_SWM_BOARD)
    typedef enum fscRtdBcm
    {
        FSC_RTD_BcmVersion,
        FSC_RTD_BcmDataLines,
        FSC_RTD_MAX_BCM_TEST
    } FSC_RTD_BCM_TEST;
#endif

#if defined (FSC_CAN_BOARD)
    typedef enum fscRtdCan
    {
        FSC_RTD_CtlPresence,
        FSC_RTD_BusStat,
        FSC_RTD_MAX_CAN_TEST
    } FSC_RTD_CAN_TEST;
#endif

    typedef enum fscRtdSdl
    {
        FSC_RTD_Temp1Log,
        FSC_RTD_LastSdlEot,
        FSC_RTD_MAX_SDL_TEST
    } FSC_RTD_SDL_TEST;

/***************************************************************** */

/* RTD test IDs by group (bitmaps) - used for fscRtdTestRun calls */

/* CPU test group */

#define FSC_RTD_TEST_CPU_POR            0x00000001U

#define FSC_RTD_TEST_CPU_MASK           0x00000001U
#define FSC_RTD_TEST_CPU_CNT            1U

/* MRAM test group */

#define FSC_RTD_TEST_MRAM_DL0           0x00000001U
#define FSC_RTD_TEST_MRAM_BE0           0x00000002U

#if defined (FSC_CPU_BOARD)

#define FSC_RTD_TEST_MRAM_DL1           0x00000004U
#define FSC_RTD_TEST_MRAM_BE1           0x00000008U

#define FSC_RTD_TEST_MRAM_MASK          0x0000000fU
#define FSC_RTD_TEST_MRAM_CNT           4U

#define FSC_RTD_SET_MRAM_DL             0x00000005U
#define FSC_RTD_SET_MRAM_BE             0x0000000aU

#else    /* Non-CPU boards */

#define FSC_RTD_TEST_MRAM_MASK          0x00000003U
#define FSC_RTD_TEST_MRAM_CNT           2U

#define FSC_RTD_SET_MRAM_DL             0x00000001U
#define FSC_RTD_SET_MRAM_BE             0x00000002U

#endif

/* CFPGA test group */

#define FSC_RTD_TEST_CFPGA_VER          0x00000001U
#define FSC_RTD_TEST_CFPGA_GEOADDR      0x00000002U
#define FSC_RTD_TEST_CFPGA_GEOPAR       0x00000004U
#define FSC_RTD_TEST_CFPGA_DATALN       0x00000008U
#define FSC_RTD_TEST_CFPGA_MODHTH       0x00000010U
#define FSC_RTD_TEST_CFPGA_APPHTH       0x00000020U
#define FSC_RTD_TEST_CFPGA_WDTMR        0x00000040U
#define FSC_RTD_TEST_CFPGA_MODVER       0x00000080U
#define FSC_RTD_TEST_CFPGA_FLTMSK       0x00000100U
#define FSC_RTD_TEST_CFPGA_WKAPPHA      0x00000200U
#define FSC_RTD_TEST_CFPGA_WKAPPHB      0x00000400U
#define FSC_RTD_TEST_CFPGA_WKHWHA       0x00000800U
#define FSC_RTD_TEST_CFPGA_WKHWHB       0x00001000U
#define FSC_RTD_TEST_CFPGA_BOOTBK       0x00002000U
#define FSC_RTD_TEST_CFPGA_CHHTH        0x00004000U
#define FSC_RTD_TEST_CFPGA_SAFEWD       0x00008000U
#define FSC_RTD_TEST_CFPGA_WRPROT       0x00010000U

#define FSC_RTD_TEST_CFPGA_HWC_MASK     0x00003f00U
#define FSC_RTD_TEST_CFPGA_MASK         0x0001ffffU
#define FSC_RTD_TEST_CFPGA_CNT          17U

#define FSC_RTD_SET_CFPGA_VERGEO        0x00000007U
#define FSC_RTD_SET_CFPGA_DATALN        0x00010008U
#define FSC_RTD_SET_CFPGA_HEALTH        0x00000030U
#define FSC_RTD_SET_CFPGA_HEALTH2       0x00004080U
#define FSC_RTD_SET_CFPGA_SAFEWD        0x00008040U

/* VFPGA test group */

#define FSC_RTD_TEST_VFPGA_VER          0x00000001U
#define FSC_RTD_TEST_VFPGA_OVCTC        0x00000002U
#define FSC_RTD_TEST_VFPGA_OVCORC       0x00000004U
#define FSC_RTD_TEST_VFPGA_GTCAC        0x00000008U
#define FSC_RTD_TEST_VFPGA_SGHTH        0x00000010U
#define FSC_RTD_TEST_VFPGA_MROLE        0x00000020U
#define FSC_RTD_TEST_VFPGA_GPWALK       0x00000040U
#define FSC_RTD_TEST_VFPGA_EXPVAL       0x00000080U
#define FSC_RTD_TEST_VFPGA_SFCLAS       0x00000100U
#define FSC_RTD_TEST_VFPGA_ARBMD        0x00000200U
#define FSC_RTD_TEST_VFPGA_DSTMC        0x00000400U
#define FSC_RTD_TEST_VFPGA_SSTMC        0x00000800U
#define FSC_RTD_TEST_VFPGA_SGCMP        0x00001000U

#define FSC_RTD_TEST_VFPGA_MASK         0x00001fffU
#define FSC_RTD_TEST_VFPGA_CNT          13U

#define FSC_RTD_SET_VFPGA_CNTRS         0x0000000eU
#define FSC_RTD_SET_VFPGA_ROLES         0x00000021U
#define FSC_RTD_SET_VFPGA_WALKS         0x00000040U
#define FSC_RTD_SET_VFPGA_STATIC        0x00000180U
#define FSC_RTD_SET_VFPGA_DCASRB        0x00000e00U
#define FSC_RTD_SET_VFPGA_SWGATE        0x00001010U

/* I2C test group */

#define FSC_RTD_TEST_I2C_TEMP           0x00000001U
#define FSC_RTD_TEST_I2C_VOLT           0x00000002U

#define FSC_RTD_TEST_I2C_MASK           0x00000003U
#define FSC_RTD_TEST_I2C_CNT            2U

#define FSC_RTD_SET_I2C_TEMPVOLT        0x00000003U

/* BCM test group */

#define FSC_RTD_TEST_BCM_VER            0x00000001U
#define FSC_RTD_TEST_BCM_DATALN         0x00000002U

#define FSC_RTD_TEST_BCM_MASK           0x00000003U
#define FSC_RTD_TEST_BCM_CNT            2U

#define FSC_RTD_SET_BCM                 0x00000003U

/* CAN test group */

#define FSC_RTD_TEST_CAN_CTL_PRES       0x00000001U
#define FSC_RTD_TEST_CAN_BUS_STAT       0x00000002U

#define FSC_RTD_TEST_CAN_MASK           0x00000003U
#define FSC_RTD_TEST_CAN_CNT            2U

#define FSC_RTD_SET_CAN_CTL             0x00000003U

/* SDL (temp logging) "test" group */

#define FSC_RTD_TEST_SDL_TEMP1          0x00000001U
#define FSC_RTD_TEST_SDL_EOT            0x00000002U

#define FSC_RTD_TEST_SDL_MASK           0x00000003U
#define FSC_RTD_TEST_SDL_CNT            2U


/***************************************************************** */

/* RTD specific FSC error returns */

#define FSC_RTD_OPEN_ERROR              ((UINT32)0xFEU)
#define FSC_RTD_IO_ERROR                ((UINT32)0xFDU)
#define FSC_RTD_DRINIT_ERROR            ((UINT32)0xFCU)

/* RTD TestRun error codes */

#define FSC_RTD_CPU_POR_ERROR           ((UINT32)0xF0U)

#define FSC_RTD_MRAM_DL0_ERROR          ((UINT32)0xEFU)
#define FSC_RTD_MRAM_BE0_ERROR          ((UINT32)0xEEU)
#define FSC_RTD_MRAM_DL1_ERROR          ((UINT32)0xEDU)
#define FSC_RTD_MRAM_BE1_ERROR          ((UINT32)0xECU)

#define FSC_RTD_CFPGA_VER_ERROR         ((UINT32)0xEBU)
#define FSC_RTD_CFPGA_GEOADDR_ERROR     ((UINT32)0xEAU)
#define FSC_RTD_CFPGA_GEOPAR_ERROR      ((UINT32)0xE9U)
#define FSC_RTD_CFPGA_DATALN_ERROR      ((UINT32)0xE8U)
#define FSC_RTD_CFPGA_MODHTH_ERROR      ((UINT32)0xE7U)
#define FSC_RTD_CFPGA_APPHTH_ERROR      ((UINT32)0xE6U)
#define FSC_RTD_CFPGA_WDTMR_ERROR       ((UINT32)0xE5U)
#define FSC_RTD_CFPGA_MODVER_ERROR      ((UINT32)0xE4U)
#define FSC_RTD_CFPGA_FLTMSK_ERROR      ((UINT32)0xE3U)
#define FSC_RTD_CFPGA_HWBUSY_ERROR      ((UINT32)0xE2U)
#define FSC_RTD_CFPGA_WKAPPHA_ERROR     ((UINT32)0xE1U)
#define FSC_RTD_CFPGA_WKAPPHB_ERROR     ((UINT32)0xE0U)
#define FSC_RTD_CFPGA_WKHWHA_ERROR      ((UINT32)0xDFU)
#define FSC_RTD_CFPGA_WKHWHB_ERROR      ((UINT32)0xDEU)
#define FSC_RTD_CFPGA_BOOTBK_ERROR      ((UINT32)0xDDU)
#define FSC_RTD_CFPGA_CHHTH_ERROR       ((UINT32)0xDCU)
#define FSC_RTD_CFPGA_SAFEWD_ERROR      ((UINT32)0xDBU)
#define FSC_RTD_CFPGA_WRPROT_ERROR      ((UINT32)0xDAU)

#define FSC_RTD_VFPGA_VER_ERROR         ((UINT32)0xCFU)
#define FSC_RTD_VFPGA_OVCTC_ERROR       ((UINT32)0xCEU)
#define FSC_RTD_VFPGA_OVCPRC_ERROR      ((UINT32)0xCDU)
#define FSC_RTD_VFPGA_GTCAC_ERROR       ((UINT32)0xCCU)
#define FSC_RTD_VFPGA_SGHTH_ERROR       ((UINT32)0xCBU)
#define FSC_RTD_VFPGA_NOTHTH_ERROR      ((UINT32)0xCAU)
#define FSC_RTD_VFPGA_MROLE_ERROR       ((UINT32)0xC9U)
#define FSC_RTD_VFPGA_GPWALK_ERROR      ((UINT32)0xC8U)
#define FSC_RTD_VFPGA_EXPVAL_ERROR      ((UINT32)0xC7U)
#define FSC_RTD_VFPGA_SFCLAS_ERROR      ((UINT32)0xC6U)
#define FSC_RTD_VFPGA_ARBMD_ERROR       ((UINT32)0xC5U)
#define FSC_RTD_VFPGA_DSTMC_ERROR       ((UINT32)0xC4U)
#define FSC_RTD_VFPGA_SSTMC_ERROR       ((UINT32)0xC3U)
#define FSC_RTD_VFPGA_SGCMP_ERROR       ((UINT32)0xC2U)

#define FSC_RTD_I2C_TEMP_ERROR          ((UINT32)0xBFU)
#define FSC_RTD_I2C_TEMP2_ERROR         ((UINT32)0xBEU)
#define FSC_RTD_I2C_VOLT_ERROR          ((UINT32)0xBDU)

#define FSC_RTD_BCM_VER_ERROR           ((UINT32)0xB8U)
#define FSC_RTD_BCM_DTLN_ERROR          ((UINT32)0xB7U)

#define FSC_RTD_CAN_CTLPRES_ERROR       ((UINT32)0xB3U)
#define FSC_RTD_CAN_BUSSTAT_ERROR       ((UINT32)0xB2U)
#define FSC_RTD_CAN_DRIVER_ERROR        ((UINT32)0xB1U)

#define FSC_RTD_SDL_NOT_INITD           ((UINT32)0xAFU)
#define FSC_RTD_SDL_TEMP_RD_ERROR       ((UINT32)0xAEU)
#define FSC_RTD_SDL_MRAM_ACCESS_ERROR   ((UINT32)0xADU)

/***************************************************************** */

FSC_STATUS fscRtdTestRun( FSC_RTD_TEST_RUN_t * const );
FSC_STATUS fscRtdTestStat( FSC_RTD_TEST_RUN_t * const );
FSC_STATUS fscRtdTestStatAll( FSC_RTD_TEST_RUN_t * const );
FSC_STATUS fscRtdKeepAlive(void);
FSC_STATUS fscRtdIsRunning( BOOL * const );
void usrAppInit ( void );

#ifdef __cplusplus
}
#endif

#endif /* __INCfscRtdh */
