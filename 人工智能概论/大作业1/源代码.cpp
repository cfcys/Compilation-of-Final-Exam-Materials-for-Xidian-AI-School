/*
老师好：
在写代码中遇到了一些问题，导致OPEN表与CLOSＥＤ的名称混了

#include<iostream>
#include<queue>
#include<map>
#include<stack>
using namespace std;

map<int, int>vis;
map<int, int>step;
map<int, int>id;
map<int, int>parent;
queue<int>open;
queue<int>close;
queue<int>nclose;
stack<int>out;
int m, n;
int dir[4][2] = { 0,-1,-1,0,0,1,1,0 };    

int change(int**p)   
{
	int s = 0;
	for(int i=0;i<m;i++)
		for (int j = 0; j < n; j++)
			s = s * 10 + p[i][j];
	return s;
}

void getid(int a,int b)      //！！获取与目标状态不同的格子数//h函数，
{
	int c;
	c = a;
	for (int i = 0; i < m * m; i++)
	{
		if ((a % 10) != (b % 10))
			id[c]++;
		a = a / 10, b = b / 10;
	}
}

int A (int u,int v)      //启发式搜索
/*
循环一下步骤
1.取出CLOSED表中第一个元素（u），作为可扩展状态
2.计算该状态的每个可扩展状态的h（n），将这些可扩展状态放入open表中//h(n)的计算方式是与目标不同的格子数
3.找到OPEN表中全局f（n）(f(n)=g(n)+h(n))最小的元素，放入CLOSED表中

有以下注意的：
当CLOSED中的第一个元素==目标状态时，停止搜索，返回f(n)(==g(n))
当OPEN表中为空时，停止循环，返回-1，表示无结果
会对每一个放入CLOSED中的元素进行标记，在以下搜索中若遇到已被标记的状态不进行搜索
*/
{
	open.push(u);    
	vis[u] = 1;     
	getid(u, v);      
	while (open.size())    
	{
		int q, p, w, x, y, newx, newy, size;
		if (open.front() == v)     //找到目标状态
			return step[v];
		size = open.size();
		for(int i=0;i<size;i++)     //找出该层数中，最小的id值
		{
			int** r;
			w=q=open.front();    //取CLOSED表中第一个元素，该元素是上一步搜索的f（n）最小的元素。进行扩展
			open.pop();
			r = new int* [n];
			for (int i = 0; i < n; i++)
				r[i] = new int[m];
			for (int i = m - 1; i >= 0; i--)    
				for (int j = n - 1; j >= 0; j--)
				{
					r[i][j] = q % 10, q = q / 10;
					if (r[i][j] == 0)//0代表空格，在该步骤显示
					{
						x = i, y = j;       
					}
				}
			for (int i = 0; i < 4; i++)     //~~扩展
			{
				newx = x + dir[i][0], newy = y + dir[i][1];
				if (newx >= 0 && newx < m && newy >= 0 && newy < n)    //若该位置可交换
				{
					r[x][y] = r[newx][newy];     //交换空白格位置
					r[newx][newy] = 0;
					p = change(r);
					if (!vis[p])     //该状态没有被访问过%%%%%%访问过的不放入
					{
						close.push(p);      //把该状态放进open表
						nclose.push(p);
						vis[p] = 1;
						step[p] = step[w] + 1;     //层数(g(n))在原来状态上加一
						parent[p] = w;     //标记父状态
						getid(p, v);
					}
					r[newx][newy] = r[x][y];     //变回原来状态
					r[x][y] = 0;
				}
			}
		}
		if (close.size())    //若open表不为空
		{
			int csize = close.size(), min;
			min = id[nclose.front()];
			for (int i = 0; i < csize; i++)      //找出open表中f（n)的最小值
				if (id[nclose.front()] < min)
				{
					min = id[nclose.front()];
					nclose.pop();
				}
				else nclose.pop();
			for (int i = 0; i < csize; i++)      //把open表中f(n)最小值的状态放进CLOSED表中
				if (id[close.front()] == min)
				{
					open.push(close.front());
					close.pop();
				}
				else close.pop();
		}
	}
	return -1;
}

int main()
{
	cout << "A搜索" << endl;
	int u, v, t;
	int** mau, ** mav;
	cout << "输入m*n：" << endl;
	cin >> m >> n;
	mau = new int* [n], mav = new int* [n];
	for (int i = 0; i < n; i++)
		mau[i] = new int[m], mav[i] = new int[m];
	cout << "输入初始状态：" << endl;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			cin >> mau[i][j];
	cout << "输入最终状态：" << endl;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			cin >> mav[i][j];
	u = change(mau), v = change(mav);
	if (A(u, v) != -1)
	{
		cout << "到达目标状态需要 " << A(u, v) << " 步" << endl;//!!A是需要多少步A*=g(n)+h(n)
		t = v;
		while (t)
		{
			out.push(t);
			t = parent[t];
		}
		while (out.size())    //输出到达目标状态的过程
		{
			int** o;
			t = out.top();
			out.pop();
			o = new int* [n];
			for (int i = 0; i < n; i++)
				o[i] = new int[m];
			for (int i = m - 1; i >= 0; i--)
				for (int j = n - 1; j >= 0; j--)
					o[i][j] = t % 10, t /= 10;
			for (int i = 0; i < m; i++)
			{
				for (int j = 0; j < n; j++)
					cout << o[i][j] << " ";
				cout << endl;
			}
			cout << "======" << endl;
		}

	}
	else cout << "无解" << endl;
}

