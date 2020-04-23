`timescale 1 ns / 1 ns
module flopr_tb();
  logic [3:0] testvectors[8];
  logic clk, reset, resete, clock;
  logic d, saida, saidaexperado;
  logic [31:0] vectornum, errors;
  flopr DUV(d, resete, clock, saida);

  initial begin
    $readmemb("flopr.tv", testvectors);
	 d = 1'b0;
	 saida = 1'b0;
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
    {d, resete, clock, saidaexperado} = testvectors[vectornum];
  end// check results on falling edge of clk

  always @(negedge clk)
    if (~reset) begin // skip during reset
      if (saida !== saidaexperado) begin // check result
        $display("Error: inputs = %b_%b_%b", {d}, {resete}, {clock});
        $display(" outputs = %b (%b experado)", saida, saidaexperado);
        errors = errors + 1;
      end else begin
        $display("OK: clock: %b | resete: %b | d: %b | saida: %b (%b experado)", d, resete, clock, saida, saidaexperado);
      end
      vectornum = vectornum + 1;
      if (vectornum == $size(testvectors)) begin
        $display("%d tests completed with %d errors",vectornum, errors);
        $finish;
      end
    end
endmodule