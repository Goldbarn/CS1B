// The main function for Charlie's coolection
// Rowan Ess
// CS1B Lab 11 Part 2
// 12-19-24

#include "collection.hpp"
#include <iostream>

using std::cout; using std::cin;

int main() {
	Collection charlie;
	char operation = ' ';
	double number = 0;

	while (operation != 'q') {
		cout << "\nCharlie, enter operation [a/r/q] then number: ";
		cin >> operation >> number;

		switch (operation) {
		case 'a':
			if (charlie.check(number) == -1) {
				charlie.addNumber(number);
			}
			else {
				cout << "That number is already in the collection!\n";
			}
			break;
		case 'r':
			if (charlie.check(number) != -1) {
				charlie.removeNumber(number);
			}
			else {
				cout << "That number isn't in the collection!\n";
			}
			break;
		case 'q':
			cout << "Thanks for collecting!\n";
			break;
		default:
			cout << "That is not a valid operation.\n";
		}

		cout << "Your numbers: ";
		charlie.output();
		cout << ". Their sum: " << charlie.value();
	}
}