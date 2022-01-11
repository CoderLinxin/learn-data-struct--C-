#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

/*****************************************			符号定义			*****************************************/


#define ERROR -1//代表操作链表时出错
#define NONE 0//代表头结点的数据域为空


/*****************************************		   链表结点定义		*****************************************/


typedef int DataType;//链表结点中数据域的类型
/*
	定义一个单链表的结点
*/
 struct Node
{

	DataType data;//结点的数据域，用于存放数据
	struct Node* pNext;//结点的指针域，指向链表的下一个结点

}*pHead;//pHead为头指针，本案例为带有头结点的单链表，因此pHead指向头结点
 typedef struct Node Node;


/*****************************************			 方法声明			*****************************************/


Node* CreateListHead(int*,int);//头插法创建链表
Node* CreateListTail(int*,int);//尾插法创建链表
void TraverList(Node*);//遍历链表
DataType GetElementList(Node*,int);//获取链表结点数据
bool IsEmpty(Node*);//判断链表是否为空
int GetListLength(Node*);//统计链表的长度
void SortList(Node*);//使用选择排序对链表升序排序
void InsertList(Node*,int, DataType);//在线性表特定位置插入一个结点
int DeleteListElement(Node*, int);//删除线性表中的一个特定位置的结点
void DeleteList(Node*);//删除整个链表
Node* UnionListByChain(Node*,Node*);//合并两个有序链表(升序排列)


/*****************************************			 方法定义			*****************************************/


/*
	头插法创建链表(根据传入的数组及其长度来创建链表)
	初始条件：传入的数组指针合法
*/
Node* CreateListHead(DataType* pArray, int length)
{

	//检查用于创建链表的数据源的合法性
	if (pArray == NULL)
	{

		printf("请传入合法的数组指针。\n");
		return ERROR;

	}
		
	Node* pHead = (Node*)malloc(sizeof(Node));//创建头指针，其指向头结点

	//初始化头结点
	pHead->data = NONE;
	pHead->pNext = NULL;

	//创建链表
	int i;

	for ( i = 0; i < length; i++)
	{

		Node* temp = (Node*)malloc(sizeof(Node));//新创建结点存放数据
		temp->data = pArray[i];//新结点数据域赋值
		temp->pNext = pHead->pNext;//新结点指向头结点next指针指向的结点(即原链表的首结点)
		pHead->pNext = temp;//头结点next指针指向新节点(该结点作为新的首结点.)

	}

	return pHead;

}

/*
	尾插法创建链表(根据传入的数组及其长度来创建链表)
	初始条件：传入的数组指针合法
*/
Node* CreateListTail(int* pArray, int length)
{

	//检查用于创建链表的数据源的合法性
	if (pArray == NULL)
	{

		printf("请传入合法的数组指针。\n");
		return ERROR;

	}

	Node* pHead = (Node*)malloc(sizeof(Node));//创建头指针，其指向头结点

	//初始化头结点
	pHead->data = NONE;
	pHead->pNext = NULL;

	//由于头指针永远指向头结点，因此需要声明一个尾结点(始终指向尾部)来帮助插入元素,空表尾指针指向头结点
	Node* pTail = pHead;

	int i;
	for ( i = 0; i < length; i++)
	{

		//新建一个结点
		Node* temp = (Node*)malloc(sizeof(Node));
		temp->data = pArray[i];//更新结点的数据域
		pTail->pNext = temp;//尾结点next指针指向新结点，该结点作为新的尾结点
		pTail = temp;//尾结点指针指向新的尾结点

	}
	pTail->pNext = NULL;//更新尾结点的next指针为NULL

	return pHead;

}

/*
	对传入的链表指针进行遍历
*/
void TraverList(Node* pHead)
{

	Node* traverP = pHead->pNext;//用traverP完成遍历任务，traverP初始指向链表的首结点

	int length =0;//用来统计链表的长度(不包括头结点)
	while (traverP != NULL)
	{

		printf("链表的第%d个数据元素为：%d\n",length+1, traverP->data);
		traverP = traverP->pNext;//traverP指针向后遍历
		length++;//更新计数器

	}

	return;

}

/*
	获取链表特定位置上的元素
	初始条件：链表不为空且position满足： 0 < position < GetListLength(pHead)
*/
DataType GetElementList(Node* pHead , int position )
{

	if (IsEmpty(pHead) || position <= 0 || position > GetListLength(pHead))
	{

		printf("获取链表结点数据失败。\n");
		return ERROR;

	}

	int current =0 ;
	Node* travelP = pHead->pNext;

	while (travelP!=NULL)
	{

		current++;
		if (current == position)
		{

			printf("获取到了链表的第%d个元素：%d。\n",current, travelP->data);
			return;

		}

		travelP = travelP->pNext;//向后遍历

	}

}

