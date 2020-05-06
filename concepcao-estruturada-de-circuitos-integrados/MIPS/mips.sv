module mips(clk, rst, RD, WD, WE,ADR);
	input clk;
	input rst;
	input WE;
	input logic [31:0] RD;
	output logic [31:0] ADR, WD;

   logic [6:0] nextState;
   logic IorD;
   logic ALUSrcA;
   logic IRWrite;
   logic PCWrite;
   logic RegDst;
   logic MemtoReg;
   logic RegWrite;
   logic MemWrite;
   logic Branch;
   logic [1:0] ALUSrcB;
   logic [1:0] ALUOp;
   logic [1:0] PCSrc;
	logic [05:0] OP;
	logic [05:0] Funct;
	


FSM controller(rst, clk, OP, Funct, nextState,IorD, ALUSrcA, IRWrite, PCWrite, RegDst, MemtoReg, RegWrite, MemWrite, Branch, ALUSrcB, ALUOp, PCSrc);	
datapath datapath_(clk,rst,IorD,ALUSrcA, ALUSrcB, PCSrc,IRWrite, PCWrite,MemWrite, RegDst, MemtoReg, RegWrite, Branch, ALUOp, RD, OP, Funct, ADR, WD,WE);

endmodule