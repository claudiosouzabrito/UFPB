module mux4_32 (d0,d1,d2,d3, Sel, y);
	input logic  [31:0]d0,d1,d2,d3;
	input logic  [1:0]Sel;
	output logic [31:0]y;
	
	genvar i;
	generate
	for (i=0; i<32; i=i+1) begin: blocomux4_32
		mux4 mux4_32(d3[i],d2[i],d1[i],d0[i], Sel[1:0], y[i]);
	end
	endgenerate
endmodule
