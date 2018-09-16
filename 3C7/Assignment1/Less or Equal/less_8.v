//Code for 8-bit less than or equal to module
//2-bit less than and 2-bit comparator modules utilised
`timescale 1ns / 1ps
module less_8(
    input wire [7:0] i0,
    input wire [7:0] i1,
    output wire [7:0]aeqltb
    );
	
	wire l0, l1, l2, l3;
	wire e0, e1, e2, e3;
	//Checking each two bit pair (less than)
	less_2 l_bit10 (.a(i0[1:0]), .b(i1[1:0]), .less(l0));
	less_2 l_bit32 (.a(i0[3:2]), .b(i1[3:2]), .less(l1));
	less_2 l_bit54 (.a(i0[5:4]), .b(i1[5:4]), .less(l2));
	less_2 l_bit76 (.a(i0[7:6]), .b(i1[7:6]), .less(l3));
	//Again checking each two bit pair (equal)
	eq2 eq_bit10 (.a(i0[1:0]), .b(i1[1:0]), .aeqb(e0));
	eq2 eq_bit32 (.a(i0[3:2]), .b(i1[3:2]), .aeqb(e1));
	eq2 eq_bit54 (.a(i0[5:4]), .b(i1[5:4]), .aeqb(e2));
	eq2 eq_bit76 (.a(i0[7:6]), .b(i1[7:6]), .aeqb(e3));
	//Checking 2's complement **this is an addition to the previous module**
	reg out_reg; //For use in always block
	always@* begin
		if (i0[7] == 1 && i1[7] == 0) //If i0 is negative and i1 is positive, it is always less than
			out_reg = 1;
		else if (i0[7] == 0 && i1[7] == 1) //If i0 is positive and i1 is negative, it is always greater than
			out_reg = 0;
		else //Otherwise check terms from least complex to most complex for less than or equal to (as before)
			out_reg = l3 | (e3 & l2) | (e3 & e2 & l1) | (e3 & e2 & e1 & l0) | (e3 & e2 & e1 & e0);
	end
	
	assign aeqltb = out_reg; //Assign the output of the module from 'out_reg'

endmodule
