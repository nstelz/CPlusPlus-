#include <Python.h>
#include <iostream>
#define NOMINMAX
#include <Windows.h>
#undef NOMINMAX
#include <cmath>
#include <string>
#include <fstream>
#include <iomanip>


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
void CallProcedure(string pName)
{
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

int callIntFunc(string proc, string param)
{
	char *procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char *paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject *pName,  *pModule, *pDict, *pFunc, *pValue = nullptr, *presult = nullptr;
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
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
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
int callIntFunc(string proc, int param)
{
	char *procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject *pName, *pModule, *pDict, *pFunc, *pValue = nullptr, *presult = nullptr;
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
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
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
void MainMenu() {//menu display for user selection
	int userInput = 0; //int variable for user input for menu selection that is 1-4
	int wordCount = 0; //int variable for counting number of times word is found
	int itemQuantity = 0; //variable to show how many times items purchased
	string searchItem; //string variable to search for item
	string itemName; //string variable to store item name
	ifstream fileinput; //variable for file input that allows data to be pulled 

	while (userInput != 4) {//menu loop only loops when the escape sequence 4 is not the input
		
		cout << "1: Calculate number of times item appears" << endl; //shows the first menu option diplaying the data
		cout << "2: Calculate frequency of item" << endl; //shows search function for specific item
		cout << "3: Create a histogram of items" << endl; //shows histogram displaying items
		cout << "4: Quit" << endl; //escape sequence
		
		cin >> userInput; //user input 

		while (cin.fail()) { //while loop that makes user enter valid selection
			
			cin.clear(); //clears user input
			
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignores to allow user to enter new input
						//ignores the input by using max number limits up to new line
			
			cout << "Please input valid number: " << endl; //prompts the user for new input
			
			cin >> userInput;
		}
		switch (userInput) { //switch statement for user menu input 1-4

		case 1: //calls python function to count and show data
			
			system("CLS"); //clears the screen for cleaner output
			
			CallProcedure("Count"); //the call function to pull from python
			
			cout << endl;
			
			break;

		case 2: //calls python function to find specific item counts
			
			system("CLS"); //cleats the screen
			
			cout << "Search item: " << endl; //prompts the user for input
			cin >> searchItem;
			
			wordCount = callIntFunc("CountInstances", searchItem); //uses function to pull data from python 
			
			cout << searchItem << " : " << wordCount << endl; //displays how many times a specified item was found
			
			break;

		case 3: //calls function to display histogram
			
			system("CLS");
			
			CallProcedure("FindData"); //calls python function to display data for histogram
			
			fileinput.open("frequency.dat"); //pulls the file that was created in python
			fileinput >> itemName; //pulls data from file into variable
			fileinput >> itemQuantity; //pulls data from file into variable

			while (!fileinput.fail()) { //while loop for histogram display
				
				cout << setw(14) << left << itemName << setw(6); //sets distance between columns for display based on char
				
				for (int i = 0; i < itemQuantity; i++) { //for loops couting item quantities
					system("color 0A"); //changes color of program when histogram is displayed
					cout << right << "*"; //outputs * to the right of items based on number
				}
				
				cout << endl;
				
				fileinput >> itemName;
				fileinput >> itemQuantity;
			}
			fileinput.close(); //closes the file
			
			break;

		case 4: //escape sequence to exit program
			return;

		default: //default that prompts user to enter input
			cout << "Please input a valid number: " << endl;
			break;
		}
	}
}


void main() //main function
{
	MainMenu(); //calls main menu to display menu

}
