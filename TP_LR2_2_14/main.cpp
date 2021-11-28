/*С использованием файловых и строковых потоков написать программу,
которая считывает текст из файла и выводит его на экран, заменив цифры от
0 до 9 словами «ноль», «один», ..., «девять», начиная каждое предложение с
новой строки.*/

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
	cout << "Введите имя файла [формат имя.тип]: " << endl << "  ";
	file_name = in(file_name);
	while (1) {
		if (!(file_name.find(".txt") + 1 || file_name.find(".dat") + 1 || file_name.find(".csv") + 1)) { cout << "Неверный тип файла" << endl << "[.txt / .dat / .csv]" << endl; }
		else if (file_name.length() >= 255 || file_name.length() <= 4) { cout << "Недопустимая длина имени файла" << endl; }
		else if ((file_name.find("<") + 1)) { cout << "Недопустимые символы в имени файла" << endl; }
		else return file_name;
		cout << "Введите имя файла [формат имя.тип]: " << endl << "  ";
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
		if (sentence[i] == '0') {cout << "ноль"; found = 1;}
		if (sentence[i] == '1') { cout << "один"; found = 1; }
		if (sentence[i] == '2') { cout << "два"; found = 1; }
		if (sentence[i] == '3') { cout << "три"; found = 1; }
		if (sentence[i] == '4') { cout << "четыре"; found = 1; }
		if (sentence[i] == '5') { cout << "пять"; found = 1; }
		if (sentence[i] == '6') { cout << "шесть"; found = 1; } 
		if (sentence[i] == '7') { cout << "семь"; found = 1; }
		if (sentence[i] == '8') { cout << "восемь"; found = 1; }
		if (sentence[i] == '9') { cout << "девять"; found = 1; }
		if (!found && !sep) {
			SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			cout << sentence[i]; }
		found = 0;
	}
	cout << endl;
}
void importToConsole(string sep_words, string sep_sentence) {
	string file_name;
	cout << endl << "Импорт" << endl;
	file_name = fileName();
	ifstream fin(file_name);		// вывод из файла

	if (!fin.is_open())										// если файл не открыт
		cout << "Файл не может быть открыт!" << endl;		// сообщить об этом
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
						cout << endl << " — ";
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
		if (sentence[i] == '0') { fout << "ноль"; found = 1; }
		if (sentence[i] == '1') { fout << "один"; found = 1; }
		if (sentence[i] == '2') { fout << "два"; found = 1; }
		if (sentence[i] == '3') { fout << "три"; found = 1; }
		if (sentence[i] == '4') { fout << "четыре"; found = 1; }
		if (sentence[i] == '5') { fout << "пять"; found = 1; }
		if (sentence[i] == '6') { fout << "шесть"; found = 1; }
		if (sentence[i] == '7') { fout << "семь"; found = 1; }
		if (sentence[i] == '8') { fout << "восемь"; found = 1; }
		if (sentence[i] == '9') { fout << "девять"; found = 1; }
		if (!found && !sep) { fout << sentence[i]; }
		found = 0;
	}
	fout << endl;
}
void importToFile(string sep_words, string sep_sentence) {
	string file_name_imp;
	cout << "Импорт" << endl;
	file_name_imp = fileName();
	ifstream fin(file_name_imp);		// вывод из файла

	string file_name_exp;
	cout << "Экспорт" << endl;
	file_name_exp = fileName();
	ofstream fout(file_name_exp);

	if (!fin.is_open() || !fout.is_open()) {
		if (!fin.is_open()) cout << "Файл импорта не может быть открыт!" << endl;
		if (!fout.is_open()) cout << "Файл экспорта не может быть открыт!" << endl;
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
	cout << "Создание" << endl;
	file_name_new = fileName();
	ofstream fout(file_name_new);

	int number;
	do {
		cout << "Введите текст:" << endl;
		string input;
		input = in(input);
		fout << input;
		cout << "Продолжить ввод? " << endl << "  [1 - да, 0 - нет]" << endl << "  >> ";
		number = selection(0, 1);
	} while (number);
}

void editFile() {
	string file_name_edit;
	cout << "Дополнение" << endl;
	file_name_edit = fileName();
	ifstream fin(file_name_edit);
	ofstream fout(file_name_edit, ios_base::app);
	
	cout << "Содержимое файла:" << endl;
	while (!(fin.eof())) {
		string buf;
		getline(fin, buf);
		cout << buf;
	}
	cout << endl << "Конец файла" << endl;

	int number;
	do {
		cout << "Введите текст:" << endl;
		string input;
		input = in(input);
		fout << input;
		cout << "Продолжить ввод? " << endl << "  [1 - да, 0 - нет]" << endl << "  >> ";
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
			else throw "Выбран отсутствующий пункт меню";
		}
		catch (const char*) {
			cin.clear();
			cerr << "Выбран отсутствующий пункт меню. Повтороите ввод" << endl << "> ";
		}
	}
	return input;
}
void print_menu() {
	system("cls");
	cout << endl << "Выберите пункт меню:" << endl;
	cout << "  1. Импортировать текст из файла и вывести на экран" << endl;
	cout << "  2. Импортировать текст из файла и сохранить в файл" << endl;
	cout << "  3. Создать файл" << endl;
	cout << "  4. Дополнить файл" << endl;
	cout << "  ---" << endl;
	cout << "  5. Поменять разделитель слов" << endl;
	cout << "  6. Поменять разделитель предложений" << endl;
	cout << "  ---" << endl;
	cout << "  0. Выход из программы" << endl;
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
			cout << endl<< "Нажмите любую клавишу, чтобы продолжить..." << endl;
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
			cout << "Введите новый разделитель слов: ";
			string new_sep_words;
			sep_words = in(new_sep_words);
			
		}
		break;
		case 6:
		{
			cout << "Введите новый разделитель предложений: ";
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
	cout << "Добро пожаловать!" << endl;
	cout << "Введите разделитель слов: ";
	string sep_words;
	sep_words = in(sep_words);
	cout << "Введите разделитель предложений: ";
	string sep_sentence; 
	sep_sentence = in(sep_sentence);
	menu(sep_words, sep_sentence);
	return 0;
}