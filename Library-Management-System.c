#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define TAB 9
#define BKSP 8
#define ENTER 10

// System functions
void password();
void menu();

// Book functions
void bookManagement();
void addBook();
void modifyBook();
void listBook();
void rentBook();
int searchBook(int);
void deleteBook();

// User functions
void userManagement();
void addUser();
void modifyUser();
void listUser();
void listRentals();
void searchUser();
void deleteUser();

// Developer information
void exitScreen();

void main()
{
    password();
}

struct termios old, current;

void initTerminal(int echo)
{
    tcgetattr(0, &old);
    current = old;
    current.c_lflag &= ~ICANON; // Disable canonical mode

    if (echo)
    {
        current.c_lflag |= ECHO; // Set echo mode
    }
    else
    {
        current.c_lflag &= ~ECHO; // Disable echo mode
    }
    tcsetattr(0, TCSANOW, &current);
}
void resetTerminal()
{
    tcsetattr(0, TCSANOW, &old);
}

char getch()
{
    char ch;
    initTerminal(0);
    ch = getchar();
    resetTerminal();

    return ch;
}

// Check password
void password()
{
    int passwordAttempt = 1;
    system("clear");
    printf("\t\t\t\t\tWelcome to Library\n");
    printf("--------------------\n");
    printf(">>> Login First <<<\n");
    printf("--------------------\n\n");

passwordLabel:
    printf("Enter the password. Hit ENTER to confirm. \n");
    printf("password: ");

    char pwd[25];
    char password[] = "Praveen";
    int i = 0;
    char ch;
    while (1)
    {
        ch = getch();

        if (ch == ENTER || ch == TAB)
        {
            pwd[i] = '\0';
            break;
        }
        else if (ch == BKSP)
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else
        {
            pwd[i++] = ch;
            printf("* \b");
        }
    }

    // Check password

    if (strcmp(password, pwd) == 0)
    {
        printf("\nAuthorized person\n");
        sleep(2);
        menu();
    }
    else
    {
        printf("\nInvalid password\n");
        (passwordAttempt == 3) ? exit(0) : passwordAttempt++;
        sleep(1);
        goto passwordLabel;
    }
}

// Main menu

void menu()
{
    system("clear");
    printf("----------------------------------\n");
    printf(">>> Library Management System <<<\n");
    printf("----------------------------------\n\n");
    printf("[*] 1. Book management\n");
    printf("[*] 2. User management\n");
    printf("[*] 3. Take a leave\n\n");

    printf("[*] Enter your choice & hit ENTER\n");
    printf("    Choice: ");

    int choice;
    scanf(" %d", &choice);
    switch (choice)
    {
    case 1:
        bookManagement();
        break;
    case 2:
        userManagement();
        break;
    case 3:
        exitScreen();
        exit(0);

    default:
        printf("Please choice current option\n");
        break;
    }

    fflush(stdin);
}

// Book management function
void bookManagement()
{
    system("clear");
    printf("---------------------------------------------------\n");
    printf(">>> Library Management System - Book panel <<<\n");
    printf("---------------------------------------------------\n\n");
    printf("[*] 1. Add book\n");
    printf("[*] 2. Modify book\n");
    printf("[*] 3. List book\n");
    printf("[*] 4. Rent book\n");
    printf("[*] 5. Search book\n");
    printf("[*] 6. Delete book\n");
    printf("[*] 7. Open main program\n");
    printf("[*] 8. Close\n\n");

    printf("[*] Enter your choice & hit ENTER\n");
    printf("    Choice: ");
    fflush(stdin);

    int choice;
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        addBook();
        break;
    case 2:
        modifyBook();
        break;
    case 3:
        listBook();
        break;
    case 4:
        rentBook();
        break;
    case 5:
        searchBook(3);
        break;
    case 6:
        deleteBook();
        break;
    case 7:
        menu();
        break;
    case 8:
        exitScreen();
        break;
    default:
        break;
    }
}

// User management

