//Multiplexer to set output for TrafficLights module, i.e. which lights should be lit
module multiplexer(
	//Input Wire
	input wire [1:0] colour_code, //2bit wide input from control module specifying the traffic light colour state 
	//Output Regs
	output reg red_reg, //Output register for red light, where HIGH (1) indicates the light is on
	output reg amber_reg, //Output register for amber light, where HIGH (1) indicates the light is on 
	output reg green_reg //Output register for green light, where HIGH (1) indicates the light is on
    );
	 
	//Local parameters for the code corresponding to light colours   
	localparam red_code = 2'b00, 
				  amber_code = 2'b01, 
				  green_code = 2'b10;
	
	//Always block to set module outputs
	always @* begin
		 case (colour_code) //Case statement on cuurent colour code in module
			red_code: begin //If the current colour is red, set appropriate lights
				red_reg = 1;
				amber_reg = 0;		
				green_reg = 0;		
			end
			amber_code: begin //If the current colour is amber, set appropriate lights
				red_reg = 0;
				amber_reg = 1;
				green_reg = 0;
			end
			green_code: begin	//If the current colour is green, set appropriate lights
				red_reg = 0;
				amber_reg = 0;	
				green_reg = 1;
			end
			default: begin	//Default case, if colour_code does not correspond to a case
				red_reg = 1; //Set two lights on, to show error has occurred
				amber_reg = 1;
				green_reg = 0;
				end
		 endcase
	 end
	 
endmodule
