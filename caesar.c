#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char *inputString(FILE* fp, size_t size){
//The size is extended by the input with the value of the provisional
    char *str;
    int ch;
    size_t len = 0;
    str = realloc(NULL, sizeof(char)*size);//size is start size
    if(!str)return str;
    while(EOF!=(ch=fgetc(fp)) && ch != '\n'){
        str[len++]=ch;
        if(len==size){
            str = realloc(str, sizeof(char)*(size+=16));
            if(!str)return str;
        }
    }
    str[len++]='\0';

    return realloc(str, sizeof(char)*len);
}

int main(int argc, char *argv[])
{
    if (argc != 2) // checks if the string count at the command line is correct
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    for (int o = 0, b = strlen(argv[1]); o < b; o++) // checks if the second string on the command line is not a number
    {
        if (isalpha(argv[1][o]) || ispunct(argv[1][o]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    int c = atoi(argv[1]);
    if (argc == 2 && c > 0 && c < pow(2, 31) - 26) // checks if the second string on the command line is a positive number
    {
        char *p;
        printf("plaintext: ");
        p = inputString(stdin, 10);
        printf("ciphertext: ");
        for (int l = 0, n = strlen(p); l < n; l++)
        {
            if (ispunct(p[l]) || isblank(p[l]) || isdigit(p[l])) // looks for if there are any chars that are not alphabetical and then prints them
            {
                printf("%c", p[l]);
                
            }
            if (isupper(p[l])) // checks if the string has any uppercase letters
            {
                if (!isupper((int) p[l] + c))
                {
                    printf("%c", ((int) p[l] - 65 + c) % 26 + 65);
                }
                else
                {
                    printf("%c", ((int) p[l] + c));
                }
            }
            if (islower(p[l])) //checks if the string has any lowercase letters
            {
                if (!islower((int) p[l] + c))
                {
                    printf("%c", ((int) p[l] - 97 + c) % 26 + 97);
                }
                else
                {
                    printf("%c", ((int) p[l] + c));
                }
            }
        }
        printf("\n");
        free(p);
        return 0;
    }
}