void userManagement()
{
    system("clear");
    printf("----------------------------------\n");
    printf(">>> Library Management System - User panel <<<\n");
    printf("----------------------------------\n\n");
    printf("[*] 1. Add user\n");
    printf("[*] 2. Modify user\n");
    printf("[*] 3. List user\n");
    printf("[*] 4. List rentals\n");
    printf("[*] 5. Search user\n");
    printf("[*] 6. Delete user\n");
    printf("[*] 7. Open main program\n");
    printf("[*] 8. Close\n\n");

    printf("[*] Enter your choice & hit ENTER\n");
    printf("    Choice: ");

    int choice;
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        addUser();
        break;
    case 2:
        modifyUser();
        break;
    case 3:
        listUser();
        break;
    case 4:
        listRentals();
        break;
    case 5:
        searchUser();
        break;
    case 6:
        deleteUser();
        break;
    case 7:
        menu();
        break;
    case 8:
        exitScreen();
        break;
    default:
        break;
    }
}
// Add book
void addBook()
{
    char book_name[100], book_author[25], book_publisher[25];
    int book_id, book_quantity;

    system("clear");
    printf("----------------------------\n");
    printf(">>> Add Boook <<<\n");
    printf("----------------------------\n\n");

addbook:
    FILE *fp = fopen("Book_details.txt", "a+");
    if (fp != NULL)
    {

        printf("[*] Enter Book name: ");
        scanf(" %[^\n]", book_name);

        printf("[*] Enter Book author: ");
        scanf(" %[^\n]", book_author);

        printf("[*] Enter Book publisher: ");
        scanf(" %[^\n]", book_publisher);

        printf("[*] Enter Book id: ");
        scanf("%d", &book_id);

        printf("[*] Enter Book quantity: ");
        scanf("%d", &book_quantity);

        fprintf(fp, "%s %s %s %d %d\n", book_name, book_author, book_publisher, book_id, book_quantity);

        printf("------------------------------\n");
        printf("[\xE2\x9C\x93] Book added successfully\n");
        printf("------------------------------\n");

        fclose(fp);

        char input;
        printf("[?] Add one more book (y/n): ");
        scanf(" %c", &input);
        printf("\n\n");

        if (input == 'n' || input == 'N')
        {
            bookManagement();
        }
        else
        {
            goto addbook;
        }
    }
    else
    {
        printf("[x] %s", strerror(errno));
        sleep(2);
        bookManagement();
    }
}

// Modify book
void modifyBook()
{

    if (searchBook(2) == 1)
    {
    }
    else
    {
        printf("\n-------------------------\n");
        printf(">>> [x] Record Not Found <<< \n");
        printf("-------------------------\n\n");
    }
}

// List book
void listBook()
{

    char find[50], book_name[100], book_author[25], book_publisher[25];
    int book_id, book_quantity;

    FILE *fp = fopen("Book_details.txt", "r");
    if (fp != NULL)
    {
        int count = 1;
        printf("\n-------------------------\n");
        printf(">>> [*] Book List <<< \n");
        printf("-------------------------\n\n");

        while (fscanf(fp, "%s %s %s %d %d", book_name, book_author, book_publisher, &book_id, &book_quantity) != EOF)
        {
            printf("------------------------------\n");
            printf("Book: %d\n", count++);
            printf("------------------------------\n");
            printf("[*] Book name: %s\n", book_name);
            printf("[*] Author name: %s\n", book_author);
            printf("[*] Publiser name: %s\n", book_publisher);
            printf("[*] Book id: %d\n", book_id);
            printf("[*] Quantity: %d\n\n", book_quantity);
        }
    }
    fclose(fp);

    char input;
    printf("[<--] Press any key to main menu ");
    getch();
    getch();
    sleep(2);
    menu();
}

// Rent book
void rentBook()
{
}

// Search Book
int searchBook(int searcher)
{
    char find[50], book_name[100], book_author[25], book_publisher[25];
    int book_id, book_quantity, flag = 0;

    printf("Enter book name or author name: ");
    scanf(" %[^n]", find);

    FILE *fp = fopen("Book_details.txt", "r");
    if (fp != NULL)
    {
        while (fscanf(fp, "%s %s %s %d %d", book_name, book_author, book_publisher, &book_id, &book_quantity) != EOF)
        {
            if (strcmp(find, book_name) || strcmp(find, book_author))
            {
                if (searcher == 3)
                {
                    printf("\n-------------------------\n");
                    printf(">>> [\xE2\x9C\x93] Record Found <<< \n");
                    printf("-------------------------\n\n");

                    printf("[*] Book name: %s\n", book_name);
                    printf("[*] Author name: %s\n", book_author);
                    printf("[*] Publiser name: %s\n", book_publisher);
                    printf("[*] Book id: %d\n", book_id);
                    printf("[*] Quantiry: %d\n", book_quantity);
                }
                else
                {
                    flag = 1;
                }
            }
            else
            {
                printf("\n-------------------------\n");
                printf(">>> [x] Record Not Found <<< \n");
                printf("-------------------------\n\n");
            }
        }
    }
    else
    {
        printf("%s\n", strerror(errno));
    }

    return flag;
}

// Delete book
void deleteBook()
{
}

// Add user
void addUser() {}

// Modify user
void modifyUser() {}

// List user
void listUser() {}

// List Rental
void listRentals() {}

// Search user
void searchUser() {}

// Delete user
void deleteUser() {}

// Exit screen
void exitScreen()
{
    system("clear");
    printf("-----------------------------------------------------------\n");
    printf(">>> Creater: @praveencyber21 (PRAVEEN M) <<<\n");
    printf("-----------------------------------------------------------\n\n");
    printf("[*] \n");
    printf("[*] \n");
    printf("[*] \n");
}