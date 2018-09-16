module negated( //A module to perform a logical NOT on an 8-bit number (i.e. flip the bits; A -> A')
    input [7:0] i, //Input 8-bit number
    input [7:0] o //Output NOT'd 8-bit number
    );
	
	wire a, b, c, d, e, f, g, h; //8 temporary variables, each bit
	bit_not b_0 (.org(i[0]), .neg(a)); //Flip the (MSB) 7th bit
	bit_not b_1 (.org(i[1]), .neg(b)); //Flip the 6th bit
	bit_not b_2 (.org(i[2]), .neg(c)); //Flip the 5th bit
	bit_not b_3 (.org(i[3]), .neg(d)); //Flip the 4th bit
	bit_not b_4 (.org(i[4]), .neg(e)); //Flip the 3rd bit
	bit_not b_5 (.org(i[5]), .neg(f)); //Flip the 2nd bit
	bit_not b_6 (.org(i[6]), .neg(g)); //Flip the 1st bit
	bit_not b_7 (.org(i[7]), .neg(h)); //Flip the (LSB) 0th bit

	assign o = {h,g,f,e,d,c,b,a}; //Arrange the flipped bits (MSB to LSB) and assign as the module output
endmodule
