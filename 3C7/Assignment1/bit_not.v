module bit_not( //Sub-module for 'negated' to flip individual bits
    input org, //Input, the original bit
    output neg //Output, the flipped bit
    );
	reg temp; //for use in always block
	always@* begin
		if (org == 1) //If the bit is a '1' make it a '0'
			temp = 0;
		else 			  //If the bit is a '0' make it a '1'
			temp = 1;
	end
	assign neg = temp; //Flipped bit is assigned to output
endmodule
