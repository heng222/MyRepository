/**
* @file GM_Utils_Define.h
* @brief ����ͨ��ģ���õ��ĺ�
* @author Hao Liming
* @date 2010-11-2 15:56:31
* @version
* <pre><b>copyright: CASCO</b></pre>
* <pre><b>email: </b>haoliming@casco.com.cn</pre>
* <pre><b>company: </b>http://www.casco.com.cn</pre>
* <pre><b>All rights reserved.</b></pre>
* <pre><b>modification:</b></pre>
* <pre>Write modifications here.</pre>
*/
#ifndef _GM_DEFINE_H
#define _GM_DEFINE_H

/************  �û�������1��ѡ�����ϵͳ  4ѡ1 *********/
 /*��Ϊwindows������:*/
#ifndef WIN32
#define WIN32
#endif



/*#define LINK_Part*/
#define SFM_Part
#define CFM_Part

#define GM_RSSP1_CHECK_CHN_NUM          2       /**< FSFB˫ͨ��У�� */

#define GM_RSSP1_MAX_USER_DAT_LEN       (480U)     /**< Ϊ����rssp2ͬ����Ϣ��GAL����(20110218)���޸� */
/* ��ΪVXWORKS5_5������:*/
#ifndef WIN32
#ifndef VXWORKS5_5
#define VXWORKS5_5
#endif
#endif
/* ��ΪVXWORKS6_6������:
#ifndef VXWORKS6_6
#define VXWORKS6_6
#endif*/
/* ��ΪQNX������:
#ifndef QNX
#define QNX
#endif
*/
/************  �û�������2��ѡ�� �忨  5ѡ1*********/
/* ��ΪVIOC_UP�壬����
#define _VIOC_6U_UP*/

/* ��ΪVIOC_DN�壬����
#define _VIOC_6U_DN*/

/*��ΪVLE_6U_UP������
#define _VLE_6U_UP*/

/*��ΪVLE_6U_DN������
#define _VLE_6U_DN*/


/*��ΪDVCOM_6U�壬����*/
/*#define _DVCOM_6U
*/
/*��Ϊ ��Ĭ�� �壬����
#define _EMERSON
*/
/*** ���ѡ�����ʹ��VLE6U���ΪVLE-2-RC�����壬������Դ˴�ѡ�� **
#define _VLE_6U_RC*/


/************  �û�������3��ѡ��ǰ��Ŀ��ȷ��SACEM���ֵ�֧�ַ�ʽ *********/
/*�����3ȡ2��Ŀ 
#define Platform_2oo3*/
/*�����������Ŀ,�������궨��*/

/************ �û�������4�����趨��Ϣλ�ĳ��ȣ���ѡ��VSL ��Ӧ�ö��Ƿ�ΪPIC *********/
#define VSL_PACKET_INFO_LEN_RCV            (3U) /*���յ���Ϣλ���ȣ���λΪ4bytes*/
#define VSL_PACKET_INFO_LEN_SND            (1U) /*���͵���Ϣλ���ȣ���λΪ4bytes*/

/*����ǵ�Ƭ�����ն� ���壺
#define PIC16_RCV
*/

/************  �û�������5�� GM�е�Ӧ��ѡ�� *********/
/*����Ҫ��ӡ��log��Ϣ�ȼ���
������ΪС��-10���� ���� GM_Log_Msg�Ĵ�����Ч
������Ϊ���ڵ���-10������������� С�ڵ���n��log��Ϣ������ӡ����.GM������붨���log��Χ�Ǵ��ڵ���0*/
#define LOG_LEVEL    (-1)

/************  �û�������6�� FSFB2�е�Ӧ��ѡ�� *********/
/* ���� FSFB2 SHB BUFFER ֧�ֵ������λ��*/
#define GM_FSFB2_SHB_SIZE_MAX    256U
#define  GM_FSFB2_CON_NUM_MAX 100U
#define GM_FSFB2_VSNID 0U /*Ĭ��0��ԭʼVSNһ��*/
/************  �û�������7�� GM_MQ_FIXED�е�Ӧ��ѡ�� *********/
/* ����GM_MQ_FIXED����Ϣ��������ŵ���Ϣ�� */
#define GM_MQ_FIXED_MSG_NUM        500U
/* ����GM_MQ_FIXED����Ϣ��������ŵ���Ϣ�� */
#define GM_MQ_FIXED_MSG_SIZE    1480U
/*(GM_MQ_FIXED_MSG_SIZE + 2) * (GM_MQ_FIXED_MSG_NUM) ӦС�� ����ϵͳ����������size���� */


