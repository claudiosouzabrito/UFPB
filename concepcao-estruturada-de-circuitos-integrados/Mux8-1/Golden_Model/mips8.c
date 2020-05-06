#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	FILE *arquivo;
	int y = 0;
	int a = 0;
	int i = 0;
	arquivo = fopen("../Simulation/ModelSim/mux8.tv", "w");

	int Sel[3] = {0}, data[8] = {0};

	for (Sel[2] = 0; Sel[2] < 2; Sel[2]++)
		for (Sel[1] = 0; Sel[1] < 2; Sel[1]++)
			for (Sel[0] = 0; Sel[0] < 2; Sel[0]++)
				for (data[7] = 0; data[7] < 2; data[7]++)
					for (data[6] = 0; data[6] < 2; data[6]++)
						for (data[5] = 0; data[5] < 2; data[5]++)
							for (data[4] = 0; data[4] < 2; data[4]++)
								for (data[3] = 0; data[3] < 2; data[3]++)
									for (data[2] = 0; data[2] < 2; data[2]++)
										for (data[1] = 0; data[1] < 2; data[1]++)
											for (data[0] = 0; data[0] < 2; data[0]++)
											{
												a = Sel[0] * (1) + Sel[1] * (2) + Sel[2] * (4);
												y = data[a];
												fprintf(arquivo, "%d%d%d_%d%d%d%d%d%d%d%d_%d\n", Sel[2], Sel[1], Sel[0], data[7], data[6], data[5], data[4], data[3], data[2], data[1], data[0], y);
											}
	fclose(arquivo);
}