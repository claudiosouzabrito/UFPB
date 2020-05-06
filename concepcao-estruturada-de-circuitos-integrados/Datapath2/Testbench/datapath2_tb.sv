`timescale 1ns/100ps
module datapath2_tb;
	logic clk, clock;
	   logic reset,rst;
	   logic IorD;
	   logic ALUSrcA;
	   logic [1:0] ALUSrcB;
	   logic [1:0] PCSrc;
	   logic IRWrite; 
	   logic PCWrite;
	   logic MemWrite; 
	   logic RegDst; 
	   logic MemtoReg; 
	   logic RegWrite; 
	   logic Branch;
	   logic  [1:0] ALUOp;
	   logic  [31:0] RD;
	   logic [31:0] outputPC;
 		logic PCEn;
	  	logic Zero;


	   logic [5:0] OP, Funct;
	   logic [31:0] ADR, WD;
	   logic WE;
       logic [5:0] OPesperado, Functesperado;
       logic [31:0] ADResperado, WDesperado;
       logic WEesperado;
	   logic [31:0]outputPC_esperado;

	   logic [159:0]vectors[10];
	   int counter, errors, auxerror;
	   logic PCEn_esperado;
	   logic Zero_esperado;


		datapath DUV(clock, reset, IorD,ALUSrcA,ALUSrcB[1:0],PCSrc[1:0], IRWrite,PCWrite,MemWrite, RegDst, MemtoReg, RegWrite,Branch,
 					 ALUOp[1:0], RD[31:0], OP[5:0], Funct[5:0], ADR[31:0], WD[31:0], WE, outputPC[31:0], PCEn,Zero);
	initial begin
		$display("Iniciando Testbench");
		$display("|reset| clock|IorD|SrcA|SrcB| PCSrc|IRWrite|PCWrite|MemWrite |RegDst |MemtoReg |RegWrite |Branch | ALUOp |                RD                |   OP   |  Funct |                ADR               |                WD                | WE|");
		$display("-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
		$readmemb("datapath.tv", vectors);
		counter=0; errors=0;
		rst = 1; #15; rst = 0;		
	end
		
	always begin
		 clk=0; #20;
		 clk=1; #20;
	end

	always @(posedge clk) begin
		if(~rst)begin
			 {reset, clock, IorD,ALUSrcA,ALUSrcB[1:0],PCSrc[1:0], IRWrite,PCWrite,MemWrite, RegDst, MemtoReg, RegWrite,Branch,
 					 ALUOp[1:0], RD[31:0], OPesperado[5:0], Functesperado[5:0], ADResperado[31:0], WDesperado[31:0], WEesperado, outputPC_esperado[31:0]} = vectors[counter];	
		end
	end

	always @(negedge clk)	//Sempre (que o clock descer)
		if(~rst)
		begin
			auxerror = errors;
			assert ((OP === OPesperado) && (Funct===Functesperado) && (ADResperado === ADR) && (WDesperado===WD) && (WEesperado===WE))
	
		else	
		begin
			errors = errors + 1; //Incrementa contador de erros a cada bit errado encontrado
			end
		if(auxerror === errors)begin
			    $display("|reset| clock|IorD|SrcA|SrcB| PCSrc|IRWrite|PCWrite|MemWrite |RegDst |MemtoReg |RegWrite |Branch | ALUOp |                RD                |   OP   |  Funct |                ADR               |                WD                | WE|");
           	 $display("|  %b  |  %b   |  %b |  %b | %b |   %b |   %b   |   %b   |    %b    |   %b   |    %b    |    %b    |   %b   |   %b  | %b | %b | %b | %b | %b | %b | OK ",reset, clock, IorD,ALUSrcA,ALUSrcB,PCSrc, IRWrite,PCWrite,MemWrite, RegDst, MemtoReg, RegWrite,Branch, ALUOp, RD, OP, Funct, ADR, WD, WE);
				//$display("clk | Zero | PCen| inPC |outPC");				
				//$display ("|%b| %b   | %b   |  %b | - OK", clock, Zero, PCEn, outputPC);
		end else begin
			    $display("|reset| clock|IorD|SrcA|SrcB| PCSrc|IRWrite|PCWrite|MemWrite |RegDst |MemtoReg |RegWrite |Branch | ALUOp |                RD                |   OP   |  Funct |                ADR               |                WD                | WE|");
             $display("|  %b  |  %b   |  %b |  %b | %b |   %b |   %b   |   %b   |    %b    |   %b   |    %b    |    %b    |   %b   |   %b  | %b | %b | %b | %b | %b | %b | ERRO",reset, clock, IorD,ALUSrcA,ALUSrcB,PCSrc, IRWrite,PCWrite,MemWrite, RegDst, MemtoReg, RegWrite,Branch, ALUOp, RD, OP, Funct, ADR, WD, WE);
				//$display("clk | Zero | PCen| inPC |outPC");				
				//$display ("|%b| %b   | %b   |  %b | - ERRO", clock, Zero, PCEn, outputPC);		
		end
		counter=counter+1;	//Incrementa contador dos vertores de teste
		
		if(counter == $size(vectors)) //Quando os vetores de teste acabarem
		begin
			$display("Testes Efetuados  = %0d", counter);
			$display("Erros Encontrados = %0d", errors);
			#10
  			$stop;
		end
	end
 endmodule