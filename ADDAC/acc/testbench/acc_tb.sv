module acc_tb();
  logic [3:0] testvectors[8];
  logic clk, reset;
  logic a, b, c, saida, saidaexperado;
  logic [31:0] vectornum, errors;
  acc DUV(a, b, c, saida);

  initial begin
    $readmemb("../../ADDAC-antes/goldenmodel/tabela-acc.tv", testvectors);
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
    {a, b, c, saidaexperado} = testvectors[vectornum];
  end// check results on falling edge of clk

  always @(negedge clk)
    if (~reset) begin // skip during reset
      if (saida !== saidaexperado) begin // check result
        $display("Error: inputs = %b_%b_%b", {a}, {b}, {c});
        $display(" outputs = %b (%b experado)", saida, saidaexperado);
        errors = errors + 1;
      end else begin
        $display("OK: a: %b | b: %b | c: %b | saida: %b (%b experado)", a, b, c, saida, saidaexperado);
      end
      vectornum = vectornum + 1;
      if (vectornum == $size(testvectors)) begin
        $display("%d tests completed with %d errors",vectornum, errors);
        $finish;
      end
    end
endmodule