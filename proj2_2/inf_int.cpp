#include "inf_int.h"
#include <cstring>
#include <string>

// 
// to be filled by students
//
// example :
//
// bool operator==(const inf_int& a , const inf_int& b)
// {
//     // we assume 0 is always positive.
//     if ( (strcmp(a.digits , b.digits)==0) && a.thesign==b.thesign )
//         return true;
//     return false;
// }
//

inf_int::inf_int()
{
	this->digits = new char[2];

	this->digits[0] = '0';
	this->digits[1] = '\0';
	this->length = 1;
	this->thesign = true;
}

inf_int::inf_int(int n) {
	int count = 0;
	int i = 0;
	int j = 0;
	if (n < 0) {
		i = -n;
		this->thesign = false;
	}
	else {
		i = n;
		this->thesign = true;
	}
	j = i;
	do {
		count++;
		i = i / 10;
	} while (i > 0);
	this->digits = new char[count + 1];
	sprintf(this->digits, "%d", j);
	this->length = strlen(this->digits);
}


inf_int::inf_int(const char* str)
{
	char* c1;
	c1 = new char[strlen(str) + 1];
	strcpy(c1, str);
	this->thesign = true;
	if (*c1 == '-') {
		this->thesign = false;
		c1++;
	}

	this->digits = new char[strlen(c1) + 1];
	strcpy(this->digits, c1);
	this->length = strlen(c1);

	if (this->thesign == false)
		c1--;
	delete[] c1;
}

inf_int::inf_int(const inf_int& a) {  //copy constructor
	this->digits = new char[a.length + 1];

	strcpy(this->digits, a.digits);
	this->length = a.length;
	this->thesign = a.thesign;
}

inf_int::~inf_int() { //destructor
	delete digits;
}

ostream& operator<<(ostream& out, const inf_int& a)
{
	if (a.thesign == false)
		out << '-';
	out << a.digits;
	return out;
}

inf_int& inf_int::operator=(const inf_int& a)
{
	if (this->digits) {
		delete this->digits;
	}
	this->digits = new char[a.length + 1];

	strcpy(this->digits, a.digits);
	this->length = a.length;
	this->thesign = a.thesign;

	return *this;
}


bool operator==(const inf_int& a, const inf_int& b)
{
	if ((strcmp(a.digits, b.digits) == 0) && a.thesign == b.thesign)
		return true;
	return false;
}

bool operator!=(const inf_int& a, const inf_int& b)
{
	return !operator==(a, b);
}

bool operator>(const inf_int& a, const inf_int& b)
{
	if (a.thesign == b.thesign) { //부호가 같을 경우
		if (a.length != b.length) {
			if (a.length > b.length)
				return true;
			else
				return false;

		}
		else {
			if (strcmp(a.digits, b.digits) == 1)
				return true;
			else
				return false;
		}
	}
	else        // 부호가 다를 경우
		return (a.thesign == true);
}

bool operator<(const inf_int& a, const inf_int& b)
{
	if (operator>(a, b) || operator==(a, b)) {
		return false;
	}
	else {
		return true;
	}
}

inf_int operator+(const inf_int& a, const inf_int& b)
{
	bool sign = true;
	char* c1, * c2;
	string str1, str2;

	inf_int v1 = a;
	inf_int v2 = b;
	if (v1.thesign == false && v2.thesign == false) {
		v1.thesign = true;
		v2.thesign = true;
		sign = false;
	}
	else if (v1.thesign == false) {
		v1.thesign = true;
		return v2 - v1;
	}
	else if (v2.thesign == false) {
		v2.thesign = true;
		return v1 - v2;
	}
	if (v1 > v2) {
		str1 = v1.digits;
		str2 = v2.digits;
	}
	else {
		str1 = v2.digits;
		str2 = v1.digits;
	}
	str1.insert(0, "0");
	reverse(str1.begin(), str1.end());
	c1 = new char[str1.length() + 1];
	strcpy(c1, str1.c_str());

	reverse(str2.begin(), str2.end());
	c2 = new char[str2.length() + 1];
	strcpy(c2, str2.c_str());

	for (int i = 0; i < (int)strlen(c2); i++) {
		*(c1 + i) = *(c1 + i) + *(c2 + i) - 48;
	}
	for (int i = 0; i < (int)strlen(c1); i++) {
		if (*(c1 + i) >= 58)
		{
			*(c1 + i) -= 10;
			*(c1 + i + 1) += 1;
		}
	}
	str1 = c1;
	reverse(str1.begin(), str1.end());
	if (str1.front() == '0')
		str1.erase(str1.begin());
	if (sign == false)
		str1.insert(0, "-");

	delete[] c1;
	delete[] c2;

	return inf_int(str1.c_str());
}

