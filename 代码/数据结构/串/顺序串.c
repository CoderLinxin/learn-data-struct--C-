#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include <assert.h>
#include <errno.h>
#include <string.h>

/*
	串的抽象数据类型:
	ADT String{
		Data:D = {a[i] | a[i] ∈ CharacterSet,i = 1,2,...,n, n>=0}
		Relation:R = {<a[i-1],a[i]> | a[i-1],a[i]∈D, i = 1,2,...,n}
		Operation:
		StrAssign(&T,chars);
		StrCompare(S,T);
		StrLength(S);
		Concat(&T,S1,S2);
		SubString(&Sub,S,pos,len);
		StrCopy(&T,S);
		StrEmpty(S);
		ClearString(&S);
		Index(S,T,pos);
		Replace(&S,T,V);
		StrInsert(&S,pos,T);
		StrDelete(&S,pos,len);
		DestroyString(&S);
	}ADT String
*/


/*****************************************			 符号定义			*****************************************/


#define MAXLENGTH 255 // 顺序串长度(由于可以通过length属性获取长度,因此本例中不设置 '/0' )
#define EXTENSION_SIZE 255 // 字符串一次扩容的大小


/*****************************************			顺序串定义			*****************************************/


struct SString
{
	// char string[MAXLENGTH + 2]; 0号位置预留，外加一个字符串结束标志
	char* string;
	int length;
	int maxLength;
};
typedef struct SString SString;
SString* pSString;

/*****************************************			 方法声明			*****************************************/


bool StrAssign(SString*, char*);// 对串进行赋值
int StrCompare(SString*, SString*);// 比较两个串
int StrLength(SString*);// 求串长
bool Concat(SString*, SString, SString);// 串连结
bool SubString(SString*, SString, int, int);// 求子串
bool StrCopy(SString*, SString);// 串拷贝
bool StrEmpty(SString*);// 串判空
bool ClearString(SString*);// 清空串
int Index_BF(SString, SString, int);// 返回子串的位置(使用BF算法)
int Index_KMP(SString, SString, int*);// 返回子串的位置(使用KMP算法)
int Index_KMP_Improve(SString, SString, int*);// 返回子串的位置(使用改进的KMP算法)
bool ReplaceWithBF(SString*, SString, SString);// 串替换(使用BF算法查找替换串)
bool ReplaceWithKMP(SString*, SString, SString);// 串替换(使用KMP算法查找替换串)
bool StrInsert(SString*, int, SString);// 子串插入
bool StrDelete(SString*, int, int);// 子串删除
int* Get_Next(SString);// 获取模式串的Next数组 
int* GET_Next_Val(SString); // 获取模式串的NextVal数组
bool DestroyString(SString*);// 串销毁


/*****************************************			 方法定义			*****************************************/


/*
	将pContainer所指向的字符串赋值为pContent指向的字符串
	初始条件:pContent指向的字符串存在
	返回结果:赋值成功返回1,赋值失败返回0
*/
bool StrAssign(SString* pContainer, char* pContent)
{
	assert(pContent);

	// 如果string存在则需要释放内存
	if (pContainer->string != NULL)
		free(pContainer->string);

	// 初始化数组
	pContainer->string = (char*)malloc((MAXLENGTH + 2) * sizeof(char));
	pContainer->maxLength = MAXLENGTH;

	if (!pContainer->string)
		printf("内存开辟失败失败原因: %s", strerror(errno));
	int frequency = 1;// 记录数组扩充次数

	int sourceIndex = 0;
	int destinationIndex = 1;// 从1开始存放字符元素
	int length = 0;

	while (pContainer->string[destinationIndex++] = pContent[sourceIndex++])
	{
		length++;

		// 如果pContent的内容大于pContainer->string的容量则需要进行扩容
		if (strlen(pContent) > MAXLENGTH*frequency - 2)
		{
			// 对字符串数组进行扩容
			frequency++;
			char* temp = pContainer->string;
			pContainer->string = (char*)malloc((MAXLENGTH*frequency + 2) * sizeof(char));
			pContainer->maxLength = MAXLENGTH*frequency;

			if (pContainer->string == NULL)
			{
				printf("内存开辟失败失败原因: %s", strerror(errno));
				return false;
			}

			int sIndex = 0, dIndex = 1, count = 0;

			while (count++ < length)
				pContainer->string[dIndex++] = temp[sIndex++];
			free(temp);// 释放内存
		}
	}

	// 字符串结尾标记
	pContainer->string[destinationIndex] = '\0';
	// 初始化数组长度
	pContainer->length = length;
}

