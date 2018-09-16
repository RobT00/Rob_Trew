//Module to measure amount of time (in seconds as based off 1Hz clock) the current light has been lit
module light_timer(
		//Input Wires
		input wire clk, //Input 1Hz clock signal, for incrementing time
		input wire reset, //Input reset signal, to reset time to 0, in event of a reset
		input wire[1:0] curr_code, //2bit wide input from the control module specifying what colour light is on
		//Output Reg
		output reg[3:0] timer_reg //4bit wide output from module specifying the time on the timer
    );
	
	//Local parameters for the code corresponding to light colours
	localparam red_code = 2'b00, 
				  amber_code = 2'b01, 
				  green_code = 2'b10;
	//Local parameters for the time (amount of time in seconds) each light should be lit for, as specified in the brief
	//Take away 1, as change of state happens one cycle later
	localparam red_time = 4'b1000 - 1,
				  amber_time = 4'b0011 - 1,
				  green_time = 4'b0110 - 1;
	//Local parameter to zero (0) timer
	localparam zero = 4'b0000;
	reg[3:0] timer_next; //Variable to hold the value of the next timer value
	reg[3:0] colour_time_reg; //Register to hold desired time (time) for colour
	reg[3:0] colour_time_next; //Register to hold next desired time (time) for colour, i.e. if colour changes
	
	//Update the value of timer_reg
	always @(posedge clk, posedge reset) begin //Asynchronous, on rising edge of both clock and reset
		if (reset) begin //If there is a reset signal
				timer_reg <= zero; //Reset the timer to zero (0)
				colour_time_reg <= red_time; //Set the target time to 8, for red (starting/default state)
			end	
		else begin //Otherwise, rising clock edge
				timer_reg <= timer_next; //Update the timer value
				colour_time_reg <= colour_time_next;	//Update the desired time for given colour
			end
	end

	//Update the value of timer_next, update the time -> timer_reg	
	always @* begin
		if (timer_reg == colour_time_reg) //If at target time for current colour
				timer_next = zero; //Set the timer to 0, as we will change colour
		else  //Otherwise, not reached desired time for colour
			timer_next = timer_reg + 1; //Increment value of timer by 1 (second)
	end

	// Update the value of target_time_next, to set the desired time for the current colour
	always @* begin
		case (curr_code)
			red_code: //If red is the current colour
				colour_time_next = red_time; //Set the desired time for red
			amber_code: //If amber is the current colour
				colour_time_next = amber_time; //Set the desired time for amber
			green_code: //If green is the current colour 
				colour_time_next = green_time; //Set the desired time for green
			default: //Default case, if not any of the previous states
				colour_time_next = red_time; //Set the desired time to the default/starting state, red
		endcase
	end
		
endmodule
