#include "Dictionary.h"

void Dictionary::SetDictionary(vector<string>& strArr, int category) {
	static const string FRUIT[4] = { "apple", "banana", "grape","watermelon" };
	static const string ANIMAL[4] = { "dog", "elephant", "monkey", "turtle" };
	static const string COUNTRY[4] = { "brazil", "australia", "canada", "germany" };
	static const string OOP_CONCEPT[4] = { "abstraction", "encapsulation", "inheritance", "polymorphism" };	// 추상화, 캡슐화, 상속, 다형성

	const string* str[4] = { FRUIT, ANIMAL, COUNTRY, OOP_CONCEPT };

	for (int i = 0; i < 4; ++i) {
		strArr.push_back(str[category][i]);
	}
}

// 단어 힌트: 문장
void Dictionary::StatementHint(string strOriginal) {
	// FRUIT
	if (strOriginal == "apple")
		printf("It is mainly red and round");
	else if (strOriginal == "banana")
		printf("Monkeys like this");
	else if (strOriginal == "grape")
		printf("Small, round, purple or pale green fruit");
	else if (strOriginal == "watermelon")
		printf("It is a summer fruit and very big.");
	// ANIMAL
	else if (strOriginal == "dog")
		printf("One of the animals that keeps a lot as pets");
	else if (strOriginal == "elephant")
		printf("Animal with a very long nose.");
	else if (strOriginal == "monkey")
		printf("Animal that likes bananas");
	else if (strOriginal == "turtle")
		printf("One of the animals known to be slow");
	// COUNTRY
	else if (strOriginal == "brazil")
		printf("South American country famous for soccer");
	else if (strOriginal == "australia")
		printf("Easy to see Kangaroo");
	else if (strOriginal == "canada")
		printf("Area of country is the second largest in the world");
	else if (strOriginal == "germany")
		printf("It was a divided country, and it is in Europe");
	// OOP_CONCEPT
	else if (strOriginal == "abstraction")
		printf("Shows only essential attributes and hides unnecessary information");
	else if (strOriginal == "encapsulation")
		printf("Binding data and methods together into objects and limiting the direct access to its internals");
	else if (strOriginal == "inheritance")
		printf("Instance of child class can access both data and behavior of parent class");
	else if (strOriginal == "polymorphism")
		printf("One name(variable, function, class) may have many different meanings");
}

// 단어 힌트: 알파벳
// 알파벳의 빈도 수가 같다면, 사전 순서로 가장 앞쪽의 알파벳이 힌트로 주어짐
void Dictionary::AlphabetHint(string strOriginal) {
	int cnt[26] = { 0 };
	int max_index = -1;
	int max_value = -1;

	int len = strOriginal.length();

	for (int i = 0; i < len; i++) {
		if (strOriginal[i] >= 'a' && strOriginal[i] <= 'z')
			cnt[strOriginal[i] - 'a']++;
	}

	for (int i = 0; i < 26; i++) {
		if (cnt[i] > max_value) {
			max_index = i;
			max_value = cnt[i];
		}
	}
	printf("Most frequently used alphabet: %c", 'a' + max_index);
}