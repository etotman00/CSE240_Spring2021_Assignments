
// CSE240 Spring 2021 HW5
// Name: Ellis Totman
// Write the compiler used: Visual studio

// READ BEFORE YOU START:
// You are given a partially completed program that creates a list of books, like book's record.
// Each record has this information: book title, author, type of the book, book id and aisle in which the book is to be kept.
// The struct 'libraryRecord' holds information of one book. bookType is enum type.
// An array of structs called 'list' is made to hold the list of books.
// To begin, you should trace through the given code and understand how it works.
// Please read the instructions above each required function and follow the directions carefully.
// You should not modify any of the given code, the return types, or the parameters, you risk getting compile error.
// You are not allowed to modify main ().
// You can use string library functions.

// WRITE COMMENTS FOR IMPORANT STEPS IN YOUR CODE.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable: 4996) // for Visual Studio Only

#define MAX_BOOKS 15
#define MAX_NAME_LENGTH 25

typedef enum { Nonfiction = 0, Fiction } bookType; // enum type 

struct libraryRecord {					// struct for book details
	char bookTitle[MAX_NAME_LENGTH];
	char author[MAX_NAME_LENGTH];
	bookType booktype;
	unsigned int bookId;
	unsigned int aisle;
};

struct libraryRecord list[MAX_BOOKS]; // declare list of books
int count = 0;						  // the number of books currently stored in the list (initialized to 0)

// functions already implmented
void flushStdIn();
void executeAction(char);
void save(char* fileName);

// functions that need implementation:
int add(char* bookTitle_input, char* author_input, char* booktype_input, unsigned int bookId_input, unsigned int aisle_input); // 20 points
void sort();				  // 10 points
int delete(unsigned int bookId_input);  // 10 points
void load(char* fileName);		  // 10 points
void display();				  // given


int main()
{
	char* fileName = "Book_List.txt";
	load(fileName);	// load list of books from file (if it exists). Initially there will be no file.
	char choice = 'i';		// initialized to a dummy value
	do
	{
		printf("\nEnter your selection:\n");
		printf("\t a: add a new book\n");
		printf("\t d: display book list\n");
		printf("\t r: remove a book from list\n");
		printf("\t s: sort book list by ID\n");
		printf("\t q: quit\n");
		choice = getchar();
		flushStdIn();
		executeAction(choice);
	} while (choice != 'q');

	save(fileName); // save list of books to file (overwrites file, if it exists)
	return 0;
}

// flush out leftover '\n' characters
void flushStdIn()
{
	char c;
	do c = getchar();
	while (c != '\n' && c != EOF);
}

// ask for details from user for the given selection and perform that action
void executeAction(char c)
{
	char bookTitle_input[MAX_NAME_LENGTH], author_input[MAX_NAME_LENGTH];
	unsigned int bookId_input, aisle_input, add_result = 0;
	char booktype_input[20];
	switch (c)
	{
	case 'a':
		// input book record from user
		printf("\nEnter book title: ");
		fgets(bookTitle_input, sizeof(bookTitle_input), stdin);
		bookTitle_input[strlen(bookTitle_input) - 1] = '\0';	// discard the trailing '\n' char
		printf("Enter author name: ");
		fgets(author_input, sizeof(author_input), stdin);
		author_input[strlen(author_input) - 1] = '\0';	// discard the trailing '\n' char
		printf("Enter book type (Fiction/ Nonfiction): ");
		fgets(booktype_input, sizeof(booktype_input), stdin);
		booktype_input[strlen(booktype_input) - 1] = '\0';	// discard the trailing '\n' char
		printf("Please enter book ID number: ");
		scanf("%d", &bookId_input);
		printf("Please enter aisle number: ");
		scanf("%d", &aisle_input);
		flushStdIn();

		// add the book to the list
		add_result = add(bookTitle_input, author_input, booktype_input, bookId_input, aisle_input);
		if (add_result == 0)
			printf("\nBook is already on the list! \n\n");
		else if (add_result == 1)
			printf("\nBook successfully added to the list! \n\n");
		else
			printf("\nUnable to add. Book list is full! \n\n");

		break;
	case 'r':
		printf("Please enter ID number of book to be deleted: ");
		scanf("%d", &bookId_input);
		flushStdIn();
		int delete_result = delete(bookId_input);
		if (delete_result == 0)
			printf("\nBook not found in the list! \n\n");
		else
			printf("\nBook deleted successfully! \n\n");
		break;
	case 'd': display();	break;
	case 's': sort();		break;

	case 'q': break;
	default: printf("%c is invalid input!\n", c);
	}
}

