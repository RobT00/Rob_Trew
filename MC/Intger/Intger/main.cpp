#include<iostream>
//#include<vector>
//#include"helper.h"

int freq_int(const int arr[], int len);
void swap(int* a, int* b);
int partition(int arr[], int lo, int hi, bool rev);
void quick_sort(int arr[], int lo, int hi, bool rev=false);
//int hash(int x, int l);

int main() {
	//std::cout << "Hello World\n";
	int tst[] = { -1, -3, 0, 34, 5, 5, 5, 5, 6 };
	//int tst[] = { 0, 0, 0 };
	//int tst[] = { 0, 1, 2, 3 };
	/*for (int i = 0; i < 3; i++) {
		std::cout << tst[i] << " ";
	}*/
	//std::cout << std::endl;
	//int size = sizeof(tst)/sizeof(tst[0]);
	std::cout << "Most Frequent integer: " << freq_int(tst, sizeof(tst) / sizeof(int)) << std::endl;
	/*for (int i = 0; i < 3; i++) {
		std::cout << tst[i] << " ";
	}*/
	//std::cout << std::endl;
	//std::string var = "Test";
	//std::cout << var[0] << std::endl;
	return 0;
}

int freq_int(const int arr[], int len) {
	int* new_arr;
	int i, j;
	//int size = sizeof(*&arr);
	//std::cout << size << std::endl;
	new_arr = new int[len];
	if (!new_arr) { return INT_MAX; } //Allocation failed
	for (int i = 0; i < len; i++) {
		new_arr[i] = arr[i];
	}
	quick_sort(new_arr, 0, len - 1);
	/*for (i = 0; i < len; i++) {
		std::cout << new_arr[i] << " ";
	}
	std::cout << std::endl;*/
	quick_sort(new_arr, 0, len-1, true);
	/*for (i = 0; i < len; i++) {
		std::cout << new_arr[i] << " ";
	}
	std::cout << std::endl;*/
	int sum;
	int max_freq = 0;
	int max_lcn = 0;
	int curr_num;
	i = 0;
	for (i; i < len; i++) {
		curr_num = new_arr[i];
		sum = 0;
		for (j = i; j < len; j++) {
			if (curr_num == new_arr[j]) { sum++; }
			else { break; }
		}
		if (sum > max_freq) {
			max_freq = sum;
			max_lcn = i;
		}
		i = j;
		if (max_freq > len / 2) { break; } //No point in continuing
	}
	int top;
	if (max_freq> 1) { top = new_arr[max_lcn]; }
	else { top = -INT_MAX; }
	delete[] new_arr;
	return top;
}

/*int hash(int val, int len) {
	return (val % len);
}*/

//Function for partition of quicksort
int partition(int arr[], int lo, int hi, bool rev) {
	int pivot = arr[hi];
	int index_small = lo - 1;  // Index of smaller element 
	if (!rev) {
		for (int j = lo; j <= hi - 1; j++) {
			if (arr[j] <= pivot) {
				index_small++;    // increment index of smaller element, ensuring non-negative
				swap(&arr[index_small], &arr[j]);
			}
		}
		swap(&arr[index_small + 1], &arr[hi]);
	}
	else {
		for (int j = lo; j <= hi - 1; j++) {
			if (arr[j] >= pivot) {
				index_small++;    // increment index of smaller element, ensuring non-negative
				swap(&arr[index_small], &arr[j]);
			}
		}
		swap(&arr[index_small + 1], &arr[hi]);
	}
	return (index_small + 1);
}

//Main recursive function for quicksort
void quick_sort(int arr[], int lo, int hi, bool rev) {
	if (lo < hi) {
		int part_index = partition(arr, lo, hi, rev);
		quick_sort(arr, lo, part_index - 1, rev);
		quick_sort(arr, part_index + 1, hi, rev);
	}
}

//Simple swap function
void swap(int* a, int* b) { 
	int t = *a;
	*a = *b;
	*b = t;
}