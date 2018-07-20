/********************************************************                                                                                                            
 �� �� ���� MAStatusData.c  
 ��    �ߣ� ZC��
 ����ʱ�䣺 2015-04-18
 ������ �г�״̬���ݹ���  
 ��ע�� ��  
********************************************************/
#include "MAStatusData.h"
#include "../../../Common/Copy.h"
#include "../../../Common/MemSet.h"

MaDataStruct gMaDataStruBuff[COMM_TRAIN_SUM_MAX];                                    /*���屾ZC���Ʒ�Χ������г��ƶ���Ȩ����*/
UINT8_S gMaDataIndexBuff[LINE_MAX_TRAIN_ID] = {LINE_MAX_TRAIN_ID};			        /*�����г��ƶ���Ȩ�������飬���鳤��Ϊ��·���ܵ�����г�ID*/
UINT8_S gMaCurSum = 0U;									                            /*��ZC�ƶ���Ȩ��ǰ�г�����*/

NextZcMaDataStruct gNextZcDataStruBuff[COMM_TRAIN_SUM_MAX];               /*��������ZC���Ʒ�Χ������г��ƶ���Ȩ����*/
UINT8_S gNextZcMaDataIndexBuff[LINE_MAX_TRAIN_ID] = {LINE_MAX_TRAIN_ID};  /*��������ZC�г��ƶ���Ȩ�������飬���鳤��Ϊ��·���ܵ�����г�ID*/
UINT8_S gNextZcMaCurSum = 0U;                                             /*��������ZC MA2����*/

/*************************************************
  ������:      GetNextZcMaStatusSum
  ��������:    ��ȡ����ZC�г��ƶ���Ȩ��������
  ����:        ��
  ���:        ��
  ����ֵ:      0u: ��ȡ����ʧ��
               >0u: �г��ƶ���Ȩ��������
*************************************************/
UINT16_S GetNextZcMaStatusSum(void)
{
	UINT16_S rtnValue = DEFAULT_ZERO;
		
	if ((gNextZcMaCurSum > DEFAULT_ZERO) && (gNextZcMaCurSum <= COMM_TRAIN_SUM_MAX))
	{
		rtnValue = gNextZcMaCurSum;
	} 
	else
	{
		rtnValue = 0U;
	}

	return rtnValue;
}

/*************************************************
  ������:      SetNextZcMaStatusSum
  ��������:    ��������ZC�г��ƶ���Ȩ��������
  ����:        const UINT8 maCurSum  �ƶ���ȨĿǰ���� 
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ��������ʧ��
               RETURN_SUCCESS: �������ݳɹ�
*************************************************/
UINT16_S SetNextZcMaStatusSum(const UINT8_S maCurSum)
{
	UINT16_S rtnValue = 0U;

	if ((gNextZcMaCurSum > DEFAULT_ZERO) && (gNextZcMaCurSum <= COMM_TRAIN_SUM_MAX))
	{
		gNextZcMaCurSum = maCurSum;
		rtnValue = RETURN_SUCCESS;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:      GetNextZcMaStatusBufIndex
  ��������:    �����г�ID����ȡ����ZC�г��ƶ���Ȩ���������±�
  ����:        const UINT16_S trainId  �г�ID
  ���:        ��
  ����ֵ:      LINE_MAX_TRAIN_ID:      ��ȡ����ʧ��
               (0u,LINE_MAX_TRAIN_ID): ��ȡ���ݳɹ�
*************************************************/
UINT8_S GetNextZcMaStatusBufIndex(const UINT16_S trainId)
{
	UINT8_S rtnValue = 0U;

	if ((trainId > DEFAULT_ZERO) && (trainId <= LINE_MAX_TRAIN_ID))
	{
		rtnValue = gNextZcMaDataIndexBuff[trainId];
	} 
	else
	{
		rtnValue = LINE_MAX_TRAIN_ID;
	}

	return rtnValue;
}

/*************************************************
  ������:      GetNextZcHandOutType
  ��������:    �����г�ID����ȡ������ƶ���Ȩ������ZC��������
  ����:        const UINT16_S trainId  �г�ID 
  ���:        ��
  ����ֵ:      RETURN_UINT8_MAX_VALUE:    ��ȡ����ʧ��
               <RETURN_UINT8_MAX_VALUE:   ����ZC��������
*************************************************/
UINT8_S GetNextZcHandOutType(const UINT16_S trainId)
{
	UINT8_S trainIndex = 0U;
	UINT8_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		rtnValue = gNextZcDataStruBuff[trainIndex].HandOutType;
	} 
	else
	{
		rtnValue = RETURN_UINT8_MAX_VALUE;
	}

	return rtnValue;
}

/*************************************************
  ������:      SetNextZcHandOutType
  ��������:    �����г�ID�����ü�����ƶ���Ȩ������ZC��������
  ����:        const UINT16_S trainId  �г�ID 
  ���:        ��
  ����ֵ:      RETURN_ERROR: ��������ʧ��
               RETURN_SUCCESS: �ɹ���������ZC��������
*************************************************/
UINT8_S SetNextZcHandOutType(const UINT16_S trainId,const UINT8_S handOutType)
{
	UINT8_S trainIndex = 0U;
	UINT8_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		gNextZcDataStruBuff[trainIndex].HandOutType = handOutType;
		rtnValue = RETURN_SUCCESS;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:      GetNextZcId
  ��������:    �����г�ID����ȡ������ƶ���Ȩ������ZCID
  ����:        const UINT16_S trainId  �г�ID 
  ���:        ��
  ����ֵ:      RETURN_UINT16_MAX_VALUE: ��ȡ����ʧ��
               <RETURN_UINT16_MAX_VALUE: ����ZCID
*************************************************/
UINT16_S GetNextZcId(const UINT16_S trainId)
{
	UINT8_S trainIndex = 0U;
	UINT16_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		rtnValue = gNextZcDataStruBuff[trainIndex].NextId;
	} 
	else
	{
		rtnValue = RETURN_UINT16_MAX_VALUE;
	}

	return rtnValue;
}

/*************************************************
  ������:      SetNextZcId
  ��������:    �����г�ID�����ü�����ƶ���Ȩ������ZCID
  ����:        const UINT16_S trainId  �г�ID 
               const UINT16_S zcId  ����ZC�ı��
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ����ʧ��
               RETURN_SUCCESS: ���óɹ�
*************************************************/
UINT16_S SetNextZcId(const UINT16_S trainId,const UINT16_S zcId)
{
	UINT8_S trainIndex = 0U;
	UINT16_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		gNextZcDataStruBuff[trainIndex].NextId = zcId;
		rtnValue = RETURN_SUCCESS;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:      GetNextZcMaInfoFlag
  ��������:    �����г�ID����ȡ����ZC�г��ƶ���Ȩ���ڱ�־
  ����:        const UINT16_S trainId  �г�ID 
  ���:        ��
  ����ֵ:      RETURN_UINT8_MAX_VALUE: ��ȡ����ʧ��
               FLAG_SET: ����MA
               FLAG_UNSET:������MA
*************************************************/
UINT8_S GetNextZcMaInfoFlag(const UINT16_S trainId)
{
	UINT8_S trainIndex = 0U;
	UINT8_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		rtnValue = gNextZcDataStruBuff[trainIndex].MaInfoFlag;
	} 
	else
	{
		rtnValue = RETURN_UINT8_MAX_VALUE;
	}

	return rtnValue;
}

/*************************************************
  ������:      SetNextZcMaInfoFlag
  ��������:    �����г�ID����������ZC�г��ƶ���Ȩ���ڱ�־
  ����:        const UINT16_S trainId  �г�ID 
               const UINT8_S maInfoFlag  ��ʶ
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ��������ʧ��
               RETURN_SUCCESS: �������ݳɹ�
*************************************************/
UINT8_S SetNextZcMaInfoFlag(const UINT16_S trainId,const UINT8_S maInfoFlag)
{
	UINT8_S trainIndex = 0U;
	UINT8_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		gNextZcDataStruBuff[trainIndex].MaInfoFlag = maInfoFlag;
		rtnValue = RETURN_SUCCESS;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:      GetNextZcMaExceedBoundaryFlag
  ��������:    �����г�ID����ȡ����ZC�г��ƶ���ȨԽ���ֽ���־
  ����:        const UINT16_S trainId  �г�ID 
  ���:        ��
  ����ֵ:      RETURN_ERROR: ��ȡ����ʧ��
               FLAG_SET: Խ���ֽ��
               FLAG_UNSET:δԽ���ֽ��
*************************************************/
UINT8_S GetNextZcMaExceedBoundaryFlag(const UINT16_S trainId)
{
	UINT8_S trainIndex = 0U;
	UINT8_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		rtnValue = gNextZcDataStruBuff[trainIndex].ExceedBoundaryFlag;
	} 
	else
	{
		rtnValue = RETURN_UINT8_MAX_VALUE;
	}

	return rtnValue;
}

/*************************************************
  ������:      GetNextZcMaStatusMaLength
  ��������:    �����г�ID����ȡ����ZC�г��ƶ���Ȩ����
  ����:        const UINT16_S trainId  �г�ID 
  ���:        ��
  ����ֵ:      RETURN_UINT8_MAX_VALUE: ��ȡ����ʧ��
               <RETURN_UINT8_MAX_VALUE:MA2����
*************************************************/
UINT8_S GetNextZcMaStatusMaLength(const UINT16_S trainId)
{
	UINT8_S trainIndex = 0U;
	UINT8_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		rtnValue = gNextZcDataStruBuff[trainIndex].MaLength;
	} 
	else
	{
		rtnValue = RETURN_UINT8_MAX_VALUE;
	}

	return rtnValue;
}

