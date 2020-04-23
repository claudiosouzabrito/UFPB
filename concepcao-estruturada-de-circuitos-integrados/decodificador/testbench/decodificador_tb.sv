`timescale 1 ns / 1 ns
module decodificador_tb();
  logic [36:0]testvectors[32];
  logic clk, reset;
  logic [4:0]a; 
  logic [31:0]saida, saidaexperado;
  logic [31:0] vectornum, errors;
  decodificador DUV(a, saida);

  initial begin
    $readmemb("deco.tv", testvectors);
    vectornum = 0;
    errors = 0;
    reset = 1;
    #27;
    reset = 0;
  end

  always begin
    clk = 1; #100; clk = 0; #5;
  end

  always @(posedge clk) begin
    #1
    {a, saidaexperado} = testvectors[vectornum];
  end// check results on falling edge of clk

  always @(negedge clk)
    if (~reset) begin // skip during reset
      if (saida !== saidaexperado) begin // check result
        $display("Error: inputs = %b", {a});
        $display(" outputs = %b (%b experado)", saida, saidaexperado);
        errors = errors + 1;
      end else begin
        $display("OK: a: %b | saida: %b (%b experado)", a, saida, saidaexperado);
      end
      vectornum = vectornum + 1;
      if (vectornum == $size(testvectors)) begin
        $display("%d tests completed with %d errors",vectornum, errors);
        $finish;
      end
    end
endmodule