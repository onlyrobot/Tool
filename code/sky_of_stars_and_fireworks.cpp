/********************************************************************************
*File name:SkyOfStars.cpp
*Author:彭瑶
*Version:1.0
*Date:2018.07.10
*Debug Environment:Visual Studio 2017
*Description:在屏幕中画出移动效果的星空为背景，以及烟花为前景
*********************************************************************************/
#include<graphics.h>
#include<time.h>
#include<conio.h>
#include<math.h>
#include<vector>

#define	WINDOW_SIZE 1000
#define PI 3.1415926 //定义Π的值
using namespace std;
struct star
{
	int r; //极坐标的半径（以屏幕中心为原点）
	double angle; //极坐标的角度
	int r0; //初始时到原点的距离
	int brightness; //星星的亮度决定了星星的初始绕屏幕中心的切向速度（默认初始法向速度为零）
	star()
	{
		r = r0 = rand() % WINDOW_SIZE + 10;
		angle = rand() % 360 / 180.0 * PI;
		brightness = rand() % 56 + 200; //亮度在156到255之间，对应于rbg颜色的不同值
	}
};
struct firework
{
	int x; //烟花中心的x座标
	int y; //烟花中心的y座标
	int time; //烟花爆炸后经过的时间，正比于烟花的当前大小
	int fireNum; //烟花爆炸后产生的焰苗数量在3~48之间
	double angle; //烟花的焰火喷射角度（与x轴正向的夹角，在 0~（Π/焰苗数量） 之间
	firework() //构造函数
	{
		x = rand() % WINDOW_SIZE;
		y = rand() % WINDOW_SIZE;
		time = 1;
		fireNum = 3 + rand() % 46;
		angle = 2 * PI / fireNum * (rand() % 11 * 0.1);
	}
};

void drawBackground(); //画出背景
void drawFireworks(); //画出烟花

int main()
{
	int i, j;

	initgraph(WINDOW_SIZE, WINDOW_SIZE);

	while (!_kbhit())
	{
		drawBackground();
		//drawFireworks();
		Sleep(50);
		cleardevice();
	}
	closegraph();
	return 0;
}

void drawBackground() //画出星空背景
{
	static int flag = 0;
	static const int maxStarNum = WINDOW_SIZE * 10;
	static star stars[maxStarNum];
	int i;
	setorigin(WINDOW_SIZE / 2, WINDOW_SIZE / 2); //设置原点位置
	if (flag == 0) //如果还未初始化，那么初始化
	{
		flag = 1;
		srand(time(NULL));
		for (i = 0; i < maxStarNum; i++)
		{
			stars[i] = star();
		}
	}

	for (i = 0; i < maxStarNum; i++) //将星星画到屏幕上，要体现以屏幕中心做近心运动的移动效果
	{
		putpixel(stars[i].r * cos(stars[i].angle), - stars[i].r * sin(stars[i].angle), 0); //先将星星原来位置去掉
		stars[i].r -= rand() % 2; //星星近心运动
		stars[i].angle -= stars[i].brightness / 100.0 / stars[i].r0;
		if (stars[i].r <= 10) //如果星星移到了屏幕中心，则生成一颗新的星星
		{
			stars[i] = star();
		}
		putpixel(stars[i].r * cos(stars[i].angle), -stars[i].r * sin(stars[i].angle), RGB(stars[i].brightness, stars[i].brightness, stars[i].brightness)); //将星星画到屏幕上新的位置
	}
}
void drawFireworks() //画出烟花
{
	static int flag = 0;
	static const int maxFireworkNum = WINDOW_SIZE / 20; //同时存在的烟花最大数量
	static vector<firework> fireworks; //保存当前存在的烟花的向量
	int i;
	setorigin(0, 0); //设置原点位置
	if (flag == 0) //如果还未初始化，那么初始化
	{
		flag = 1;
		srand(time(NULL));
		i = rand() % maxFireworkNum; //随机决定当前烟花数量
		for (; i > 0; i--) //将随机生成的烟花添加到集合中
		{
			firework fw = firework();
			fireworks.push_back(fw);
		}
	}
	//画烟花
	int points[8]; //代表焰火的多边形的座标
	double angle;
	vector<firework>::iterator it = fireworks.begin();
	for (; it != fireworks.end();) //循环画每一个烟花
	{
		angle = it->angle;
		for (i = 0; i < it->fireNum; i++) //循环画每一个焰火
		{
			points[0] = it->x + it->time * 10 * cos(angle);
			points[1] = it->y - it->time * 10 * sin(angle);
			points[4] = it->x + (it->time - it->time / 3 - 1) * 10 * cos(angle);
			points[5] = it->y - (it->time - it->time / 3 - 1) * 10 * sin(angle);
			points[2] = it->x + (it->time * 10 - 3) * cos(angle + 2 * PI / it->fireNum / 8);
			points[3] = it->y - (it->time * 10 - 3) * sin(angle + 2 * PI / it->fireNum / 8);
			points[6] = it->x + (it->time * 10 - 3) * cos(angle - 2 * PI / it->fireNum / 8);
			points[7] = it->y - (it->time * 10 - 3) * sin(angle - 2 * PI / it->fireNum / 8);
			setfillcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
			fillpoly(4, points);
			angle += 2 * PI / it->fireNum; //angle自增
		}
		//判断时间是否大于等于10，如果是则烟花消失，否则时间加一
		if (it->time >= 15)
		{
			it = fireworks.erase(it);
		}
		else
		{
			it->time++;
			it++;
		}
	}
	//适当补充新的烟花，数量随机，但是数量总数不能超过最大烟花数
	for (i = rand() % (maxFireworkNum - fireworks.size() + 1); i > 0; i--)
	{
		firework fw = firework();
		fireworks.push_back(fw);
	}
	Sleep(50);
}