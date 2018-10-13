#include<iostream>
#include<chrono>

#define N 1000000

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

int main() {
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	//std::cout << ackermann(3, 6) << std::endl;
	int a;
	volatile int x = 3;
	for (int i = 0; i < N; i++) {
		a = ackermann(x, 6);
	}
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	float duration = std::chrono::duration_cast<std::chrono::nanoseconds> (t2 - t1).count();
	duration = duration / N;
	std::cout << duration << " ns" << std::endl;
	return 0;
}