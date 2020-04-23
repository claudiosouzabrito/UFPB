#ifndef INV_H_INCLUDED
#define INV_H_INCLUDED

#include <stdbool.h>

int inversor(int clk, rst, en, d)
{

	if (clk == 1 || rst == 1)
	{
		if (rst)
			y = 0;
		else if (en)
			y = d;
	}
	return y;
}
#endif // INV_H_INCLUDED