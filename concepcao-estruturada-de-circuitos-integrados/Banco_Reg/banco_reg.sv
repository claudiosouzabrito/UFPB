	module banco_reg(clk, rst, A1, A2, A3, RD1, RD2, WD3, WE3);
	input logic  clk, WE3, rst;
	input logic  [4:0]  A1, A2, A3;
	input logic  [31:0] WD3;
	output logic RD1, RD2;
	
	logic [31:0] output_decoder;
	logic [31:0] and_output;
	logic [31:0] reg_output;
	logic [31:0] qa;

	decodificador decoder_block(A3,output_decoder); //Prepara a entrada da AND
	
	genvar i;
	generate 
		for (i=0; i<32;i=i+1) begin: forBancoReg
			and (and_output[i],output_decoder[i], WE3);
			flopenr block_reg(clk, rst, and_output[i], WD3[i], reg_output[i],qa[i]); //instancia do flip 
			assign qa[i] = reg_output[i];
			end
	endgenerate	
	
	mux32 muxA(reg_output[31:0], A1[4:0],RD1);
	mux32 muxB(reg_output[31:0], A2[4:0],RD2);

endmodule
