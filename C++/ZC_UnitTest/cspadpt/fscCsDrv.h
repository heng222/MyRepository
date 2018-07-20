/* 
* fscCsLib.h - FSC Control/Status API Shared Library
*
* Copyright (c) 2014-2017 Artesyn Embedded Technologies, Inc. All Rights Reserved.
* This Source Code is furnished u/nder License, and may not be
* copied or distributed without express written agreement.
*
* Copyright (c) 2013 Emerson Network Power - Embedded Computing, Inc.
*
* Modification History
* --------------------
* 07a,20Jan2017, wjs IR 14513: removed restrictions on fscCsSafetyWdStatusGet
* 06c,02Feb2016, wjs IR-7745 update comments/defines for vFPGA
* 06b,04feb2016, jvt FTR8401: fix build warning on fscCsIopUsrEnableSet()
* 06a,19Jan2016, wjs IR-7630 boot-watchdog APIs and APIGEN
* 04e,11Nov2015, wjs IR-6570 added fscCsSafetyWdLatchClear
* 04d,14oct15,   jvt PCR4487: PC-lint for MISRA-C violations
* 04c,Oct2015,   wjs IR-3117 removed fscCsBootBankSet()/fscCsBootBankToggle()
* 04b,26Oct15    wjs IR-5459 removed fscCsChassisHealthGet
* 04a,August2015 wjs PCR-3012 removed fscCsArbActiveStatusSet from maint mode
* 03d,June2015,  wjs PCR-3012 removed fscCsHwFaultMaskGet/Set
* 03c,14apr2015, kmr PCR2581; Operational Mode image
* 03b,March2015, wjs PCR2473; align with FPGA v1.5
* 03a,Feb2015,   wjs PCR2281; EA Release
* 02f,Sept2014,  wjs IR 1894
* 02e,Aug2014,   wjs IR-983 (Tasks 1546, 1548, 1551, 1555)
* 02d,July2014,  wjs IR-1151, IR-1152, PCR-1447
* 02b,15May2014, wjs PCR-1202, Additional FTR updates
* 02a,30Apr2014, wjs Task-1203, FTR updates
* 01a,14Nov2013, wjs initial release.
*/


#ifndef __INCfscCSDrv_h__
#define __INCfscCSDrv_h__

