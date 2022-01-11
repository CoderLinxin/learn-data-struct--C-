#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>


/*****************************************			���Ŷ���				*****************************************/ 


#define ERROR -1//�������һ���������


/*****************************************			 ���ж���			*****************************************/


typedef int QNodeElementType;//����Ԫ����������
struct QueueNode//���н��
{

	QNodeElementType data;//������
	struct QueueNode* pNext;//ָ����

};
typedef struct QueueNode QueueNode;

typedef struct
{

	QueueNode* front;//��ͷָ�룬ָ��ͷ���
	QueueNode* rear;//��βָ�룬ָ��β���

}QueuePoint;


/*****************************************			 ��������			*****************************************/


QueuePoint IniteListQueue();//���ӳ�ʼ��
void TraverListQueue(QueuePoint);//�������ӽ��
QNodeElementType ListQueueTopElement(QueuePoint);//ȡ��ͷԪ��(�׽��������)
void EnListQueue(QueuePoint,QNodeElementType);//�������
void DeListQueue(QueuePoint);//���ӳ���
void DestroyListQueue(QueuePoint);//��������
void ClearListQueue(QueuePoint);//�����ÿ�
bool EmptyListQueue(QueuePoint);//�ж������Ƿ�Ϊ��
bool ExistListQueue(QueuePoint);//�ж������Ƿ����
int ListQueueLength(QueuePoint);//�����ӳ���


/*****************************************			 ��������			*****************************************/


/*
	���ӳ�ʼ��
*/
QueuePoint IniteListQueue()
{

	QueuePoint pQueue = {NULL,NULL};

	//��ʼ������ָ��
	pQueue.front = pQueue.rear = (QueueNode*)malloc(sizeof(QueueNode));

	if (pQueue.front == NULL)
	{

		printf("����ռ�ʧ�ܣ����г�ʼ��ʧ�ܡ�\n");
		return ;

	}

	pQueue.front->pNext = NULL;//��ͷ���nextָ���ÿ�

	return pQueue;

}

/*
	�������ӽ��
	��ʼ���������Ӵ����Ҳ�Ϊ��
*/
void TraverListQueue(QueuePoint pQueue)
{

	if (EmptyListQueue(pQueue))
	{

		printf("��������ʧ�ܣ����Ӳ����ڻ�Ϊ�ա�\n");
		return ERROR;

	}

	int count = 1;//���ڼ���
	QueueNode* head = pQueue.front->pNext;//������ɱ�������ʼָ���׽��
	while (head !=NULL)
	{

		printf("���ӵĵ�%d��Ԫ��Ϊ��%d��\n",count, head->data);
		count++;
		head = head->pNext;//������

	}

	return;
}

/*
	ȡ��ͷԪ��(�׽��������)
	��ʼ���������Ӵ����Ҳ�Ϊ��
*/
QNodeElementType ListQueueTopElement(QueuePoint pQueue)
{

	if (EmptyListQueue(pQueue)||!ExistListQueue(pQueue))
	{

		printf("ȡ��ͷԪ��ʧ�ܣ�����Ϊ�ջ򲻴��ڡ�\n");
		return ERROR;

	}

	return pQueue.front->pNext->data;

}

/*
	�������һ��Ԫ��(������Ҫ�ı�rear��ָ��������Ҫ�������ָ��)
	��ʼ���������Ӵ���
*/
void EnListQueue(QueuePoint* pQueue, QNodeElementType data)
{

	if (!ExistListQueue(*pQueue))
	{

		printf("���Ӳ����ڣ����ʧ�ܡ�\n");
		return ERROR;

	}

	//�����½��
	QueueNode* p = (QueueNode*)malloc(sizeof(QueueNode));
	p->data = data;

	p->pNext = NULL;
	pQueue->rear->pNext = p;//�½�����β������
	pQueue->rear = p;//����β���

	return;

}

