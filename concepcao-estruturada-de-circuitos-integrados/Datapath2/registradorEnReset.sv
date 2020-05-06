module registradorEnReset(ck, reset_register, enable, in, out);
	
	input logic ck, reset_register, enable;
	input logic[31:0] in;
	output logic[31:0] out;
	
	always@(posedge ck or posedge reset_register) begin
		if(reset_register == 1'b1) begin
			out = 32'b0;
		end
		else if(enable == 1'b1) begin
			out = in;
		end
	end
	
endmodule