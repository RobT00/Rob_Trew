module minus //Module to make an 8-bit number negative (i.e. 8'b0000_0001 -> 8'b1111_1111)
	(
    input [7:0] i, //input 8-bit number
    output [7:0] o //output 8-bit number
    );
	 wire [7:0] temp1, temp2; //Temporary variables for operation
	 negated neg (.i(i), .o(temp1)); //A module that will NOT an 8-bit number (i.e. flight all the bits; A -> A')
	\8bit_ripple_adder add1 (.x(temp1), .y(1), .c_in(0), .sum(temp2)); //8-bit ripple adder, will add 1 (8'b0000_0001) to the number, resulting in the 2's complement form
	assign o = temp2; //Assign the 2's complement number as the output for the module
endmodule
