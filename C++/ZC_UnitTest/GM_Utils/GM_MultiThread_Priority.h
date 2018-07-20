/**
* @file GM_MultiThread_Priority.h
* @brief 为了跨平台,在Windows,Linux,Vxworks的任务优先级上做了一个映射关系
* @author 
* @date 
* @version

*/
#ifndef _GM_MULTITHREAD_PRIORITY_H
#define _GM_MULTITHREAD_PRIORITY_H

#include "GM_Utils_Base.h"

#ifdef __cplusplus
extern "C"
{
#endif /**< __cplusplus */

#ifdef WIN32
#define GM_TASK_PRIORITY_0 THREAD_PRIORITY_HIGHEST
#define GM_TASK_PRIORITY_1 THREAD_PRIORITY_HIGHEST
#define GM_TASK_PRIORITY_2 THREAD_PRIORITY_HIGHEST
#define GM_TASK_PRIORITY_3 THREAD_PRIORITY_HIGHEST
#define GM_TASK_PRIORITY_4 THREAD_PRIORITY_HIGHEST
#define GM_TASK_PRIORITY_5 THREAD_PRIORITY_HIGHEST
#define GM_TASK_PRIORITY_6 THREAD_PRIORITY_HIGHEST
#define GM_TASK_PRIORITY_7 THREAD_PRIORITY_HIGHEST
#define GM_TASK_PRIORITY_8 THREAD_PRIORITY_HIGHEST
#define GM_TASK_PRIORITY_9 THREAD_PRIORITY_HIGHEST
#define GM_TASK_PRIORITY_10 THREAD_PRIORITY_HIGHEST
#define GM_TASK_PRIORITY_11 THREAD_PRIORITY_HIGHEST
#define GM_TASK_PRIORITY_12 THREAD_PRIORITY_HIGHEST
#define GM_TASK_PRIORITY_13 THREAD_PRIORITY_HIGHEST
#define GM_TASK_PRIORITY_14 THREAD_PRIORITY_HIGHEST
#define GM_TASK_PRIORITY_15 THREAD_PRIORITY_HIGHEST
#define GM_TASK_PRIORITY_16 THREAD_PRIORITY_HIGHEST
#define GM_TASK_PRIORITY_17 THREAD_PRIORITY_HIGHEST
#define GM_TASK_PRIORITY_18 THREAD_PRIORITY_HIGHEST
#define GM_TASK_PRIORITY_19 THREAD_PRIORITY_HIGHEST
#define GM_TASK_PRIORITY_20 THREAD_PRIORITY_HIGHEST
#define GM_TASK_PRIORITY_21 THREAD_PRIORITY_HIGHEST
#define GM_TASK_PRIORITY_22 THREAD_PRIORITY_HIGHEST
#define GM_TASK_PRIORITY_23 THREAD_PRIORITY_HIGHEST
#define GM_TASK_PRIORITY_24 THREAD_PRIORITY_HIGHEST
#define GM_TASK_PRIORITY_25 THREAD_PRIORITY_HIGHEST
#define GM_TASK_PRIORITY_26 THREAD_PRIORITY_HIGHEST
#define GM_TASK_PRIORITY_27 THREAD_PRIORITY_HIGHEST
#define GM_TASK_PRIORITY_28 THREAD_PRIORITY_HIGHEST
#define GM_TASK_PRIORITY_29 THREAD_PRIORITY_HIGHEST
#define GM_TASK_PRIORITY_30 THREAD_PRIORITY_ABOVE_NORMAL
#define GM_TASK_PRIORITY_31 THREAD_PRIORITY_ABOVE_NORMAL
#define GM_TASK_PRIORITY_32 THREAD_PRIORITY_ABOVE_NORMAL
#define GM_TASK_PRIORITY_33 THREAD_PRIORITY_ABOVE_NORMAL
#define GM_TASK_PRIORITY_34 THREAD_PRIORITY_ABOVE_NORMAL
#define GM_TASK_PRIORITY_35 THREAD_PRIORITY_ABOVE_NORMAL
#define GM_TASK_PRIORITY_36 THREAD_PRIORITY_ABOVE_NORMAL
#define GM_TASK_PRIORITY_37 THREAD_PRIORITY_ABOVE_NORMAL
#define GM_TASK_PRIORITY_38 THREAD_PRIORITY_ABOVE_NORMAL
#define GM_TASK_PRIORITY_39 THREAD_PRIORITY_ABOVE_NORMAL
#define GM_TASK_PRIORITY_40 THREAD_PRIORITY_ABOVE_NORMAL
#define GM_TASK_PRIORITY_41 THREAD_PRIORITY_ABOVE_NORMAL
#define GM_TASK_PRIORITY_42 THREAD_PRIORITY_ABOVE_NORMAL
#define GM_TASK_PRIORITY_43 THREAD_PRIORITY_ABOVE_NORMAL
#define GM_TASK_PRIORITY_44 THREAD_PRIORITY_ABOVE_NORMAL
#define GM_TASK_PRIORITY_45 THREAD_PRIORITY_ABOVE_NORMAL
#define GM_TASK_PRIORITY_46 THREAD_PRIORITY_ABOVE_NORMAL
#define GM_TASK_PRIORITY_47 THREAD_PRIORITY_ABOVE_NORMAL
#define GM_TASK_PRIORITY_48 THREAD_PRIORITY_ABOVE_NORMAL
#define GM_TASK_PRIORITY_49 THREAD_PRIORITY_ABOVE_NORMAL
#define GM_TASK_PRIORITY_50 THREAD_PRIORITY_ABOVE_NORMAL
#define GM_TASK_PRIORITY_51 THREAD_PRIORITY_ABOVE_NORMAL
#define GM_TASK_PRIORITY_52 THREAD_PRIORITY_ABOVE_NORMAL
#define GM_TASK_PRIORITY_53 THREAD_PRIORITY_ABOVE_NORMAL
#define GM_TASK_PRIORITY_54 THREAD_PRIORITY_ABOVE_NORMAL
#define GM_TASK_PRIORITY_55 THREAD_PRIORITY_ABOVE_NORMAL
#define GM_TASK_PRIORITY_56 THREAD_PRIORITY_ABOVE_NORMAL
#define GM_TASK_PRIORITY_57 THREAD_PRIORITY_ABOVE_NORMAL
#define GM_TASK_PRIORITY_58 THREAD_PRIORITY_ABOVE_NORMAL
#define GM_TASK_PRIORITY_59 THREAD_PRIORITY_ABOVE_NORMAL
#define GM_TASK_PRIORITY_60 THREAD_PRIORITY_NORMAL
#define GM_TASK_PRIORITY_61 THREAD_PRIORITY_NORMAL
#define GM_TASK_PRIORITY_62 THREAD_PRIORITY_NORMAL
#define GM_TASK_PRIORITY_63 THREAD_PRIORITY_NORMAL
#define GM_TASK_PRIORITY_64 THREAD_PRIORITY_NORMAL
#define GM_TASK_PRIORITY_65 THREAD_PRIORITY_NORMAL
#define GM_TASK_PRIORITY_66 THREAD_PRIORITY_NORMAL
#define GM_TASK_PRIORITY_67 THREAD_PRIORITY_NORMAL
#define GM_TASK_PRIORITY_68 THREAD_PRIORITY_NORMAL
#define GM_TASK_PRIORITY_69 THREAD_PRIORITY_NORMAL
#define GM_TASK_PRIORITY_70 THREAD_PRIORITY_NORMAL
#define GM_TASK_PRIORITY_71 THREAD_PRIORITY_BELOW_NORMAL
#define GM_TASK_PRIORITY_72 THREAD_PRIORITY_BELOW_NORMAL
#define GM_TASK_PRIORITY_73 THREAD_PRIORITY_BELOW_NORMAL
#define GM_TASK_PRIORITY_74 THREAD_PRIORITY_BELOW_NORMAL
#define GM_TASK_PRIORITY_75 THREAD_PRIORITY_BELOW_NORMAL
#define GM_TASK_PRIORITY_76 THREAD_PRIORITY_BELOW_NORMAL
#define GM_TASK_PRIORITY_77 THREAD_PRIORITY_BELOW_NORMAL
#define GM_TASK_PRIORITY_78 THREAD_PRIORITY_BELOW_NORMAL
#define GM_TASK_PRIORITY_79 THREAD_PRIORITY_BELOW_NORMAL
#define GM_TASK_PRIORITY_80 THREAD_PRIORITY_LOWEST
#define GM_TASK_PRIORITY_81 THREAD_PRIORITY_LOWEST
#define GM_TASK_PRIORITY_82 THREAD_PRIORITY_LOWEST
#define GM_TASK_PRIORITY_83 THREAD_PRIORITY_LOWEST
#define GM_TASK_PRIORITY_84 THREAD_PRIORITY_LOWEST
#define GM_TASK_PRIORITY_85 THREAD_PRIORITY_LOWEST
#define GM_TASK_PRIORITY_86 THREAD_PRIORITY_LOWEST
#define GM_TASK_PRIORITY_87 THREAD_PRIORITY_LOWEST
#define GM_TASK_PRIORITY_88 THREAD_PRIORITY_LOWEST
#define GM_TASK_PRIORITY_89 THREAD_PRIORITY_LOWEST
#define GM_TASK_PRIORITY_90 THREAD_PRIORITY_IDLE
#define GM_TASK_PRIORITY_91 THREAD_PRIORITY_IDLE
#define GM_TASK_PRIORITY_92 THREAD_PRIORITY_IDLE
#define GM_TASK_PRIORITY_93 THREAD_PRIORITY_IDLE
#define GM_TASK_PRIORITY_94 THREAD_PRIORITY_IDLE
#define GM_TASK_PRIORITY_95 THREAD_PRIORITY_IDLE
#define GM_TASK_PRIORITY_96 THREAD_PRIORITY_IDLE
#define GM_TASK_PRIORITY_97 THREAD_PRIORITY_IDLE
#define GM_TASK_PRIORITY_98 THREAD_PRIORITY_IDLE
#define GM_TASK_PRIORITY_99 THREAD_PRIORITY_IDLE
#endif

#ifdef QNX
#define GM_TASK_PRIORITY_0 1
#define GM_TASK_PRIORITY_1 1
#define GM_TASK_PRIORITY_2 2
#define GM_TASK_PRIORITY_3 3
#define GM_TASK_PRIORITY_4 4
#define GM_TASK_PRIORITY_5 5
#define GM_TASK_PRIORITY_6 6
#define GM_TASK_PRIORITY_7 7
#define GM_TASK_PRIORITY_8 8
#define GM_TASK_PRIORITY_9 9
#define GM_TASK_PRIORITY_10 10
#define GM_TASK_PRIORITY_11 11
#define GM_TASK_PRIORITY_12 12
#define GM_TASK_PRIORITY_13 13
#define GM_TASK_PRIORITY_14 14
#define GM_TASK_PRIORITY_15 15
#define GM_TASK_PRIORITY_16 16
#define GM_TASK_PRIORITY_17 17
#define GM_TASK_PRIORITY_18 18
#define GM_TASK_PRIORITY_19 19
#define GM_TASK_PRIORITY_20 20
#define GM_TASK_PRIORITY_21 21
#define GM_TASK_PRIORITY_22 22
#define GM_TASK_PRIORITY_23 23
#define GM_TASK_PRIORITY_24 24
#define GM_TASK_PRIORITY_25 25
#define GM_TASK_PRIORITY_26 26
#define GM_TASK_PRIORITY_27 27
#define GM_TASK_PRIORITY_28 28
#define GM_TASK_PRIORITY_29 29
#define GM_TASK_PRIORITY_30 30
#define GM_TASK_PRIORITY_31 31
#define GM_TASK_PRIORITY_32 32
#define GM_TASK_PRIORITY_33 33
#define GM_TASK_PRIORITY_34 34
#define GM_TASK_PRIORITY_35 35
#define GM_TASK_PRIORITY_36 36
#define GM_TASK_PRIORITY_37 37
#define GM_TASK_PRIORITY_38 38
#define GM_TASK_PRIORITY_39 39
#define GM_TASK_PRIORITY_40 40
#define GM_TASK_PRIORITY_41 41
#define GM_TASK_PRIORITY_42 42
#define GM_TASK_PRIORITY_43 43
#define GM_TASK_PRIORITY_44 44
#define GM_TASK_PRIORITY_45 45
#define GM_TASK_PRIORITY_46 46
#define GM_TASK_PRIORITY_47 47
#define GM_TASK_PRIORITY_48 48
#define GM_TASK_PRIORITY_49 49
#define GM_TASK_PRIORITY_50 50
#define GM_TASK_PRIORITY_51 51
#define GM_TASK_PRIORITY_52 52
#define GM_TASK_PRIORITY_53 53
#define GM_TASK_PRIORITY_54 54
#define GM_TASK_PRIORITY_55 55
#define GM_TASK_PRIORITY_56 56
#define GM_TASK_PRIORITY_57 57
#define GM_TASK_PRIORITY_58 58
#define GM_TASK_PRIORITY_59 59
#define GM_TASK_PRIORITY_60 60
#define GM_TASK_PRIORITY_61 61
#define GM_TASK_PRIORITY_62 62
#define GM_TASK_PRIORITY_63 63
#define GM_TASK_PRIORITY_64 63
#define GM_TASK_PRIORITY_65 63
#define GM_TASK_PRIORITY_66 63
#define GM_TASK_PRIORITY_67 63
#define GM_TASK_PRIORITY_68 63
#define GM_TASK_PRIORITY_69 63
#define GM_TASK_PRIORITY_70 63
#define GM_TASK_PRIORITY_71 63
#define GM_TASK_PRIORITY_72 63
#define GM_TASK_PRIORITY_73 63
#define GM_TASK_PRIORITY_74 63
#define GM_TASK_PRIORITY_75 63
#define GM_TASK_PRIORITY_76 63
#define GM_TASK_PRIORITY_77 63
#define GM_TASK_PRIORITY_78 63
#define GM_TASK_PRIORITY_79 63
#define GM_TASK_PRIORITY_80 63
#define GM_TASK_PRIORITY_81 63
#define GM_TASK_PRIORITY_82 63
#define GM_TASK_PRIORITY_83 63
#define GM_TASK_PRIORITY_84 63
#define GM_TASK_PRIORITY_85 63
#define GM_TASK_PRIORITY_86 63
#define GM_TASK_PRIORITY_87 63
#define GM_TASK_PRIORITY_88 63
#define GM_TASK_PRIORITY_89 63
#define GM_TASK_PRIORITY_90 63
#define GM_TASK_PRIORITY_91 63
#define GM_TASK_PRIORITY_92 63
#define GM_TASK_PRIORITY_93 63
#define GM_TASK_PRIORITY_94 63
#define GM_TASK_PRIORITY_95 63
#define GM_TASK_PRIORITY_96 63
#define GM_TASK_PRIORITY_97 63
#define GM_TASK_PRIORITY_98 63
#define GM_TASK_PRIORITY_99 63
#endif					    
						    
#ifdef VXWORKS			    
#define GM_TASK_PRIORITY_0 0
#define GM_TASK_PRIORITY_1 1
#define GM_TASK_PRIORITY_2 2
#define GM_TASK_PRIORITY_3 3
#define GM_TASK_PRIORITY_4 4
#define GM_TASK_PRIORITY_5 5
#define GM_TASK_PRIORITY_6 6
#define GM_TASK_PRIORITY_7 7
#define GM_TASK_PRIORITY_8 8
#define GM_TASK_PRIORITY_9 9
#define GM_TASK_PRIORITY_10 10
#define GM_TASK_PRIORITY_11 11
#define GM_TASK_PRIORITY_12 12
#define GM_TASK_PRIORITY_13 13
#define GM_TASK_PRIORITY_14 14
#define GM_TASK_PRIORITY_15 15
#define GM_TASK_PRIORITY_16 16
#define GM_TASK_PRIORITY_17 17
#define GM_TASK_PRIORITY_18 18
#define GM_TASK_PRIORITY_19 19
#define GM_TASK_PRIORITY_20 20
#define GM_TASK_PRIORITY_21 21
#define GM_TASK_PRIORITY_22 22
#define GM_TASK_PRIORITY_23 23
#define GM_TASK_PRIORITY_24 24
#define GM_TASK_PRIORITY_25 25
#define GM_TASK_PRIORITY_26 26
#define GM_TASK_PRIORITY_27 27
#define GM_TASK_PRIORITY_28 28
#define GM_TASK_PRIORITY_29 29
#define GM_TASK_PRIORITY_30 30
#define GM_TASK_PRIORITY_31 31
#define GM_TASK_PRIORITY_32 32
#define GM_TASK_PRIORITY_33 33
#define GM_TASK_PRIORITY_34 34
#define GM_TASK_PRIORITY_35 35
#define GM_TASK_PRIORITY_36 36
#define GM_TASK_PRIORITY_37 37
#define GM_TASK_PRIORITY_38 38
#define GM_TASK_PRIORITY_39 39
#define GM_TASK_PRIORITY_40 40
#define GM_TASK_PRIORITY_41 41
#define GM_TASK_PRIORITY_42 42
#define GM_TASK_PRIORITY_43 43
#define GM_TASK_PRIORITY_44 44
#define GM_TASK_PRIORITY_45 45
#define GM_TASK_PRIORITY_46 46
#define GM_TASK_PRIORITY_47 47
#define GM_TASK_PRIORITY_48 48
#define GM_TASK_PRIORITY_49 49
#define GM_TASK_PRIORITY_50 50
#define GM_TASK_PRIORITY_51 51
#define GM_TASK_PRIORITY_52 52
#define GM_TASK_PRIORITY_53 53
#define GM_TASK_PRIORITY_54 54
#define GM_TASK_PRIORITY_55 55
#define GM_TASK_PRIORITY_56 56
#define GM_TASK_PRIORITY_57 57
#define GM_TASK_PRIORITY_58 58
#define GM_TASK_PRIORITY_59 59
#define GM_TASK_PRIORITY_60 60
#define GM_TASK_PRIORITY_61 61
#define GM_TASK_PRIORITY_62 62
#define GM_TASK_PRIORITY_63 63
#define GM_TASK_PRIORITY_64 64
#define GM_TASK_PRIORITY_65 65
#define GM_TASK_PRIORITY_66 66
#define GM_TASK_PRIORITY_67 67
#define GM_TASK_PRIORITY_68 68
#define GM_TASK_PRIORITY_69 69
#define GM_TASK_PRIORITY_70 70
#define GM_TASK_PRIORITY_71 71
#define GM_TASK_PRIORITY_72 72
#define GM_TASK_PRIORITY_73 73
#define GM_TASK_PRIORITY_74 74
#define GM_TASK_PRIORITY_75 75
#define GM_TASK_PRIORITY_76 76
#define GM_TASK_PRIORITY_77 77
#define GM_TASK_PRIORITY_78 78
#define GM_TASK_PRIORITY_79 79
#define GM_TASK_PRIORITY_80 80
#define GM_TASK_PRIORITY_81 81
#define GM_TASK_PRIORITY_82 82
#define GM_TASK_PRIORITY_83 83
#define GM_TASK_PRIORITY_84 84
#define GM_TASK_PRIORITY_85 85
#define GM_TASK_PRIORITY_86 86
#define GM_TASK_PRIORITY_87 87
#define GM_TASK_PRIORITY_88 88
#define GM_TASK_PRIORITY_89 89
#define GM_TASK_PRIORITY_90 90
#define GM_TASK_PRIORITY_91 91
#define GM_TASK_PRIORITY_92 92
#define GM_TASK_PRIORITY_93 93
#define GM_TASK_PRIORITY_94 94
#define GM_TASK_PRIORITY_95 95
#define GM_TASK_PRIORITY_96 96
#define GM_TASK_PRIORITY_97 97
#define GM_TASK_PRIORITY_98 98
#define GM_TASK_PRIORITY_99 99
#endif

#ifdef __cplusplus
}

#endif /**< __cplusplus */

#endif /**< _GM_MULTITHREAD_PRIORITY_H */

