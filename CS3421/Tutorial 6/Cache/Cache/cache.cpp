//Robert Trew - 15315527
//Includes
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

//Globals
int l = 16;
int k = 8;
int n = 4;

//Function Definitions
string hit_or_miss(vector<int> &, int);

//Classes
class Cache {
public:
	int l, k, n;
	int misses, hits;
	vector<vector<int>> addr_num;

	Cache(int _l, int _k, int _n) {
		l = _l;
		k = _k;
		n = _n;
		addr_num.resize(n, vector<int>(k, -1));
		misses = 0;
		hits = 0;
	}

	~Cache() {
		cout << "Destructor called" << endl;
		//free(&addr_num);
	}

	int offset_fn(string line, size_t *ptr = nullptr, int base = 16) {
		return (str_to_val(line, ptr, base) & (l - 1));
	}
	int set_num_fn(string line, size_t *ptr = nullptr, int base = 16) {
		return ((str_to_val(line, ptr, base) >> int(log2(l))) & (int(pow(2, log2(n)) - 1)));
	}
	int tag_fn(string line, size_t *ptr = nullptr, int base = 16) {
		return (str_to_val(line, ptr, base) >> (int(log2(l)) + int(log2(n))));
	}

	//Function to return whether cache hit or miss and modify vector as necessary
	string hit_or_miss(int tag, int set_num) {
		string res = "Miss";
		for (int i = 0; i < k; i++) {
			if (addr_num[set_num][i] == -1) { break; } //-1 is the default value for tags, from the resize function
			if (addr_num[set_num][i] == tag) {
				res = "Hit"; //A cache hit
				hits++;
				if (i != 0 && k > 1) { //If not the first element and have >1 tag in the set
					addr_num[set_num].insert(addr_num[set_num].begin(), tag); //Insert at the top the tag (most recently used)
					auto it = addr_num[set_num].begin(); //Make iterator to find place in vector
					advance(it, i + 1); //Move the iterator to the old entry of the tag
					addr_num[set_num].erase(it); //Remove the previous tag (restoring the length of the vector)
				}
				break;
			}
		}
		if (res == "Miss") { //A hit has not been found
			misses++;
			addr_num[set_num].insert(addr_num[set_num].begin(), tag); //Add the tag to the vector (as most recently used)
			addr_num[set_num].erase(addr_num[set_num].end() - 1); //Remove the last tag (least recently used) restoring the vector length
		}
		return res;
	}

private:
	unsigned int str_to_val(string line, size_t *ptr = nullptr, int base = 16) {
		return stoul(line, ptr, base);
	}
};

int main()
{
	//Reading addresses from file
	ifstream addrs;
	addrs.open("addresses.csv");
	if (!addrs.is_open()) {
		cout << "File to read addresses from is not found or open\n";
		return -1;
	}
	//File to write results to (also written to console)
	ofstream answer;
	answer.open("Output.txt");
	if (!addrs.is_open()) {
		cout << "File to print output to is not found or open\n";
		return -1;
	}

	cout << "Cache size = " << (l*k*n) << " bytes\n";
	answer << "Cache size = " << (l*k*n) << " bytes\n";
	cout << "L = " << l << "\tK = " << k << "\tN = " << n << endl;
	answer << "L = " << l << "\tK = " << k << "\tN = " << n << endl;
	cout << "\nAddress\t|\tSet\t|\tHit/Miss\n";
	answer << "\nAddress\t|\tSet\t|\tHit/Miss\n";
	cout << string(40, '-') << endl;
	answer << string(40, '-') << endl;

	Cache cache_obj = Cache(l, k, n);
	
	/*//2D vector to contain sets and tags
	vector<vector<int>> addr_num;
	//Resize the vector for appropriate cache size, tags are set to -1 as a default value
	addr_num.resize(n, vector<int>(k, -1));
	
	string line;
	string res;
	
	int hit_count = 0;
	int miss_count = 0;

	//Reading addresses from the csv
	while (getline(addrs, line)) {
		cout << line << "\t|\t";
		answer << line << "\t|\t";
		unsigned int a = stoul(line, nullptr, 16); //Convert the hex address to an unsigned integer
		int off = a & (l - 1); //Calculate the offset (not actually needed)
		int set_num = (a >> int(log2(l))) & (int(pow(2, log2(n)) - 1)); //Calculate the set number (for 1st dimenesion of vector)
		int tag = (a >> (int(log2(l)) + int(log2(n)))); //Calculate the tag (for 2nd dimension of vector)
		cout << set_num << "\t|\t";
		answer << set_num << "\t|\t";
		res = hit_or_miss(addr_num[set_num], tag);
		if (res == "Miss") { miss_count++; }
		else { hit_count++; }
		cout << res << endl;
		answer << res << endl;
	}

	cout << string(40, '-') << endl;
	answer << string(40, '-') << endl;
	//Print the hit/miss counts
	cout << "\n\nHit Count: " << hit_count;
	answer << "\n\nHit Count: " << hit_count;
	cout << "\nMiss Count: " << miss_count << endl;
	answer << "\nMiss Count: " << miss_count << endl;
	cout << "\n";*/
	
	string line;
	string res;
	while (getline(addrs, line)) {
		cout << line << "\t|\t";
		answer << line << "\t|\t";
		//unsigned int a = stoul(line, nullptr, 16); //Convert the hex address to an unsigned integer
		//int off = a & (l - 1); //Calculate the offset (not actually needed)
		//int set_num = (a >> int(log2(l))) & (int(pow(2, log2(n)) - 1)); //Calculate the set number (for 1st dimenesion of vector)
		//int tag = (a >> (int(log2(l)) + int(log2(n)))); //Calculate the tag (for 2nd dimension of vector)
		int set_num = cache_obj.set_num_fn(line);
		cout << set_num << "\t|\t";
		answer << set_num << "\t|\t";
		res = cache_obj.hit_or_miss(cache_obj.tag_fn(line), set_num);
		cout << res << endl;
		answer << res << endl;
	}

	//Print the hit/miss counts
	cout << "\n\nHit Count: " << cache_obj.hits;
	answer << "\n\nHit Count: " << cache_obj.hits;
	cout << "\nMiss Count: " << cache_obj.misses << endl;
	answer << "\nMiss Count: " << cache_obj.misses << endl;

	//Close the files
	answer.close();
	addrs.close();
	return 0;
}

//Function to return whether cache hit or miss and modify vector as necessary
string hit_or_miss(vector<int> &v, int tag) {
	string res = "Miss";
	for (int i = 0; i < k; i++) {
		if (v[i] == -1) { break; } //-1 is the default value for tags, from the resize function
		if (v[i] == tag) {
			res = "Hit"; //A cache hit
			if (i != 0 && k > 1) { //If not the first element and have >1 tag in the set
				v.insert(v.begin(), tag); //Insert at the top the tag (most recently used)
				auto it = v.begin(); //Make iterator to find place in vector
				advance(it, i+1); //Move the iterator to the old entry of the tag
				v.erase(it); //Remove the previous tag (restoring the length of the vector)
			}
			break;
		}
	}
	if (res == "Miss") { //A hit has not been found
		v.insert(v.begin(), tag); //Add the tag to the vector (as most recently used)
		v.erase(v.end() - 1); //Remove the last tag (least recently used) restoring the vector length
	}
	return res;
}