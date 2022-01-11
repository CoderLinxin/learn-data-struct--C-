#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>


/*****************************************			符号定义				*****************************************/ 


#define ERROR -1//用来标记一个错误操作


/*****************************************			 队列定义			*****************************************/


typedef int QNodeElementType;//队列元素数据类型
struct QueueNode//队列结点
{

	QNodeElementType data;//数据域
	struct QueueNode* pNext;//指针域

};
typedef struct QueueNode QueueNode;

typedef struct
{

	QueueNode* front;//队头指针，指向头结点
	QueueNode* rear;//队尾指针，指向尾结点

}QueuePoint;


/*****************************************			 方法声明			*****************************************/


QueuePoint IniteListQueue();//链队初始化
void TraverListQueue(QueuePoint);//遍历链队结点
QNodeElementType ListQueueTopElement(QueuePoint);//取队头元素(首结点数据域)
void EnListQueue(QueuePoint,QNodeElementType);//链队入队
void DeListQueue(QueuePoint);//链队出队
void DestroyListQueue(QueuePoint);//链队销毁
void ClearListQueue(QueuePoint);//链队置空
bool EmptyListQueue(QueuePoint);//判断链队是否为空
bool ExistListQueue(QueuePoint);//判断链队是否存在
int ListQueueLength(QueuePoint);//求链队长度


/*****************************************			 方法定义			*****************************************/


/*
	链队初始化
*/
QueuePoint IniteListQueue()
{

	QueuePoint pQueue = {NULL,NULL};

	//初始化队列指针
	pQueue.front = pQueue.rear = (QueueNode*)malloc(sizeof(QueueNode));

	if (pQueue.front == NULL)
	{

		printf("分配空间失败，队列初始化失败。\n");
		return ;

	}

	pQueue.front->pNext = NULL;//将头结点next指针置空

	return pQueue;

}

/*
	遍历链队结点
	初始条件：链队存在且不为空
*/
void TraverListQueue(QueuePoint pQueue)
{

	if (EmptyListQueue(pQueue))
	{

		printf("遍历链队失败：链队不存在或为空。\n");
		return ERROR;

	}

	int count = 1;//用于计数
	QueueNode* head = pQueue.front->pNext;//用于完成遍历，初始指向首结点
	while (head !=NULL)
	{

		printf("链队的第%d个元素为：%d。\n",count, head->data);
		count++;
		head = head->pNext;//向后遍历

	}

	return;
}

/*
	取队头元素(首结点数据域)
	初始条件：链队存在且不为空
*/
QNodeElementType ListQueueTopElement(QueuePoint pQueue)
{

	if (EmptyListQueue(pQueue)||!ExistListQueue(pQueue))
	{

		printf("取队头元素失败：链队为空或不存在。\n");
		return ERROR;

	}

	return pQueue.front->pNext->data;

}

/*
	链队入队一个元素(由于需要改变rear的指向所以需要传入二级指针)
	初始条件：链队存在
*/
void EnListQueue(QueuePoint* pQueue, QNodeElementType data)
{

	if (!ExistListQueue(*pQueue))
	{

		printf("链队不存在，入队失败。\n");
		return ERROR;

	}

	//创建新结点
	QueueNode* p = (QueueNode*)malloc(sizeof(QueueNode));
	p->data = data;

	p->pNext = NULL;
	pQueue->rear->pNext = p;//新结点接在尾结点后面
	pQueue->rear = p;//更新尾结点

	return;

}

/*
	链队出队一个元素(由于可能需要改变rear的指向所以需要传入二级指针)
	初始条件：链表非空
*/
void DeListQueue(QueuePoint* pQueue)
{

	if (EmptyListQueue(*pQueue))
	{

		printf("链队出队失败：空队或队不存在。\n");
		return ERROR;

	}

	//假设链表结点>1，此时出队不需要修改rear指针

	QueueNode* p = pQueue->front->pNext;//用于记录被删除的当前首结点
	pQueue->front->pNext = p->pNext;//更新首结点

	//当链表结点=1时，删除一个结点，rear指向的尾结点被释放,此时队为空，需要更新rear指针
	if (pQueue->rear == p)//假设被删除的是尾结点
		pQueue->rear = pQueue->front;//将链队置空

	free(p);//释放被删除的前首结点
	
	return;


}

/*
	链队销毁
*/
void DestroyListQueue(QueuePoint* pQueue)
{

	QueueNode* p;//用于记录被删除结点

	while (pQueue->front)//遍历完成头指针被置空
	{

		p = pQueue->front;
		pQueue->front = pQueue->front->pNext;//向后遍历
		free(p);


	}

	pQueue->rear = NULL;//尾指针置空

	return;

}

/*
	链队置空
	初始条件：链队存在,由于需要改变front和rear所以需要传递pQueue的地址
*/
void ClearListQueue(QueuePoint* pQueue)
{

	if (!ExistListQueue(*pQueue))
		return ERROR;
	
	QueueNode* p= pQueue->front->pNext;//用于完成遍历
	pQueue->rear = p;//用于帮助释放空间
	while (p)
	{

		p = p->pNext;//向后遍历
		free(pQueue->rear);//释放结点
		pQueue->rear = p;

	}

	pQueue->rear = pQueue->front;//尾指针指向头结点

	return;

}

/*
	判断链队是否为空
	初始条件：链队存在
*/
bool EmptyListQueue(QueuePoint pQueue)
{

	if (!ExistListQueue(pQueue))
		return ERROR;

	if (pQueue.front == pQueue.rear)
		return true;

	return false;

}

/*
	判断链队是否存在
*/
bool ExistListQueue(QueuePoint pQueue)
{

	if (pQueue.front != NULL)
		return true;

	return false;

}

/*
	求链队长度
	初始条件：链队存在
*/
int ListQueueLength(QueuePoint pQueue)
{

	if(!ExistListQueue(pQueue))
		return ERROR;

	QueueNode* current = pQueue.front->pNext;//用于完成遍历，初始指向首结点
	int count = 0;//用于计数

	while (current)
	{

		count++;
		current = current->pNext;//向后遍历

	}

	return count;

}


//int main()
//{
//
//	//初始化链队
//	QueuePoint pQueue = IniteListQueue();
//
//	//销毁链队
//	//DestroyListQueue(&pQueue);
//
//	//链队入队
//	EnListQueue(&pQueue, 20);
//	EnListQueue(&pQueue, 60);
//	EnListQueue(&pQueue, 70);
//
//	//链队出队
//	DeListQueue(&pQueue);
//	//DeListQueue(&pQueue);
//
//	printf("链队长度为：%d。\n", ListQueueLength(pQueue));
//
//	//取队头元素
//	printf("队头元素为：%d\n", ListQueueTopElement(pQueue));
//
//	//清空队列
//	//ClearListQueue(&pQueue);
//
//	//销毁队列
//	//DestroyListQueue(&pQueue);
//
//	//遍历链队
//	TraverListQueue(pQueue);
//
//}