/************  �û�������8�� MR�е�Ӧ��ѡ�� *********/
/* ����MR������ŵ��ڴ���� */
#define GM_CHKW_MEMORY_NUM_MAX_EACHSLOT (30U) /**< add by kou on 11-04-20 �����ˢ��ʱ϶���ڴ��������� */
#define GM_CHKW_CREATE_CHKW_NUM_MAX (20U)   /**< add by kou on 11-04-21 ����ϲ�����ĳ��У������������У���ָ��� */

/************  �û�������9�� MUDP�е�Ӧ��ѡ�� *********/
/* ����MUDP�У����ն�SN��Ĵ�С */
#define GM_MUDP_RCV_SN_MAX_NUM (15U) /* sjz: ���ն�SN��Ĵ�С */

/************  �û������� ���� *********/
/*�������ϵͳ�ظ�����*/
/*��ΪVXWORKSʱ����VXWORKS*/
#ifdef VXWORKS5_5
#ifndef VXWORKS
#define VXWORKS
#endif
#undef VXWORKS6_6
#undef WIN32
#undef QNX
#endif

#ifdef VXWORKS6_6
#ifndef VXWORKS
#define VXWORKS
#endif
#undef VXWORKS5_5
#undef WIN32
#undef QNX
#endif

#ifdef WIN32
#undef VXWORKS
#undef VXWORKS5_5
#undef VXWORKS6_6
#undef QNX
#endif

#ifdef QNX
#undef VXWORKS
#undef VXWORKS5_5
#undef VXWORKS6_6
#undef WIN32
#endif

/*����忨�ظ�����  
_VLE_6U_RC    ��BIOS Timeʱ����Ҫ��֧��VLE RC��
_6U            VIOC VLE��UP DN�� DVCOM�嶼��Ҫ        DRAM HD WD TIMER SYSTIMESTAMP
_VLE_6U        VLE(UP DN)��Ҫ�����ں�VIOC����    DRAM
_EMERSON    CPCI6200��Ҫ                        HD WD Timer SYSTIMESTAMP BIOSTime
*/

/*Ϊ _VLE_6U_UP�壬 ����궨��_6U,�ų���_VIOC�Ķ���*/
#ifdef _VLE_6U_UP
#define _VLE_6U
#define _6U_UP
#define _6U
#undef _EMERSON
#endif

/*Ϊ_VLE_6U_DN��*/
#ifdef _VLE_6U_DN
#define _VLE_6U
#define _6U_DN
#define _6U
#undef _EMERSON
#endif

/*Ϊ VIOC�壬 VIOC��VLE_6U��������һ��*/
#ifdef _VIOC_6U_UP
#define _6U_UP
#define _6U
#undef _VLE_6U
#undef _EMERSON
#undef _VLE_6U_RC
#endif

/*Ϊ VIOC�壬 VIOC��VLE_6U��������һ��*/
#ifdef _VIOC_6U_DN
#define _6U_DN
#define _6U
#undef _VLE_6U
#undef _EMERSON
#undef _VLE_6U_RC
#endif


/*Ϊ_DVCOM_6U ��*/
#ifdef _DVCOM_6U
#define _6U
#undef _VLE_6U
#undef _EMERSON
#undef _VLE_6U_RC
#endif

/*Ϊ_EMERSON ��*/
#ifdef _EMERSON
#undef _VLE_6U
#undef _6U
#undef _VLE_6U_RC
#endif

/*����SACEM���ֺ궨��*/
#ifdef Platform_2oo3
#define NO_PRINTF
#else/*��2003������Ŀ֧��malloc�Ͷ��ļ�*/

#define GM_SACEM_Malloc_Used
#define GM_SACEM_Initial_From_File
#endif






#endif

