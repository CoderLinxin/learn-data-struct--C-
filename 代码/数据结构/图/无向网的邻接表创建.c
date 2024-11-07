#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

#define MaxNumber 20//��ʾ�ڽӱ���ͷ����������󳤶�

typedef int weigh;//����Ȩ����������

/*
	�ڽӱ�ı��㶨��(ÿ��������������Ӧͷ������һ����)
*/
struct EdgeNode
{

	int VertexIndex;//����ͷ���������,��ñ߶�Ӧ��ͷ�������ɵ���һ���ߵ���һ�������±�
	weigh info;//��ʾ�ñ߶�Ӧ��Ȩ
	struct EdgeNode* nextEdge;//���ڴ����ñ�����Ӧͷ������һ����

};
typedef struct EdgeNode EdgeNode;

typedef char HeadNodeType;//�ڽӱ�ͷ������������
/*
	�ڽӱ��ͷ��㶨��
*/
struct HeadNode
{

	HeadNodeType data;//ͷ����������
	EdgeNode* firstEdge;//ָ��ͷ���ĵ�һ����(ע��ÿ���ߵĵ�λ��ƽ�е�û���Ⱥ�˳��)

};
typedef struct HeadNode HeadNode;

/*
	�������Ľṹ����
*/
 struct Picture
{

	int vextexNumber, edgeNumber;//�����������ṹ����Ӧ�Ķ������ͱ���
	HeadNode headNodeArray[MaxNumber];//�����ڽӱ��ͷ�������

};
typedef struct Picture  Picture;

/*
	��pPictureָ���ͼ�ṹ��ͷ��������в���vertex��Ӧ���±�
*/
VertexLocate(Picture* pPicture, HeadNodeType vertex)
{

	for (int i = 0; i < pPicture->vextexNumber; i++)
		if (pPicture->headNodeArray[i].data == vertex)
			return i;

}

/*
	��������������ʽ�洢�ṹ-�ڽӱ�
*/
void CreateUDPByList(Picture* pPicture)
{

	//1.ȷ���������Ķ�������ͱ���

	printf("��������Ҫ����������ͼ�Ķ�������");
	scanf("%d", &(pPicture->vextexNumber));

	printf("��������Ҫ����������ͼ�ı�����");
	scanf("%d", &(pPicture->edgeNumber));

	//2.����ͷ�������
	for (int i = 0; i < pPicture->vextexNumber; i++) 
	{

		while (getchar() != '\n');//���ϴ����������ֵ���˵�

		printf("�������%d����������ݣ�", i + 1);
		scanf("%c", &pPicture->headNodeArray[i].data);//��ʼ��ͷ������������
		pPicture->headNodeArray[i].firstEdge = NULL;//��ͷ���ı�ָ�����ÿ�

	}

	HeadNodeType vertex1='0', vertex2='0';
	int j = 0,k=0;
	weigh  weighTemp = 0;
	EdgeNode* temp = NULL;

	//3.�����ڽӱ�
	for (int i = 0; i < pPicture->edgeNumber; i++)
	{

		while (getchar() != '\n');//���ϴ����������ֵ���˵�

		//4.����ߵ���������Ȩֵ

		printf("�������һ���߹����Ķ��㼴��Ӧ��Ȩֵ(��#����):");//��a#b#20
		scanf("%c#%c#%d", &vertex1, &vertex2, &weighTemp);

		//�ҳ�vertex1��vertex2��ͷ��������ж�Ӧ���±�
		j = VertexLocate(pPicture, vertex1);
		k = VertexLocate(pPicture, vertex2);

		//5.��������Ľ���Ȩ�������(�൱�ڹ���� j - k )

		temp = (EdgeNode*)malloc(sizeof(EdgeNode));//�½�һ������
		temp->VertexIndex = j;//�ñ������Ӧ��ͷ�����ɵıߵ���һ��ͷ�����±�
		temp->info = weighTemp;//���ݸ���

		//6.ͷ�巨�������

		temp->nextEdge = pPicture->headNodeArray[k].firstEdge;
		pPicture->headNodeArray[k].firstEdge = temp;

		//7.�����( k - j )

		temp = (EdgeNode*)malloc(sizeof(EdgeNode));
		temp->VertexIndex = k;
		temp->info = weighTemp;

		temp->nextEdge = pPicture->headNodeArray[j].firstEdge;
		pPicture->headNodeArray[j].firstEdge = temp;

	}

	return;

}

/*
	��������ͼ���ڽӱ�
*/
void TraverPicture(Picture* pPicture)
{

	//����ͷ�������
	for (int i = 0; i < pPicture->vextexNumber; i++)
	{

		printf("%c ",pPicture->headNodeArray[i].data);

		EdgeNode* current=pPicture->headNodeArray[i].firstEdge;//������ɱ�������
		//����ÿ��ͷ�ڵ������Ӧ�ı���
		while (current!=NULL)
		{

			printf(" %cȨ:%d", pPicture->headNodeArray[current->VertexIndex].data, current->info);
			current = current->nextEdge;
		}

		printf("\n");

	}

}

