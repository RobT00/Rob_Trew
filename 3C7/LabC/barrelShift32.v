module barrelShift32( //32-bit Rotate Left or Right Module
    input wire [31:0] sample, //Input 32-bit number
    input wire [4:0] move, //Amount to rotate by (bits), 0-31
    input wire direction, //Direction of rotation, 1 == RIGHT, 0 == LEFT
    output reg [31:0] result //Output (rotated) 32-bit number
    );
	reg [31:0] s0, s1, s2, s3; //Temporary variables of same length as input/output, for use in multistage shift
	always@* begin
	if (direction == 1) begin //1 indicates, Rotate Right
		s0 = move[0] ? {sample[0], sample[31:1]} : sample; //if bit 0 (LSB) of move is 1, s0 = rotate sample (input) right by 1 (place LSB as MSB and shift all other bits right by 1), ELSE s0 = sample (no change)
		s1 = move[1] ? {s0[1:0], s0[31:2]} : s0; //if bit 1 of move is 1, s1 = rotate s0 right by 2 (place 2 LSBs as MSBs and shift all other right bits by 2), ELSE s1 = s0
		s2 = move[2] ? {s1[3:0], s1[31:4]} : s1; //if bit 2 of move is 1, s2 = rotate s1 right by 4 (place 4 LSBs as MSBs and shift all other right bits by 4), ELSE s2 = s1
		s3 = move[3] ? {s2[7:0], s2[31:8]} : s2; //if bit 3 of move is 1, s3 = rotate s2 right by 8 (place 8 LSBs as MSBs and shift all other right bits by 8), ELSE s3 = s2
		result = move[4] ? {s3[15:0], s3[31:16]} : s3; //if bit 4 (MSB) of move is 1, result (output) = rotate s3 right by 16 (place 16 LSBs as MSBs and shift all other bits right by 16), ELSE, result (output) = s3
		end
	else begin //ELSE (i.e. 0), Rotate Left
		s0 = move[0] ? {sample[30:0], sample[31]} : sample; //if bit 0 (LSB) of move is 1, s0 = rotate sample (input) left by 1 (place MSB as LSB and shift all other bits left by 1), ELSE s0 = sample (no change)
		s1 = move[1] ? {s0[29:0], s0[31:30]} : s0; //if bit 1 of move is 1, s1 = rotate s0 left by 2 (place 2 MSBs as LSBs and shift all other bits left by 2), ELSE s1 = s0
		s2 = move[2] ? {s1[27:0], s1[31:28]} : s1; //if bit 2 of move is 1, s2 = rotate s1 left by 4 (place 4 MSBs as LSBs and shift all other bits left by 4), ELSE s2 = s1
		s3 = move[3] ? {s2[23:0], s2[31:24]} : s2; //if bit 3 of move is 1, s3 = rotate s2 left by 8 (place 8 MSBs as LSBs and shift all other bits left by 8), ELSE s3 = s2
		result = move[4] ? {s3[15:0], s3[31:16]} : s3; //if bit 4 (MSB) of move is 1, result (output) = rotate s3 left by 16 (place 16 MSBs as LSBa and shift all other bits left by 16), ELSE result (output) = s3
		end
	end
endmodule
