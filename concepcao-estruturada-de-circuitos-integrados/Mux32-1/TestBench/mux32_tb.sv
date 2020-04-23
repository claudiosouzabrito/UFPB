`timescale 1ns/100ps
module mux32_tb;
	int counter, errors, aux_error;
	logic clk,rst;
	logic [31:0]data;
	logic [4:0]sel;
	logic y, y_esperado;
	logic [37:0]vectors[32];

	mux32 DUV(data[31:0], sel[4:0], y);

	initial begin
		$display("Iniciando Testbench");
		$display("|  Sel  |                 Data                | Y |"); 
		$display("--------------------------------------------------");
		$readmemb("C:/Users/satc1/OneDrive/Documentos/Concepcao/MIPS/Mux32-1/Simulation/ModelSim/mux32.tv",vectors);
		counter=0; errors=0;
		rst = 1; #15; rst = 0;		
	end
		
	always begin
		clk=0; #15;
		clk=1; #15;
	end

	always @(posedge clk) begin
		if(~rst)begin
			{sel[4:0], data[31:0],  y_esperado} = vectors[counter];	
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
			$display("| %b |  %b   | %b | OK", sel[4:0], data[31:0], y);
		else
			$display("| %b |  %b   | %b | ERRO", sel[4:0], data[31:0], y);

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