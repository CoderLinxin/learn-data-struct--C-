// 并查集.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

//表示并查集中的一个元素
struct UnionSearch
{

	int parent;//代表当前元素父元素的下标
	int data;//数据域

};

UnionSearch unionSearch[10];

/*
	初始化一个并查集森林(所有元素都看成一个集合,维护着自己的根结点(即自身))
*/
void init()
{

	for (int i = 0; i < 10; i++)
		unionSearch[i].parent = i;//将结点的父节点设置为自己

}

/*
	确定元素属于哪一个子集
	查找集合中下标为x的元素的根结点
*/
int find(int x)
{

	if (unionSearch[x].parent == x) return x;//根结点的双亲结点为自身

	return  unionSearch[x].parent= find(unionSearch[x].parent);//当前结点非根结点则继续向上查找(查找时可以把当前结点的父节点设置为父节点的父节点(路径压缩))

}

/*
	判断并查集中(森林)下标为x,y的元素是否在同一集合内,只需要判断x,y所属集合的根结点是否相同即可
*/
bool comp(int x,int y)
{

	return find(x) == find(y);

}

/*
	合并并查集(森林)中下标为x,y的两个元素所在的两个集合(即把一个集合的根结点设置成另一个集合根结点的父节点即可)
*/
bool merge(int x,int y)
{

	if (find(x) == find(y)) return false;//x,y同属于一个集合则合并失败

	//将下标为x的元素所在集合的根结点设置为下标为y的元素所在集合的根结点
	unionSearch[find(x)].parent = find(y);

	return;

}

int main()
{

	init();
	merge(0, 1);
	merge(1, 2);
	merge(2, 3);
	merge(3, 4);

	find(0);

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