/*************************************************
  ������:      SetNextZcMaStatusMaLength
  ��������:    �����г�ID����ȡ����ZC�г��ƶ���Ȩ����
  ����:        const UINT16_S trainId  �г�ID 
               const UINT8_S maLength  MA����
  ���:        ��
  ����ֵ:      RETURN_ERROR:  ��������ʧ��
               RETURN_SUCCESS:�������ݳɹ�
*************************************************/
UINT8_S SetNextZcMaStatusMaLength(const UINT16_S trainId,const UINT8_S maLength)
{
	UINT8_S trainIndex = 0U;
	UINT8_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		gNextZcDataStruBuff[trainIndex].MaLength = maLength;
		rtnValue = RETURN_SUCCESS;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:      GetNextZcMaHeadLink
  ��������:    ��ȡ�ƶ���Ȩ���LINK
  ����:        const UINT16_S trainId  �г�ID 
  ���:        ��
  ����ֵ:      RETURN_ERROR:  ��ȡ����ʧ��
               >0u: ���LINK
*************************************************/
UINT16_S GetNextZcMaHeadLink(const UINT16_S trianId)
{
	UINT8_S trainIndex = 0U;     /*�����±�*/
	UINT16_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trianId);  /*��ȡ�����±�*/

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		rtnValue = gNextZcDataStruBuff[trainIndex].MaHeadLink;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:      SetNextZcMaHeadLink
  ��������:    �����ƶ���Ȩ���LINK
  ����:        const UINT16_S trainId  �г�ID 
               const UINT16_S link MA���link
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ����ʧ��
               RETURN_SUCCESS: ���óɹ�
*************************************************/
UINT8_S SetNextZcMaHeadLink(const UINT16_S trianId, const UINT16_S link)
{
	UINT8_S trainIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trianId);  /*��ȡ�����±�*/

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		gNextZcDataStruBuff[trainIndex].MaHeadLink = link;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:      GetNextZcMaHeadOffset
  ��������:    ��ȡMA2�ƶ���Ȩ���offset
  ����:        const UINT16_S trainId  �г�ID 
  ���:        ��
  ����ֵ:      RETURN_UINT32_MAX_VALUE: ��ȡ����ʧ��
               <RETURN_UINT32_MAX_VALUE: ���offset
*************************************************/
UINT32_S GetNextZcMaHeadOffset(const UINT16_S trianId)
{
	UINT8_S trainIndex = 0U;     /*�����±�*/
	UINT32_S rtnValue = 0U;

	trainIndex = GetMaStatusBufIndex(trianId);  /*��ȡ�����±�*/

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		rtnValue = gNextZcDataStruBuff[trainIndex].MaHeadOffset;
	}
	else
	{

		rtnValue = RETURN_UINT32_MAX_VALUE;
	}

	return rtnValue;
}

/*************************************************
  ������:      SetNextZcMaHeadOffset
  ��������:    ����MA2�ƶ���Ȩ���offset
  ����:        const UINT16_S trainId  �г�ID 
               const UINT32_S offset  ���ƫ����
  ���:        ��
  ����ֵ:      RETURN_SUCCESS: ���óɹ�
               RETURN_ERROR:   ����ʧ��
*************************************************/
UINT8_S SetNextZcMaHeadOffset(const UINT16_S trianId, const UINT32_S offset)
{
	UINT8_S trainIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = 0U;

	trainIndex = GetMaStatusBufIndex(trianId);  /*��ȡ�����±�*/

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		gNextZcDataStruBuff[trainIndex].MaHeadOffset = offset;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:      GetNextZcMaHeadDir
  ��������:    ��ȡ����ZC�ƶ���Ȩ��㷽��
  ����:        const UINT16_S trainId  �г�ID 
  ���:        ��
  ����ֵ:      RETURN_UINT8_MAX_VALUE: ���óɹ�
               <RETURN_UINT8_MAX_VALUE: ���LINK����
*************************************************/
UINT8_S GetNextZcMaHeadDir(const UINT16_S trainId)
{
	UINT8_S trainIndex = 0U;
	UINT8_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		rtnValue = gNextZcDataStruBuff[trainIndex].MaHeadDir;
	} 
	else
	{
		rtnValue = RETURN_UINT8_MAX_VALUE;
	}

	return rtnValue;
}

/*************************************************
  ������:      SetNextZcMaHeadDir
  ��������:    ��������ZC�ƶ���Ȩ��㷽��
  ����:        const UINT16_S trainId  �г�ID 
               const UINT8_S maHeadDir ���MA����
  ���:        ��
  ����ֵ:      RETURN_SUCCESS: ���óɹ�
               RETURN_ERROR:   ����ʧ��
*************************************************/
UINT8_S SetNextZcMaHeadDir(const UINT16_S trainId,const UINT8_S maHeadDir)
{
	UINT8_S trainIndex = 0U;
	UINT8_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		gNextZcDataStruBuff[trainIndex].MaHeadDir = maHeadDir;
		rtnValue = RETURN_SUCCESS;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:      GetNextZcMaTailLink
  ��������:    ��ȡMA2�ƶ���Ȩ�յ�LINK
  ����:        const UINT16_S trainId  �г�ID 
  ���:        ��
  ����ֵ:      DEFAULT_UINT16_VALUE: ��ȡ����ʧ��
               >0u: ���LINK
*************************************************/
UINT16_S GetNextZcMaTailLink(const UINT16_S trianId)
{
	UINT8_S trainIndex = 0U;     /*�����±�*/
	UINT16_S rtnValue = DEFAULT_UINT16_VALUE;


	trainIndex = GetNextZcMaStatusBufIndex(trianId);  /*��ȡ�����±�*/

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		rtnValue = gNextZcDataStruBuff[trainIndex].MaTailLink;
	}
	else
	{
		rtnValue = DEFAULT_UINT16_VALUE;
	}

	return rtnValue;
}

