module somador4(input logic [3:0]a, input logic [3:0]b, input logic cin, output logic cout, output logic [3:0]s);
    logic cout1;
    logic cout2;
    logic cout3;
    somador som1(a[0], b[0], cin, cout1, s[0]);
    somador som2(a[1], b[1], cout1, cout2, s[1]);
    somador som3(a[2], b[2], cout2, cout3, s[2]);
    somador som4(a[3], b[3], cout3, cout, s[3]);
endmodule