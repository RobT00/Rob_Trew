// Listing 4.2
module d_ff_reset //D Type Flip-Flop, to investigate clock setup scenarios
   (
    input wire clk, reset, //Clock signal and reset signal input
    input wire d, //Data, input wire to D Type Flip-Flop
    output reg q //Output, of D Type Flip-Flop
   );

   // body
   always @(negedge clk) //Setup as negative edge, synchronous
      if (reset) //If reset is high, q is 0
         q <= 1'b0;`
      else //Otherwise, q has the value of d
         q <= d;
endmodule