module pc32(rst, clk, en, d, y, qa);
	input logic [31:0] d;    
	input logic clk, rst, en;
	output logic [31:0] y;
	input logic [31:0]qa;
	
		   
	always @(posedge clk, posedge rst) begin
		if (rst) y <= 32'b0;
		else if (en) y <= d;
    else y<=qa;
	end
endmodule