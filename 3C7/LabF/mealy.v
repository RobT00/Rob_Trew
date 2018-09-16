//FSM based off Mealy Model, to detect sequence "101" in a stream of bits
module mealy(
    input wire clk, //Clock signal input to FSM
    input wire reset, //Reset signal to FSM
    input wire bitstream, //Bitstream input, to be parsed for "101" sequence
    output reg tick //Output to show "101" sequence has been seen
    );
	
	//Symbolic State Declaration	
	localparam [1:0] //Parameters are 2bit wide so to accommodate all 3 states of FSM, i.e. A, B, C
		A = 2'b00, //First state; "looking for 1"
		B = 2'b01, //Second state; "found 1, looking for 0"
		C = 2'b10; //Third (final) state; "found 10, looking for 1"
		
	//Signal Declaration
	reg[1:0] state_reg, state_next; //Registers also 2bit wide, due to parameters/states of FSM
	reg tick_next; //Register to facilitate synchronous operation
	//State Register (sequential)
	always@(posedge clk) 
		if (reset)
			state_reg <= A; //If reset is HIGH, remain in state A (first state)
		else begin
			state_reg <= state_next; //IF reset is LOW, advance to appropriate state
			tick <= tick_next; //Synchronously set tick to the value of tick_next
		end
	
	// Next State Logic and Output logic (combinatorial)
	always@* begin
		state_next = state_reg; //state will remain the same unless changed by following logic
		tick_next = 0; //tick is set LOW, unless changed by logic
		case (state_reg) //Beginning of FSM case statement
			A:	//State A (First)
				if (bitstream) //If a "1" is seen advance to next state, B
					state_next = B; 
					//Otherwise remain in state A (current state)
			B: //State B (Second)
				if (~bitstream) //If in state B and a "0" is seen, advance to state C (10 sequence)
					state_next = C;
				else				//Otherwise return to state A, looking for a "1"
					state_next = A;
			C: //State C (Third)
				if (bitstream) begin //If in state C (seen 10) and bit is "1" (101 sequence)
					state_next = B; //As a "1" is seen, return to state B, sequence is now "1", so looking for "0"
					tick_next = 1; //As sequence is complete, set tick HIGH to represent this
					end
				else
					state_next = A; //If a "0" is seen, sequence is broken, return to state A, looking for "1"
			default: //Default case 
				state_next = A;
		endcase
	end
	
endmodule
