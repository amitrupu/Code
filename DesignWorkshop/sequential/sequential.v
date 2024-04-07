module clockgen(clk);
output clk;
parameter period = 10;
parameter initial_value = 1'b0;
reg clk;
initial
begin
	clk = initial_value;
	forever #(period/2) clk = ~clk;
end
endmodule

module flipflop(clk, rst, d, q);
input clk, rst, d;
output q;
reg q;
always @(posedge rst or posedge clk)
	if (rst)
		q <= 1'b0;
	else
		q <= d;
endmodule

module flipflopb(clk, rst, d, q);
input clk, rst, d;
output q;
reg q;
always @(posedge rst or posedge clk)
	if (rst)
		q = 1'b0;
	else
		q = d;
endmodule

module latch(en, rst, d, q);
input en, rst, d;
output q;
reg q;
always @(rst or en or d)
	if (rst)
		q <= 1'b0;
	else if (en)
		q <= d;
endmodule

module tb;
wire fclk, clk;
reg rst, d;
wire qf, qfc, ql;

clockgen #(10) fclkgen(fclk);
clockgen #(20) clkgen(clk);

flipflop ff(clk, rst, d, qf);
flipflop ffc(clk, rst, qf, qfc);

latch l(clk, rst, d, ql);

initial
begin
	rst = 1'b0;
	d = 1'b0;
	#5 rst = 1'b1;
	#10 rst = 1'b0;
	@(negedge fclk) d = 1'b1;
	@(negedge fclk);
	@(posedge fclk) d = ~d;
	@(negedge fclk);
	@(negedge fclk);
	@(posedge fclk) d = ~d;
	@(negedge fclk);
	@(posedge fclk) d = ~d;
end
initial
begin
	$dumpvars;
	#200 $finish;
end
endmodule
