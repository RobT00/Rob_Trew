`timescale 1ns / 10ps
module d_ff_tb; //Testbench for D Type Flip-Flop
	// Inputs
	reg clk; //Clock Signal
	reg reset; //Reset Signal
	reg d; //Input Data
	// Outputs
	wire q; //Output of D Type Flip-FLop
	//Declarations
	localparam T = 40; //clock period (ns)
	// Instantiate the Unit Under Test (UUT)
	d_ff_reset uut (
		.clk(clk), 
		.reset(reset), 
		.d(d), 
		.q(q)
	);

	always begin //Block will repeat
		// Initialize Inputs
		clk = 1; //Set clock high
		#(T/2); //Wait half a cycle
		clk = 0; //Set clock low
		#(T/2); //Wait half a cycle
	end //Repeat

	initial begin //Values based off required behaviour in brief
		reset = 1; //Set Reset high
		#(T + (3*T)/4); //Wait specified time
		reset = 0; //Set reset low
		#(4*T); //Wait specified amount of time
		reset = 1; //Set reset high
		#((3*T)/2); //Wait 
		reset = 0; //Set reset low
	end //Does not repeat
	
	initial begin //Values based off required behaviour in brief
		d = 0; //Set data to 0
		#(2*T); //Wait specified time
		d = 1; //Set data to 1
		#(T + T/4); //Wait specified time
		d = 0; //Set data to 0
		#((3*T)/2); //Wait specified time
		d = 1; //Set data to 1
		#(5*T); //Wait specified time
		d = 0; //Set data to 0
	end //Does not repeat
	
      
endmodule

