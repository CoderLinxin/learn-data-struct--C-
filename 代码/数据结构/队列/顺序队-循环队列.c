#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

/*****************************************	     队的数据类型定义			*****************************************/


/*
	ADT Queue{
		数据对象：D = {a | a ∈ElemSet, i = 1,2,3,...,n, n>=0}
		数据关系：R = {<a[i-1],a[i]> | a[i-1],a[i]∈D, i=2,..n}
		基本操作：
			Queue* IniteQueue();//构造一个空队列
			void DestroyQueue(Queue*);//销毁一个队列
			void ClearQueue(Queue*);//清空一个队列
			int QueueLength(Queue*);//求队列的实际长度
			QueueElementType GetQueueHead(Queue*);//取队头元素
			void EnQueue(Queue*, QueueElementType);//入队一个元素
			void DeQueue(Queue*);//出队一个元素
			bool EmptyQueue(Queue*);//判断队列是否为空
			void TraverQueue(Queue*);//遍历队列
			bool ExistQueue(Queue*);//判断队列是否存在
	}
*/


/*****************************************			符号定义				*****************************************/


#define MAXSIZE 6//代表队列最大长度
#define ERROR -1//用来标记一个错误操作


/*****************************************			 队列定义				*****************************************/


typedef int QueueElementType;//队列元素的数据类型
struct Queue
{

	QueueElementType* base;//初始化的动态分配的存储空间
	int front;//代表队列的头指针，指向队头元素
	int rear;//代表队列的尾指针,指向队尾的下一个元素

}*pQueue;
typedef struct Queue Queue;


/*****************************************			 方法声明			*****************************************/


Queue* IniteQueue();//构造一个空队列
void DestroyQueue(Queue*);//销毁一个队列
void ClearQueue(Queue*);//清空一个队列
int QueueLength(Queue*);//求队列的实际长度
QueueElementType GetQueueHead(Queue*);//取队头元素
void EnQueue(Queue*, QueueElementType);//入队一个元素
void DeQueue(Queue*);//出队一个元素
bool EmptyQueue(Queue*);//判断队列是否为空
void TraverQueue(Queue*);//遍历队列
bool ExistQueue(Queue*);//判断队列是否存在


/*****************************************			 方法定义			*****************************************/


/*
	构造一个空队列,并返回其指针
*/
Queue* IniteQueue()
{

	Queue* pQueue = (Queue*)malloc(sizeof(Queue));

	//队列初始化
	pQueue->base = (QueueElementType*)malloc(sizeof(QueueElementType)*MAXSIZE);//用于存放真正的队列元素
	if (pQueue->base == NULL)
	{

		printf("分配空间失败，无法创建队列。\n");
		return ERROR;

	}

	pQueue->front = pQueue->rear = 0;//队列置空

	return pQueue;

}

/*
	销毁一个队列
*/
void DestroyQueue(Queue* pQueue)
{

	pQueue->base == NULL;
	pQueue->front = pQueue->rear = 0;

	return;

}

/*
	清空一个队列
	初始条件：队列存在
*/
void ClearQueue(Queue* pQueue)
{

	if (!ExistQueue(pQueue))
	{

		printf("清空队列失败：队列不存在。\n");
		return ERROR;

	}

	pQueue->front = pQueue->rear = 0;
	return;

}

/*
	求队列的实际长度
	初始条件：队列存在
*/
int QueueLength(Queue* pQueue)
{

	if (!ExistQueue(pQueue))
	{

		printf("无法获取队列长度：队列不存在。\n");
		return ERROR;

	}
		
	return (pQueue->rear - pQueue->front + MAXSIZE) % MAXSIZE;

}

/*
	取队头元素
	初始条件：队列存在且不为空
*/
QueueElementType GetQueueHead(Queue* pQueue)
{

	if (EmptyQueue(pQueue) || !ExistQueue(pQueue))
	{

		printf("无法获取队头元素：队列为空。\n");
		return ERROR;

	}

	return pQueue->base[pQueue->front];

}

/*
	入队一个元素
	初始条件：队列存在且队列不为满
*/
void EnQueue(Queue* pQueue, QueueElementType value)
{

	//判断是否队满
	if ((pQueue->rear + 1) % MAXSIZE == pQueue->front)
	{

		printf("入队失败：队列已满。\n");
		return ERROR;

	}

	//插入元素到队尾
	pQueue->base[pQueue->rear] = value;
	pQueue->rear = (pQueue->rear + 1) % MAXSIZE;//队尾指针后移

	return;

}

/*
	出队一个元素
	初始条件：队列存在且不为空
*/
void DeQueue(Queue* pQueue)
{

	if (!ExistQueue(pQueue) || EmptyQueue(pQueue))
	{

		printf("出队失败：队列不存在或为空。\n");
		return ERROR;

	}
	
	pQueue->front=(pQueue->front + 1) % MAXSIZE;//头指针后移

	return;

}

/*
	判断队列是否为空
	初始条件：队列存在
*/
bool EmptyQueue(Queue* pQueue)
{

	if (!ExistQueue(pQueue))
	{

		printf("无法判断队列是否为空：队列不存在。\n");
		return ERROR;

	}

	if (pQueue->front == pQueue->rear)
		return true;

	return false;

}

/*
	遍历队列
	初始条件：队列存在且不为空
*/
void TraverQueue(Queue* pQueue)
{

	if (!ExistQueue(pQueue) || EmptyQueue(pQueue))
	{

		printf("遍历失败：队列不存在或为空。\n");
		return ERROR;

	}

	int current = pQueue->front;//用于完成遍历任务
	int count = 0;//用于计数

	while ((current)%MAXSIZE != pQueue->rear)
	{
		count++;
		printf("队列的第%d个元素为：%d。\n", count,pQueue->base[current]);
		current++;

	}

	return;

}

/*
	判断队列是否存在
*/
bool ExistQueue(Queue* pQueue)
{

	if (pQueue->base == NULL)
		return false;

	return true;

}


//int main()
//{
//   
//	//初始化队列
//	pQueue = IniteQueue();
//
//	//入队
//	EnQueue(pQueue,20);
//	EnQueue(pQueue,22);
//	EnQueue(pQueue,99);
//	EnQueue(pQueue,66);
//	EnQueue(pQueue,7);
//
//	//出队
//	DeQueue(pQueue);
//	DeQueue(pQueue);
//	DeQueue(pQueue);
//	DeQueue(pQueue);
//
//	//ClearQueue(pQueue);
//
//	TraverQueue(pQueue);
//
//	if(!(pQueue->rear + 1) % MAXSIZE == pQueue->front)
//		printf("队列当前长度为：%d。\n", QueueLength(pQueue));
//	
//	return 0;
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
