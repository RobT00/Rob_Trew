#include<iostream>
#include<chrono>

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

void main() {
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	//std::cout << ackermann(3, 6) << std::endl;
	ackermann(3, 6);
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds> (t2 - t1).count();

	std::cout << duration << " ns" << std::endl;
	return;
}