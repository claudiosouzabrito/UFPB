#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define peso_A 4
#define peso_B 3
#define peso_C 2
#define peso_D 1
#define peso_E 0

int calcula_decimal(int a, int b, int c, int d, int e)
{
	int resultado = 0;
	resultado = (a * pow(2, peso_A)) + (b * pow(2, peso_B)) + (c * pow(2, peso_C)) + (d * pow(2, peso_D)) + (e * pow(2, peso_E));
	return resultado;
}

int *decoder(int a, int b, int c, int d, int e)
{
	int set = 0;
	set = calcula_decimal(a, b, c, d, e);
	int *bits = (int *)calloc(32, sizeof(int));
	for (int i = 0; i < 32; i++)
		bits[i] = 0;
	bits[31 - set] = 1;
	return bits;
}

int flopenr(int clk, int rst, int en, int d, int qa)
{
	int y = 0;

	if (rst == 1)
	{
		y = 0;
		qa = 0;
	}
	else
	{
		if (clk == 1)
		{
			if (en)
				y = d;
			else
				y = qa;
		}
		else
		{
			y = qa;
		}
	}
	return y;
}

int mux32(int sel_4, int sel_3, int sel_2, int sel_1, int sel_0)
{
	int pos = 0;
	pos = sel_0 * (1) + sel_1 * (2) + sel_2 * (4) + sel_3 * (8) + sel_4 * 16;
	return pos;
}

int main(int argc, char **argv)
{

	FILE *arquivo;
	arquivo = fopen("../Simulation/ModelSim/banco_reg.tv", "w");

	int clk, WE3, rst;
	int A1[5], A2[5], A3[5];
	int WD3[] = {1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1};
	int RD1, RD2;
	int output_decoder[32] = {0};
	int output_reg[32] = {0};
	int a, b, c, d, e;
	int *bits;
	int and [32] = {0};
	int pos = 0;
	int qa[32] = {0};
	int count = -1;

	for (rst = 0; rst < 2; rst++)
		for (int f = 0; f < 2; f++)
		{ //A1
			for (int g = 0; g < 2; g++)
				for (int h = 0; h < 2; h++)
					for (int j = 0; j < 2; j++)
						for (int k = 0; k < 2; k++)
							for (int l = 0; l < 2; l++) //A2
								for (int m = 0; m < 2; m++)
									for (int n = 0; n < 2; n++)
										for (int o = 0; o < 2; o++)
											for (int p = 0; p < 2; p++)
												for (a = 0; a < 2; a++) //A3
													for (b = 0; b < 2; b++)
														for (c = 0; c < 2; c++)
															for (d = 0; d < 2; d++)
																for (e = 0; e < 2; e++)
																	for (WE3 = 0; WE3 < 2; WE3++)
																		for (clk = 0; clk < 2; clk++)
																		{
																			A1[4] = f;
																			A1[3] = g;
																			A1[2] = h;
																			A1[1] = j;
																			A1[0] = k;

																			A2[4] = l;
																			A2[3] = m;
																			A2[2] = n;
																			A2[1] = o;
																			A2[0] = p;

																			A3[4] = a;
																			A3[3] = b;
																			A3[2] = c;
																			A3[1] = d;
																			A3[0] = e;

																			count++;

																			fprintf(arquivo, "%d_%d_", rst, clk);

																			bits = decoder(A3[4], A3[3], A3[2], A3[1], A3[0]);

																			fprintf(arquivo, "%d%d%d%d%d_%d%d%d%d%d_", A1[4], A1[3], A1[2], A1[1], A1[0], A2[4], A2[3], A2[2], A2[1], A2[0]);
																			fprintf(arquivo, "%d%d%d%d%d_", A3[4], A3[3], A3[2], A3[1], A3[0]);
																			fprintf(arquivo, "%d_", WE3);

																			for (int i = 0; i < 32; i++)
																			{
																				and[i] = bits[i] & WE3;
																				//fprintf(arquivo, "%d", bits[i]); //Se o enable estiver off, sai 0 -- enable 1 recebe a saída do decoder..
																				//bits = saida do decodificador
																			}
																			//fprintf(arquivo, "_");

																			for (int i = 0; i < 32; i++)
																				fprintf(arquivo, "%d", WD3[i]); //entrada

																			fprintf(arquivo, "_");
																			for (int i = 0; i < 32; i++)
																			{
																				output_reg[i] = flopenr(clk, rst, and[i], WD3[i], qa[i]);
																				qa[i] = output_reg[i];
																				//fprintf(arquivo, "%d", output_reg[i]); //Sai a entrada qnd o WE3=1 & CLK=1 & RST=0
																			}

																			//for (int i = 0; i < 32; i++)
																			//	fprintf(arquivo, "%d", output_reg[i]); //Sai um qnd o WE3=1 & CLK=1 & RST=0
																			pos = mux32(A1[4], A1[3], A1[2], A1[1], A1[0]);
																			RD1 = output_reg[31 - pos];
																			pos = mux32(A2[4], A2[3], A2[2], A2[1], A2[0]);
																			RD2 = output_reg[31 - pos];
																			if (count >= 3)
																				fprintf(arquivo, "%d_%d\n", RD1, RD2); //Sai um qnd o WE3=1 & CLK=1 & RST=0
																			else
																				fprintf(arquivo, "x_x\n"); //Esses sao os 3 primeiros casos onde o Qa é X
																		}
		}

	return 0;
}
