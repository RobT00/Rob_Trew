module decision( //A helper module for 'ALU' to use a case statement to decide on the appropriate module output
    input [3:0] selection, //INput 4-bit number to decide output (sel)
    input [7:0] a, //Input, output of 'zero' module (8'b0000_0000)
    input [7:0] b, //Input, output of 'no_change' module (A)
    input [7:0] c, //Input, output of 'no_change' module (B)
    input [7:0] d, //Input, output of 'minus' module (-A)
	input [7:0] e, //Input, output of 'minus' module (-B)
    input [7:0] f, //Input, output of 'barrelShift' module (A ROR(4)))
    input [7:0] g, //Input, output of 'barrelShift' module (B ROR(4)))
    input [7:0] h, //Input, output of 'less_8' module (A <= B)
    input [7:0] i, //Input, output of 'bitw_xor' module (A XOR B)
    input [7:0] j, //Input, output of 'negated' module (A')
	input [7:0] k, //Input, output of 'negated' module (B')
    input [7:0] l, //Input, output of '\8bit_ripple_adder' module (A - B or A + (-B))
    input [7:0] m, //Input, output of '\8bit_ripple_adder' module (A + B)
	input [7:0] n, //Input, output of 'ones' module (8'b1111_1111)
    output reg [7:0] result //Output, resultant outcome of case statement, decided by 'selection'
    );
	always@* begin
		case(selection)
			4'b0000: result = a;
			4'b0001: result = b;
			4'b0010: result = c;
			4'b0011: result = d;
			4'b0100: result = e;
			4'b0101: result = f;
			4'b0110: result = g;
			4'b0111: result = h;
			4'b1000: result = i;
			4'b1001: result = j;
			4'b1010: result = k;
			4'b1011: result = l;
			4'b1100: result = m;
			4'b1111: result = n;
			default: result = 8'b1010_0101; //Default statement, for values of 'selection' that do not correspond to an ALU function, this 8-bit number will be output
		endcase
	end
endmodule