#ifdef __cplusplus
extern "C" {
#endif

#include "fscLib.h"

#include "..\FSFB\GM_RSSP1_APP_Interface.h"
#include "..\FSFB\GM_RSSP1_Msg_Queue.h"
#include "..\FSFB\SFM\GM_RSSP1_SFM.h"
#include "..\GM_Utils\GM_Ini_File.h"
#include "..\GM_Utils\GM_Memcpy.h"
#include "..\GM_Utils\GM_Memset.h"
#include "..\GM_Utils\GM_Mutex.h"
#include "..\INTERCOMM\GM_CFG_INTERCOMM.h"
#include "..\cspadpt\fscVpd.h"
/*******************************************************************************
* Public Datatypes - grouped by subcomponent
*
* grouping is based on where the usage first appears; the types may 
* span multiple subcomponents
*/

/* --- Active Register vs Latched Copy --- */
#define ACTIVE_REG	((BOOL) TRUE)
#define LATCHED_REG	((BOOL) FALSE)


/* --- Module Reset/Last Reset --- */
#define FSCCS_RESET_POWER_CYCLE 	((UINT16) 0x0001U)
#define FSCCS_RESET_SAFETY_WDA_TIMEOUT	((UINT16) 0x0002U)
#define FSCCS_RESET_SAFETY_WDB_TIMEOUT	((UINT16) 0x0200U)
#define FSCCS_RESET_MAINT_WD_TIMEOUT	((UINT16) 0x0004U)
#define FSCCS_RESET_SOFTWARE_REQUEST	((UINT16) 0x0008U)
#define FSCCS_RESET_FRONT_PANEL_RESET	((UINT16) 0x0010U)
#define FSCCS_RESET_BOOT_WD_TIMEOUT	((UINT16) 0x0020U)
#define FSCCS_RESET_VPX_FROM_BACKPLANE	((UINT16) 0x0040U)
#define FSCCS_RESET_VPX_TO_BACKPLANE	((UINT16) 0x0100U)
#define FSCCS_RESET_RTM_STATUS_CHANGE	((UINT16) 0x0080U)

typedef enum 
    {
    fscCsSysController,		/* in system-controller mode */
    fscCsNotSysController 	/* not in system-controller mode */
    } 
    FSCCS_SYSCTRL_STATUS;	/* SWM boards only */

typedef enum 
    {
    fscCsNotAsserted,		/* given health signal is not asserted */
    fscCsAsserted		/* given health signal is asserted */
    } 
    FSCCS_ASSERT_STATUS;

typedef enum
    {
    fscCsUnhealthy,		/* The module (or chassis, etc.) is unhealthy */
    fscCsHealthy		/* The module (or chassis, etc.) is healthy */
    }
    FSCCS_HEALTH_STATUS;

typedef enum 
    {
    fscCsDisabled,		/* The device (or interface, etc.) is disabled */
    fscCsEnabled		/* The device (or interface, etc.) is enabled */
    } 
    FSCCS_ENABLE_STATUS;

typedef enum 
    {
    fscCsUnlocked,		/* The device (or memory, etc.) is Unlocked */
    fscCsLocked			/* The device (or memory, etc.) is Locked (persistent) */
    } 
    FSCCS_LOCK_STATUS;

typedef struct
    {
    UINT16 usrControlled;	/* Indicates that the port been set by the user */
    UINT16 usrSetting;		/* users enable/disable setting */
    } 
    FSCCS_IOP_USRCTRL;


/* --- LED API --- */
#define FSCCS_LED_POWER_GREEN		((UINT16) 0x0001U)
#define FSCCS_LED_MODHEALTH_GREEN	((UINT16) 0x0004U)
#define FSCCS_LED_MODHEALTH_RED		((UINT16) 0x0008U)
#define FSCCS_LED_SYSHEALTH_GREEN	((UINT16) 0x0010U)	/* only available on CPU boards */
#define FSCCS_LED_SYSHEALTH_RED		((UINT16) 0x0020U)	/* only available on CPU boards */
#define FSCCS_LED_ACTIVE_GREEN		((UINT16) 0x0040U)	/* only available on CPU boards */
#define FSCCS_LED_STANDBY_AMBER		((UINT16) 0x0080U)	/* only available on CPU boards */


/* --- System Status --- */
#define FSCCS_FPGA_VERSION_LEN		9

typedef enum 
    {
    fscCsUnknCard,		/* board type is Unknown */
    fscCsCpuCard,		/* board type is CPU module */
    fscCsSwmCard, 		/* board type is Switch module */
    fscCsIouCanCard,		/* board type is IOU-CAN module */
    fscCsIouUartCard, 		/* board type is IOU-UART module */
    fscCsIouEthCard, 		/* board type is IOU-Ethernet module */
    fscCsIouRingCard		/* board type is IOU-RING module */
    } 
    FSCCS_BOARD_TYPE;

typedef enum 
    {
    fscCsSafetyMode,		/* In Safety Mode */
    fscCsMaintenanceMode	/* In Maintenance Mode */
    } 
    FSCCS_SAFETY_MODE;

typedef enum 
    {
    fscCsStandby,		/* the FSC is in Standby mode */
    fscCsActive			/* the FSC is in Active mode */
    } 
    FSCCS_ACTIVE_STATUS;

typedef enum 
    {
    fscCsRtmNotPresent,		/* The RTM is not installed */
    fscCsRtmPresent		/* The RTM is installed */
    } 
    FSCCS_RTM_PRESENCE;

typedef enum 
    {
    fscCsFrontPanel,		/* Front Panel */
    fscCsBackPanel 		/* Back Panel */
    } 
    FSCCS_DEV_LOCATION;



/* --- Boot Bank --- */
typedef enum 
    {
    fscCsBootBankB,		/* NOR flash boot bank B */
    fscCsBootBankA		/* NOR flash boot bank A */
    } 
    FSCCS_BOOTBANK;

typedef enum 
    {
    fscDeviceNotBusy,		/* The target device is NOT busy */
    fscDeviceBusy		/* The target device is busy */
    } 
    FSCCS_DEVICE_BUSY;


/* ------ Watchdog APIs - Safety Relevant ------ */

#define FSCCS_SRWD_ENABLED 	((UINT16) 0x0001U)
#define FSCCS_SRWD_EXPIRED 	((UINT16) 0x0002U)
#define FSCCS_SRWD_MULT_RETRIG 	((UINT16) 0x0004U)
#define FSCCS_SRWD_MISS_RETRIG 	((UINT16) 0x0008U)


/* --- I/O Port Control - not available on CPU boards --- */
#define FSCCS_IOP_PORT0		((UINT16) 0x0001U)
#define FSCCS_IOP_PORT1		((UINT16) 0x0002U)
#define FSCCS_IOP_PORT2		((UINT16) 0x0004U)
#define FSCCS_IOP_PORT3		((UINT16) 0x0008U)
#define FSCCS_IOP_PORT4		((UINT16) 0x0010U)
#define FSCCS_IOP_PORT5		((UINT16) 0x0020U)
#define FSCCS_IOP_PORT6		((UINT16) 0x0040U)
#define FSCCS_IOP_PORT7		((UINT16) 0x0080U)

typedef enum 
    {
    fscCsSafetyRelevant,	/* IOP Safety Class / safety relevant */
    fscCsInterferenceFree	/* IOP Safety Class / interference free */
    } 
    FSCCS_SAFETY_CLASS;

typedef enum 
    {
    fscCsSingleAttach,		/* IOP Attach Mode / single attached */
    fscCsDualAttach		/* IOP Attach Mode / dual attached */
    } 
    FSCCS_ATTACH_MODE;


/* --- Module Health --- */
#define FSCCS_MODHEALTH_HW_BIT		((UINT16) 0x0001U)
#define FSCCS_MODHEALTH_APP_BIT		((UINT16) 0x0002U)
#define FSCCS_MODHEALTH_WD_BIT		((UINT16) 0x0004U)

#define FSCCS_APP_BIT_SAFETY_MODE	((UINT16) 0xffffU)	/* clear APP Elem-Health register */

typedef enum 
    {
    fscCsHwFault,		/* HW Element Health - fault */
    fscCsNoHwFault		/* HW Element Health - no fault */
    } 
    FSCCS_HWEH_FAULT_MODE;


/* The following defines are applicable to the HW Faults & HW Fault Mask */
#define FSCCS_HWEH_IOP_ERROR_STATUS 	((UINT16) 0x0001)	/* not valid on CPU cards */
#define FSCCS_HWEH_OTHER_FPGA_CRC 	((UINT16) 0x0002)
#define FSCCS_HWEH_VFPGA_HEALTH 	((UINT16) 0x0004)	/* only valid on CPU cards */
#define FSCCS_HWEH_VFPGA2_HEALTH 	((UINT16) 0x0008)	/* only valid on CPU cards */
#define FSCCS_HWEH_CHC_A_HEALTH 	((UINT16) 0x0040)
#define FSCCS_HWEH_ASC_A_HEALTH 	((UINT16) 0x0080)
#define FSCCS_HWEH_TS_A_HEALTH 		((UINT16) 0x0100)
#define FSCCS_HWEH_VC_HEALTH_A1 	((UINT16) 0x0200)
#define FSCCS_HWEH_VC_HEALTH_A2 	((UINT16) 0x0400)	/* only valid on CPU cards */
#define FSCCS_HWEH_LHTC_A_HEALTH 	((UINT16) 0x0800)
#define FSCCS_HWEH_WDT_A_HEALTH 	((UINT16) 0x1000)
#define FSCCS_HWEH_MHT_A_HEALTH 	((UINT16) 0x2000)
#define FSCCS_HWEH_MST_A_HEALTH 	((UINT16) 0x4000)

/* --- Chassis Health --- */
#define FSCCS_CHASSIS_HEALTH_LOCAL	((UINT16) 0x0800U)
#define FSCCS_CHASSIS_HEALTH_PEER	((UINT16) 0x0400U)
#define FSCCS_CHASSIS_HEALTH_LOCAL_RTM	((UINT16) 0x0200U)
#define FSCCS_CHASSIS_HEALTH_PEER_RTM	((UINT16) 0x0100U)

/* Module Health & Safety Classification */
#define FSCCS_CHASSIS_STATUS		((UINT16) 0x8000U)
#define FSCCS_CHASSIS_CPU_B_MODULE	((UINT16) 0x0100U)
#define FSCCS_CHASSIS_CPU_A_MODULE	((UINT16) 0x0080U)
#define FSCCS_CHASSIS_SWM_MODULE	((UINT16) 0x0040U)
#define FSCCS_CHASSIS_IOU6_MODULE	((UINT16) 0x0020U)
#define FSCCS_CHASSIS_IOU5_MODULE	((UINT16) 0x0010U)
#define FSCCS_CHASSIS_IOU4_MODULE	((UINT16) 0x0008U)
#define FSCCS_CHASSIS_IOU3_MODULE	((UINT16) 0x0004U)
#define FSCCS_CHASSIS_IOU2_MODULE	((UINT16) 0x0002U)
#define FSCCS_CHASSIS_IOU1_MODULE	((UINT16) 0x0001U)

/* Active Status Values */
#define FSCCS_ARBSTAT_BP_A_ACTIVE	((UINT16) 0x0080U)
#define FSCCS_ARBSTAT_BP_B_ACTIVE	((UINT16) 0x0040U)
#define FSCCS_ARBSTAT_SWCTRL_ACTIVE	((UINT16) 0x0010U)
#define FSCCS_ARBSTAT_LOCAL_A_ACTIVE	((UINT16) 0x0008U)
#define FSCCS_ARBSTAT_LOCAL_B_ACTIVE	((UINT16) 0x0004U)
#define FSCCS_ARBSTAT_REMOTE_A_ACTIVE	((UINT16) 0x0002U)
#define FSCCS_ARBSTAT_REMOTE_B_ACTIVE	((UINT16) 0x0001U)

typedef enum 
    {
    fscCsForcedHealthy,		/* The module is not forced unhealthy */
    fscCsForcedUnhealthy	/* The module is forced unhealthy */
    } 
    FSCCS_FORCED_HEALTH;	/* CPU boards only */

/* Arbitration types */
typedef enum 
    {
    fscCsDirectConnect,		/* arbitration mode = direct connect (DCA) */
    fscCsDcaNoSwInput,		/* HW is indicating DCA, need SW confirmation */
    fscCsSftyRelayBox,		/* arbitration mode = safety relay box (SRB) */
    fscCsSrbNoSwInput		/* HW is indicating SRB, need SW confirmation */
    } 
    FSCCS_ARB_MODE;               /* CPU boards only */

typedef enum 
    {
    fscCsSecondary,		/* arbitration role = secondary/SRB */
    fscCsSecNoSwInput,		/* HW is indicating Secondary, need SW confirmation */
    fscCsPrimary,		/* arbitration role = primary */
    fscCsPriNoSwInput		/* HW is indicating Primary, need SW confirmation */
    } 
    FSCCS_ARB_ROLE;		/* CPU boards only */

typedef enum 
    {
    fscCsArbFault,		/* ARB Health - fault */
    fscCsNoArbFault		/* ARB Health - no fault */
    } 
    FSCCS_ARB_HEALTH;		/* CPU boards only */


/* --- Voting FPGA Config - only available on CPU boards --- */
#define FSCCS_CFPGA_VCFG_ERR		((UINT16) 0x0080U)
#define FSCCS_CFPGA_VCFG_NSTATUS_ERR	((UINT16) 0x0040U)
#define FSCCS_CFPGA_VCFG_CFGDONE_ERR	((UINT16) 0x0020U)
#define FSCCS_CFPGA_VCFG_CFGINIT_ERR	((UINT16) 0x0010U)
#define FSCCS_CFPGA_VCFG_SUCCESS	((UINT16) 0x0008U)


/*******************************************************************************
* Function Prototypes - grouped by logical subcomponent.
*/

/* ------ Module Reset ------ */

/* Get the cause for the last reset */
extern FSC_STATUS fscCsResetCauseGet
    ( 
    UINT16 * const cause 
    );

/* Clear the cause for the last reset */
extern FSC_STATUS fscCsResetCauseClear
    (
    void
    );

/* Return the current value for GDiscrete1, boot maintenance or safety OS */
extern FSC_STATUS fscCsGdiscrete1Get
    ( 
    FSCCS_ASSERT_STATUS * const status
    );

#if (defined FSC_CPU_BOARD) || (defined FSC_SWM_BOARD)
/* Allows software to set GDiscrete1 */
extern FSC_STATUS fscCsGdiscrete1Set
    ( 
    FSCCS_ASSERT_STATUS const status
    );

/* Allows software to reset the ControlSafe Computer */
extern FSC_STATUS fscCsSystemReset
    (
    void
    );
#endif

/* Determine if this board is in the system controller slot */
extern FSC_STATUS fscCsSystemCtrlGet
    ( 
    FSCCS_SYSCTRL_STATUS * const status
    );

/* Reset and hold the PHY devices in reset */
extern FSC_STATUS fscCsPhyResetHold
    ( 
    FSCCS_DEV_LOCATION const location
    );

/* Clear the Reset and Hold bit for the PHY devices */
extern FSC_STATUS fscCsPhyResetHoldClear
    ( 
    FSCCS_DEV_LOCATION const location
    );


/* ------ Console Status ------ */

/* Return the current status of the console settings */
extern FSC_STATUS fscCsConsoleStatusGet
    ( 
    FSCCS_ENABLE_STATUS * const txStatus, 
    FSCCS_ENABLE_STATUS * const rxStatus 
    );

/* Enable/Disable the front panel COM port (transmit) */
extern FSC_STATUS fscCsConsoleStatusTxSet
    ( 
    FSCCS_ENABLE_STATUS const txStatus 
    );

/* Enable/Disable the front panel COM port (receive) */
extern FSC_STATUS fscCsConsoleStatusRxSet
    ( 
    FSCCS_ENABLE_STATUS const rxStatus 
    );


/* ------ Memory Access ------ */

/* Return the current setting for the VPD ROM write-protection status */
extern FSC_STATUS fscCsVpdLockStatusGet
    ( 
    FSCCS_LOCK_STATUS * const vpdStatus 
    );

/* Set the VPD ROM write-protection status (locked) */
extern FSC_STATUS fscCsVpdLock
    ( 
    void 
    );

/* Clear the VPD ROM write-protection status (unlocked) */
extern FSC_STATUS fscCsVpdUnlock
    ( 
    void 
    );

/* Return the current setting for SDRAMs persistence */
extern FSC_STATUS fscCsPdramStatusGet
    ( 
    FSCCS_ENABLE_STATUS * const pdramStatus 
    );

/* Enable SDRAMs persistence on warm reset */
extern FSC_STATUS fscCsPdramEnable
    ( 
    void 
    );

/* Disable SDRAMs persistence on warm reset */
extern FSC_STATUS fscCsPdramDisable
    ( 
    void 
    );

#if (defined FSC_CPU_BOARD)
/* Return the current setting for the MRAM write-protection status - Internal Use Only */
extern FSC_STATUS fscCsMramLockStatusGet
    ( 
    FSCCS_LOCK_STATUS * const lockStatusA,
    FSCCS_LOCK_STATUS * const lockStatusB 
    );
#else
/* Return the current setting for the MRAM write-protection status - Internal Use Only */
extern FSC_STATUS fscCsMramLockStatusGet
    ( 
    FSCCS_LOCK_STATUS * const lockStatus 
    );
#endif

/* Lock MRAM - Internal Use Only */
extern FSC_STATUS fscCsMramLock
    ( 
    void 
    );

/* Unlock MRAM - Internal Use Only */
extern FSC_STATUS fscCsMramUnlock
    ( 
    void 
    );


/* ------ LED API ------ */

/* Read the Front Panel LED Status */
extern FSC_STATUS fscCsLedStatusGet
    ( 
    UINT16 * const ledStatus 
    );

#if (defined FSC_SWM_BOARD) 
/* Get the status of the Ethernet LEDs - Internal Use Only */
extern FSC_STATUS fscCsEthLedStatusGet
    (
    UINT16 * const ledStatus 
    );

/* Set the status of the Ethernet LEDs - Internal Use Only */
extern FSC_STATUS fscCsEthLedStatusSet
    (
    UINT16 const ledStatus 
    );
#endif


/* ------ System Status ------ */

/* Return the board type (e.g. CPU, SWM, CAN, RING, etc.) */
extern FSC_STATUS fscCsBoardTypeGet
    ( 
    FSCCS_BOARD_TYPE * const boardType 
    );

/* Query the system safety mode, either active or standby */
extern FSC_STATUS fscCsSafetyModeGet
    ( 
    FSCCS_SAFETY_MODE * const safetyMode 
    );

/* Set the system safety mode */
extern FSC_STATUS fscCsSafetyModeSet
    ( 
    const FSCCS_SAFETY_MODE safetyMode 
    );

/* Query the system mode, either active or standby */
extern FSC_STATUS fscCsActiveModeGet
    ( 
    FSCCS_ACTIVE_STATUS * const statusA,
    FSCCS_ACTIVE_STATUS * const statusB 
    );

/* Query the module health, either healthy or unhealthy */
FSC_STATUS fscCsModuleHealthGet
    (
    FSCCS_HEALTH_STATUS * const statusA,
    FSCCS_HEALTH_STATUS * const statusB 
    );

/* Query the system/chassis health, either healthy or unhealthy */
FSC_STATUS fscCsSystemHealthGet
    (
    FSCCS_HEALTH_STATUS * const statusA,
    FSCCS_HEALTH_STATUS * const statusB 
    );

/* RTM presence */
extern FSC_STATUS fscCsIsRtmPresent
    ( 
    FSCCS_RTM_PRESENCE * const rtmStatus 
    );

/* Return the geographic address of the slot */
extern FSC_STATUS fscCsGeographicAddrGet
    ( 
    UINT16 * const slot 
    );

#if (defined FSC_SWM_BOARD)
/* Return the chassis-id */
extern FSC_STATUS fscCsChassisIdGet
    (
    UINT16 * const chassisid 
    );

/* Query the status of the chassis fan tray */
extern FSC_STATUS fscCsFanTrayStatusGet
    (
    FSCCS_ENABLE_STATUS * const ftStatus 
    );

/* Enable the chassis fan tray */
extern FSC_STATUS fscCsFanTrayEnable
    (
    void
    );

/* Disable the chassis fan tray */
extern FSC_STATUS fscCsFanTrayDisable
    (
    void
    );
#endif

/* Verify the FPGA (s) are loaded */
extern FSC_STATUS fscCsVerifyFpga
    (
    void
    );

/* Read the build information for the Control FPGA */
extern FSC_STATUS fscCsFpgaVersionGet
    ( 
    CHAR * const fpgaVerA, UINT16 const lenA,
    CHAR * const fpgaVerB, UINT16 const lenB 
    );

#if (defined FSC_CPU_BOARD)
/* Read the build information for the Voting FPGA */
extern FSC_STATUS fscCsVFpgaVersionGet
    (
    CHAR * const fpgaVerA, UINT16 const lenA,
    CHAR * const fpgaVerB, UINT16 const lenB 
    );
#endif


/* ------ Boot Bank ------ */

/* Returns boot bank used in the last boot */
extern FSC_STATUS fscCsLastBootBankGet
    ( 
    FSCCS_BOOTBANK * const bootBank 
    );

/* Returns the currently selected boot bank */
extern FSC_STATUS fscCsBootBankGet
    ( 
    FSCCS_BOOTBANK * const bootBank 
    );

/* Read the boot failure count, the number of successive failures */
extern FSC_STATUS fscCsBootFailCntGet
    ( 
    UINT16 * const bankACount,
    UINT16 * const bankBCount 
    );

#if (!defined FSC_OPERATIONAL_MODE)
/* Returns the number of allowable boot attempts */
extern FSC_STATUS fscCsBootAttemptCntGet
    (
    UINT16 * bankACount,
    UINT16 * bankBCount 
    );

/* Set the boot attempt count */
extern FSC_STATUS fscCsBootAttemptCntSet
    ( 
    UINT16 const count 
    );

/* Query the NOR Flash status (idle/busy) - Internal Use Only */ 
extern FSC_STATUS fscCsIsNorFlashBusy
    ( 
    FSCCS_DEVICE_BUSY * const bankABusy,
    FSCCS_DEVICE_BUSY * const bankBBusy 
    );

/* Query the upgradable-NOR Flash write-protection status - Internal Use Only */
extern FSC_STATUS fscCsNorFlashLockStatusGet
    (
    FSCCS_LOCK_STATUS * const lockStatus 
    );

/* Lock the upgradable-NOR Flash - Internal Use Only */
extern FSC_STATUS fscCsNorFlashLock
    ( 
    void 
    );

/* Unlock the upgradable-NOR Flash - Internal Use Only */
extern FSC_STATUS fscCsNorFlashUnlock
    ( 
    void 
    );
#endif


/* ------ Watchdog APIs - Safety Relevant ------ */

#if (defined FSC_OPERATIONAL_MODE)

/* Get time remaining before CS-Safety WD expires */
extern FSC_STATUS fscCsSafetyWdExpTimeGet
    ( 
    UINT16 * const expireTimeA,
    UINT16 * const expireTimeB 
    );

/* Rearm the SC-Safety WD */
extern FSC_STATUS fscCsSafetyWdRearm
    ( 
    void 
    );

/* Read the duration (window size) for the SC-Safety WD */
extern FSC_STATUS fscCsSafetyWdTimerValGet
    (
    UINT16 * const timerValueA,
    UINT16 * const timerValueB 
    );

/* Set the duration (window size) for the SC-Safety WD */
extern FSC_STATUS fscCsSafetyWdTimerValSet
    ( 
    UINT16 const timerValue 
    );

/* Start the fail safe SC-Safety WD */
extern FSC_STATUS fscCsSafetyWdStart
    ( 
    void 
    );
#endif

/* Query the status of the SC-Safety WD */
extern FSC_STATUS fscCsSafetyWdStatusGet
    ( 
    UINT16 * const wdStatusA,
    UINT16 * const wdStatusB,
    BOOL const activeReg
    );


#if (!defined FSC_OPERATIONAL_MODE)

/* Clear the Fail Safe Watchdog Fault Code Registers */
FSC_STATUS fscCsSafetyWdLatchClear
    (
    void
    );
#endif


/* ------ Watchdog APIs - Boot WD ------ */

/* Get time remaining before boot WD expires */
extern FSC_STATUS fscCsBootWdExpTimeGet
    ( 
    UINT16 * const expireTime 
    );

/* Rearm the boot WD */
extern FSC_STATUS fscCsBootWdRearm
    ( 
    void 
    );

/* Query the status of the boot WD */
extern FSC_STATUS fscCsBootWdStatusGet
    ( 
    FSCCS_ENABLE_STATUS * const wdStatus 
    );

/* Stop the boot WD */
extern FSC_STATUS fscCsBootWdStop
    ( 
    void 
    );


/* ------ Watchdog APIs - Software Update WD - Internal Use Only ------ */

#if (!defined FSC_OPERATIONAL_MODE)

/* Get time remaining before the Software Update WD expires */
extern FSC_STATUS fscCsSwUpdtWdExpTimeGet
    ( 
    UINT16 * const expireTime 
    );

/* Rearm the Software Update WD */
extern FSC_STATUS fscCsSwUpdtWdRearm
    ( 
    void 
    );

/* Query the status of the Software Update WD */
extern FSC_STATUS fscCsSwUpdtWdStatusGet
    ( 
    FSCCS_ENABLE_STATUS * const wdStatus 
    );

/* Stop the Software Update WD */
extern FSC_STATUS fscCsSwUpdtWdStop
    ( 
    void 
    );

/* Read the duration (window size) for the Software Update WD */
extern FSC_STATUS fscCsSwUpdtWdTimerValGet
    ( 
    UINT16 * const timerValue 
    );

/* Set the duration (window size) for the Software Update WD */
extern FSC_STATUS fscCsSwUpdtWdTimerValSet
    ( 
    UINT16 const timerValue 
    );

/* Start the Software Update WD */
extern FSC_STATUS fscCsSwUpdtWdStart
    ( 
    void 
    );

#endif


/* ------ I/O Port Control ------ */

#if (!defined FSC_CPU_BOARD) 
/* Read the I/O port classification mode for RTM I/O ports */
extern FSC_STATUS fscCsIopSftyClassGet
    (
    UINT16 * const classStatusA, 
    UINT16 * const classStatusB,
    BOOL const activeReg 
    );

/* Set the port classification for RTM I/O ports */
extern FSC_STATUS fscCsIopSftyClassSet
    (
    UINT16 const classStatus 
    );

/* Read the I/O port attach mode for RTM I/O ports */
extern FSC_STATUS fscCsIopAttachModeGet
    ( 
    UINT16 * const modeStatusA, 
    UINT16 * const modeStatusB,
    BOOL const activeReg 
    );

/* Set the port attach mode RTM I/O ports */
extern FSC_STATUS fscCsIopAttachModeSet
    (
    UINT16 const modeStatus
    );

/* Read the port status for RTM I/O ports */
extern FSC_STATUS fscCsIopEnableGet
    (
    UINT16 * const enableStatusA, 
    UINT16 * const enableStatusB,
    BOOL const activeReg 
    );

extern FSC_STATUS fscCsIopUsrEnableGet
    (
    FSCCS_IOP_USRCTRL * const enableStatusA,
    FSCCS_IOP_USRCTRL * const enableStatusB
    );

extern FSC_STATUS fscCsIopUsrEnableSet
    (
    FSCCS_IOP_USRCTRL * const enableStatus
    );

#if (!defined FSC_OPERATIONAL_MODE)
/* Clear the port classification for RTM I/O ports */
extern FSC_STATUS fscCsIopSftyClassLatchClear
    ( 
    void 
    );

/* Clear the latched I/O port-attach mode register */
extern FSC_STATUS fscCsIopAttachModeLatchClear
    ( 
    void 
    );

/* Clear the latched I/O port-enable mode register */
extern FSC_STATUS fscCsIopEnableLatchClear
    ( 
    void 
    );
#endif   /* !FSC_OPERATIONAL_MODE */
#endif   /* FSC_CPU_BOARD */


/* ------ Module Health ------ */

/* Read the Module Health Register */
extern FSC_STATUS fscCsModHlthCircuitGet
    ( 
    UINT16 * const healthStatusA, 
    UINT16 * const healthStatusB,
    BOOL const activeReg 
    );

/* Read OS status/errors from the HW Element Health Register */
extern FSC_STATUS fscCsEhOsFaultGet
    (
    UINT16 * const elHealthA, 
    UINT16 * const elHealthB,
    BOOL const activeReg 
    );

/* Write OS status/errors to the HW Element Health Register */
extern FSC_STATUS fscCsEhOsFaultSet
    (
    UINT16 const elHealth 
    );

/* Read HW status/errors from the HW Element Health Register */
extern FSC_STATUS fscCsEhHwFaultGet
    ( 
    UINT16 * const elHealthA, 
    UINT16 * const elHealthB,
    BOOL const activeReg 
    );

/* Read APP status/errors from the APP Element Health Register */
extern FSC_STATUS fscCsEhAppFaultGet
    ( 
    UINT16 * const elHealthA, 
    UINT16 * const elHealthB,
    BOOL const activeReg 
    );

/* Write APP status/errors to the APP Element Health Register */
extern FSC_STATUS fscCsEhAppFaultSet
    (
    UINT16 const elHealth 
    );

#if (!defined FSC_OPERATIONAL_MODE)
/* Clear the latched Module Health Register */
extern FSC_STATUS fscCsModHlthCircuitLatchClear
    ( 
    void 
    );

/* Clear latched copies, OS side of the HW Element Health Register */
extern FSC_STATUS fscCsEhOsFaultLatchClear
    ( 
    void 
    );

/* Clear latched copies, HW side of the HW Element Health Register */
extern FSC_STATUS fscCsEhHwFaultLatchClear
    ( 
    void 
    );

/* Clear latched copies of the APP Element Health Register */
extern FSC_STATUS fscCsEhAppFaultLatchClear
    ( 
    void 
    );
#endif   /* !FSC_OPERATIONAL_MODE */


/* ------ Chassis Health ------ */

#if (defined FSC_CPU_BOARD) 

/* Chassis-Level Health; query module health status */
extern FSC_STATUS fscCsChassisModHealthGet
    ( 
    UINT16 * const moduleHealth,
    BOOL const activeReg 
    );

/* Chassis-Level Health; query module safety classification status */
extern FSC_STATUS fscCsChassisModClassGet
    ( 
    UINT16 * const moduleClass,
    BOOL const activeReg 
    );

/* Chassis-Level Health; set module safety classification status */
extern FSC_STATUS fscCsChassisModClassSet
    ( 
    UINT16 const moduleClass 
    );

/* Chassis-Level Health; query module forced-unhealthy status */
extern FSC_STATUS fscCsChassisModHlthForceGet
    ( 
    UINT16 * const moduleHealth,
    BOOL const activeReg 
    );

/* Chassis-Level Health; set module forced-unhealthy status */
extern FSC_STATUS fscCsChassisModHlthForceSet
    ( 
    UINT16 const moduleHealth 
    );

/* Chassis-Level Health; qualified Module Health */
extern FSC_STATUS fscCsChassisModHlthQualGet
    ( 
    UINT16 * const chassisHealth,
    BOOL const activeReg 
    );

/* Healthy Status of the Arbiter */
extern FSC_STATUS fscCsArbStatusGet
    ( 
    FSCCS_ARB_HEALTH * const health 
    );

/* Return the arbitration connection mode (DCA/SRB) */
extern FSC_STATUS fscCsArbModeGet
    ( 
    FSCCS_ARB_MODE * const arbModeA,
    FSCCS_ARB_MODE * const arbModeB,
    BOOL const activeReg 
    );

/* Set the arbitration mode (DCA/SRB) */
extern FSC_STATUS fscCsArbModeSet
    ( 
    FSCCS_ARB_MODE const arbMode 
    );

/* Return the arbitration role, primary role versus secondary role */
extern FSC_STATUS fscCsArbRoleGet
    ( 
    FSCCS_ARB_ROLE * const arbRole,
    BOOL const activeReg 
    );

/* Set the arbitration role, primary or other (secondary or SRB mode) */
extern FSC_STATUS fscCsArbRoleSet
    ( 
    FSCCS_ARB_ROLE const arbRole 
    );

/* Provides status and control of the various Active signals */
extern FSC_STATUS fscCsArbActiveStatusGet
    ( 
    UINT16 * const activeStatus,
    BOOL const activeReg 
    );

#if (defined FSC_OPERATIONAL_MODE)
/* Set the state of this ControlSafe Computer to active */
extern FSC_STATUS fscCsArbActiveStatusSet
    ( 
    FSCCS_ASSERT_STATUS const status 
    );
#endif

/* Provides status of the various Chassis Health signals */
extern FSC_STATUS fscCsArbChassisStatusGet
    ( 
    FSCCS_ASSERT_STATUS * const statusCpuA,
    FSCCS_ASSERT_STATUS * const statusCpuB,
    BOOL const localChassis 
    );

#endif


/* ------ Voting FPGA Configuration - Internal Use Only ------ */

#if (defined FSC_CPU_BOARD) 

/* Initiate FPGA configuration */
extern FSC_STATUS fscCsVFpgaConfigInit
    ( 
    FSCCS_ENABLE_STATUS const mode 
    );

/* Is the FPGA ready for the next word? */
extern FSC_STATUS fscCsVFpgaIsReady
    ( 
    BOOL * const status 
    );

/* Voting FPGA Configuration Status Register */
extern FSC_STATUS fscCsVFpgaConfigStatusGet
    ( 
    BOOL * const status 
    );

/* Voting FPGA Configuration Data Register */
extern FSC_STATUS fscCsVFpgaConfigDataPut
    ( 
    UINT16 const data 
    );

/* Done with the configuration */
extern FSC_STATUS fscCsVFpgaConfigDone
    ( 
    void 
    );

#endif


/* ------ RTD - Internal Use Only ------ */

/* Read and return the given register offset */
extern FSC_STATUS fscCsDiagGet
    ( 
    UINT32 const offset,
    UINT16 * const value
    );

/* Write the given value to the register offset */
extern FSC_STATUS fscCsDiagSet
    ( 
    UINT32 const offset,
    UINT16 const value
    );

/******************************************************************************/

/* ------ Callable by VxWorks only ------ */
extern void fscCsInitDrv
    (
    void
    );

#ifdef __cplusplus
}
#endif

#endif /* __INCfscCsDrv_h__ */

