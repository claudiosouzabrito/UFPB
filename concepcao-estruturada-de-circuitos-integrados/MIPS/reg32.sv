module reg32(rst, clk, enable, d, y);

	input logic [31:0] d;    
	input logic clk, rst, enable;
	output logic [31:0] y;
	logic [31:0]qa;

	genvar i;
	generate 
		for (i=0; i<32;i=i+1) begin: flips
			flopenr block_reg(clk, rst, enable, d[i], y[i],qa[i]); //instancia do flip 
			assign qa[i] = y[i];
			end
	endgenerate	

endmodule

