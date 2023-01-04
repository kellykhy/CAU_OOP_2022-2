#ifndef _INF_INT_H_
#define _INF_INT_H_
#include <iostream>
using namespace std;
#pragma warning(disable:4996)

class inf_int
{
private:
    char* digits;  // You may modify this to "string digits;" if you want.
    unsigned int length;
    bool thesign;   // true if positive , false if negative.
    // ex) 15311111111111111 -> digits="11111111111111351", length=17, thesign=true;
    // ex) -12345555555555 -> digits="55555555554321", length=14, thesign=false
    // You may modify or add private members of inf_int class. So, it is OK to insert Add() private member function in inf_int class. However, You may not modify public members of inf_int class.

public:
    inf_int();               // assign 0 as a default value
    inf_int(int);
    inf_int(const char*);
    inf_int(const inf_int&); // copy constructor
    ~inf_int(); // destructor

    inf_int& operator=(const inf_int&); // assignment operator

    friend bool operator==(const inf_int&, const inf_int&);
    friend bool operator!=(const inf_int&, const inf_int&);
    friend bool operator>(const inf_int&, const inf_int&);
    friend bool operator<(const inf_int&, const inf_int&);

    friend inf_int operator+(const inf_int&, const inf_int&);
    friend inf_int operator-(const inf_int&, const inf_int&);
    friend inf_int operator*(const inf_int&, const inf_int&);

    friend ostream& operator<<(ostream&, const inf_int&);

    bool ReadThesign() { return thesign; }
    unsigned int ReadLength() { return length; }
    char* ReadDigits() { return digits; }
};

#endif
