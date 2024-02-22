// CSE240 Spring 2021 HW3

// Name: Ellis Totman
// State the IDE that you use: Visual Studio 

#include <stdio.h>
#include <string.h>


#pragma warning(disable : 4996)  // compiler directive for Visual Studio only

// Read before you start:
// You are given a partially complete program. Your job is to complete the functions in order for this program to work successfully.
// All instructions are given above the required functions, please read them and follow them carefully. 
// You shoud not modify the function return types or parameters.
// You can assume that all inputs are valid. Ex: If prompted for an integer, the user will input an integer.

// Global Macro Values. They are used to define the size of 2D array of integers
#define NUM_ROWS 5
#define NUM_COLUMNS 5

#define NUM_STRINGS 5 
#define STRING_LENGTH 50

// Forward Declarations
void printMatrix(int[NUM_ROWS][NUM_COLUMNS]);
void printScalarMultiple(int[NUM_ROWS][NUM_COLUMNS], int);
void squaredSumMatrices(int[NUM_ROWS][NUM_COLUMNS], int[NUM_ROWS][NUM_COLUMNS]);
void squaredTransposeMatrix(int[NUM_ROWS][NUM_COLUMNS]);
void multiplyMatrix(int[NUM_ROWS][NUM_COLUMNS], int[NUM_ROWS][NUM_COLUMNS]);
int noOfOccurencesOfChar(char s[NUM_STRINGS * STRING_LENGTH], char);
void reverseStrings(char strings[NUM_STRINGS * STRING_LENGTH]);



// Problem 1: printMatrix (5 points)
// Traverse the 2D array of integers variable 'matrix' (input from main)
// and print the contents in the following format (actual contents may vary)
// 1 2 3 4 5
// 6 7 8 9 10
// 11 12 13 14 15
// 16 17 18 19 20
// 21 22 23 24 25
void printMatrix(int matrix[NUM_ROWS][NUM_COLUMNS])
{	
	// 'x' is the number of rows, while 'y' is the number of columns.
	int x, y;
	/* The logic within the for loops.
	* The first for loop is the row limit.
	* The second for loop is the column limit.
	*/
	for (x = 0; x < NUM_ROWS; x++) 
	{
		for (y = 0; y < NUM_COLUMNS; y++) 
		{
			printf("%d ", matrix[x][y]);
		}
		// Prints extra line space.
		printf("\n"); 
	}
}

// Problem 2: printScalarMultiple (5 points)
// Traverse the 2D array of integers 'matrix' and print scalar multiple of the matrix 
// e.g.
// 1 2 3	    2 4 6
// 4 5 6	=>  8 10 12
// 7 8 9        14 16 18
void printScalarMultiple(int matrix[NUM_ROWS][NUM_COLUMNS], int multiple)
{
	int x, y; 

	/* Same logic with problem (1), but
	* the array is multiplied by 2.
	*/
	for (x = 0; x < NUM_ROWS; x++) 
	{
		for (y = 0; y < NUM_COLUMNS; y++) 
		{
			printf("%d ", matrix[x][y] * multiple);
		}
		printf("\n");
	}
}

// Problem 3: printSquaredDiagonal (5 points)
// Traverse the 2D array of integers 'matrix' and print each squared value on the diagonal from the 
// top left to bottom right position.
// e.g.
// 1 2 3		1 25 81
// 4 5 6	=>
// 7 8 9
void printSquaredDiagonal(int matrix[NUM_ROWS][NUM_COLUMNS])
{
	int x, squared;

	/* Within the for loop below, 
	* the matrix array is multiplied by 
	* another matrix array so that it 
	* would be printed out as a squared
	* answer.
	*/
	for (x = 0; x < NUM_ROWS && x < NUM_COLUMNS; x++) 
	{
		squared = matrix[x][x] * matrix[x][x];
		printf("%d ",  squared);
	}
	printf("\n");
		
}


// Problem 4: squaredSumMatrices (5 points)
// Traverse the 2D array of integers 'matrices' and print the sum of each squared value.
// Consider both the arrays are of same size.
// e.g.
// 1 2 3   1 2 3        2 8 18
// 4 5 6   4 5 6	=> 32 50 72
// 7 8 9   7 8 9  	   98 128 162  

void squaredSumMatrices(int matrix1[NUM_ROWS][NUM_COLUMNS], int matrix2[NUM_ROWS][NUM_COLUMNS])
{
	int x, y, squared_sum;
	
	/* 'matrix2' array is the product of 
	*  two 'matrix1' arrays. Then 
	* two 'matrix2' arrays are added together
	* to get the squared sum.
	*/
	for (x = 0; x < NUM_ROWS; x++)
	{
		for (y = 0; y < NUM_COLUMNS; y++) 
		{
			matrix2[x][y] = matrix1[x][y] * matrix1[x][y];
			squared_sum = matrix2[x][y] + matrix2[x][y];
			printf("%d ", squared_sum);
		}
		printf("\n");
	}
}

