#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

/*
	线性表的抽象数据类型：
	ADT List{
		Data:D = {a[i] | a[i] 属于Eleset,(i=1,2,...,n,n>=0)}
		Relation:R = {<a[i-1],a[i]>(序偶性) | a[i-1],a[i]属于D,(i=2,3,..,n)}
		Operation:
		initList(&L);
		DestroyList();
		ListInsert(&L,i,e);
		AppendList(&L,e);
		ListDelete(&L,i,&e);
		ListEmpty(L);
		ListLength(L);
		GetElement(L,i,&e);
		LocateElement(L,e,compare());
		PriorElem(L,current,&pre);
		NextElem(L,current,&next);
		ListTraverse(&L,visted());
	}
*/


/*****************************************			符号定义			*****************************************/


#define MAX_SIZE 20 //线性表的最大长度
#define ORIGANL 0//用来初始化线性表的元素
#define ERROR -1 //代表操作线性表时出错
#define EMPTYLIST -2//用来标记一个空表
#define NOTEMPTYLIST -3//用来标记一个非空线性表


/*****************************************			线性表定义			*****************************************/	


typedef int ElementType;//线性表中的数据元素类型

struct List
{

	ElementType* data;//用于存放线性表的数组data为指向该数组的指针
	int length;//线性表的当前长度

}*pList;
typedef struct List List;


/*****************************************			 方法声明			*****************************************/


List* InitList();//创建一个线性表(本案例未实现可扩容)
void DestroyList(List*);//销毁一个线性表
int ListInsert(List*, int, ElementType);//向线性表指定位置插入元素
int AppendList(List*, ElementType);//在线性表末尾追加一个元素
int ListDelete(List*, int);//删除线性表中指定位置的元素
int ListEmpty(List*);//判断线性表是否为空表
int ListLength(List*);//获取线性表的长度
int GetElement(List*, int);//获取线性表中指定位置的元素的值
int LocateElement(List*, ElementType, bool(*)(ElementType, ElementType));//查询线性表中是否有某值，有则返回符合的第一个元素的位序
int PriorElem(List*, int);//获取线性表中某元素的前驱元素
int NextElem(List*, int);//获取线性表中某元素的后继元素
void ListTraverse(List*, void(*)(ElementType, ElementType));//遍历线性表中的元素并进行visted操作
List* UnionListByOrder(List*,List*);//合并两个有序顺序表（升序排列）


/*****************************************			 方法定义			*****************************************/


/*
	创建一个线性表，并初始化线性表元素，返回指向该线性表的指针
*/
List* InitList()
{

	List* pList = (List*)malloc(sizeof(List));//开辟一块连续的动态内存来存储线性表
	pList->length = 0;//设置线性表长度为0，表示线性表中无元素
	pList->data = (ElementType*)malloc(sizeof(ElementType)*MAX_SIZE);//创建线性表的数据

	//初始化线性表
	int i=0;
	for ( i = 0; i < MAX_SIZE; i++)
		pList->data[i] = ORIGANL;

	return pList;//返回线性表的指针
}

/*
	销毁指针p指向的线性表，即把p指向的空间释放,并把p置空
	//初始条件：p指向不为空
*/
void DestroyList(List** pList)//修改一级指针变量的值需要二级指针
{

	if (*pList == NULL)
	{
		printf("删除线性表失败,error:指向了无效的线性表\n");
		return 0;
	}

	free(*pList);
	*pList = NULL;

}

/*
	在线性表中第i个位置处插入元素
	初始条件：线性表存在且线性表元素未满，且position满足：1 ≤ position ≤ List.lengh+1
*/
int ListInsert(List* pList, int position, ElementType value)
{

	//线性表已满

	if (pList->length == MAX_SIZE)
	{

		printf("线性表已满，无法插入元素。\n");
		return ERROR;

	}

	//线性表未满

	//判断插入位置是否合法,即只允许在当前线性表有效队列中插入元素
	if (position <= 0 || position > pList->length+1)
	{

		printf("无法在该位置上插入元素，当前线性表长度为：%d\n", pList->length);
		return ERROR;

	}

	//将插入位置以后的元素都后移一位
	int i = pList->length - 1;//标识线性表的末尾元素
	while (i >= position - 1)
	{

		pList->data[i + 1] = pList->data[i];//元素后移一位
		i--;

	}

	pList->data[i+1] = value;//将新元素插入
	pList->length++;//线性表长度+1

	return 1;

}

/*
	在线性表末尾追加一个元素
	初始条件：线性表存在且线性表未满
*/
int AppendList(List* pList, ElementType value)
{

	if (pList == NULL)
	{

		printf("线性表不存在\n");
		return ERROR;

	}

	//线性表已满

	if (pList->length == MAX_SIZE)
	{

		printf("线性表已满，无法追加元素。\n");
		return ERROR;

	}

	//线性表未满

	//向线性表末尾追加一个元素
	pList->data[pList->length] = value;
	pList->length++;//更新线性表长度

	return 0;

}

