	module banco_reg_32(clk, rst, A1, A2, A3, RD1, RD2, WD3, WE3);
	input logic  clk, WE3, rst;
	input logic  [4:0]  A1, A2, A3;
	input logic  [31:0] WD3;
	output logic [31:0]RD1;
   output logic [31:0]RD2;
	
	logic [31:0] output_decoder;
	logic [31:0] and_output;

	logic[31:0]array_reg[31:0];

	decoder decoder_block(A3,output_decoder); //Prepara a entrada da AND
	
	genvar i;
	generate 
		for (i=0; i<32;i=i+1) begin: forBancoReg
			and (and_output[i],output_decoder[i], WE3);
			reg32 block_regs (rst, clk, and_output[i], WD3[i],array_reg[i]); //32 instancias dos 32 flips
			end
	endgenerate	
	
	genvar k;
	generate 
		for (k=0; k<32;k=k+1) begin: formuxs
			mux32 muxA(array_reg[k], A1[4:0],RD1[k]);
			mux32 muxB(array_reg[k], A2[4:0],RD2[k]);
			end
	endgenerate	

endmodule