/*
	打印数组(测试用)
	由于本例中模拟字符串没有向其尾插入'/0',所以调用字符串相关库函数可能会出错,需要注意
*/
void myPrintf(SString pSString)
{
	int index = 1;
	int count = 0;
	while (count++ < pSString.length)
	{
		putchar(pSString.string[index]);
		index++;
	}

	putchar('\n');
}

/*
	比较pString1和pString2是否相等
	初始条件:pString1、pString2指向的串存在
	返回结果:
		pString1 = pString2:返回0,
		pString > pString2:返回大于0的值,
		pString1 < pString2:返回小于0的值
*/
int StrCompare(SString* pString1, SString* pString2)
{
	assert(pString1->string != NULL);
	assert(pString2->string != NULL);

	int index1 = 1, index2 = 1;

	while ((index1 <= pString1->length) && (index2 <= pString2->length))
		// 寻找第一个不同的元素
		if (pString1->string[index1++] != pString2->string[index2++])
			break;

	return pString1->string[index1 - 1] - pString2->string[index2 - 1];
}

/*
	求pString的长度
	初始条件:pString指向的串存在
	返回结果:返回pString的串长
*/
int StrLength(SString* pString)
{
	assert(pString->string != NULL);

	int length = 0, index = 1;
	while (pString->string[index++])
		length++;

	return pString->length = length;
}

/*
	连接pSourceString1和pSourceString2并赋值给pdestinationString
	初始条件:pSourceString1和pSourceString2指向的串存在
	返回结果:是否拼接成功
*/
bool Concat(SString* pdestinationString, SString pSourceString1, SString pSourceString2)
{
	assert(pSourceString1.string != NULL);
	assert(pSourceString2.string != NULL);

	// 字符串存在则清空引用
	if (pdestinationString != NULL)
		free(pdestinationString->string);

	// 更新新数组长度
	pdestinationString->length = pSourceString1.length + pSourceString2.length;

	// 决定新数组的容量:pdestinationString->length - 1 为了解决边界问题
	// 5/5 + 1 = 2 // bad
	// (5-1/5) + 1 = 1 // good
	int newCapacity = (((pdestinationString->length - 1) / MAXLENGTH) + 1)*MAXLENGTH;
	pdestinationString->string = (char*)malloc((newCapacity + 2) * sizeof(char*));
	pdestinationString->maxLength = newCapacity;

	if (NULL == pdestinationString->string)
	{
		printf("内存开辟失败失败原因: %s", strerror(errno));
		return false;
	}

	// 字符串拼接
	int index = 1;
	int sIndex1 = 1;
	while (pdestinationString->string[index++] = pSourceString1.string[sIndex1++])
	{
		;
	}

	int sIndex2 = 1;
	while (pdestinationString->string[index++] = pSourceString2.string[sIndex2++])
	{
		;
	}

	// 添加字符串结束标志
	pdestinationString->string[index] = '\0';
	return true;
}

