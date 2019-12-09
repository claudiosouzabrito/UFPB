module acc(input logic clk, input logic [3:0] a, input logic [3:0] acu, output logic [3:0] saida);
    always@(*) begin
		case (clk)
			1'b0: saida<=a;
			1'b1: saida<=acu;
		endcase
	end
endmodule