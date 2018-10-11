#include<iostream>
#include<string>

std::string rev_it(const std::string s);
std::string rev_rec(const std::string s, int pos);
void swap(char* a, char* b);

int main() {
	std::string var = "racecaR";
	std::cout << "var: " << var << std::endl;
	std::cout << "rev_it: " << rev_it(var) << std::endl;
	std::cout << "rev_rec: " << rev_rec(var, var.length()) << std::endl;
	return 0;
}

std::string rev_it(const std::string s) {
	std::string rev_str = s;
	int i = 0;
	int n = s.length() - 1;
	for (i, n ; i < n ; i++, n--) {
		swap(&rev_str[i], &rev_str[n]);
	}
	return rev_str;
}

std::string rev_rec(const std::string s, int pos) {
	return (pos == 0 ? "" : s[pos - 1] + rev_rec(s, pos - 1));
}

void swap(char* a, char*b) {
	char t = *a;
	*a = *b;
	*b = t;
}