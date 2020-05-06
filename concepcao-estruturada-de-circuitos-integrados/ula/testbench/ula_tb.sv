`timescale 1 ns / 1 ns
module ula_tb();
  logic [104:0] testvectors[28];
  logic clk, reset ;
  logic [1:0] aluop;
  logic [5:0] funct; 
  logic [31:0] saida1, saida1experado, a, b;
  logic [31:0] vectornum, errors;
  uladec DUV( funct, aluop, a, b, saida1);
  initial begin
    $readmemb("ula.tv", testvectors);
    vectornum = 0;
    errors = 0;
    reset = 1;
    #27;
    reset = 0;
  end
  always begin
    clk = 1; #10; clk = 0; #5;
  end
  always @(posedge clk) begin
    #1
    {aluop, funct, a, b, saida1experado} = testvectors[vectornum];
  end// check results on falling edge of clk~
  always @(negedge clk)
    if (~reset) begin // skip during reset
      if (saida1 !== saida1experado) begin // check result
        $display("Error: aluop = %b, funct = %b, a = %b, b = %b", {aluop}, {funct}, {a},{b});
        $display("aluout = %b (%b experado)", saida1, saida1experado);
        errors = errors + 1;
      end else begin
        $display("OK: aluop = %b, funct = %b, a = %b, b = %b | aluout: %b (%b experado)", aluop, funct, a, b, saida1, saida1experado);
      end
      vectornum = vectornum + 1;
      if (vectornum == $size(testvectors)) begin
        $display("%d tests completed with %d errors",vectornum, errors);
        $finish;
      end
    end
endmodule