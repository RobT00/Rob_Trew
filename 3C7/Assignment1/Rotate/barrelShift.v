module barrelShift( //8-bit Rotate Right Module
    input wire [7:0] sample, //Input 8-bit number
    input wire [2:0] move, //Amount to rotate by (bits)
    output wire [7:0] result //Output (rotated) 8-bit number
    );
	wire [7:0] s0, s1; //Temporary variables of same length as input/output, for use in multistage shift
	
	assign s0 = move[0] ? {sample[0], sample[7:1]} : sample; //if bit 0 (LSB) of move is 1, s0 = rotate sample (input) right by 1 (place LSB as MSB and shift all other bits right by 1), ELSE s0 = sample (no change
	assign s1 = move[1] ? {s0[1:0], s0[7:2]} : s0; //if bit 1 of move is 1, s1 = rotate s0 right by 2 (place 2 LSBs as MSBs and shift all other right bits by 2), ELSE s1 = s0
	assign result = move[2] ? {s1[3:0], s1[7:4]} : s1; //if bit 2 (MSB) of move is 1, result (output) = rotate s1 right by 4 (place 4 LSBs as MSBs and shift all other bits right by 4), ELSE, result (output) = s1 
endmodule