// Q1 : add (20 points)
// This function is used to add a book into the list. You can simply add the new book to the end of list (array of structs).
// Do not allow the book to be added to the list if it already exists in the list. You can do that by checking book names AND IDs already in the list.
// If the book already exists then return 0 without adding it to the list. If the book does not exist in the list then add the book at the end of the list and return 1.
// If book list is full, then do not add new book to the list and return 2.
// NOTE: Notice how return type of add() is checked in case 'a' of executeAction()
// NOTE: You must convert the string 'booktype_input' to an enum type and store it in the list because the booktype has enum type (not string type).
// The list should be case sensitive. For instance, 'Roger' and 'roger' should be considered two different names.
// Hint: 'count' holds the number of books currently in the list
int add(char* bookTitle_input, char* author_input, char* booktype_input, unsigned int bookId_input, unsigned int aisle_input)
{

	/* Two integer variables initialized.
	'x' is used for the arraylist.
	'booktypeValue' is used for conversion of enum type variable.
	*/
	int x = 0, booktypeValue = booktype_input;

	/* If the amount of books has reach the maximum limit,
	* then no books will be added to the list.
	*/
	if (count == MAX_BOOKS)
	{
		return 2;
	}
	/* If the amount of books is less than the maximum limit,
	* then a book wil be added to the list.
	*/
	if (count < MAX_BOOKS)
	{
		strcpy(list[x].bookTitle, bookTitle_input);
		strcpy(list[x].author, author_input);
		// Enum to number conversion.
		if (list[x].booktype == booktype_input)
			booktypeValue = 0;		// 0 for Nonfiction
		else
			booktypeValue = 1;		// 1 for Fiction
		booktypeValue = booktype_input;
		list[x].bookId = bookId_input;
		list[x].aisle = aisle_input;
		count++; 
		return 1;
	}
	/* If the user has entered a book title or ID similar to
	* recently added book, then the book the user tried
	* to add will not be on the list along with the already
	* published books.
	*/
	if (bookId_input == list[x].bookId)
	{
		return 0;
	}
}



// This function displays the book list with the details (struct elements) of each book. 
void display()
{
	char* booktypeString = "Nonfiction";						// dummy init

	for (int i = 0; i < count; i++)								// iterate through the list
	{
		printf("\nBook Title: %s", list[i].bookTitle);			// display Book title
		printf("\nAuthor Name: %s", list[i].author);			// display author

		if (list[i].booktype == Nonfiction)						// find what to display for book type
			booktypeString = "Nonfiction";
		else
			booktypeString = "Fiction";

		printf("\nBook Type: %s", booktypeString);			// display book type
		printf("\nBook ID: %d", list[i].bookId);			// display book id
		printf("\nAisle number: %d", list[i].aisle);		// display aisle number
		printf("\n");
	}

}

// Q2 : sort (10 points)
// This function is used to sort the list(array of structs) numerically by book ID.
// Parse the list and compare the book IDs to check which one should appear before the other in the list.
// Sorting should happen within the list. That is, you should not create a new array of structs having sorted books.
// Hint: Use a temp struct (already declared) if you need to swap two structs in your logic
void sort()
{
	struct libraryRecord libraryTemp;	// needed for swapping structs. Not absolutely necessary to use.
	/* Two integers initialized.
	* 'x' is used for the 'for' loops.
	* 'y' is used for the arraylist.
	*/
	int x, y;

	for (x = 0; x < count; x++)
	{
		for (y = 0; y < (count - 1 - x); y++) 
		{
			if (list[y].bookId < list[y + 1].bookId) 
			{
				// Sorts the arraylist.
				libraryTemp = list[y];
				list[y] = list[y + 1];
				list[y + 1] = libraryTemp;
			}
		}
	}

	// display message for user to check the result of sorting.
	printf("\nBook list sorted! Use display option 'd' to view sorted list.\n");
}