inf_int operator-(const inf_int& a, const inf_int& b)
{
	bool sign = true;
	char* c1, * c2;
	string str1, str2;

	inf_int v1 = a;
	inf_int v2 = b;
	if (v1.thesign == false && v2.thesign == false) {
		v1.thesign = true;
		v2.thesign = true;
		return v2 - v1;
	}
	else if (v2.thesign == false) {
		v2.thesign = true;
		return v1 + v2;
	}
	else if (v1.thesign == false) {
		v2.thesign = false;
		return v1 + v2;
	}

	if (v1 < v2) {
		str1 = v2.digits;
		str2 = v1.digits;
		sign = false;
	}
	else {
		str1 = v1.digits;
		str2 = v2.digits;
		sign = true;
	}

	reverse(str1.begin(), str1.end());
	c1 = new char[str1.length() + 1];
	strcpy(c1, str1.c_str());

	reverse(str2.begin(), str2.end());
	c2 = new char[str2.length() + 1];
	strcpy(c2, str2.c_str());

	for (int i = 0; i < (int)strlen(c2); i++)
		*(c1 + i) = *(c1 + i) - *(c2 + i) + 48;
	for (int i = 0; i < (int)strlen(c1) - 1; i++) {
		if (*(c1 + i) < 48) {
			*(c1 + i) += 10;
			*(c1 + i + 1) -= 1;
		}
	}
	str1 = c1;
	reverse(str1.begin(), str1.end());
	while (str1.front() == '0' && str1.length() != 1) {
		str1.erase(str1.begin());
	}
	if (sign == false)
		str1.insert(0, "-");

	delete[] c1;
	delete[] c2;

	return inf_int(str1.c_str());
}

inf_int operator*(const inf_int& a, const inf_int& b)
{
	if (strcmp(a.digits, "0") == 0 || strcmp(b.digits, "0") == 0)
		return inf_int();

	bool sign = true;
	char* c1, * c2;
	int* c3;
	string str1, str2, str3;
	inf_int result;

	inf_int v1 = a;
	inf_int v2 = b;

	if (v1.thesign != v2.thesign)
		sign = false;
	v1.thesign = true;
	v2.thesign = true;

	if (v1 > v2) {
		str1 = v1.digits;
		str2 = v2.digits;
	}
	else {
		str1 = v2.digits;
		str2 = v1.digits;
	}

	reverse(str1.begin(), str1.end());
	c1 = new char[str1.length() + 1];
	strcpy(c1, str1.c_str());

	reverse(str2.begin(), str2.end());
	c2 = new char[str2.length() + 1];
	strcpy(c2, str2.c_str());

	c3 = new int[str1.length() + 1];

	for (int i = 0; i < (int)strlen(c2); i++) {
		for (int i = 0; i < str1.length() + 1; i++)
			c3[i] = 0;
		str3.erase(str3.begin(), str3.end());
		for (int j = 0; j < (int)strlen(c1); j++)
			*(c3 + j) = (*(c1 + j)-48) * (*(c2 + i)-48);

		for (int j = 0; j < str1.length(); j++) {
			if (*(c3 + j) >= 10) {
				int a = *(c3 + j);
				*(c3 + j) = a % 10;
				*(c3 + j + 1) += a / 10;
			}
		}

		for (int i = 0; i < str1.length() + 1; i++) {
			str3 += to_string(c3[i]);
		}

		reverse(str3.begin(), str3.end());
		if (str3.front() == '0')
			str3.erase(str3.begin());
		for (int h = 0; h < i; h++)
			str3.insert(str3.length(), "0");
		result = result + inf_int(str3.c_str());
	}
	result.thesign = sign;

	delete[] c1;
	delete[] c2;
	delete[] c3;
	return result;
}
