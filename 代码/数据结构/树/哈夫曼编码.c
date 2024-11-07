#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <string.h>
#include <malloc.h>
//#include "�����������.c"


//����˳��洢�ṹ(һά����)�����������

#define N 8 //��ʾ��ʼʱ��N������Ȩֵ��ɭ�ֵ�ÿ��ֻ��һ�����������ĸ����

typedef struct//����һ�����������Ľ��
{

	int weight;//��ʾ����Ȩ
	int parent, leftChild, rightChild;//�ֱ�Ϊ����˫�׽��,���ӽ����Һ��ӽ����±�,0�����޺���/˫�׽��
	//����˫�׽����������ж�ɸѡɭ���еĸ����(�������˫��)
}HuffmanNode;
HuffmanNode huffmanTree[2 * N];//���ڴ�Ź�������������(����(1,N)��Ԫ���б�ʾ������ÿ����ֻӵ�и�����ɭ��,(N+1,2N)��Ԫ�����ڴ�źϲ���ʼɭ����N���������������N-1�����,�±�Ϊ0��Ԫ�ز�����κ�����)

typedef char* HuffmanCode[N+1];//����һ��ָ������,ָ��Ҷ�ӽ��Ĺ�������������(ͬ������ĵ�һ��ָ��ָ��Ϊ��)
/*
	���ݹ���������ȡÿ��Ҷ�ӽ��Ĺ���������
	��һ������:��Ź�������������ָ��
	�ڶ�������:һ��ָ������,ÿ��ָ��ָ���Ź�������Ҷ�ӽ��Ĺ��������������
*/
void CreateHuffmanCode(HuffmanNode* huffmanArray, HuffmanCode pCode)
{

	char* temp = (char*)malloc(N);//����һ����ʱ���ڷ��򿽱���������������鲢���ܹ�����Ŀ���������Ҷ�ӽ�������������������,(ÿ��Ҷ�ӽ��ı��볤��Ϊ����������������(N-1)+1)����һ��λ�÷�'\0',���Ա�ʾ����Ľ���λ��
	temp[N - 1] = '\0';//��ʼ�����������һ��Ԫ��Ϊ'\0',���Ա�ʾ����������Ľ�����־
	int start;//��ʾÿ�λ��ݳɹ���temp�����й���������ĵ�һ���ַ�����ʼ��ַ

	int i;
	for ( i = 1; i <= N; i++)//��N����������Ҷ�ӽ��Ĺ���������
	{

		//��Ϊ��֪��ÿ��Ҷ�ӽ��Ĺ���������ĳ��ȣ����Զ���һ����󳤶ȵ����飬ÿ���ɹ����һ��Ҷ�ӽڵ�Ĺ���������洢�ڸ������У�Ȼ��̬����һ���պ��������¸ñ��볤�ȵ��������洢

		start = N - 1;//��ʾ��ʱ��������һ��λ�õ��±�,����ʱ����ĸ��±괦��ʼ��ǰ�洢����
		int parent = huffmanArray[i].parent;//�ӵ�ǰҶ�ӽ���˫�׽�㿪ʼ����
		int current = i;//��ʾ��ǰҶ�ӽ����±�

		while (parent!=0)//��Ҷ�ӽ�����ϻ���
		{

			start--;//ÿ�λ���start��ǰһ��λ��
			if (huffmanArray[parent].leftChild == current)//��ǰ���Ϊ˫�׽������������Ϊ0,�������Ϊ1
				temp[start] = '0';
			else
				temp[start] = '1';

			//�ӵ�ǰ����˫�׽��������ϻ���
			current = parent;
			parent = huffmanArray[parent].parent;

		}

		//����Ҷ�ӽ��ɹ���startָ��temp�����д�Ź����������һ���ַ����±�

		pCode[i] = (char*)malloc(N - start);//N - start��ʾÿ�γɹ�����һ��Ҷ�ӽ��ʱ�õ��Ĺ���������ĳ���(����\0)������һ������洢���ݳɹ���Ҷ�ӽ��Ĺ���������,���ѵ�ַ���ظ�pCode[i]
		strcpy(pCode[i], &temp[start]);//����ʱ�����start�±괦(�����ݳɹ������һ�����������봦)�����ַ�����pCode[i]ָ����ַ�����
		//ע���������������ַ������ַ��ĵ�ַ,��Ҫ��д��strcpy(pCode[i], temp[start]);

	}

	free(temp);//�ͷŵ���ʱ����Ŀռ�

}


//
//int main()
//{
//
//	//�������ɹ���������ɭ�ֵĸ�����Ȩ������
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