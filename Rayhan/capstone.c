#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TRANSACTIONS 100

void homepage();

typedef struct
{
    char type[20];
    int amount;
} Transaction;

int main()
{
    homepage();
}

void homePage()
{

    int option = 0;

    printf("Welcome to Capstone Bank\n");
    printf("1. Login\n2. Sign In\n");
    printf("Select an option from this two: ");
    scanf("%d", &option);
    switch (option)
    {
    case 1:
        login();
        break;
    case 2:
        signIn();
        break;
    default:
        printf("hoynai abar 1 and 2 er moddhe select korun. Please try again.\n");
        homePage();
        break;
    }
}

