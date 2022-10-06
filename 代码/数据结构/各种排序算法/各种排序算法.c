// 各种排序算法.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
//#include "直接插入排序.c"

#define	 MAXSIZE 20//记录的最大个数

typedef int KeyType;//关键字的数据类型
typedef int InfoType;//记录的除关键字外其他数项的数据类型

//定义每条记录的结构(包含多个关键字)
typedef struct 
{

	KeyType key;//记录的关键字
	InfoType otherInfo;//记录的其他数据项

}Record;

//定义顺序表的结构(包含多条记录)
typedef struct 
{

	Record records[MAXSIZE + 1];//定义一个最大长度的顺序表(能够最多存放 MAXSIZE + 1条记录),records[0]可以设置哨兵
	int length;//标记当前顺序表的长度

}List;

/*
	堆调整(已知R[s..m]中记录的关键字除R[s]之外均满足堆的定义,调整R[s]的关键字，使R[s..m成为一个大根堆])
	大根堆：根结点的值大于其孩子结点的值
*/
void HeapAdjust(List* pList,int root,int rear )
{

	int i;
	Record rootValue = pList->records[root];//记录当前待调整的堆的根结点的值
	for ( i = 2* root; i <= rear; i*=2)
	{

		//筛选i的孩子结点中较大的孩子结点
		if (i < rear&&pList->records[i].key < pList->records[i + 1].key)//即右孩子结点较大
			i++;//i指向右孩子结点

		//如果i比i的孩子结点中较大的孩子结点还大或者等于则i仍然作为根结点,并且应该第一轮就结束循环(因为第一轮for循环rootVlue就是整棵树的根结点(并且该算法只是在根结点不满足堆定义的前提下运算的，根结点满足堆定义那么该算法就不需要进行下去了))
		if (rootValue.key >= pList->records[i].key)//这里改成pList->records[root].key >= pList->records[i].key会出错,因为在本程序中我们只是做了单向交换而已,没有把父节点的值赋值给孩子结点而是存储在rootValue中
			break;

		//注意这里只是作了单向交换，只是孩子结点提到根结点，而根结点没有下放到孩子结点，即原来的孩子结点仍然不变(可以看成空(待赋值))
		//当执行下面root = i ,此时root对应的仍然是上一轮孩子i的结点(而不是一开始的根结点),因为我们实际上只需要在确定好根结点的最终位置后再进行根结点的赋值即可
		pList->records[root] = pList->records[i];//将较大的孩子结点赋值给根结点
		root = i;//向下进行调整

	}

	pList->records[root] = rootValue;//将一开始保留的rootValue插入正确位置(叶子结点)

}

/*
	堆排序
*/
void HeapSort(List* pList)
{

	int i;
	Record temp;

	//建立初始堆
	for ( i = pList->length/2; i >=1; i--)
		//进行堆调整,从pList->length/2即第一个非叶子结点处开始从右到左，从下到上调整,每次都是调整以i为根结点的子堆(经过每次调整子堆依次扩大),当i=1即作为根结点时,即调整完整颗树,即建立堆完成
		HeapAdjust(pList,i,pList->length);//每次调整，i不断向上移动

	for ( i = pList->length; i >1; i--)//有pList->length个元素，进行pList->length-1趟排序
	{

		//输出有序堆的根结点,这里我们把每次输出的根结点从数组最后一个位置开始放入,然后把每次进行堆排序的堆的最后一个元素放在根结点位置上,这样从低下标遍历到高下标处的序列为升序
		temp = pList->records[1];
		pList->records[1] =  pList->records[i];
		pList->records[i] =  temp;

		//将剩下的不标准子堆重新调整标准堆
		HeapAdjust(pList, 1, i - 1);

	}

}

int increments[] = {7,3,1};//增量序列采用2^(i)-1
int length = sizeof(increments) / sizeof(increments[0]);

