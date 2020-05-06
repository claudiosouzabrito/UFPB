int mux4_func()
{
	FILE *arquivo;
	int y = 0;
	arquivo = fopen("Mux4-1/Simulation/ModelSim/mux4.tv", "w");

	for (int Sel_0 = 0; Sel_0 < 2; Sel_0++)
	{

		for (int Sel_1 = 0; Sel_1 < 2; Sel_1++)
		{
			for (int a = 0; a < 2; a++)
			{
				for (int b = 0; b < 2; b++)
				{
					for (int c = 0; c < 2; c++)
					{
						for (int d = 0; d < 2; d++)
						{
							if ((Sel_0 == 0) & (Sel_1 == 0))
								y = a;
							else if ((Sel_0 == 0) & (Sel_1 == 1))
								y = b;
							else if ((Sel_0 == 1) & (Sel_1 == 0))
								y = c;
							else
								y = d;
							fprintf(arquivo, "%d_%d_%d_%d_%d_%d_%d\n", Sel_0, Sel_1, a, b, c, d, y);
						}
					}
				}
			}
		}
	}
	fclose(arquivo);
}