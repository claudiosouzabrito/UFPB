module mux2 (a,b,sel,y);
	input logic a,b,sel;
	output logic y;
	
	always@(*) begin
		case (sel)
			1'b0: y<=a;
			1'b1: y<=b;
		endcase
	end
endmodule