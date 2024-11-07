#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>


/*****************************************			符号定义				*****************************************/


#define MAXSIZE 20 //定义栈的最大元素个数
#define ERROR -1//用来标记一个错误操作


/*****************************************		链式二叉树结点定义		*****************************************/


//目标树的前序遍历结果：
char str1[]="ab.cg...de..f..";//用于树的遍历结果
int index1 = 0;//指针偏移

////目标树的中序遍历结果
//char str2[]=".b.g.c.a.e.d.f.";//用于树的遍历结果
//int index2 = 0;//指针偏移：
//
////目标树的后序遍历结果：
//char str3[]="...g.cb..e..fda";//用于树的遍历结果
//int index3 = 0;//指针偏移

typedef char TreeElementType;//二叉树结点数据类型
struct TreeNode
{

	TreeElementType data;//树结点的数据域
	struct TreeNode* pLeft;//指向该结点的左子结点
	struct TreeNode* pRight;//指向该结点的右子结点

}*pRoot;
typedef struct TreeNode TreeNode;


/*****************************************			 方法声明			*****************************************/


TreeNode* PreCreateBinaryTree(TreeNode**);//递归创建二叉树(前序)

void InOrderTraverUnRecursion(TreeNode*);//栈实现二叉树中序遍历(非递归),假设是后序和前序与该算法思想完全不同(暂时不考虑)

void PreOrderTraver(TreeNode*);//二叉树前序遍历(递归实现)
void InOrderTraver(TreeNode*);//二叉树中序遍历(递归实现)
void PostOrderTraver(TreeNode*);//二叉树后序遍历(递归实现)

void BinaryTreeLayerTraver(TreeNode*);//二叉树的层次遍历

void CopyTree(TreeNode*, TreeNode**);//复制二叉树(先序)
int TreeDepth(TreeNode*);//计算二叉树的深度(后序)
int TreeNodeCount(TreeNode*);//计算二叉树结点总数
int LeafNodeCount(TreeNode*);//计算二叉树叶子结点数


/*****************************************			 方法定义			*****************************************/


/*
	递归创建二叉树(前序),我们需要输入一颗树的扩展二叉树(即所有叶子结点必须都用空来表示)的前序遍历的结果,传入参数为构建的树的根节点的指针(因为要修改其指向所以传入二级指针)
*/
TreeNode* PreCreateBinaryTree(TreeNode** pRoot)
{

	//注意如果str1不是一颗扩展二叉树则无法成功创建树(会无限递归下去)

	TreeElementType data;
	data = str1[index1++];

	//此时如果接收后序和前序的字符串第一个字符必定为 '.' 则无法完成递归，所以前序后序创建树无意义
	if ( data == '.')//假设读取到字符为.即pRoot指针指向一个虚结点(即该结点不存在,但是用NULL表示)，此时相当于退出当前函数，返回上一层函数，即相当于左/右子树创建完毕，返回上一层继续创建左/右子树
		(*pRoot) = NULL;
	else
	{

		*pRoot = (TreeNode*)malloc(sizeof(TreeNode));//假设读取到其他字符则构建一个根结点,pRoot指向该结点

		if (!*pRoot)
			exit(0);//假设分配空间失败直接终止程序(而return只是退出该层函数无法终止递归)

		(*pRoot)->data = data;//结点数据域赋值
		PreCreateBinaryTree(&(*pRoot)->pLeft);//以上一步创建的根结点构建左子树
		PreCreateBinaryTree(&(*pRoot)->pRight);//以上一步创建的根结点构建右子树

	}

	return;

}

/*
	二叉树前序遍历(递归实现)
	初始条件：树存在
*/
void PreOrderTraver(TreeNode* pRoot)
{

	if (pRoot == NULL)
		return;

	printf("%c",pRoot->data);
	PreOrderTraver(pRoot->pLeft);
	PreOrderTraver(pRoot->pRight);

}

/*
	二叉树中序遍历(递归实现)
	初始条件：树存在
*/
void InOrderTraver(TreeNode* pRoot)
{

	if (pRoot == NULL)
		return;

	InOrderTraver(pRoot->pLeft);
	printf("%c", pRoot->data);
	InOrderTraver(pRoot->pRight);

}

