//Compares two bits, to see if one is less than the other
module less_2(
    input wire [1:0] a,
    input wire [1:0] b,
    output wire less
    );
	// Signal Declaration
	wire p0, p1, p2;
	
	// Body
	// SOP of terms
	assign less = p0 | p1 | p2;
	// Product Terms
	assign p0 = ~a[1] & b[1]; //Corresponds to 'red' group on Karnaugh Map
	assign p1 = ~a[0] & ~a[1] & b[0]; //Corresponds to 'green' group on Karnaugh Map
	assign p2 = ~a[0] & b[0] & b[1]; //Corresponds to 'blue' group on Karnaugh Map

endmodule