/*****************************************		  ѭ�����ж���			*****************************************/

#define MAXSIZE 20//��ʾѭ�����е���󳤶�

typedef HeadNode QueueElementType;//����Ԫ�ص���������
struct Queue
{

	QueueElementType* base;//��ʼ���Ķ�̬����Ĵ洢�ռ�
	int front;//������е�ͷָ�룬ָ���ͷԪ��
	int rear;//������е�βָ��,ָ���β����һ��Ԫ��

}*pQueue;
typedef struct Queue Queue;

/*
	����һ���ն���,��������ָ��
*/
Queue* IniteQueue()
{

	Queue* pQueue = (Queue*)malloc(sizeof(Queue));

	//���г�ʼ��
	pQueue->base = (QueueElementType*)malloc(sizeof(QueueElementType)*MAXSIZE);//���ڴ�������Ķ���Ԫ��
	if (pQueue->base == NULL)
	{

		printf("����ռ�ʧ�ܣ��޷��������С�\n");
		return;

	}

	pQueue->front = pQueue->rear = 0;//�����ÿ�

	return pQueue;

}

/*
	�ж϶����Ƿ�Ϊ��
	��ʼ���������д���
*/
bool EmptyQueue(Queue* pQueue)
{

	if (pQueue->front == pQueue->rear)
		return true;

	return false;

}

/*
	���һ��Ԫ��
	��ʼ���������д����Ҷ��в�Ϊ��
*/
void EnQueue(Queue* pQueue, QueueElementType* headNode)
{

	//�ж��Ƿ����
	if ((pQueue->rear + 1) % MAXSIZE == pQueue->front)
	{

		printf("���ʧ�ܣ�����������\n");
		return;

	}

	//����Ԫ�ص���β
	pQueue->base[pQueue->rear] = *headNode;
	pQueue->rear = (pQueue->rear + 1) % MAXSIZE;//��βָ�����

	return;

}

/*
	����һ��Ԫ��,��Ԫ�صĵ�ַ���ظ�*headNode
	��ʼ���������д����Ҳ�Ϊ��
*/
void DeQueue(Queue* pQueue, QueueElementType** headNode)
{

	if (EmptyQueue(pQueue))
	{

		printf("����ʧ�ܣ����в����ڻ�Ϊ�ա�\n");
		return;

	}

	*headNode = &(pQueue->base[pQueue->front]);
	pQueue->front = (pQueue->front + 1) % MAXSIZE;//ͷָ�����

	return;

}

int  visted1[MaxNumber] = { 0 };//һ�������������ڱ���������Ľ���Ƿ񱻷��ʹ�

/*
	�ڽӱ�Ĺ�����ȱ���(��������ʵ��)(ͬ��������ֻ������ͨͼ�Ĺ�����ȱ���)
	����1����Ҫ���й�����ȱ�����ͼ
	����2�����й�����ȱ����ĳ�ʼ�����±�
*/
void BreadthFirstSearch(Picture* pPicture,int firstIndex)
{

	//����һ������
	Queue* queue = IniteQueue();
	//����Ҫ�����ĵ�һ��������
	EnQueue(queue, &(pPicture->headNodeArray[firstIndex]));

	visted1[firstIndex] = 1;//��ͷ����������±�ΪfirstIndex�����Ϊ���ʹ�

	printf("�����˽��:%c.\n",pPicture->headNodeArray[firstIndex].data);//���ʳ�ʼ���

	HeadNode* temp1;
	EdgeNode* temp2;

	while (!EmptyQueue(queue))//������в�Ϊ��
	{

		DeQueue(queue, &temp1);//��ͷԪ�س��Ӳ���ֵ��temp1

		//�Գ��ӵ�Ԫ�ؽ����й�ȱ���(�������Ӧ�����б�(��)���)
		temp2 = temp1->firstEdge;
		while (temp2!=NULL)
		{

			if (visted1[temp2->VertexIndex]==0)//�ñ���û�з��ʹ�����з���
			{

				printf("�����˽��:%c.\n", pPicture->headNodeArray[temp2->VertexIndex].data);//���ʵ�ǰ���ӽ��������ڽӵ�(�ڽӱ��еı�(��)���)
				visted1[temp2->VertexIndex] = 1;//���Ϊ���ʹ�
				EnQueue(queue, &(pPicture->headNodeArray[temp2->VertexIndex]));//���һ��Ԫ��(��ӵ��Ǳ߽��VertexIndex�±��Ӧ��ͷ���)

			}

			temp2 = temp2->nextEdge;//����������

		}

	}

}


int main()
{

	Picture picture;

	//�����ڽӱ�
	CreateUDPByList(&picture);

	////�����ڽӱ�
	//TraverPicture(&picture);

	BreadthFirstSearch(&picture, 0);

}