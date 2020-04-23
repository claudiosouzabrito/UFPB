module mux4(input logic  [3:0]d,
			input logic [1:0]Sel,
			output logic y);
 assign y = Sel[1] ? (Sel[0] ? d[3] : d[2])
 				    : (Sel[0] ? d[1] : d[0]);
endmodule