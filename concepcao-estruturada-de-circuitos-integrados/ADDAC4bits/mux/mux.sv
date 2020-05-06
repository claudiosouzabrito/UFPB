module mux(input logic [3:0] a, input logic [3:0] b, input logic c, output logic [3:0] saida);
    assign saida = c ? b : a;
endmodule