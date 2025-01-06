// The main function for Charlie's coolection
// Rowan Ess
// CS1B Lab 10 Part 2
// 12-4-24

#include <iostream>
#include <vector>
#include <algorithm>

using std::cout; using std::cin; using std::vector; using std::find;

int main() {
	vector<double> collection;
	char operation = ' ';
	double number = 0;

	while (operation != 'q') {
		cout << "\nCharlie, enter operation [a/r/q] then number: ";
		cin >> operation >> number;

		switch (operation) {
		case 'a':
			if (find(collection.begin(), collection.end(), number) == collection.end()) {
				collection.push_back(number);
			}
			else {
				cout << "That number is already in the collection!\n";
			}
			break;
		case 'r': 
			if (find(collection.begin(), collection.end(), number) != collection.end()) {
				collection.erase(find(collection.begin(), collection.end(), number));
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
		double sum = 0;
		for (int i = 0; i < collection.size(); ++i) {
			cout << collection[i] << ' ';
			sum += collection[i];
			}
		cout << ". Their sum: " << sum;
	}
}
