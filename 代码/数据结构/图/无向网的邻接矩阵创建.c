#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>

#define MaxNumber 9999//用于在邻接矩阵中表示两个顶点无边的情况
#define MaxVertexNumber 100//用于表示顶点表的最大长度

typedef char VertexType;//表示顶点表顶点的数据类型
typedef int WeighType;//代表边的权值类型

struct UnDirectionPicture
{

	VertexType VertexGraphic[MaxVertexNumber];//无向图的顶点表
	WeighType AdjacencyMatrix[MaxVertexNumber][MaxVertexNumber];//无向图的邻接矩阵
	int vertextNumber, edgeNumber;//表示当前无向图的有效顶点数和边数

}pUnDirectionPicture;//表示一个无向图
typedef struct UnDirectionPicture UnDirectionPicture;

/*
	创建一个无向图
*/
void CreateUnDirectionPicture(UnDirectionPicture* pPicture)
{

	//1.确定无向图的顶点数和边数

	printf("请输入需要创建的无向图的顶点数。");
	scanf("%d", &(pPicture->vertextNumber));

	printf("请输入需要创建的无向图的边数。");
	scanf("%d", &(pPicture->edgeNumber));

	//2.将顶点数据录入顶点表
	for (int i = 0; i < pPicture->vertextNumber; i++)
	{

		while (getchar() != '\n');//把上次输入的垃圾值过滤掉

		printf("请输入第%d个顶点的数据：", i + 1);
		scanf("%c", &pPicture->VertexGraphic[i]);

	}

	//3.初始化邻接矩阵中的边的权重为最大值

	for (int i = 0; i < pPicture->vertextNumber; i++)
		for (int j = 0; j < pPicture->vertextNumber; j++)
			pPicture->AdjacencyMatrix[i][j] = MaxNumber;

	//4.构造邻接矩阵

	int weigh = 0, k = 0, l = 0;
	char vertex1 = '0', vertex2 = '0';
	for (int i = 0; i < pPicture->edgeNumber; i++)
	{

		while (getchar() != '\n');//把上次输入的垃圾值过滤掉

		printf("请输入第%d条边所依附的顶点和边的权值(用#隔开)。\n", i + 1);
		scanf("%c#%c#%d", &vertex1, &vertex2, &weigh);

		//确定vertex1和vertex2对应的顶点在邻接矩阵中的位置
		k = LocateVertex(pPicture, vertex1);
		l = LocateVertex(pPicture, vertex2);

		//由于是无向图,因此权值关于两边是对称的
		pPicture->AdjacencyMatrix[k][l] = weigh;
		pPicture->AdjacencyMatrix[l][k] = pPicture->AdjacencyMatrix[k][l];

	}

}

/*
	查找顶点在顶点表中对应的下标
*/
int LocateVertex(UnDirectionPicture* pPicture,char vertex)
{

	for (int i = 0; i < pPicture->vertextNumber; i++)
		if (pPicture->VertexGraphic[i] == vertex)
			return i;

}

int visted[MaxNumber] = { 0 };//创建一个辅助数组用于标记深度优先遍历中的顶点是否被访问过(1代表访问过,0代表没访问过)

/*
	对邻接矩阵的深度优先遍历(递归实现)
	参数1:一个无向图
	参数2:需要最开始访问的邻接矩阵中的第一个顶点的下标
	注意没有边的点则不会遍历
*/
void DepthFirstSearch(UnDirectionPicture* pPicture, int firstIndex)
{

	//设置结点下标为firstIndex的状态为访问过
	visted[firstIndex] = 1;
	printf("访问了下标为%d的结点%c。\n",firstIndex,pPicture->VertexGraphic[firstIndex]);

	//遍历与邻接矩阵中下标为firstIndex的那一行即firstIndex为下标的结点的所有邻接点(由于采用循环里面嵌套递归的方式
	//当找到未访问的邻接点时则进入递归直到沿着该邻接点一直遍历下去,遍历完成之后会返回当前层继续下一层循环,当循环结束，即以遍历的起始结点的所有邻接点遍历完成即完成深度遍历)
	for (int i = 0; i < pPicture->vertextNumber; i++)
		if (pPicture->AdjacencyMatrix[firstIndex][i] != MaxNumber && visted[i]==0)
			DepthFirstSearch(pPicture, i);

}


//int main()
//{
//
//	UnDirectionPicture pUnDirectionPicture;
//
//	CreateUnDirectionPicture(&pUnDirectionPicture);
//
//	DepthFirstSearch(&pUnDirectionPicture, 2);//从下标为2的顶点表中的顶点开始在邻接矩阵中进行深度遍历
//
//	//int l = 0;
//	//遍历邻接矩阵
//	//for (int i = 0; i < pUnDirectionPicture.vertextNumber; i++)
//	//{
//
//	//	for (; l < 1;l++)
//	//	{
//
//	//		printf("%-5c",' ');
//	//		for (int  k = 0; k < pUnDirectionPicture.vertextNumber; k++)
//	//		{
//
//	//			printf("%-5c ",pUnDirectionPicture.VertexGraphic[k]);
//
//	//		}
//	//		printf("\n");
//
//	//	}
//
//	//	printf("%c ", pUnDirectionPicture.VertexGraphic[i]);
//
//	//	for (int j = 0; j < pUnDirectionPicture.vertextNumber; j++)
//	//	{
//
//	//		printf("%-5d ",pUnDirectionPicture.AdjacencyMatrix[i][j]);
//
//	//	}
//
//	//	printf("\n");
//
//	//}
//
//
//
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
