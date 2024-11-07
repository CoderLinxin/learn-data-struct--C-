#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>


/*****************************************			���Ŷ���				*****************************************/


#define MAXSIZE 1000//���農̬�������󳤶�Ϊ1000����Ч���ݳ���Ϊ998��


/*****************************************		��̬�����㶨��			*****************************************/


typedef DataType;//��̬������������������
typedef struct 
{

	DataType data;//����������
	int cursor;//���ڴ�ŵ�ǰ���ĺ�̽���������е��±꣬Ϊ0ʱ��ʾ��ǰ���Ϊβ���(��������NULL����ʾ)

}Node,StaticLinkList[MAXSIZE];//����һ��1000��Ԫ�صľ�̬�������������(ע��������)


/*****************************************			 ��������			*****************************************/


void InitStaticList(StaticLinkList);//��ʼ����̬����
int StaticListLength(StaticLinkList);//���㾲̬����ĳ���(��Ч���ĸ���)
void StaticListInsert(StaticLinkList,int,DataType);//�����㵽��̬������
int LeisureListPosition(StaticLinkList);//�ڱ��������в��ҿ��н��
void StaticListDelete(StaticLinkList, int);//ɾ�������ĳ�����
void FreeNode(StaticLinkList, int);//���ձ�ɾ���Ľ�㵽��������


/*****************************************			 ��������			*****************************************/


/*
	��ʼ����̬����
*/
void InitStaticList(StaticLinkList list)//�β����������ͣ�����������Ԫ�ص�ַ
{
	
	int i;

	//���ڴ�����̬����ʱ������β����ⶼ�Ǳ����������Գ�β����⣬��������cursor���δ����һ�����±�
	for ( i = 0; i < MAXSIZE-1; i++)
		list[i].cursor = i + 1;//�����һ�����±�

	list[MAXSIZE - 1].cursor = 0;//β����cursor��Ϊ0��ʾһ���ձ����ҵ����ձ��һ��λ�ò����һ��Ԫ��ʱ��0�ḳֵ���½���cursor��ʾ����Ľ���

	return;

}

/*
	��ȡ��̬�������Ч������
*/
int StaticListLength(StaticLinkList list)
{

	int first = list[MAXSIZE - 1].cursor;//��ȡ��̬�����еĵ�һ����Ч����������е��±�(ע���һ����Ч��㲻һ��������ĵڶ���Ԫ��)
	int current = first;//������ɱ�������

	int count = 0;

	while (current!=0)//current == 0 ���ʾ��������β�����һ���൱��phead != NULL
	{

		count++;
		current = list[current].cursor;

	}
	
	return count;

}

/*
	�ھ�̬�����ָ��λ���ϲ�����
*/
void StaticListInsert(StaticLinkList list, int position, DataType value)
{

	if (position<1 || position > StaticListLength(list) + 1)//�жϲ���λ�õĺϷ���,���ں�����ж��Ƿ��п��пռ��������ﲻ�ÿ��Ǳ�������Ϊ�յ����
	{

		printf("����λ�ò��Ϸ���\n");
		return;

	}
		
	int leisure = LeisureListPosition(list);//��ȡ����Ԫ�ص��±�

	if (leisure != 0)//�жϱ��������Ƿ�Ϊ��(���Ƿ�û�п���Ԫ��)
	{

		int current = MAXSIZE - 1;//��ʾ��ͷ��㿪ʼ�������൱��pHead

		int currentPosition = 0;//����ͳ�Ƶ�ǰ�������ڼ������
		//���ҵ� position - 1 ��������
		while (currentPosition < position -1)
		{

			currentPosition++;
			current = list[current].cursor;//������,����¼��ǰ���ڱ����Ľ����±�

		}
		
		list[leisure].data = value;//�����ݸ�ֵ������Ԫ��(���Կ���һ���´����Ľ��)��data
		list[leisure].cursor = list[current].cursor;//�½��ָ���position�����
		list[current].cursor = leisure;//��position - 1 �����ָ���½��

	}

}

/*
	�ڱ��������в��ҿ��н�㲢�������±�,����̬���������򷵻�0
*/
int LeisureListPosition(StaticLinkList list)
{

	//��ȡ���������е�һ�������±�
	int leisure = list[0].cursor;
	
	if (leisure)//����п��н����ô�����±�һ������ [1,MAXSIZE-1]���������,���農̬������������ô���һ����Ч����cursor������Ϊ0�ͱ����ǿ��ǽ�ȥ��
		list[0].cursor = list[leisure].cursor;//���±�������ĵ�һ�������±�
	return leisure;

}

/*
	ɾ����̬������positionλ���ϵĽ��
*/
void StaticListDelete(StaticLinkList list , int position)
{

	int current = MAXSIZE - 1;//��ͷ��㿪ʼ������������ɾ�������׽�㣬��Ҫ�õ�ǰһ����㼴ͷ��㣩
	int currentPosition = 1;//����ͳ�Ƶ�ǰ�������ڼ������

	while (list[current].cursor!=0 && currentPosition < position )//�ж�position�ĺϷ���(�����жϵ��ǵ�ǰ����һ��ָ���Ƿ�Ϊ�գ���������ѭ��ʱ�õ��������жϵ�ǰһ�����)
	{

		currentPosition++;
		current = list[current].cursor;//������

	}

	//�ж�λ�õĺϷ���,�����������жϿ��ܻ����һ��һ�ٵ���������Էֱ�Ҫ������������ٽ����ж�
	if (list[current].cursor == 0 || currentPosition > position)
	{

		printf("ɾ��λ�ò��Ϸ���\n");
		return;

	}

	int deleteNode = list[current].cursor;//�����Ҫ��ɾ�������±�
	list[current].cursor = list[deleteNode].cursor;//��ɾ�����ǰһ�����ָ��ɾ������һ�����
	FreeNode(list, deleteNode);//����ɾ�������뱸��������
	
	return;

}

/*
	��������
*/
void StaticListTraverse(StaticLinkList list)
{
	
	int current = list[MAXSIZE - 1].cursor;//���׽�㿪ʼ������

	int currentPosition = 0;
	while (current !=0)
	{

		currentPosition++;
		printf("����ĵ�%d�����Ϊ��%d��\n", currentPosition,list[current].data);
		current = list[current].cursor;//������

	}

}

/*
	���ձ�ɾ���Ľ��
*/
void FreeNode(StaticLinkList list, int deleteNode)
{

	list[deleteNode].cursor = list[0].cursor;//����һ��Ԫ�ص�cursor��ֵ����ɾ������cursor��deleteNode���ڽ�������Ϊָ��������ĵ�һ�����
	list[0].cursor = deleteNode;//�������һ��Ԫ�ص�cursor��ΪdeleteNode,��������һ��Ԫ�ص�cursor������Ϊָ���Ա�ɾ�����Ϊ�µ��׽��ı�������

}


//int main()
//{
//
//	StaticLinkList list;
//
//	//��ʼ����̬����
//	InitStaticList(list);
//
//	//����Ԫ�ص���̬������
//	StaticListInsert(list, 1, 55);
//	StaticListInsert(list, 2, 66);
//	StaticListInsert(list, 1, 33);
//
//	//��������ĳ���
//	printf("����ĵ�ǰ����Ϊ:%d\n", StaticListLength(list));
//
//	//ɾ��������
//	StaticListDelete(list,4);
//
//	//��������
//	StaticListTraverse(list);
//
//	printf("��̬����ĳ���Ϊ��%d��\n", StaticListLength(list));
//
//	return 0;
//
//}