// BASYS and Spartan-3E Starter Board
// PS/2 Mouse mouse.v
// c 2008 Embedded Design using Programmable Gate Arrays  Dennis Silage

module mouse(input CCLK, inout PS2CLK, inout PS2DAT,
				output reg dav, output reg [2:0] parity,
				output reg [1:0] button, output reg [1:0] ovf,
				output reg [1:0] sign,
				output reg [7:0] mousexdata,
				output reg [7:0] mouseydata);

reg [12:0] count;			// delay counter
reg [1:0] resstate=0;	// reset state
reg [4:0] sstate;			// sent data state
reg [5:0] rstate;			// received data state
reg clkps2;
reg datps2;
reg reset;

assign PS2CLK=clkps2;
assign PS2DAT=datps2;

always@(posedge CCLK)
	begin
		resstate<=resstate+1;
		if (resstate==1)
			reset=1;
		if (resstate==3)
			begin
				resstate<=2;
				reset=0;
			end
	end
	
always@(count or reset)
	begin
		if (reset==1)
			clkps2=1'bz;
		else if (count<=5500 && reset==0)
			clkps2=0;
		else
			clkps2=1'bz;
	end
	
always@(posedge CCLK or posedge reset)
	begin
		if (reset==1)
			count<=0;
		else if (count==6000)
			count<=count;
		else
			count<=count+1;
	end
	
always@(count or reset)
	begin
		if (reset==1)
			datps2=1'bz;
		else if (count>5000 && sstate==0)
			datps2=0;				// start bit
		else if (sstate==1)		// F4h
			datps2=0;
		else if (sstate==2)
			datps2=0;
		else if (sstate==3)
			datps2=1;
		else if (sstate==4)
			datps2=0;		
		else if (sstate==5)
			datps2=1;
		else if (sstate==6)
			datps2=1;
		else if (sstate==7)
			datps2=1;
		else if (sstate==8)
			datps2=1;		
		else if (sstate==9)		// parity bit
			datps2=0;		
		else if (sstate==10)		// stop bit
			datps2=1;
		else
			datps2=1'bz;	
	end
	
always@(negedge PS2CLK or posedge reset)
	begin
		if (reset==1)
			sstate<=0;
		else if (sstate<=21)
			sstate<=sstate+1;
		else if (sstate==22)
			sstate<=22;
		else
			sstate<=0;		
	end
						
always@(negedge PS2CLK)			// read mouse data
	begin
		if (reset==1)
			rstate=0;
		else if (sstate==22)
			begin
				rstate=rstate+1;
				case (rstate)
					1: dav=0;
					2: button[1]=PS2DAT;		// x button
					3: button[0]=PS2DAT;		// y button
					4: dav=0;
					5: dav=0;
					6: sign[1]=PS2DAT;		// x sign
					7: sign[0]=PS2DAT;		// y sign
					8: ovf[1]=PS2DAT;			// x overflow
					9: ovf[0]=PS2DAT;			// y overflow
					10: parity[0]=PS2DAT;
					11: dav=0;
					12: dav=0;
					13: mousexdata[0]=PS2DAT;	// x data
					14: mousexdata[1]=PS2DAT;
					15: mousexdata[2]=PS2DAT;
					16: mousexdata[3]=PS2DAT;
					17: mousexdata[4]=PS2DAT;
					18: mousexdata[5]=PS2DAT;
					19: mousexdata[6]=PS2DAT;
					20: mousexdata[7]=PS2DAT;
					21: parity[1]=PS2DAT;	// x data parity
					22: dav=0;
					23: dav=0;
					24: mouseydata[0]=PS2DAT;	// y data
					25: mouseydata[1]=PS2DAT;
					26: mouseydata[2]=PS2DAT;
					27: mouseydata[3]=PS2DAT;
					28: mouseydata[4]=PS2DAT;
					29: mouseydata[5]=PS2DAT;
					30: mouseydata[6]=PS2DAT;
					31: mouseydata[7]=PS2DAT;
					32: parity[2]=PS2DAT;	// y data parity
					33: begin 
							rstate=0;
							dav=1;
						 end
				endcase
			end
		end

endmodule

