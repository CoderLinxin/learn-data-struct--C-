#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

/*****************************************			���Ŷ���			*****************************************/


#define ERROR -1//�����������ʱ����
#define NONE 0//����ͷ����������Ϊ��


/*****************************************		   �����㶨��		*****************************************/


typedef int DataType;//�������������������
/*
	����һ��������Ľ��
*/
 struct Node
{

	DataType data;//�������������ڴ������
	struct Node* pNext;//����ָ����ָ���������һ�����

}*pHead;//pHeadΪͷָ�룬������Ϊ����ͷ���ĵ��������pHeadָ��ͷ���
 typedef struct Node Node;


/*****************************************			 ��������			*****************************************/


Node* CreateListHead(int*,int);//ͷ�巨��������
Node* CreateListTail(int*,int);//β�巨��������
void TraverList(Node*);//��������
DataType GetElementList(Node*,int);//��ȡ����������
bool IsEmpty(Node*);//�ж������Ƿ�Ϊ��
int GetListLength(Node*);//ͳ������ĳ���
void SortList(Node*);//ʹ��ѡ�������������������
void InsertList(Node*,int, DataType);//�����Ա��ض�λ�ò���һ�����
int DeleteListElement(Node*, int);//ɾ�����Ա��е�һ���ض�λ�õĽ��
void DeleteList(Node*);//ɾ����������
Node* UnionListByChain(Node*,Node*);//�ϲ�������������(��������)


/*****************************************			 ��������			*****************************************/


/*
	ͷ�巨��������(���ݴ�������鼰�䳤������������)
	��ʼ���������������ָ��Ϸ�
*/
Node* CreateListHead(DataType* pArray, int length)
{

	//������ڴ������������Դ�ĺϷ���
	if (pArray == NULL)
	{

		printf("�봫��Ϸ�������ָ�롣\n");
		return ERROR;

	}
		
	Node* pHead = (Node*)malloc(sizeof(Node));//����ͷָ�룬��ָ��ͷ���

	//��ʼ��ͷ���
	pHead->data = NONE;
	pHead->pNext = NULL;

	//��������
	int i;

	for ( i = 0; i < length; i++)
	{

		Node* temp = (Node*)malloc(sizeof(Node));//�´������������
		temp->data = pArray[i];//�½��������ֵ
		temp->pNext = pHead->pNext;//�½��ָ��ͷ���nextָ��ָ��Ľ��(��ԭ������׽��)
		pHead->pNext = temp;//ͷ���nextָ��ָ���½ڵ�(�ý����Ϊ�µ��׽��.)

	}

	return pHead;

}

/*
	β�巨��������(���ݴ�������鼰�䳤������������)
	��ʼ���������������ָ��Ϸ�
*/
Node* CreateListTail(int* pArray, int length)
{

	//������ڴ������������Դ�ĺϷ���
	if (pArray == NULL)
	{

		printf("�봫��Ϸ�������ָ�롣\n");
		return ERROR;

	}

	Node* pHead = (Node*)malloc(sizeof(Node));//����ͷָ�룬��ָ��ͷ���

	//��ʼ��ͷ���
	pHead->data = NONE;
	pHead->pNext = NULL;

	//����ͷָ����Զָ��ͷ��㣬�����Ҫ����һ��β���(ʼ��ָ��β��)����������Ԫ��,�ձ�βָ��ָ��ͷ���
	Node* pTail = pHead;

	int i;
	for ( i = 0; i < length; i++)
	{

		//�½�һ�����
		Node* temp = (Node*)malloc(sizeof(Node));
		temp->data = pArray[i];//���½���������
		pTail->pNext = temp;//β���nextָ��ָ���½�㣬�ý����Ϊ�µ�β���
		pTail = temp;//β���ָ��ָ���µ�β���

	}
	pTail->pNext = NULL;//����β����nextָ��ΪNULL

	return pHead;

}

