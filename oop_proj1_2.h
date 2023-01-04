#include <string>
#define MAX 50
using namespace std;

class student
{
public:
	string name;
	string student_id;
	string dept;
	string birth_year;
	string tel;
};

class students
{
public:
	student student_data[MAX];
	int sorting_option;
	int students_num;
public:
	students();
	void insert();
	void search();
	void sort_display();
	int check_same_id(string id);
};