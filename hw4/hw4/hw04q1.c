//CSE240 Spring 2021 HW4

// Name: Ellis Totman
// State the IDE that you use: Visual Studio

#include <stdio.h>
#include <string.h>

#pragma warning(disable : 4996)  // compiler directive for Visual Studio only

// Read before you start:
// You are given a partially complete program. Complete the functions in order for this program to work successfully.
// All instructions are given above the required functions, please read them and follow them carefully. 
// You shoud not modify the function return types or parameters.
// You can assume that all inputs are valid. Ex: If prompted for an integer, the user will input an integer.
// You can use only the strlen() of strings.h library to check string length. Do not use any other string functions 
// because you are supposed to use pointers for this homework. 
// **** DO NOT use arrays to store or to index the characters in the string ****

// Global Macro Values. They are used to define the size of 2D array of characters
#define NUM_STRINGS 4
#define STRING_LENGTH 50

// Forward Declarations
void initializeStrings(char[NUM_STRINGS][STRING_LENGTH]);
void printStrings(char[NUM_STRINGS][STRING_LENGTH]);
void toUppercase(char[STRING_LENGTH]);
void toLowercase(char[STRING_LENGTH]);
void changeAllToUpperOrLower(char[NUM_STRINGS][STRING_LENGTH], char);
void wordMatch(char strings[NUM_STRINGS][STRING_LENGTH], char input[STRING_LENGTH]);
void concatStr(char[NUM_STRINGS][STRING_LENGTH], char[NUM_STRINGS * STRING_LENGTH]);


// Problem 1: initializeStrings (5 points)
// Use pointer 'p' to traverse the 2D array of characters variable 'strings' (input from user in main() ) and set all characters in each
// array to a null terminator so that there is a 4 row and 50 column 2D array full of null terminators.
// The null terminator '\0' is used to denote the end of a string.
void initializeStrings(char strings[NUM_STRINGS][STRING_LENGTH])
{

	// Pointer and two integers initialized.
	char* p = &strings[0][0];
	int x, y;

	// 'For' loop for the 2D array.
	for (x = 0; x < NUM_STRINGS; x++)
	{
		for (y = 0; y < STRING_LENGTH; y++) 
		{
			//The array is set to the null terminator.
			*(p + x * STRING_LENGTH + y) = '\0';
		}
	}
}

// Problem 2: printStrings (5 points)
// Use pointer 'p' to traverse the 2D character array 'strings' and print each string.
// See the example outputs provided in the word document. Each string should be printed on a new line.
void printStrings(char strings[NUM_STRINGS][STRING_LENGTH])
{
	
	// Pointer and two integers initialized.
	char* p = &strings[0][0];
	int x, y;

	// 'For' loop for the 2D array.
	for (x = 0; x < NUM_STRINGS; x++)
	{
		for (y = 0; y < STRING_LENGTH; y++)
		{
			//The array is printed.
			printf("%c", strings[x][y]);
			p++;
		}
		printf("\n");
	}
}

// Problem 3: toUppercase() and toLowercase() (15 points)
// Problem 3-1: toUppercase 
// Convert the string in the array 's' to an uppercase string.
// Traverse the input using pointer 'p' and covert the character to an uppercase letter if it is lowercase.
// You need to write down the code to check whether or not the character is lowercase.
// HINT: Use a pointer to change the ASCII value of a character.
//       The ASCII value of 'a'= 97 and the ASCII value of 'A' = 65 so the difference between them is 32.
void toUppercase(char s[STRING_LENGTH]) 
{
	
	// Pointer and integer initialized.
	char* p = &s[0];
	int x;

	// 'For' loop used for the array.
	for (x = 0; s[x] != '\0'; x++) 
	{
		if (s[x] >= 'a'  && s[x] <= 'z')
		{
			// The string is then capitalized. 
			s[x] = s[x] - 32;
			p++;
		}
	}
}

// Problem 3-2: toLowercase 
// HINT : This should be very similar to toUppercase().
// Convert the string in the array 's' to an lowercase string.
// Traverse the input using pointer 'p' and covert the character to a lowercase letter if it is uppercase.
// You need to write down the code to check whether or not the character is uppercase.
// HINT: Use a pointer to change the ASCII value of a character.
//       The ASCII value of 'a'= 97 and the ASCII value of 'A' = 65 so the difference between them is 32.
void toLowercase(char s[STRING_LENGTH]) 
{

	// Pointer and integer initialized. 
	char* p = &s[0];
	int x;

	// 'For' loop used for the array.
	for (x = 0; x <= strlen(s); x++)
	{
		if (s[x] >= 65 && s[x] <= 90) 
		{
			// The string is then lowercased.
			s[x] = s[x] + 32;
			p++;
		}
	}
}