/*
	二叉树中序遍历(递归实现)
	初始条件：树存在
*/
void PostOrderTraver(TreeNode* pRoot)
{

	if (pRoot == NULL)
		return;

	PostOrderTraver(pRoot->pLeft);
	PostOrderTraver(pRoot->pRight);
	printf("%c", pRoot->data);

}

/*
	复制二叉树(先序),结果返回给pNewRoot(所以需要二级指针)
	思路分析：
	假设最低限度的二叉树的复制,当二叉树只有一个根结点时,由于pRoot不为空,pNewRoot指向根结点,然后进行递归
	首先进行左子树的复制，将根结点的左子树作为递归调用的参数,由于其为空,因此传入的pNewRoot的左子树也指向空
	接着进行右子树的复制，将根结点的右子树作为递归调用的参数,由于其为空,因此传入的pNewRoot的右子树也指向空
	将根结点扩大到整棵树完成树的复制
*/
void CopyTree(TreeNode* pRoot, TreeNode** pNewRoot)
{

	if (pRoot == NULL)//假设根结点为空,则新树的根结点也赋值为空
	{

		*pNewRoot = NULL;
		return;

	}
	else
	{

		*pNewRoot = (TreeNode*)malloc(sizeof(TreeNode));//新树的根结点创建的一个新结点
		(*pNewRoot)->data = pRoot->data;//数据域复制
		CopyTree(pRoot->pLeft, &((*pNewRoot)->pLeft));//复制左子树
		CopyTree(pRoot->pRight, &((*pNewRoot)->pRight));//复制右子树

	}
		
	return;
}

/*
	计算二叉树的深度(先序)
	思路分析:
	作最低限度的递归,当二叉树只有一个根结点时,因为根结点不为空所以记为1(但是1是需要在遍历完左子树和右子树之后再一起返回的),继续遍历左右子树,由于左右子树为空,此时
	leftNode == rightNode == 0,因此返回左右子树深度其中的较大值加上1(根结点的深度)
	当根结点换成一颗树时同理
*/
int TreeDepth(TreeNode* pRoot)
{

	int leftNode = 0,rightNode =0,rootNode=0;//用来分别统计左右子树和根结点的深度

	if (pRoot == NULL)//假设根结点为空,则深度记作0
		return 0;
	else
	{

		rootNode = 1;
		leftNode = TreeDepth(pRoot->pLeft);//遍历左子树
		rightNode = TreeDepth(pRoot->pRight);//遍历右子树

		//返回左子树和右子树其中的最大深度加1(根结点)
		if (leftNode > rightNode)
			return leftNode + rootNode;
		else
			return rightNode + rootNode;

	}
	
}

/*
	计算二叉树结点总数(先序)
	作最低限度的递归,假设二叉树只有一个根结点,由于根结点不为空,因此声明一个变量rootCount = 1,否则rootCount = 0
	接着遍历左子树和右子树将他们的返回值分别记录在leftCount和leftCount中(由于左子树和右子树都为空,因此都记为0),最后返回三者之和.
	将根结点换成整颗树同理
*/
int TreeNodeCount(TreeNode* pRoot)
{

	int leftCount=0, rightCount =0,rootCount=0;//记录根结点和左子树,右子树的结点数


	if (pRoot == NULL)//根结点为空,直接返回rootCount
		return rootCount;
	else
	{

		rootCount = 1;//根结点不为空则记为1
		leftCount = TreeNodeCount(pRoot->pLeft);//遍历左子树并记录结点数
		rightCount = TreeNodeCount(pRoot->pRight);//遍历右子树并记录结点数
		
		return leftCount + rightCount + rootCount;//返回左子树右子树和根结点的结点数之和

	}


}

/*
	计算二叉树叶子结点数
	作最低限度的递归,假设二叉树只有根结点,由于根结点不为空,且其判断左子树和右子树不为空,计数器加1,接着遍历其左右子树将结果记录起来
	左右子树为空递归结束.返回的叶子结点数为1
	将根结点换成整棵树同理
*/
int LeafNodeCount(TreeNode* pRoot)
{

	int leaveCount = 0;
	if (pRoot == NULL)
		return leaveCount;

	if(pRoot->pLeft ==NULL && pRoot->pRight ==NULL)//根结点的左子树和右子树均为空则证明其为叶子结点
		leaveCount = 1;

	leaveCount += LeafNodeCount(pRoot->pLeft);//遍历左子树
	leaveCount += LeafNodeCount(pRoot->pRight);//遍历右子树

	return leaveCount;

}


