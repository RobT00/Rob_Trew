// Spartan-3E Starter Board 
// Digital-to-Analog Converter s3edac.v
// c 2008 Embedded Design using Programmable Gate Arrays  Dennis Silage

module s3edac(input dacclk, input dacdav, output reg davdac,
					input [11:0] dacdata, input [3:0] dacaddr,
					input [3:0] daccmd, output reg dacsck,
					output reg dacspid, output reg csdac,
					output reg clrdac=1);

reg [5:0] dacstate=0;

always@(posedge dacclk)
	begin
		if (dacdav==0)		// DAC data?
			begin
				dacstate=0;
				davdac=0;	// DAC data NAK 
			end
			
		if (dacdav==1 && davdac==0)
			begin
				case (dacstate)
				0: begin
						csdac=1;
						dacsck=0;
						dacstate=1;
					end
				1: begin
						csdac=0;
						dacstate=2;
					end
				2: begin
						dacspid=daccmd[3];
						dacstate=3;
					end
				3: begin
						dacsck=1;
						dacstate=4;
					end
				4: begin
						dacsck=0;
						dacspid=daccmd[2];
						dacstate=5;
					end			
				5: begin
						dacsck=1;
						dacstate=6;
					end
				6: begin
						dacsck=0;
						dacspid=daccmd[1];
						dacstate=7;
					end			
				7: begin
						dacsck=1;
						dacstate=8;
					end
				8: begin
						dacsck=0;
						dacspid=daccmd[0];
						dacstate=9;
					end			
				9: begin
						dacsck=1;
						dacstate=10;
					end
				10: begin
						dacsck=0;
						dacspid=dacaddr[3];
						dacstate=11;
					end			
				11: begin
						dacsck=1;
						dacstate=12;
					end
				12: begin
						dacsck=0;
						dacspid=dacaddr[2];
						dacstate=13;
					end			
				13: begin
						dacsck=1;
						dacstate=14;
					end
				14: begin
						dacsck=0;
						dacspid=dacaddr[1];
						dacstate=15;
					end			
				15: begin
						dacsck=1;
						dacstate=16;
					end
				16: begin
						dacsck=0;
						dacspid=dacaddr[0];
						dacstate=17;
					end			
				17: begin
						dacsck=1;
						dacstate=18;
					end
				18: begin
						dacsck=0;
						dacspid=dacdata[11];
						dacstate=19;
					end								
				19: begin
						dacsck=1;
						dacstate=20;
					end
				20: begin
						dacsck=0;
						dacspid=dacdata[10];
						dacstate=21;
					end			
				21: begin
						dacsck=1;
						dacstate=22;
					end
				22: begin
						dacsck=0;
						dacspid=dacdata[9];
						dacstate=23;
					end								
				23: begin
						dacsck=1;
						dacstate=24;
					end
				24: begin
						dacsck=0;
						dacspid=dacdata[8];
						dacstate=25;
					end		
				25: begin
						dacsck=1;
						dacstate=26;
					end
				26: begin
						dacsck=0;
						dacspid=dacdata[7];
						dacstate=27;
					end								
				27: begin
						dacsck=1;
						dacstate=28;
					end
				28: begin
						dacsck=0;
						dacspid=dacdata[6];
						dacstate=29;
					end			
				29: begin
						dacsck=1;
						dacstate=30;
					end
				30: begin
						dacsck=0;
						dacspid=dacdata[5];
						dacstate=31;
					end								
				31: begin
						dacsck=1;
						dacstate=32;
					end
				32: begin
						dacsck=0;
						dacspid=dacdata[4];
						dacstate=33;
					end		
				33: begin
						dacsck=1;
						dacstate=34;
					end
				34: begin
						dacsck=0;
						dacspid=dacdata[3];
						dacstate=35;
					end								
				35: begin
						dacsck=1;
						dacstate=36;
					end
				36: begin
						dacsck=0;
						dacspid=dacdata[2];
						dacstate=37;
					end		
				37: begin
						dacsck=1;
						dacstate=38;
					end
				38: begin
						dacsck=0;
						dacspid=dacdata[1];
						dacstate=39;
					end								
				39: begin
						dacsck=1;
						dacstate=40;
					end
				40: begin
						dacsck=0;
						dacspid=dacdata[0];
						dacstate=41;
					end			
				41: begin
						dacsck=1;
						dacstate=42;
					end
				42: begin
						dacsck=0;
						dacspid=0;		// X (don't care)
						dacstate=43;
					end			
				43: begin
						dacsck=1;		// X1
						dacstate=44;
					end
				44: begin
						dacsck=0;
						dacstate=45;
					end								
				45: begin
						dacsck=1;		// X2
						dacstate=46;
					end
				46: begin
						dacsck=0;
						dacstate=47;
					end		
				47: begin
						dacsck=1;		// X3
						dacstate=48;
					end
				48: begin
						dacsck=0;
						dacstate=49;
					end		
				49: begin
						dacsck=1;		// X3
						dacstate=50;
					end
				50: begin
						dacsck=0;
						csdac=1;
						davdac=1;		// DAC data ACK
						dacstate=51;
					end		
				51: dacstate=51;
				default: dacstate=51;
			endcase
		end
	end
endmodule
