#pragma once
#include <stdio.h>
void adjust_down(long long a[], int len, int p_index) //helper function
{
	int l_c_index = p_index * 2 + 1, r_c_index = p_index * 2 + 2;
	int t_index = r_c_index;
	if (r_c_index > len - 1) t_index = l_c_index;
	if (l_c_index > len - 1) return;
	t_index = a[l_c_index] < a[t_index] ? l_c_index : t_index;
	if (a[t_index] < a[p_index])
	{
		a[p_index] += a[t_index], a[t_index] = a[p_index] - a[t_index], a[p_index] -= a[t_index];
		adjust_down(a, len, t_index);
	}
}
void make_heap(long long a[], int len) //call this function to make array a into a heap
{
	for (int i = (len - 2) / 2; i >= 0; --i) adjust_down(a, len, i);
}
void push_heap(long long a[], int len, long long num)
{
	a[len] = num, ++len;

	int c_index = len - 1, p_index = (c_index - 1) / 2;
	while (p_index >= 0)
	{
		if (a[c_index] < a[p_index]) a[c_index] += a[p_index], a[p_index] = a[c_index] - a[p_index], a[c_index] -= a[p_index];
		else break;
		c_index = p_index, p_index = (c_index - 1) / 2;
	}
}
long long pop_heap(long long a[], int len) //pop element from heap, you should --len manufactory after pop_heap
{
	if (len == 1) return a[0];
	--len;
	a[len] += a[0], a[0] = a[len] - a[0], a[len] -= a[0];
	adjust_down(a, len, 0);
	return a[len];
}