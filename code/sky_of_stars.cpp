/********************************************************************************
*File name:SkyOfStars.cpp                                                       *
*Author:彭瑶                                                                    *
*Version:1.0                                                                    *
*Date:2018.07.10                                                                *
*Debug Environment:Visual Studio 2017                                           *
*Description:在屏幕中画出移动效果的星空，可以当作程序的背景                     *
*********************************************************************************/
#include<graphics.h>
#include<time.h>
#include<conio.h>

#define	WINDOW_SIZE 1000
using namespace std;
struct star
{
	int x;
	int y;
	int brightness; //星星的亮度决定了星星的移动速度
};

void drawBackground(); //画出背景

int main()
{
	int i, j;

	initgraph(WINDOW_SIZE, WINDOW_SIZE);

	while (!_kbhit())
	{
		drawBackground();
		Sleep(100);
	}
	closegraph();
	return 0;
}

void drawBackground() //画出星空背景
{
	static int flag = 0;
	static const int maxStarNum = WINDOW_SIZE / 3;
	static star stars[maxStarNum] = { 0, 0, 0 };
	int i;

	if (flag == 0) //如果还未初始化，那么初始化
	{
		flag = 1;
		srand(time(NULL));
		for (i = 0; i < maxStarNum; i++)
		{
			stars[i].x = rand() % WINDOW_SIZE;
			stars[i].y = rand() % WINDOW_SIZE;
			stars[i].brightness = rand() % 56 + 200; //亮度在156到255之间，对应于rbg颜色的不同值
		}
	}

	for (i = 0; i < maxStarNum; i++) //将星星画到屏幕上，要体现从左到右的移动效果
	{
		putpixel(stars[i].x, stars[i].y, 0); //先将星星原来位置去掉
		stars[i].x += ((stars[i].brightness - 200) / 25 + 1); //星星从左到右移动
		if (stars[i].x >= WINDOW_SIZE) //如果星星移出了屏幕，则在最左端重新生成一颗星星
		{
			stars[i].x = 0;
			stars[i].y = rand() % WINDOW_SIZE;
			stars[i].brightness = rand() % 56 + 200; //亮度在156到255之间，对应于rbg颜色的不同值
		}
		putpixel(stars[i].x, stars[i].y, RGB(stars[i].brightness, stars[i].brightness, stars[i].brightness)); //将星星画到屏幕上新的位置
	}
}