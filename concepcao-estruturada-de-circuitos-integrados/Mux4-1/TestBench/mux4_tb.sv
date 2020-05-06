`timescale 1ns/100ps
module mux4_tb;
	int counter, errors, aux_error;
	logic clk,rst;
	logic a, b, c, d, sel1, sel0;
	logic y, y_esperado;
	logic [6:0]vectors[64];

	mux4 DUV(a, b, c, d, sel1, sel0, y);

	initial begin
		$display("Iniciando Testbench");
		$display("|Sel0|Sel1| A | B | C | D | Y |"); 
		$display("---------------");
		$readmemb("C:/Users/satc1/OneDrive/Documentos/Concepcao/Mux4-1/Simulation/ModelSim/mux4.tv",vectors);
		counter=0; errors=0;
		rst = 1; #10; rst = 0;		
	end
		
	always begin
		 clk=1; #30;
		clk=0; #5;
	end

	always @(posedge clk) begin
		if(~rst)begin
			{sel1,sel0,a, b, c, d,  y_esperado} = vectors[counter];	
		end
	end

	always @(negedge clk)	//Sempre (que o clock descer)
		if(~rst)
		begin
			aux_error = errors;
			assert (y === y_esperado)
		else	
		begin
			errors = errors + 1; //Incrementa contador de erros a cada bit errado encontrado
			end
		if(aux_error === errors)
			$display("| %b | %b | %b | %b | %b | %b | %b | OK", sel1, sel0, a, b, c, d, y);
		else
			$display("| %b | %b | %b | %b | %b | %b | %b | ERRO", sel1, sel0, a, b, c, d, y);

		counter++;	//Incrementa contador dos vertores de teste
		
		if(counter == $size(vectors)) //Quando os vetores de teste acabarem
		begin
			$display("Testes Efetuados  = %0d", counter);
			$display("Erros Encontrados = %0d", errors);
			#10
			$stop;
		end
	end
 endmodule