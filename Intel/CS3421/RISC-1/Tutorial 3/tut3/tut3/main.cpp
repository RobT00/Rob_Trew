#include<iostream>
#include<chrono>

#define N 1000000

int ackermann(int, int);
void enter();
void exit();
int ackermann_mod(int, int);
void run(int);

//Globals
int num_windows;
int calls;
int curr_depth;
int max_depth;
int overflows;
int underflows;
int windows_used;

int main() {
	run(6);
	run(8);
	run(16);
	int a;
	//a = ackermann(3, 6);
	//std::cout << a << std::endl;
	volatile int x = 3;
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	//std::cout << ackermann(3, 6) << std::endl;
	for (int i = 0; i < N; i++) {
		a = ackermann(3, 6);
	}
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	float duration = std::chrono::duration_cast<std::chrono::nanoseconds> (t2 - t1).count();
	duration /= N;
	
	//std::cout << a << std::endl;
	std::cout << "Computing ackermann(3, 6) = " << a << std::endl;
	std::cout << "Took: " << duration << " ns" << std::endl;
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
	if (windows_used == num_windows) {
		overflows++;
	}
	else {
		windows_used++;
	}
}

void exit() {
	curr_depth--;
	if (windows_used == 2) {
		underflows++;
	}
	else {
		windows_used--;
	}
}

void run(int registers) {
	num_windows = registers;
	calls = 0;
	curr_depth = max_depth = overflows = underflows = 0;
	windows_used = 2;
	int v = ackermann_mod(3, 6);
	std::cout << "ackermann_mod(3, 6) = " << v << ", calls = " << calls << ", max depth = " << max_depth << std::endl
		<< "window size = " << num_windows << ", overflows = " << overflows << ", underflows = " << underflows << std::endl;
	if (overflows != underflows) {
		std::cout << "ERROR:\nOverflows = " << overflows << "\nunderflows = " << underflows << "\nThese should be equal\n";
	}
	std::printf("\n");
}