// save() is called at the end of main()
// This function saves the array of structures to file. It is already implemented.
// You should read and understand how this code works. It will help you with 'load()' function.
// save() is called at end of main() to save the book list to a file.
// The file is saved at the same place as your C file. For VS, the default directory looks like this:
// C:\Users\<username>\Documents\Visual Studio 2017\Projects\Project1\Project1
// You can simply delete the file to 'reset the list' or to avoid loading from it.
void save(char* fileName)
{
	FILE* file;
	int i, booktypeValue = 0;
	file = fopen(fileName, "wb");		// open file for writing

	fwrite(&count, sizeof(count), 1, file);		// First, store the number of books in the list

	// Parse the list and write book record to file

	for (i = 0; i < count; i++)
	{
		fwrite(list[i].bookTitle, sizeof(list[i].bookTitle), 1, file);
		fwrite(list[i].author, sizeof(list[i].author), 1, file);
		// convert enum to a number for storing
		if (list[i].booktype == Nonfiction)
			booktypeValue = 0;		// 0 for Nonfiction
		else
			booktypeValue = 1;		// 1 for Fiction

		fwrite(&booktypeValue, sizeof(booktypeValue), 1, file);
		fwrite(&list[i].bookId, sizeof(list[i].bookId), 1, file);
		fwrite(&list[i].aisle, sizeof(list[i].aisle), 1, file);
	}

	fclose(file);			// close the file after writing
}

// Q3 : delete (10 points)
// This function is used to delete a book by ID.
// Parse the list and compare the book IDs to check which one should be deleted.
// Restore the array structure after removal of the book record.
// Return 0 if the specified ID was not found. Return 1 upon successful removal of a record.
int delete(unsigned int bookId_input)
{
	/* The char nullStr (nullString) is used to delete the strings
	* like the book title and the author.
	* Three integers initialized.
	* 'booktypeValue' is used for the enum conversion.
	* 'y' for the arraylist.
	* 'x' for the book ID input from the user.
	*/
	char nullStr[24] = { "\0" };
	int booktypeValue = 0;
	int y = 0, x = bookId_input;
	
	/* If the ID entered by the user matches one of the 
	* book IDs present in the list, then that book will
	* be removed from the list.
	*/
	if (x == list[y].bookId)
	{
		strcpy(list[y].bookTitle, nullStr);
		strcpy(list[y].author, nullStr);
		// Enum to number conversion.
		if (list[y].booktype == Nonfiction)
			booktypeValue = 0;		// 0 for Nonfiction
		else
			booktypeValue = 1;		// 1 for Fiction
		list[y].booktype = booktypeValue = NULL;
		list[y].bookId = NULL;
		list[y].aisle = NULL;
		count--;
		return 1;
	}
	/* If the ID entered by the user does not match
	* with one of the existing books in the list,
	* then the deletion process will not happen.
	*/
	if (x != list[y].bookId)
	{
		return 0;
	}
}

// Q4:  load (10 points)
// This function is called in the beginning of main().
// This function reads the book list from the saved file and builds the array of structures 'list'. 
// In the first run of the program, there will be no saved file because save() is called at the end of program.
// So at the begining of this function, write code to open the file and check if it exists. If file does not exist, then return from the function.
// (See expected output of add() in homework question file. It displays "Book_List.txt not found" because the file did not exist initially.)
// If the file exists, then parse the book list to read the book details from the file.
// Use the save function given above as an example of how to write this function. Notice the order in which the struct elements are saved in save()
// You need to use the same order to read the list back.
// NOTE: The saved file is not exactly readable because all elements of the struct are not string or char type.
//       So you need to implement load() similar to how save() is implemented. Only then the 'list' will be loaded correctly.
//		You can simply delete the file to 'reset the list' or to avoid loading from it.
void load(char* fileName)
{
	/* The 'fileName' char is initialized to "Book_List.txt" file.
	* 'file' is used for reading each content of the file.
	* Two integers initialized.
	* 'x' is used for the 'for' loop and arraylist.
	* 'booktypeValue' used fo the enum conversion.
	* The text file is then opened for reading.
	*/
	fileName = "Book_List.txt";
	FILE* file;
	int x, booktypeValue = 0;
	file = fopen(fileName, "r");

	// If file is not found, this happens.
	if (fileName == -1)
	{
		printf("Unable to load file: %s\n", fileName);
		return 1;
	}
	// File is read and opens.
	else
	{
		for (x = 0; x < count; x++)
		{
			fread(list[x].bookTitle, sizeof(list[x].bookTitle), 1, file);
			fread(list[x].author, sizeof(list[x].author), 1, file);
			// convert enum to a number for storing
			if (list[x].booktype == Nonfiction)
				booktypeValue = 0;		// 0 for Nonfiction
			else
				booktypeValue = 1;		// 1 for Fiction

			fread(&booktypeValue, sizeof(booktypeValue), 1, file);
			fread(&list[x].bookId, sizeof(list[x].bookId), 1, file);
			fread(&list[x].aisle, sizeof(list[x].aisle), 1, file);
			printf("File '%s' successfully loaded.\n", fileName);
		}
	} 
	
}