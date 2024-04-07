module cascaded_counter(clk, rst, load, q);
input clk, rst;
input [3:0] load;
output [3:0] q;
wire [3:0] temp;
counter count1(clk, rst, load, temp);
counter count2(temp[3], rst, load, q);
endmodule

