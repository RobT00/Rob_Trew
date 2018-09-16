// Spartan-3E Starter Board 
// Analog-to-Digital Converter s3eadc.v
// c 2008 Embedded System Design using Programmable Gate Arrays  Dennis Silage

module s3eadc(input bufclk, input adcdav, output reg davadc,
					output reg [13:0] adc0data, 
					output reg [13:0] adc1data,
					output reg adcsck, input adcspod,
					output reg conad);

reg [6:0] adcstate;
reg adcclk;

always@(posedge bufclk)	// buffered clock event driven
	begin
		adcclk=~adcclk;
		if (adcdav==0)
			begin
				adcstate=0;
				conad=0;
				davadc=0;	// ADC data NAK
			end
			
		if (adcdav==1 && davadc==0 && adcclk==1)
			begin
				case (adcstate)
				0: begin
						conad=1;		// ADC convert command
						adcsck=0;
						adcstate=1;
					end
				1: adcstate=2;
				2: begin
						conad=0;
						adcstate=3;
					end
				3: begin
						adcsck=1;
						adcstate=4;
					end
				4: begin
						adcsck=0;	// 1
						adcstate=5;
					end
				5: begin
						adcsck=1;
						adcstate=6;
					end			
				6: begin
						adcsck=0;	// 2
						adcstate=7;
					end
				7: begin
						adcsck=1;
						adcstate=8;
					end			
				8: begin
						adcsck=0;	// 3
						adc0data[13]=adcspod;
						adcstate=9;
					end
				9: begin
						adcsck=1;
						adcstate=10;
					end			
				10: begin
						adcsck=0;	// 4
						adc0data[12]=adcspod;
						adcstate=11;
					end
				11: begin
						adcsck=1;
						adcstate=12;
					end			
				12: begin
						adcsck=0;	// 5
						adc0data[11]=adcspod;
						adcstate=13;
					end
				13: begin
						adcsck=1;
						adcstate=14;
					end			
				14: begin
						adcsck=0;	// 6
						adc0data[10]=adcspod;
						adcstate=15;
					end
				15: begin
						adcsck=1;
						adcstate=16;
					end			
				16: begin
						adcsck=0;	// 7
						adc0data[9]=adcspod;
						adcstate=17;
					end
				17: begin
						adcsck=1;
						adcstate=18;
					end			
				18: begin
						adcsck=0;	// 8
						adc0data[8]=adcspod;
						adcstate=19;
					end
				19: begin
						adcsck=1;
						adcstate=20;
					end			
				20: begin
						adcsck=0;	// 9
						adc0data[7]=adcspod;
						adcstate=21;
					end
				21: begin
						adcsck=1;
						adcstate=22;
					end								
				22: begin
						adcsck=0;	// 10
						adc0data[6]=adcspod;
						adcstate=23;
					end
				23: begin
						adcsck=1;
						adcstate=24;
					end			
				24: begin
						adcsck=0;	// 11
						adc0data[5]=adcspod;
						adcstate=25;
					end
				25: begin
						adcsck=1;
						adcstate=26;
					end								
				26: begin
						adcsck=0;	// 12
						adc0data[4]=adcspod;
						adcstate=27;
					end
				27: begin
						adcsck=1;
						adcstate=28;
					end		
				28: begin
						adcsck=0;	// 13
						adc0data[3]=adcspod;
						adcstate=29;
					end
				29: begin
						adcsck=1;
						adcstate=30;
					end								
				30: begin
						adcsck=0;	// 14
						adc0data[2]=adcspod;
						adcstate=31;
					end
				31: begin
						adcsck=1;
						adcstate=32;
					end			
				32: begin
						adcsck=0;	// 15
						adc0data[1]=adcspod;
						adcstate=33;
					end
				33: begin
						adcsck=1;
						adcstate=34;
					end								
				34: begin
						adcsck=0;	// 16
						adc0data[0]=adcspod;
						adcstate=35;
					end
				35: begin
						adcsck=1;
						adcstate=36;
					end		
				36: begin
						adcsck=0;	// 17
						adcstate=37;
					end
				37: begin
						adcsck=1;
						adcstate=38;
					end								
				38: begin
						adcsck=0;	// 18
						adcstate=39;
					end
				39: begin
						adcsck=1;
						adcstate=40;
					end		
				40: begin
						adcsck=0;	// 19
						adc1data[13]=adcspod;
						adcstate=41;
					end
				41: begin
						adcsck=1;
						adcstate=42;
					end								
				42: begin
						adcsck=0;	// 20
						adc1data[12]=adcspod;
						adcstate=43;
					end
				43: begin
						adcsck=1;
						adcstate=44;
					end			
				44: begin
						adcsck=0;	// 21
						adc1data[11]=adcspod;
						adcstate=45;
					end
				45: begin
						adcsck=1;
						adcstate=46;
					end			
				46: begin
						adcsck=0;	// 22	
						adc1data[10]=adcspod;
						adcstate=47;
					end
				47: begin
						adcsck=1;
						adcstate=48;
					end								
				48: begin
						adcsck=0;	// 23
						adc1data[9]=adcspod;
						adcstate=49;
					end
				49: begin
						adcsck=1;
						adcstate=50;
					end		
				50: begin
						adcsck=0;	// 24
						adc1data[8]=adcspod;
						adcstate=51;
					end
				51: begin
						adcsck=1;
						adcstate=52;
					end		
				52: begin
						adcsck=0;	// 25
						adc1data[7]=adcspod;
						adcstate=53;
					end
				53: begin
						adcsck=1;
						adcstate=54;
					end
				54: begin
						adcsck=0;	// 26
						adc1data[6]=adcspod;
						adcstate=55;
					end
				55: begin
						adcsck=1;
						adcstate=56;
					end
				56: begin
						adcsck=0;	// 27
						adc1data[5]=adcspod;
						adcstate=57;
					end
				57: begin
						adcsck=1;
						adcstate=58;
					end
				58: begin
						adcsck=0;	// 28
						adc1data[4]=adcspod;
						adcstate=59;
					end
				59: begin
						adcsck=1;
						adcstate=60;
					end
				60: begin
						adcsck=0;	// 29
						adc1data[3]=adcspod;
						adcstate=61;
					end
				61: begin
						adcsck=1;
						adcstate=62;
					end
				62: begin
						adcsck=0;	// 30
						adc1data[2]=adcspod;
						adcstate=63;
					end
				63: begin
						adcsck=1;
						adcstate=64;
					end
				64: begin
						adcsck=0;	// 31
						adc1data[1]=adcspod;
						adcstate=65;
					end
				65: begin
						adcsck=1;
						adcstate=66;
					end
				66: begin
						adcsck=0;	// 32
						adc1data[0]=adcspod;
						adcstate=67;
					end
				67: begin
						adcsck=1;
						adcstate=68;
					end
				68: begin
						adcsck=0;	// 33
						adcstate=69;
					end
				69: begin
						adcsck=1;
						adcstate=70;
					end
				70: begin
						adcsck=0;	// 34
						davadc=1;	// ADC data ACK
						adcstate=71;
					end
				71: adcstate=71;
				default: adcstate=71;
			endcase
		end
	end
endmodule
