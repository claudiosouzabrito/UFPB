module flopenr (clk,reset,en,d,q,qa);
			   
  input logic clk;
  input logic reset;
  input logic en;
  input logic d;
  input logic qa;
  output logic q;
			   
	always @(posedge clk, posedge reset) begin
		if (reset) q <= 1'b0;
		else if (en) q <= d;
    else q<=qa;
	end
endmodule