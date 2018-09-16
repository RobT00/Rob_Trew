`timescale 1ns / 1ps
module LFSR_tb; //Testbench for LFSR module
	// Inputs
	reg clk; //Clock Signal
	reg reset; //Reset Signal
	reg [15:0]count_reg; //Count of total cycles (independent of reset)
	// Outputs
	wire lfsr_out; //Output from LFSR, MSB
	wire max_tick; //Output from LFSR, if seed if repeated
	wire [13:0]count_out; //Cycle count (reset dependent) from LFSR
	localparam T = 0.001; //clock period (ns)
	// Instantiate the Unit Under Test (UUT)
	LFSR uut (
		.clk(clk), 
		.reset(reset), 
		.lfsr_out(lfsr_out),
		.max_tick(max_tick),
		.count_out(count_out)
	);
	initial begin
		count_reg = 0; //Start the total cycle count at 0
	end
	
	always begin //Will run repeatedly
		clk = 1; //Set clock to 1
		#(T/2); //Wait half a cycle
		clk = 0; //Set clock to 0
		#(T/2); //Wait half a cycle
		count_reg = count_reg + 1; //Increment total count
		if (count_reg > 16389) //Total count to end testbench
			$finish; //End Testbench
	end //Repeat

	initial begin //Run once, rest high at start
		reset = 1; //Set reset to 1
		#(10*T); //Keep high for 10 cycles
		reset = 0; //Set reset low
	end //Does not repeat
	   
endmodule

