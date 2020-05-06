module addac(input logic sel_0, input logic sel_1, input logic [3:0] a, input logic [3:0]acu, input logic clk,output logic [3:0]s, output logic [3:0] saida);

 logic [3:0] mux0, mux1, somador, supsup;
 logic cout;
 inv sup(a, supsup );
 mux sas01(a, supsup, sel_0, mux0);
 somador4 somador1(mux0, acu, sel_0, cout, somador);
 mux mux11(mux0, somador, sel_1, s);

 acc acc1(clk, s, acu, saida);
 
 endmodule 