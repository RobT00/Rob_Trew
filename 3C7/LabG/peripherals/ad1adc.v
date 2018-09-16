// Basys Board and Nexys Board
// Analog-to-Digital Converter ad1adc.v
// c 2008 Embedded Design using Programmable Gate Arrays  Dennis Silage

module ad1adc(input bufclk, adcdav, output reg davadc=0,
					output reg [11:0] adc0data, 
					output reg [11:0] adc1data,
					output reg adcsck, input adc0d, adc1d,
					output reg adccs=1);

reg [6:0] adcstate=0;
reg adcclk=0;

always@(posedge bufclk)	// buffered clock event driven
	begin
			adcclk=~adcclk;	// clock divider
			if (adcdav==0)
				begin
					adcstate=0;
					adcsck=1;
					adccs=1;
					davadc=0;	// ADC data NAK
				end
			
		if (adcdav==1 && davadc==0 && adcclk==1)
			begin
				case (adcstate)
				0: begin
						adccs=0;		// ADC chip select
						adcsck=1;
						adcstate=1;
					end
				1: begin
						adcsck=0;	// 1  X
						adcstate=2;
					end
				2: begin
						adcsck=1;
						adcstate=3;
					end
				3: begin
						adcsck=0;	// 2  X
						adcstate=4;
					end
				4: begin
						adcsck=1;
						adcstate=5;
					end
				5: begin
						adcsck=0;	// 3  X  
						adcstate=6;
					end			
				6: begin
						adcsck=1;
						adcstate=7;
					end
				7: begin
						adcsck=0;	// 4  x
						adcstate=8;
					end			
				8: begin
						adcsck=1;
						adcstate=9;
					end
				9: begin
						adcsck=0;
						adc0data[11]=adc0d;
						adc1data[11]=adc1d;
						adcstate=10;
					end			
				10: begin
						adcsck=1;
						adcstate=11;
					end
				11: begin
						adcsck=0;
						adc0data[10]=adc0d;
						adc1data[10]=adc1d;
						adcstate=12;
					end			
				12: begin
						adcsck=1;
						adcstate=13;
					end
				13: begin
						adcsck=0;
						adc0data[9]=adc0d;
						adc1data[9]=adc1d;
						adcstate=14;
					end			
				14: begin
						adcsck=1;
						adcstate=15;
					end
				15: begin
						adcsck=0;
						adc0data[8]=adc0d;
						adc1data[8]=adc1d;
						adcstate=16;
					end			
				16: begin
						adcsck=1;
						adcstate=17;
					end
				17: begin
						adcsck=0;
						adc0data[7]=adc0d;
						adc1data[7]=adc1d;
						adcstate=18;
					end			
				18: begin
						adcsck=1;
						adcstate=19;
					end
				19: begin
						adcsck=0;
						adc0data[6]=adc0d;
						adc1data[6]=adc1d;
						adcstate=20;
					end			
				20: begin
						adcsck=1;
						adcstate=21;
					end
				21: begin
						adcsck=0;
						adc0data[5]=adc0d;
						adc1data[5]=adc1d;
						adcstate=22;
					end								
				22: begin
						adcsck=1;
						adcstate=23;
					end
				23: begin
						adcsck=0;
						adc0data[4]=adc0d;
						adc1data[4]=adc1d;
						adcstate=24;
					end			
				24: begin
						adcsck=1;
						adcstate=25;
					end
				25: begin
						adcsck=0;
						adc0data[3]=adc0d;
						adc1data[3]=adc1d;
						adcstate=26;
					end								
				26: begin
						adcsck=1;
						adcstate=27;
					end
				27: begin
						adcsck=0;
						adc0data[2]=adc0d;
						adc1data[2]=adc1d;
						adcstate=28;
					end		
				28: begin
						adcsck=1;
						adcstate=29;
					end
				29: begin
						adcsck=0;
						adc0data[1]=adc0d;
						adc1data[1]=adc1d;
						adcstate=30;
					end								
				30: begin
						adcsck=1;
						adcstate=31;
					end
				31: begin
						adcsck=0;
						adc0data[0]=adc0d;
						adc1data[0]=adc1d;
						adcstate=32;
					end			
				32: begin
						adcsck=1;
						adcstate=33;
					end
				33: begin
						adccs=1;
						davadc=1;
						adcstate=34;
					end								
				34: adcstate=34;
				default: adcstate=34;
			endcase
		end
	end
endmodule