// Problem 4: changeAllToUpperOrLower (5 points)
// Change all words in the array 'strings' to uppercase or lowercase based on the value of char variable 'set'.
// If the value of char 'set' is 'u' or 'U', change all words to uppercase strings.
// If the value of char 'set' is 'l' or 'L', change all words to lowercase strings.
// No change, otherwise.
// You may use toUppercase() and toLowercase() here.
void changeAllToUpperOrLower(char strings[NUM_STRINGS][STRING_LENGTH], char set) 
{

	// Initialized pointer.
	char* ptr = &strings[0][0];

	// If the char is 'u' or 'U', the string will be capitalized.
	if (set == 'u' || set == 'U') 
	{
		toUppercase(strings);
	}
	// If the char is 'l' or 'L', the string will be lowercased.
	if (set == 'l' || set == 'L') 
	{
		toLowercase(strings);
	}
	else
	{
	}
}

// Problem 5: wordMatch (10 points)
// This function must be working as follows:
// 1. Compare the strings in the 2D array with input string
// 2. If one of them matches with input string, print "Match found"
// 3. Else print "Match not found"
// Example: strings array -> ["Hi", "Sun", "Devils"], input -> "Sun"  => print "Match found"
// Example: strings array -> ["Hi", "Sun", "Devils"], input -> "Hello"  => print "Match not found"
void wordMatch(char strings[NUM_STRINGS][STRING_LENGTH], char input[STRING_LENGTH]) 
{

	// Pointer and integers initialized.
	char* p = &strings[0][0];
	int flag = 0, x, y, z;

	// 'For' loop for the array and preparation for the matching process.
	for (x = 0; x < NUM_STRINGS; x++)
	{
		for (z = 0; z < STRING_LENGTH; z++) 
		{
			y = strcmp(&strings[x][z], input);
			if (y == 0) {
			flag = x;
			}
		}
	}

	// If the inputed word matches with one of the string.
	if (flag == 0) 
	{
		printf("No match");
	}
	// If the word does not match.
	else 
	{
		printf("Match found");
	}
	printf("\n");
}

// Problem 6: concatStr (10 points)
// This function must be working as follows:
// 1. Concatenate the string in the array 'strings' together in a sentence.
// 2. Store the string to the array 'result'.
// 3. Print the string in the array 'result'.
// The sample output is shown in document
// NOTE: This is the function partially containing what you have implemented so far.
// Initialize the array 'result' first before you store a string to it.
// You may declare and use more pointers if needed.
void concatStr(char strings[NUM_STRINGS][STRING_LENGTH], char result[NUM_STRINGS * STRING_LENGTH]) 
{

	// Pointers and integers initialized.
	char* p_result = result[0] = NULL;
	char* p = &strings[0][0];
	char* p_input = &strings[0][0];
	char* p_input2 = &strings[1][0];
	char* p_input3 = &strings[2][0];
	char* p_input4 = &strings[3][0];
	int x, y;

	// The concatenation of the strings from the array, plus spaces in between.
	strcat(result, p_input);
	strcat(result, " ");
	strcat(result, p_input2);
	strcat(result, " ");
	strcat(result, p_input3);
	strcat(result, " ");
	strcat(result, p_input4);
	strcat(result, " ");
	printf("%s", result);
	
}


// You should study and understand how main() works.
// *** DO NOT modify it in any way ***
int main()
{
	char strings[NUM_STRINGS][STRING_LENGTH]; // will store four strings each with a max length of 34
	int i, key;
	char input[STRING_LENGTH];
	char result[NUM_STRINGS * STRING_LENGTH];

	printf("CSE240 HW4: Pointers\n\n");
	initializeStrings(strings);

	for (i = 0; i < NUM_STRINGS; i++)
	{
		printf("Enter a string: ");				// prompt for string
		fgets(input, sizeof(input), stdin);		// store input string
		input[strlen(input) - 1] = '\0';		// convert trailing '\n' char to '\0' (null terminator)
		strcpy(strings[i], input);				// copy input to 2D strings array
	}

	printf("\nEnter a string to find a match: ");	// prompt for string
	fgets(input, sizeof(input), stdin);			// store input string
	input[strlen(input) - 1] = '\0';			// convert trailing '\n' char to '\0' (null terminator)

	// Word match function call
	wordMatch(strings, input);

	// Concate all strings in array string to a sentence
	printf("\n\nThe concatenated string is: \n");
	concatStr(strings, result);

	// Convert all strings in array string to a particular case
	printf("\n\nChange strings to a particular case: \n");
	changeAllToUpperOrLower(strings, 'l');
	printStrings(strings);
	getchar();									// flush out newline '\n' char



	getchar();									// keep VS console open
	return 0;
}