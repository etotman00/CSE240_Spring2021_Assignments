// CSE240 Spring 2021 HW8
// Name: Ellis Totman
// Write the compiler used: Visual Studio

// READ BEFORE YOU START:
// You are given a partially completed program which consist of a class 'Book' defined in book.h
// The definitions of class member functions are to be filled in book.cpp (this file).
// hw08q1.c creates an array of objects 'b[]' and uses a menu driven program to add a book, display book info, 
// sort the book list and to find the book with the longest title among the books whose bookType contain a specific substring.
// You should start completing the program from from Q1. Question numbers are given around line 24 in book.cpp.
// To begin, you should trace through the given code and understand how it works.
// Please read the instructions above each required function and follow the directions carefully.
// If you modify any of the given code, the return types, or the parameters, you risk getting compile error.

// ***** WRITE COMMENTS FOR IMPORANT STEPS OF YOUR CODE. *****
// ***** GIVE MEANINGFUL NAMES TO VARIABLES. *****

#include "book.h"
#include <iostream>
#include <string.h>

#define MAX_BOOKS 5

using namespace std;

// forward declaration of functions (already implmented)
void executeAction(char);

// functions that need implementation:
// in book.cpp :
// Q1 Book constructor		// 2 points
// Q2 Book member functions // 18 points

// in this file (hw08q1.cpp) : Q3 to Q6
int addBook(string title_input, int id_input, int aisle_input, string bookType_input); // 10 points
void displayBooks();				// 5 points
void sort();						// 10 points
void bookTypeWithSpecificString();		// 5 points


Book b[MAX_BOOKS];		// array of objects
int currentCount = 0;				// number of books in the list


int main()
{
	char choice = 'i';		// initialized to a dummy value
	do
	{
		cout << "\nCSE240 HW8\n";
		cout << "Please select an action:\n";
		cout << "\t a: add a new book\n";
		cout << "\t d: display book list\n";
		cout << "\t s: sort the books in descending order based on ID (within a range)\n";
		cout << "\t n: display the book with the longest title among the books whose bookType contain a specific substring\n";
		cout << "\t q: quit\n";
		cin >> choice;
		cin.ignore();			// ignores the trailing \n
		executeAction(choice);
	} while (choice != 'q');

	return 0;
}


// Ask for details from user for the given selection and perform that action
// Read the function case by case
void executeAction(char c)
{
	string title_input, bookType_input;
	int ID_input, aisle_input, result = 0;

	switch (c)
	{
	case 'a':	// add book
				// input book details from user
		cout << "Please enter book title: ";
		getline(cin, title_input);
		cout << "Please enter book ID: ";
		cin >> ID_input;
		cin.ignore();
		cout << "Please enter aisle number: ";
		cin >> aisle_input;
		cin.ignore();
		cout << "Please enter bookType: ";
		getline(cin, bookType_input);

		// add the book to the list
		result = addBook(title_input, ID_input, aisle_input, bookType_input);
		if (result == 0)
			cout << "\nThat book is already in the list or list is full! \n\n";
		else
			cout << "\nBook successfully added to the list! \n\n";
		break;

	case 'd':		// display the list
		displayBooks();
		break;

	case 's':		// sort the list
		sort();
		break;

	case 'n':		// find and display book with the longest title among the books whose bookType contain a specific substring.
		bookTypeWithSpecificString();
		break;

	case 'q':		// quit
		cout << "\nGoodbye!\n";
		break;

	default: cout << c << " is invalid input!\n";
	}

}

// Q3 addBook (10 points)
// This function adds a new book with the details given in function arguments.
// Add the book in 'b' (array of objects) only if there is remaining capacity in the array and if the book does not already exist in the list (title or ID)
// This function returns 1 if the book is added successfully, else it returns 0 for the cases mentioned above.
// Assume user enters ID and aisle number  in 0 - any positive integer range.
int addBook(string title_input, int id_input, int aisle_input, string bookType_input)
{
	int libraryIndex = -1;
	if (currentCount == MAX_BOOKS)	// If reached maximum number of books
	{
		return 0;					// Return 0 as a reminder that book limit reached
	}

	for (int x = 0; x < currentCount; x++) // Find the number of books/elements in the array
	{
		if (b[x].getTitle() == title_input || b[x].getID() == id_input) // If title or ID matches with one of the books in array database
		{
			libraryIndex = x;	// No book added to array
			break;
		}
	}
	
	if (libraryIndex == -1)	// If space is available 
	{
		b[currentCount].setTitle(title_input);			// Add book title
		b[currentCount].setID(id_input);				// Add book ID
		b[currentCount].setAisle(aisle_input);			// Add aisle number
		b[currentCount].setBookType(bookType_input);	// Add book type
		currentCount++;									// Increments value after inputing book details					
		return 1;										// Return 1 as a reminder that book successfully added 
	}
	else 
	{
		return 0;	// Failed to add book
	}
}