/*
	删除线性表上指定位置的元素
	初始条件：线性表不为空，且position满足：1 ≤ position ≤ List.lengh
*/
int ListDelete(List*pList, int position)
{

	//线性表存在且不为空
	if (ListEmpty(pList) == EMPTYLIST)
	{

		printf("线性表为空。");
		return EMPTYLIST;

	}

	//线性表不为空

	//判断删除位置是否合法
	if (position <= 0 || position > pList->length)
	{

		printf("删除元素失败,当前线性表长度为：%d\n", pList->length);
		return ERROR;

	}

	//position后的元素直接全部往前移一位
	int i = pList->length - 1;//标记线性表末尾元素
	while (position-1 < i)
	{

		pList->data[position-1] = pList->data[position];
		position++;

	}

	pList->data[position-1] = ORIGANL;//将原本线性表末尾元素置为初始值(也可以不用，我们用length来限制) 
	pList->length--;//更新线性表长度

	return 0;

}

/*
	判断线性表是否为空
	初始条件：需要判断的线性表存在
*/
int ListEmpty(List* pList)
{

	if (pList == NULL)
	{

		printf("请传入正确的线性表指针。\n");
		return ERROR;

	}	

	if (pList->length == 0)
		return EMPTYLIST;

	return NOTEMPTYLIST;

}

/*
	查询线性表的长度
	初始条件：查询的线性表存在
*/
int ListLength(List* pList)
{

	if (pList == NULL)
	{

		printf("查询线性表不存在。\n");
		return ERROR;

	}

	int length=pList->length;
	printf("线性表长度为：%d\n", length);
	return length;

}

/*
	获取线性表中特定位置上元素的值
	初始条件：线性表存在且不为空表，position满足：1 <= position <= length
*/
int GetElement(List* pList, int position)
{

	//线性表存在且不为空
	if (ListEmpty(pList) == EMPTYLIST)
	{

		printf("线性表为空。");
		return EMPTYLIST;

	}

	//判断position的合法性
	if (position <= 0 || position > pList->length)
	{

		printf("查询错误，该位置不在线性表上。\n");
		return ERROR;

	}

	//返回查询到的值
	ElementType result = pList->data[position - 1];
	printf("位于线性表第%d个元素的值为：%d。\n",position, result);
	return result;

}

/*
	//查询线性表中是否有某值，有则返回符合的第一个元素的位序
	//初始条件：线性表存在且不为空
*/
int LocateElement(List* pList, ElementType value, bool(*compare)(ElementType, ElementType))
{

	//线性表存在且不为空
	if (ListEmpty(pList) == EMPTYLIST)
	{

		printf("线性表为空。");
		return EMPTYLIST;

	}

	//遍历线性表并进行比较
	int i ;
	for ( i = 0; i < pList->length; i++)
	{

		//调用比较函数进行比较
		if (compare(pList->data[i], value) == true)
		{

			int position = i + 1;
			printf("查询到了该元素位于线性表的第%d个位置上。\n",position);
			return position;

		}

	}
	
	printf("在线性表上查询不到该元素。\n");
	return 0;

}
/*
	用于比较两个元素是否相等
*/
bool compare(ElementType value1, ElementType value2)
{

	if (value1 == value2)
		return true;
	else
		return false;

}

/*
	查询线性表中某位置元素的前驱元素
	初始条件：线性表存在且不为空,current满足： 1 < current <= length
*/
int PriorElem(List* pList, int current)
{

	//线性表存在且不为空
	if (ListEmpty(pList) == EMPTYLIST)
	{

		printf("线性表为空。");
		return EMPTYLIST;

	}

	//判断当前元素是否是线性表的首元素
	if (current == 1)
	{

		printf("该元素为线性表的头结点，无直接前驱。\n");
		return 0;

	}
	
	if (1 < current &&current <= pList->length)
	{

		//返回当前元素的直接前驱元素
		ElementType value = pList->data[current - 2];
		printf("当前元素的直接前驱元素的值为：%d。\n", value);
		return value;

	}
	else
	{

		printf("查找位置非法。");

	}

}

/*
	查询线性表中某位置元素的后继元素
	初始条件：线性表存在且不为空,current满足： 1 <= current < length
*/
int NextElem(List* pList, int current)
{

	//线性表存在且不为空
	if (ListEmpty(pList) == EMPTYLIST)
	{

		printf("线性表为空。");
		return EMPTYLIST;

	}

	//判断当前元素是否是线性表的末尾元素
	if (current == pList->length)
	{

		printf("该元素为线性表的尾结点，无直接后继。\n");
		return 0;

	}

	if (1 <= current &&current < pList->length)
	{

		//返回当前元素的直接后继元素
		ElementType value = pList->data[current ];
		printf("当前元素的直接后继元素的值为：%d。\n", value);
		return value;

	}else
	{

		printf("查找位置非法。");

	}

}

