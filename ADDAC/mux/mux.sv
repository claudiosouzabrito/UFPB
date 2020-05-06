module mux(input logic a, input logic b, input logic c, output logic saida);
    assign saida = c ? b : a;
endmodule