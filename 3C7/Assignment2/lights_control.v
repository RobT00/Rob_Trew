//Module to control the changing of states, i.e. what lights should be on
module lights_control(
		//Input Wires
		input wire clk,//Input 1Hz clock signal, for running module, in conjunction with output of timer module
		input wire reset, //Input reset signal, to reset states, to red and cycling (red, green, amber), in event of a reset 
		input wire pedestrian, //Input pedestrian signal, to signal if pedestrain state should be triggered
		input wire ped_flag_in, //Input flag to signal whether or not to remain in pedestrian state
		input wire [3:0] count, //4bit wide input from timer specifyiung how long the light has been lit for
		//Output Regs
		output reg [1:0] state_reg, //2bit wide output from module specifying the current colour of the light
		output reg ped_flag_out //Output from module, that will be fed back in to flag if should remain in pedestrian state
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
	reg [1:0] state_next; //2bit wide register to hold the next state of the FSM, i.e. what light should be lit
	reg cond_next; //Register to hold next value for pedestrian flag
	
	//Always block, sequentially triggered, to assign state and pedestrian flag
	always @(posedge clk, posedge reset) begin //Asynchronous, trigger on rising edge 
			if (reset) begin //If there's a reset signal
				ped_flag_out <= 0; //Set the pedestrian flag to be 0
				state_reg <= red_code; //Set the state to indicate the red light should be lit (default/statring state)				
			end
			else begin //Otherwise, triggered off clock signal
				ped_flag_out <= cond_next; //Set the pedestrian flag from the combinatorial logic
				state_reg <= state_next; //Update the state, i.e. the colour of the light
			end
	end
	
	//Always block, containg combinatorial logic for sequential block
	always @* begin
		//Pedestrian State -> amber, red, green, amber ->
		if (pedestrian || ped_flag_in) begin //If the input is the pedestrian button or the pedestrian flag being HIGH (1)
			cond_next = 1; //Set the pedestrian flag to be HIGH (1)
			if (pedestrian) //If the trigger has been the pedestrian button
				state_next = amber_code; //Set the light to amber
			else begin //Otherwise, the trigger has been the pedestrian flah
				case (state_reg) //Case statement for current light colour (state)
					amber_code: begin	 //If the state is amber
						if (count == amber_time) //If the count matches the desired time
							state_next = red_code; //Set the next state to be red
						else //Otherwise, not at desired count (time)
							state_next = amber_code; //Remain in the current state
						end
					red_code: begin //If the state is red
							if (count == red_time)	//If the count matches the desired time
								state_next = green_code; //Set the next state to be green
							else //Otherwise, not at desired count (time)
								state_next = red_code; //Remain in current state
							end
					green_code: begin	//If the state is green
							if (count == green_time) begin //If the count matches the desired time
								cond_next = 0; //Set the pedestrian flag to LOW (0), as exiting the state
								state_next = amber_code; //Set the next state to amber, ready to rejoin the cyclic state
							end
							else //Otherwise, not at desired count (time)
								state_next = green_code; //Remain in current state
							end
					default: //Default case, no state matches
						state_next = amber_code; //Set state to amber, default for pedestrian state
					endcase
			end
		end
		//Cyclic state -> red, green, amber, red...
		else begin
			cond_next = 0; //Set the pedestrian flag to LOW (0)
			case (state_reg) //Case statement for current light colour (state)
				red_code: begin //If the state is red
					if (count == red_time)	//If the count matches the desired time
						state_next = green_code; //Set the next state to be green
					else //Otherwise, not at desired count (time)
						state_next = red_code; //Remain in current state
					end
				amber_code: begin	 //If the state is amber
					if (count == amber_time) //If the count matches the desired time
						state_next = red_code; //Set the next state to be red
					else //Otherwise, not at desired count (time)
						state_next = amber_code; //Remain in the current state
					end
				green_code: begin	 //If the state is green
					if (count == green_time) //If the count matches the desired time
						state_next = amber_code; //Set the next state to be amber
					else //Otherwise, not at desired count (time)
						state_next = green_code; //Remain in the current state
					end
				default: //Default case, not state matches
					state_next = red_code; //Set state to red, default for cyclic state
			endcase
		end
	end
	
endmodule
