`timescale 1ns / 1ps
//Test Bench for traffic lights solution 
module traffic_lights_tb;
	// Inputs
	reg clk; //Clock signal to module being tested
	reg reset; //Reset signal to module being tested
	reg pedestrian; //Pedestrian signal to module being tested
	// Outputs
	wire Red; //Red light output
	wire Amber; //Amber light output
	wire Green; //Green light output
	wire Flag; //Signal for being in "Pedestrian" mode
	// Instantiate the Unit Under Test (UUT)
	localparam T = 20; //20ns period -> 50Mhz
	//Unit under test
	traffic_lights uut (
		.second_clk(clk), //Bypassing clock module for testing purposes (quicker) 
		.reset(reset), 
		.pedestrian(pedestrian), 
		.Red(Red), 
		.Amber(Amber), 
		.Green(Green), 
		.Flag(Flag)
	);
	
	//Clock
	always begin
		clk = 1;
		#(T/2); //50% load cycle
		clk = 0;
		#(T/2);
	end
	
	//Reset
	initial begin
      reset = 1;
		#(2*T);
		reset = 0;
		#(9*T);
		reset = 1;
		#(2*T);
		reset = 0;
		#(27*T);
		reset = 1;
		#(2*T);
		reset = 0;
	end
	
	//Pedestrian
	initial begin
		pedestrian = 0;
		#(25*T);
		pedestrian = 1;
		#(3*T);
		pedestrian = 0;
	end
endmodule
