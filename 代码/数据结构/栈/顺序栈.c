#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

/*****************************************	     栈的数据类型定义			*****************************************/


/*
	ADT Stack{
		
		数据对象: D = { a[i] | a[i] ∈ ElementSet, i = 1,2,3,..,n, n >=0 } //ElementSet表示一组类型相同的数
		数据关系: R = { <a[i-1],a[i]> | a[i-1], a[i]∈D, i = 1,2,3,...,n}
				 约定a[n]为栈顶，a[1]为栈底。
		基本操作: 初始化,进栈,出栈,取栈顶元素.

	}ADT Stack
*/


/*****************************************			符号定义				*****************************************/


#define MAXSIZE 5 //定义栈的最大元素个数
#define ERROR -1//用来标记一个错误操作


/*****************************************			 栈定义				*****************************************/


typedef int StackElementType;//定义栈元素的数据类型
struct Stack
{

	StackElementType* stackTop;//栈顶指针指向栈顶元素的后一个元素
	StackElementType* stackBase;//栈底指针指向栈底元素
	int stackSize;//用来标识一个栈的最大长度

}*pStack;
typedef struct Stack Stack;


/*****************************************			 方法声明			*****************************************/


Stack* IniteStack();//完成栈的初始化
void DestroyStack(Stack*);//销毁栈
bool StackEmpty(Stack*);//判断是否为空栈
int StackLength(Stack*);//获取一个栈的长度
StackElementType* GetTop(Stack*);//取栈顶元素
void ClearStack(Stack*);//清空栈
void Push(Stack*, StackElementType);//压栈一个元素
void Pop(Stack*);//弹出一个元素
void TraverStack(Stack*);//遍历一个栈


/*****************************************			 方法定义			*****************************************/


/*
	初始化栈，返回指向该栈的指针
*/
Stack* IniteStack()
{

	//创建一个栈结构
	Stack* pStack = (Stack*)malloc(sizeof(Stack));
	
	//栈底指针指向一个数组
	pStack->stackBase = (StackElementType*)malloc(sizeof(StackElementType)*MAXSIZE);

	if (pStack->stackBase == NULL)
	{

		printf("创建栈失败。\n");
		exit(0);

	}

	pStack->stackTop = pStack->stackBase;//表示空栈
	pStack->stackSize = MAXSIZE;

	return pStack;

}

/*
	销毁栈
	初始条件：栈存在
*/
void DestroyStack(Stack* pStack)
{

	if (pStack->stackBase)
	{

		//释放栈底指针指向的空间
		free(pStack->stackBase);
		pStack->stackSize = 0;//栈大小置0
		pStack->stackBase = pStack->stackTop = NULL;//栈底和栈顶指针置空

		return;

	}

}

/*
	判断栈是否为空
	初始条件：栈存在
*/
bool StackEmpty(Stack* pStack)
{

	if (pStack->stackBase == NULL)
	{

		printf("栈不存在");
		return ERROR;

	}

	if (pStack->stackBase == pStack->stackTop)
	{

		return true;

	}

	return false;

}

/*
	获取栈的当前长度
	初始条件：栈存在
*/
int StackLength(Stack* pStack)
{

	if (pStack->stackBase == NULL)
		return ERROR;
	
	int length = pStack->stackTop - pStack->stackBase;

	return length;

}

/*
	取栈顶元素
	初始条件：栈存在且不为空
*/
StackElementType* GetTop(Stack* pStack)
{

	if (pStack->stackBase == NULL || StackEmpty(pStack))
		return ERROR;

	return *(pStack->stackTop-1);

}

/*
	清空栈
	初始条件：栈存在
*/
void ClearStack(Stack* pStack)
{

	if (pStack->stackBase == NULL)
		return ERROR;

	pStack->stackTop = pStack->stackBase;
	return;

}

/*
	压栈一个元素
	初始条件：栈存在且栈未满
*/
void Push(Stack* pStack,StackElementType value)
{

	if (pStack->stackBase == NULL)
		return ERROR;

	if (StackLength(pStack) >= pStack->stackSize)
	{

		printf("栈已满，无法入栈。\n");
		return ERROR;

	}

	*pStack->stackTop = value;
	pStack->stackTop++;

	return;

}

/*
	出栈一个元素
	初始条件：栈存在且不为空
*/
void Pop(Stack* pStack)
{

	if (pStack->stackBase == NULL)
		return ERROR;

	if (StackLength(pStack) == 0)
	{

		printf("当前栈为空，出栈失败。\n");
		return;

	}

	pStack->stackTop--;

	return;

}

/*
	遍历栈
	初始条件：栈存在且不为空
*/
void TraverStack(Stack* pStack)
{

	if (pStack->stackBase == NULL || StackEmpty(pStack))
	{

		printf("遍历栈失败：栈不存在或为空。\n");
		return ERROR;

	}

	int length = StackLength(pStack);//用于确定遍历的趟数
	StackElementType* current = pStack->stackTop ; //用于完成遍历任务,注意从Top往base遍历

	int i = 0;
	for ( i = 0; i <length; i++)
	{

		printf("栈的第%d个元素为：%d。\n",i+1, *(current-1-i));

	}
	
}


//int main()
//{
//   
//	//初始化栈
//	pStack = IniteStack();
//
//	//压栈
//	Push(pStack, 50);
//	Push(pStack, 20);
//	Push(pStack, 10);
//	//Push(pStack, 5);
//	//Push(pStack, 2);
//
//	printf("当前栈顶元素为：%d。\n", GetTop(pStack));
//
//	//出栈
//	//Pop(pStack);
//	//Pop(pStack);
//	//Pop(pStack);
//	//Pop(pStack);
//	//Pop(pStack);
//	//Pop(pStack);
//
//	//销毁栈
//
//	//清空栈
//	//ClearStack(pStack);
//
//	//销毁栈
//	//DestroyStack(pStack);
//
//	//计算栈的长度
//	int length= StackLength(pStack);
//	if(length != ERROR)
//	printf("栈的当前长度为:%d。\n",StackLength(pStack));
//
//
//	//遍历栈
//	TraverStack(pStack);
//
//	return;
//
//}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