/*
	返回pMainString字符串的第postion(不是数组索引)个字符起长度为length的子串赋值给pChildString
	初始条件:
		postion不能越界
		length不能大于剩余子串的最大长度
	返回结果:查找字串成功返回1,否则返回0
*/
bool SubString(SString* pChildString, SString pMainString, int postion, int length)
{

	assert(pMainString.string);

	// 检查是否需要销毁数组
	if (pChildString->string != NULL)
		free(pChildString->string);

	if (postion < 1 || postion > pMainString.length)
	{
		printf("position参数设置错误：应该在%d ~ %d之间。\n", 1, pMainString.length);
		return false;
	}

	if ((length < 0) || (length > pMainString.length - postion + 1))
	{
		printf("length参数设置错误：应该在%d ~ %d之间。\n");
		return false;
	}

	// 重新设置数组大小
	int newCapacity = ((length - 1) / MAXLENGTH + 1)*MAXLENGTH;
	pChildString->string = (char*)malloc((newCapacity + 2) * sizeof(char));
	pChildString->maxLength = newCapacity;
	pChildString->length = length;

	int index = 1;
	while (length-- > 0)
		pChildString->string[index++] = pMainString.string[1 + postion++];

	pChildString->string[index] = '\0';
	return true;
}

/*
	将pdestinationString所指向的字符串拷贝给pSourceString
	初始条件:
		pSourceString指向的字符串存在
	返回结果:拷贝成功返回1,否则返回0
*/
bool StrCopy(SString* pdestinationString, SString pSourceString)
{

	assert(pSourceString.string != NULL);

	int index = 1;
	pdestinationString->length = 0;
	while (pdestinationString->string[index] = pSourceString.string[index])
	{
		pdestinationString->length++;
		index++;
	}

	pdestinationString->string[index] = '\0';
	pdestinationString->maxLength = pSourceString.maxLength;
	return true;
}

/*
	pString指向的字符串是否为空串
	初始条件:pString指向的字符串存在
	返回结果:空串则返回1,否则返回0
*/
bool StrEmpty(SString* pString)
{
	assert(pString->string != NULL);

	return !pString->length;
}

/*
	将pString指向的字符串清空
	初始条件:pString指向的字符串存在
	初始条件:操作无异常返回1,否则返回0
*/
bool ClearString(SString* pString)
{
	assert(pSString->string != NULL);

	pSString->string[1] = '\0';

	return !(pSString->length = 0);
}

/*
	返回pChildString指向的字符串在pManString指向的字符串中第一次出现的位置(使用BF算法)
	参数:
		position:可以指明从主串的哪个位置开始进行匹配
	初始条件:
		pChildString和pManString指向的字符串存在,且pChildString不为空串
		position + pChildString的长度 <= pManString的长度
		position的数值要合法
	返回结果:返回符合条件的子串位置,匹配失败或出现异常返回0
*/
int Index_BF(SString pMianString, SString pChildString, int position)
{
	assert(pMianString.string != NULL);
	assert(pChildString.string != NULL);
	assert(pChildString.length != 0);

	if (position < 1 || (position > pMianString.length))
	{
		printf("参数输入错误");
		return 0;
	}

	int restLength = (position + pChildString.length - 1) > pMianString.length;
	if (restLength)
	{
		printf("主串中第%d起的子串长度小于模式串的长度，匹配失败。\n", restLength);
		return 0;
	}

	// 从主串第position处开始匹配
	int i = position, j = 1;
	while (i <= pMianString.length && j <= pChildString.length)
	{
		// 依次匹配各个字符
		if (pMianString.string[i] == pChildString.string[j])
		{
			i++;
			j++;
		}
		else // 进行下一轮匹配
		{
			i = i - (j - 1) + 1; // 主串指针回溯
			j = 1; // 模式串指针回溯
		}
	}

	if (j > pChildString.length)
		// 匹配成功返回相应位置
		return i - pChildString.length;
	else
		return 0;
}

