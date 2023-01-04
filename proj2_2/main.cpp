#include "inf_int.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	string str;
	char op;
	int op_pos;
	cout << "This calculator program supports addition(+), subtraction(-), and multiplication(*) of infinite precision integers." << endl << endl;
	cout << "ex1) 25555555555551111 + 2111111111" << endl;
	cout << "ex2) 345 - 1111111111111111111111111111111111111111111111111111" << endl;
	cout << "ex3) 333333333333333333333333 * 73755" << endl << endl;

	while (1) {
		cout << "Input : ";
		getline(cin, str);
		if (str == "0")
			break;
		op_pos = str.find(' ') + 1;
		op = str[op_pos];

		char* c1 = new char[op_pos-1 +1];
		char* c2 = new char[str.length() - op_pos - 2 +1];

		strcpy(c1, (str.substr(0, op_pos-1)).c_str());
		strcpy(c2, (str.substr(op_pos + 2)).c_str());

		cout << "Output : ";
		switch (op)
		{
		case '+':
			cout << inf_int(c1) + inf_int(c2) << endl;
			break;
		case '-':
			cout << inf_int(c1) - inf_int(c2) << endl;
			break;
		case '*':
			cout << inf_int(c1) * inf_int(c2) << endl;
			break;
		}
		cout << endl;

		delete[] c1;
		delete[] c2;
	}

	return 0;
}
