// Spartan-3E starter Board
// Programmable Pre-Amplifier s3eprogamp.v
// c 2008 Embedded Design using Programmable Gate Arrays  Dennis Silage

module s3eprogamp(input bufclk, input ampdav,
				output reg davamp, input [3:0] ampcmd0,
				input [3:0] ampcmd1, output reg ampsck,
				output reg ampspid, output reg csamp,
				output reg sdamp=0);

reg [4:0] ampstate=0;		// state register
reg [2:0] ampclkreg=0;		// prog amp clock register
reg ampclk=0;					// prog amp clock

always@(posedge bufclk)	// master clock event driven 50 MHz
	begin
		ampclkreg=ampclkreg+1;	// increment clock register	
		if (ampclkreg==3)
			begin
				ampclkreg=0;
				ampclk=~ampclk; 	// 8.33 MHz clock, 60+60=120 ns
			end
	end
	
always@(posedge ampclk)	// local clock event driven 8.33 MHz
	begin
		if (ampdav==0)		// prog amp data?
			begin
				ampsck=0;
				ampstate=0;
				csamp=1;
				davamp=0;	// prog amp NAK
			end
		
		if (ampdav==1 && davamp==0)
			begin			
				case (ampstate)
				0: begin
						csamp=1; 
						ampsck=0;
						ampstate=1;
					end
				1: begin
						csamp=0;
						ampspid=ampcmd0[3];
						ampstate=2;
					end
				2: begin
						ampsck=1;
						ampstate=3;
					end
				3: begin
						ampsck=0;
						ampspid=ampcmd0[2];
						ampstate=4;
					end
				4: begin
						ampsck=1;
						ampstate=5;
					end
				5: begin
						ampsck=0;
						ampspid=ampcmd0[1];
						ampstate=6;
					end
				6: begin
						ampsck=1;
						ampstate=7;
					end
				7: begin
						ampsck=0;
						ampspid=ampcmd0[0];
						ampstate=8;
					end			
				8: begin
						ampsck=1;
						ampstate=9;
					end
				9: begin
						ampsck=0;
						ampspid=ampcmd1[3];
						ampstate=10;
					end			
				10: begin
						ampsck=1;
						ampstate=11;
					end
				11: begin
						ampsck=0;
						ampspid=ampcmd1[2];
						ampstate=12;
					end			
				12: begin
						ampsck=1;
						ampstate=13;
					end
				13: begin
						ampsck=0;
						ampspid=ampcmd1[1];
						ampstate=14;
					end			
				14: begin
						ampsck=1;
						ampstate=15;
					end
				15: begin
						ampsck=0;
						ampspid=ampcmd1[0];
						ampstate=16;
					end			
				16: begin
						ampsck=1;
						ampstate=17;
					end			
				17: begin
						csamp=1;		// set prog amp gain
						ampstate=18;
					end
				18: begin
						ampsck=0;
						ampspid=0;
						davamp=1;	// prog amp ACK
						ampstate=19;
					end
				19: ampstate=19;
				default: ampstate=19;
			endcase
		end
	end
endmodule
