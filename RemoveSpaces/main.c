/**
 * A simple program used to remove the spaces from a string
*/

#include <stdio.h>
#include <string.h>
#include <malloc.h>

void removeSpaces(char* s, char* totString)
{
    char* token; 
    token = strtok(s, " ");
    strcpy(totString, token);

    while (token != NULL)
    {
        token = strtok(NULL, " ");

        if(token != NULL)
            strcat(totString, token); // concat the token into the new string
    }

}


int count_spaces(char* s) {
    char* cPtr;
    int spaces = 0;
    for (cPtr = s; cPtr < s + strlen(s); cPtr++) {
        if (*cPtr == ' ') {
            spaces++;
        }
    }
    return spaces;
}

int main()
{
    char s[20]; 
    char *sTot;
    int sTotDim; 

    gets(s);
    printf("- Hai acquisito: %s", s);

    if (strlen(s) > 0)
        sTotDim = strlen(s) - count_spaces(s);

    sTot = (char*)malloc(sizeof(char) * sTotDim); // allocation

    if (sTot != NULL) {
        if (sTot != NULL) {
            removeSpaces(s, sTot);
            printf("\n\n- Stringa finale: %s\n\n", sTot);
        }
    }

    return 0;
}