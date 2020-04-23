module mux2_5(a,b,sel,y);
	input logic [4:0]a;
	input logic [4:0]b;
	input logic sel;
	output logic [4:0]y;
	
	genvar i;
	generate
	for (i=0; i<5; i=i+1) begin: muxs5_2
		mux2 bloco(a[i], b[i], sel, y[i]);
	end
	endgenerate
endmodule

	