module no_change( //Module that returns the inputted 8-bit number
    input [7:0] i, //Input 8-bit number
    output [7:0] o //Output 8-bit number
    );
	assign o = i; //Assign the input as the output (i.e. return the input number with no changes)

endmodule
