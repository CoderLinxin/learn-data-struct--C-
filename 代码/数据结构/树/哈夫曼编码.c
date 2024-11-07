#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <string.h>
#include <malloc.h>
//#include "构造哈夫曼树.c"


//采用顺序存储结构(一维数组)构造哈夫曼树

#define N 8 //表示初始时有N个给定权值的森林的每棵只有一个根结点的树的根结点

typedef struct//定义一个哈夫曼树的结点
{

	int weight;//表示结点的权
	int parent, leftChild, rightChild;//分别为结点的双亲结点,左孩子结点和右孩子结点的下标,0代表无孩子/双亲结点
	//有无双亲结点可以用来判断筛选森林中的根结点(根结点无双亲)
}HuffmanNode;
HuffmanNode huffmanTree[2 * N];//用于存放哈夫曼树的数组(其中(1,N)个元素中表示给定的每棵树只拥有根结点的森林,(N+1,2N)个元素用于存放合并初始森林中N个根结点所产生的N-1个结点,下标为0的元素不存放任何数据)

typedef char* HuffmanCode[N+1];//定义一个指针数组,指向叶子结点的哈夫曼编码数组(同样数组的第一个指针指向为空)
/*
	根据哈夫曼树获取每个叶子结点的哈夫曼编码
	第一个参数:存放哈夫曼树的数组指针
	第二个参数:一个指针数组,每个指针指向存放哈夫曼树叶子结点的哈夫曼编码的数组
*/
void CreateHuffmanCode(HuffmanNode* huffmanArray, HuffmanCode pCode)
{

	char* temp = (char*)malloc(N);//分配一个临时用于反向拷贝哈夫曼编码的数组并且能够容纳目标哈夫曼树叶子结点的最长哈夫曼编码的数组,(每个叶子结点的编码长度为哈夫曼树的最大深度(N-1)+1)增加一个位置放'\0',用以表示编码的结束位置
	temp[N - 1] = '\0';//初始化数组中最后一个元素为'\0',用以表示哈夫曼编码的结束标志
	int start;//表示每次回溯成功后temp数组中哈夫曼编码的第一个字符的起始地址

	int i;
	for ( i = 1; i <= N; i++)//求N个哈夫曼树叶子结点的哈夫曼编码
	{

		//因为不知道每个叶子结点的哈夫曼编码的长度，所以定义一个最大长度的数组，每当成功求得一个叶子节点的哈夫曼编码存储在该数组中，然后动态创建一个刚好能容纳下该编码长度的数组来存储

		start = N - 1;//表示临时数组的最后一个位置的下标,从临时数组的高下标处开始向前存储数据
		int parent = huffmanArray[i].parent;//从当前叶子结点的双亲结点开始找起
		int current = i;//表示当前叶子结点的下标

		while (parent!=0)//从叶子结点向上回溯
		{

			start--;//每次回溯start向前一个位置
			if (huffmanArray[parent].leftChild == current)//当前结点为双亲结点的左孩子则编码为0,否则编码为1
				temp[start] = '0';
			else
				temp[start] = '1';

			//从当前结点的双亲结点继续向上回溯
			current = parent;
			parent = huffmanArray[parent].parent;

		}

		//回溯叶子结点成功后start指向temp数组中存放哈夫曼编码第一个字符的下标

		pCode[i] = (char*)malloc(N - start);//N - start表示每次成功回溯一个叶子结点时得到的哈夫曼编码的长度(包括\0)，分配一个数组存储回溯成功的叶子结点的哈夫曼编码,并把地址返回给pCode[i]
		strcpy(pCode[i], &temp[start]);//从临时数组的start下标处(即回溯成功的最后一个哈夫曼编码处)拷贝字符串给pCode[i]指向的字符数组
		//注意两个参数都是字符串首字符的地址,不要错写成strcpy(pCode[i], temp[start]);

	}

	free(temp);//释放掉临时数组的空间

}


//
//int main()
//{
//
//	//用于生成哈夫曼树的森林的根结点的权的数组
//	int sourse[N] = {5,29,7,8,14,23,3,11};
//	int length = sizeof(sourse) / sizeof(sourse[0]);
//
//	CreateHuffmanTree(huffmanTree,sourse,length);
//
//	HuffmanCode huffmanCode;
//	int codeLength = sizeof(huffmanCode) / sizeof(huffmanCode[0]);
//	CreateHuffmanCode(huffmanTree, huffmanCode);
//
//}