module acc(input logic clk, input logic a, input logic acu, output logic saida);
    always@(*) begin
		case (clk)
			1'b0: saida<=a;
			1'b1: saida<=acu;
		endcase
	end
endmodule