/*
	判断链表是否为空
*/
bool IsEmpty(Node* pHead)
{

	if (pHead->pNext == NULL)
	{

		printf("链表为空。");
		return true;

	}

	return false;

}

/*
	统计链表的长度
*/
int GetListLength(Node* pHead)
{

	int length = 0;//用于统计链表的长度

	Node* traverP = pHead->pNext;//用于遍历链表的指针

	while (traverP!=NULL)
	{

		length++;
		traverP = traverP->pNext;

	}

	return length;

}

/*
	在线性表position处插入一个元素
	初始条件：position满足 0 < position <= GetListLength(pHead) + 1
*/
void InsertList(Node* pHead, int position,DataType data)
{

	//判断插入元素位置是否合法
	if (position<=0 || position > GetListLength(pHead)+1)
	{

		printf("插入元素位置不合法。\n");
		return;

	}

	int current = 0;//用于标记当前位置
	Node* traverP = pHead->pNext;//用于完成遍历任务

	while (traverP!=NULL)
	{

		current++;
		if (current == position-1)
		{

			//创建一个结点
			Node* temp = (Node*)malloc(sizeof(Node));
			temp->data = data;
			temp->pNext = traverP->pNext;//新结点next指针指向原第position个结点
			traverP->pNext = temp;//第position-1个结点next指针指向新创建的结点
			return;

		}

		traverP = traverP->pNext;//向后遍历

	}

}

/*
	删除链表中特定位置上的结点
	初始条件:线性表不为空且position满足： 0 < position <= GetListLength(pHead)
*/
int DeleteListElement(Node* pHead, int position)
{

	Node* traverP = pHead;//用于完成遍历任务,假设删除的结点为首结点，因此需要用到前一个结点即头结点，所以从头结点开始向后遍历
	int current = 1;//标记当前位置

	//向后遍历找到position-1位置上的结点并且判断的是position而不是position-1	
	//注意之前判断的是traverP !=NULL && current < position - 1 其逻辑含义实际上是查找 第position - 1 个结点 ,
	//但是实际上我们需要判断的是position是否合法即，position是否 > 0 && <= 链表的长度,但是该逻辑意义却被我理解成了查找第position-1个结点,
	//假设链表长度为6，删除位置为7，于是通过该循环我们查找到了第6个结点，因为7-1 == 6 恰好是position-1但是很明显7就是非法的，所以这种判断是不行的  
	//而假设position == 0 , 此时如果判断 traverP !=NULL，current初始化为0时，current == position 就不会进入下面current > position的判断，因此current需要初始化为1来进行
	//注意关键在于判断traverP->pNext这里其他的current可以改为0 current < position-1
	while (traverP->pNext!=NULL && current < position)//判断的是position的合法性。
	{//由于尾指针为NULL会自动退出，所以实际上排除了position > GetListLength(pHead)这种情况

		current++;
		traverP = traverP->pNext;

	}

	//判断位置的合法性,由于上面与判断可能会出现一真一假的情况，所以分别要对这两种情况再进行判断
	if (traverP->pNext == NULL || current > position)
	{

		printf("删除位置不合法或线性表为空。\n");
		return;

	}
	
	//记录将被删除的结点(以便释放内存)
	Node* pDelete = traverP->pNext;
	//进行删除操作(将position-1位置结点next指针指向position位置结点next指针所指向的结点)
	traverP->pNext = pDelete->pNext;
	free(pDelete);//释放被删除的结点的内存

	return;

}

/*
	删除链表中特定位置上的结点(实现2)推荐使用
	初始条件:线性表不为空且position满足： 0 < position <= GetListLength(pHead)
*/
int DeleteListElement2(Node* pHead, int position)
{

	Node* traverP = pHead;//用于完成遍历任务,假设删除的结点为首结点，因此需要用到前一个结点即头结点，所以从头结点开始向后遍历
	int current = 0;//标记当前位置

	while (traverP->pNext != NULL && current < position-1)//寻找position-1处个结点，但是判断的是position处的结点(traverP->pNext)是否存在
	//(因为删除结点需要将被删除结点的前一个和后一个结点连接起来,而只要position处的结点存在那么其next指针也就存在(即使为NULL),所以这样就满足删除结点的条件)
	{//由于尾指针为NULL会自动退出，所以实际上排除了position > GetListLength(pHead)这种情况

		current++;
		traverP = traverP->pNext;

	}

	//判断位置的合法性,由于上面与判断可能会出现一真一假的情况，所以分别要对这两种情况再进行判断
	if (traverP->pNext == NULL || current > position-1)
	{

		printf("删除位置不合法或线性表为空。\n");
		return;

	}

	//记录将被删除的结点(以便释放内存)
	Node* pDelete = traverP->pNext;
	//进行删除操作(将position-1位置结点next指针指向position位置结点next指针所指向的结点)
	traverP->pNext = pDelete->pNext;
	free(pDelete);//释放被删除的结点的内存

	return;

}

