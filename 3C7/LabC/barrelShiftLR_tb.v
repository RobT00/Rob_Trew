`timescale 1ns / 1ps
module barrelShiftLR_tb; //Testbench for Left and Right 8-bit Barrel Shifter
	// Inputs
	reg [7:0] sample; //Original 8-bit input
	reg [2:0] move; //Amount to rotate by (bits), 0-7
	reg direction; //Direction of rotation (1) RIGHT, or (0) LEFT
	// Outputs
	wire [7:0] result; //Rotated 8-bit number

	// Instantiate the Unit Under Test (UUT)
	barrelShiftLR uut (
		.sample(sample), 
		.move(move), 
		.direction(direction), 
		.result(result)
	);

	initial begin
		// Initialize Inputs
		sample = 0;
		move = 0;
		direction = 0;
		// test vector 1
		sample = 8'b00010010; //Input Value
		move = 3'b000; //Amount to rotate by -> 0
		direction = 0; //Direction of rotation -> LEFT
		#100; //Expected Output -> 00010010
      //test vector 2
		sample = 8'b00010010; //Input Value
		move = 3'b010; //Amount to rotate by -> 2
		direction = 1; //Direction of rotation -> RIGHT
		#100; //Expected Output -> 10000100		
		//test vector 3
		sample = 8'b00010010; //Input Value
		move = 3'b001; //Amount to rotate by -> 1
		direction = 0; //Direction of rotation -> LEFT
		#100; //Expected Output -> 00100100		
		//test vector 4
		sample = 8'b10010010; //Input Value
		move = 3'b000; //Amount to rotate by -> 0
		direction = 1; //Direction of rotation -> RIGHT
		#100; //Expected Output -> 10010010		
		//test vector 5
		sample = 8'b10010010; //Input Value
		move = 3'b011; //Amount to rotate by -> 3
		direction = 0; //Direction of rotation -> LEFT
		#100; //Expected Output -> 10010100
		sample = 8'b00010000; //Input Value
		move = 3'b100; //Amount to rotate by -> 4
		direction = 1; //Direction of rotation -> RIGHT
		#100; //Expected Output -> 00000001
		sample = 8'b10000000; //Input Value
		move = 3'b111; //Amount to rotate by -> 7
		direction = 0; //Direction of rotation -> LEFT
		#100; //Expected Output -> 01000000
		$stop; //End Simulation/Testing
	end
      
endmodule

