/********************************************************************************
*File name:HanoiByRecursion.c                                                   *
*Author:彭瑶                                                                    *
*Version:1.0                                                                    *
*Date:2018.04.26                                                                *
*Debug Environment:Visual Studio 2017                                           *
*Description:汉诺塔问题的递归实现                                               *
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>


//move方法，实现将n个盘子从moveFrom柱借助swap柱移动到moveTo柱
void move(int n, char moveFrom, char moveTo, char swap)
{
	if (n == 1)
	{
		printf("%c->%c\t", moveFrom, moveTo);
		return;
	}
	move(n - 1, moveFrom, swap, moveTo);
	move(1, moveFrom, moveTo, swap);
	move(n - 1, swap, moveTo, moveFrom);
}
int main()
{
	int n = 3;
	//调用move函数
	move(n, 'A', 'B', 'C');
	system("pause");
	return 0;
}