// Problem 5: squaredTransposeMatrix (10 points)
// Take the 2D array of integers 'matrix' and print the squared tranpose matrix.
// You may assume that row and column counts are equal.
// **Hint: Use printMatrix to print the result**
// e.g.
// 1 2 3	    1 16 49
// 4 5 6	=>  4 25 64
// 7 8 9        9 36 81
void squaredTransposeMatrix(int matrix[NUM_ROWS][NUM_COLUMNS])
{
	int x, y, matrix2[NUM_ROWS][NUM_COLUMNS];
	for (x = 0; x < NUM_ROWS; ++x)
	{
		for (y = 0; y < NUM_COLUMNS; ++y) 
		{
			/* The variable 'x' and 'y' have swapped
			* places from each other so that the array would
			* be printed out in a way where the order of 
			* squared transposed numbers would be counted
			* from up to down, left to right.
			*/
			matrix2[y][x] = matrix[x][y];
		}
	}

	// Prints the array.
	for (x = 0; x < NUM_ROWS; ++x) 
	{
		for (y = 0; y < NUM_COLUMNS; ++y) 
		{
			printf("%d ", matrix2[x][y]);
		}
		printf("\n");
	}

}

// Problem 6: multiplyMatrix (10 points)
// Take two 2D arrays of integers 'matrix1' and 'matrix2' and print the 
// resulting matrix gained by multiplying the entries in each corresponding location.
// You can assume the two matrices will have the same dimensions.
// **Hint: Use printMatrix to print the result**
// e.g.
// 1 2 3	1 2 3      1 4 9
// 4 5 6	4 5 6  =>  16 25 36
// 7 8 9    7 8 9      49 64 81
void multiplyMatrix(int matrix1[NUM_ROWS][NUM_COLUMNS], int matrix2[NUM_ROWS][NUM_COLUMNS])
{
	int x, y, matrixResult[NUM_ROWS][NUM_COLUMNS];
	for (x = 0; x < NUM_ROWS; ++x)
	{
		for (y = 0; y < NUM_COLUMNS; ++y)
		{
			/* The 'matrix2' array is equal to 
			* the first matrix. The second matrix 
			* then goes into the result, where each
			* number is squared.
			*/
			matrix2[x][y] = matrix1[x][y];
			matrixResult[x][y] = matrix2[x][y];
			printf("%d ", matrixResult[x][y]);
		}
		printf("\n");
	}
}

// Problem 7: reverseString (5 points)
// Reverse each string of strings[][]. 
// Consider one string at a time and reverse the characters. For instance, "hi hello" should reverse to "olleh ih".
void reverseStrings(char strings[NUM_STRINGS * STRING_LENGTH])
{
	// The limit amount of characters allowed.
	strings[STRING_LENGTH];
	/* The strings that the user inputed
	* will be reversed by using 'strrev'.
	*/
	strrev(strings);
}

// Problem 8: noOfOccurencesOfChar (5 points)
// Count all occurrences of the specified character 'filter' from s[]. 
int noOfOccurencesOfChar(char s[NUM_STRINGS * STRING_LENGTH], char filter)
{
	/* 'x' initialized for the loop below.
	* 'charCount' will count the occurrences
	* of a specific character.
	*/
	int x, charCount = 0;
	for (x = 0; s[x]; x++) 
	{
		if (s[x] == filter)
		{
			charCount++;
		}
	}
	return charCount;
}

// You should study and understand how this main() works.
// *** DO NOT modify it in any way ***
int main()
{
	printf("CSE240 HW3: 2D Integer Arrays\n\n");

	int matrix[NUM_ROWS][NUM_COLUMNS] =
	{
		{1, 2, 3, 4, 5},
		{6, 7, 8, 9, 10},
		{11, 12, 13, 14, 15},
		{16, 17, 18, 19, 20},
		{21, 22, 23, 24, 25}
	};
	int multiple = 2;

	printMatrix(matrix);
	printf("\n\n");
	printScalarMultiple(matrix, multiple);
	printf("\n\n");
	printSquaredDiagonal(matrix);
	printf("\n\n");
	squaredSumMatrices(matrix, matrix);
	printf("\n\n");
	squaredTransposeMatrix(matrix);
	printf("\n\n");
	multiplyMatrix(matrix, matrix);

	printf("\nCSE240 HW3: 2D Character Arrays\n\n");

	char words[NUM_STRINGS * STRING_LENGTH];
	printf("\nEnter sentence with max 5 words: ");
	fgets(words, sizeof(words), stdin);
	reverseStrings(words);
	printf("\nReveresed string: %s", words);
	printf("\nNo of occurences of a: %d", noOfOccurencesOfChar(words, 'a'));
	int i = getchar();
	i = getchar(); // Keep console open
	return 0;
}
