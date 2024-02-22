// CSE240 Spring 2021 HW 7
// Name: Ellis Totman
// Write the compiler used: Visual Studio 

// READ BEFORE YOU START:
// You are given a partially completed program that creates a linked list of book information.
// The global linked list 'list' is a list of books with each node being struct 'libraryList'.
// 'libraryList' consists of struct 'book' which has: book title, aisle number, and a linked list of 'bookType'.
// The linked list of bookType has each node containing simply the book type name.
// 
// 

// To begin, you should trace through the given code and understand how it works.
// Please read the instructions above each required function and follow the directions carefully.
// If you modify any of the given code, the return types, or the parameters, you risk getting compile error.
// You are not allowed to modify main ().
// You can use string library functions.

// ***** WRITE COMMENTS FOR IMPORANT STEPS OF YOUR CODE. *****
// ***** GIVE MEANINGFUL NAMES TO VARIABLES. *****
// ***** Before implementing any function, see how it is called in executeAction() *****


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable: 4996) // for Visual Studio

#define MAX_NAME 30

// global linked list 'list' contains the list of books
struct libraryList {
	struct book* book;
	struct libraryList* next;
} *list = NULL;				// currently empty list

// structure "book" contains the book's title, aisle number and linked list of bookType
struct book {
	char title[MAX_NAME];
	unsigned int aisle;
	struct bookType* types;		// linked list 'types' contains names of bookType
};

//  structure 'bookType' contains type name 
struct bookType {
	char type[MAX_NAME];
	struct bookType* next;
};

// forward declaration of functions (already implmented)
void flushStdIn();
void executeAction(char);

// functions already implemented
void addBook(char* bookTitleInput, unsigned int aisleInput);
void displayBookList(struct libraryList* tempList);

// functions that need to be implemented
struct book* searchBook(char* bookTitleInput);	      // 5 points

void addBookType(char* bookTitleInput, char* typeInput);	// 15 points
void displayBookTypeList(struct libraryList* tempList);	// 15 points
void removeBook(char* bookTitleInput);			        // 15 points

int main()
{
	char selection = 'a';		// initialized to a dummy value
	do
	{
		printf("\nCSE240 HW 7\n");
		printf("Please enter your selection:\n");

		printf("\t a: add a new book to the list\n");
		printf("\t d: display book list (no book type)\n");
		printf("\t b: search for a book on the list\n");

		printf("\t c: add a book type of a book\n");
		printf("\t l: display books who have a specific book type\n");
		printf("\t r: remove a book\n");
		printf("\t q: quit\n");

		selection = getchar();
		flushStdIn();
		executeAction(selection);
	} while (selection != 'q');

	return 0;
}

// flush out leftover '\n' characters
void flushStdIn()
{
	char c;
	do c = getchar();
	while (c != '\n' && c != EOF);
}

// Ask for details from user for the given selection and perform that action
// Read the function case by case
void executeAction(char c)
{
	char bookTitleInput[MAX_NAME], bookTypeInput[MAX_NAME];
	unsigned int aisleInput;
	struct book* searchResult = NULL;

	switch (c)
	{
	case 'a':	// add book
				// input book details from user
		printf("\nPlease enter books's title: ");
		fgets(bookTitleInput, sizeof(bookTitleInput), stdin);
		bookTitleInput[strlen(bookTitleInput) - 1] = '\0';	// discard the trailing '\n' char
		printf("Please enter aisle number: ");
		scanf("%d", &aisleInput);
		flushStdIn();

		//if (searchBook(bookTitleInput) == NULL)					
		if (searchBook(bookTitleInput) == NULL)	// Search book in 'libraryList'
		{
			addBook(bookTitleInput, aisleInput);
			printf("\nBook successfully added to the list!\n");
		}
		else
			printf("\nThat Book is already on the list!\n");
		break;

	case 'd':		// display the list
		displayBookList(list);
		break;

	case 'b':		// search for an book on the list
		printf("\nPlease enter book's title: ");
		fgets(bookTitleInput, sizeof(bookTitleInput), stdin);
		bookTitleInput[strlen(bookTitleInput) - 1] = '\0';	// discard the trailing '\n' char

		//if (searchBook(bookTitleInput) == NULL)					
		if (searchBook(bookTitleInput) == NULL)	// Search book in 'libraryList'
			printf("\nBook title does not exist or the list is empty! \n\n");
		else
		{
			printf("\nBook title exists on the list! \n\n");
		}
		break;

	case 'r':		// remove book
		printf("\nPlease enter book's title: ");
		fgets(bookTitleInput, sizeof(bookTitleInput), stdin);
		bookTitleInput[strlen(bookTitleInput) - 1] = '\0';	// discard the trailing '\n' char

		//if (searchBook(bookTitleInput) == NULL)				
		if (searchBook(bookTitleInput) == NULL)	// Search book in 'libraryList'
			printf("\nBook title does not exist or the list is empty! \n\n");
		else
		{
			removeBook(bookTitleInput);
			printf("\nBook title successfully removed from the list! \n\n");
		}
		break;

	case 'c':		// add book type
		printf("\nPlease enter book's title: ");
		fgets(bookTitleInput, sizeof(bookTitleInput), stdin);
		bookTitleInput[strlen(bookTitleInput) - 1] = '\0';	// discard the trailing '\n' char

		//if (searchBook(bookTitleInput) == NULL)					
		if (searchBook(bookTitleInput) == NULL)	// Search book in 'libraryList'
			printf("\nBook title does not exist or the list is empty! \n\n");
		else
		{
			printf("\nPlease enter book type: ");
			fgets(bookTypeInput, sizeof(bookTypeInput), stdin);
			bookTypeInput[strlen(bookTypeInput) - 1] = '\0';	// discard the trailing '\n' char

			addBookType(bookTitleInput, bookTypeInput);
			printf("\nBook type added! \n\n");
		}
		break;

	case 'l':		// list book type's books
		displayBookTypeList(list);
		break;

	case 'q':		// quit
		printf("\nGoodbye!");
		exit(0);
		break;

	default: printf("%c is invalid input!\n", c);
	}
}

