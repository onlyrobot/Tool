/********************************************************************************
*File name:HanoiByIteration.c                                                   *
*Author:彭瑶                                                                    *
*Version:1.0                                                                    *
*Date:2018.04.26                                                                *
*Debug Environment:Visual Studio 2017                                           *
*Description:汉诺塔问题的迭代实现                                               *
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct record //用于记录递归环境，放入栈中
{
	int n;
	char moveFrom;
	char moveTo;
	char swap;
	struct record *next;
} record;
typedef struct stack //定义一个栈
{
	record * records;
	int num;

} stack;

//栈相关方法
void push(record *record, stack *stack) //向栈内放置元素
{
	stack->num++;
	record->next = stack->records;
	stack->records = record;
}
record * pop(stack *stack) //从栈顶弹出元素
{
	record *record;
	stack->num--;
	record = stack->records;
	stack->records = stack->records->next;
	return record;
}
//move方法，实现将n个盘子从moveFrom柱借助swap柱移动到moveTo柱
void move(int n, char moveFrom, char moveTo, char swap)
{
	stack stack = { NULL, 0 };
	record *record1, *p_record;
	//初始化栈
	record1 = (record *)malloc(sizeof(record));
	record1->n = n, record1->moveFrom = moveFrom, record1->moveTo = moveTo;
	record1->swap = swap;
	push(record1, &stack);
	//迭代开始
	while (stack.num != 0)
	{
		//从栈中取出元素，并进行相应操作
		p_record = pop(&stack);
		if (p_record->n == 1)
		{
			printf("%c->%c\t", p_record->moveFrom, p_record->moveTo);
			free(p_record);
			continue;
		}

		//记录递归环境，并放入栈中
		record *record2 = (record *)malloc(sizeof(record));
		record *record3 = (record *)malloc(sizeof(record));
		record *record4 = (record *)malloc(sizeof(record));
		record2->n = p_record->n - 1, record2->moveFrom = p_record->moveFrom,
			record2->moveTo = p_record->swap, record2->swap = p_record->moveTo;
		record3->n = 1, record3->moveFrom = p_record->moveFrom,
			record3->moveTo = p_record->moveTo, record3->swap = p_record->swap;
		record4->n = p_record->n - 1, record4->moveFrom = p_record->swap,
			record4->moveTo = p_record->moveTo, record4->swap = p_record->moveFrom;
		push(record4, &stack);
		push(record3, &stack);
		push(record2, &stack);

		//不要忘记释放内存
		free(p_record);
	}
}
int main()
{
	int n = 7;
	//调用move方法
	move(n, 'A', 'B', 'C');
	system("pause");
	return 0;
}

