#include <iostream>
#include <string>
#include <vector>
#include "Calculater.h"
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

int main(){
	cout << "please enter an expression" << endl;
	string exp;
	cin >> exp;
	Calculater cal;
	float res = cal.execute(exp);  
	cout << exp << " = " << res << endl;
	return 0;
}