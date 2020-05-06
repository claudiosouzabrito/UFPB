`timescale 1 ns / 1 ns
module bancoReg_tb;
	int    counter, errors, aux_error;
	logic  clk, we3, rst;
	logic  [4:0]  A1, A2, A3;
	logic  [31:0] wd3;
 	logic  rd1;
 	logic  rd2;	
	logic  clock, reset;
	logic  rd1_esperado, rd2_esperado;
	
	logic [51:0]vectors[262144];
	banco_reg DUV(clk, rst, A1[4:0], A2[4:0], A3[4:0], rd1, rd2, wd3[31:0],we3);

	initial begin
		$display("                          Iniciando Testbench                 ");
		$display("| rst | clk | en |   A1  |  A2   |  A3   |            WD3                   | RD1 | RD2 |"); 
		$display("------------------------------------------------------------------------------------- ---");
		$readmemb("banco_reg.tv",vectors);
		counter=0; errors=0;
		reset = 1; #20; reset = 0;		
	end
		
	always begin
		clock=0; #10;
		clock=1; #5;
	end

	always @(posedge clock) begin
		if(~reset)begin
			{rst, clk, A1[4:0], A2[4:0], A3[4:0], we3, wd3[31:0], rd1_esperado, rd2_esperado} = vectors[counter];	
		end
	end

	always @(negedge clock)	//Sempre (que o clock descer)
		if(~reset)
		begin
			aux_error = errors;
			assert ((rd1 === rd1_esperado) && (rd2 === rd2_esperado))
		else	
		begin
			errors = errors + 1; //Incrementa contador de erros a cada bit errado encontrado
			end
		if(aux_error === errors)
				$display("|  %b  |  %b  | %b  | %b | %b | %b | %b |  %b  |  %b  | OK ",rst, clk, we3,  A1[4:0], A2[4:0], A3[4:0], wd3[31:0], rd1, rd2);
		else
		//if(aux_error!==errors)
			$display("|  %b  |  %b  | %b  | %b | %b | %b | %b |  %b  |  %b  | ERRO ",rst, clk, we3,  A1[4:0], A2[4:0], A3[4:0], wd3[31:0], rd1, rd2);
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
