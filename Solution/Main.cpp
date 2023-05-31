#include <iostream>
#include <string>
#include <fstream> 
//#include <Windows.h>
#include <regex>

using namespace std;

void developerInformation() {
	cout << "Добро пожаловать!\n\nПрограмму выполнил: Плеханов Алексей\n\nОбработка текстовой информации\n\nВводить текст в Input.txt строго на английском языке!!" << endl << endl;
}

void WriteNewFile(string namefile) {
	ofstream f(namefile + ".txt");
	f.close();
}
void textLen(string text) {

	if (text.find(' ')) {
		cout << "Количество символов в тексте: " << text.length() << endl;
	}
	else {
		cout << "Текст с пробелами не найден!" << endl;
	}
}
string WasteChar(string& text) {
	string new_text;
	regex rgx_pattern("\\s*([.,!?;:<>%])\\s*");
	char isEx[] { '.', ',', '?', ';', ':', '<', '>', '%' };
	
	for (int i = 0; i < text.size(); i++) {
		for (auto isExp : isEx) {
			while ((text[i] == text[i + 1]) && text[i + 1] == isExp) {
				text.erase(i + 1, 1);
			}
		}
	}

	new_text.reserve(text.size());
	regex_replace(back_inserter(new_text), text.cbegin(), text.cend(), rgx_pattern, "$1 ");

	return new_text;
}

void formattingText() {
	string text, line;
	int countLine = 0;

	cout << "Чтение файла Input.txt" << endl;

	ifstream fileRead("Input.txt");

	while (getline(fileRead, line) && countLine <= 9) {

		if (line.length() < 61 && line.length() > 0) {
			while (line[0] == ' ' || line[0] == '\t') line.erase(0, 1);
			text += line + "\n";
			countLine++;
		}
		else { continue; }

		text = WasteChar(text);
	}

	textLen(text); // кол-во символов
	cout << "Кол-во строк в файле: " << countLine << endl << endl;

	cout << "Ваш текст (отформатирован):\n" << text << endl << endl;

	ofstream fileOut("Output.txt");
	fileOut << text;
	fileOut.close();

	fileRead.close();
}

void splitTextonFile() {
	string text, line;

	fstream fileOut("Output.txt");
	while (getline(fileOut, line)) text += line;
	fileOut.close();

	WriteNewFile("Output-line.txt");

	fstream file("Output-line.txt");

	for (int i = 0; i < text.length(); i++) {
		if (text[i] == ' ') {
			text.replace(i, 1, "\n");
		}
	}

	file << text;
	file.close();
}

void searchWord() {
	string line, userinput;
	bool SucSearch = false;

	char exception[] = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";

	cout << "Введите слово или часть слова, которое хотите найти (англ. буквами): ";
	cin >> userinput;

	for (auto Exp : exception) {
		while (userinput[0] == Exp) {
			cout << "Введите слово или часть слова, которое хотите найти (англ. буквами): ";
			cin >> userinput;
		}
	}

	fstream file("Output-line.txt");

	while (getline(file, line)) {
		if (strstr(line.c_str(), userinput.c_str())) {
			cout << "\nНайдено слово с " << userinput << ": " << line << endl << endl;
			SucSearch = true;
		}
	}

	if(SucSearch == false) cout << "\nНе найдено слово с " << userinput << endl << endl;

	file.close();
}
void countingSyllables() {
	string line;

	fstream file("Output-line.txt");
	cout << "Вывод слов, где больше двух слогов: " << endl;

	while (getline(file, line)) {
		int countVowel = 0;
		for (int i = 0; i < line.length(); i++) {
			if (tolower(line[i]) == 'a' || tolower(line[i]) == 'e' || tolower(line[i]) == 'i' || tolower(line[i]) == 'o' || tolower(line[i]) == 'u' || tolower(line[i]) == 'y') countVowel++;
		}
		if (countVowel >= 2) cout << line << endl;
	}
	file.close();
}

int main() {

	setlocale(LC_ALL, "Russian");

	developerInformation();
	formattingText();
	splitTextonFile();
	searchWord();
	countingSyllables();

	system("pause");

	return 0;
}