/*
	获取模式串对应的next数组
	初始条件：
		patternString指向的字符串存在
	返回结果:
		操作正常返回next数组,否则返回NULL;
*/
int* Get_Next(SString patternString)
{
	assert(patternString.string != NULL);

	// 分配next数组空间(从1号索引处开始存值)
	int* next = (int*)malloc(sizeof(int)*(patternString.length+1));

	if (next == NULL)
	{
		printf("内存分配失败，创建next数组失败。");
		return NULL;
	}

	// j用来标识模式串的各个字符，t用来标识next数组中对应位置上的值
	int j = 1, t = 0;
	next[1] = 0;// next数组1号位置固定为0,表示模式串第一个字符就不匹配的情况

	// 由于循环体中存在关于 j+1 的表达式，因此循环条件中 j 不能等于 length
	// 逐个求解Next数组各个位置上的值
	while (j < patternString.length)
	{

		// t == 0 既可以表示当经过多次循环,最长公共前后缀长度为0,t为1(Next[2]),
		// 此时Pi 仍然不等于 Pj,最后 t = 0 == Next[1] 这个特殊标记时
		// 由于不属于模式串第一个字符不匹配的情况我们需要将 next[j + 1] 的值设为1
		if (t == 0 || patternString.string[j] == patternString.string[t])
		{
			// 当第一次进入while循环时也相当于为 next[2] 设置值为1(也是固定值),表示模式串中第二个字符不匹配的情况
			// 有了next[2]这个固定值才能继续进行接下来的迭代
			next[j + 1] = t + 1; 
			j++;
			t++;
		}
		else // Pj != Pi 则继续定位前缀串
			t = next[t];
	}

	return next;
}

/*
	获取模式串对应的next数组
	初始条件：
		patternString指向的字符串存在
	返回结果:
		操作正常返回next数组,否则返回NULL;
*/
int* GET_Next_Val(SString patternString)
{
	assert(patternString.string != NULL);

	int* next = (int*)malloc(sizeof(int)*(patternString.length + 1));
	int* nextVal = (int*)malloc(sizeof(int)*(patternString.length + 1));

	if (next == NULL)
	{
		printf("内存分配失败，创建next数组失败。");
		return NULL;
	}

	// j用来标识模式串的各个字符，t用来标识next数组中对应位置上的值
	int j = 1, t = 0;
	nextVal[1] = 0; // nextVal[1]位置用作特殊标记
	next[1] = 0;

	// 逐个求解Next数组各个位置上的值
	while (j < patternString.length)
	{

		if (t == 0 || patternString.string[j] == patternString.string[t])
		{
			next[j + 1] = t + 1;

			/* 求next数组代码中增加的部分 */ 
			if (patternString.string[j + 1] != patternString.string[next[j + 1]])
				// P[j+1]不等于P[next[j+1]]则下一次回溯可能匹配成功,所以不应该跳过所有可能的匹配,nextVal[j+1]直接等于next[j+1]
				nextVal[j + 1] = next[j + 1]; 
			else
				// P[j+1]等于P[next[j+1]],则根据next数组进行的此次回溯没有意义,因此nextVal[j+1]赋值为nextVal[next[j+1]]
				// nextVal[next[j+1]]记录了其之前求解nextVal值的足迹,
				// 由于必然有(next[j+1]指向j+1号元素左边子串的最长公共前缀后一个字符): next[j+1] < j+1,因此下面的代码是正确的
				nextVal[j + 1] = nextVal[next[j + 1]];
			/* 求next数组代码中增加的部分 */

			j++;
			t++;
		}
		else 
			// 由于上面求next[t+1]的同时可求nextVal[t]  (递推求法)
			// 因此求next[t]的同时可求nextVal[t]
			// 因此使用效率更高的 nextVal[t] 代替 next[t]
			t = nextVal[t]; 
	}

	return next;
}

/*
	返回pChildString指向的字符串在pManString指向的字符串中第一次出现的位置(使用KMP算法)
	参数:
		next:指示每次匹配失败如何确定下一次迭代模式串比较指针指向的next数组
	初始条件:
		pChildString和pManString指向的字符串存在,且pChildString不为空串
	返回结果:返回符合条件的子串位置,匹配失败或出现异常返回0
*/
int Index_KMP(SString pMianString, SString pChildString, int* next)
{
	assert(pMianString.string != NULL);
	assert(pChildString.string != NULL);
	assert(pChildString.length != 0);

	int mainIndex = 1, childIndex = 1;

	while (mainIndex <= pMianString.length && childIndex <= pChildString.length)
	{
		// 当 childIndex在某次回溯被设置为 next[1] == 0 时，也需要让主串比较指针向前移动，且childIndex设置为1
		if (0 == childIndex || pMianString.string[mainIndex] == pChildString.string[childIndex])
		{
			mainIndex++;
			childIndex++;
		}
		else
			childIndex = next[childIndex];

	}

	if (childIndex > pChildString.length)
		return mainIndex - pChildString.length;
	else 
		return 0;


}