/*****************************************			 栈定义				*****************************************/


typedef  TreeNode StackElementType;//定义栈元素的数据类型
struct Stack
{

	StackElementType* stackTop;//栈顶指针指向栈顶元素的后一个元素
	StackElementType* stackBase;//栈底指针指向栈底元素
	int stackSize;//用来标识一个栈的最大长度

}*pStack;
typedef struct Stack Stack;

Stack* IniteStack();//完成栈的初始化
void Push(Stack*, StackElementType);//压栈一个元素
StackElementType Pop(Stack*, StackElementType);//弹出一个元素

/*
	初始化栈，返回指向该栈的指针
*/
Stack* IniteStack()
{

	//创建一个栈结构
	Stack* pStack = (Stack*)malloc(sizeof(Stack));

	//栈底指针指向一个数组
	pStack->stackBase = (StackElementType*)malloc(sizeof(StackElementType)*MAXSIZE);

	if (pStack->stackBase == NULL)
	{

		printf("创建栈失败。\n");
		exit(0);

	}

	pStack->stackTop = pStack->stackBase;//表示空栈
	pStack->stackSize = MAXSIZE;

	return pStack;

}

/*	
	压栈一个元素
	初始条件：栈存在且栈未满
*/
void Push(Stack* pStack, StackElementType* pTreeNode)
{

	if (pStack->stackBase == NULL)
		return ERROR;

	if ((pStack->stackTop - pStack->stackBase) >= pStack->stackSize)
	{

		printf("栈已满，无法入栈。\n");
		return ERROR;

	}

	*pStack->stackTop = *pTreeNode;
	pStack->stackTop++;

	return;

}

/*
	出栈一个元素并返回给pTreeNode(因此需要二级指针)
	初始条件：栈存在且不为空
*/
StackElementType Pop(Stack* pStack, StackElementType** pTreeNode)
{

	if (pStack->stackBase == NULL)
		return;

	if (pStack->stackTop - pStack->stackBase ==0)
	{

		printf("当前栈为空，出栈失败。\n");
		return;

	}

	 *pTreeNode = (pStack->stackTop-1);

	pStack->stackTop--;

}


/*****************************************		  循环队列定义			*****************************************/


typedef TreeNode QueueElementType;//队列元素的数据类型
struct Queue
{

	QueueElementType* base;//初始化的动态分配的存储空间
	int front;//代表队列的头指针，指向队头元素
	int rear;//代表队列的尾指针,指向队尾的下一个元素

}*pQueue;
typedef struct Queue Queue;

/*
	构造一个空队列,并返回其指针
*/
Queue* IniteQueue()
{

	Queue* pQueue = (Queue*)malloc(sizeof(Queue));

	//队列初始化
	pQueue->base = (QueueElementType*)malloc(sizeof(QueueElementType)*MAXSIZE);//用于存放真正的队列元素
	if (pQueue->base == NULL)
	{

		printf("分配空间失败，无法创建队列。\n");
		return ERROR;

	}

	pQueue->front = pQueue->rear = 0;//队列置空

	return pQueue;

}

/*
	判断队列是否为空
	初始条件：队列存在
*/
bool EmptyQueue(Queue* pQueue)
{

	if (pQueue->front == pQueue->rear)
		return true;

	return false;

}

/*
	入队一个元素
	初始条件：队列存在且队列不为满
*/
void EnQueue(Queue* pQueue, QueueElementType* treeNode)
{

	//判断是否队满
	if ((pQueue->rear + 1) % MAXSIZE == pQueue->front)
	{

		printf("入队失败：队列已满。\n");
		return ERROR;

	}

	//插入元素到队尾
	pQueue->base[pQueue->rear] = *treeNode;
	pQueue->rear = (pQueue->rear + 1) % MAXSIZE;//队尾指针后移

	return;

}

/*
	出队一个元素,将元素的地址返回给*pTreeNode
	初始条件：队列存在且不为空
*/
void DeQueue(Queue* pQueue, QueueElementType** pTreeNode)
{

	if (EmptyQueue(pQueue))
	{

		printf("出队失败：队列不存在或为空。\n");
		return ERROR;

	}

	*pTreeNode = &(pQueue->base[pQueue->front]);
	pQueue->front = (pQueue->front + 1) % MAXSIZE;//头指针后移

	return;

}


