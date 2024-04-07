`define INIT 2'b00
`define D1   2'b01
`define D10  2'b10
`define D101 2'b11

module pattern_detector(clk, rst, data, detected);
input clk, rst, data;
output detected;
reg detected;
reg [1:0] state;

always @(posedge clk)
    if (rst)
    begin
        state <= `INIT;
        detected <= 1'b0;
    end
    else
    begin
        detected <= 1'b0;
        case (state)
            `INIT:
            if (data)
                state <= `D1;
            `D1:
            if (~data)
                state <= `D10;
            `D10:
            if (data)
                state <= `D101;
            else
                state <= `INIT;
            `D101:
            if (data)
            begin
                state <= `D1;
                detected <= 1'b1;
            end
            else
                state <= `D10;
        endcase
    end
endmodule