/*
	返回pChildString指向的字符串在pManString指向的字符串中第一次出现的位置(使用改进的KMP算法)
	参数:
		next:指示每次匹配失败如何确定下一次迭代模式串比较指针指向的next数组
	初始条件:
		pChildString和pManString指向的字符串存在,且pChildString不为空串
		position + pChildString的长度 <= pManString的长度
	返回结果:返回符合条件的子串位置,匹配失败或出现异常返回0
*/
int Index_KMP_Improve(SString pManString, SString pChildString, int* next)
{

}

/*
	在字符串pMainString中查找字符串pChildString(使用BF算法)，并将pMainString中出现的第一个pChildString用字符串pReplaceString替换
	初始条件:
		pMainString、pChildString、pReplaceString指向的字符串存在,且pChildString不能是空串
		pChildString的长度 <= pMainString的长度
	返回结果:替换成功返回1,替换失败返回0
*/
bool ReplaceWithBF(SString* pMainString, SString pChildString, SString pReplaceString)
{
	assert(pMainString->string != NULL);
	assert(pChildString.string != NULL);
	assert(pReplaceString.string != NULL);
	assert(pChildString.length != 0);

	if (pChildString.length > pMainString->length)
	{
		printf("length参数输入错误。\n");
		return false;
	}

	// 通过BF算法获取模式串在主串中的位置(从第一个字符处开始匹配)
	int position = Index_BF(*pMainString, pChildString,1);

	if (!position)
	{
		printf("替换失败，找不到对应的子串");
		return false;
	}
	else
	{
		// 统一扩容与否的行为，都对主串进行重新赋值
		SString* temp = (SString*)malloc(sizeof(SString));
		temp->string = (char*)malloc(pMainString->maxLength + 2);
		temp->length = 0;
		temp->maxLength = pMainString->maxLength;
		StrCopy(temp, *pMainString);

		// 判断进行替换是否需要扩容
		int newLength = pMainString->length - pChildString.length + pReplaceString.length;
		if (newLength > pMainString->maxLength)
		{
			int newCapacity = ((newLength - 1) / MAXLENGTH + 1)*MAXLENGTH;
			pMainString->string = (char*)malloc((newCapacity + 2) * sizeof(char));
			pMainString->maxLength = newCapacity;
		}

		int tIndex = 1; // 标记源字符串副本
		int dIndex = 1; // 标记主串
		// 源字符串前半部分迁移
		while (tIndex < position)
			pMainString->string[dIndex++] = temp->string[tIndex++];

		// 插入进行替换的串
		int rIndex = 1;// 标记进行替换的串
		while (rIndex <= pReplaceString.length)
			pMainString->string[dIndex++] = pReplaceString.string[rIndex++];

		// 源字符串后半部分迁移(需要跳过被替换的串)
		tIndex = tIndex + pChildString.length;
		while (pMainString->string[dIndex++] = temp->string[tIndex++])
		{
			;
		}

		pMainString->length = newLength;
		return true;
	}
}