// Q1: addBook (already implemented)
// This function is used to insert a new book in the linked list. 
// The new book is inserted to the head of linked list 'list'.
// You need NOT check if the book already exists in the list because that is taken care by searchBook() called in executeAction(). Look at how this function is used in executeAction().
// Don't bother to check how to implement searchBook() while implementing this function. Simply assume that book does not exist in the list while implementing this function.
// NOTE: The function needs to add the book to the head of the list.
// NOTE: This function does not add book types to the book info. There is another function addBookType() for that.
// Hint: In this question, no book type means NULL bookType.
void addBook(char* bookTitleInput, unsigned int aisleInput)
{
	// create new 'book' node
	struct book* newBook = (struct book*)malloc(sizeof(struct book));
	strcpy(newBook->title, bookTitleInput);		// fill new node with user input
	newBook->aisle = aisleInput;
	newBook->types = NULL;			// book types not added in this function

	// create new 'libraryList' node
	struct libraryList* newBookListMember = (struct libraryList*)malloc(sizeof(struct libraryList));
	newBookListMember->book = newBook;		// fill new node with new 'book' node
	newBookListMember->next = NULL;

	newBookListMember->next = list;		// add new 'libraryList' ahead of current head
	list = newBookListMember;			// make 'list' point to new head (new 'libraryList' node)
}

// Q2: displayBookList (already implemented)
// This function displays the book details (struct elements) of each book.
// Parse through the linked list 'list' and print the book details ( title and aisle number) one after the other.
// Book type is not display in this function.
// Notice that 'list' is passed to the function argument. Recursion is used to keep calling this function till end of list.
void displayBookList(struct libraryList* tempList)
{
	if (tempList == NULL)			// check if end of list is reached
	{
		printf("\n(end of list) \n");
		return;
	}
	tempList = list;
	while (tempList != NULL)
	{
		printf("\nBook Title: %s", tempList->book->title);
		printf("\nAisle number: %d\n", tempList->book->aisle);
		tempList = tempList->next;			// move on to next book
	}
}

// Q3: searchBook (5 points)
// This function searches the 'list' to check if the given book exists in the list. Search by book title.
// If it exists then return that 'book' node of the list. Notice the return type of this function.
// If the book does not exist in the list, then return NULL.
// NOTE: After implementing this fucntion, go to executeAction() to comment and un-comment the lines mentioned there which use searchBook()
//       in case 'a', case 'r', case 'l' (total 3 places)
struct book* searchBook(char* bookTitleInput)
{
	struct libraryList* tempList = list; // work on a copy of 'list'

	while (tempList != NULL)			 // While the end of the list is not reached
	{			 
		if (strcmp(tempList->book->title, bookTitleInput) == 0) // If the bookTitleInput matches with any book title in the list,
		{														//	
			return tempList->book;								// then return the book node
		}	
		else													// Otherwise, if there is no match at all
		{														//
			return NULL;										// then return a NULL value, therefore nonexistent or list is empty
		}
		tempList = tempList->next;		 // Move onto to the next book
	}
	
}

