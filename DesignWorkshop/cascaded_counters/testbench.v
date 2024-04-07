module testbench;
wire clk;
wire [3:0] q;
reg rst;
integer i;

clockgen clkgen(clk);
cascaded_counter inst(clk, rst, 4'b0, q);

initial
begin
	$dumpvars;
	rst = 1'b0;
	#5 rst = 1'b1;
	for (i = 0; i < 2; i = i+1)
		@(posedge clk);
	rst = 1'b0;
	#1000 $finish;
end
endmodule
