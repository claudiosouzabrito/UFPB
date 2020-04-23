module mdr(rst, clk, enable, d, y);
	
	input logic clk, rst, enable;
	input logic[31:0] d;
	output logic[31:0] y;
	
	always@(posedge clk or posedge rst) begin
		if(rst == 1'b1) begin
			y = 32'b0;
		end
		else if(enable == 1'b1) begin
			y = d;
		end
	end
	
endmodule