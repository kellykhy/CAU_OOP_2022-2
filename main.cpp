#include "inf_int.h"
#include <iostream>

using namespace std;

int main()
{
	inf_int a, e;
	inf_int b(100);
	inf_int c("321111111111122222222222233333333333444444444445555555555");
	inf_int d("123451987651234572749499923455022211");
	inf_int f = d;
	inf_int g(f);

	inf_int x = b * c;
	inf_int y = c - d;
	inf_int z = g + f;

	//inf_int h(1);
	//inf_int k(4);

	//cout << "h(1) < k(4) : " << (h < k) << endl;

	if (f == d) {
		cout << "a : " << a << endl;
		cout << "b : " << b << endl;
		cout << "c : " << c << endl;
		cout << "d : " << d << endl;
		cout << "e : " << e << endl;
		cout << "f : " << f << endl;
		cout << "g : " << g << endl;

		cout << "x = b * c : " << x << endl;
		cout << "y = c - d : " << y << endl;
		cout << "z = g + f : " << z << endl;
	}

	return 0;
}
