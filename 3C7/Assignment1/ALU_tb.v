`timescale 1ns / 1ps
module ALU_tb; //Testbench for mini-ALU

	// Inputs
	reg [3:0] sel; //Input 4-bit number, will determine output (X)
	reg [7:0] A; //Input 8-bit number to be operated upon
	reg [7:0] B; //Input 8-bit number to be operated upon

	// Outputs
	wire [7:0] X; //Output 8-bit number

	// Instantiate the Unit Under Test (UUT)
	ALU uut (
		.sel(sel), 
		.A(A), 
		.B(B), 
		.X(X)
	);
	
	initial begin
		// Initialise Inputs
		//sel = 0;
		//A = 0;
		//B = 0;
		// Wait 100 ns for global reset to finish
		//#100;
      for (sel = 0; sel < 16; sel = sel + 1) begin
			//Both positive A < B
			A = 8'b0001_1000; //24
			B = 8'b0100_1000; //72
			#100;
			//Both positive A > B
			A = 8'b0100_1111; //79
			B = 8'b0000_0010; //2
			#100;
			//Both positive A = B
			A = 8'b0001_1100; //28
			B = 8'b0001_1100; //28
			#100;
			//Both negative A < B
			A = 8'b1000_0011; //-125
			B = 8'b1110_0010; //-30
			#100;
			//Both negative A > B
			A = 8'b1011_1111; //-65
			B = 8'b1000_1000; //-120
			#100;
			//Both negative A = B
			A = 8'b1001_0000; //-112
			B = 8'b1001_0000; //-112
			#100;
			//One positive one negative A < B
			A = 8'b1110_0111; //-25
			B = 8'b0011_1111; //63
			#100;
			//One positive one negative A > B
			A = 8'b0000_0011; //3
			B = 8'b1111_1101; //-3
			#100;			
			//Extreme (0)
			A = 8'b0000_0000;
			B = 8'b0000_0000;
			#100;
			//Extreme (1)
			A = 8'b1111_1111;
			B = 8'b1111_1111;
			#100;
		end
		$stop;
		//1 -> zero
		/*A = 8'b1000_0010;
		B = 8'b0100_0001;
		sel = 4'b0000;
		#100; //Output -> 8'b0000_0000
		//2 -> no_change
		sel = 4'b0001;
		#100; //Output -> A
		//3 -> minus, negated, \8bit_ripple_adder, bit_not, full_adder
		sel = 4'b0100;
		#100; //Output -> -B (i.e. 8'b1011_1111)
		//4 -> barrelShift
		sel = 4'b0101;
		#100; //Output -> A ROR(4) (i.e. 8'b0010_1000)
		//5 -> less_8, less_2, eq2, eq1
		sel = 4'b0111;
		#100; //Output -> A <= B (i.e. 8'b0000_0001)
		//6 -> bitw_xor
		sel = 4'b1000;
		#100; //Output -> A ^ B (i.e. 8'b1100_0011)
		//7 -> ones
		sel = 4'b1111;
		#100; //Output -> 8'b1111_1111
		//8 -> decision
		sel = 4'b1101;
		#100; //Output -> not mapped, default case (i.e. 8'b1010_0101)*/
		$stop;
	end

endmodule