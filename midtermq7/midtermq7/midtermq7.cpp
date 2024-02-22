// Type your code here, or load an example.
#include <stdio.h>
#include <string.h>
#include <fstream>
#pragma warning(disable: 4996)
int main()
{
    int a, b, c;
    int first, second, third;
    printf("Enter a? ");
    scanf("%d", &a);
    printf("Enter b? ");
    scanf("%d", &b);
    printf("Enter c? ");
    scanf("%d", &c);

    if (a >= b)
    {
        if (a >= c)
        {
            first = a;
            if (b >= c)
            {
                second = b;
                third = c;
            }
            else
            {
                second = c;
                third = b;
            }
        }
        else
        {
            first = c;
            second = a;
            third = b;
        }
    }
    else
    {
        if (b >= c)
        {
            first = b;
            if (a >= c)
            {
                second = a;
                third = c;
            }
            else
            {
                second = c;
                third = a;
            }
        }
        else
        {
            first = c;
            second = b;
            third = a;
        }
    }
    a = first, b = second, c = third;
    printf("a = %d\n", first);
    printf("b = %d\n", second);
    printf("c = %d\n", third);
    return 0;
}