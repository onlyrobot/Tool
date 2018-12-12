/********************************************************************************
*File name:Fireworks.cpp
*Author:彭瑶
*Version:1.0
*Date:2018.07.11
*Debug Environment:Visual Studio 2017
*Description:在屏幕中画出变换的烟花，可以用于程序的背景
*********************************************************************************/
#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<math.h>
#include<vector>

#define WINDOW_SIZE 1000 //窗口大小
#define PI 3.1415926 //定义Π的值
using namespace std;

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

void drawBackground(); //画出背景中变换的烟花
int main()
{
	initgraph(WINDOW_SIZE, WINDOW_SIZE);
	while (!_kbhit())
	{
		drawBackground();
	}
	closegraph();
	return 0;
}
void drawBackground() //画出背景中变换的烟花
{
	static int flag = 0;
	static const int maxFireworkNum = WINDOW_SIZE / 20; //同时存在的烟花最大数量
	static vector<firework> fireworks; //保存当前存在的烟花的向量
	int i;
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
	cleardevice();
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