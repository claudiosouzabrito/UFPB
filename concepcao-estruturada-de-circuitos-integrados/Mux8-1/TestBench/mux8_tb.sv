`timescale 1ns/100ps
module mux8_tb;
	int counter, errors, aux_error;
	logic clk,rst;
	logic [7:0]data;
	logic [2:0]sel;
	logic y, y_esperado;
	logic [11:0]vectors[2048];

	mux8 DUV(data[7:0], sel[2:0], y);

	initial begin
		$display("Iniciando Testbench");
		$display("| Sel |   Data   | Y |"); 
		$display("----------------------");
		$readmemb("C:/Users/satc1/OneDrive/Documentos/Concepcao/MIPS/Mux8-1/Simulation/ModelSim/mux8.tv",vectors);
		counter=0; errors=0;
		rst = 1; #10; rst = 0;		
	end
		
	always begin
		clk=1; #30;
		clk=0; #5;
	end

	always @(posedge clk) begin
		if(~rst)begin
			{sel[2:0], data[7:0],  y_esperado} = vectors[counter];	
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
			$display("| %b |   %b   | %b | OK", sel[2:0], data[7:0], y);
		else
			$display("| %b |   %b   | %b | ERRO", sel[2:0], data[7:0], y);

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