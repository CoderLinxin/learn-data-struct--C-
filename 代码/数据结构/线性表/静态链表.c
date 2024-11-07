#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>


/*****************************************			符号定义				*****************************************/


#define MAXSIZE 1000//假设静态链表的最大长度为1000（有效数据长度为998）


/*****************************************		静态链表结点定义			*****************************************/


typedef DataType;//静态链表结点的数据域的类型
typedef struct 
{

	DataType data;//结点的数据域
	int cursor;//用于存放当前结点的后继结点在数组中的下标，为0时表示当前结点为尾结点(这里我用NULL来表示)

}Node,StaticLinkList[MAXSIZE];//声明一个1000个元素的静态链表的数组类型(注意是数组)


/*****************************************			 方法声明			*****************************************/


void InitStaticList(StaticLinkList);//初始化静态链表
int StaticListLength(StaticLinkList);//计算静态链表的长度(有效结点的个数)
void StaticListInsert(StaticLinkList,int,DataType);//插入结点到静态链表中
int LeisureListPosition(StaticLinkList);//在备用链表中查找空闲结点
void StaticListDelete(StaticLinkList, int);//删除链表的某个结点
void FreeNode(StaticLinkList, int);//回收被删除的结点到备用链表


/*****************************************			 方法定义			*****************************************/


/*
	初始化静态链表
*/
void InitStaticList(StaticLinkList list)//形参是数组类型，接收数组首元素地址
{
	
	int i;

	//由于创建静态链表时除了首尾结点外都是备用链表，所以除尾结点外，其他结点的cursor依次存放下一结点的下标
	for ( i = 0; i < MAXSIZE-1; i++)
		list[i].cursor = i + 1;//存放下一结点的下标

	list[MAXSIZE - 1].cursor = 0;//尾结点的cursor设为0表示一个空表，并且当给空表第一个位置插入第一个元素时，0会赋值给新结点的cursor表示链表的结束

	return;

}

/*
	获取静态链表的有效结点个数
*/
int StaticListLength(StaticLinkList list)
{

	int first = list[MAXSIZE - 1].cursor;//获取静态链表中的第一个有效结点在数组中的下标(注意第一个有效结点不一定是数组的第二个元素)
	int current = first;//用于完成遍历任务

	int count = 0;

	while (current!=0)//current == 0 则表示遍历到了尾结点这一步相当于phead != NULL
	{

		count++;
		current = list[current].cursor;

	}
	
	return count;

}

/*
	在静态链表的指定位置上插入结点
*/
void StaticListInsert(StaticLinkList list, int position, DataType value)
{

	if (position<1 || position > StaticListLength(list) + 1)//判断插入位置的合法性,由于后面会判断是否有空闲空间所以这里不用考虑备用链表为空的情况
	{

		printf("插入位置不合法。\n");
		return;

	}
		
	int leisure = LeisureListPosition(list);//获取空闲元素的下标

	if (leisure != 0)//判断备用链表是否为空(即是否没有空闲元素)
	{

		int current = MAXSIZE - 1;//表示从头结点开始向后遍历相当于pHead

		int currentPosition = 0;//用来统计当前遍历到第几个结点
		//查找第 position - 1 个链表结点
		while (currentPosition < position -1)
		{

			currentPosition++;
			current = list[current].cursor;//向后遍历,并记录当前正在遍历的结点的下标

		}
		
		list[leisure].data = value;//将数据赋值给空闲元素(可以看成一个新创建的结点)的data
		list[leisure].cursor = list[current].cursor;//新结点指向第position个结点
		list[current].cursor = leisure;//第position - 1 个结点指向新结点

	}

}

/*
	在备用链表中查找空闲结点并返回其下标,若静态链表已满则返回0
*/
int LeisureListPosition(StaticLinkList list)
{

	//获取备用链表中第一个结点的下标
	int leisure = list[0].cursor;
	
	if (leisure)//如果有空闲结点那么他的下标一定属于 [1,MAXSIZE-1]这个区间中,假设静态链表已满，那么最后一个有效结点的cursor由于设为0就被我们考虑进去了
		list[0].cursor = list[leisure].cursor;//更新备用链表的第一个结点的下标
	return leisure;

}

/*
	删除静态链表上position位置上的结点
*/
void StaticListDelete(StaticLinkList list , int position)
{

	int current = MAXSIZE - 1;//从头结点开始向后遍历（假设删除的是首结点，需要用到前一个结点即头结点）
	int currentPosition = 1;//用来统计当前遍历到第几个结点

	while (list[current].cursor!=0 && currentPosition < position )//判断position的合法性(并且判断的是当前的下一个指针是否为空，所以跳出循环时拿到的是所判断的前一个结点)
	{

		currentPosition++;
		current = list[current].cursor;//向后遍历

	}

	//判断位置的合法性,由于上面与判断可能会出现一真一假的情况，所以分别要对这两种情况再进行判断
	if (list[current].cursor == 0 || currentPosition > position)
	{

		printf("删除位置不合法。\n");
		return;

	}

	int deleteNode = list[current].cursor;//存放需要被删除结点的下标
	list[current].cursor = list[deleteNode].cursor;//被删除结点前一个结点指向被删除结点后一个结点
	FreeNode(list, deleteNode);//将被删除结点放入备用链表中
	
	return;

}

/*
	遍历链表
*/
void StaticListTraverse(StaticLinkList list)
{
	
	int current = list[MAXSIZE - 1].cursor;//从首结点开始向后遍历

	int currentPosition = 0;
	while (current !=0)
	{

		currentPosition++;
		printf("链表的第%d个结点为：%d。\n", currentPosition,list[current].data);
		current = list[current].cursor;//向后遍历

	}

}

/*
	回收被删除的结点
*/
void FreeNode(StaticLinkList list, int deleteNode)
{

	list[deleteNode].cursor = list[0].cursor;//将第一个元素的cursor赋值给被删除结点的cursor，deleteNode所在结点可以认为指向备用链表的第一个结点
	list[0].cursor = deleteNode;//将数组第一个元素的cursor设为deleteNode,即第数组一个元素的cursor可以人为指向以被删除结点为新的首结点的备用链表

}


//int main()
//{
//
//	StaticLinkList list;
//
//	//初始化静态链表
//	InitStaticList(list);
//
//	//插入元素到静态链表中
//	StaticListInsert(list, 1, 55);
//	StaticListInsert(list, 2, 66);
//	StaticListInsert(list, 1, 33);
//
//	//计算链表的长度
//	printf("链表的当前长度为:%d\n", StaticListLength(list));
//
//	//删除链表结点
//	StaticListDelete(list,4);
//
//	//遍历链表
//	StaticListTraverse(list);
//
//	printf("静态链表的长度为：%d。\n", StaticListLength(list));
//
//	return 0;
//
//}