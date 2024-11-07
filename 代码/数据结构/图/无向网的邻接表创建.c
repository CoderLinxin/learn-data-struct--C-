#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

#define MaxNumber 20//表示邻接表中头结点数组的最大长度

typedef int weigh;//代表权的数据类型

/*
	邻接表的表结点定义(每个表结点代表与其对应头结点组成一条边)
*/
struct EdgeNode
{

	int VertexIndex;//代表头结点数组中,与该边对应的头结点所组成的另一条边的另一个结点的下标
	weigh info;//表示该边对应的权
	struct EdgeNode* nextEdge;//用于串联该边所对应头结点的下一条边

};
typedef struct EdgeNode EdgeNode;

typedef char HeadNodeType;//邻接表头结点的数据类型
/*
	邻接表的头结点定义
*/
struct HeadNode
{

	HeadNodeType data;//头结点的数据域
	EdgeNode* firstEdge;//指向头结点的第一条边(注意每条边的地位是平行的没有先后顺序)

};
typedef struct HeadNode HeadNode;

/*
	无向网的结构定义
*/
 struct Picture
{

	int vextexNumber, edgeNumber;//代表整个网结构所对应的顶点数和边数
	HeadNode headNodeArray[MaxNumber];//代表邻接表的头结点数组

};
typedef struct Picture  Picture;

/*
	在pPicture指向的图结构的头结点数组中查找vertex对应的下标
*/
VertexLocate(Picture* pPicture, HeadNodeType vertex)
{

	for (int i = 0; i < pPicture->vextexNumber; i++)
		if (pPicture->headNodeArray[i].data == vertex)
			return i;

}

/*
	创建无向网的链式存储结构-邻接表
*/
void CreateUDPByList(Picture* pPicture)
{

	//1.确定无向网的顶点个数和边数

	printf("请输入需要创建的无向图的顶点数。");
	scanf("%d", &(pPicture->vextexNumber));

	printf("请输入需要创建的无向图的边数。");
	scanf("%d", &(pPicture->edgeNumber));

	//2.构造头结点数组
	for (int i = 0; i < pPicture->vextexNumber; i++) 
	{

		while (getchar() != '\n');//把上次输入的垃圾值过滤掉

		printf("请输入第%d个顶点的数据：", i + 1);
		scanf("%c", &pPicture->headNodeArray[i].data);//初始化头结点数组的数据
		pPicture->headNodeArray[i].firstEdge = NULL;//将头结点的边指针域置空

	}

	HeadNodeType vertex1='0', vertex2='0';
	int j = 0,k=0;
	weigh  weighTemp = 0;
	EdgeNode* temp = NULL;

	//3.构造邻接表
	for (int i = 0; i < pPicture->edgeNumber; i++)
	{

		while (getchar() != '\n');//把上次输入的垃圾值过滤掉

		//4.输入边的两个结点和权值

		printf("请输入第一条边关联的顶点即对应的权值(用#隔开):");//如a#b#20
		scanf("%c#%c#%d", &vertex1, &vertex2, &weighTemp);

		//找出vertex1和vertex2在头结点数组中对应的下标
		j = VertexLocate(pPicture, vertex1);
		k = VertexLocate(pPicture, vertex2);

		//5.根据输入的结点和权构造表结点(相当于构造边 j - k )

		temp = (EdgeNode*)malloc(sizeof(EdgeNode));//新建一个表结点
		temp->VertexIndex = j;//该表结点与对应的头结点组成的边的另一个头结点的下标
		temp->info = weighTemp;//数据更新

		//6.头插法插入表结点

		temp->nextEdge = pPicture->headNodeArray[k].firstEdge;
		pPicture->headNodeArray[k].firstEdge = temp;

		//7.构造边( k - j )

		temp = (EdgeNode*)malloc(sizeof(EdgeNode));
		temp->VertexIndex = k;
		temp->info = weighTemp;

		temp->nextEdge = pPicture->headNodeArray[j].firstEdge;
		pPicture->headNodeArray[j].firstEdge = temp;

	}

	return;

}

