
/*ͳ��������ַ����и��ַ��ĸ���*/

#include "stdafx.h"

#include "TargetDll.h"

/*�����Լ��*/
TARGETDLL_API int CalcGreatestCommonDivisor(int firstNum, int secondNum)
{
	int exchangeNum = 0;
	int firstSameNum = 0, secondSameNum = 0;

	/*firstSameNum,secondSameNum���ڱ������������������ֵ�����ڼ�����С������*/
	firstSameNum = firstNum;
	secondSameNum = secondNum;

	/*���ҳ��������нϴ����*/
	if (firstNum < secondNum)
	{
		exchangeNum = firstNum;
		firstNum = secondNum;
		secondNum = exchangeNum;

	}

	/*�ýϴ�������Խ�С������ֱ������Ϊֹ*/
	while (firstNum % secondNum != 0)
	{
		exchangeNum = firstNum % secondNum;
		firstNum = secondNum;
		secondNum = exchangeNum;
	}

	printf("���Լ��Ϊ��%d\n", secondNum);
	/*����������С�������������������ĳ˻��������ǵ����Լ��*/
	printf("��С������Ϊ��%d\n", firstSameNum*secondSameNum / secondNum);

	return secondNum;
}

/*ͳ��Ӣ���ַ�����*/
TARGETDLL_API int CalcCharacterCount(const char* string)
{
    int character = 0, characterLength = 0;

    /*letterNumΪ��ĸ������spaceNumΪ�ո������digitNumΪ���ָ�����otherCharacterNumΪ�����ַ�����*/
    int letterNum = 0, spaceNum = 0, digitNum = 0, otherCharacterNum = 0;

    characterLength = strlen(string);

    for (character = 0; character < characterLength; character++)
    {
        if ((string[character] >= 'A' && string[character] <= 'Z') || (string[character] >= 'a' && string[character] <= 'z'))
        {
            letterNum++;
        }
        else if (string[character] == ' ')
        {
            spaceNum++;
        }
        else if (string[character] >= '0' && string[character] <= '9')
        {
            digitNum++;
        }
        else
        {
            otherCharacterNum++;
        }
	}

	printf("����ַ����ܵ��ַ�����Ϊ��%d\n", characterLength);
	printf("Ӣ����ĸ����Ϊ��%d\n", letterNum);
	printf("�ո����Ϊ��%d\n", spaceNum);
	printf("���ָ���Ϊ��%d\n", digitNum);
	printf("�����ַ�����Ϊ��%d\n", otherCharacterNum);

	return letterNum;
}
