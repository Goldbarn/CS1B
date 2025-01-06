// Justifies unjustified.txt into justified.txt
// Rowan Ess
// Lab7_LineJustify CS1B
// 12-3-24

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>

using std::cin; using std::cout; using std::endl; 
using std::string;
using std::ifstream; using std::ofstream;

const int lineLength = 80;
const string punc = ",.!?:";

void addAfterPunc(string&);
void addInSpace(string&);

int main() {
	ifstream fin("unjustified.txt");
	ofstream fout("justified.txt");
	string line;
	while (getline(fin, line)) {
		addAfterPunc(line);
		addInSpace(line);
		fout << line << '\n';
	}
	fin.close();
}

void addAfterPunc(string& input) {
	int pos = input.find_first_of(punc);
	while (pos != string::npos && input.size() >= 40) {
		if (input.find(' ', pos) == pos + 1) {
			input.insert(pos + 1, 1, ' ');
		}
		pos = input.find_first_of(punc, pos + 1);
	}
}

void addInSpace(string& input) {
	srand(time(nullptr));
	while (input.size() >= 40 && input.size() < 80) {
		int randy = rand() % input.size();
		if (input.find(' ', randy) == randy) {
			input.insert(randy, 1, ' ');
		}
	}
}
