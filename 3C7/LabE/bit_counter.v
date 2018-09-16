module bit_counter( //Module to count MSB 1s and 0s for LFSR
	 input bit_in, //MSB from LFSR
	 input reset, //Reset signal from LFSR
	 input max_tick //Max_tick signal from LFSR
    );
	reg [13:0]ones_out_reg; //Register for count of 1s
	reg [13:0]zeros_out_reg; //Register for count of 0s
	always@ (posedge clk, posedge reset) //Asynchronous, Rising Edge
		begin
		if (!reset && !max_tick) begin //Only if not max_tick (i.e. seed) and reset is low
			if (bit_in) //If the MSB is a 1, increase the count of 1s
				ones_out_reg = ones_out_reg + 1;
			else //If the MSB is 0, increase the count of 0s
				zeros_out_reg = zeros_out_reg + 1;
		end
		else begin //Otherwise (i.e. reset and/or max_tick is high) zero/reset the counts
			ones_out_reg = 0;
			zeros_out_reg = 0;
		end
	end
	
endmodule
