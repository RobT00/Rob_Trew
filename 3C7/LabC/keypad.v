module keypad(
	 //Inputs
    input wire row_a,
    input wire row_b,
    input wire row_c,
    input wire row_d,
    input wire col_x,
    input wire col_y,
    input wire col_z,
	 //Outputs
    output wire key_valid, //1 if a valid keypress
    output wire[3:0] key_value //Value of keypress
    );
	//Variables for use in always block
	reg [3:0] key;
	reg valid;
	always @*
	begin
	valid = 1; //Start by assuming valid keypress
	case({row_a, row_b, row_c, row_d, col_x, col_y, col_z}) //Start of case statement, all rows and columns as inputs
		7'b1000100: key = 4'b0111; //7
		7'b1000010: key = 4'b1000; //8
		7'b1000001: key = 4'b1001; //9
		7'b0100100: key = 4'b0100; //4
		7'b0100010: key = 4'b0101; //5
		7'b0100001: key = 4'b0110; //6
		7'b0010100: key = 4'b0001; //1
		7'b0010010: key = 4'b0010; //2
		7'b0010001: key = 4'b0011; //3
		7'b0001100: key = 4'b0000; //0
		7'b0001010: key = 4'b1010; //# -> 10
		7'b0001001: key = 4'b1111; //* -> 15
		default: //If no case input matches, invalid keypress
		begin
			key = 4'b1110; //error -> 14, indicates invalid keypress also
			valid = 0;
		end
		endcase
	//Check if valid key press
	if (valid != 0) //Only checked if still considered a valid keypress (will be 0 if default case triggered)
		valid = (((row_a+row_b+row_c+row_d)==3'b001)
						&& ((col_x+col_y+col_z)==3'b001));
	end
	//Keypad outputs
	assign key_valid = valid;
	assign key_value = key;
endmodule
