module mux4(input logic  d3,d2,d1,d0,
			input logic [1:0]Sel,
			output logic y);
 assign y = Sel[1] ? (Sel[0] ? d3 : d2)
 				    : (Sel[0] ? d1 : d0);
endmodule