/*
	删除整个链表(将链表置空)
*/
void DeleteList(Node* pHead)
{

	Node* traverP = pHead->pNext;//用于完成遍历任务
	Node* deleteP;//用于完成删除结点的任务

	while (traverP != NULL)
	{

		deleteP = traverP->pNext;//记录下一个结点(以便向后遍历)
		free(traverP);//删除结点（释放内存）
		traverP = deleteP;//向后遍历

	}

	pHead->pNext = NULL;//头结点next指针置空
	return;

}

/*
	用选择排序对链表进行排序(升序)
*/
void SortList(Node* pHead)
{

	Node* traverP = pHead->pNext;//用于完成遍历链表的任务

	int length = GetListLength(pHead);//获取链表的长度

	int i;
	Node* currentNode=traverP;//用于记录当前正在排序的位置

	for ( i = 0; i < length; i++)//每次for循环排好一个位置
	{

		DataType temp = currentNode->data;//用于存储此次排序的最小数据以便交换数据
		Node* tempNode= currentNode;//用于记录此次排序中最小数据的结点
		traverP = currentNode;//遍历起点更新(由于每排序一个位置travelP总是会指向尾指针，因此需要在每次排序当前位置前更新tavelP指针)

		while (traverP!=NULL)
		{

			if (temp>traverP->data)
			{

				temp = traverP->data;//更新记录的当前排序位置上的最小值
				tempNode = traverP;//记录符合交换规则的结点

			}

			traverP = traverP->pNext;//向后遍历

		}

		//数据交换，完成一个位置的排序
		tempNode->data = currentNode->data;
		currentNode->data = temp;

		currentNode = currentNode->pNext;//对下一个位置进行排序

	}

}

/*
	合并两个有序链表,返回合成的目标链表的头指针(升序排列)
*/
Node* UnionListByChain(Node* pAHead, Node* pBHead)
{

	//用pAHead作为结果链表C的头指针
	Node* pCHead = pAHead;

	//声明用于遍历A,B,C表的指针
	Node* aCurrent = pAHead->pNext;
	Node* bCurrent = pBHead->pNext;
	Node* cCurrent = pCHead;
	
	while (aCurrent&&bCurrent)//当A链表结点和B链表的结点都不为尾结点时
	{

		//A表的结点数据小于B表的结点数据则依次接续在C表的后面，反之同理
		if (aCurrent->data <= bCurrent->data)
		{

			cCurrent->pNext = aCurrent;
			cCurrent = aCurrent;//C表尾指针后移(因为每次都是插入到C表的尾结点之后)
			aCurrent = aCurrent->pNext;//向后遍历

		}
		else
		{

			cCurrent->pNext = bCurrent;
			cCurrent = bCurrent;
			bCurrent = bCurrent->pNext;//向后遍历

		}

	}

	//当A表和B表任一遍历到尾结点时
	cCurrent->pNext = aCurrent ? aCurrent : bCurrent;//剩下的非空链表直接接到C表的尾结点后
	free(pBHead);//释放b表头结点

	return pCHead;

}

//int main()
//{
//
//	//DataType array[] = {5,6,9,526,11,561};
//
//	////注意这里array传递进去后用sizeof运算符算的是地址变量的大小而不是数组的大小
//	////pHead = CreateListHead(array, 6);
//
//	////判断链表是否为空
//	////IsEmpty(pHead);
//
//	////尾插法创建链表
//	//pHead = CreateListTail(array, 6);
//
//	////获取链表长度
//	//printf("链表的长度为：%d。\n", GetListLength(pHead));
//
//	////获取链表元素
//	////GetElementList(pHead,5);
//
//	////插入结点
//	////InsertList(pHead,7,999);
//
//	////对链表进行排序
//	////SortList(pHead);
//
//	////删除结点
//	//DeleteListElement2(pHead,7);
//	////DeleteList(pHead);
//
//	////对链表进行遍历
//	//TraverList(pHead);
//
//	//printf("链表的长度为：%d。\n", GetListLength(pHead));
//
//	DataType array1[] = { 5,6,9,11,20,561 };
//	Node* aHead = CreateListTail(array1, 6);
//	//TraverList(aHead);
//
//	DataType array2[] = { 20,22,22,30,50 };
//	Node* bHead = CreateListTail(array2, 5);
//	//TraverList(bHead);
//
//	Node* cHead = UnionListByChain(aHead, bHead);
//	TraverList(cHead);
//
//}