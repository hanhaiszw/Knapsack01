// Knapsack01.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
using namespace std;
#define BIT(n) (1<<n)   //位运算  1<<2 = 4
#pragma warning(disable:4996)
//小偷偷东西
void test01() {
	int v[5] = { 6,3,5,4,6 };//价值
	int h[5] = { 2,2,6,5,4 };//重量
	int c = 10;//最大容量
	unsigned char bit = 31;//二进制11111 分别代表5个宝贝 ，选中为1，未选中为0 共有2^5种    可能性
	int maxv = 0;//偷到宝贝的总价值

	//scanf("%d,%d,%d,%d,%d", &v[0], &v[1], &v[2], &v[3], &v[4]);
	//scanf("%d,%d,%d,%d,%d", &h[0], &h[1], &h[2], &h[3], &h[4]);
	//scanf("%d", &c);

	int N = 5;
	//循环32次  i要从 00000 到 11111，  其中如何一种5位的01组合都能遍历到
	//  & 运算符  1&0=0  1&1=1   
	//经此循环  能取到所有的情况
	for (int i = 0; i <= bit; i++)
	{
		//判断选中宝贝重量之和是否小于最大容量
		int temp = 0;
		for (int j = 0; j < N; j++) {
			//i&BIT(j)  决定这个宝贝取不取  >>j  只是把值转化为0 1
			temp += h[j] * ((i&BIT(j)) >> j);
		}
		if (temp <= c) {
			int value = 0;
			for (int j = 0; j < N; j++) {
				value += v[j] * ((i&BIT(j)) >> j);
			}
			//找到最大的价值
			if (value > maxv) {
				maxv = value;
			}
		}
	}


	printf("最大价值：%d\n", maxv);
}


//动态规划求解01背包问题
//https://blog.csdn.net/xp731574722/article/details/70766804
const int N = 15;

void test02() {
	int v[N] = { 0,8,10,6,3,7,2 };
	int w[N] = { 0,4,6, 2,2,5,1 };


	int m[N][N];
	int n = 6, c = 12;  //六种物品  背包容量为12
	memset(m, 0, sizeof(m));
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= c; j++)
		{
			if (j >= w[i])
				m[i][j] = max(m[i - 1][j], m[i - 1][j - w[i]] + v[i]);


			else
				m[i][j] = m[i - 1][j];
		}
	}

	for (int i = 0; i <= c; i++) {
		cout << setw(2) << i << ' ';
	}
	cout << endl;
	for (int i = 1; i <= n; i++)
	{
		cout << setw(2) << i << ' ';
		for (int j = 1; j <= c; j++)
		{
			cout <<setw(2)<< m[i][j] << ' ';
		}
		cout << endl;
	}

	printf("最大价值：%2d\n", m[6][12]);

	//查看选择的方案
	//记录都选了哪几样
	vector<int> x;
	x.resize(n+1);
	for (int i = n; i>1; i--)
	{
		if (m[i][c] == m[i - 1][c])
			x[i] = 0;
		else
		{
			x[i] = 1;
			c -= w[i];
		}
	}
	x[1] = (m[1][c]>0) ? 1 : 0;
	for (int i = 0; i <= n; i++) {
		cout << i << "  ";
	}
	cout << endl;
	for (int v : x) {
		cout << v << "  ";
	}
	cout << endl;
}

int main()
{
	//test01();
	test02();

	system("pause");
    return 0;
}

