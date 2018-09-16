`timescale 1ns / 1ps
module ALU(//top level module of mini-ALU
    input wire [3:0] sel, //A 4-bit number that will determine the module output
    input wire [7:0] A, //Input 8-bit number
    input wire [7:0] B, //Input 8-bit number
    output [7:0] X //Output 8-bit number (determined by sel)
    );
	//Temporary variables, one for each module output of the ALU
	 wire [7:0] a, b, c, d, e, f, g, h, i, j, k, l, m, n, o;
	//All modules are instantiated in the top level of the ALU
	 zero 					zeroA 	(.o(a));							//a
	 //Wire 'a' holds the output of the 'zero' module (i.e. 8'b0000_0000)
	 no_change 				sameA 	(.i(A), .o(b));						//b
	 //Wire 'b' holds the output of the 'no_change' module with input A (i.e. A)
	 no_change 				sameB 	(.i(B), .o(c));						//c
	 //Wire 'c' holds the output of the 'no_change' module with input B (i.e. B)
	 minus 					minA 	(.i(A), .o(d));						//d
	 //Wire 'd' holds the output of the 'minus' module with input A (i.e. the 2's complement representation of A; A -> -A) 
	 minus 					minB 	(.i(B), .o(e));						//e
	 //Wire 'e' holds the output of the 'minus' module with input B (i.e. the 2's complement representation of B; B -> -B)  
	 barrelShift			shftA	(.sample(A), .move(4), .result(f));	//f
	 //Wire 'g' holds the output of the 'barrelShift' module with input A (i.e. A rotated right by 4 bits)
	 barrelShift			shftB	(.sample(B), .move(4), .result(g));	//g
	 //Wire 'g' holds the output of the 'barrelShift' module with input B (i.e. B rotated right by 4 bits)
	 less_8					leqlt	(.i0(A), .i1(B), .aeqltb(h));		//h
	 //Wire 'h' holds the output of the 'less_8' module with inputs A and B (i.e. h will be 1 if A is less than or equal to B, otherwise it will be 0)
	 bitw_xor				xorAB	(.i1(A), .i2(B), .o(i));			//i
	 //Wire 'i' holds the output of the 'bitw_xor' module with inputs A and B (i.e. each bit of A is XOR'd with each bit of B)
	 negated 				negA	(.i(A), .o(j));						//j
	 //Wire 'j' holds the output of the 'negated' module with input A (i.e. A NOT)
	 negated				negB	(.i(B), .o(k));						//k
	 //Wire 'k' holds the output of the 'negated' module with input B (i.e. B nOT)
	 \8bit_ripple_adder		AminB	(.x(A), .y(e), .c_in(0), .sum(l));	//l
	 //Wire 'l' holds the output of the '\8bit_ripple_adder' module with inputs A and 'e' (as this is -B) (i.e. A - B or A + (-B))
	 \8bit_ripple_adder		ApluB	(.x(A), .y(B), .c_in(0), .sum(m));	//m
	 //Wire 'm' holds the output of the '\8bit_ripple_adder' module with inputs A and B (i.e. A + B)
	 ones					oneA	(.o(n));							//n
	 //Wire 'n; holds the output of the 'ones' module (i.e. 8'b1111_1111)
	 
	 decision 				res 	(.selection(sel), .a(a), .b(b), .c(c), .d(d), .e(e), .f(f), .g(g), .h(h), .i(i), .j(j), .k(k), .l(l), .m(m), .n(n), .result(o));
	 //Wire 'o' stores the output of the 'decision' module with inputs 'sel' and 'a' through 'n' (i.e. based on the value of 'sel' the appropriate result will be output)
	 assign X = o; //Assign the correct output (based on the value of sel)
endmodule
