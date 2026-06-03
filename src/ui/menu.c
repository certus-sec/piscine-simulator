#include <stdio.h>

int menu_main(void)
{
    int choice;

    printf("\n1. Start Exam 00\n");
    printf("2. Start Exam 01\n");
    printf("3. Start Exam 02\n");
    printf("4. Start Exam 03\n");
    printf("0. Exit\n");
    printf("Choice: ");
    if (scanf("%d", &choice) != 1)
    {
        while (getchar() != '\n');
        return -1;
    }
    while (getchar() != '\n');
    return choice;
}

int menu_pause(void)
{
    int choice;

    printf("\n1. Continue\n");
    printf("2. Quit Exam\n");
    printf("Choice: ");
    if (scanf("%d", &choice) != 1)
    {
        while (getchar() != '\n');
        return -1;
    }
    while (getchar() != '\n');
    return choice;
}

int menu_confirm_submit(void)
{
    char c;

    printf("Submit? (y/n): ");
    if (scanf(" %c", &c) != 1)
    {
        while (getchar() != '\n');
        return 0;
    }
    while (getchar() != '\n');
    return (c == 'y' || c == 'Y');
}
