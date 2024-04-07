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
