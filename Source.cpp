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
	regex reg("(([ ]+[IN].+[ ]+)|(.+[ ]+))?(��������|�������|������|��������)(([ ]+<[0-9]+>)?[ ]+)((�������(([ ]+.+[ ]+)|([ ]+))<[0-9]+> ��\\.��)|(���������[ ]+<[0-9]+>))");//[ ]+.+[ ]+[<]?
	regex reg_wrong_square("(([ ]+[IN].+[ ]+)|(.+[ ]+))?(��������|�������|������|��������)(([ ]+<[0-9]+>)?[ ]+)((�������[ ]+.+(([ ]+<)|([ ]+)).*> ��\\.��)|(���������[ ]+<([0-9]+)>))");
	regex reg_wrong_people("(([ ]+[IN].+[ ]+)|(.+[ ]+))?(��������|�������|������|��������)(([ ]+<[0-9]+>[ ]+)|([ ]+))((�������[ ]+.+[ ]+[<]?[0-9]+> ��\\.��)|(���������[ ]+<(.*)>))");

	ifstream fin("input.txt");
	vector <string> result;
	cout << "��� MATCH: " << endl;
	while (getline(fin, proc)) {
		if (regex_match(proc, reg))
			result.push_back(proc);
		else if (regex_match(proc, reg_wrong_square) and regex_match(proc, reg_wrong_people))
			result.push_back("������������ ��� ������ � ������� � ���������! : " + proc);
		else if (regex_match(proc, reg_wrong_square) and !regex_match(proc, reg_wrong_people))
			result.push_back("������������ ��� ������ � �������! : " + proc);
		else if (!regex_match(proc, reg_wrong_square) and regex_match(proc, reg_wrong_people))
			result.push_back("������������ ��� ������ � ���������! : " + proc);
	}

	for (auto i : result)
		cout << i << endl;
	cout << "��� ��!" << endl;
	result.clear();
	fin.clear();
	fin.seekg(0);
	smatch m;
	cout << endl << "��� SEARCH: " << endl;
	while (getline(fin, proc)) {
		if (regex_search(proc, m, reg))
			result.push_back(m.str());
		else if (regex_search(proc, m, reg_wrong_square) and regex_search(proc, m, reg_wrong_people))
			result.push_back("������������ ��� ������ � ������� � ���������! : " + m.str());
		else if (regex_search(proc, m, reg_wrong_square) and !regex_search(proc, m, reg_wrong_people))
			result.push_back("������������ ��� ������ � �������! : " + m.str());
		else if (!regex_search(proc, m, reg_wrong_square) and regex_search(proc, m, reg_wrong_people))
			result.push_back("������������ ��� ������ � ���������! : " + m.str());
	}
	for (auto i : result)
		cout << i << endl;
	cout << "��� ��!" << endl;
}