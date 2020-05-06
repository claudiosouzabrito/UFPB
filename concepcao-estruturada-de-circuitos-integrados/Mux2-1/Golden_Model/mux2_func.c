int mux2_func()
{
	FILE *arquivo;
	int y = 0;
	arquivo = fopen("Mux2-1/Simulation/ModelSim/mux2.tv", "w");

	for (int Sel_0 = 0; Sel_0 < 2; Sel_0++)
	{
		for (int a = 0; a < 2; a++)
		{
			for (int b = 0; b < 2; b++)
			{
				if (!Sel_0)
				{
					y = a;
				}
				else
				{
					y = b;
				}
				fprintf(arquivo, "%d_%d_%d_%d\n", Sel_0, a, b, y);
			}
		}
	}
	fclose(arquivo);
}