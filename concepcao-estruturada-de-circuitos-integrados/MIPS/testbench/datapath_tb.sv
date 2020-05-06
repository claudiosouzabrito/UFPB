`timescale 1ns/10ps

module Datapath_tb();
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
       logic  [2:0]  ALUControl;
	   logic  [31:0] RD;

	   logic [05:0] OP, Funct;
	   logic [31:0] ADR; WD;
	   logic WE;

       logic [05:0] OP_esperado, Funct_esperado;
       logic [31:0] ADR_esperado, WD_esperado;
       logic WE_esperado;
	
	datapath DUV(clock, reset, IorD,ALUSrcA,ALUSrcB,PCSrc, IRWrite,PCWrite,MemWrite, RegDst, MemtoReg, RegWrite,Branch,
 				 ALUOp, ALUControl, RD, OP_esperado, Funct_esperado, ADR_esperado, WD_esperado, WE_esperado);
	always
		begin
			clk = 1; #25; clk = 0; #5;
		end
		
		initial
			begin 
				$readmemb("C:/Users/satc1/OneDrive/Documentos/Concepcao/MIPS-Componentes/DataPath_2/Simulation/ModelSim/datapath.tv", testvectors);
				vectornum = 0;
				errors = 0;
				rst = 1; #8; rst = 0;
			end
			
		always @ (posedge clk)
			begin
				#1 {clock, reset, IorD,ALUSrcA,ALUSrcB,PCSrc, IRWrite,PCWrite,MemWrite, RegDst, MemtoReg, RegWrite,Branch, ALUOp, ALUControl, 
				, RD, OP_esperado, Funct_esperado, ADR_esperado, WD_esperado, WE_esperado} = testvectors[vectornum];


		always @ (negedge clk)
			if (~rst) begin
				for(reg[5:0] i = 6'b000000; i < 6'b100000; i++) begin
					assert (Adr[i] === Adr_expected[i]) else 
					 begin
						if(Adr_expected[i] !== 1'bx) begin
							$display("Line with error: %1d", vectornum + 1);
							$display("Error: ck: %b, reset_: %b, IorD: %b, IRWrite: %b,", ck, reset_, IorD, IRWrite); 
							$display(" RegDest: %b, MemtoReg: %b, RegWrite: %b,", RegDest, MemtoReg, RegWrite);
							$display(" ALUSrcA: %b, ALUSrcB: %b, ALUControl: %b,", ALUSrcA, ALUSrcB, ALUControl);
							$display(" Branch: %b, PCWrite: %b, PCSrc: %b, RD: %b", Branch, PCWrite, PCSrc, RD);
							$display(" Adr[%d] = %b, (%b expected)", i, Adr[i], Adr_expected[i]);
						
							errors = errors + 1;
						end
					 end
					 assert (WD[i] === WD_expected[i]) else 
					 begin
						if(WD_expected[i] !== 1'bx) begin
							$display("Line with error: %1d", vectornum + 1);
							$display("Error: ck: %b, reset_: %b, IorD: %b, IRWrite: %b,", ck, reset_, IorD, IRWrite); 
							$display(" RegDest: %b, MemtoReg: %b, RegWrite: %b,", RegDest, MemtoReg, RegWrite);
							$display(" ALUSrcA: %b, ALUSrcB: %b, ALUControl: %b,", ALUSrcA, ALUSrcB, ALUControl);
							$display(" Branch: %b, PCWrite: %b, PCSrc: %b, RD: %b", Branch, PCWrite, PCSrc, RD);
							$display(" WD[%d] = %b, (%b expected)", i, WD[i], WD_expected[i]);
						
							errors = errors + 1;
						end
					 end
				end
				assert (overflow === overflow_expected) else 
					 begin
						if(overflow_expected !== 1'bx) begin
							$display("Line with error: %1d", vectornum + 1);
							$display("Error: ck: %b, reset_: %b, IorD: %b, IRWrite: %b,", ck, reset_, IorD, IRWrite); 
							$display(" RegDest: %b, MemtoReg: %b, RegWrite: %b,", RegDest, MemtoReg, RegWrite);
							$display(" ALUSrcA: %b, ALUSrcB: %b, ALUControl: %b,", ALUSrcA, ALUSrcB, ALUControl);
							$display(" Branch: %b, PCWrite: %b, PCSrc: %b, RD: %b", Branch, PCWrite, PCSrc, RD);
							$display(" overflow = %b, (%b expected)", overflow, overflow_expected);
						
							errors = errors + 1;
						end
					 end
				
				vectornum = vectornum + 1;
				
				if(testvectors[vectornum] === 114'bx) begin
					$display("%d tests completed with %d errors", vectornum, errors);
					$finish;
				end
			end
endmodule
