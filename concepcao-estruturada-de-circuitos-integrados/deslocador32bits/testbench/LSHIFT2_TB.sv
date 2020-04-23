`timescale 1 ns / 1 ns
module LSHIFT2_TB();
  logic [63:0] testvectors [65536];
  logic clk, reset;
  logic [31:0] entrada;
  logic [31:0] saida;
  logic [31:0] expected_s;
  logic [31:0] vectornum, errors;
  LSHIFT2 DUV(.entrada(entrada), .saida(saida));
  initial begin
    $readmemb("lshift2.tv", testvectors);
    vectornum = 0;
    errors = 0;
    reset = 1;
    #27;
    reset = 0;
  end
  always begin
    clk = 1; #1000; clk = 0; #500;
  end	
  always @(posedge clk) begin
    #1
    {entrada, expected_s} = testvectors[vectornum];
  end
  always @(negedge clk)
    if (~reset) begin
      if ( (saida !== expected_s) ) begin
        $display("Error: inputs = %b", entrada);
        $display(" s = %b (%b expected)", saida, expected_s);
        errors = errors + 1;
      end else begin
        $display("OK: a: %b | saida: %b (%b expected)", entrada, saida, expected_s);
      end
      vectornum = vectornum + 1;
      if (vectornum == $size(testvectors)) begin
        $display("%d tests completed with %d errors",vectornum, errors);
		$stop;
	end
    end
endmodule