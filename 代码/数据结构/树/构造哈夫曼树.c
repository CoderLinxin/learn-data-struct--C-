#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>

//采用顺序存储结构(一维数组)构造哈夫曼树

#define N 8 //表示初始时有N个给定权值的森林的每棵只有一个根结点的树的根结点

typedef struct//定义一个哈夫曼树的结点
{

	int weight;//表示结点的权
	int parent,leftChild,rightChild;//分别为结点的双亲结点,左孩子结点和右孩子结点的下标,0代表无孩子/双亲结点
	//有无双亲结点可以用来判断筛选森林中的根结点(根结点无双亲)
}HuffmanNode;
HuffmanNode huffmanTree[2 * N];//用于存放哈夫曼树的数组(其中(1,N)个元素中表示给定的每棵树只拥有根结点的森林,(N+1,2N)个元素用于存放合并初始森林中N个根结点所产生的N-1个结点,下标为0的元素不存放任何数据)

void Select(HuffmanNode* huffmanArray, int range, int* pA, int* pB);

/*
	构造一颗哈夫曼树
	参数1:用于生成目标哈夫曼树的数组
	参数2:用于构造哈夫曼树的森林的每个根结点的权的数组,结果返回给原数组
	参数3:用于构造哈夫曼树的森林的每个根结点的权的数组的长度
*/
void CreateHuffmanTree(HuffmanNode* huffmanArray,int* weightArray,int length)
{

	if (length <= 1)
		return;

	//根据给定的权的数组初始化哈夫曼树数组的(1,N)个元素(注意下标为0处不存放任何数据)
	int i;
	for (i = 1; i <= length; i++)
	{

		huffmanArray[i].weight = weightArray[i - 1];
		//初始化结点的双亲和孩子结点为无
		huffmanArray[i].parent = 0;
		huffmanArray[i].leftChild = 0;
		huffmanArray[i].rightChild = 0;

	}

	//建立哈夫曼树(将创建过程中因合并产生的N-1个结点存放到剩余数组空间中(除下标为0处))
	int j;
	int a,b;//用于存放每次合并森林中结点时所选中的两个结点的下标
	for ( j = length+1; j <= 2*length-1; j++)
	{

		//在huffmanArray的(1,j-1)个元素(由于每次合并两个结点生成一个结点额外存储起来因此每次筛选范围都会扩大)中筛选两个其双亲域为0(即根结点)且权最小的结点,返回他们的序号给a,b
		Select(huffmanArray,j-1, &a, &b);
		//设置筛选出的森林中的两个根结点的双亲的下标
		huffmanArray[a].parent = j;
		huffmanArray[b].parent = j;

		//设置新产生筛选的两个根结点的双亲的有关数据
		huffmanArray[j].leftChild = a;
		huffmanArray[j].rightChild = b;
		huffmanArray[j].weight = huffmanArray[a].weight + huffmanArray[b].weight;

	}

	for (int j = 1;j <= 2 * length - 1; j++)
	{

		if (huffmanArray[j].parent == 0)
			printf("哈夫曼树的根结点的下标为:%d",j);//查找数组(森林)中的唯一一个parent为0的就是哈夫曼树的根结点

	}

}

void Select(HuffmanNode* huffmanArray, int range, int* pA, int* pB)
{

	int i;
	*pA = *pB = 0;
	huffmanArray[0].weight = 9999;//防止出现数组第一个值为最小值导致无法进入下面的if判断
	//冒泡排序筛选huffmanArray中(1,range)个结点中权最小的两个结点并返回序号给pA和pB
	for (i = 1; i <= range; i++)
	{

		if (huffmanArray[i].parent == 0)//筛选符合条件的根结点
		{

			if (huffmanArray[i].weight < huffmanArray[*pA].weight)//与当前得到的最小值比较
			{

				*pB = *pA;//*pB记录上一次比较得到的较小值
				*pA = i;//*pA记录这次比较得到的较小值

			}
			else if (huffmanArray[i].weight < huffmanArray[*pB].weight)//与当前得到的次小值比较
				*pB = i;

		}


	}

}

//int main()
//{
//
//	//用于生成哈夫曼树的森林的根结点的权的数组
//	int sourse[N] = {5,29,7,8,14,23,3,11};
//	int length = sizeof(sourse) / sizeof(sourse[0]);
//
//	CreateHuffmanTree(huffmanTree,sourse,length);
//
//}