#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

int main() {
	setlocale(LC_ALL, "russian");
	string proc;
	string tmp;
	regex reg("(([ ]+[IN].+[ ]+)|(.+[ ]+))?(Беларусь|Венгрия|Польша|Болгария)(([ ]+<[0-9]+>)?[ ]+)((площадь(([ ]+.+[ ]+)|([ ]+))<[0-9]+> кв\\.км)|(население[ ]+<[0-9]+>))");//[ ]+.+[ ]+[<]?
	regex reg_wrong_square("(([ ]+[IN].+[ ]+)|(.+[ ]+))?(Беларусь|Венгрия|Польша|Болгария)(([ ]+<[0-9]+>)?[ ]+)((площадь[ ]+.+(([ ]+<)|([ ]+)).*> кв\\.км)|(население[ ]+<([0-9]+)>))");
	regex reg_wrong_people("(([ ]+[IN].+[ ]+)|(.+[ ]+))?(Беларусь|Венгрия|Польша|Болгария)(([ ]+<[0-9]+>[ ]+)|([ ]+))((площадь[ ]+.+[ ]+[<]?[0-9]+> кв\\.км)|(население[ ]+<(.*)>))");

	ifstream fin("input.txt");
	vector <string> result;
	cout << "Это MATCH: " << endl;
	while (getline(fin, proc)) {
		if (regex_match(proc, reg))
			result.push_back(proc);
		else if (regex_match(proc, reg_wrong_square) and regex_match(proc, reg_wrong_people))
			result.push_back("Неправильный тип данных в площади и населении! : " + proc);
		else if (regex_match(proc, reg_wrong_square) and !regex_match(proc, reg_wrong_people))
			result.push_back("Неправильный тип данных в площади! : " + proc);
		else if (!regex_match(proc, reg_wrong_square) and regex_match(proc, reg_wrong_people))
			result.push_back("Неправильный тип данных в населении! : " + proc);
	}

	for (auto i : result)
		cout << i << endl;
	cout << "Это всё!" << endl;
	result.clear();
	fin.clear();
	fin.seekg(0);
	smatch m;
	cout << endl << "ЭТО SEARCH: " << endl;
	while (getline(fin, proc)) {
		if (regex_search(proc, m, reg))
			result.push_back(m.str());
		else if (regex_search(proc, m, reg_wrong_square) and regex_search(proc, m, reg_wrong_people))
			result.push_back("Неправильный тип данных в площади и населении! : " + m.str());
		else if (regex_search(proc, m, reg_wrong_square) and !regex_search(proc, m, reg_wrong_people))
			result.push_back("Неправильный тип данных в площади! : " + m.str());
		else if (!regex_search(proc, m, reg_wrong_square) and regex_search(proc, m, reg_wrong_people))
			result.push_back("Неправильный тип данных в населении! : " + m.str());
	}
	for (auto i : result)
		cout << i << endl;
	cout << "Это всё!" << endl;
}