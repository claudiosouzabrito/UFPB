module addac_tb();
  logic [18:0] testvectors[2048];
  logic clk, reset;
  logic [3:0] c, d, saida1, saida2, saida1experado, saida2experado;
  logic a,b,e;
  logic [2047:0] vectornum, errors;
  addac DUV(a, b, c, d, e, saida1, saida2);

  initial begin
    $readmemb("../simulation/modelsim/tabela-addac.tv", testvectors);
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
    {a, b, c, d, e, saida1experado, saida2experado} = testvectors[vectornum];
  end// check results on falling edge of clk

  always @(negedge clk)
    if (~reset) begin // skip during reset
      if (saida1 !== saida1experado || saida2 !== saida2experado) begin // check result
        $display("Error: inputs = %b_%b_%b_%b_%b", {a}, {b}, {c}, {d}, {e});
        $display(" outputs = %b (%b experado), %b (%b experado)", saida1, saida1experado, saida2, saida2experado);
        errors = errors + 1;
      end else begin
        $display("OK: a: %b | b: %b | c: %b | d: %b | e: %b | saida1: %b (%b experado) | saida2: %b (%b experado)", a, b, c, d, e , saida1, saida1experado, saida2, saida2experado);
      end
      vectornum = vectornum + 1;
      if (vectornum == $size(testvectors)) begin
        $display("%d tests completed with %d errors",vectornum, errors);
        $finish;
      end
    end
endmodule