#include <iostream>
#include <string>
#include <vector>
using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::string;

#ifndef CALCULATER_H
#define CALCULATER_H
class Calculater {
	public:
		float execute(string expression);
	private:
		const vector<char> valid_char = {'0', '1', '2', '3', '4', '5', 
		                                 '6', '7', '8', '9', '.', '+',
		                                 '-', '*', '/'};
		string get_rid_of_brace(string arg);
};

string Calculater::get_rid_of_brace(string arg) {
	if (arg[0] == ' ')
		arg = arg.substr(1,arg.size()-1);
	if (arg[arg.size()-1] == ' ')
		arg = arg.substr(0, arg.size()-2);
	if (arg[0] == '(' && arg[arg.size()-1] == ')')
		return arg.substr(1, arg.size()-2);
	else
		return arg; 
}

float Calculater::execute(string expression) {
	//empty check
	int length = expression.size();
	if (length <= 0) {
		cout << "empty expression" << endl;
		return 0;
	}

	string left_argument = "";
	char operator_char = '+';
	string right_argument = "";

	// find the operator index
	int end_index = -1;
	int brace_count = 0;
	for (int i=0; i<length; ++i){
		char c = expression[i];
		//check if it is a valid char
		/*
		int id = find(valid_char.begin(), valid_char.end(), c);
		if (id != 1) {
			cout << "invalid expression at " << c << endl;
			return 0;
		}*/
		if (i == 0 && (c=='+' || c=='-' || c=='*' || c=='/')) {
			cout << "there is no left argument" << endl;
			return 0;
		} else if (i > 0 && brace_count==0 && (c=='+' || c=='-' || c=='*' || c=='/')){
			end_index = i-1;
			break;
		} else if (c == '(') {
			++brace_count;
		} else if (c == ')') {
			if (brace_count == 1) {
				end_index = i;
				break;
			} else {
				--brace_count;
			}
		} else if (c == ' ' || c == '.') {
			continue;
		}
	}
	if (end_index == length-1 || end_index == -1) {
		return atof(expression.c_str());
	}

	int operator_index = end_index+1;
	left_argument = expression.substr(0,operator_index);
	operator_char = expression[operator_index];
	right_argument = expression.substr(operator_index+1, length);
	
	left_argument = get_rid_of_brace(left_argument);
	right_argument = get_rid_of_brace(right_argument);

	switch (operator_char) {
		case '+':
			return execute(left_argument) + execute(right_argument);
			break;
		case '-':
			return execute(left_argument) - execute(right_argument);
			break;
		case '*':
			return execute(left_argument) * execute(right_argument);
			break;
		case '/':
			return execute(left_argument) / execute(right_argument);
			break;
		default:
			cout << "operator not match" << endl;
			return 0;
	}

}
#endif