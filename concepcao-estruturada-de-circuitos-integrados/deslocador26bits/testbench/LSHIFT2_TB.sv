module LSHIFT2_TB();
  logic [53:0] testvectors [2];
  logic clk, reset;
  logic [25:0] entrada;
  logic [27:0] saida;
  logic [27:0] expected_s;
  logic [32:0] vectornum, errors;
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
    clk = 1; #100; clk = 0; #5;
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