// Collection func definitions
// Rowan Ess
// cs1b lab 11 part 2
// 4/12/2024

#include "collection.hpp"
#include <iostream>

using std::cout;


// void constructor
Collection::Collection() {
	col_ = new double[0];
}
// returns index of element containg "number" or -1 if none
int Collection::check(double number) {
	int index = -1;
	double* tempCol = col_;
	for (int i = 0; i < size_; ++i) {
		if (*tempCol == number)
			index = i;
		++tempCol;
	}
	return index;
}
// adds number to the collection
void Collection::addNumber(double number) {
	if (check(number) == -1) {
		int newSize = ++size_;
		double* newArr = new double[newSize];
		for (int i = 0; i < size_; ++i) {
			newArr[i] = col_[i];
		}
		newArr[newSize - 1] = number;
		delete[] col_;
		col_ = newArr;
		size_ = newSize;
	}
}
// deletes the number from the collection
void Collection::removeNumber(double number) {
	if (check(number) != -1) {
		int newSize = size_ - 1;
		double* newArr = new double[newSize];
		bool found = false;
		for (int i = 0; i < size_; ++i) {
			if (col_[i] == number && !found) {
				found = true;
			}
			else {
				if (!found) {
					newArr[i] = col_[i];
				}
				else {
					newArr[i - 1] = col_[i];
				}
			}
		}
		delete[] col_;
		col_ = newArr;
		size_ = newSize;
	}
}
// prints the values of the collection
void Collection::output() const {
	for (int i = 0; i < size_; ++i) {
		cout << col_[i] << ' ';
	}
}
// returns the sum of the values in the collection
double Collection::value() const {
	int total = 0;
	for (int i = 0; i < size_; ++i) {
		total += col_[i];
	}
	return total;
}
// copy constructor
Collection::Collection(const Collection& old) {
	size_ = old.size_;
	col_ = new double[size_];
	for (int i = 0; i < size_; ++i) {
		col_[i] = old.col_[i];
	}
}
// overloaded assignment
const Collection& Collection::operator=(const Collection& other) {
	if (this != &other) {
		size_ = other.size_;
		delete[] col_;
		col_ = new double[size_];
		for (int i = 0; i < size_; ++i) {
			col_[i] = other.col_[i];
		}
	}
	return *this;
}
// destructor
Collection::~Collection() {
	delete[] col_;
}