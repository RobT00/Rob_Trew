module ones( //A module that returns an 8-bit number that is all 1's
    //There is no need for inputs as the module will always output an 8-bit number of all 1's
	output [7:0] o //Output 8-bit number
    );
	 
	assign o =8'b1111_1111; //Assign an 8-bit number of all 1's as the module output

endmodule
