#include<iostream>
#include<chrono>

#define N 100000

int ackermann(int, int);
void enter();
void exit();
int ackermann_mod(int, int);
void ackermann_metrics(int);

//Globals
int num_windows;
int calls;
int curr_depth;
int max_depth;
int overflows;
int underflows;
int windows_used;

int main() {
	ackermann_metrics(6);
	ackermann_metrics(8);
	ackermann_metrics(16);
	
	int a;
	volatile int x = 3; // Using volatile int to defeat compiler optimisation in for loop
	volatile int y = 6;
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < N; i++) {
		a = ackermann(x, y);
	}
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> duration = t2 - t1;
	duration /= N;
	
	std::cout << "Computing ackermann(3, 6) = " << a << std::endl;
	std::cout << "Average execution time: " << duration.count() << " ms" << std::endl;
	return 0;
}

int ackermann(int x, int y) {
	if (x == 0) {
		return (y + 1);
	}
	else if (y == 0) {
		return (ackermann(x - 1, 1));
	}
	else {
		return (ackermann(x - 1, ackermann(x, y - 1)));
	}
}

int ackermann_mod(int x, int y) {
	int z;
	enter();
	if (x == 0) {
		z = y + 1;
	}
	else if (y == 0) {
		z = ackermann_mod(x - 1, 1);
	}
	else {
		z = ackermann_mod(x - 1, ackermann_mod(x, y - 1));
	}
	exit();
	return z;
}

void enter() {
	calls++;
	curr_depth++;
	if (curr_depth > max_depth) {
		max_depth = curr_depth;
	}
	if ((windows_used + 1) % num_windows == 0) { // CWP+1=SWP -> 0 defined as 1st window on stack (SWP) 
		overflows++;
	}
	else {
		windows_used++;
	}
}

void exit() {
	curr_depth--;
	if ((windows_used - 1) % num_windows == 0) { // CWP-1=SWP -> 0 defined as 1st window on stack (SWP)
		underflows++;
	}
	else {
		windows_used--;
	}
}

void ackermann_metrics(int registers) {
	num_windows = registers;
	calls = 0;
	curr_depth = max_depth = overflows = underflows = 0;
	windows_used = 1; // window for main
	int v = ackermann_mod(3, 6);
	std::cout << "ackermann_mod(3, 6) = " << v << "\nCalls = " << calls << 
		", Max depth = " << max_depth << std::endl
		<< "Register Set = " << num_windows << 
		", Overflows = " << overflows << ", Underflows = " << underflows << std::endl;
	std::printf("\n");
}