/*
	�Դ��������ָ����б���
*/
void TraverList(Node* pHead)
{

	Node* traverP = pHead->pNext;//��traverP��ɱ�������traverP��ʼָ��������׽��

	int length =0;//����ͳ������ĳ���(������ͷ���)
	while (traverP != NULL)
	{

		printf("����ĵ�%d������Ԫ��Ϊ��%d\n",length+1, traverP->data);
		traverP = traverP->pNext;//traverPָ��������
		length++;//���¼�����

	}

	return;

}

/*
	��ȡ�����ض�λ���ϵ�Ԫ��
	��ʼ����������Ϊ����position���㣺 0 < position < GetListLength(pHead)
*/
DataType GetElementList(Node* pHead , int position )
{

	if (IsEmpty(pHead) || position <= 0 || position > GetListLength(pHead))
	{

		printf("��ȡ����������ʧ�ܡ�\n");
		return ERROR;

	}

	int current =0 ;
	Node* travelP = pHead->pNext;

	while (travelP!=NULL)
	{

		current++;
		if (current == position)
		{

			printf("��ȡ��������ĵ�%d��Ԫ�أ�%d��\n",current, travelP->data);
			return;

		}

		travelP = travelP->pNext;//������

	}

}

/*
	�ж������Ƿ�Ϊ��
*/
bool IsEmpty(Node* pHead)
{

	if (pHead->pNext == NULL)
	{

		printf("����Ϊ�ա�");
		return true;

	}

	return false;

}

/*
	ͳ������ĳ���
*/
int GetListLength(Node* pHead)
{

	int length = 0;//����ͳ������ĳ���

	Node* traverP = pHead->pNext;//���ڱ��������ָ��

	while (traverP!=NULL)
	{

		length++;
		traverP = traverP->pNext;

	}

	return length;

}

/*
	�����Ա�position������һ��Ԫ��
	��ʼ������position���� 0 < position <= GetListLength(pHead) + 1
*/
void InsertList(Node* pHead, int position,DataType data)
{

	//�жϲ���Ԫ��λ���Ƿ�Ϸ�
	if (position<=0 || position > GetListLength(pHead)+1)
	{

		printf("����Ԫ��λ�ò��Ϸ���\n");
		return;

	}

	int current = 0;//���ڱ�ǵ�ǰλ��
	Node* traverP = pHead->pNext;//������ɱ�������

	while (traverP!=NULL)
	{

		current++;
		if (current == position-1)
		{

			//����һ�����
			Node* temp = (Node*)malloc(sizeof(Node));
			temp->data = data;
			temp->pNext = traverP->pNext;//�½��nextָ��ָ��ԭ��position�����
			traverP->pNext = temp;//��position-1�����nextָ��ָ���´����Ľ��
			return;

		}

		traverP = traverP->pNext;//������

	}

}

