#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	FILE *arquivo;
	int y = 0;
	int a = 0;
	int i = 0;
	arquivo = fopen("../Simulation/ModelSim/mux32.tv", "w");

	int Sel[5] = {0}, data[32] = {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0};
	//Testa uma entrada para todas as variações de chaves
	for (Sel[4] = 0; Sel[4] < 2; Sel[4]++)
		for (Sel[3] = 0; Sel[3] < 2; Sel[3]++)
			for (Sel[2] = 0; Sel[2] < 2; Sel[2]++)
				for (Sel[1] = 0; Sel[1] < 2; Sel[1]++)
					for (Sel[0] = 0; Sel[0] < 2; Sel[0]++)
					{
						a = Sel[0] * (1) + Sel[1] * (2) + Sel[2] * (4) + Sel[3] * (8) + Sel[4] * 16;
						y = data[a];
						fprintf(arquivo, "%d%d%d%d%d_%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d_%d\n", Sel[4], Sel[3], Sel[2], Sel[1], Sel[0], data[31], data[30], data[29], data[28], data[27], data[26], data[25],
								data[24], data[23], data[22], data[21], data[20], data[19], data[18], data[17], data[16],
								data[15], data[14], data[13], data[12], data[11], data[10], data[9], data[8],
								data[7], data[6], data[5], data[4], data[3], data[2], data[1], data[0], y);
					}
	fclose(arquivo);
}