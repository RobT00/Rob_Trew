// Basys Board and Spartan-3E Starter Board
// LED Bar Graph Test bargraphtest.v
// c 2008 Embedded Design using Programmable Gate Arrays  Dennis Silage


module bargraphtest(input CCLK, output LD7, LD6, LD5, LD4,
                    LD3, LD2, LD1, LD0);

wire [7:0] data;
						  
clock M0 (CCLK, 250000, clock);
bargraph M1 (clock, data, LD7, LD6, LD5, LD4,
             LD3, LD2, LD1, LD0); 
gendata M2 (clock, data);

endmodule

// generate bar graph test data

module gendata(input clock, output reg [7:0] gdata);

always@(negedge clock)
	gdata=gdata+1;
	
endmodule