/*****************************************		非递归实现中序遍历		*****************************************/


/*
	非递归实现二叉树中序遍历(先访问根节点，接着先序遍历左子树，然后先序遍历右子树)
	实现思路:
	while(栈中的结点全部出栈完毕 或 当前正在遍历的结点为空)
	{
		先将根结点入栈，接着一直将左子树的根结点入栈，当遇到左子树的根结点为空时，则出栈一个结点，
		并将遍历结点更新为该结点，接着一直将该结点的右子树入栈直到为空接着继续出栈一个结点，遍历结点更新为当前结点
	}
	由于整棵树的根节点是最先入栈的，等到其出栈后证明其他结点一定都出栈了，这样树就遍历完了
*/
void InOrderTraverUnRecursion(TreeNode* pRoot)
{

	Stack* pStack = IniteStack();//用于存储遍历时经过的结点

	TreeNode* temp = pRoot;//用于存储弹栈时所取出的栈顶结点

	while (pRoot || !(pStack->stackTop - pStack->stackBase == 0))//如果栈不为空或当前结点不为空
	{

		if (pRoot)//假设当前正在遍历的树根结点存在
		{

			Push(pStack, pRoot);//将根节点进栈
			pRoot = pRoot->pLeft;//继续遍历根节点的左子树

		}
		else
		{

			Pop(pStack, &temp);//表示遍历左/右子树完成,弹出该左右子树的根节点(这一步可以表示对结点进行的访问),这一步相当于二叉树的遍历算法中函数执行遇到NULL返回上一层调用的函数(实际上也就是相当于返回当前子树的根结点)
			printf("%c", temp->data);//访问结点
			pRoot = temp->pRight;//继续根据上一步弹出的根节点遍历该根结点的右子树

		}

	}


}


/*****************************************		 二叉树的层次遍历			*****************************************/


/*
	二叉树的层次遍历
	思路分析：
	由于队列是先进先出，我们先将根结点入队,然后判断队是否为空，不为空则出队一个结点，
	判断该结点有无左右孩子有则分别入队之后重复该过程直到队空
	由于这一过程根结点一定比孩子结点先入队因此比孩子结点先出队，这样保证了遍历过程从上到下
	由于左孩子结点比右孩子结点先入队，因此左孩子结点比右孩子结点先出队，这样保证了遍历过程从左到右
*/
void BinaryTreeLayerTraver(TreeNode* pRoot)
{

	Queue* pQueue = IniteQueue();
	EnQueue(pQueue, pRoot);//将根结点入队

	TreeNode* temp = pRoot;//用于存储出队时所取出的队头结点

	while (!EmptyQueue(pQueue))//假设队列不为空
	{

		DeQueue(pQueue, &temp);//出队一个结点
		printf("%c", temp->data);//访问该结点
		if (temp->pLeft != NULL)
			EnQueue(pQueue, temp->pLeft);//如果该结点的左孩子不为空则入队
		if (temp->pRight != NULL)
			EnQueue(pQueue, temp->pRight);//如果该结点的右孩子不为空则入队

	}

}


int main()
{

	//前序创建二叉树
	PreCreateBinaryTree(&pRoot);

	//前序遍历二叉树
	PreOrderTraver(pRoot);

	//中序遍历二叉树
	//InOrderTraver(pRoot);
	//printf("\n");

	//后序遍历二叉树
	//PostOrderTraver(pRoot);
	//printf("\n");

	//pStack = IniteStack();

	//Push(pStack, pRoot);
	//Push(pStack, pRoot);

	//char c = Pop(pStack, pRoot);

	//InOrderTraverUnRecursion(pRoot);
	//printf("\n");

	//Queue* pQueue = IniteQueue();

	//EnQueue(pQueue,pRoot);

	//EnQueue(pQueue,&pRoot);

	//BinaryTreeLayerTraver(pRoot);

	//复制二叉树
	//TreeNode* pNewRoot;
	//CopyTree(pRoot, &pNewRoot);
	//PreOrderTraver(pNewRoot);

	printf("二叉树的深度为：%d\n", TreeDepth(pRoot));

	printf("二叉树的结点总数为：%d\n", TreeNodeCount(pRoot));

	printf("二叉树的叶子结点数为：%d\n", LeafNodeCount(pRoot));


}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
