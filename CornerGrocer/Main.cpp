/*
 * Module 7 Corner Grocer
 *
 *  Date: [6/17/2021]
 *  Author: [Jon Curtis]
 */
#include <Python.h>
#include <iostream>
#include<fstream>
#include <Windows.h>
#include <cmath>
#include <string>
#undef max

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName) {
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param) {
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc)) {
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else {
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param) {
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc)) {
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else {
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

void printMenu() {// Prints Menu
	cout << "1: Display Overall Frequency of items." << endl;
	cout << "2: Display Individual Frequency of a item." << endl;
	cout << "3: Display a Histogram of items." << endl;
	cout << "4: Exit" << endl;
	cout << "Enter your selection as a number 1, 2, 3, or 4." << endl;
	cout << endl;
}

void printHistogram() {
	ifstream inFS;     // Input file stream
	string listItem;
	int listNum;
	int fileNum1;      // Data value from file
	int i = 0;

	inFS.open("frequency.dat");// Open File

	if (!inFS.is_open()) {// File did not open
		cout << "Could not open file wordFile.txt." << endl;
	}

	while (!inFS.eof()) { // Runs to end of File
		inFS >> listItem;
		inFS >> listNum;

		if (!inFS.fail()) {//Runs while no errors
			cout << listItem << " ";
			for (i = 0; i < listNum; ++i) {
				cout << "*";
			}
			cout << endl;
		}
	}

	// Close file when done reading
	inFS.close();
}

bool menuSelection(bool& quit) { // Takes selection and number, sends to Python
	string userItem = "";// Number sent to Python
	int i = 0;
	int userInput = 0;// User Selection
	bool correct = false;

	cin >> userInput;

	while (cin.fail() || (userInput - floor(userInput))) {//Validates Input asks for new if fail
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Error" << endl;
		cout << "Enter your selection as a number 1, 2, 3, or 4." << endl;
		cin >> userInput;
	}

	switch (userInput)//Sorts user Selection
	{
	case 1:
		
		CallProcedure("OverallFrequency");//Calls Python function

		break;

	case 2:
		cout << "Enter a Item:" << endl;
		cin >> userItem;//Get Input

		for (i = 0; i < userItem.length(); i++) { // Check input

			if ((userItem[i] >= 'A' && userItem[i] <= 'Z') || (userItem[i] >= 'a' && userItem[i] <= 'z')) {
				correct = true;
			}
			else {
				correct = false;
			}
		}

		while (cin.fail() || correct == false) {//Validates Input
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Error" << endl;
			cout << "Enter a Item:" << endl;
			cin >> userItem;

			for (i = 0; i < userItem.length(); i++) { // Sets Bool

				if ((userItem[i] >= 'A' && userItem[i] <= 'Z') || (userItem[i] >= 'a' && userItem[i] <= 'z')) {
					correct = true;
				}
				else {
					correct = false;
				}
			}
		}
		cout << userItem << ": ";//Prints requested item
		cout << callIntFunc("IndividualFrequency", userItem) << endl;//Calls Python function

		cout << endl;

		break;

	case 3:
		
		CallProcedure("Histogram");//Calls Python function
		printHistogram();// Calls Histogram print

		break;

	case 4:
		quit = true;//Quits program
		return true;
		break;

	default:
		break;
	}

	return false;
}

void main() {
	bool quit = false;// For ending program

	while (quit == false) {// Runs until quit
		printMenu();
		menuSelection(quit);
	}
	// Unused original code
	/*  
	CallProcedure("printsomething");
	cout << callIntFunc("PrintMe", "House") << endl;
	cout << callIntFunc("SquareValue", 2);
	*/
}