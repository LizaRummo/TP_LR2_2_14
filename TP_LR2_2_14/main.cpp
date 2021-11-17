/*� �������������� �������� � ��������� ������� �������� ���������,
������� ��������� ����� �� ����� � ������� ��� �� �����, ������� ����� ��
0 �� 9 ������� ������, �����, ..., ��������, ������� ������ ����������� �
����� ������.*/

#include <Windows.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

string in(string str) {
	do {
		getline(cin, str);
	} while (str.empty());
	return str;
}

//�������� ��� ����� �����
string checkNumber(string input) {
	string buf = "", res = "";
	while (true) {
		int length = 0, ctr_err = 0;
		int first_numb = NULL, find_err = 0;
		length = input.length();
		for (int i = 0; i <= length; i++) {
			if (input[i] < '0' || input[i] > '9' ||
				input[i] == '\0' || input[i] == '\n') {
				if (!find_err) {
					buf.assign(input, first_numb, i - (res.length() + ctr_err));
					res += buf;
					first_numb = NULL;
					find_err = 1;
					ctr_err++;
				}
			}
			else
				if (find_err) {
					first_numb = i;
					find_err = 0;
				}
		}
		return res;
	}

}

int selection(int first, int last) {
	int input;
	string buf;
	while (true) {
		try
		{
			buf = in(buf);
			buf = checkNumber(buf);
			input = stoi(buf);
			//cin >> input;
			if (!(cin.fail() || input < first || input > last))
				return input;
			else throw "������ ������������� ����� ����";
		}
		catch (const char*) {
			cin.clear();
			cerr << "������ ������������� ����� ����. ���������� ����" << endl << "> ";
		}
		//cin.ignore(32767, '\n');
	}
	return input;
}

void print_menu() {
	system("cls");
	//statusbar();
	//cout << "������� ����" << endl;
	cout << endl << "�������� ����� ����:" << endl;
	cout << "  1. ��������" << endl;
	cout << "  2. �������" << endl;
	cout << "  3. �������� ������" << endl;
	cout << "  4. ������� ������ ������" << endl;
	cout << "  ---" << endl;
	cout << "  5. ��������� � ����" << endl;
	cout << "  6. ��������� �� �����" << endl;
	cout << "  ---" << endl;
	cout << "  7. ����� �� �������" << endl;
	cout << "  ---" << endl;
	cout << "  0. ����� �� ���������" << endl;
	cout << "  >> ";
}

void found_numbs(string sentence) {
	int length = sentence.length();
	bool found = 0;
	for (int i = 0; i < length; i++) {
		if (sentence[i] == '0') {cout << "����"; found = 1;}
		if (sentence[i] == '1') { cout << "����"; found = 1; }
		if (sentence[i] == '2') { cout << "���"; found = 1; }
		if (sentence[i] == '3') { cout << "���"; found = 1; }
		if (sentence[i] == '4') { cout << "������"; found = 1; }
		if (sentence[i] == '5') { cout << "����"; found = 1; }
		if (sentence[i] == '6') { cout << "�����"; found = 1; } 
		if (sentence[i] == '7') { cout << "����"; found = 1; }
		if (sentence[i] == '8') { cout << "������"; found = 1; }
		if (sentence[i] == '9') { cout << "������"; found = 1; }
		if (!found) cout << sentence[i];
		found = 0;
	}
	cout << endl;
}

void import(string sep_words, string sep_sentence) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	string file_name;
	cout << "������� ��� ����� [������ ���.���]: " << endl << "  ";
	file_name = in(file_name);
	while (1) {
		if (!(file_name.find(".txt") + 1 || file_name.find(".dat") + 1 || file_name.find(".csv") + 1)) { cout << "�������� ��� �����" << endl << "[.txt / .dat / .csv]" << endl; }
		else if (file_name.length() >= 255 || file_name.length() <= 4) { cout << "������������ ����� ����� �����" << endl; }
		else if ((file_name.find("<") + 1)) { cout << "������������ ������� � ����� �����" << endl; }
		else break;
		cout << "������� ��� ����� [������ ���.���]: " << endl << "  ";
		file_name = in(file_name);
	}

	ifstream fin(file_name);		// ����� �� �����

	if (!fin.is_open())										// ���� ���� �� ������
		cout << "���� �� ����� ���� ������!" << endl;		// �������� �� ����
	else {

		while (!(fin.eof())/*||(buf!=empty)*/) {
			string input = "", buf = "", empty = "", res = "";
			int length = 0, ctr = 0, first_letter = NULL, find_sep_sentence = 0;

			getline(fin, input);
			//getline(fin, input);
			length = input.length();
			for (int i = 0; i < length; i++) {
				if (input[i] == sep_sentence[0]) {
					if (!find_sep_sentence) {
						ctr++;
						buf.assign(input, first_letter, ctr);
						//����� ����
						found_numbs(buf);

						first_letter = NULL;
						find_sep_sentence = 1;
						ctr = 0;
					}
					//ctr++;
				}
				else
					if (find_sep_sentence) {
						first_letter = i;
						find_sep_sentence = 0;
					}
				ctr++;
			}
			
		}
	}
}

void menu() {
	int point;
	while (1) {

		print_menu();
		switch (point = selection(0, 7)) {
		case 1:
		{
			
		}
		break;
		case 2:
		{
			
		}
		break;
		case 3:
		{
			
		}
		break;
		case 4:
		{
			
		}
		break;
		case 5:
		{
			
		}
		break;
		case 6:
		{
			
		}
		break;
		case 7:
		{
			
		}
		break;
		case 0:
			exit(0);
		}
	}
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	cout << "����� ����������!" << endl;
	cout << "������� ����������� ����: ";
	string sep_words = "";
	sep_words = in(sep_words);
	cout << "������� ����������� �����������: ";
	string sep_sentence = ""; 
	sep_sentence = in(sep_sentence);
	//menu();
	import(sep_words, sep_sentence);
	return 0;
}