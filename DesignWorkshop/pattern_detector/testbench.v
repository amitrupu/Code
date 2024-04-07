module testbench;
wire clk, detected;
reg rst, data;
integer i;

clockgen clkgen(clk);
pattern_detector dut(clk, rst, data, detected);

initial
begin
	$dumpvars;
	rst = 1'b0;
	data = 1'b0;
	#5 rst = 1'b1;
	#20 rst = 1'b0;
	#1000 $finish;
end

always @(negedge clk)
	data <= $random % 2;

endmodule
