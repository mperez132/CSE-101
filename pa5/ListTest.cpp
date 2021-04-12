/*
Name: Moises Perez
CruzID: mperez86
Assignment: pa5

*/
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "List.h"

using namespace std;

void PrintLine(int len = 40)
{
	for (int i = 0; i < len; i++)
	{
		cout << '-';
	}
	cout << endl;
}

int RandValue(int maxValue = 100)
{
	return (int)(rand() % maxValue + 1);
}

void announce()
{
	cout << "ListTest.cpp" << endl;
	cout << "By: Moises Perez" << endl;
	cout << "Demonstrating the C++ List ADT. " << endl;
	cout << "IDE used: Visual Studio\n";
	cout << "File: " << __FILE__ << endl;
	cout << "Authored: 11/27/20" << endl;
	cout << "Complied: " << __DATE__ << " at " << __TIME__ << endl << endl;
	cout << endl << endl;
}

void RunTest() {

	List A, B;
	List C;
	List D;
	for (int i = 1; i <= 5; i++) {
		int value = RandValue();
		A.insertAfter(value);
		value = RandValue();
		B.insertAfter(value);
	}

	cout << "A = " << A << endl;
	cout << "A.position() = " << A.position() << endl;
	cout << "B = " << B << endl;
	cout << "B.position() = " << B.position() << endl;

	PrintLine();

	cout << "A is empty?: ";
	cout << "\nShoud be false:\n A is: ";
	cout << A.isEmpty() << endl;

	PrintLine();

	cout << "B is empty?: ";
	cout << "\nShoud be false:\n B is: ";
	cout << B.isEmpty() << endl;

	for (int i = 1; i <= 5; i++) {
		int value = RandValue();
		C.insertAfter(value);
		value = RandValue();
		D.insertAfter(value);
	}

	PrintLine();

	cout << "C = " << C << endl;
	cout << "C.position() = " << C.position() << endl;
	cout << "D = " << D << endl;
	cout << "D.position() = " << D.position() << endl;

	PrintLine();

	C.clear();
	cout << "Clearing C: " << endl;
	cout << "C is empty? " << (C.isEmpty() ? "true" : "false") << endl;
 
	PrintLine();

	C = A.concat(B);
	cout << "Concat A+B to C : " << endl;
	cout << "A = " << A << endl;
	cout << "C = " << C << endl;

	PrintLine();

	D = B;
	cout << "Setting D = B: " << endl;
	cout << "B = " << B << endl;
	cout << "D = " << D << endl;

	PrintLine();

	A.clear();
	B.clear();
	C.clear();
	D.clear();

	cout << "Clearing A: " << endl;
	cout << "A is empty? " << (A.isEmpty() ? "true" : "false") << endl;

	cout << "Clearing B: " << endl;
	cout << "B is empty? " << (B.isEmpty() ? "true" : "false") << endl;

	cout << "Clearing C: " << endl;
	cout << "C is empty? " << (C.isEmpty() ? "true" : "false") << endl;

	cout << "Clearing D: " << endl;
	cout << "D is empty? " << (D.isEmpty() ? "true" : "false") << endl;

}

int main() {

	announce();
	RunTest();

	return 0;
}