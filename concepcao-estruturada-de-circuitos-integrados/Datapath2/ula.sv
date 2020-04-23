module ula(input logic [2:0] aluctrl,
           input logic a,
           input logic b,
           input logic ci,
			  input logic addsub,
           output logic cout,
           output logic aluout);
	 logic aand;
    logic oor;
    logic xoor;
    logic noor;
	 logic slt;
    logic suus;
	 
    logic [7:0]in;
    assign aand = a & b;
    assign oor = a | b;
    assign noor = ~(a | b);
    assign xoor = a ^ b;
    assign suus = a ^ b ^ ci;
	 always@(*)
		if(!addsub) begin
			 cout = ((a & b) | (a & ci) | (b & ci));
		end
		else begin
			 cout = ((!a & b) | (!a & ci) | (b & ci));
		end
	 always@(*)
		 if (a < b) begin
			slt = 1'b1;
		 end
		 else begin 
			slt = 1'b0;
		 end
    assign in[0] = aand;
    assign in[1] = oor;
    assign in[2] = noor;
    assign in[3] = xoor;
    assign in[4] = suus;
	 assign in[5] = slt;
    mux8 blocoM8_1(in[7:0],aluctrl[2:0], aluout);
endmodule