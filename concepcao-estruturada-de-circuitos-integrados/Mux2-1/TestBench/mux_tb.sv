`timescale 1ns/100ps
module mux_tb;
	int counter, errors, aux_error;
	logic clk,rst;
	logic a , b, sel;
	logic y, y_esperado;
	logic [3:0]vectors[8];

	mux DUV(a, b, sel, y);

	initial begin
		$display("Iniciando Testbench");
		$display("|Sel| A | B | Y |"); 
		$display("---------------");
		$readmemb("C:/Users/satc1/OneDrive/Documentos/Concepcao/Mux2-1/Simulation/ModelSim/mux2.tv",vectors);
		counter=0; errors=0;
		rst = 1; #10; rst = 0;		
	end
		
	always begin
		 clk=1; #30;
		clk=0; #5;
	end

	always @(posedge clk) begin
		if(~rst)begin
			{sel,a, b, y_esperado} = vectors[counter];	
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
			$display("| %b | %b | %b | %b | OK", sel,a, b, y);
		else
			$display("| %b | %b | %b | %b | ERRO", sel, a, b, y);

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