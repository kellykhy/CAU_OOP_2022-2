// OOP project01
#include <algorithm>
#include<iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "proj1_class.h"
using namespace std;
#define MAX 50

int students::check_same_id(string id) {
	int result = 0;
	for (int i = 0; i < students_num; i++) {
		if (id.compare(student_data[i].student_id) == 0)
			result = 1;
	}
	return result;
}
void students::insert() {
	student new_student;
	string line;
	ofstream myfile;
	myfile.open("student_info.txt", ios::app | ios::ate);
	if (myfile.tellp() == 0)
	{
		myfile << setw(15) << "Name";
		myfile << setw(20) << "Student ID";
		myfile << setw(25) << "Dept";
		myfile << setw(15) << "Birth Year";
		myfile << setw(15) << "Tel" << endl;
	}
	cout << "Name ? ";
	getline(cin, new_student.name);
	cout << "Student ID(10 digits) ? ";
	getline(cin, new_student.student_id);
	if (check_same_id(new_student.student_id))
		cout << endl << "Error : Already inserted" << endl << endl;
	else {
		cout << "Birth Year (4 digits) ? ";
		getline(cin, new_student.birth_year);
		cout << "Department ? ";
		getline(cin, new_student.dept);
		cout << "Tel ? ";
		getline(cin, new_student.tel);
		cout << endl;

		student_data[students_num] = new_student;

		myfile << setw(15) << new_student.name;
		myfile << setw(20) << new_student.student_id;
		myfile << setw(25) << new_student.dept;
		myfile << setw(15) << new_student.birth_year;
		myfile << setw(15) << new_student.tel << endl;

		students_num++;
	}
	myfile.close();
}

bool compare1(student a, student b) { // 1. sort by name
	string comp1 = a.name;
	string comp2 = b.name;

	return comp1 < comp2;
}
bool compare2(student a, student b) { // 2. sort by std id (num)
	string comp1 = a.student_id;
	string comp2 = b.student_id;
	stoi(comp1);
	stoi(comp2);
	return comp1 < comp2;
}
bool compare3(student a, student b) { // 3. sort by admission year (num)
	string comp1 = a.student_id.substr(0, 4);
	string comp2 = b.student_id.substr(0, 4);
	stoi(comp1);
	stoi(comp2);
	return comp1 < comp2;
}
bool compare4(student a, student b) { // 4. sort by department name
	string comp1 = a.dept;
	string comp2 = b.dept;

	return comp1 < comp2;
}

static inline void ltrim(string& s) {
	s.erase(s.begin(), find_if(s.begin(), s.end(), [](int ch) {
		return !isspace(ch);
		}));
}
students::students() {
	students_num = 0;
	sorting_option = 1;
	string line;
	string chunk;

	ofstream myfile_make;
	myfile_make.open("student_info.txt", ios::app);
	myfile_make.close();

	fstream myfile;
	myfile.open("student_info.txt");
	if (myfile.is_open()) {
		getline(myfile, line);
		while (getline(myfile, line))
		{
			chunk = line.substr(0, 15);
			ltrim(chunk);
			student_data[students_num].name = chunk;
			chunk = line.substr(15, 20);
			ltrim(chunk);
			student_data[students_num].student_id = chunk;
			chunk = line.substr(35, 25);
			ltrim(chunk);
			student_data[students_num].dept = chunk;
			chunk = line.substr(60, 15);
			ltrim(chunk);
			student_data[students_num].birth_year = chunk;
			chunk = line.substr(75, 15);
			ltrim(chunk);
			student_data[students_num].tel = chunk;
			students_num += 1;
		}
		myfile.close();
	}
	else
		cout << "Unable to open file";
}