/*
	在字符串pMainString中查找字符串pChildString(使用KMP算法)，并将pMainString中出现的第一个pChildString用字符串pReplaceString替换
	初始条件:
		pMainString、pChildString、pReplaceString指向的字符串存在
		pChildString的长度 <= pMainString的长度
	返回结果:替换成功返回1,替换失败返回0
*/
bool ReplaceWithKMP(SString* pMainString, SString pChildString, SString pReplaceString)
{
	assert(pMainString->string != NULL);
	assert(pChildString.string != NULL);
	assert(pReplaceString.string != NULL);
	assert(pChildString.length != 0);

	if (pChildString.length > pMainString->length)
	{
		printf("length参数输入错误。\n");
		return false;
	}

	// 通过BF算法获取模式串在主串中的位置(从第一个字符处开始匹配)
	int position = Index_KMP(*pMainString, pChildString,Get_Next(pChildString));

	if (!position)
	{
		printf("替换失败，找不到对应的子串");
		return false;
	}
	else
	{
		// 统一扩容与否的行为，都对主串进行重新赋值
		SString* temp = (SString*)malloc(sizeof(SString));
		temp->string = (char*)malloc(pMainString->maxLength + 2);
		temp->length = 0;
		temp->maxLength = pMainString->maxLength;
		StrCopy(temp, *pMainString);

		// 判断进行替换是否需要扩容
		int newLength = pMainString->length - pChildString.length + pReplaceString.length;
		if (newLength > pMainString->maxLength)
		{
			int newCapacity = ((newLength - 1) / MAXLENGTH + 1)*MAXLENGTH;
			pMainString->string = (char*)malloc((newCapacity + 2) * sizeof(char));
			pMainString->maxLength = newCapacity;
		}

		int tIndex = 1; // 标记源字符串副本
		int dIndex = 1; // 标记主串
		// 源字符串前半部分迁移
		while (tIndex < position)
			pMainString->string[dIndex++] = temp->string[tIndex++];

		// 插入进行替换的串
		int rIndex = 1;// 标记进行替换的串
		while (rIndex <= pReplaceString.length)
			pMainString->string[dIndex++] = pReplaceString.string[rIndex++];

		// 源字符串后半部分迁移(需要跳过被替换的串)
		tIndex = tIndex + pChildString.length;
		while (pMainString->string[dIndex++] = temp->string[tIndex++])
		{
			;
		}

		pMainString->length = newLength;
		return true;
	}
}

/*
	向pMainString指向的字符串中第position个字符位置插入子串pChildString
	初始条件:
		pMainString和pChildString指向的字符串存在
	返回结果:插入成功返回1,插入失败返回0
*/
bool StrInsert(SString* pMainString, int position, SString pChildString)
{
	assert(pMainString->string != NULL);
	assert(pChildString.string != NULL);

	if ((position < 1) || (position > pMainString->length + 1))
	{
		printf("position参数错误\n");
		return false;
	}

	// 源主串拷贝一份，统一扩容与不扩容的情况，后续都对pMainString使用temp保存的源副本进行重新赋值
	SString* temp = (SString*)malloc(sizeof(SString));
	temp->string = (char*)malloc((pMainString->maxLength + 2) * sizeof(char));
	temp->length = 0;
	temp->maxLength = pMainString->maxLength;
	StrCopy(temp, *pMainString);

	// 如果插入元素后会导致数组溢出则需要扩容
	int capacity = pChildString.length + pMainString->length;
	if (capacity > pMainString->maxLength)
	{
		int newCapacity = ((capacity - 1) / MAXLENGTH + 1)*MAXLENGTH;
		pMainString->string = malloc((newCapacity + 2) * sizeof(char));
		pMainString->maxLength = newCapacity;
	}

	// 拼接源主串前半部分
	int index = 1; // 标记目标字符串
	int tempIndex = 1; // 标记源主串
	while (index <= position)
		pMainString->string[index++] = temp->string[tempIndex++];

	// 插入子串
	int indey = 1; // 标记子串
	// 注意这里不要拷贝子串的'\0'
	while (indey <= pChildString.length)
	{
		pMainString->string[index++] = pChildString.string[indey++];
	}

	// 拼接源主串后半部分
	while (pMainString->string[index++] = temp->string[tempIndex++])
	{
		;
	}

	// 后续处理
	free(temp->string);
	pMainString->length = pMainString->length + pChildString.length;
	return true;
}