/*************************************************
  ������:      SetNextZcMaTailLink
  ��������:    �����ƶ���Ȩ�յ�LINK
  ����:        const UINT16_S trainId  �г�ID 
               const UINT16_S link MA�յ�link
  ���:        ��
  ����ֵ:      RETURN_SUCCESS: ���óɹ�
               RETURN_ERROR:   ����ʧ��
*************************************************/
UINT8_S SetNextZcMaTailLink(const UINT16_S trianId, const UINT16_S link)
{
	UINT8_S trainIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trianId);  /*��ȡ�����±�*/

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		gNextZcDataStruBuff[trainIndex].MaTailLink = link;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:      GetNextZcMaTailOffset
  ��������:    ��ȡMA2�ƶ���Ȩ�յ�offset
  ����:        const UINT16_S trainId  �г�ID 
  ���:        ��
  ����ֵ:      RETURN_UINT32_MAX_VALUE: ��ȡ����ʧ��
               <RETURN_UINT32_MAX_VALUE: ���offset
*************************************************/
UINT32_S GetNextZcMaTailOffset(const UINT16_S trianId)
{
	UINT8_S trainIndex = 0U;     /*�����±�*/
	UINT32_S rtnValue = RETURN_UINT32_MAX_VALUE;

	trainIndex = GetMaStatusBufIndex(trianId);  /*��ȡ�����±�*/

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		rtnValue = gNextZcDataStruBuff[trainIndex].MaTailOffset;
	}
	else
	{

		rtnValue = RETURN_UINT32_MAX_VALUE;
	}

	return rtnValue;
}

/*************************************************
  ������:      SetNextZcMaTailOffset
  ��������:    ����MA2�ƶ���Ȩ�յ�offset
  ����:        const UINT16_S trainId  �г�ID 
               const UINT32_S offset MA�յ�offset
  ���:        ��
  ����ֵ:      RETURN_SUCCESS: ���óɹ�
               RETURN_ERROR:   ����ʧ��
*************************************************/
UINT8_S SetNextZcMaTailOffset(const UINT16_S trianId, const UINT32_S offset)
{
	UINT8_S trainIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = 0U;

	trainIndex = GetMaStatusBufIndex(trianId);  /*��ȡ�����±�*/

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		gNextZcDataStruBuff[trainIndex].MaTailOffset = offset;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:      GetNextZcMaTailDir
  ��������:    ��ȡ����ZC�ƶ���Ȩ�յ㷽��
  ����:        const UINT16_S trainId  �г�ID 
  ���:        ��
  ����ֵ:      RETURN_UINT8_MAX_VALUE: ��ȡ����ʧ��
               <RETURN_UINT8_MAX_VALUE: �յ�LINK����
*************************************************/
UINT8_S GetNextZcMaTailDir(const UINT16_S trainId)
{
	UINT8_S trainIndex = 0U;
	UINT8_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		rtnValue = gNextZcDataStruBuff[trainIndex].MaTailDir;
	} 
	else
	{
		rtnValue = RETURN_UINT8_MAX_VALUE;
	}

	return rtnValue;
}

/*************************************************
  ������:      SetNextZcMaTailDir
  ��������:    ��ȡ����ZC�ƶ���Ȩ�յ㷽��
  ����:        const UINT16_S trainId  �г�ID 
               const UINT8_S maTailDir �յ�MA����
  ���:        ��
  ����ֵ:      RETURN_SUCCESS: ���óɹ�
               RETURN_ERROR:   ����ʧ��
*************************************************/
UINT8_S SetNextZcMaTailDir(const UINT16_S trainId,const UINT8_S maTailDir)
{
	UINT8_S trainIndex = 0U;
	UINT8_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		gNextZcDataStruBuff[trainIndex].MaTailDir = maTailDir;
		rtnValue = RETURN_SUCCESS;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:      GetNextZcMaEndAttribute
  ��������:    ��ȡ����ZC�ƶ���Ȩ�յ�����
  ����:        const UINT16_S trainId  �г�ID 
  ���:        ��
  ����ֵ:      RETURN_UINT8_MAX_VALUE: ��ȡ����ʧ��
               >0u:                    �յ�����
*************************************************/
UINT8_S GetNextZcMaEndAttribute(const UINT16_S trainId)
{
	UINT8_S trainIndex = 0U;
	UINT8_S rtnValue = RETURN_UINT8_MAX_VALUE;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		rtnValue = gNextZcDataStruBuff[trainIndex].MaEndAttribute;
	}
	else
	{
		rtnValue = RETURN_UINT8_MAX_VALUE;
	}

	return rtnValue;
}

/*************************************************
  ������:      SetNextZcMaEndAttribute
  ��������:    ��������ZC�ƶ���Ȩ�յ�����
  ����:        const UINT16_S trainId  �г�ID 
               const UINT8_S endAttribute �յ�����
  ���:        ��
  ����ֵ:      RETURN_SUCCESS: ���óɹ�
               RETURN_ERROR:   ����ʧ��
*************************************************/
UINT8_S SetNextZcMaEndAttribute(const UINT16_S trainId, const UINT8_S endAttribute)
{
	UINT8_S trainIndex = 0U;
	UINT8_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		gNextZcDataStruBuff[trainIndex].MaEndAttribute = endAttribute;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:      GetNextZcMaObsNum
  ��������:    ��ȡ����ZC�ƶ���Ȩ��Ӧ�ϰ�������
  ����:        const UINT16_S trainId  �г�ID 
  ���:        ��
  ����ֵ:      RETURN_UINT8_MAX_VALUE: ��ȡ����ʧ��
               <RETURN_UINT8_MAX_VALUE: �ϰ�������
*************************************************/
UINT8_S GetNextZcMaObsNum(const UINT16_S trainId)
{
	UINT8_S trainIndex = 0U;
	UINT8_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		rtnValue = gNextZcDataStruBuff[trainIndex].ObsNum;
	}
	else
	{
		rtnValue = RETURN_UINT8_MAX_VALUE;
	}

	return rtnValue;
}

