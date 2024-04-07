// Clock Generator
module clockgen(clk);
output clk;
parameter period = 10;
parameter initial_value = 1'b0;
reg clk;
initial
begin
	clk = initial_value;
	// toggling clock after each half period
	forever
		#(period/2) clk = ~clk;
end
endmodule

// testbench
module tb;
wire clk10, clk14, clk16i;

// dut instantiations
clockgen clkgen10(clk10);		  // default period 10
clockgen #(14) clkgen14(clk14);   // period = 14
clockgen #(16) clkgen16i(clk16i); // period = 16
defparam clkgen16i.initial_value = 1'b1; // phase inverted starting initial value 1
initial
begin
	$dumpvars;
	$monitor($time, clk10, clk14, clk16i);
	#100 $finish;
end
endmodule
