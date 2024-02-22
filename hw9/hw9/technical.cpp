// Q2b: Define displayEmployee() for Technical class (5 points)
// Define the function displayEmployee() that you declared within the Technical class in the header file
// See expected output in question file.

#include "employee.h"
#include "technical.h"
#include <iostream>

using namespace std;

void Technical :: displayEmployee()
{
	cout << endl;												// Skip a line
	cout << "Employee Name: " << getName() << endl;				// Display Employee Name
	cout << "Salary: " << getSalary() << endl;					// Display Salary 
	string employeeType;										// String named 'employeeType'
	
	if (getEmpType() == 1)										// If employee type is equal to 1, then display "Technical"
	{
		employeeType = "Technical";
	}
	else														// Otherwise, the employee profile is considered "Nontechnical"
	{
		employeeType = "Nontechnical";
	}
	cout << "Employee Type: " << employeeType << endl << endl;	// Display Employee Type 
}

// (displayList() function in hw9.cpp should call this function.)
// Include necessary header files