/*************************************************
  ������:      SetNextZcMaObsNum
  ��������:    ��������ZC�ƶ���Ȩ��Ӧ�ϰ�������
  ����:        const UINT16_S trainId  �г�ID 
               const UINT8_S obsNum �ϰ�������
  ���:        ��
  ����ֵ:      RETURN_SUCCESS: ���óɹ�
               RETURN_ERROR:   ����ʧ��
*************************************************/
UINT8_S SetNextZcMaObsNum(const UINT16_S trainId, const UINT8_S obsNum)
{
	UINT8_S trainIndex = 0U;
	UINT8_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		gNextZcDataStruBuff[trainIndex].ObsNum = obsNum;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:      GetNextZcObsOfMAStru
  ��������:    ��ȡ����ZC�ƶ���Ȩ�ϰ�����Ϣ
  ����:        const UINT16_S trainId  �г�ID                
  ���:        ObsOfMAStruct obsStru[] �ϰ�����Ϣ���� 
  ����ֵ:      RETURN_SUCCESS: ��ȡ�ɹ�
               RETURN_ERROR:   ��ȡʧ��
*************************************************/
UINT8_S GetNextZcObsOfMAStru(const UINT16_S trainId, ObsOfMAStruct obsStru[])
{
	UINT8_S trainIndex = 0U;
	UINT8_S cycle = 0U;
	UINT8_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if ((LINE_MAX_TRAIN_ID != trainIndex) && (NULL != obsStru))
	{
		for (cycle = DEFAULT_ZERO;cycle < MA_AREA_OBS_SUM_MAX;cycle++)
		{
			obsStru[cycle].ObsId = gNextZcDataStruBuff[trainIndex].ObsOfMAStru[cycle].ObsId;
			obsStru[cycle].ObsType = gNextZcDataStruBuff[trainIndex].ObsOfMAStru[cycle].ObsType;
			obsStru[cycle].ObsStatus = gNextZcDataStruBuff[trainIndex].ObsOfMAStru[cycle].ObsStatus;
			obsStru[cycle].ObsLockStatus = gNextZcDataStruBuff[trainIndex].ObsOfMAStru[cycle].ObsLockStatus;

		}
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:      SetNextZcObsOfMAStru
  ��������:    ��������ZC�ƶ���Ȩ�ϰ�����Ϣ
  ����:        const UINT16_S trainId  �г�ID                
               const ObsOfMAStruct obsStru[] �ϰ�����Ϣ����
               const UINT8_S obsNum �ϰ�������
  ���:        ��
  ����ֵ:      RETURN_SUCCESS: ��ȡ�ɹ�
               RETURN_ERROR:   ��ȡʧ��
*************************************************/
UINT8_S SetNextZcObsOfMAStru(const UINT16_S trainId,const ObsOfMAStruct obsStru[],const UINT8_S obsNum)
{
	UINT8_S trainIndex = 0U;
	UINT8_S cycle = 0U;
	UINT8_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if ((LINE_MAX_TRAIN_ID != trainIndex) && (NULL != obsStru))
	{
		for (cycle = DEFAULT_ZERO;cycle < obsNum;cycle++)
		{
			gNextZcDataStruBuff[trainIndex].ObsOfMAStru[cycle].ObsId = obsStru[cycle].ObsId;
			gNextZcDataStruBuff[trainIndex].ObsOfMAStru[cycle].ObsType = obsStru[cycle].ObsType;
			gNextZcDataStruBuff[trainIndex].ObsOfMAStru[cycle].ObsStatus = obsStru[cycle].ObsStatus;
			gNextZcDataStruBuff[trainIndex].ObsOfMAStru[cycle].ObsLockStatus = obsStru[cycle].ObsLockStatus;
		}

		gNextZcDataStruBuff[trainIndex].ObsNum = obsNum;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:      GetNextZcMaTsrNum
  ��������:    ��ȡ����ZC�ƶ���Ȩ��ӦTrs����
  ����:        const UINT16_S trainId  �г�ID                
  ���:        ��
  ����ֵ:      RETURN_UINT8_MAX_VALUE: ��ȡ����ʧ��
               <RETURN_UINT8_MAX_VALUE: ��ʱ��������
*************************************************/
UINT8_S GetNextZcMaTsrNum(const UINT16_S trainId)
{
	UINT8_S trainIndex = 0U;
	UINT8_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		rtnValue = gNextZcDataStruBuff[trainIndex].TsrNum;
	}
	else
	{
		rtnValue = RETURN_UINT8_MAX_VALUE;
	}

	return rtnValue;
}

/*************************************************
  ������:      SetNextZcMaTsrNum
  ��������:    �����ƶ���Ȩ��Ӧ��ʱ��������
  ����:        const UINT16_S trainId  �г�ID
               const UINT8_S tsrNum    ��ʱ��������
  ���:        ��
  ����ֵ:      RETURN_SUCCESS:  ���óɹ�
               RETURN_ERROR:    ����ʧ��
*************************************************/
UINT8_S SetNextZcMaTsrNum(const UINT16_S trainId, const UINT8_S tsrNum)
{
	UINT8_S trainIndex = 0U;
	UINT8_S rtnValue = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if (LINE_MAX_TRAIN_ID != trainIndex)
	{
		gNextZcDataStruBuff[trainIndex].TsrNum = tsrNum;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:      GetNextZcTsrOfMAStru
  ��������:    ��ȡ����ZC�ƶ���ȨTsr��Ϣ
  ����:        const UINT16_S trainId    �г�ID
  ���:        TsrOfMAStruct ObsOfMAStru Tsr��Ϣ
  ����ֵ:      RETURN_SUCCESS:  ��ȡ�ɹ�
               RETURN_ERROR:    ��ȡʧ��
*************************************************/
UINT8_S GetNextZcTsrOfMAStru(const UINT16_S trainId, TsrOfMAStruct tsrOfMAStru[])
{
	UINT8_S trainIndex = 0U;
	UINT8_S rtnValue = 0U;
	UINT8_S cycle = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if ((LINE_MAX_TRAIN_ID != trainIndex) && (NULL != tsrOfMAStru))
	{
		for (cycle = DEFAULT_ZERO;cycle < MA_AREA_TSR_SUM_MAX;cycle++)
		{
		    /*pbw 20161021 ���Ӹ�ֵZCID */            
            tsrOfMAStru[cycle].BelongZcId = gNextZcDataStruBuff[trainId].TsrOfMAStru[cycle].BelongZcId;
			tsrOfMAStru[cycle].TsrHeadLink = gNextZcDataStruBuff[trainId].TsrOfMAStru[cycle].TsrHeadLink;
			tsrOfMAStru[cycle].TsrHeadOffset = gNextZcDataStruBuff[trainId].TsrOfMAStru[cycle].TsrHeadOffset;
			tsrOfMAStru[cycle].TsrTailLink = gNextZcDataStruBuff[trainId].TsrOfMAStru[cycle].TsrTailLink;
			tsrOfMAStru[cycle].TsrTailOffset = gNextZcDataStruBuff[trainId].TsrOfMAStru[cycle].TsrTailOffset;
			tsrOfMAStru[cycle].TsrSpeed = gNextZcDataStruBuff[trainId].TsrOfMAStru[cycle].TsrSpeed;
		}
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:      SetNextZcTsrOfMAStru
  ��������:    ��������ZC�ƶ���ȨTsr��Ϣ
  ����:        const UINT16_S trainId    �г�ID
               const TsrOfMAStruct* tsrOfMAStru Tsr��Ϣ
               const UINT8_S tsrNum  TSR����
  ���:        ��
  ����ֵ:      RETURN_SUCCESS:  ���óɹ�
               RETURN_ERROR:    ����ʧ��
*************************************************/
UINT8_S SetNextZcTsrOfMAStru(const UINT16_S trainId, const TsrOfMAStruct* tsrOfMAStru,const UINT8_S tsrNum)
{
	UINT8_S trainIndex = 0U;
	UINT8_S rtnValue = 0U;
	UINT8_S cycle = 0U;

	trainIndex = GetNextZcMaStatusBufIndex(trainId);

	if ((LINE_MAX_TRAIN_ID != trainIndex) && (tsrNum < MA_AREA_TSR_SUM_MAX) && (NULL != tsrOfMAStru))
	{
		for (cycle = DEFAULT_ZERO;cycle < tsrNum;cycle++)
		{
		    /*pbw 20161021 ���Ӹ�ֵZCID */     
            gNextZcDataStruBuff[trainId].TsrOfMAStru[cycle].BelongZcId = tsrOfMAStru[cycle].BelongZcId;
			gNextZcDataStruBuff[trainId].TsrOfMAStru[cycle].TsrHeadLink = tsrOfMAStru[cycle].TsrHeadLink;
			gNextZcDataStruBuff[trainId].TsrOfMAStru[cycle].TsrHeadOffset = tsrOfMAStru[cycle].TsrHeadOffset;
			gNextZcDataStruBuff[trainId].TsrOfMAStru[cycle].TsrTailLink = tsrOfMAStru[cycle].TsrTailLink;
			gNextZcDataStruBuff[trainId].TsrOfMAStru[cycle].TsrTailOffset = tsrOfMAStru[cycle].TsrTailOffset;
			gNextZcDataStruBuff[trainId].TsrOfMAStru[cycle].TsrSpeed = tsrOfMAStru[cycle].TsrSpeed;
		}

		gNextZcDataStruBuff[trainId].TsrNum = tsrNum;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:      SetNextZcMaStatusTrainId
  ��������:    ��������ZC����ĳ�±��Ӧ���г�ID
  ����:        const UINT16_S trainId    �г�ID
  ���:        ��
  ����ֵ:      RETURN_SUCCESS:  ���óɹ�
               RETURN_ERROR:    ����ʧ��
*************************************************/
UINT8_S SetNextZcMaStatusTrainId(const UINT16_S trainId)
{
	UINT16_S bufIndex = LINE_MAX_TRAIN_ID;
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetNextZcMaStatusBufIndex(trainId);

	if (LINE_MAX_TRAIN_ID == bufIndex)
	{
		/*����*/
		if (gNextZcMaCurSum >= COMM_TRAIN_SUM_MAX)
		{
			/*�������Ϣ,����ʧ��*/
		} 
		else
		{
			/*�ƶ���Ȩ��Ϣ*/
			gNextZcDataStruBuff[gNextZcMaCurSum].TrainID = trainId;
			gNextZcMaDataIndexBuff[trainId] = gNextZcMaCurSum;
			gNextZcMaCurSum++;
			rtnValue = RETURN_SUCCESS;
		}
	} 
	else
	{
		if (COMM_TRAIN_SUM_MAX <= bufIndex )
		{
            rtnValue = RETURN_ERROR;			
		} 
		else
		{
            gNextZcDataStruBuff[bufIndex].TrainID = trainId;
            rtnValue = RETURN_SUCCESS;
		}
	}

	return rtnValue;
}

/*************************************************
  ������:      DeleteNextZcSingleTrainMaInfo
  ��������:    ɾ������ZC���뵥���г��ƶ���Ȩ��Ϣ
  ����:        const UINT16_S trainId    �г�ID
  ���:        ��
  ����ֵ:      ��
*************************************************/
void DeleteNextZcSingleTrainMaInfo(const UINT16_S trainId)
{
	UINT8_S bufIndex = 0U;
	UINT8_S cycle = DEFAULT_ZERO;

	bufIndex = GetNextZcMaStatusBufIndex(trainId);

	/**/
	if (LINE_MAX_TRAIN_ID == bufIndex)
	{
		/*������*/
	} 
	else
	{
		/*�����Ϣ*/
		if (bufIndex == (GetNextZcMaStatusSum() - 1U))
		{
			MemorySet(&gNextZcDataStruBuff[bufIndex],((UINT32_S)(sizeof(NextZcMaDataStruct))),
                        0U,((UINT32_S)(sizeof(NextZcMaDataStruct))));
		} 
		else
		{
			for (cycle = bufIndex + 1U;cycle < GetNextZcMaStatusSum();cycle++)
			{
				MemoryCpy(&gNextZcDataStruBuff[cycle - 1U],((UINT32_S)(sizeof(NextZcMaDataStruct))),
                            &gNextZcDataStruBuff[cycle],((UINT32_S)(sizeof(NextZcMaDataStruct))));

				/*������������*/
				gNextZcMaDataIndexBuff[gNextZcDataStruBuff[cycle - 1U].TrainID] = cycle - 1U;
			}

			MemorySet(&gNextZcDataStruBuff[gNextZcMaCurSum - 1U],((UINT32_S)(sizeof(NextZcMaDataStruct))),
                         0U,((UINT32_S)(sizeof(NextZcMaDataStruct))));
		}

		if (gNextZcMaCurSum > 0U)
		{
			gNextZcMaCurSum--;
		} 
		else
		{
			gNextZcMaCurSum = 0U;
		}

		gNextZcMaDataIndexBuff[trainId] = LINE_MAX_TRAIN_ID;
	}
}

/*************************************************
  ������:      ClearNextZcSingleTrainMaInfo
  ��������:    �������ZC���뵥���г��ƶ���Ȩ��Ϣ
  ����:        const UINT16_S trainId    �г�ID
  ���:        ��
  ����ֵ:      ��
*************************************************/
void ClearNextZcSingleTrainMaInfo(const UINT16_S trainId)
{
	UINT8_S bufIndex = 0U;

	bufIndex = GetNextZcMaStatusBufIndex(trainId);

	/**/
	if (LINE_MAX_TRAIN_ID == bufIndex)
	{
		/*������*/
	} 
	else
	{
		/*�����Ϣ*/
		MemorySet(&gNextZcDataStruBuff[bufIndex],((UINT32_S)(sizeof(NextZcMaDataStruct))),
                     0U,((UINT32_S)(sizeof(NextZcMaDataStruct))));
		gNextZcDataStruBuff[bufIndex].TrainID = trainId;
	}
}

/*************************************************
  ������:      GetMaStatusData
  ��������:    ��ȡ�ƶ���Ȩ����
  ����:        ��
  ���:        ��
  ����ֵ:      �ƶ���Ȩ�ṹ��������׵�ַ
*************************************************/
MaDataStruct* GetMaStatusData(void)
{
	return gMaDataStruBuff;
}

/*************************************************
  ������:      GetMaStatusSum
  ��������:    ��ȡ�г��ƶ���Ȩ��������
  ����:        ��
  ���:        ��
  ����ֵ:      �г��ƶ���Ȩ��������
*************************************************/
UINT16_S GetMaStatusSum(void)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if ((gMaCurSum > DEFAULT_ZERO) && (gMaCurSum <= COMM_TRAIN_SUM_MAX))
	{
		rtnValue = gMaCurSum;
	} 
	else
	{
		rtnValue = 0U;
	}

	return rtnValue;
}

/*************************************************
  ������:      GetMaStatusTrainId
  ��������:    ��ȡĳ�±��Ӧ���г�ID
  ����:        const UINT16_S bufIndex, �����±� 
  ���:        ��
  ����ֵ:      0u:  ��ȡ����ʧ��
               >0u: �г�ID 
*************************************************/
UINT16_S GetMaStatusTrainId(const UINT16_S bufIndex)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (COMM_TRAIN_SUM_MAX <= bufIndex)
	{
		rtnValue = 0U;
	} 
	else
	{	
        rtnValue = gMaDataStruBuff[bufIndex].TrainID;
	}

	return rtnValue;
}

/*************************************************
  ������:      SetMaStatusTrainId
  ��������:    ����ĳ�±��Ӧ���г�ID
  ����:        const UINT16_S trainId, �г�Id  
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ����ʧ��
               RETURN_SUCCESS: ���óɹ�
*************************************************/
UINT8_S SetMaStatusTrainId(const UINT16_S trainId)
{
	UINT16_S bufIndex = LINE_MAX_TRAIN_ID;
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trainId);

	if (LINE_MAX_TRAIN_ID == bufIndex)
	{
		/*����*/
		if (gMaCurSum >= COMM_TRAIN_SUM_MAX)
		{
			/*�������Ϣ,����ʧ��*/
		} 
		else
		{
			/*�ƶ���Ȩ��Ϣ*/
			gMaDataStruBuff[gMaCurSum].TrainID = trainId;
			gMaDataIndexBuff[trainId] = gMaCurSum;
			gMaCurSum++;
			rtnValue = RETURN_SUCCESS;
		}
	} 
	else
	{
		if (COMM_TRAIN_SUM_MAX <= bufIndex)
		{
            rtnValue = RETURN_ERROR;		
		} 
		else
		{
            gMaDataStruBuff[bufIndex].TrainID = trainId;
            rtnValue = RETURN_SUCCESS;
		}
	}

	return rtnValue;
}

/*************************************************
  ������:      GetMaStatusBufIndex
  ��������:    ��ȡָ���г�ID������
  ����:        const UINT16_S trainId, �г�Id  
  ���:        ��
  ����ֵ:      LINE_MAX_TRAIN_ID:      ��ȡʧ��
               [1u,LINE_MAX_TRAIN_ID): ��ȡ�ɹ�
*************************************************/
UINT8_S GetMaStatusBufIndex(const UINT16_S trainId)
{
	UINT8_S rtnValue = DEFAULT_ZERO;

	if ((trainId > DEFAULT_ZERO) && (trainId < LINE_MAX_TRAIN_ID))
	{
		rtnValue = gMaDataIndexBuff[trainId];
	} 
	else
	{
		rtnValue = LINE_MAX_TRAIN_ID;
	}

	return rtnValue;
}

/*************************************************
  ������:      GeSingleMaInfo
  ��������:    ��ȡָ���г�ID��MA��Ϣ
  ����:        const UINT16_S trainId, �г�Id  
  ���:        MaDataStruct *singleMaInfo ,MA�ṹ��ָ��
  ����ֵ:      RETURN_ERROR:  ��ȡʧ��
               RETURN_SUCESS: ��ȡ�ɹ�
*************************************************/
UINT8_S GeSingleMaInfo(const UINT16_S trainId,MaDataStruct *singleMaInfo)
{
	UINT8_S bufIndex = 0U;
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trainId);

	if ((LINE_MAX_TRAIN_ID != bufIndex) && (NULL != singleMaInfo))
	{
		MemoryCpy(singleMaInfo,sizeof(MaDataStruct),&gMaDataStruBuff[bufIndex],sizeof(MaDataStruct));
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:      GetMaType
  ��������:    ��ȡ�ƶ���Ȩ����
  ����:        const UINT16_S trainId, �г�Id  
  ���:        ��
  ����ֵ:      RETURN_UINT8_MAX_VALUE:  ��ȡʧ��
               >0u:                     ��ȡ�ɹ�
*************************************************/
UINT8_S GetMaType(const UINT16_S trianId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*��ȡ�����±�*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		rtnValue = gMaDataStruBuff[bufIndex].MaType;
	}
	else
	{
		rtnValue = RETURN_UINT8_MAX_VALUE;
	}

	return rtnValue;
}

/*************************************************
  ������:      SetMaType
  ��������:    �����ƶ���Ȩ����
  ����:        const UINT16_S trainId, �г�Id  
               const UINT8_S maType, MA����
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetMaType(const UINT16_S trianId,const UINT8_S maType)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*��ȡ�����±�*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		if ((NORMAL_MA_TYPE == maType)
			|| (ABNORMAL_MA_TYPE == maType)
			|| (CANCELLATION_MA_TYPE == maType)
			|| (NO_MA_TYPE == maType))
		{
			gMaDataStruBuff[bufIndex].MaType = maType;
		} 
		else
		{
			gMaDataStruBuff[bufIndex].MaType = DEFAULT_ZERO;
		}
		
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:      GetMaHeadLink
  ��������:    ��ȡ�ƶ���Ȩ���LINK
  ����:        const UINT16_S trainId, �г�Id
  ���:        ��
  ����ֵ:      RETURN_UINT16_MAX_VALUE:    ��ȡʧ��
               >0u:  ��ȡ�ɹ�
*************************************************/
UINT16_S GetMaHeadLink(const UINT16_S trianId)
{
	UINT16_S bufIndex = RETURN_UINT16_MAX_VALUE;     /*�����±�*/
	UINT16_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*��ȡ�����±�*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		rtnValue = gMaDataStruBuff[bufIndex].MaHeadLink;
	}
	else
	{
		rtnValue = RETURN_UINT16_MAX_VALUE;
	}

	return rtnValue;
}

/*************************************************
  ������:      SetMaHeadLink
  ��������:    �����ƶ���Ȩ���LINK
  ����:        const UINT16_S trainId, �г�Id
               const UINT16_S link, MA���link
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetMaHeadLink(const UINT16_S trianId, const UINT16_S link)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*��ȡ�����±�*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		gMaDataStruBuff[bufIndex].MaHeadLink = link;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:      GetMaHeadOffset
  ��������:    ��ȡ�ƶ���Ȩ���offset
  ����:        const UINT16_S trainId, �г�Id
  ���:        ��
  ����ֵ:      RETURN_UINT32_MAX_VALUE:  ��ȡʧ��
               >0u:                      ��ȡ�ɹ�
*************************************************/
UINT32_S GetMaHeadOffset(const UINT16_S trianId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT32_S rtnValue = DEFAULT_ZERO; 

	bufIndex = GetMaStatusBufIndex(trianId);  /*��ȡ�����±�*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		rtnValue = gMaDataStruBuff[bufIndex].MaHeadOffset;
	}
	else
	{
		rtnValue = RETURN_UINT32_MAX_VALUE;
	}

	return rtnValue;
}

/*************************************************
  ������:      SetMaHeadOffset
  ��������:    �����ƶ���Ȩ���offset
  ����:        const UINT16_S trainId, �г�Id
               const UINT32_S offset,  MA���offset
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetMaHeadOffset(const UINT16_S trianId, const UINT32_S offset)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*��ȡ�����±�*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		gMaDataStruBuff[bufIndex].MaHeadOffset = offset;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:      GetMaHeadDir
  ��������:    ��ȡ�ƶ���Ȩ��㷽��
  ����:        const UINT16_S trainId, �г�Id
  ���:        ��
  ����ֵ:      DEFAULT_UINT8_VALUE:  ��ȡʧ��
               >0u:                  ��ȡ�ɹ�
*************************************************/
UINT8_S GetMaHeadDir(const UINT16_S trianId)
{
	UINT16_S bufIndex = DEFAULT_UINT8_VALUE;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*��ȡ�����±�*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		rtnValue = gMaDataStruBuff[bufIndex].MaHeadDir;
	}
	else
	{
		rtnValue = DEFAULT_UINT8_VALUE;
	}

	return rtnValue;
}

/*************************************************
  ������:      SetMaHeadDir
  ��������:    �����ƶ���Ȩ��㷽��
  ����:        const UINT16_S trainId, �г�Id
               const UINT8_S dir,      MA��㷽��
  ���:        ��
  ����ֵ:      RETURN_ERROR:       ����ʧ��
               RETURN_SUCCESS:     ���óɹ�
*************************************************/
UINT8_S SetMaHeadDir(const UINT16_S trianId, const UINT8_S dir)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*��ȡ�����±�*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		gMaDataStruBuff[bufIndex].MaHeadDir = dir;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:      GetMaTailLink
  ��������:    ��ȡ�ƶ���Ȩ�յ�LINK
  ����:        const UINT16_S trainId, �г�Id
  ���:        ��
  ����ֵ:      0:    ��ȡʧ��
               >0u:  ��ȡ�ɹ�
*************************************************/
UINT16_S GetMaTailLink(const UINT16_S trianId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT16_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*��ȡ�����±�*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		rtnValue = gMaDataStruBuff[bufIndex].MaTailLink;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:      SetMaTailLink
  ��������:    �����ƶ���Ȩ�յ�LINK
  ����:        const UINT16_S trainId, �г�Id
               const UINT16_S link, MA�յ�link
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetMaTailLink(const UINT16_S trianId, const UINT16_S link)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*��ȡ�����±�*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		gMaDataStruBuff[bufIndex].MaTailLink = link;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:      GetMaTailOffset
  ��������:    ��ȡ�ƶ���Ȩ�յ�offset
  ����:        const UINT16_S trainId, �г�Id
  ���:        ��
  ����ֵ:      RETURN_UINT32_MAX_VALUE:  ��ȡʧ��
               [0u,RETURN_UINT32_MAX_VALUE): ��ȡ�ɹ�
*************************************************/
UINT32_S GetMaTailOffset(const UINT16_S trianId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT32_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*��ȡ�����±�*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		rtnValue = gMaDataStruBuff[bufIndex].MaTailOffset;
	}
	else
	{
		rtnValue = RETURN_UINT32_MAX_VALUE;
	}

	return rtnValue;
}

/*************************************************
  ������:      SetMaTailOffset
  ��������:    �����ƶ���Ȩ�յ�offset
  ����:        const UINT16_S trainId, �г�Id
               const UINT32_S offset,  MA�յ�offset
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetMaTailOffset(const UINT16_S trianId, const UINT32_S offset)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*��ȡ�����±�*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		gMaDataStruBuff[bufIndex].MaTailOffset = offset;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:      GetMaTailDir
  ��������:    ��ȡ�ƶ���Ȩ�յ㷽��
  ����:        const UINT16_S trainId, �г�Id
  ���:        ��
  ����ֵ:      RETURN_ERROR:  ��ȡʧ��
               >0u:                  ��ȡ�ɹ�
*************************************************/
UINT8_S GetMaTailDir(const UINT16_S trianId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*��ȡ�����±�*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		rtnValue = gMaDataStruBuff[bufIndex].MaTailDir;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:      SetMaTailDir
  ��������:    �����ƶ���Ȩ�յ㷽��
  ����:        const UINT16_S trainId, �г�Id
               const UINT8_S dir,      MA�յ㷽��
  ���:        ��
  ����ֵ:      RETURN_ERROR:       ����ʧ��
               RETURN_SUCCESS:     ���óɹ�
*************************************************/
UINT8_S SetMaTailDir(const UINT16_S trianId, const UINT8_S dir)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*��ȡ�����±�*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		gMaDataStruBuff[bufIndex].MaTailDir = dir;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:      GetMaEndObsId
  ��������:    ��ȡ�ƶ���Ȩ�յ��ϰ���Id
  ����:        const UINT16_S trainId, �г�Id
  ���:        ��
  ����ֵ:      RETURN_ERROR:  ��ȡʧ��
               >0u:                  ��ȡ�ɹ�
*************************************************/
UINT16_S GetMaEndObsId(const UINT16_S trianId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT16_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*��ȡ�����±�*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		rtnValue = gMaDataStruBuff[bufIndex].MaEndObsId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:      SetMaEndObsId
  ��������:    �����ƶ���Ȩ�յ��ϰ���Id
  ����:        const UINT16_S trainId, �г�Id
               const UINT8_S endObstacleId, �յ��ϰ���Id
  ���:        ��
  ����ֵ:      RETURN_ERROR:         ����ʧ��
               RETURN_SUCCESS:       ��ȡ�ɹ�
*************************************************/
UINT8_S SetMaEndObsId(const UINT16_S trianId, const UINT8_S endObstacleId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*��ȡ�����±�*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		gMaDataStruBuff[bufIndex].MaEndObsId = endObstacleId;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:      GetMaEndObsType
  ��������:    ��ȡ�ƶ���Ȩ�յ��ϰ�������
  ����:        const UINT16_S trainId, �г�Id
  ���:        ��
  ����ֵ:      RETURN_ERROR:  ��ȡʧ��
               >0u:           ��ȡ�ɹ�
*************************************************/
UINT8_S GetMaEndObsType(const UINT16_S trianId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*��ȡ�����±�*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		rtnValue = gMaDataStruBuff[bufIndex].MaEndObsType;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:      SetMaEndObsType
  ��������:    �����ƶ���Ȩ�յ��ϰ�������
  ����:        const UINT16_S trainId, �г�Id
               const UINT8_S endObstacleType, �յ��ϰ�������
  ���:        ��
  ����ֵ:      RETURN_ERROR:         ����ʧ��
               RETURN_SUCCESS:       ��ȡ�ɹ�
*************************************************/
UINT8_S SetMaEndObsType(const UINT16_S trianId, const UINT8_S endObstacleType)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*��ȡ�����±�*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		gMaDataStruBuff[bufIndex].MaEndObsType = endObstacleType;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:      GetMaEndAttribute
  ��������:    ��ȡ�ƶ���Ȩ�յ�����
  ����:        const UINT16_S trainId, �г�Id
  ���:        ��
  ����ֵ:      RETURN_ERROR:  ��ȡʧ��
               >0u:           ��ȡ�ɹ�
*************************************************/
UINT8_S GetMaEndAttribute(const UINT16_S trianId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*��ȡ�����±�*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		rtnValue = gMaDataStruBuff[bufIndex].MaEndAttribute;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:      SetMaEndAttribute
  ��������:    �����ƶ���Ȩ�յ�����
  ����:        const UINT16_S trainId, �г�Id
               const UINT8_S endAttribute, �յ�����
  ���:        ��
  ����ֵ:      RETURN_ERROR:         ����ʧ��
               RETURN_SUCCESS:       ��ȡ�ɹ�
*************************************************/
UINT8_S SetMaEndAttribute(const UINT16_S trianId, const UINT8_S endAttribute)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*��ȡ�����±�*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		gMaDataStruBuff[bufIndex].MaEndAttribute = endAttribute;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:      GetMaObsNum
  ��������:    ��ȡ�ƶ���Ȩ��Ӧ�ϰ�������
  ����:        const UINT16_S trainId, �г�Id
  ���:        ��
  ����ֵ:      RETURN_ERROR:  ��ȡʧ��
               >0u:           ��ȡ�ɹ�
*************************************************/
UINT8_S GetMaObsNum(const UINT16_S trianId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*��ȡ�����±�*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		rtnValue = gMaDataStruBuff[bufIndex].ObsNum;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:      SetMaObsNum
  ��������:    �����ƶ���Ȩ��Ӧ�ϰ�������
  ����:        const UINT16_S trainId, �г�Id
               const UINT8_S obsNum, �ϰ�������
  ���:        ��
  ����ֵ:      RETURN_ERROR:         ����ʧ��
               RETURN_SUCCESS:       ��ȡ�ɹ�
*************************************************/
UINT8_S SetMaObsNum(const UINT16_S trianId, const UINT8_S obsNum)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*��ȡ�����±�*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		gMaDataStruBuff[bufIndex].ObsNum = obsNum;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:      GetObsOfMAStru
  ��������:    ��ȡ�ƶ���Ȩ�ϰ�����Ϣ
  ����:        const UINT16_S trainId, �г�Id
               const UINT8_S bufSize,����ϰ���ṹ�����С(Ԥ��)
  ���:        ObsOfMAStruct obsOfMaStrBuff[],����ϰ���ṹ����
  ����ֵ:      RETURN_ERROR:     ��ȡʧ��
               RETURN_SUCCESS:   ��ȡ�ɹ�
*************************************************/
UINT8_S GetObsOfMAStru(const UINT16_S trianId,const UINT8_S bufSize,ObsOfMAStruct obsOfMaStrBuff[])
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = 0U;
	UINT8_S cycle = 0U;

	bufIndex = GetMaStatusBufIndex(trianId);  /*��ȡ�����±�*/

	if ((LINE_MAX_TRAIN_ID != bufIndex) && (NULL != obsOfMaStrBuff))
	{
		for (cycle = DEFAULT_ZERO;cycle < GetMaObsNum(trianId);cycle++)
		{
			obsOfMaStrBuff[cycle].ObsId = gMaDataStruBuff[bufIndex].ObsOfMAStru[cycle].ObsId;
			obsOfMaStrBuff[cycle].ObsType = gMaDataStruBuff[bufIndex].ObsOfMAStru[cycle].ObsType;
			obsOfMaStrBuff[cycle].ObsStatus = gMaDataStruBuff[bufIndex].ObsOfMAStru[cycle].ObsStatus;
			obsOfMaStrBuff[cycle].ObsLockStatus = gMaDataStruBuff[bufIndex].ObsOfMAStru[cycle].ObsLockStatus;
		}

		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:      SetObsOfMAStru
  ��������:    �����ƶ���Ȩ�ϰ�����Ϣ
  ����:        const UINT16_S trainId, �г�Id
               const ObsOfMAStruct obsOfMABuff[],�ϰ�����Ϣ����
               const UINT8_S obsNum,�ϰ�������
  ���:        ��
  ����ֵ:      RETURN_ERROR:     ����ʧ��
               RETURN_SUCCESS:   ���óɹ�
*************************************************/
UINT8_S SetObsOfMAStru(const UINT16_S trianId, const ObsOfMAStruct obsOfMABuff[],const UINT8_S obsNum)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S cycle = 0U;
	UINT8_S index = 0U;
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*��ȡ�����±�*/

	if ((LINE_MAX_TRAIN_ID != bufIndex) && (obsNum < MA_AREA_OBS_SUM_MAX) && (NULL != obsOfMABuff))
	{
		for (cycle = DEFAULT_ZERO;cycle < obsNum;cycle++)
		{
			gMaDataStruBuff[bufIndex].ObsOfMAStru[cycle].ObsId = obsOfMABuff[index].ObsId;
			gMaDataStruBuff[bufIndex].ObsOfMAStru[cycle].ObsType = obsOfMABuff[index].ObsType;
			gMaDataStruBuff[bufIndex].ObsOfMAStru[cycle].ObsStatus = obsOfMABuff[index].ObsStatus;
			gMaDataStruBuff[bufIndex].ObsOfMAStru[cycle].ObsLockStatus = obsOfMABuff[index].ObsLockStatus;

			index++;
		}

		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

    return rtnValue;
}

/*************************************************
  ������:      GetMaTsrNum
  ��������:    ��ȡ�ƶ���Ȩ��ӦTsr����
  ����:        const UINT16_S trainId, �г�Id
  ���:        ��
  ����ֵ:      RETURN_ERROR:     ��ȡʧ��
               >0u:   Tsr����
*************************************************/
UINT8_S GetMaTsrNum(const UINT16_S trianId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*��ȡ�����±�*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		rtnValue = gMaDataStruBuff[bufIndex].TsrNum;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:      SetMaTsrNum
  ��������:    �����ƶ���Ȩ��Ӧ��ʱ��������
  ����:        const UINT16_S trainId, �г�Id
               const UINT8_S tsrNum, ��ʱ��������
  ���:        ��
  ����ֵ:      RETURN_ERROR:     ����ʧ��
               RETURN_SUCCESS:   ���óɹ�
*************************************************/
UINT8_S SetMaTsrNum(const UINT16_S trianId, const UINT8_S tsrNum)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*��ȡ�����±�*/

	if (LINE_MAX_TRAIN_ID != bufIndex)
	{
		gMaDataStruBuff[bufIndex].TsrNum = tsrNum;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:      GetTsrOfMAStru
  ��������:    ��ȡ�ƶ���ȨTsr��Ϣ
  ����:        const UINT16_S trainId, �г�Id
               const UINT8_S bufSize,����ϰ���ṹ�����С(Ԥ��)
  ���:        TsrOfMAStruct tsrOfMaStrBuff[],�����ʱ���ٽṹ����
  ����ֵ:      RETURN_ERROR:     ��ȡʧ��
               RETURN_SUCCESS:   ��ȡ�ɹ�
*************************************************/
UINT8_S GetTsrOfMAStru(const UINT16_S trianId,const UINT8_S bufSize,TsrOfMAStruct tsrOfMaStrBuff[])
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = 0U;
	UINT8_S cycle = 0U;

	bufIndex = GetMaStatusBufIndex(trianId);  /*��ȡ�����±�*/

	if ((LINE_MAX_TRAIN_ID != bufIndex) && (NULL != tsrOfMaStrBuff))
	{
		for (cycle = DEFAULT_ZERO;cycle < GetMaTsrNum(trianId);cycle++)
		{
			tsrOfMaStrBuff[cycle].TsrSpeed = gMaDataStruBuff[bufIndex].TsrOfMAStru[cycle].TsrSpeed;
			tsrOfMaStrBuff[cycle].TsrHeadLink = gMaDataStruBuff[bufIndex].TsrOfMAStru[cycle].TsrHeadLink;
			tsrOfMaStrBuff[cycle].TsrHeadOffset = gMaDataStruBuff[bufIndex].TsrOfMAStru[cycle].TsrHeadOffset;
			tsrOfMaStrBuff[cycle].TsrTailLink = gMaDataStruBuff[bufIndex].TsrOfMAStru[cycle].TsrTailLink;
			tsrOfMaStrBuff[cycle].TsrTailOffset = gMaDataStruBuff[bufIndex].TsrOfMAStru[cycle].TsrTailOffset;
			tsrOfMaStrBuff[cycle].BelongZcId = gMaDataStruBuff[bufIndex].TsrOfMAStru[cycle].BelongZcId;
		}

		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:      SetTsrOfMAStru
  ��������:    �����ƶ���ȨTsr��Ϣ
  ����:        const UINT16_S trainId, �г�Id
               const TsrOfMAStruct tsrOfMAStru[],Tsr��Ϣ
               const UINT8_S tsrNum,Tsr����
  ���:        ��
  ����ֵ:      RETURN_ERROR:     ����ʧ��
               RETURN_SUCCESS:   ���óɹ�
*************************************************/
UINT8_S SetTsrOfMAStru(const UINT16_S trianId, const TsrOfMAStruct tsrOfMAStru[],const UINT8_S tsrNum)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S cycle = 0U;
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trianId);  /*��ȡ�����±�*/

	if ((LINE_MAX_TRAIN_ID != bufIndex) && (tsrNum < MA_AREA_TSR_SUM_MAX) && (NULL != tsrOfMAStru))
	{
		for (cycle = DEFAULT_ZERO;cycle < tsrNum;cycle++)
		{
		    /*pbw 20161021���Ӹ�ֵZCID */
            gMaDataStruBuff[bufIndex].TsrOfMAStru[cycle].BelongZcId = tsrOfMAStru[cycle].BelongZcId;
			gMaDataStruBuff[bufIndex].TsrOfMAStru[cycle].TsrHeadLink = tsrOfMAStru[cycle].TsrHeadLink;
			gMaDataStruBuff[bufIndex].TsrOfMAStru[cycle].TsrHeadOffset = tsrOfMAStru[cycle].TsrHeadOffset;
			gMaDataStruBuff[bufIndex].TsrOfMAStru[cycle].TsrTailLink = tsrOfMAStru[cycle].TsrTailLink;
			gMaDataStruBuff[bufIndex].TsrOfMAStru[cycle].TsrTailOffset = tsrOfMAStru[cycle].TsrTailOffset;
			gMaDataStruBuff[bufIndex].TsrOfMAStru[cycle].TsrSpeed = tsrOfMAStru[cycle].TsrSpeed;
		}

		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:      DeleteSingleTrainMaInfo
  ��������:    ɾ�������г��ƶ���Ȩ��Ϣ
  ����:        const UINT16_S trainId, �г�Id             
  ���:        ��
  ����ֵ:      ��
*************************************************/
void DeleteSingleTrainMaInfo(const UINT16_S trainId)
{
	UINT8_S bufIndex = 0U;
	UINT8_S cycle = DEFAULT_ZERO;

	bufIndex = GetMaStatusBufIndex(trainId);

	/**/
	if (LINE_MAX_TRAIN_ID == bufIndex)
	{
		/*������*/
	} 
	else
	{
		/*�����Ϣ*/
		if (bufIndex == (GetMaStatusSum()-1U))
		{
			MemorySet(&gMaDataStruBuff[bufIndex],((UINT32_S)(sizeof(MaDataStruct))),0U,((UINT32_S)(sizeof(MaDataStruct))));
		} 
		else
		{
			for (cycle = bufIndex + 1U;cycle < GetMaStatusSum();cycle++)
			{
				MemoryCpy(&gMaDataStruBuff[cycle - 1U],((UINT32_S)(sizeof(MaDataStruct))),
                            &gMaDataStruBuff[cycle],((UINT32_S)(sizeof(MaDataStruct))));

				/*������������*/
				gMaDataIndexBuff[gMaDataStruBuff[cycle - 1U].TrainID] = cycle - 1U;
			}

			MemorySet(&gMaDataStruBuff[gMaCurSum - 1U],((UINT32_S)(sizeof(MaDataStruct))),
                        0U,((UINT32_S)(sizeof(MaDataStruct))));
		}

		if (gMaCurSum > 0U)
		{
			gMaCurSum--;
		} 
		else
		{
			gMaCurSum = 0U;
		}

		gMaDataIndexBuff[trainId] = LINE_MAX_TRAIN_ID;
	}
}

/*************************************************
  ������:      ClearSingleTrainMaInfo
  ��������:    ��������г��ƶ���Ȩ��Ϣ
  ����:        const UINT16_S trainId, �г�Id             
  ���:        ��
  ����ֵ:      ��
*************************************************/
void ClearSingleTrainMaInfo(const UINT16_S trainId)
{
	UINT8_S bufIndex = 0U;

	bufIndex = GetMaStatusBufIndex(trainId);

	/**/
	if (LINE_MAX_TRAIN_ID == bufIndex)
	{
		/*������*/
	} 
	else
	{
		/*�����Ϣ*/
		MemorySet(&gMaDataStruBuff[bufIndex],((UINT32_S)(sizeof(MaDataStruct))),0U,((UINT32_S)(sizeof(MaDataStruct))));
		gMaDataStruBuff[bufIndex].TrainID = trainId;
	}
}
