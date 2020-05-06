module somador(input logic a, input logic b, input logic cin, output logic cout, output logic s);
    logic p;
    assign p = a ^ b;
    assign s = a ^ b ^ cin;
    assign cout = (a & b) | (p & cin);
endmodule