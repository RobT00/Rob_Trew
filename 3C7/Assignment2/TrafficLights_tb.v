`timescale 100ms / 10ms

////////////////////////////////////////////////////////////////////////////////
// Company: Trinity College Dublin
// Engineer: Warren Pretorius
// Create Date:   09:29:30 03/29/2018
// Design Name:   TrafficLights
// Module Name:   TrafficLights_tb.v
////////////////////////////////////////////////////////////////////////////////

module TrafficLights_tb;

	// Inputs
	reg clk;
	reg reset;
	reg pedestrian;

	// Outputs
	wire Red;
	wire Green;
	wire Amber;
	wire LED0, LED1, LED2, LED3, LED4, LED5, LED6, LED7;

	// Instantiate the Unit Under Test (UUT)
	TrafficLights uut (
		.clk(clk), 
		.reset(reset), 
		.pedestrian(pedestrian), 
		.Red(Red), 
		.Green(Green), 
		.Amber(Amber),
		.LED0(LED0),
		.LED1(LED1),
		.LED2(LED2),
		.LED3(LED3),
		.LED4(LED4),
		.LED5(LED5),
		.LED6(LED6),
		.LED7(LED7)
	);
	
	always
		#10 clk = ~clk;
	
	initial begin
		// Initialize Inputs
		clk = 0;
		reset = 1;
		pedestrian = 0;

		// Wait 100 ns for global reset to finish
		#100;
		reset = 0;
		
		#1000;
		reset = 1;
		#40;
		reset = 0;
		#400;
		pedestrian = 1;
		#10;
		pedestrian = 0;
		#280;
		pedestrian = 1;
		#10;
		pedestrian = 0;
		#300;
		reset = 1;
		#10;
		reset = 0;
		#1000;
		
		$stop;

	end
      
endmodule

