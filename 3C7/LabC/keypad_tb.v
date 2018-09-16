`timescale 1ns / 1ps
module keypad_tb; //To test functionality of Keypad Module
	// Inputs
	reg row_a;
	reg row_b;
	reg row_c;
	reg row_d;
	reg col_x;
	reg col_y;
	reg col_z;
	// Outputs
	wire key_valid;
	wire [3:0] key_value;

	// Instantiate the Unit Under Test (UUT)
	keypad uut (
		.row_a(row_a), 
		.row_b(row_b), 
		.row_c(row_c), 
		.row_d(row_d), 
		.col_x(col_x), 
		.col_y(col_y), 
		.col_z(col_z), 
		.key_valid(key_valid), 
		.key_value(key_value)
	);

	initial begin
		// Initialise Inputs
		row_a = 0;
		row_b = 0;
		row_c = 0;
		row_d = 0;
		col_x = 0;
		col_y = 0;
		col_z = 0;

		//test vector 1
		//Not valid keypress -> 0
		//Expected output -> 14 (1110)
		row_a = 1;
		row_b = 1;
		row_c = 0;
		row_d = 0;
		col_x = 1;
		col_y = 0;
		col_z = 0;
		#100;
      //test vector 2
		//Valid keypress -> 1
		//Expected Output -> 7 (0111)
		row_a = 1;
		row_b = 0;
		row_c = 0;
		row_d = 0;
		col_x = 1;
		col_y = 0;
		col_z = 0;
		#100;
		//test vector 3
		//Not valid keypress -> 0
		//Expected Output -> 14 (1110)
		row_a = 0;
		row_b = 0;
		row_c = 0;
		row_d = 1;
		col_x = 1;
		col_y = 1;
		col_z = 0;
		#100;
		//test vector 4
		//Valid keypress -> 1
		//Expected Output -> 15 (1111)
		row_a = 0;
		row_b = 0;
		row_c = 0;
		row_d = 1;
		col_x = 0;
		col_y = 0;
		col_z = 1;
		#100;
		//test vector 5
		//Not valid keypress -> 0
		//Expected Output -> 14 (1110)
		row_a = 1;
		row_b = 1;
		row_c = 1;
		row_d = 1;
		col_x = 1;
		col_y = 1;
		col_z = 1;
		#100;
		//Stop the simulation/testing
		$stop;
	end
      
endmodule

