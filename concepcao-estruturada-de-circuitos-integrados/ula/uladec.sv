module uladec(input logic [5:0] funct,
			  input logic [1:0] aluop,
           input logic [31:0]a,
           input logic [31:0]b,
           output logic [31:0]aluout,
			  output logic zero);
	 logic addsub;
	 logic [2:0] aluctrl;
    always@ (funct)
		case(aluop)
		  2'b00: begin 
				   aluctrl <= 3'b100; // add
				   addsub <= 1'b0;
		  end	
		  2'b01: begin 
				   aluctrl <= 3'b100; // sub
				   addsub <= 1'b1;
		  end 
		  default: case(funct) // R-type instructions
							6'b100000: begin 
										  aluctrl <= 3'b100; // add
										  addsub <= 1'b0;
							end
							6'b100010: begin
											aluctrl <= 3'b100; // sub
											addsub <= 1'b1;
							end
							6'b100100: aluctrl <= 3'b000; // and
							6'b100101: aluctrl <= 3'b001; // or
							6'b100111: aluctrl <= 3'b011; // xor
							6'b100110: aluctrl <= 3'b010; // nor
							6'b101010: aluctrl <= 3'b101; // slt
							default: aluctrl <= 3'bxxx; // ???
					  endcase
		  endcase
	 logic [31:0] ci;
    ula u(aluctrl[2:0], a[0], b[0], addsub, addsub, ci[0], aluout[0]);
	 genvar i;
	 generate
	 for(i = 1; i < 32; i = i + 1)begin: xuxu
		ula v(aluctrl[2:0], a[i], b[i], ci[i-1], addsub, ci[i], aluout[i]);
	 end
	 endgenerate
	
	 assign zero = ~|aluout;
	 
	 
endmodule