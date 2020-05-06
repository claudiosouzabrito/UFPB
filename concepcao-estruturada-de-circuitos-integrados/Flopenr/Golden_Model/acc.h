#ifndef ACC_H_INCLUDED
#define ACC_H_INCLUDED

#include <stdbool.h>

int acc(int clk, int rst, int en, int d)
{
	int y = 0;
	if (clk == 1 || rst == 1)
	{
		if (rst)
			y = 0;
		else if (en)
			y = d;
	}
	return y;
}
#endif // ACC_H_INCLUDED