module mux2_32(a,b,sel,y);
	input logic [31:0]a;
	input logic [31:0]b;
	input logic sel;
	output logic [31:0]y;
	
	genvar i;
	generate
	for (i=0; i<32; i=i+1) begin: mux2_32
		mux2 mux2_2(a[i], b[i], sel, y[i]);
	end
	endgenerate
endmodule
