//Module to simulate an 8bit Ripple Adder, to allow for 2's complement addition and subtraction of 8-bit numbers
//Accepting two 8-bit inputs and a carry in value
//Utilises a Full Adder (full_adder.v)
//Returns resulting 8-bit sum, overflow and carry out
module \8bit_ripple_adder //The '\8' is an escaped identifier, as Verilog does not allow modules to being with a number, i.e. '8'
	(
    input [7:0] x, //First number to be added
    input [7:0] y, //Second number to be added
    input c_in, //1 if carry in (i.e. from previous operations) is present
    output overflow, //If there is an overflow from the resultant addition this is 1
    output c_out, //If there is a carry out from the resultant addition this is 1
    output [7:0] sum //The sum of the two added numbers (x plus y)
    );
	//Intermediate variables (wiring between units)
	wire s0, s1, s2, s3, s4, s5, s6, s7;
	wire c0, c1, c2, c3, c4, c5, c6, c7;
	//Using Full Adder to add 0th bits (LSBs), passing carry in (from testbench), returning sum of added bits and resulting and carry out
	FullAdder add_bit0 (.a(x[0]), .b(y[0]), .cin(c_in), .s(s0), .cout(c0));
	//Using Full Adder to add 1st bits, passing carry in from 0th bit addition (c_out from previous), returning sum of added bits and resulting carry out
	FullAdder add_bit1 (.a(x[1]), .b(y[1]), .cin(c0), .s(s1), .cout(c1));
	//Using Full Adder to add 2nd bits, passing carry in from 1st bit addition (c_out from previous), returning sum of added bits and resulting carry out	
	FullAdder add_bit2 (.a(x[2]), .b(y[2]), .cin(c1), .s(s2), .cout(c2));
	//Using Full Adder to add 3rd bits, passing carry in from 2nd bit addition (c_out from previous), returning sum of added bits and resulting carry out	
	FullAdder add_bit3 (.a(x[3]), .b(y[3]), .cin(c2), .s(s3), .cout(c3));
	//Using Full Adder to add 4th bits, passing carry in from 3rd bit addition (c_out from previous), returning sum of added bits and resulting carry out	
	FullAdder add_bit4 (.a(x[4]), .b(y[4]), .cin(c3), .s(s4), .cout(c4));
	//Using Full Adder to add 5th bits, passing carry in from 4th bit addition (c_out from previous), returning sum of added bits and resulting carry out	
	FullAdder add_bit5 (.a(x[5]), .b(y[5]), .cin(c4), .s(s5), .cout(c5));				
	//Using Full Adder to add 6th bits, passing carry in from 5th bit addition (c_out from previous), returning sum of added bits and resulting carry out	
	FullAdder add_bit6 (.a(x[6]), .b(y[6]), .cin(c5), .s(s6), .cout(c6));
	//Using Full Adder to add 7th bits (MSBs), passing carry in from 6th bit addition (c_out from previous), returning sum of added bits and resulting carry out	
	FullAdder add_bit7 (.a(x[7]), .b(y[7]), .cin(c6), .s(s7), .cout(c7));
	//Overflow determined by XOR between carry in and carry out of final addition
	assign overflow = c6 ^ c7;
	//Carry out is set to resulting carry out from final (MSB) addition
	assign c_out = c7;
	//Sum is defined as the arrangement of all resultant sums from MSB to LSB
	assign sum = {s7,s6,s5,s4,s3,s2,s1,s0};
endmodule
