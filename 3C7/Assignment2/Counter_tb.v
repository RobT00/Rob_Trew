`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: Trinity College Dublin
// Engineer: Warren Pretorius
// Create Date:   09:32:37 04/01/2018
// Design Name:   Counter
// Module Name:   Counter_tb.v
////////////////////////////////////////////////////////////////////////////////

module Counter_tb;

	// Create Testbench variables to match the inputs of Counter.v
	reg clk;
	reg reset;
	reg pedestrian;
	reg [1:0] currColour;

	// Create an output varibale to analyse the output from the UUT
	wire [3:0] counter_reg;

	// Instantiate the Unit Under Test (UUT)
	Counter uut (
		.second_clk(clk), 
		.reset(reset), 
		.pedestrian(pedestrian), 
		.currColour(currColour), 
		.counter_reg(counter_reg)
	);
	
	always
		#10 clk = ~clk;			// Oscillate the clock with a period of 20ns

	initial begin
		// Initialize Inputs
		clk = 0;
		reset = 1;
		pedestrian = 0;
		currColour = 2'b00;

		// Wait 100 ns for global reset to finish
		#100;
		
		reset = 0;
		#240;				// We are in red and the count should reset after 10 cycles  = 200ns
							// So wait for 340ns to observe this fully
							
		reset = 1;					// Manually reset counter to zero
		currColour = 2'b11;		// Change the colour of the light to Green
		#5;							// Wait a brief period (similar to button being pressed)
		reset = 0;					// Set reset low again
		#180;							// The count should reset after 160ns so make 180 to observe this fully
		
		reset = 1;					// Manually reset counter to zero
		currColour = 2'b01;		// Change the colour of the light to Amber
		#5;							// Wait a brief period (similar to button being pressed)
		reset = 0;					// Set reset low again
		#100;							// The count should reset after 80ns so make 100 to observe this fully					
		
		reset = 1;					// Manually reset counter to zero
		currColour = 2'b11;		// Change the colour of the light to Green
		#5;							// Wait a brief period (similar to button being pressed)
		reset = 0;					// Set reset low again
		
		#120;							// Send new signal before count resets
		pedestrian = 1;			// Send in pedestrian signal
		#20;							// Wait a brief period (similar to button being pressed)
		pedestrian = 0;			// Remove pedestrian signal
		#200;							// wait 200ns to make sure 8 cycles pass and count resets
		
		reset = 1;					// Manually reset counter to zero
		currColour = 2'b01;		// Change the colour of the light to Amber
		#5;							// Wait a brief period (similar to button being pressed)
		reset = 0;					// Set reset low again
		
		#20;							// Send new signal before count resets
		pedestrian = 1;			// Send in pedestrian signal
		#20;							// Wait a brief period (similar to button being pressed)
		pedestrian = 0;			// Remove pedestrian signal
		#110;							// wait 110ns to make sure 4 cycles pass and count resets
		
		reset = 1;					// Manually reset counter to zero
		currColour = 2'b00;		// Change the colour of the light to Red
		#5;							// Wait a brief period (similar to button being pressed)
		reset = 0;					// Set reset low again
		
		#100;							// Send new signal before count resets
		pedestrian = 1;			// Send in pedestrian signal
		#20;							// Wait a brief period (similar to button being pressed)
		pedestrian = 0;			// Remove pedestrian signal
		#240;							// wait 240ns to make sure 10 cycles pass and count resets
		
		$stop;

	end
      
endmodule

