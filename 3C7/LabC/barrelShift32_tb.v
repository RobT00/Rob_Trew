`timescale 1ns / 1ps
module barrelShift32_tb; //Testbench for Left and Right 32-bit Barrel Shifter
	// Inputs
	reg [31:0] sample; //Original 32-bit input
	reg [4:0] move; //Amount to rotate by (bits), 0-31
	reg direction; //Direction of rotation (1) RIGHT, or (0) LEFT
	// Outputs
	wire [31:0] result; //Rotated 32-bit number

	// Instantiate the Unit Under Test (UUT)
	barrelShift32 uut (
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
		sample = 32'h00000030; //Input Value
		move = 5'b00000; //Amount to rotate by -> 0
		direction = 0; //Direction of rotation -> LEFT
		#100; //Expected Output ->00000030
      //test vector 2
		sample = 32'h00000030; //Input Value
		move = 5'b00010; //Amount to rotate by -> 2
		direction = 1; //Direction of rotation -> RIGHT
		#100; //Expected Output ->0000000C
		//test vector 3
		sample = 32'h0000003A; //Input Value
		move = 5'b00001; //Amount to rotate by -> 1
		direction = 0; //Direction of rotation -> LEFT
		#100; //Expected Output ->00000074		
		//test vector 4
		sample = 32'h0000003A; //Input Value
		move = 5'b00000; //Amount to rotate by -> 0
		direction = 1; //Direction of rotation -> RIGHT
		#100; //Expected Output ->0000003A		
		//test vector 5
		sample = 32'h00000300; //Input Value
		move = 5'b00011; //Amount to rotate by -> 3
		direction = 0; //Direction of rotation -> LEFT
		#100; //Expected Output ->00001800
		//test vector 6
		sample = 32'h0000030A; //Input Value
		move = 5'b00100; //Amount to rotate by -> 4
		direction = 1; //Direction of rotation -> RIGHT
		#100; //Expected Output ->A0000030
		//test vector 7
		sample = 32'h00000AFF; //Input Value
		move = 5'b00111; //Amount to rotate by -> 7
		direction = 0; //Direction of rotation -> LEFT
		#100; //Expected Output ->00057F80
		//test vector 8
		sample = 32'h10000000; //Input Value
		move = 5'b10000; //Amount to rotate by -> 16
		direction = 1; //Direction of rotation -> RIGHT
		#100; //Expected Output ->00001000
		//test vector 9
		sample = 32'h0100000A; //Input Value
		move = 5'b10111; //Amount to rotate by -> 23
		direction = 0; //Direction of rotation -> LEFT
		#100; //Expected Output ->05008000
		$stop; //End Simulation/Testing
	end
      
endmodule