/*
	���ӳ���һ��Ԫ��(���ڿ�����Ҫ�ı�rear��ָ��������Ҫ�������ָ��)
	��ʼ����������ǿ�
*/
void DeListQueue(QueuePoint* pQueue)
{

	if (EmptyListQueue(*pQueue))
	{

		printf("���ӳ���ʧ�ܣ��նӻ�Ӳ����ڡ�\n");
		return ERROR;

	}

	//����������>1����ʱ���Ӳ���Ҫ�޸�rearָ��

	QueueNode* p = pQueue->front->pNext;//���ڼ�¼��ɾ���ĵ�ǰ�׽��
	pQueue->front->pNext = p->pNext;//�����׽��

	//��������=1ʱ��ɾ��һ����㣬rearָ���β��㱻�ͷ�,��ʱ��Ϊ�գ���Ҫ����rearָ��
	if (pQueue->rear == p)//���豻ɾ������β���
		pQueue->rear = pQueue->front;//�������ÿ�

	free(p);//�ͷű�ɾ����ǰ�׽��
	
	return;


}

/*
	��������
*/
void DestroyListQueue(QueuePoint* pQueue)
{

	QueueNode* p;//���ڼ�¼��ɾ�����

	while (pQueue->front)//�������ͷָ�뱻�ÿ�
	{

		p = pQueue->front;
		pQueue->front = pQueue->front->pNext;//������
		free(p);


	}

	pQueue->rear = NULL;//βָ���ÿ�

	return;

}

/*
	�����ÿ�
	��ʼ���������Ӵ���,������Ҫ�ı�front��rear������Ҫ����pQueue�ĵ�ַ
*/
void ClearListQueue(QueuePoint* pQueue)
{

	if (!ExistListQueue(*pQueue))
		return ERROR;
	
	QueueNode* p= pQueue->front->pNext;//������ɱ���
	pQueue->rear = p;//���ڰ����ͷſռ�
	while (p)
	{

		p = p->pNext;//������
		free(pQueue->rear);//�ͷŽ��
		pQueue->rear = p;

	}

	pQueue->rear = pQueue->front;//βָ��ָ��ͷ���

	return;

}

/*
	�ж������Ƿ�Ϊ��
	��ʼ���������Ӵ���
*/
bool EmptyListQueue(QueuePoint pQueue)
{

	if (!ExistListQueue(pQueue))
		return ERROR;

	if (pQueue.front == pQueue.rear)
		return true;

	return false;

}

/*
	�ж������Ƿ����
*/
bool ExistListQueue(QueuePoint pQueue)
{

	if (pQueue.front != NULL)
		return true;

	return false;

}

/*
	�����ӳ���
	��ʼ���������Ӵ���
*/
int ListQueueLength(QueuePoint pQueue)
{

	if(!ExistListQueue(pQueue))
		return ERROR;

	QueueNode* current = pQueue.front->pNext;//������ɱ�������ʼָ���׽��
	int count = 0;//���ڼ���

	while (current)
	{

		count++;
		current = current->pNext;//������

	}

	return count;

}


//int main()
//{
//
//	//��ʼ������
//	QueuePoint pQueue = IniteListQueue();
//
//	//��������
//	//DestroyListQueue(&pQueue);
//
//	//�������
//	EnListQueue(&pQueue, 20);
//	EnListQueue(&pQueue, 60);
//	EnListQueue(&pQueue, 70);
//
//	//���ӳ���
//	DeListQueue(&pQueue);
//	//DeListQueue(&pQueue);
//
//	printf("���ӳ���Ϊ��%d��\n", ListQueueLength(pQueue));
//
//	//ȡ��ͷԪ��
//	printf("��ͷԪ��Ϊ��%d\n", ListQueueTopElement(pQueue));
//
//	//��ն���
//	//ClearListQueue(&pQueue);
//
//	//���ٶ���
//	//DestroyListQueue(&pQueue);
//
//	//��������
//	TraverListQueue(pQueue);
//
//}