/*
	遍历线性表中的元素并进行visted操作
	初始条件：线性表存在且不为空
*/
void ListTraverse(List* pList, void(*visited)(ElementType, ElementType))
{

	//线性表存在且不为空
	if (ListEmpty(pList) == EMPTYLIST)
	{

		printf("线性表为空。");
		return EMPTYLIST;

	}
	
	int i;
	for ( i = 0; i < pList->length; i++)
		visited(pList->data[i],i+1);

	return 0;

}
/*
	进行一次访问操作
*/
void Visted(ElementType value, ElementType position)
{

	printf("线性表的第%d个元素：%d。\n",position, value);

}

/*
	将线性表La和Lb合并到La中
	初始条件：线性表a和b存在
*/
void  unionL(List* La,List* Lb)
{

	//判断并操作对象的合法性
	if (La == NULL || Lb == NULL)
	{

		printf("并操作的某一操作数不合法。");
		return ERROR;

	}

	//查找存在于Lb但不存在于La的元素插入La中

	int lenB = ListLength(Lb);//获取Lb长度

	//遍历Lb
	int i;
	for ( i = 1; i <= lenB; i++)
	{

		//查找存在于Lb不存在于La的元素
		ElementType temp = GetElement(Lb,i);
		if (!LocateElement(La, temp,compare))
			AppendList(La, temp);//在La后面追加该元素

	}

	return 0;

}

/*
	合并两个有序顺序表,返回合并结果的指针pC(升序排列)
*/
List* UnionListByOrder(List* pListA, List* pListB)
{
	
	//声明两个变量表示A，B线性表的尾结点的下标
	int pALast = pListA->length-1;
	int pBLast = pListB->length-1;
	
	int lengthC = pListA->length + pListB->length;//计算表A和表B的大小之和

	List* pListC = (List*)malloc(sizeof(List));//创建一个线性表C

	pListC->length = lengthC;//线性表C的长度设置为表A和表B的长度之和以便存放合并后的结果
	pListC->data = (ElementType*)malloc(sizeof(ElementType)*MAX_SIZE);

	//表示A，B,c线性表的首结点的下标
	int aStart = 0,bStart = 0,cStart=0;

	while (aStart<= pALast &&bStart<= pBLast)//两个表都非空
	{

		//分别比较AB表中的数据，如果A表中的结点数据小于B表中的结点数据则A的该结点先存入C中，否则同理
		if (pListA->data[aStart] <= pListB->data[bStart])
			pListC->data[cStart++] = pListA->data[aStart++];
		else
			pListC->data[cStart++] = pListB->data[bStart++];

	}

	//B表为空直接把A表的数据装入C表中
	while (aStart <= pALast)
		pListC->data[cStart++] = pListA->data[aStart++];
	
	//A表为空直接把B表的数据装入C表
	while (bStart <= pBLast)
		pListC->data[cStart++] = pListB->data[bStart++];

	return pListC;

}



/*****************************************			 主函数				*****************************************/

int main()
{

	////创建一个线性表
	//pList = InitList();

	//判断线性表是否为空
	//int isEmpty = ListEmpty(pList);
	//if (isEmpty == EMPTYLIST)
	//{
	//	printf("该表为空。\n");
	//}
	//else if (isEmpty == NOTEMPTYLIST)
	//{
	//	printf("非空表。\n");
	//}

	////插入元素到线性表中
	//ListInsert(pList,1,1);
	//ListInsert(pList,2,2);
	//ListInsert(pList,1,10);

	////查询线性表中的元素
	//GetElement(pList,2);

	////在线性表上查询某值
	//LocateElement(pList, 2, compare);

	////查询线性表长度
	//int length = ListLength(pList);

	//向线性表追加元素
	//AppendList(pList, 5);
	//AppendList(pList, 6);
	//AppendList(pList, 7);

	//ListDelete(pList,2);
	//ListDelete(pList,5);

	////查找线性表中某位置元素的直接前驱元素
	//PriorElem(pList, 2);

	////查找线性表中某位置元素的直接后继元素
	//NextElem(pList, 1);

	////遍历线性表
	//ListTraverse(pList, Visted);

	//List* pList2 = InitList();

	//AppendList(pList2, 19);
	//AppendList(pList2, 5);
	//AppendList(pList2, 6);
	//AppendList(pList2, -1);
	//AppendList(pList2, 555);

	//unionL(pList, pList2);

	////销毁线性表
	//DestroyList(&pList);


	List* pListA = InitList();
	AppendList(pListA,15);
	AppendList(pListA,50);
	AppendList(pListA,60);
	AppendList(pListA,70);
	AppendList(pListA,100);

	List* pListB = InitList();
	AppendList(pListB, 2);
	AppendList(pListB, 20);
	AppendList(pListB, 99);

	List* pListC = UnionListByOrder(pListA, pListB);
	
	ListTraverse(pListC,Visted);

}