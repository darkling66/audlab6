// aud1lab6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "string.h"
#include "math.h"
#include "windows.h"


typedef double(*func_t)(double);
void process_func(
	double a
	, double b
	, double h
	, double(*pf)(double)
);
int tabulate_func(func_t);
double func(double);

int main()
{
	tabulate_func(func);
	return 0;
}

int tabulate_func(func_t func)
{
	double a = -0.5, b = 0.5, h = 0.1;
	process_func(a, b, h, func);
	system("pause");
	return 0;
}



int is_min(double y1, double y2, double y3)
{
	return y2 < y1 && y2 < y3;
}

int is_max(double y1, double y2, double y3)
{
	return y2 > y1 && y2 > y3;
}

void get_mark_extr(double y[], int sz, char* mark)
{
	if (sz < 3)
	{
		perror("Invalid count of points\n");
		exit(-1);
	}

	strcpy(mark, "");
	if (is_min(y[0], y[1], y[2]))
	{
		strcpy(mark, "Min");
	}
	else
	{
		if (is_max(y[0], y[1], y[2]))
		{
			strcpy(mark, "Max");
		}
	}
}

void process_func(
	double a
	, double b
	, double h
	, double(*pf)(double)
)
{
	double x[3], y[3];
	x[0] = a; y[0] = pf(x[0]);

	int j;

	for (j = 0; j < 2; ++j)
	{
		x[j + 1] = x[j] + h;
		y[j + 1] = pf(x[j + 1]);
	}

	{
		char mark[20] = "";
		get_mark_extr(y, 3, mark);
		for (j = 0; j < 3; ++j)
		{
			printf("%.3f %.3f %s\n", x[j], y[j], j == 1 ? mark : "");
		}
	}

	for (; x[2] <= b;)
	{
		for (j = 0; j < 2; ++j)
		{
			x[j] = x[j + 1];
			y[j] = y[j + 1];
		}

		x[2] += h;
		y[2] = pf(x[2]);
		{
			char mark[20] = "";
			get_mark_extr(y, 3, mark);
			printf("%.3f %.3f %s\n", x[j], y[j], mark);
		}
	}

}

double func(double x)
{
	return x * x - cos(x);
}