`timescale 1 ns / 1 ns
module mips_tb();
  logic [35:0] testvectors[105];
  logic clk, reset, clock, resete, IorD, AluSrcA, IRWrite, PCWrite, RegDst, MemtoReg, RegWrite,
  MemWrite, Branch;
  logic [1:0] AluSrcB, ALUOp, PCSrc;
  logic [5:0] opcode, funct; 
  logic [6:0] saida, saidaexperado;
  logic [31:0] vectornum, errors;
  mips DUV(resete, clock, opcode, funct, saida, IorD, AluSrcA, IRWrite, PCWrite, RegDst, MemtoReg,
  RegWrite, MemWrite, Branch, AluSrcB, ALUOp, PCSrc);
  initial begin
    $readmemb("saida.tv", testvectors);
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
    {resete, clock, opcode, funct, saidaexperado, IorD, AluSrcA, IRWrite, PCWrite, RegDst, MemtoReg,
    RegWrite, MemWrite, Branch, AluSrcB, ALUOp, PCSrc} = testvectors[vectornum];
  end// check results on falling edge of clk~
  always @(negedge clk)
    if (~reset) begin // skip during reset
      if (saida !== saidaexperado) begin // check result
        $display("Error: reset = %b, clock = %b, opcode = %b ,e funct = %b, IorD = %b, AluSrcA = %b, IRWrite = %b, PCWrite = %b, RegDst = %b, MemtoReg = %b, RegWrite = %b, MemWrite = %b, Branch = %b, AluSrcB = %b, ALUOp = %b, PCSrc = %b", {resete}, {clock},  {opcode}, {funct}, {IorD}, {AluSrcA}, {IRWrite}, {PCWrite},{RegDst}, {MemtoReg}, {RegWrite}, {MemWrite}, {Branch}, {AluSrcB}, {ALUOp}, {PCSrc});
        $display(" output = %b (%b experado)", saida, saidaexperado);
        errors = errors + 1;
      end else begin
        $display("OK: reset: %b, clock: %b, opcode: %b, funct: %b, IorD = %b, AluSrcA = %b, IRWrite = %b, PCWrite = %b, RegDst = %b, MemtoReg = %b, RegWrite = %b, MemWrite = %b, Branch = %b, AluSrcB = %b, ALUOp = %b, PCSrc = %b | saida: %b (%b experado)", resete, clock, opcode, funct, IorD, AluSrcA, IRWrite, PCWrite, RegDst, MemtoReg, RegWrite, MemWrite, Branch, AluSrcB, ALUOp, PCSrc, saida, saidaexperado);
      end
      vectornum = vectornum + 1;
      if (vectornum == $size(testvectors)) begin
        $display("%d tests completed with %d errors",vectornum, errors);
        $finish;
      end
    end
endmodule