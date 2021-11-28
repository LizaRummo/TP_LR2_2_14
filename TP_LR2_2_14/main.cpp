/*� �������������� �������� � ��������� ������� �������� ���������,
������� ��������� ����� �� ����� � ������� ��� �� �����, ������� ����� ��
0 �� 9 ������� ������, �����, ..., ��������, ������� ������ ����������� �
����� ������.*/

#include <Windows.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int selection(int first, int last);
string in(string str) {
	do {
		getline(cin, str);
	} while (str.empty());
	return str;
}
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
string fileName() {
	string file_name;
	cout << "������� ��� ����� [������ ���.���]: " << endl << "  ";
	file_name = in(file_name);
	while (1) {
		if (!(file_name.find(".txt") + 1 || file_name.find(".dat") + 1 || file_name.find(".csv") + 1)) { cout << "�������� ��� �����" << endl << "[.txt / .dat / .csv]" << endl; }
		else if (file_name.length() >= 255 || file_name.length() <= 4) { cout << "������������ ����� ����� �����" << endl; }
		else if ((file_name.find("<") + 1)) { cout << "������������ ������� � ����� �����" << endl; }
		else return file_name;
		cout << "������� ��� ����� [������ ���.���]: " << endl << "  ";
		file_name = in(file_name);
	}
}

void foundNumbsToConsole(string sentence, string sep_words) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	int length = sentence.length();
	bool found = 0, sep = 1;

	for (int i = 0; i < length; i++) {
		if (sentence[i] != sep_words[0]) sep = 0;
		SetConsoleTextAttribute(hStdOut, BACKGROUND_GREEN);
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
		if (!found && !sep) {
			SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			cout << sentence[i]; }
		found = 0;
	}
	cout << endl;
}
void importToConsole(string sep_words, string sep_sentence) {
	string file_name;
	cout << endl << "������" << endl;
	file_name = fileName();
	ifstream fin(file_name);		// ����� �� �����

	if (!fin.is_open())										// ���� ���� �� ������
		cout << "���� �� ����� ���� ������!" << endl;		// �������� �� ����
	else {
		string input, buf, empty = "", res = "";
		int length = 0, ctr = 0, first_letter = NULL, find_sep_sentence = 0;
		while (!(fin.eof())) {
			getline(fin, input);
			length = input.length();
			for (int i = 0; i < length; i++) {
				ctr++;
				if (input[i] == sep_sentence[0]|| (i + 1) == length) {
					if (!find_sep_sentence) {
						buf.assign(input, first_letter, ctr);
						cout << endl << " � ";
						foundNumbsToConsole(buf, sep_words);
						first_letter = NULL;
						find_sep_sentence = 1;
						ctr = 0;
					}
				}
				else
					if (find_sep_sentence) {
						first_letter = i;
						find_sep_sentence = 0;
					}
				
			}
		}
	}
}

void foundNumbsToFile(string file_name, string sentence, string sep_words) {
	ofstream fout(file_name, ios_base::app);
	int length = sentence.length();
	bool found = 0, sep = 1;
	for (int i = 0; i < length; i++) {
		if (sentence[i] != sep_words[0]) sep = 0;
		if (sentence[i] == '0') { fout << "����"; found = 1; }
		if (sentence[i] == '1') { fout << "����"; found = 1; }
		if (sentence[i] == '2') { fout << "���"; found = 1; }
		if (sentence[i] == '3') { fout << "���"; found = 1; }
		if (sentence[i] == '4') { fout << "������"; found = 1; }
		if (sentence[i] == '5') { fout << "����"; found = 1; }
		if (sentence[i] == '6') { fout << "�����"; found = 1; }
		if (sentence[i] == '7') { fout << "����"; found = 1; }
		if (sentence[i] == '8') { fout << "������"; found = 1; }
		if (sentence[i] == '9') { fout << "������"; found = 1; }
		if (!found && !sep) { fout << sentence[i]; }
		found = 0;
	}
	fout << endl;
}
void importToFile(string sep_words, string sep_sentence) {
	string file_name_imp;
	cout << "������" << endl;
	file_name_imp = fileName();
	ifstream fin(file_name_imp);		// ����� �� �����

	string file_name_exp;
	cout << "�������" << endl;
	file_name_exp = fileName();
	ofstream fout(file_name_exp);

	if (!fin.is_open() || !fout.is_open()) {
		if (!fin.is_open()) cout << "���� ������� �� ����� ���� ������!" << endl;
		if (!fout.is_open()) cout << "���� �������� �� ����� ���� ������!" << endl;
	}
	else {
		string input, buf, empty = "", res = "";
		int length = 0, ctr = 0, first_letter = NULL, find_sep_sentence = 0;
		while (!(fin.eof())) {
			getline(fin, input);
			length = input.length();
			for (int i = 0; i < length; i++) {
				ctr++;
				if (input[i] == sep_sentence[0] || (i + 1) == length) {
					if (!find_sep_sentence) {
						buf.assign(input, first_letter, ctr);
						foundNumbsToFile(file_name_exp, buf, sep_words);
						first_letter = NULL;
						find_sep_sentence = 1;
						ctr = 0;
					}
				}
				else
					if (find_sep_sentence) {
						first_letter = i + 1;
						find_sep_sentence = 0;
					}
			}
		}
	}
}

