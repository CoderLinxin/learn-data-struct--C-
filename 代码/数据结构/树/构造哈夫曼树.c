#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>

//����˳��洢�ṹ(һά����)�����������

#define N 8 //��ʾ��ʼʱ��N������Ȩֵ��ɭ�ֵ�ÿ��ֻ��һ�����������ĸ����

typedef struct//����һ�����������Ľ��
{

	int weight;//��ʾ����Ȩ
	int parent,leftChild,rightChild;//�ֱ�Ϊ����˫�׽��,���ӽ����Һ��ӽ����±�,0�����޺���/˫�׽��
	//����˫�׽����������ж�ɸѡɭ���еĸ����(�������˫��)
}HuffmanNode;
HuffmanNode huffmanTree[2 * N];//���ڴ�Ź�������������(����(1,N)��Ԫ���б�ʾ������ÿ����ֻӵ�и�����ɭ��,(N+1,2N)��Ԫ�����ڴ�źϲ���ʼɭ����N���������������N-1�����,�±�Ϊ0��Ԫ�ز�����κ�����)

void Select(HuffmanNode* huffmanArray, int range, int* pA, int* pB);

/*
	����һ�Ź�������
	����1:��������Ŀ���������������
	����2:���ڹ������������ɭ�ֵ�ÿ��������Ȩ������,������ظ�ԭ����
	����3:���ڹ������������ɭ�ֵ�ÿ��������Ȩ������ĳ���
*/
void CreateHuffmanTree(HuffmanNode* huffmanArray,int* weightArray,int length)
{

	if (length <= 1)
		return;

	//���ݸ�����Ȩ�������ʼ���������������(1,N)��Ԫ��(ע���±�Ϊ0��������κ�����)
	int i;
	for (i = 1; i <= length; i++)
	{

		huffmanArray[i].weight = weightArray[i - 1];
		//��ʼ������˫�׺ͺ��ӽ��Ϊ��
		huffmanArray[i].parent = 0;
		huffmanArray[i].leftChild = 0;
		huffmanArray[i].rightChild = 0;

	}

	//������������(��������������ϲ�������N-1������ŵ�ʣ������ռ���(���±�Ϊ0��))
	int j;
	int a,b;//���ڴ��ÿ�κϲ�ɭ���н��ʱ��ѡ�е����������±�
	for ( j = length+1; j <= 2*length-1; j++)
	{

		//��huffmanArray��(1,j-1)��Ԫ��(����ÿ�κϲ������������һ��������洢�������ÿ��ɸѡ��Χ��������)��ɸѡ������˫����Ϊ0(�������)��Ȩ��С�Ľ��,�������ǵ���Ÿ�a,b
		Select(huffmanArray,j-1, &a, &b);
		//����ɸѡ����ɭ���е�����������˫�׵��±�
		huffmanArray[a].parent = j;
		huffmanArray[b].parent = j;

		//�����²���ɸѡ������������˫�׵��й�����
		huffmanArray[j].leftChild = a;
		huffmanArray[j].rightChild = b;
		huffmanArray[j].weight = huffmanArray[a].weight + huffmanArray[b].weight;

	}

	for (int j = 1;j <= 2 * length - 1; j++)
	{

		if (huffmanArray[j].parent == 0)
			printf("���������ĸ������±�Ϊ:%d",j);//��������(ɭ��)�е�Ψһһ��parentΪ0�ľ��ǹ��������ĸ����

	}

}

void Select(HuffmanNode* huffmanArray, int range, int* pA, int* pB)
{

	int i;
	*pA = *pB = 0;
	huffmanArray[0].weight = 9999;//��ֹ���������һ��ֵΪ��Сֵ�����޷����������if�ж�
	//ð������ɸѡhuffmanArray��(1,range)�������Ȩ��С��������㲢������Ÿ�pA��pB
	for (i = 1; i <= range; i++)
	{

		if (huffmanArray[i].parent == 0)//ɸѡ���������ĸ����
		{

			if (huffmanArray[i].weight < huffmanArray[*pA].weight)//�뵱ǰ�õ�����Сֵ�Ƚ�
			{

				*pB = *pA;//*pB��¼��һ�αȽϵõ��Ľ�Сֵ
				*pA = i;//*pA��¼��αȽϵõ��Ľ�Сֵ

			}
			else if (huffmanArray[i].weight < huffmanArray[*pB].weight)//�뵱ǰ�õ��Ĵ�Сֵ�Ƚ�
				*pB = i;

		}


	}

}

//int main()
//{
//
//	//�������ɹ���������ɭ�ֵĸ�����Ȩ������
//	int sourse[N] = {5,29,7,8,14,23,3,11};
//	int length = sizeof(sourse) / sizeof(sourse[0]);
//
//	CreateHuffmanTree(huffmanTree,sourse,length);
//
//}