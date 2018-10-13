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