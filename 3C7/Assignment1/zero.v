module zero( //A module that returns an 8-bit number that is all 0's
	//There is no need for inputs as the module will always output an 8-bit number of all 0's
    output wire [7:0] o //Output 8-bit number
    );
	 
	assign o = 8'b0000_0000; //Assign an 8-bit number of all 0's as the module output

endmodule
