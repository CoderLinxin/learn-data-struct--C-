#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

/*****************************************			 ���Ŷ���				*****************************************/


#define ERROR -1


/*****************************************			ջ��㶨��				*****************************************/


//ע����ջͷָ����ֱ��ָ���׽���(û��ͷ���)
typedef int ListStackElementType;//������ջ����������������������
struct StackNode
{

	ListStackElementType data;//��ջ�ϵĽ��
	struct StackNode* pNext;//ָ����һ����ָ��

}*pStackTop;
typedef struct StackNode StackNode;


/*****************************************			 ��������			*****************************************/


StackNode* IniteChainStack();//��ʼ����ջ
void TravelChainStack(StackNode*);//������ջ
int ChainStackLength(StackNode*);//��ȡ��ջ�ĳ���
void PushChainStack(StackNode**,ListStackElementType);//��ջ��ջһ��Ԫ��
void PopChainStack(StackNode**);//��ջ��ջһ��Ԫ��
bool ChainStackEmpty(StackNode*);//�ж���ջ�Ƿ�Ϊ��
ListStackElementType GetChainStackTop(StackNode*);//ȡջ��Ԫ��

/*****************************************			 ��������			*****************************************/


/*
	��ʼ����ջ
*/
StackNode* IniteChainStack()
{

	StackNode* pStackTop = NULL;//����һ����ջ��ջ��ָ���ÿ�
	return pStackTop;
	
}

/*
	������ջ
*/
void TravelChainStack(StackNode* pStackTop)
{

	if (ChainStackEmpty(pStackTop))
	{

		printf("��ջΪ�գ�����ʧ��");
		return ERROR;

	}

	int current = 1;//���ڼ���
	while (pStackTop !=NULL)
	{

		printf("��ջ��%d��Ԫ��Ϊ��%d��\n",current,pStackTop->data);
		current++;
		pStackTop = pStackTop->pNext;//������

	}


}

/*
	��ȡ��ջ�ĳ���
*/
int ChainStackLength(StackNode* pStackTop)
{

	
	if (ChainStackEmpty(pStackTop))//�ж��Ƿ�Ϊ��ջ
		return 0;

	int length = 0;
	while (pStackTop)
	{

		length++;
		pStackTop = pStackTop->pNext;//������

	}

	return length;

}

/*
	��ջ��ջһ��Ԫ��
*/
void PushChainStack(StackNode** pStackTop,ListStackElementType data)
{

	//����һ���½��
	StackNode* stackNode = (StackNode*)malloc(sizeof(StackNode));
	stackNode->data = data;

	stackNode->pNext = *pStackTop;//�½��ָ��pStackTopָ��Ľ��
	*pStackTop = stackNode;//����ͷָ��

	return;

}

/*
	��ջ��ջһ��Ԫ��
	��ʼ��������ջ��Ϊ��
*/
void PopChainStack(StackNode** pStackTop)
{

	if (ChainStackEmpty(*pStackTop))
	{

		printf("��ջΪ�գ���ջʧ�ܡ�\n");
		return ERROR;

	}

	StackNode* temp = *pStackTop;//��ʱ����ָ����Ҫ��ɾ�����׽��
	*pStackTop = (*pStackTop)->pNext;//����ͷָ��
	free(temp);//�ͷű�ɾ���Ľ��

	return;

}

/*
	�ж���ջ�Ƿ�Ϊ��
*/
bool ChainStackEmpty(StackNode* pStackTop)
{

	if (pStackTop == NULL)
		return true;

	return false;

}

/*
	ȡջ��Ԫ��
	��ʼ������ջ��Ϊ��
*/
GetChainStackTop(StackNode* pStackTop)
{

	if (ChainStackEmpty(pStackTop))
	{

		printf("��ջΪ�գ�ȡջ��Ԫ��ʧ�ܡ�\n");
		return ERROR;

	}

	return pStackTop->data;

}


int main()
{

	//��ʼ����ջ
	pStackTop = IniteChainStack();
	PushChainStack(&pStackTop, 20);
	PushChainStack(&pStackTop, 50);
	PushChainStack(&pStackTop, 100);

	//��ջһ��Ԫ��
	PopChainStack(&pStackTop);

	printf("��ջ��ǰ����Ϊ��%d��\n", ChainStackLength(pStackTop));

	//ȡջ��Ԫ��
	printf("ջ��Ԫ�أ�%d��\n", GetChainStackTop(pStackTop));;

	//������ջ
	TravelChainStack(pStackTop);

}