/*
	简单选择排序(升序)
*/
void SimpleSelectSort(List* pList)
{

	int i,j,temp;
	for (i = 1; i <= pList->length - 1; i++)//同样类似于冒泡排序,有length个元素需要length-1趟选择排序
	{

		temp = i;//记录当前正在比较元素的最小元素的下标(默认为当前元素怒)
		for (j = i + 1; j <= pList->length; j++)//j = i+1 因为当前元素为i 只需要从i+1起比较
			if (pList->records[j].key < pList->records[temp].key)
				temp = j;//最小元素的下标更新

		//交换元素
		if (temp != i)
		{

			//最小元素位置确定,需要将目标位置上的元素放在最小元素原来的位置以便放置最小元素
			pList->records[0] = pList->records[i];
			pList->records[i] = pList->records[temp];
			pList->records[temp] = pList->records[0];

		}

	}

}

/*
	进行一趟快速排序
	返回所选定枢轴最终坐落的下标
*/
int Partition(List* pList, int low, int high)
{

	pList->records[0] = pList->records[low];//选取顺序表第一个结点作为枢轴并临时存储在0号结点处

	//确定枢轴的最终坐落位置

	while (low < high)
	{

		//由于选取的第一个(low)元素作为枢轴并且存储在0号下标处,因此low处的位置处于空闲,因此从high处开始查看是否有小于选取的元素的结点可以交换到low处
		while (low < high && pList->records[high].key > pList->records[0].key)
			high--;
		pList->records[low] = pList->records[high];

		//上面语句执行完成证明high处的元素已经搬到low处,因此此时high处的位置处于空闲,可以从low处查看是否有元素需要搬到high处的空闲位置上
		while (low < high && pList->records[low].key < pList->records[0].key)
			low++;
		pList->records[high] = pList->records[low];

	}

	//快速排序结束，将枢轴的元素放到正确位置上(此时high == low)
	pList->records[low] = pList->records[0];

	return low;//返回枢轴所处位置的下标

}

/*
	快速排序(升序)
	第一个参数:待排序的顺序表
	第二个参数:进行快速排序的顺序表的起始结点的下标
	第三个参数:进行快速排序的顺序表的末尾结点的下标
*/
void QuickSort(List* pList, int low, int high)
{

	int pivotLocate;

	if (low < high)//当low == high 证明待排序顺序表只有一个元素,则证明已经有序.快速排序结束
	{

		pivotLocate = Partition(pList, low, high);//进行快速排序并且记录枢轴的下标

		//以枢轴为中点分别对左右子表进行快速排序

		QuickSort(pList, pivotLocate + 1, high);//对右子表进行快速排序
		QuickSort(pList, low, pivotLocate - 1);//对左子表进行快速排序

	}

}

/*
	冒泡排序(升序)
*/
void BubbleSort(List* pList)
{

	int i, j, flag=1;//flag用来标记某一趟冒泡排序是否交换了元素,如果没有交换元素则标记为0(否则标记为1),并且说明前面的数据都已经是有序的了可以提前结束算法

	Record temp;

	for ( i = 1; i <= pList->length-1 && flag ==1; i++)//有length个元素需要进行length-1趟冒泡排序
	{

		//每趟冒泡排序确定一个最终位置,每趟冒泡排序比较次数依次递减
		for ( j = 1; j <= pList->length - i; j++)
		{

			flag = 0;//假设本趟排序没有交换元素
			if (pList->records[j].key > pList->records[j + 1].key)
			{

				temp = pList->records[j];
				pList->records[j] = pList->records[j + 1];
				pList->records[j + 1] = temp;
				flag = 1;//falg标记为1,表明序列仍不是有序,下趟冒泡排序仍需继续

			}

		}

	}

}

