module mux8 (d, Sel, y);

	input logic [7:0] d;    
	input logic [2:0] Sel;
	logic [1:0]intermediario;
	output logic y;

mux4 blocoM4_1(d[3],d[2],d[1],d[0],Sel[1:0], intermediario[0]);
mux4 blocoM4_2(d[7],d[6],d[5],d[4],Sel[1:0], intermediario [1]);
mux2 blocoM2_1 (intermediario[0],intermediario[1], Sel[2], y);

endmodule

