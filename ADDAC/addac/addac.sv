module addac(input logic sel_0, input logic sel_1, input logic a, input logic acu, input logic clk,output logic s, output logic saida);

 logic mux0, mux1, somador, cout, supsup;
 inv sup(a, supsup );
 mux sas01(a, supsup, sel_0, mux0);
 somador somador1(mux0, acu, sel_0, cout, somador);
 mux mux11(mux0, somador, sel_1, s);

 acc acc1(clk, s, acu, saida);
 
 endmodule 