module ulactrl(input logic [5:0] funct,
              output logic [2:0] alucontrol,
              output logic addsub);
    always_comb
        case(funct) // R-type instructions
            6'b100000: alucontrol <= 3'b100; // add
            6'b100000: addsub <= 1'b0;
            6'b100010: alucontrol <= 3'b100; // sub
            6'b100010: addsub <= 1'b1;
            6'b100100: alucontrol <= 3'b000; // and
            6'b100101: alucontrol <= 3'b001; // or
            6'b100111: alucontrol <= 3'b011; // xor
            6'b100110: alucontrol <= 3'b010; // nor
            default: alucontrol <= 3'bxxx; // ???
        endcase
endmodule