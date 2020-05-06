module acc_tb();
  logic [12:0] testvectors[512];
  logic clk, reset;
  logic [3:0] a, b, saida, saidaexperado;
  logic c;
  logic [511:0] vectornum, errors;
  acc DUV(c, a , b , saida);

  initial begin
    $readmemb("../simulation/modelsim/tabela-acc.tv", testvectors);
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
    {c, a, b, saidaexperado} = testvectors[vectornum];
  end// check results on falling edge of clk

  always @(negedge clk)
    if (~reset) begin // skip during reset
      if (saida !== saidaexperado) begin // check result
        $display("Error: inputs = %b_%b_%b", {c}, {a}, {b});
        $display(" outputs = %b (%b experado)", saida, saidaexperado);
        errors = errors + 1;
      end else begin
        $display("OK: c: %b | a: %b | b: %b | saida: %b (%b experado)", c, a, b, saida, saidaexperado);
      end
      vectornum = vectornum + 1;
      if (vectornum == $size(testvectors)) begin
        $display("%d tests completed with %d errors",vectornum, errors);
        $finish;
      end
    end
endmodule