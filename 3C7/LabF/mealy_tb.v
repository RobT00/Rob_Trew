`timescale 1ns / 1ps
//Testbench for Mealy FSM
module mealy_tb;
	localparam T = 20; //Set clock period to 20ns
	// Inputs
	reg clk; //Clock signal input
	reg reset; //Reset signal input
	reg bitstream; //Bitstream input, will be searched for "101"

	// Outputs
	wire tick; //Output from FSM, if sequence ("101") is found
	
	// Instantiate the Unit Under Test (UUT)
	mealy uut (
		.clk(clk), 
		.reset(reset), 
		.bitstream(bitstream), 
		.tick(tick)
	);
	reg[15:0] bit_reg = 16'b1010_0010_0110_1110; //Register in testbench, bitstream passed to FSM
	integer i; //Integer in testbench for use in 'for loop'
	
	//Block for controlling reset signal to FSM
	initial begin
		reset = 1; //Set reset HIGH at start of testing
		#((3*T)/2);
		reset = 0;
		//Set reset LOW for period during testing of testing
		#((9*T)/4);
		reset = 1;
		#((8*T)/5);
		reset = 0;
		//After testing reset again, set LOW for remainder of testing
	end
	
	//Block for controlling bitsream to FSM
	always begin
		//Loop through sequence of bits, fed one at a time to FSM
		for ( i = 0; i < 16; i = i + 1 ) begin 
			bitstream = bit_reg[i];
			#T; //Pause for 1 clock cycle so bit can be read
		end
	end
	
	//Block for controlling clock signal to FSM
	always begin
		clk = 0; //Start with clock at 0
		#(T/2); //Wait half a period
		clk = 1; //Set clock to 1
		#(T/2); //Wait half a period, repeat
	end
   
endmodule

