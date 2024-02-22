#ifndef _TECHNICAL_H_
#define _TECHNICAL_H_
// Q1b: Create Technical class (5 points)
// Part 1: Create a child class of the Employee class named 'Technical'

class Technical : public Employee
{
	public:
	// Part2: Declare constructor which accepts the same 3 parameters as the parent class Employee's constructor.
	// Pass the 3 parameters to the super constructor of the Employee class.

		Technical(string empName, double salary, empType employeeType)
			: Employee(empName, salary, employeeType) {};

	// Part 3: Re-declare the method displayEmployee (virtual method found inside of parent class Employee)

	void displayEmployee();
};


#endif // _TECHNICAL_H_