/*
	遍历无向图的邻接表
*/
void TraverPicture(Picture* pPicture)
{

	//遍历头结点数组
	for (int i = 0; i < pPicture->vextexNumber; i++)
	{

		printf("%c ",pPicture->headNodeArray[i].data);

		EdgeNode* current=pPicture->headNodeArray[i].firstEdge;//用于完成遍历任务
		//遍历每个头节点数组对应的表结点
		while (current!=NULL)
		{

			printf(" %c权:%d", pPicture->headNodeArray[current->VertexIndex].data, current->info);
			current = current->nextEdge;
		}

		printf("\n");

	}

}

/*****************************************		  循环队列定义			*****************************************/

#define MAXSIZE 20//表示循环队列的最大长度

typedef HeadNode QueueElementType;//队列元素的数据类型
struct Queue
{

	QueueElementType* base;//初始化的动态分配的存储空间
	int front;//代表队列的头指针，指向队头元素
	int rear;//代表队列的尾指针,指向队尾的下一个元素

}*pQueue;
typedef struct Queue Queue;

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
		return;

	}

	pQueue->front = pQueue->rear = 0;//队列置空

	return pQueue;

}

/*
	判断队列是否为空
	初始条件：队列存在
*/
bool EmptyQueue(Queue* pQueue)
{

	if (pQueue->front == pQueue->rear)
		return true;

	return false;

}

/*
	入队一个元素
	初始条件：队列存在且队列不为满
*/
void EnQueue(Queue* pQueue, QueueElementType* headNode)
{

	//判断是否队满
	if ((pQueue->rear + 1) % MAXSIZE == pQueue->front)
	{

		printf("入队失败：队列已满。\n");
		return;

	}

	//插入元素到队尾
	pQueue->base[pQueue->rear] = *headNode;
	pQueue->rear = (pQueue->rear + 1) % MAXSIZE;//队尾指针后移

	return;

}

/*
	出队一个元素,将元素的地址返回给*headNode
	初始条件：队列存在且不为空
*/
void DeQueue(Queue* pQueue, QueueElementType** headNode)
{

	if (EmptyQueue(pQueue))
	{

		printf("出队失败：队列不存在或为空。\n");
		return;

	}

	*headNode = &(pQueue->base[pQueue->front]);
	pQueue->front = (pQueue->front + 1) % MAXSIZE;//头指针后移

	return;

}

int  visted1[MaxNumber] = { 0 };//一个辅助数组用于标记无向网的结点是否被访问过

/*
	邻接表的广度优先遍历(借助队列实现)(同样本函数只考虑连通图的广度优先遍历)
	参数1：需要进行广度优先遍历的图
	参数2：进行广度优先遍历的初始结点的下标
*/
void BreadthFirstSearch(Picture* pPicture,int firstIndex)
{

	//创建一个队列
	Queue* queue = IniteQueue();
	//将需要遍历的第一个结点入队
	EnQueue(queue, &(pPicture->headNodeArray[firstIndex]));

	visted1[firstIndex] = 1;//将头结点数组中下标为firstIndex结点标记为访问过

	printf("访问了结点:%c.\n",pPicture->headNodeArray[firstIndex].data);//访问初始结点

	HeadNode* temp1;
	EdgeNode* temp2;

	while (!EmptyQueue(queue))//假设队列不为空
	{

		DeQueue(queue, &temp1);//队头元素出队并赋值给temp1

		//对出队的元素结点进行广度遍历(遍历其对应的所有边(表)结点)
		temp2 = temp1->firstEdge;
		while (temp2!=NULL)
		{

			if (visted1[temp2->VertexIndex]==0)//该表结点没有访问过则进行访问
			{

				printf("访问了结点:%c.\n", pPicture->headNodeArray[temp2->VertexIndex].data);//访问当前出队结点的所有邻接点(邻接表中的边(表)结点)
				visted1[temp2->VertexIndex] = 1;//标记为访问过
				EnQueue(queue, &(pPicture->headNodeArray[temp2->VertexIndex]));//入队一个元素(入队的是边结点VertexIndex下标对应的头结点)

			}

			temp2 = temp2->nextEdge;//向后遍历表结点

		}

	}

}


int main()
{

	Picture picture;

	//创建邻接表
	CreateUDPByList(&picture);

	////遍历邻接表
	//TraverPicture(&picture);

	BreadthFirstSearch(&picture, 0);

}