// Q4: addBookType (15 points)
// This function adds book type name to a book node.
// Parse the list to locate the book and add the book type to that book's 'bookType' linked list. No need to check if the book title exists on the list. That is done in executeAction().
// If the 'bookType' list is empty, then add the bookType. If the book has existing book types, then you may add the new book type to the head or the tail of the 'bookType' list.
// You can assume that the same book type does not exist. So no need to check for existing book type, like we do when we add new book.
// NOTE: Make note of whether you add the bookType to the head or tail of 'bookType' list. 
//       (Sample solution has book type added to the tail of 'bookType' list. You are free to add new book type to head or tail of 'bookType' list.)
void addBookType(char* bookTitleInput, char* bookTypeInput)
{
	// Create new 'bookType' node
	struct libraryList* tempList = list;		// work on a copy of 'list'
	struct book* tempBook = searchBook(bookTitleInput); // Check if book exists or not
	struct bookType* tempType = (struct bookType*)malloc(sizeof(struct bookType)); 

	strcpy(tempType->type, bookTypeInput); // Fill new node with user input
	tempType->next = tempBook->types;	   // Add new list of book types ahead of current head.
	tempBook->types = tempType;			   // Make 'tempBook->types' point to new head (new 'bookType' node)
}

// Q5: displayBookTypeList (15 points)
// This function prompts the user to enter a type name. This function then searches for books with this book type.
// Parse through the linked list passed as parameter and print the matching book details ( title and aisle) one after the other. See expected output screenshots in homework question file.
// HINT: Use inputs gathered in executeAction() as a model for getting the book type input.
// NOTE: You may re-use some Q2 displayBookList(list) code here.
void displayBookTypeList(struct libraryList* tempList)
{
	if (tempList == NULL)           // check if end of list is reached
	{
		printf("\n (end of list) \n");
		return;
	}
	else
	{
		char bookTypeInput[MAX_NAME];					   // Char variable for the user to enter book title
		printf("\nPlease enter book type: ");
		fgets(bookTypeInput, sizeof(bookTypeInput), stdin);
		bookTypeInput[strlen(bookTypeInput) - 1] = '\0';   // discard following '\n' char 

		while (tempList != NULL)						   // While the end of the list has not been reached
		{
			struct bookType* tempType = tempList->book->types;  
			int tempInt = 0;							   // A temporary integer with a dummy value
			while (tempType != NULL)					   // While the end of the bookType list has not been reached
			{					   
				if (strcmp(tempType->type, bookTypeInput) == 0) // If both strings match with each other,
				{												//
					tempInt = 1;								// then return the value of the temporary integer
					break;
				}
				tempType = tempType->next;				   // Move onto the next bookType
			}
			if (tempInt == 1)							   // If bookType list is found
			{							   
				printf("\nBook Title: %s", tempList->book->title);
				printf("\nAisle number: %d\n", tempList->book->aisle);
			}
			tempList = tempList->next;	// Move onto the next book
		}
	}
}

// Q6: removeBook (15 points)
// This function removes a book from the list.
// Parse the list to locate the book and delete that 'book' node.
// You need not check if the book exists because that is done in executeAction()
// removeBook() is supposed to remove book details like title and aisle number.
// The function will remove bookTypes of the book too.
// When the book is located in the 'list', after removing the title and aisle number, parse the 'bookType' list of that book
// and remove the book types.
void removeBook(char* bookTitleInput)
{
	struct libraryList* tempList = list;	// work on a copy of 'list'
	struct book* tempBook = searchBook(bookTitleInput);	// Check if book exists or not
	struct bookType* tempBookType = tempList->book->types; 
	struct libraryList* prevlist = list;	// work on previous list of the 'libraryList'
	struct libraryList* temp = list->next;	// work on temporary list
	int tempInt = 0;						// A temporary integer with a dummy value

	if (strcmp(tempList->book->title, bookTitleInput) == 0) // If both strings match with each other
	{
		list = list->next;											// Move onto next list
		while(tempList->book->types != NULL)						// While the end of the book list has not been reached
		{															
			tempList->book->types = tempList->book->types->next;    // Move onto the next bookType list
			free(tempBookType);										// Clear bookType node
		}
		free(tempList->book);										// Clear book node
		free(tempList);												// Clear node from the list
		tempInt = 1;												// The temporary integer value is 1 
	}
	else                                                    // Otherwise, no book removal if no match
	{
		while (temp != NULL)										// While the end of the temporary list has not been reached
		{
			if (strcmp(temp->book->title, bookTitleInput) == 0)		// If both strings match with each other 
			{
				break;												
			}
			prevlist = temp;										// Make the previous list point to new head (new 'libraryList' node)
			temp = temp->next;										// Move onto next temp node 
		}
		if (temp != NULL)											// If temporary list has not been reached
		{
			prevlist->next = temp->next;							// Add new list of previous nodes ahead of current head
			while (temp->book->types != NULL)						// While the end has not been reached 
			{
				tempBookType = temp->book->types;					// Move onto next type list
				temp->book->types = temp->book->types->next;		// Make 
				free(tempBookType);									// Clear bookType node
			}
			free(temp->book);										// Clear book node
			free(temp);												// Clear node from list
			tempInt = 1;											// The temporary integer value is 1
		}
	}
}
// End of hw7.c