/*
	按一定增量元素间隔对元素进行插入排序
	第一个参数：待排序的顺序表
	第二个参数：每个排序元素之间的间隔(偏移量)
*/
void ShellInsert(List* pList,int offset)
{

	//对*pList中的元素进行直接插入排序,所有间隔为offset元素组成一个子序列
	int i,j;
	for ( i = offset+1; i <= pList->length; i++)//i也从offset+1(即相当于第二个元素需要排序)起开始对所有间隔为offset的元素组成的子序列进行排序(i也可以从1开始,这样结束标志就是i + offset <= pList->length)
	{

		//之所以i每次++是因为我们需要让所有间隔为offset的序列整体有序,当i == pList->length排序后,整个以offset为间隔的子序列就是有序的(因为该子序列的最后一个元素分布在接近pList->length处),每当i增加offset个单位时就相当于排序的每个子序列的有序元素加1
		//注意使得i增加到pList->length是有必要的

		if (pList->records[i].key < pList->records[i - offset].key)
		{

			pList->records[0] = pList->records[i];//设置哨兵

			//j设为当前比较元素的前一个元素,当前待排序元素需要和其所在的间隔为offset的序列中的所有有序元素进行比较,所以j需要 -=offset 且 > 0 
			for (j = i - offset; j > 0 && pList->records[0].key < pList->records[j].key; j -= offset)
				pList->records[j + offset] = pList->records[j];

			pList->records[j + offset] = pList->records[0];

		}

	}

}

/*
	希尔排序(升序)
	第一个参数：待排序的顺序表
	第二个参数：用于分隔顺序表的增量序列
	第三个参数：增量序列的长度
*/
void ShellSort(List* pList, int increments[], int length)
{

	//按增量序列(increments[0],increments[length-1])对*pList进行希尔排序
	int i;
	for (i = 0; i < length; i++)
		ShellInsert(pList, increments[i]);//对*pList作一趟增量为increments[i]的直接插入排序

}

/*
	直接插入排序(升序)
*/
void InsertSort(List* pList)
{

	int i, j;

	for (i = 2; i <= pList->length; i++)//从第二个元素开始需要进行比较判断是否需要移动(第0个元素设置哨兵，第一个元素不用移动)
	{

		if (pList->records[i].key < pList->records[i - 1].key)//当前位置上的元素比前一个元素小时,前一个元素后移(设置哨兵也是为了防止元素后移导致覆盖了元素)
		{

			pList->records[0] = pList->records[i];//设置哨兵

			for (j = i - 1; pList->records[0].key < pList->records[j].key; j--)
				pList->records[j + 1] = pList->records[j];//比目标元素大的元素都后移

			pList->records[j + 1] = pList->records[0];//插入元素

		}

	}

}

/*
	折半插入排序(升序)
*/
void HalfInsertSort(List* pList)
{

	int i,j,low,high,mid;
	for ( i = 2; i < pList->length; i++)//从第二个元素开始需要排序(设待排序元素为无序表的第一个元素)
	{

		pList->records[0] = pList->records[i];//设置哨兵,这里哨兵的作用仅仅为了防止后面后移元素覆盖掉待排序元素而保留的副本
		low = 1;//有序表的第一个元素的下标
		high = i-1;//有序表的最后一个元素的下标

		//if(pList->records[0].key< pList->records[i-1].key)//这里可以加上该语句判断元素是否已经处于正确位置上(可以提升性能),false则本次for循环后的语句都不用执行
			
		while (low <= high)
		{

			mid = (low + high) / 2;
			if (pList->records[mid].key > pList->records[0].key)//二分查找逐渐缩小隔离区间
				high = mid - 1;
			else
				low = mid + 1;

		}

		//在high+1处插入元素/在low处插入元素(画图看即可)
		
		//high+1处及其后面的元素都后移
		for ( j =i-1; j>=high+1; j--)
			pList->records[j + 1] = pList->records[j];

		pList->records[high + 1] = pList->records[0];//待排序的无序表的元素插入有序表的正确位置

	}

	return;

}

int main()
{

	List list;
	list.records[1].key = 15;
	list.records[2].key = 5;
	list.records[3].key = 35;
	list.records[4].key = -2;
	list.records[5].key = 50;
	list.records[6].key = 20;
	list.records[7].key = 100;
	list.records[8].key = 660;
	list.records[9].key = -25;
	list.records[10].key = -70;
	list.length = 10;

	//InsertSort(&list);//直接插入排序
	//HalfInsertSort(&list);//二分插入排序
	//ShellSort(&list, increments, length);//希尔排序
	//BubbleSort(&list);//冒泡排序
	QuickSort(&list, 1, 10);//快速排序
	//SimpleSelectSort(&list);
	//HeapSort(&list);//堆排序

	for (int i = 1;i <= list.length;i++)
		printf("%d ", list.records[i].key);
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