void createFile() {
	string file_name_new;
	cout << "��������" << endl;
	file_name_new = fileName();
	ofstream fout(file_name_new);

	int number;
	do {
		cout << "������� �����:" << endl;
		string input;
		input = in(input);
		fout << input;
		cout << "���������� ����? " << endl << "  [1 - ��, 0 - ���]" << endl << "  >> ";
		number = selection(0, 1);
	} while (number);
}

void editFile() {
	string file_name_edit;
	cout << "����������" << endl;
	file_name_edit = fileName();
	ifstream fin(file_name_edit);
	ofstream fout(file_name_edit, ios_base::app);
	
	cout << "���������� �����:" << endl;
	while (!(fin.eof())) {
		string buf;
		getline(fin, buf);
		cout << buf;
	}
	cout << endl << "����� �����" << endl;

	int number;
	do {
		cout << "������� �����:" << endl;
		string input;
		input = in(input);
		fout << input;
		cout << "���������� ����? " << endl << "  [1 - ��, 0 - ���]" << endl << "  >> ";
		number = selection(0, 1);
	} while (number);
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
			if (!(cin.fail() || input < first || input > last))
				return input;
			else throw "������ ������������� ����� ����";
		}
		catch (const char*) {
			cin.clear();
			cerr << "������ ������������� ����� ����. ���������� ����" << endl << "> ";
		}
	}
	return input;
}
void print_menu() {
	system("cls");
	cout << endl << "�������� ����� ����:" << endl;
	cout << "  1. ������������� ����� �� ����� � ������� �� �����" << endl;
	cout << "  2. ������������� ����� �� ����� � ��������� � ����" << endl;
	cout << "  3. ������� ����" << endl;
	cout << "  4. ��������� ����" << endl;
	cout << "  ---" << endl;
	cout << "  5. �������� ����������� ����" << endl;
	cout << "  6. �������� ����������� �����������" << endl;
	cout << "  ---" << endl;
	cout << "  0. ����� �� ���������" << endl;
	cout << "  >> ";
}
void menu(string sep_words, string sep_sentence) {
	int point;
	while (1) {

		print_menu();
		switch (point = selection(0, 6)) {
		case 1:
		{
			importToConsole(sep_words, sep_sentence);
			cout << endl<< "������� ����� �������, ����� ����������..." << endl;
			cin.get();
		}
		break;
		case 2:
		{
			importToFile(sep_words, sep_sentence);
		}
		break;
		case 3:
		{
			createFile();
		}
		break;
		case 4:
		{
			editFile();
		}
		break;
		case 5:
		{
			cout << "������� ����� ����������� ����: ";
			string new_sep_words;
			sep_words = in(new_sep_words);
			
		}
		break;
		case 6:
		{
			cout << "������� ����� ����������� �����������: ";
			string new_sep_sentence;
			sep_sentence = in(new_sep_sentence);
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
	string sep_words;
	sep_words = in(sep_words);
	cout << "������� ����������� �����������: ";
	string sep_sentence; 
	sep_sentence = in(sep_sentence);
	menu(sep_words, sep_sentence);
	return 0;
}