#include "main.h"

/**
 * reverseString - Reverse a given string in-place.
 *
 * @inputString: The string to be reversed.
 *
 * Return: No return value.
 */
void reverseString(char *inputString);
{
    int length = 0;
    int i, j;
    char *str, temp;

    while (length >= 0)
    {
        if (inputString[length] == '\0')
            break;
        length++;
    }
     for (i = 0, j = length - 1; i < j; i++, j--)
    {
	    temp = inputString[i];
        inputString[i] = inputString[j];
        inputString[j] = temp;
    }
}
int main() {
    char myString[] = "Hello, World!";
     reverseString(myString);
     printf("Reversed String: %s\n", myString);

    return 0;
}
