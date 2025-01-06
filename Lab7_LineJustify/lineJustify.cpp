// Justifies whole lines and adds to terminal (80 characters)
// Rowan Ess
// Lab7_LineJustify CS1B
// 8-3-24

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using std::cin; using std::cout; using std::endl; using std::string;  using std::getline;

const int lineLength = 80;
const string punc = ",.!?:";

void addAfterPunc(string&);
void addInSpace(string&);

int main() {
	cout << "Please input a string that is less than 80 characters: \n";
	string input;
	getline(cin, input);
	cout << input.size() << endl;
		addAfterPunc(input);
		addInSpace(input);
	cout << input;
	cout << endl << input.size();
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