// Q4 displayBooks (5 points)
// This function displays the list of books.
// Parse the object array 'b' and display the details of all books in the array. See expected output given in question file.
// You can call the class function 'displayBook()' here. Note that these are two different functions.
// Book::displayBook() displays details of one Book object, while displayBooks() should display all books.
void displayBooks()
{
	for (int x = 0; x < currentCount; x++)	// Find the number of books/elements in the array
	{
		b[x].displayBook();					// Display the library/array
	}
	cout << endl;							// Flush out the '\n' strings
}

// Q5 sort (10 points)
// This function sorts the books in descending order of ID, and then display the books within a given range.
// You need to get lower bound and higher bound from user after printing a prompt. (Check the output in the pdf)
// You may use the 'temp' object for sorting logic, if needed.
void sort()
{
	Book temp;						// Temporary variable for the array
	int lower_bound, higher_bound;	// Two integers for the ID bounds
	int x, y;						// Two integers for the 'for' loops
	
	cout << "\nPlease enter the lower bound of ID: ";	// Enter lower bound of ID
	cin >> lower_bound;									// Store lower bound
	cout << "Please enter the higher bound of ID: ";	// Enter higher bound of ID
	cin >> higher_bound;								// Store higher bound

	for (x = 0; x < currentCount; x++)					// Find the number of books/elements in the array
	{
		for (y = x + 1; y < currentCount; y++)		
		{
			if (b[y].getID() < b[x].getID()) 
			{
				// Sort the array 
				temp = b[y];
				b[y] = b[x];
				b[x] = temp;
			}
		}
	}

	cout << endl << "Successfully sorted!\n";							// Display message indicating succession
	
	for (x = 0; x < currentCount; x++)									// Find the number of books/elements in the array
	{
		if (b[x].getID() >= lower_bound && b[x].getID() <= higher_bound)// Find the books within the ID range
		{
			b[x].displayBook();											// Display array within the ID range
		}
	}
}

// Q6 bookTypeWithSpecificString (5 points)
// This function displays an book with the longest name among the books whose bookType contain a specific substring.
// You should find the book as follows:
// 1. By traversing all books, you should find the books whose booktype include a specific substring. 
// NOTE: you need to get a substring from user after printing a prompt. (Check the output in the pdf)
// HINT: You may refer to the document of string::find.
// 2. After step 1, you should find the book whose title is the longest. You may use 'titleLength' and 'index' variable.
// 3. After step 2, copy the details of the book to 'bookWithLengthyTitle' object created using 'new' 
// and display the book's details using 'bookWithLengthyTitle' object.
// NOTE: You necessarily have to use the 'bookWithLengthyTitle' object to store the book details in it and delete it after displaying.
//       You should not display book details using 'b[]' object.
// 4. Finally delete the 'bookWithLengthyTitle' object.
void bookTypeWithSpecificString()
{
	string subString;				// Ask the user for a character
	Book* bookWithLengthyTitle = new Book;
	int titleLength = 0;
	
	cout << "\nEnter the substring of book's bookType: "; // Ask user to enter substring of bookType
	cin >> subString;									  // Store substring
	
	for (int x = 0; x < currentCount; x++)				  // Find the number of books/elements in the array
	{
		if (titleLength < b[x].getTitle().length())		  // Find book with the longest title
		{
			titleLength = b[x].getTitle().length();
			bookWithLengthyTitle = &b[x];
		}
	}
	cout << endl;							// Flush out the '\n' strings
	bookWithLengthyTitle->displayBook();	// Display 'bookwithLengthyTitle'

	delete bookWithLengthyTitle;			// Delete the 'bookWithLengthyTitle' object 
}
// End of hw08q1.cpp