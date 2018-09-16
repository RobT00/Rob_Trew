`timescale 1ns / 1ps
//This testbench to to test the functionality of the 8bit_ripple_adder.v module 
module LabD_8bitRippleAdder_tb;
	// Inputs
	reg [7:0] x; //First 8-bit number to be added
	reg [7:0] y; //Second 8-bit number to be added
	reg c_in; //1 if there is a carry in to be simulated, otherwise 0

	// Outputs
	wire overflow; //1 if overflow is present, ELSE 0
	wire c_out; //1 if there is a carry out from the final bitwise additon (i.e. the MSBs addition in full_adder.v)
	wire [7:0] sum; //The returned 8-bit sum of x + y

	// Instantiate the Unit Under Test (UUT)
	\8bit_ripple_adder uut (
		.x(x), //The 8-bit quantity x
		.y(y), //The 8-vit quantity y
		.c_in(c_in), //The value of carry in
		.overflow(overflow), //Whether there is an overflow or not from the operation
		.c_out(c_out), //Whether there is a carry out or not from the operation
		.sum(sum) //The resultant 8-bit sum of the operation (i.e. x + y)
	);

	initial begin
		// Initialize Inputs
		x = 0;
		y = 0;
		c_in = 0;
		// '#100' symbolises waiting 100ns between test vectors, to allow the inputs to be set
		//test vector 1 (Both Positive & carry in LOW)
		x = 8'b01000000;
		y = 8'b00100000;
		c_in = 0; 
		#100; //Overflow = 0, Carryout = 0
		//Sum = 8'b0110_0000	
		//test vector 2 (Both Positive & carry in HIGH)
		x = 8'b01000000;
		y = 8'b00100000;
		c_in = 1;
		#100; //Overflow = 0, Carryout = 0
		//Sum = 8'b0110_0001
		//test vector 3 (Both Positive, Equal & carry in LOW)
		x = 8'b00010000;
		y = 8'b00010000;
		c_in = 0;
		#100; //Overflow = 0, Carryout = 0
		//Sum = 8'b0010_0000
		//test vector 4 (Both Positive, Equal & carry in HIGH)
		x = 8'b00010000;
		y = 8'b00010000;
		c_in = 1;
		#100; //Overflow = 0, Carryout = 0
		//Sum = 8'b0010_0001 
		//test vector 5 (Both Negative & carry in LOW)
		x = 8'b11000000;
		y = 8'b10100000;
		c_in = 0;
		#100; //Overflow = 1, Carryout = 1
		//Sum = 8'b0110_0000
		//test vector 6 (Both Negative & carry in HIGH)
		x = 8'b11000000;
		y = 8'b10100000;
		c_in = 1;
		#100; //Overflow = 1, Carryout = 1
		//Sum = 8'b0110_0001
		//test vector 7 (Both Negative, Equal & carry in LOW)
		x = 8'b10010000;
		y = 8'b10010000;
		c_in = 0;
		#100; //Overflow = 1, Carryout = 1
		//Sum = 8'b0010_0000
		//test vector 8 (Both Negative, Equal & carry in HIGH)
		x = 8'b10010000;
		y = 8'b10010000;
		c_in = 1;
		#100;	//Overflow = 1, Carryout = 1	
		//Sum = 8'b0010_0001 
		//test vector 9 (One Positive(x), One Negative(y) & carry in LOW)
		x = 8'b00001000;
		y = 8'b10100000;
		c_in = 0;
		#100; //Overflow = 0, Carryout = 0
		//Sum = 8'b1010_1000
		//test vector 10 (One Positive(x), One Negative(y) & carry in HIGH)
		x = 8'b00001000;
		y = 8'b10100000;
		c_in = 1;
		#100; //Overflow = 0, Carryout = 0
		//Sum = 8'b1010_1001
		//test vector 11 (One Positive(y), One Negative(x) & carry in LOW)
		x = 8'b10101000;
		y = 8'b00100010;
		c_in = 0;
		#100; //Overflow = 0, Carryout = 0
		//Sum = 8'b1100_1010
		//test vector 12 (One Positve(y), One Negative(x) & carry in HIGH)
		x = 8'b10101000;
		y = 8'b00100010;
		c_in = 1;
		#100; //Overflow = 0, Carryout = 0
		//Sum = 8'b1100_1011
		//test vector 13 (Both Zero & carry in LOW)
		x = 8'b00000000;
		y = 8'b00000000;
		c_in = 0;
		#100; //Overflow = 0, Carryout = 0		
		//Sum = 8'b0000_0000
		//test vector 14 (Both Zero & carry in HIGH)
		x = 8'b00000000;
		y = 8'b00000000;
		c_in = 1;
		#100; //Overflow = 0, Carryout = 0	
		//Sum = 8'b0000_0001 
		//test vector 15 (One Positive(x), One Negative(y) & carry in LOW)
		x = 8'b01111111;
		y = 8'b10000000;
		c_in = 0;
		#100; //Overflow = 0, Carryout = 0
		//Sum = 8'b1111_1111
		//test vector 16 (One Positive(x), One Negative(y) & carry in HIGH)
		x = 8'b01111111;
		y = 8'b10000000;
		c_in = 1;
		#100; //Overflow = 0, Carryout = 1
		//Sum = 8'b0000_0000
		//test vector 17 (Both Positive & carry in LOW)
		x = 8'b01111111;
		y = 8'b01111111;
		c_in = 0;
		#100; //Overflow = 1, Carryout = 0
		//Sum = 8'b1111_1110 
		//test vector 18 (Both Positive & carry in HIGH)
		x = 8'b01111111;
		y = 8'b01111111;
		c_in = 1;
		#100; //Overflow = 1, Carryout = 0
		//Sum = 8'b1111_1111 
	end
endmodule