/*
	ɾ���������ض�λ���ϵĽ��
	��ʼ����:���Ա�Ϊ����position���㣺 0 < position <= GetListLength(pHead)
*/
int DeleteListElement(Node* pHead, int position)
{

	Node* traverP = pHead;//������ɱ�������,����ɾ���Ľ��Ϊ�׽�㣬�����Ҫ�õ�ǰһ����㼴ͷ��㣬���Դ�ͷ��㿪ʼ������
	int current = 1;//��ǵ�ǰλ��

	//�������ҵ�position-1λ���ϵĽ�㲢���жϵ���position������position-1	
	//ע��֮ǰ�жϵ���traverP !=NULL && current < position - 1 ���߼�����ʵ�����ǲ��� ��position - 1 ����� ,
	//����ʵ����������Ҫ�жϵ���position�Ƿ�Ϸ�����position�Ƿ� > 0 && <= ����ĳ���,���Ǹ��߼�����ȴ���������˲��ҵ�position-1�����,
	//����������Ϊ6��ɾ��λ��Ϊ7������ͨ����ѭ�����ǲ��ҵ��˵�6����㣬��Ϊ7-1 == 6 ǡ����position-1���Ǻ�����7���ǷǷ��ģ����������ж��ǲ��е�  
	//������position == 0 , ��ʱ����ж� traverP !=NULL��current��ʼ��Ϊ0ʱ��current == position �Ͳ����������current > position���жϣ����current��Ҫ��ʼ��Ϊ1������
	//ע��ؼ������ж�traverP->pNext����������current���Ը�Ϊ0 current < position-1
	while (traverP->pNext!=NULL && current < position)//�жϵ���position�ĺϷ��ԡ�
	{//����βָ��ΪNULL���Զ��˳�������ʵ�����ų���position > GetListLength(pHead)�������

		current++;
		traverP = traverP->pNext;

	}

	//�ж�λ�õĺϷ���,�����������жϿ��ܻ����һ��һ�ٵ���������Էֱ�Ҫ������������ٽ����ж�
	if (traverP->pNext == NULL || current > position)
	{

		printf("ɾ��λ�ò��Ϸ������Ա�Ϊ�ա�\n");
		return;

	}
	
	//��¼����ɾ���Ľ��(�Ա��ͷ��ڴ�)
	Node* pDelete = traverP->pNext;
	//����ɾ������(��position-1λ�ý��nextָ��ָ��positionλ�ý��nextָ����ָ��Ľ��)
	traverP->pNext = pDelete->pNext;
	free(pDelete);//�ͷű�ɾ���Ľ����ڴ�

	return;

}

/*
	ɾ���������ض�λ���ϵĽ��(ʵ��2)�Ƽ�ʹ��
	��ʼ����:���Ա�Ϊ����position���㣺 0 < position <= GetListLength(pHead)
*/
int DeleteListElement2(Node* pHead, int position)
{

	Node* traverP = pHead;//������ɱ�������,����ɾ���Ľ��Ϊ�׽�㣬�����Ҫ�õ�ǰһ����㼴ͷ��㣬���Դ�ͷ��㿪ʼ������
	int current = 0;//��ǵ�ǰλ��

	while (traverP->pNext != NULL && current < position-1)//Ѱ��position-1������㣬�����жϵ���position���Ľ��(traverP->pNext)�Ƿ����
	//(��Ϊɾ�������Ҫ����ɾ������ǰһ���ͺ�һ�������������,��ֻҪposition���Ľ�������ô��nextָ��Ҳ�ʹ���(��ʹΪNULL),��������������ɾ����������)
	{//����βָ��ΪNULL���Զ��˳�������ʵ�����ų���position > GetListLength(pHead)�������

		current++;
		traverP = traverP->pNext;

	}

	//�ж�λ�õĺϷ���,�����������жϿ��ܻ����һ��һ�ٵ���������Էֱ�Ҫ������������ٽ����ж�
	if (traverP->pNext == NULL || current > position-1)
	{

		printf("ɾ��λ�ò��Ϸ������Ա�Ϊ�ա�\n");
		return;

	}

	//��¼����ɾ���Ľ��(�Ա��ͷ��ڴ�)
	Node* pDelete = traverP->pNext;
	//����ɾ������(��position-1λ�ý��nextָ��ָ��positionλ�ý��nextָ����ָ��Ľ��)
	traverP->pNext = pDelete->pNext;
	free(pDelete);//�ͷű�ɾ���Ľ����ڴ�

	return;

}

/*
	ɾ����������(�������ÿ�)
*/
void DeleteList(Node* pHead)
{

	Node* traverP = pHead->pNext;//������ɱ�������
	Node* deleteP;//�������ɾ����������

	while (traverP != NULL)
	{

		deleteP = traverP->pNext;//��¼��һ�����(�Ա�������)
		free(traverP);//ɾ����㣨�ͷ��ڴ棩
		traverP = deleteP;//������

	}

	pHead->pNext = NULL;//ͷ���nextָ���ÿ�
	return;

}

