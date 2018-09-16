module bitw_xor( //Bitwise (i.e. bit by bit) logical XOR operator (for 8-bit numbers)
    input wire [7:0] i1, //Input 1
	input wire [7:0] i2, //Input 2
    output wire [7:0] o //Output, result of XOR
    );
	reg [3:0] j; //Loop counter 4-bit number so can count to 8
	reg [7:0] temp; //For use in always block to store result of bitwise XOR
	always@* begin
		//Loop runs for 0 to 7, so that each bit in the 8-bit numbers are bitwise XOR'd and the result is held in 'temp'
		for (j = 0; j < 8; j = j + 1) begin
			temp[j] = i1[j] ^ i2[j];
		end
	end
	assign o = temp; //8-bit XOR result is assigned as the output of the module

endmodule
