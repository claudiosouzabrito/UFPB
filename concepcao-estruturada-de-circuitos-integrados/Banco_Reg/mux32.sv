module mux32 (d, Sel, y);

	input logic [31:0] d;    
	input logic [4:0] Sel;
	output logic y;
	logic [3:0] intermediario;

	mux8 blocoM8_1(d[7:0], Sel[2:0], intermediario[0]);
	mux8 blocoM8_2(d[15:8], Sel[2:0],intermediario [1]);
	mux8 blocoM8_3(d[23:16], Sel[2:0], intermediario[2]);
	mux8 blocoM8_4(d[31:24], Sel[2:0],intermediario [3]);
	mux4 blocoM4_1 (intermediario[3:0], Sel[4:3], y);

endmodule

