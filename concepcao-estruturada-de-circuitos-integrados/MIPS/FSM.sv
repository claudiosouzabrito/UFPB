module FSM(input logic reset,
			  input logic clk,
			  input logic [5:0] opcode,
			  input logic [5:0] funct,
			  output logic [6:0] y,
			  output logic IorD,
			  output logic AluSrcA,
			  output logic IRWrite,
			  output logic PCWrite,
			  output logic RegDst,
			  output logic MemtoReg,
			  output logic RegWrite,
			  output logic MemWrite,
			  output logic Branch,
			  output logic [1:0] AluSrcB,
			  output logic [1:0] ALUOp,
			  output logic [1:0] PCSrc
			  );
						  
    typedef enum logic [6:0] { S0 = 7'd0, S1 = 7'd1, S2 = 7'd2, S3 = 7'd3, S4 = 7'd4, S5 = 7'd5, S6 = 7'd6,
										 S61 = 7'd61, S62 = 7'd62, S63 = 7'd63, S64 = 7'd64, S65 = 7'd65, S66 = 7'd66,
										 S7 = 7'd7, S8 = 7'd8, S9 = 7'd9, S10 = 7'd10, S11 = 7'd11} statetype;
    statetype state, nextstate;
    // state register
    always_ff @(posedge clk, posedge reset)
        if (reset) state <= S0;
			else state <= nextstate;
    // next state logic
    always @(state)
        case (state)
            S0: begin
					nextstate  <= S1;
					IorD   = 1'b0;
					AluSrcA   = 1'b0;
					AluSrcB   = 2'd1;
					ALUOp   = 2'd0;
					PCSrc   = 2'd0;
					IRWrite   = 1'b1;
					PCWrite   = 1'b1;
					AluSrcA = AluSrcA;
				end
            S1: begin
					AluSrcA   = 1'b0;
					AluSrcB   = 2'd3;
					ALUOp   = 2'd0;
					case(opcode)
                    6'b000000: nextstate  <= S6;
                    6'b100011: nextstate  <= S2;
                    6'b101011: nextstate  <= S2;
                    6'b000100: nextstate  <= S8;
                    6'b000101: nextstate  <= S8;
                    6'b001000: nextstate  <= S9;
                    6'b000010: nextstate  <= S11;
                endcase
				end
				
            S2: begin
					AluSrcA   = 1'b1;
					AluSrcB   = 2'd2;
					ALUOp   = 2'd0;
					case(opcode)
                    6'b100011: nextstate  <= S3;
                    6'b101011: nextstate  <= S5;
                    default: nextstate  <= S0;
                endcase
				end
				
            S3: begin
					IorD   = 1'b1;
					if(reset) nextstate  <= S0;
					else nextstate <= S4;
				end
            S4: begin
					nextstate  <= S0;
					RegDst   = 1'b0;
					MemtoReg   = 1'b1;
					RegWrite   = 1'b1;
				end
            S5: begin
					nextstate  <= S0;
					IorD   = 1'b1;
					MemWrite   = 1'b1;
				end
            S6: begin
					AluSrcA   = 1'b1;
            	AluSrcB   = 2'd0;
					ALUOp   = 2'd2;
					case(funct)
                    6'b100000: nextstate  <= S61;
                    6'b100010: nextstate  <= S62;
                    6'b100100: nextstate  <= S63;
                    6'b100101: nextstate  <= S64;
                    6'b100111: nextstate  <= S65;
                    6'b100110: nextstate  <= S66;
                    default: nextstate   <= S0;
                endcase
				end
            S61: if(reset) nextstate  <= S0;
					  else nextstate  <= S7;
            S62: if(reset) nextstate  <= S0;
					  else nextstate  <= S7;
            S63: if(reset) nextstate  <= S0;
					  else nextstate  <= S7;
            S64: if(reset) nextstate  <= S0;
					  else nextstate  <= S7;
            S65: if(reset) nextstate  <= S0;
					  else nextstate  <= S7;
            S66: if(reset) nextstate <= S0;
					  else nextstate  <= S7;
					  
            S7: begin
					nextstate  <= S0;
					RegDst   = 1'b1;
					MemtoReg   = 1'b0;
					RegWrite   = 1'b1;
				end
				
            S8: begin
					nextstate  <= S0;
            	AluSrcA   = 1'b1;
					AluSrcB   = 2'd0;
					ALUOp   = 2'd1;
					PCSrc   = 2'd1;
					Branch   = 1'b1;
				end
				
            S9: begin
					if(reset) nextstate  <= S0;
					else nextstate  <= S10;
					AluSrcA   = 1'b1;
					AluSrcB   = 2'd2;
					ALUOp   = 2'd0;
				end
				
            S10: begin
					nextstate  <= S0;
					RegDst   = 1'b0;
					MemtoReg   = 1'b0;
					RegWrite   = 1'b1;
				end
				
            S11: begin
					nextstate  <= S0;
            	PCSrc   = 2'd2;
					PCWrite   = 1'b1; 
				end
				
            default: nextstate  <= S0;
        endcase
    // output logic
    assign y = state;
    
endmodule
