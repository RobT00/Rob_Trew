module LFSR( //LFSR Module
    input wire clk, //Input Clock Signal
    input wire reset, //Reset Signal Input
    output wire lfsr_out, //MSB of LFSR
	 output wire max_tick, //High (1) if value is seed, after initial reset
	 output wire [13:0]count_out //Count number of cycles
    );
	localparam seed = 14'b11_1100_0011_1100; //Parameter for seed of LFSR (arbitrarily chosen)
	//localparam seed = 14'b11_1111_1111_1111; //Parameter for forbidden seed of LFSR
	reg[13:0] lfsr_reg; //Reg for use in always block, contains all bits of LFSR
	reg[13:0] lfsr_next; //Reg for use in always block, contains next LFSR (i.e. with feedback)
	reg lfsr_tap; //Result of XNOR (feedback) from tapped bits of LFSR (this is the feedback)
	reg tick_reg; //Reg for use in always block, same as max_tick in operation
	reg [13:0]count_reg; //Reg for use in always blocks, count number of cycles, corresponds to count_out
	//Manipulate LFSR
	always @(posedge clk, posedge reset) //Asynchronous, Rising edges
		if (reset)
			lfsr_reg <= seed;	//seed
		else
			lfsr_reg <= lfsr_next; //set as next LFSR, i.e. shift bits with feedback
	//Check for seed		
	always @*
		if (lfsr_reg == seed && !reset) begin //Will be high when seed is reached again, after 2^N - 1 cycles
				tick_reg = 1;
			end
		else
			tick_reg = 0;
	//Count cycles		
	always @(posedge clk, posedge reset) //Asynchronous, Rising Edges 
		if (!reset) begin
			count_reg = count_reg + 1; //Increment count if not reset
			end
		else begin
			count_reg = 0; //COunt is 0 at reset, count will return to 0 after 2^N - 1, as it is 14bits
			end
	//Calculating new LFSR
	always @* begin //Using XNOR, N = 14 -> 13:0
		lfsr_tap = lfsr_reg[13] ~^ lfsr_reg[4] ~^ lfsr_reg[2] ~^ lfsr_reg[0]; //Perform XNOR in taps
		lfsr_next = {lfsr_reg[12:0],lfsr_tap}; //Setup new LFSR
	end
	//Module to count MSB 1s and 0s
	bit_counter count_bits (.bit_in(lfsr_reg[13]), .max_tick(max_tick), .reset(reset));
	assign lfsr_out = lfsr_reg[13]; //Output MSB of LFSR
	assign count_out = count_reg; //Output the cycles count
	assign max_tick = tick_reg; //Output max_tick

endmodule
