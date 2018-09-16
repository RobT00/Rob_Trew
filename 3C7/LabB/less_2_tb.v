//Testbench code for 2-bit less than module
`timescale 1ns / 1ps
module less_2_tb;

	// Inputs
	reg [1:0] a;
	reg [1:0] b;

	// Outputs
	wire less;

	// Instantiate the Unit Under Test (UUT)
	less_2 uut (
		.a(a), 
		.b(b), 
		.less(less)
	);

	initial begin
		// Initialize Inputs
		a = 0;
		b = 0;
		//Nested repeat loops allows to cycle through all possible input combinations
		repeat(4) begin
			repeat(4) begin
				#100;
				b=b+1;
			end
			a=a+1;
		end  
	end
      
endmodule