/*
	��ѡ������������������(����)
*/
void SortList(Node* pHead)
{

	Node* traverP = pHead->pNext;//������ɱ������������

	int length = GetListLength(pHead);//��ȡ����ĳ���

	int i;
	Node* currentNode=traverP;//���ڼ�¼��ǰ���������λ��

	for ( i = 0; i < length; i++)//ÿ��forѭ���ź�һ��λ��
	{

		DataType temp = currentNode->data;//���ڴ洢�˴��������С�����Ա㽻������
		Node* tempNode= currentNode;//���ڼ�¼�˴���������С���ݵĽ��
		traverP = currentNode;//����������(����ÿ����һ��λ��travelP���ǻ�ָ��βָ�룬�����Ҫ��ÿ������ǰλ��ǰ����tavelPָ��)

		while (traverP!=NULL)
		{

			if (temp>traverP->data)
			{

				temp = traverP->data;//���¼�¼�ĵ�ǰ����λ���ϵ���Сֵ
				tempNode = traverP;//��¼���Ͻ�������Ľ��

			}

			traverP = traverP->pNext;//������

		}

		//���ݽ��������һ��λ�õ�����
		tempNode->data = currentNode->data;
		currentNode->data = temp;

		currentNode = currentNode->pNext;//����һ��λ�ý�������

	}

}

/*
	�ϲ�������������,���غϳɵ�Ŀ�������ͷָ��(��������)
*/
Node* UnionListByChain(Node* pAHead, Node* pBHead)
{

	//��pAHead��Ϊ�������C��ͷָ��
	Node* pCHead = pAHead;

	//�������ڱ���A,B,C���ָ��
	Node* aCurrent = pAHead->pNext;
	Node* bCurrent = pBHead->pNext;
	Node* cCurrent = pCHead;
	
	while (aCurrent&&bCurrent)//��A�������B����Ľ�㶼��Ϊβ���ʱ
	{

		//A��Ľ������С��B��Ľ�����������ν�����C��ĺ��棬��֮ͬ��
		if (aCurrent->data <= bCurrent->data)
		{

			cCurrent->pNext = aCurrent;
			cCurrent = aCurrent;//C��βָ�����(��Ϊÿ�ζ��ǲ��뵽C���β���֮��)
			aCurrent = aCurrent->pNext;//������

		}
		else
		{

			cCurrent->pNext = bCurrent;
			cCurrent = bCurrent;
			bCurrent = bCurrent->pNext;//������

		}

	}

	//��A���B����һ������β���ʱ
	cCurrent->pNext = aCurrent ? aCurrent : bCurrent;//ʣ�µķǿ�����ֱ�ӽӵ�C���β����
	free(pBHead);//�ͷ�b��ͷ���

	return pCHead;

}

//int main()
//{
//
//	//DataType array[] = {5,6,9,526,11,561};
//
//	////ע������array���ݽ�ȥ����sizeof���������ǵ�ַ�����Ĵ�С����������Ĵ�С
//	////pHead = CreateListHead(array, 6);
//
//	////�ж������Ƿ�Ϊ��
//	////IsEmpty(pHead);
//
//	////β�巨��������
//	//pHead = CreateListTail(array, 6);
//
//	////��ȡ������
//	//printf("����ĳ���Ϊ��%d��\n", GetListLength(pHead));
//
//	////��ȡ����Ԫ��
//	////GetElementList(pHead,5);
//
//	////������
//	////InsertList(pHead,7,999);
//
//	////�������������
//	////SortList(pHead);
//
//	////ɾ�����
//	//DeleteListElement2(pHead,7);
//	////DeleteList(pHead);
//
//	////��������б���
//	//TraverList(pHead);
//
//	//printf("����ĳ���Ϊ��%d��\n", GetListLength(pHead));
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