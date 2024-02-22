// Q2a: Define displayEmployee() for Nontechnical class (5 points)
// Define the function displayEmployee() that you declared within the Nontechnical class in the header file
// See expected output in question file.

#include "employee.h"
#include "nontechnical.h"
#include <iostream>

using namespace std;

void Nontechnical :: displayEmployee()
{
	cout << endl;												// Skip a line
	cout << "Employee Name: " << getName() << endl;				// Display Employee Name
	cout << "Salary: " << getSalary() << endl;					// Display Salary
	string employeeType;										// String named 'employeeType'

	if (getEmpType() == 0)										// If employee type is equal to 0, then display "Nontechnical"
	{
		employeeType = "Nontechnical";
	}
	else                                                        // Otherwise, the employee profile is considered "Technical"
	{
		employeeType = "Technical";
	}
	cout << "Employee Type: " << employeeType << endl << endl;	// Display Employee Type
}

// (displayList() function in hw9.cpp should call this function.)
// Include necessary header files