//Testbench code for 8-bit less than or equal to module
`timescale 1ns / 1ps
module less_8_tb;

	// Inputs
	reg [7:0] i0;
	reg [7:0] i1;

	// Outputs
	wire aeqltb;

	// Instantiate the Unit Under Test (UUT)
	less_8 uut (
		.i0(i0), 
		.i1(i1), 
		.aeqltb(aeqltb)
	);
	integer i, j;
	initial begin
		// Initialize Inputs
		//Similar to 2-bit less than, using nested repeat loops to run through all possible combinations
		//This code is only commented so that only the for loops are run
		/*i0 = 0;
		i1 = 0;
		repeat(256) begin
			repeat(256) begin
				#100;
				i1=i1+1;
			end
			i0=i0+1;
		end*/
		
		//For waveform clarity, utilise for loop to generate inputs in a more easily waveform-readable fashion
		i0 = 0;
		//These nested for loops should always result in a LOGIC 0, as i0 > i1
		for ( i = 0; i < 256; i = i+1) begin
			i1 = 0;
			for (j = 0; j < i; j = j+1) begin
				#100;
				i1 = i1 + 1;
			end
			i0 = i0 + 1;
		end
		i0 = 0;
		//These nested for loops should always result in a LOGIC 1, as i0 <= i1
		for ( i = 0; i < 256; i = i+1) begin
			i1 = i;
			for (j = i; j < 256; j = j+1) begin
				#100;
				i1 = i1 + 1;
			end
			i0 = i0 + 1;
		end		   
	end
      
endmodule

