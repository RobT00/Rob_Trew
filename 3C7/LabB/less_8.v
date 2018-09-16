//Code for 8-bit less than or equal to module
//2-bit less than and 2-bit comparator modules utilised
`timescale 1ns / 1ps
module less_8(
    input wire [7:0] i0,
    input wire [7:0] i1,
    output wire aeqltb
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
	
	//Terms process from left to right, i.e. least complex to most complex
	assign aeqltb = l3 | (e3 & l2) | (e3 & e2 & l1) | (e3 & e2 & e1 & l0) | (e3 & e2 & e1 & e0);

endmodule
