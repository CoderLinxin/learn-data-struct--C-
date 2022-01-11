#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

/*****************************************			 符号定义				*****************************************/


#define ERROR -1


/*****************************************			栈结点定义				*****************************************/


//注意链栈头指针是直接指向首结点的(没有头结点)
typedef int ListStackElementType;//代表链栈各个结点数据域的数据类型
struct StackNode
{

	ListStackElementType data;//链栈上的结点
	struct StackNode* pNext;//指向下一结点的指针

}*pStackTop;
typedef struct StackNode StackNode;


/*****************************************			 方法声明			*****************************************/


StackNode* IniteChainStack();//初始化链栈
void TravelChainStack(StackNode*);//遍历链栈
int ChainStackLength(StackNode*);//获取链栈的长度
void PushChainStack(StackNode**,ListStackElementType);//链栈入栈一个元素
void PopChainStack(StackNode**);//链栈出栈一个元素
bool ChainStackEmpty(StackNode*);//判断链栈是否为空
ListStackElementType GetChainStackTop(StackNode*);//取栈顶元素

/*****************************************			 方法定义			*****************************************/


/*
	初始化链栈
*/
StackNode* IniteChainStack()
{

	StackNode* pStackTop = NULL;//构造一个空栈，栈顶指针置空
	return pStackTop;
	
}

/*
	遍历链栈
*/
void TravelChainStack(StackNode* pStackTop)
{

	if (ChainStackEmpty(pStackTop))
	{

		printf("链栈为空，遍历失败");
		return ERROR;

	}

	int current = 1;//用于计数
	while (pStackTop !=NULL)
	{

		printf("链栈第%d个元素为：%d。\n",current,pStackTop->data);
		current++;
		pStackTop = pStackTop->pNext;//向后遍历

	}


}

/*
	获取链栈的长度
*/
int ChainStackLength(StackNode* pStackTop)
{

	
	if (ChainStackEmpty(pStackTop))//判断是否为空栈
		return 0;

	int length = 0;
	while (pStackTop)
	{

		length++;
		pStackTop = pStackTop->pNext;//向后遍历

	}

	return length;

}

/*
	链栈入栈一个元素
*/
void PushChainStack(StackNode** pStackTop,ListStackElementType data)
{

	//创建一个新结点
	StackNode* stackNode = (StackNode*)malloc(sizeof(StackNode));
	stackNode->data = data;

	stackNode->pNext = *pStackTop;//新结点指向pStackTop指向的结点
	*pStackTop = stackNode;//更新头指针

	return;

}

/*
	链栈出栈一个元素
	初始条件：链栈不为空
*/
void PopChainStack(StackNode** pStackTop)
{

	if (ChainStackEmpty(*pStackTop))
	{

		printf("链栈为空，出栈失败。\n");
		return ERROR;

	}

	StackNode* temp = *pStackTop;//临时变量指向需要被删除的首结点
	*pStackTop = (*pStackTop)->pNext;//更新头指针
	free(temp);//释放被删除的结点

	return;

}

/*
	判断链栈是否为空
*/
bool ChainStackEmpty(StackNode* pStackTop)
{

	if (pStackTop == NULL)
		return true;

	return false;

}

/*
	取栈顶元素
	初始条件：栈不为空
*/
GetChainStackTop(StackNode* pStackTop)
{

	if (ChainStackEmpty(pStackTop))
	{

		printf("链栈为空，取栈顶元素失败。\n");
		return ERROR;

	}

	return pStackTop->data;

}


int main()
{

	//初始化链栈
	pStackTop = IniteChainStack();
	PushChainStack(&pStackTop, 20);
	PushChainStack(&pStackTop, 50);
	PushChainStack(&pStackTop, 100);

	//出栈一个元素
	PopChainStack(&pStackTop);

	printf("链栈当前长度为：%d。\n", ChainStackLength(pStackTop));

	//取栈顶元素
	printf("栈顶元素：%d。\n", GetChainStackTop(pStackTop));;

	//遍历链栈
	TravelChainStack(pStackTop);

}