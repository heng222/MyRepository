
/*统计输入的字符串中各字符的个数*/

#include "stdafx.h"

#include "TargetDll.h"

/*求最大公约数*/
TARGETDLL_API int CalcGreatestCommonDivisor(int firstNum, int secondNum)
{
	int exchangeNum = 0;
	int firstSameNum = 0, secondSameNum = 0;

	/*firstSameNum,secondSameNum用于保留输入的两个数的数值，便于计算最小公倍数*/
	firstSameNum = firstNum;
	secondSameNum = secondNum;

	/*先找出两个数中较大的数*/
	if (firstNum < secondNum)
	{
		exchangeNum = firstNum;
		firstNum = secondNum;
		secondNum = exchangeNum;

	}

	/*用较大的数除以较小的数，直到除尽为止*/
	while (firstNum % secondNum != 0)
	{
		exchangeNum = firstNum % secondNum;
		firstNum = secondNum;
		secondNum = exchangeNum;
	}

	printf("最大公约数为：%d\n", secondNum);
	/*两个数的最小公倍数等于这两个数的乘积除以它们的最大公约数*/
	printf("最小公倍数为：%d\n", firstSameNum*secondSameNum / secondNum);

	return secondNum;
}

/*统计英文字符个数*/
TARGETDLL_API int CalcCharacterCount(const char* string)
{
    int character = 0, characterLength = 0;

    /*letterNum为字母个数，spaceNum为空格个数，digitNum为数字个数，otherCharacterNum为其他字符个数*/
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

	printf("这个字符串总的字符个数为：%d\n", characterLength);
	printf("英文字母个数为：%d\n", letterNum);
	printf("空格个数为：%d\n", spaceNum);
	printf("数字个数为：%d\n", digitNum);
	printf("其他字符个数为：%d\n", otherCharacterNum);

	return letterNum;
}