/*
	删除pString指向的字符串中包括第position个字符起长度为length的子串
	初始条件:
		pString指向的字符串存在
		pString第position个字符起的剩余子串长度 >= length
	返回结果:删除成功返回1,否则返回0
*/
bool StrDelete(SString* pString, int position, int length)
{
	assert(pString->string != NULL);

	if (position < 1 || (pString->length - length + 1 < position))
	{
		printf("position和length参数设置错误~\n");
		return false;
	}

	int backIndex = position + length;// 需要后移子串的首字符
	// 将被删除子串后面的子串前移
	while (pString->string[position++] = pString->string[backIndex++])
		;

	pString->string[backIndex] = '\0';
	pSString->length = pString->length - length;
	return true;
}

/*
	销毁pString指向的字符串
	初始条件:pString指向的字符串存在
	返回结果:销毁成功返回1,否则返回0
*/
bool DestroyString(SString* pString)
{
	if (pString->string != NULL)
		free(pString->string);

	pString->length = 0;
	pString->string = NULL;
	return true;
}


int main()
{
	pSString = (SString*)malloc(sizeof(SString));
	pSString->string = NULL;
	pSString->length = 0;
	StrAssign(pSString, "hello world!!!");
	// myPrintf(*pSString);

	SString* pSString2 = (SString*)malloc(sizeof(SString));
	pSString2->string = NULL;
	pSString2->length = 0;
	StrAssign(pSString2, "hello world!!!");

	// int result = StrCompare(pSString, pSString2);
	// printf("%d", result);

	// printf("%d", StrLength(pSString));

	SString* pSString3 = (SString*)malloc(sizeof(SString));
	pSString3->string = NULL;
	pSString3->length = 0;

	// Concat(pSString3, *pSString2, *pSString);
	// myPrintf(*pSString3);


	// SubString(pSString3, *pSString, 2,3);
	// myPrintf(*pSString3);


	// StrCopy(pSString, *pSString2);
	// myPrintf(*pSString);

	// StrDelete(pSString, 2, 1);
	// myPrintf(*pSString);

	// StrInsert(pSString, 2, *pSString2);
	// myPrintf(*pSString);

	// int position = Index_BF(*pSString, *pSString2, 1);
	// if (position)
	//	 printf("子串在主串中的位置为：%d。", position);
	// else
	//	 printf("匹配失败。");

	// SString* pSString4 = (SString*)malloc(sizeof(SString));
	// pSString4->string = NULL;
	// pSString4->length = 0;
	// StrAssign(pSString4, "world");

	// SString* pSString5 = (SString*)malloc(sizeof(SString));
	// pSString5->string = NULL;
	// pSString5->length = 0;
	// StrAssign(pSString5, "我打尼玛的");
	// ReplaceWithBF(pSString, *pSString4, *pSString5);
	// myPrintf(*pSString);


	// SString* pSString6 = (SString*)malloc(sizeof(SString));
	// pSString6->string = NULL;
	// pSString6->length = 0;
	// StrAssign(pSString6, "abab_abaabbaba_dbabdabd");

	// SString* pSString7 = (SString*)malloc(sizeof(SString));
	// pSString7->string = NULL;
	// pSString7->length = 0;
	// StrAssign(pSString7, "abaabbaba");

	// int* next = Get_Next(*pSString7);

	// printf("子串在主串中的位置为：%d。\n", Index_KMP(*pSString6, *pSString7, next));


	// SString* pSString8 = (SString*)malloc(sizeof(SString));
	// pSString8->string = NULL;
	// pSString8->length = 0;
	// StrAssign(pSString8, "hello world!!!");
	
	// SString* pSString9 = (SString*)malloc(sizeof(SString));
	// pSString9->string = NULL;
	// pSString9->length = 0;
	// StrAssign(pSString9, "llo");

	// SString* pSString10 = (SString*)malloc(sizeof(SString));
	// pSString10->string = NULL;
	// pSString10->length = 0;
	// StrAssign(pSString10, "你好");

	// ReplaceWithKMP(pSString8, *pSString9, *pSString10);
	// myPrintf(*pSString8);


	return 1;
}







