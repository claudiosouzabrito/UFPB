module datapath
(	 
	 input logic clk,
	 input logic reset,
	 input logic IorD,
	 input logic ALUSrcA,
	 input logic [1:0] ALUSrcB,
	 input logic [1:0] PCSrc,
	 input logic IRWrite, 
	 input logic PCWrite,
	 input logic MemWrite, 
	 input logic RegDst, 
	 input logic MemtoReg, 
	 input logic RegWrite, 
	 input logic Branch,
	 input logic  [1:0] ALUOp,
	 input logic  [31:0] RD,
	 output logic [05:0] OP, Funct,
	 output logic [31:0] ADR, WD,
	 output logic WE
);
	logic [31:0] inputPC;
	logic [31:0] outputPC;
	logic [31:0] outputIR;
	logic [31:0] outputMDR;
	logic [31:0] outputData;
	logic [4:0] outputMux5Bit;
	logic [31:0] RD1;
	logic [31:0] RD2;
	logic [31:0] A;
	logic [31:0] B;
	logic [31:0] SrcA;
	logic [31:0] SrcB;
	logic [31:0] outputExtensor;
	logic [31:0] outputLSHIFT;
	logic [27:0] outputExtensorMuxPc;
	logic [31:0] ALUresult;
	logic [31:0] ALUoutput;
	logic Zero;
	logic PCEn;
	logic aux;
	
	and (aux,  Branch,  Zero);
	or  (PCEn, PCWrite, aux);

	ir IRreg(reset, clk, IRWrite, RD, outputIR);
	pc PCreg(reset, clk, PCEn, inputPC, outputPC);
	mdr MDR(reset, clk, 1'b1, RD, outputMDR);
	mux2_5 bloco_mux2_5 (outputIR[20:16], outputIR[15:11], RegDst, outputMux5Bit);
	mux2_32 bloco_mux2_32 (ALUoutput, outputMDR, MemtoReg, outputData);
	
	mux2_32 muxIORD (outputPC,ALUoutput,IorD,ADR); //primeiro uso do PC out
	
	banco_reg_32 BancoReg(clk, reset, outputIR[25:21], outputIR[20:16], outputMux5Bit, RD1, RD2, outputData, RegWrite);
	reg32 RD1_reg (reset, clk, 1'b1, RD1, A); 
	reg32 RD2_reg (reset, clk, 1'b1, RD2, B); 
	
	mux2_32 mux2_entrada_ula (outputPC, A, ALUSrcA, SrcA); //srcA = entrada da ULA
	
	extensor bloco_extensor (outputIR[15:0],outputExtensor);
	LSHIFT2 boco_Lshift (outputExtensor,outputLSHIFT);
	mux4_32 bloco_mux4_32 (B,32'b0000000000000000000100,outputExtensor,outputLSHIFT, ALUSrcB, SrcB); //srcB = entrada da ULA
	assign WD = B;
	assign WE = MemWrite;
	
	uladec ULA32(outputIR[6:0],ALUOp,SrcA,SrcB,ALUresult,Zero);
	LSHIFT2_26 lshIFT26(outputIR[25:0], outputExtensorMuxPc);
	reg32 regULA(reset, clk, 1'b1, ALUresult, ALUoutput); 
	mux3 mux3_32 (ALUresult,ALUoutput,outputExtensorMuxPc,PCSrc,inputPC);
	
	
	

	
	
	

endmodule