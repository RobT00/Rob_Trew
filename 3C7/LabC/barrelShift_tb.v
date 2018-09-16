`timescale 1ns / 1ps
module barrelShift_tb; //Test 8-bit Rotate Right
	// Inputs
	reg [7:0] sample; //Original 8-bit input
	reg [2:0] move; //Amount to rotate by (bits), 0-7
	// Outputs
	wire [7:0] result; //Rotated 8-bit number

	// Instantiate the Unit Under Test (UUT)
	barrelShift uut (
		.sample(sample), 
		.move(move), 
		.result(result)
	);

	initial begin
		// Initialize Inputs
		sample = 0;
		move = 0;
		// test vector 1
		sample = 8'b00010010; //Input Value
		move = 3'b000; //Amount to rotate by -> 0
		#100; //Expected Output -> 00010010
		//test vector 2
		sample = 8'b00010010; //Input value
		move = 3'b010; //Amount to rotate by -> 2
		#100; //Expected Output -> 10000100		
		//test vector 3
		sample = 8'b00010010; //Input value
		move = 3'b001; //Amount to rotate by -> 1
		#100; //Expected Output -> 00001001		
		//test vector 4
		sample = 8'b10010010; //Input value
		move = 3'b000; //Amount to rotate by -> 0
		#100; //Expected Output -> 10010010		
		//test vector 5
		sample = 8'b10010010; //Input value
		move = 3'b011; //Amount to rotate by -> 3
		#100; //Expected Output -> 01010010
		sample = 8'b00010000; //Input value
		move = 3'b100; //Amount to rotate by -> 4
		#100; //Expected Output -> 00000001
		sample = 8'b10000000; //Input value
		move = 3'b111; //Amount to rotate by -> 7
		#100; //Expected Output -> 00000001
		$stop; //End Simulation/Testing
	end
      
endmodule