void students::sort_display() {
	string line;
	ifstream myfile;

	if (sorting_option == 1) // 1. Sort by name
		sort(student_data, student_data + students_num, compare1);
	else if (sorting_option == 2) // 2. Sort by student ID
		sort(student_data, student_data + students_num, compare2);
	else if (sorting_option == 3) // 3. Sort by admission year
		sort(student_data, student_data + students_num, compare3);
	else if (sorting_option == 4) // 4. Sort by department name
		sort(student_data, student_data + students_num, compare4);
	for (int i = 0; i < students_num; i++) {
		cout << setw(15) << student_data[i].name;
		cout << setw(20) << student_data[i].student_id;
		cout << setw(25) << student_data[i].dept;
		cout << setw(15) << student_data[i].birth_year;
		cout << setw(15) << student_data[i].tel << endl;
	}
}

void students::search() {
	int choice = 0;
	string line;
	string keyword;

	cout << "1. Search by name" << endl;
	cout << "2. Search by student ID (10 numbers)" << endl;
	cout << "3. Search by admission year (4 numbers)" << endl;
	cout << "4. Search by department name" << endl;
	cout << "5. List All" << endl;

	cin >> choice;
	cin.ignore();
	cout << endl;
	if (choice == 1) {
		cout << "Name keyword? ";
		cin >> keyword;
		cin.ignore();
		for (int i = 0; i < students_num; i++) {
			if (student_data[i].name.find(keyword) != string::npos) {
				cout << setw(15) << student_data[i].name;
				cout << setw(20) << student_data[i].student_id;
				cout << setw(25) << student_data[i].dept;
				cout << setw(15) << student_data[i].birth_year;
				cout << setw(15) << student_data[i].tel;
			}
		}
	}
	else if (choice == 2) {
		cout << "student id keyword? ";
		cin >> keyword;
		cin.ignore();
		for (int i = 0; i < students_num; i++) {
			if (student_data[i].student_id.find(keyword) != string::npos) {
				cout << setw(15) << student_data[i].name;
				cout << setw(20) << student_data[i].student_id;
				cout << setw(25) << student_data[i].dept;
				cout << setw(15) << student_data[i].birth_year;
				cout << setw(15) << student_data[i].tel;
			}
		}
	}
	else if (choice == 3) {
		cout << "admission year keyword? ";
		cin >> keyword;
		cin.ignore();
		for (int i = 0; i < students_num; i++) {
			if (student_data[i].student_id.substr(0,4).find(keyword) != string::npos) {
				cout << setw(15) << student_data[i].name;
				cout << setw(20) << student_data[i].student_id;
				cout << setw(25) << student_data[i].dept;
				cout << setw(15) << student_data[i].birth_year;
				cout << setw(15) << student_data[i].tel;
			}
		}
	}
	else if (choice == 4) {
		cout << "department name keyword? ";
		cin >> keyword;
		cin.ignore();
		for (int i = 0; i < students_num; i++) {
			if (student_data[i].dept.find(keyword) != string::npos) {
				cout << setw(15) << student_data[i].name;
				cout << setw(20) << student_data[i].student_id;
				cout << setw(25) << student_data[i].dept;
				cout << setw(15) << student_data[i].birth_year;
				cout << setw(15) << student_data[i].tel;
			}
		}
	}
	else {
		sort_display();
	}
	cout << endl << endl;
}

int main() {
	int choice = 0;
	string data[MAX];
	students student_data;

	while (1) {
		cout << "[Student Information Management System]" << endl;
		cout << "1. Insertion" << endl;
		cout << "2. Search" << endl;
		cout << "3. Sorting Option" << endl;
		cout << "4. Exit" << endl;

		cin >> choice;
		cin.ignore();
		if (choice == 1)
			student_data.insert();
		else if (choice == 2)
			student_data.search();
		else if (choice == 3)
		{
			cout << "1. Sort by Name" << endl;
			cout << "2. Sort by Student ID" << endl;
			cout << "3. Sort by Admission Year" << endl;
			cout << "4. Sort by Department name" << endl;
			cin >> student_data.sorting_option;
			cin.ignore();
		}
		else if (choice == 4) // 4. Exit
			break;
	}
	return 0;
}
