module mux3(d0,d1,d2, Sel, y);

	input logic [31:0]d0, d1, d2;
	input logic [1:0]Sel;
	output logic [31:0]y;
	logic [31:0]d3;//lixo, entrada impossivel

 assign y = Sel[1] ? (Sel[0]  ?  d3: d2)
 				      : (Sel[0]  ? d1 : d0);
endmodule

