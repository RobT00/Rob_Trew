#include <iostream>
#include <string>
#include <fstream>
#include "check.h"

using namespace std;

Check::Check() {

}

bool Check::compare(string& ans, string& corr) {
	if (ans == corr)
		return true;
	return false;
}