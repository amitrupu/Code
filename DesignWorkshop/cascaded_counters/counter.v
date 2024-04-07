module counter(clk, rst, load, q);
input clk, rst;
input [3:0] load;
output [3:0] q;
reg [3:0] q;
always @(posedge rst or posedge clk)
	if (rst)
		q <= load;
	else
		q <= q + 1;
endmodule

