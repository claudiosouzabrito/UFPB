module flopr(input logic d,
            input logic reset,
            input logic  clk,
            output logic q);
// asynchronous reset
    always_ff @(posedge clk or posedge reset)
        if (reset) q <= 1'b0;
        else q <= d;
endmodule