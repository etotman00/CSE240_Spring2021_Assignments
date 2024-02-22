/*************************************************************
* Name: Ellis Totman
* Project Name: hw06q1.c (for HW6)
* Class: CSE240 Spring 2021
* IDE Software Used: Visual Studio
* Purpose of this project: This project gives the user 5 the 
* following five options. Option 1, add a new book. Option 2,
* display the list of books. Option 3, remove a book from list.
* Option 4, sort book list by ID. Option 5, quit the program.
* The project mainly focuses on linked lists.
*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable: 4996)

struct libraryRecord // The struct for the linked list.
{
	char bookTitle[50]; // Title of book with a 50 character limit.
	char author[50]; // Name of author with a 50 character limit.
	char bookGenre[50]; // Genre with a 50 character limit.
	unsigned int bookID; // Unsigned integer for book ID.
	unsigned int aisle; // Unsigned integer for aisle number.
	struct libraryRecord *next; // Pointer to libraryRecord structure.
};

struct libraryRecord *libraryList; // The list of books.

int counter = 0; // Universal variable for some function.

// Function needed for implementation and some already implemented.
int add(); // Addings book function.
int delete(); // Deletes book function.
void display(); // Displays list.
void sort(); // Sorts list by ID.
void swapID(struct libraryRecord* ID1, struct libraryRecord* ID2); // swapID() used as a sub-function for Sort().
void flushStdIn(); // Flushes any excess/remaining '\n' characters.
void save(char* fileName); // Saves file.
void load(char* fileName); // Loads file.

int main() // The main driver.
{
	libraryList = NULL; // The list is set to a "blank" dummy value.
	char* listOfBooks = "Library_List.txt"; // The name of the text file.
	load(listOfBooks); // Loads the file.
	char choice = 'i'; // Dummy value to start off.
	do
	{
		printf("\nWelcome to the CSE240 Library!\n"); // Welcome screen presented to the user.
		printf("\nPlease enter one of the following available options:\n"); // Asks the user to enter one of the following options below.
		printf("\t a: Add a new book\n");
		printf("\t d: Display book list\n");
		printf("\t r: Remove a book from list\n");
		printf("\t s: Sort book list by ID\n");
		printf("\t q: Quit program\n");
		scanf("%s", &choice);
		flushStdIn();
		switch (choice) // Switch statement used for the entered options.
		{
		case 'a': // The user wants to add a book.
			add();
			break;
		case 'd': // The user wants to display the list.
			display(); 
			break;
		case 'r': // The user wants to delete a book.
			delete(); 
			break;
		case 's': // The user wants to sort the list.
			sort();
			break;
		case 'q': // The user wants to quit.
			printf("\nGoodbye!\n\n");
			exit(1); // Program exits.
			break;
		default: // The user has entered an option that is not available.
			printf("\nOut of Range!\n\n");
			break;
		}
	} while (choice != 'q'); 

	save(listOfBooks); // Saves the list to the file.
	return 0;
}

int add()
{
	struct libraryRecord *newBook, *libraryTemp; // The libraryList named as 'newBook', along with a temporary variable for the if-else statements.
	newBook = (struct libraryRecord*)malloc(sizeof(struct libraryRecord)); // Allocates the memory for the list pointer.
	printf("\nEnter book title: "); // Asks user for book title.
	scanf("%s", newBook->bookTitle);
	printf("Enter name of author: "); // Asks user for author.
	scanf("%s", newBook->author); 
	printf("Enter book type: "); // Asks user for genre.
	scanf("%s", newBook->bookGenre);
	printf("Enter ID: "); // Asks user for ID.
	scanf("%d", &newBook->bookID);
	printf("Enter aisle number: "); // Asks user for aisle number.
	scanf("%d", &newBook->aisle);
	newBook->next = NULL; 
	if (libraryList == NULL) // If libraryList is empty, then a book won't be added.
	{
		libraryList = newBook;
		printf("\nFailed to add book to the list.\n\n");
		return 1;
	}
	else // Otherwise if present, then a book will be added to the list. 
	{
		libraryTemp = libraryList;
		while (libraryTemp->next!=NULL) 
		{
			libraryTemp = libraryTemp->next;
		}
		libraryTemp->next = newBook;
		printf("\nBook successfully added to the list!\n\n");
	}
	return 0;
}

void flushStdIn() // Gets rid of the excess '\n' characters.
{
	char c;
	do c = getchar();
	while (c != '\n' && c != EOF);
}

void display()
{
	struct libraryRecord* libraryTemp;
	if (libraryList == NULL) // If list is empty.
	{
		printf("\nNothing to display.\n\n");
		return;
	}

	libraryTemp = libraryList;
	while (libraryTemp != NULL) // If a book is present in the list, everything will be displayed.
	{
			printf("\nBook Title: %s\n", libraryTemp->bookTitle);
			printf("Author: %s\n", libraryTemp->author);
			printf("Book Genre: %s\n", libraryTemp->bookGenre);
			printf("Book ID: %d\n", libraryTemp->bookID);
			printf("Aisle number: %d\n", libraryTemp->aisle);
			printf("\n");
			libraryTemp = libraryTemp->next;
	}
}
void swapID(struct libraryRecord* ID1, struct libraryRecord* ID2) // Two struct variables used for swapping the main struct.
{
	int temp = ID1->bookID; 
	ID1->bookID = ID2->bookID;
	ID2->bookID = temp;
}

void sort()
{
	struct libraryRecord* ptr, *libraryTemp = NULL; // ptr variable, and temporary variable set to dummy value.
	int swapped; // Integer variable used for the loop below.

	if (libraryList == NULL) // If list contains only one book or is empty, no sorting will happen. 
		printf("\nNot enough books to sort!\n\n");
		return;
	
	do // This do-while loop sorts the list by book ID.
	{
		swapped = 0;
		ptr = libraryList;
		
		while (ptr->next != libraryTemp) 
		{
			if (ptr->bookID > ptr->next->bookID) 
			{
				swapID(ptr, ptr->next);
				swapped = 1;
			}
			ptr = ptr->next;
			printf("\nBook list sorted! Enter 'd' to view list.\n\n");
		}
		libraryTemp = ptr;
	} while (swapped);
}

void save(char* fileName)
{
	FILE* listOfBooks; // File variable is initialized as "listOfBooks".
	int x; // Integer variable used for the for-loop.
	listOfBooks = fopen(fileName, "wb"); // File opened for writing in-file.

	fwrite(libraryList, sizeof(libraryList), 1, listOfBooks);

	for (x = 0; x < counter; x++) 
	{
		fwrite(libraryList->bookTitle, sizeof(libraryList), 1, listOfBooks); // Writes title.
		fwrite(libraryList->author, sizeof(libraryList), 1, listOfBooks); // Writes author.
		fwrite(libraryList->bookGenre, sizeof(libraryList), 1, listOfBooks); // Writes genre.
		fwrite(&libraryList->bookID, sizeof(libraryList), 1, listOfBooks); // Writes ID.
		fwrite(&libraryList->aisle, sizeof(libraryList), 1, listOfBooks); // Writes aisle number.
	}

	fclose(listOfBooks); // Closes file.
}

int delete()
{
	struct libraryRecord* libraryTemp, *delBook; 
	delBook = (struct libraryRecord*)malloc(sizeof(struct libraryRecord)); // Allocates memory of list.
	printf("\nEnter ID of book for removal: "); // Asks user to enter book ID for book removal.
	scanf("%d", &delBook->bookID); 
	
	if (delBook->bookID == NULL) // If book is not found.
	{
		printf("\nBook not found in the list!\n\n");
		return 1;
	}
	if (delBook->bookID == libraryList->bookID) // If book is found.
	{
		libraryTemp = libraryList;
		libraryList = libraryList->next;
		free(libraryTemp); // The book is deleted and memory has been freed.
		printf("\nBook removed successfully!\n\n");
		return 0;
	}
	return;
}

void load(char* fileName) 
{
	FILE* listOfBooks; // File variable is initialized as "listOfBooks".
	char files[1000]; // Character limit set for the if else statement.
	listOfBooks = fopen(fileName, "r"); // File opened for reading.

	if (listOfBooks == NULL) // If file is not found.
	{
		printf("Failed to load file: %s\n", listOfBooks);
		return 1;
	}
	else // If file has been found.
	{ 
		fscanf(listOfBooks, "%[^\n]", files); // Searches for the file by name.
		printf("File successfully loaded!\n\n");
		fclose(listOfBooks); // Closes file.
		return 0;
	}
}
// End of Program.