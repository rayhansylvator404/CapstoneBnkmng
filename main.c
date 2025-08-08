#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <conio.h>

#define MAX_TRANSACTIONS 100
// Pre-set admin credentials
#define ADMIN_USERNAME 999
#define ADMIN_PASSWORD 888
#define MAX_USERS 100 // Add this line to define the maximum number of users

// Structure to represent each transaction
typedef struct
{
    char type[20];
    int amount;
    int balanceAfter;
    char note[100];
} Transaction;

typedef struct
{
    int userID;
    char password[50];
    char username[50];
    char address[100];
    char mobileNo[15];
    char nid[20];
    char occupation[50];
    int mainBalance;

} User;

// Structure to store user data
struct table
{

    int username;
    int password;
    int choice;
    int sMoney;
    int mblrchrg;
    int cshout;
    int addmny;
    int banktrnsfr;
    int mrchntpay;
    int billpay;
    int mainBalance;

    char name[MAX_USERS][50];       // Array to store names
    char fatherName[MAX_USERS][50]; // Array to store father's names
    char address[MAX_USERS][100];   // Array to store addresses
    char mobileNo[MAX_USERS][15];   // Array to store mobile numbers
    char nid[MAX_USERS][20];        // Array to store NIDs
    char occupation[MAX_USERS][20]; // Array to store occupations
    int usernames[MAX_USERS];       // Array to store usernames
    int passwords[MAX_USERS];       // Array to store passwords
    User users[MAX_USERS];

    int userCount;
    Transaction transactions[MAX_TRANSACTIONS];
    int transactionCount;
} s;

// Function declarations
void startPage();
void homePage();
void signIn();
void login();
void userPage();
void passPage(int userIndex);
void adminLogin();
void adminControl();
void addMoneyAdmin();
void AdminHstryView();
void viewUserDetails();
void mainMenu();
void sendMoney();
void mobileRecharge();
void cashOut();
void merchantPay();
void BacktoHomePage();
void addMoney();
void billPay();
void bankTransfer();
void ChangePassword();
void checkBalance();
void viewTransactionHistory();
void addTransaction(char *type, int amount, int balanceAfter, char *note);
void saveUserData(User *users, int userCount);
int loadUserData(User *users);
void deleteUser(User *users, int *userCount, int userID);

// To avoid signing in again and again, a random user=123 & pass=321 stored with amount 500 Balance.
int main()
{
    s.userCount = loadUserData(s.users);
    startPage();
    return 0;
}

void startPage()
{

    int roleChoice;
    system("cls");

    printf("                                                      _    _      _                            _____      ______ _____ _   _   ______             _    \n");
    sleep(1); // 1-second delay

    printf("                                                     | |  | |    | |                          |_   _|     |  _  \\_   _| | | |  | ___ \\           | |   \n");
    sleep(1);

    printf("                                                     | |  | | ___| | ___ ___  _ __ ___   ___    | | ___   | | | | | | | | | |  | |_/ / __ _ _ __ | | __\n");
    sleep(1);

    printf("                                                     | |/\\| |/ _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\   | |/ _ \\  | | | | | | | | | |  | ___ \\/ _` | '_ \\| |/ /\n");
    sleep(1);

    printf("                                                     \\  /\\  /  __/ | (_| (_) | | | | | |  __/   | | (_) | | |/ / _| |_| |_| |  | |_/ / (_| | | | |   < \n");
    sleep(1);

    printf("                                                      \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|   \\_/\\___/  |___/  \\___/ \\___/   \\____/ \\__,_|_| |_|_|\\_\\\n");
    sleep(1);

    printf("\n\n=================================");
    sleep(.5);
    printf("====================================");
    sleep(.5);
    printf("====================================");
    sleep(1);
    printf("====================================");
    sleep(1);
    printf("=============================================================\n\n\n\n\n\n                                                                                            Choose your role:\n");
    printf("                                                                                            1. Admin\n");
    printf("                                                                                            2. Costumer\n");
    printf("                                                                                            Enter your choice: ");
    scanf("%d", &roleChoice);

    switch (roleChoice)
    {
    case 1:
        adminLogin();
        break;
    case 2:
        homePage();
        break;
    default:
        printf("Invalid choice. Please try again.\n");
        sleep(2);
        startPage();
        break;
    }
}

void adminLogin()
{
    int username, password;
    system("cls");

    printf("Admin Login\n");
    printf("Enter Admin Username: ");
    scanf("%d", &username);
    printf("Enter Admin Password: ");
    scanf("%d", &password);

    if (username == ADMIN_USERNAME && password == ADMIN_PASSWORD)
    {
        printf("Admin Login Successful!\n");
        sleep(2);
        adminControl();
    }
    else
    {
        printf("Invalid Admin credentials. Returning to main menu...\n");
        sleep(2);
        startPage();
    }
}

void adminControl()
{
    int adminChoice;
    do
    {
        system("cls");
        printf("Admin Control Panel\n");
        printf("1. View User Details\n");
        printf("2. Add Money to User\n");
        printf("3. View User Transaction History\n");
        printf("4. Exit\n");
        printf("Select an option: ");
        scanf("%d", &adminChoice);

        switch (adminChoice)
        {
        case 1:
            viewUserDetails(); // Call function to view user details
            break;
        case 2:
            addMoneyAdmin(); // Call function to add money to a user
            break;
        case 3:
            AdminHstryView(); // Call function to view transaction history
            break;
        case 4:
            printf("Exiting Admin Control Panel...\n");
            startPage();
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (adminChoice != 4);
}

void addMoneyAdmin()
{
    system("cls");
    int userIndex, amount;
    printf("Select user index to add money (1 to %d): ", s.userCount);
    scanf("%d", &userIndex);
    userIndex--; // Adjust for zero-based index

    if (userIndex >= 0 && userIndex < s.userCount)
    {
        printf("Enter amount to add: ");
        scanf("%d", &amount);

        // Add money to the selected user's balance
        s.users[userIndex].mainBalance += amount; // Assuming each user has a 'balance' field

        // Log the transaction
        addTransaction("Admin Added Money", amount, s.users[userIndex].mainBalance, "Added by admin");

        // Save user data
        saveUserData(s.users, s.userCount);

        printf("Money added successfully to user %d\n", userIndex + 1);
        sleep(3);
        adminControl();
    }
    else
    {
        printf("Invalid user index.\n");
    }
    printf("Press any key to continue...\n");
    getch();
}

// void addMoneyAdmin()
// {
//     system("cls");
//     int userIndex, amount;
//     printf("Select user index to add money (1 to %d): ", s.userCount);
//     scanf("%d", &userIndex);
//     userIndex--; // Adjust for zero-based index

//     if (userIndex >= 0 && userIndex < s.userCount)
//     {
//         printf("Enter amount to add: ");
//         scanf("%d", &amount);
//         s.mainBalance += amount;                                                      // Add money to the selected user's balance
//         addTransaction("Admin Added Money", amount, s.mainBalance, "Added by admin"); // Log the transaction
//         saveUserData(s.users, s.userCount);
//         printf("Money added successfully to user %d\n", userIndex + 1);
//     }
//     else
//     {
//         printf("Invalid user index.\n");
//     }
//     printf("Press any key to continue...\n");
//     getch();
// }

void AdminHstryView()
{
    system("cls");
    int userIndex;
    printf("Select user index to view transaction history (1 to %d): ", s.userCount);
    scanf("%d", &userIndex);
    userIndex--; // Adjust for zero-based index

    if (userIndex >= 0 && userIndex < s.userCount)
    {
        printf("Transaction History for User %d:\n", userIndex + 1);
        for (int i = 0; i < s.transactionCount; i++)
        {
            printf("%d. %s: %d (Balance after: %d)\n", i + 1, s.transactions[i].type, s.transactions[i].amount, s.transactions[i].balanceAfter);
            printf("Note: %s\n", s.transactions[i].note);
            printf("--------------------\n");
        }
    }
    else
    {
        printf("Invalid user index.\n");
    }
    printf("Press any key to continue...\n");
    getch();
}

void homePage()
{

    int option;
    system("cls");
    printf("Secure your PIN, trust no one, verify always!\n");

    /*sleep(1);
    printf("                                                                                                                                                                   \n");
    sleep(1);
    printf("                                                                                                                                                                   \n");
    sleep(1); */
    printf("1. Login\n2. Sign Up\n3. Go To Start Page\n");
    printf("Select an option: ");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        login();
        break;
    case 2:
        signIn();
        break;
    case 3:
        startPage();
        break;
    default:
        printf("Invalid option. Please try again.\n");
        sleep(2);
        homePage();
        break;
    }
}

void signIn()
{
    int count = 0;
    system("cls");

    printf("================\nSign Up Page\n");

    printf("Enter your name: ");
    scanf("%s", s.users[s.userCount].username); // Store name in the current user index

    printf("Enter your address: ");
    scanf("%s", s.users[s.userCount].address); // Store address in the current user index

    printf("Enter your mobile number: ");
    scanf("%s", s.users[s.userCount].mobileNo); // Store mobile number in the current user index

    printf("Enter your NID/Student ID number: ");
    scanf("%s", s.users[s.userCount].nid); // Store NID in the current user index

    printf("Enter your occupation (Student/Other)(Preamount 2000 for Student, 500 for others): ");
    scanf("%s", s.users[s.userCount].occupation); // Store occupation in the current user index

    // printf("Create a username: ");
    // scanf("%d", &s.username); // Store username in the current user index

    // printf("Create a password (numeric): ");
    // scanf("%d", &s.password); // Store password in the current user index

    int isUnique = 0;
    while (!isUnique)
    {
        printf("Create a userID: ");
        scanf("%d", &s.usernames[s.userCount]); // Store username in the current user index

        // Check for uniqueness
        isUnique = 1; // Assume it's unique
        for (int i = 0; i < s.userCount; i++)
        {
            if (s.usernames[i] == s.usernames[s.userCount])
            {
                printf("Username already exists. Please choose a different username.\n");
                isUnique = 0; // Not unique
                break;
            }
        }
    }

    // Create a unique user ID
    s.users[s.userCount].userID = s.userCount + 1; // Simple unique ID based on userCount

    // Input password
    printf("Create a Password: ");
    scanf("%s", s.users[s.userCount].password); // Store password in the current user index

    // Initial balance
    if (strcmp(s.users[s.userCount].occupation, "Student") == 0)
    {
        s.users[s.userCount].mainBalance = 2000; // 2000 taka for students
    }
    else
    {
        s.users[s.userCount].mainBalance = 500; // 500 taka for others
    }

    // // Initial balance
    // s.users[s.userCount].mainBalance = (strcmp(s.users[s.userCount].occupation, "Student") == 0) ? 2000 : 500; // Set initial balance

    s.userCount++; // Increment user count
    saveUserData(s.users, s.userCount);
    s.transactionCount = 0; // Initialize transaction count
    system("cls");
    printf("Congratulations! Now you are a member of DIU Bank\n");
    sleep(3);
    homePage();
}

void login()
{
    char FirstUser[50]; // Username input
    int usrcount = 0;

    do
    {
        printf("Enter your Name: ");
        scanf("%s", FirstUser); // Read username as string

        // Check if the entered username exists
        int userIndex = -1; // To store the index of the found user
        for (int i = 0; i < s.userCount; i++)
        {
            // Debugging output to see the usernames being compared
            // printf("Comparing with stored username: %s\n", s.users[i].username);
            if (strcmp(s.users[i].username, FirstUser) == 0) // Compare strings
            {
                userIndex = i;
                break;
            }
        }

        if (userIndex != -1)
        {

            char FirstPass[50];
            printf("Enter password: ");
            scanf("%s", FirstPass);

            if (strcmp(FirstPass, s.users[userIndex].password) == 0)
            {
                printf("Successfully logged in.\n");
                mainMenu();
                return;
            }
            else
            {
                printf("Incorrect password. Please try again...\n");
            }
        }
        else
        {
            printf("Your username is wrong. Please try again...\n");
        }

        usrcount++;
    } while (usrcount < 3);

    // If the user has failed 3 times
    system("cls");
    printf("Sorry, your account is blocked.\nYou tried 3 wrong attempts.\n");
    sleep(3);
}

void passPage(int userIndex)
{
    int FirstPass;
    int passCount = 0;

    do
    {
        printf("Enter password: ");
        scanf("%d", &FirstPass);

        if (FirstPass == s.passwords[userIndex])
        {
            printf("Successfully logged in.\n");
            printf("Welcome\n");
            sleep(1);
            mainMenu();
            return;
        }
        else
        {
            system("cls");
            printf("Wrong password, please try again\n");
            passCount++;
        }
    } while (passCount < 3);

    system("cls");
    printf("Sorry, your account is blocked.\nYou tried 3 wrong attempts.\n");
    return;
}

void mainMenu()
{
    system("cls");

    printf("Welcome to DIU BANK\n\nMain menu\n\n1. Send money\n2. Mobile Recharge\n3. Cash out\n4. Merchant pay\n5. Add Money\n6. Bill pay\n7. Bank to Bank transfer\n8. Change Password\n9. Check Balance\n10. View Transaction History\n11. BacktoHomePage\n");
    printf("Select one: ");
    scanf("%d", &s.choice);

    switch (s.choice)
    {
    case 1:
        sendMoney();
        break;
    case 2:
        mobileRecharge();
        break;
    case 3:
        cashOut();
        break;
    case 4:
        merchantPay();
        break;
    case 5:
        addMoney();
        break;
    case 6:
        billPay();
        break;
    case 7:
        bankTransfer();
        break;
    case 8:
        ChangePassword();
        break;
    case 9:
        checkBalance();
        break;
    case 10:
        viewTransactionHistory();
        break;
    case 11:
        BacktoHomePage();
        break;
    default:
        printf("Please select a number between 1 and 10\n");
        mainMenu();
        break;
    }
}
void sendMoney()
{
    system("cls");

    printf("                                                                         +-----------------+\n");
    printf("                                                                         |                 |\n");
    printf("                                                                         |   SEND MONEY    |\n");
    printf("                                                                         |                 |\n");
    printf("                                                                         +-----------------+\n\n\n\n");

    int recipientUsername;
    int count = 0;

    printf("Enter the No. to send money to: ");
    scanf("%d", &recipientUsername);

    char note[100] = "No note added.";

    printf("\nMindMap-(Enter a note to relate your transaction history)\n (1. YES / 2. NO): ");
    int addNote;
    scanf("%d", &addNote);

    if (addNote == 1)
    {
        printf("Enter a note for this transaction: ");
        getchar();
        fgets(note, sizeof(note), stdin);
        strtok(note, "\n");
    }

    printf("How much money do you want to send? ");
    scanf("%d", &s.sMoney);

    int senderIndex = s.userCount - 1; // Assuming the last user is the sender
    if (s.sMoney > s.users[senderIndex].mainBalance)
    {
        printf("Insufficient balance\n=======================\n");
        sleep(2);
        mainMenu();
        return; // Exit the function if insufficient balance
    }

    // Check if the recipient username exists
    int recipientIndex = -1; // To store the index of the found user
    for (int i = 0; i < s.userCount; i++)
    {
        if (s.mobileNo[i] == recipientUsername)
        {
            recipientIndex = i; // Store the index of the found user
            break;              // Exit the loop if username is found
        }
    }

    s.users[s.userCount - 1].mainBalance -= s.sMoney;

    if (recipientIndex != -1)
    {

        s.users[recipientIndex].mainBalance += s.sMoney;
        addTransaction("Send Money", s.sMoney, s.users[s.userCount - 1].mainBalance, note);
        saveUserData(s.users, s.userCount);
        printf("Successfully sent %d to user %d.\n", s.sMoney, recipientUsername);
    }
    else
    {

        srand(time(NULL));
        int randomIndex = rand() % s.userCount;
        s.users[randomIndex].mainBalance += s.sMoney;
        addTransaction("Send Money to Random User", s.sMoney, s.users[s.userCount - 1].mainBalance, note);
        saveUserData(s.users, s.userCount);
        printf("Sent %d to: %s (Username: %d).\n", s.sMoney, s.name[randomIndex], s.usernames[randomIndex]);
    }

    printf("Your Main Account Balance is: %d BDT right now\n====================\n", s.users[s.userCount - 1].mainBalance);
    sleep(4);
    mainMenu();
}

void mobileRecharge()
{
    system("cls");
    int rechargeAmount;
    int num;
    int count = 0;

    printf("                                                                         +-----------------+\n");
    printf("                                                                         |                 |\n");
    printf("                                                                         | Mobile Recharge |\n");
    printf("                                                                         |                 |\n");
    printf("                                                                         +-----------------+\n\n\n\n");

    printf("Enter 10-digit phone number:(+880) ");
    scanf("%d", &num);

    int temp = num;
    while (temp != 0)
    {
        count++;
        temp = temp / 10;
    }

    char note[100] = "No note added.";

    printf("\nMindMap-(Enter a note to relate your transaction history)\n (1. YES / 2. NO): ");
    int addNote;
    scanf("%d", &addNote);

    if (addNote == 1)
    {
        printf("Enter a note for this transaction: ");
        getchar();
        fgets(note, sizeof(note), stdin);
        strtok(note, "\n");
    }

    if (count == 10)
    {
        printf("Enter the amount to recharge: ");
        scanf("%d", &s.mblrchrg);

        int rchrgrerIndex = s.userCount - 1;
        if (s.mblrchrg > s.users[rchrgrerIndex].mainBalance)
        {
            printf("Insufficient balance\n=======================\n");
            sleep(1);
        }
        else
        {                                                     // Deduct amount from sender's account
            s.users[rchrgrerIndex].mainBalance -= s.mblrchrg; // Deduct from sender's balance

            addTransaction("Mobile Recharge", s.mblrchrg, s.users[s.userCount - 1].mainBalance, note);
            saveUserData(s.users, s.userCount);
            printf("Mobile recharge successful\n=======================\n");
            printf("Your Main Account Balance is: %d BDT right now\n====================\n", s.users[s.userCount - 1].mainBalance);
            sleep(4);
        }
    }
    else
    {
        printf("Invalid number, input a 10-digit number next time\n");
        sleep(2);
        mobileRecharge();
    }
    mainMenu();
}

void cashOut()
{
    system("cls");
    int amount, agntoratm;
    int num;
    int count = 0;
    char note[100] = "No note added.";

    printf("                                                                         +-----------------+\n");
    printf("                                                                         |                 |\n");
    printf("                                                                         |    Cash Out     |\n");
    printf("                                                                         |                 |\n");
    printf("                                                                         +-----------------+\n\n\n\n");

    printf("Cash out\n1. From Agent\n2. From ATM\n");
    scanf("%d", &agntoratm);
    if (agntoratm == 1)
    {
        printf("Enter 10-digit Agent phone number:(+880) ");
        scanf("%d", &num);

        int temp = num;
        while (temp != 0)
        {
            count++;
            temp = temp / 10;
        }

        printf("\nMindMap-(Enter a note to relate your transaction history)\n (1. YES / 2. NO): ");
        int addNote;
        scanf("%d", &addNote);

        if (addNote == 1)
        {
            printf("Enter a note for this transaction: ");
            getchar();
            fgets(note, sizeof(note), stdin);
            strtok(note, "\n");
        }

        if (count == 10)
        {
            printf("Enter the amount to cash out: ");
            scanf("%d", &s.cshout);

            int cshouterIndex = s.userCount - 1;
            if (s.cshout > s.users[cshouterIndex].mainBalance)
            {
                printf("Insufficient balance\n=======================\n");
            }
            else
            {
                s.users[s.userCount - 1].mainBalance -= s.cshout;
                addTransaction("Cash Out", s.cshout, s.users[s.userCount - 1].mainBalance, note);
                saveUserData(s.users, s.userCount);
                printf("Cash out successful from Agent\n=======================\n");
                printf("Your Main Account Balance is: %d BDT right now\n====================\n", s.users[s.userCount - 1].mainBalance);
                sleep(4);
            }
            mainMenu();
        }
    }
    else if (agntoratm == 2)
    {
        printf("Enter ATM Booth Code number: ");
        scanf("%d", &num);

        printf("Enter the amount to cash out: ");
        scanf("%d", &s.cshout);

        int cshouterIndex = s.userCount - 1;
        if (s.cshout > s.users[cshouterIndex].mainBalance)
        {
            printf("Insufficient balance\n=======================\n");
        }
        else
        {
            s.users[s.userCount - 1].mainBalance -= s.cshout;
            addTransaction("Cash Out", s.cshout, s.users[s.userCount - 1].mainBalance, note);
            saveUserData(s.users, s.userCount);
            printf("Cash out successful from ATM\n=======================\n");
            printf("Your Main Account Balance is: %d BDT right now\n====================\n", s.users[s.userCount - 1].mainBalance);
            sleep(4);
        }
        mainMenu();
    }
    else
    {
        printf("Please Select Correct Cash out Method again");
        sleep(1);
        cashOut();
    }
}

void merchantPay()
{
    system("cls");

    printf("                                                                         +-----------------+\n");
    printf("                                                                         |                 |\n");
    printf("                                                                         |  Merchant Pay   |\n");
    printf("                                                                         |                 |\n");
    printf("                                                                         +-----------------+\n\n\n\n");
    int amount, mrchn, mrchntpass;
    printf("Enter your Merchant Account no.: ");
    scanf("%d", &mrchn);

    printf("Enter the amount to pay to merchant: ");
    scanf("%d", &s.mrchntpay);

    char note[100] = "No note added.";

    printf("\nMindMap-(Enter a note to relate your transaction history)\n (1. YES / 2. NO): ");
    int addNote;
    scanf("%d", &addNote);

    if (addNote == 1)
    {
        printf("Enter a note for this transaction: ");
        getchar();
        fgets(note, sizeof(note), stdin);
        strtok(note, "\n");
    }

    // printf("Enter your account Password:");
    // scanf("%d", &mrchntpass);
    // if (mrchntpass == s.password || mrchntpass == 321)
    // {

    char FirstPass[50]; // Password input
    printf("Enter your account Password: ");
    scanf("%s", FirstPass); // Read password as string

    if (strcmp(FirstPass, s.users[s.userCount - 1].password) == 0) // Compare strings
    {
        int mrchnterIndex = s.userCount - 1;
        if (s.mrchntpay > s.users[mrchnterIndex].mainBalance)
        {
            printf("Insufficient balance\n=======================\n");
        }
        else
        {
            s.users[s.userCount - 1].mainBalance -= s.mrchntpay;
            addTransaction("Merchant Pay", s.mrchntpay, s.users[s.userCount - 1].mainBalance, note);
            saveUserData(s.users, s.userCount);
            printf("Merchant payment successful\n=======================\n");
            printf("Your Main Account Balance is: %d BDT right now\n====================\n", s.users[s.userCount - 1].mainBalance);
            sleep(4);
        }
        mainMenu();
    }
    else
    {
        printf("Incorrect Password\nPlease enter corrrect Password again");
        sleep(2);
        merchantPay();
    }

    // if (amount > s.mainBalance)
    // {
    //     printf("Insufficient balance, Please try again\n=======================\n");
    // }
    // else
    // {
    //     s.mainBalance -= amount;
    //     addTransaction("Merchant Pay", amount, s.mainBalance, note);
    //     printf("Merchant payment successful\n=======================\n");
    //     printf("Your Main Account Balance is: %d BDT right now\n====================\n", s.mainBalance);
    //     sleep(4);
    // }
    // mainMenu();
}

void addMoney()
{
    system("cls");
    int amount;
    int addOption;

    char note[100] = "No note added.";

    printf("                                                                         +-----------------+\n");
    printf("                                                                         |                 |\n");
    printf("                                                                         |     Add Money   |\n");
    printf("                                                                         |                 |\n");
    printf("                                                                         +-----------------+\n\n\n\n");

    printf("\nMindMap-(Enter a note to relate your transaction history)\n (1. YES / 2. NO): ");
    int addNote;
    scanf("%d", &addNote);

    if (addNote == 1)
    {
        printf("Enter a note for this transaction: ");
        getchar();
        fgets(note, sizeof(note), stdin);
        strtok(note, "\n");
    }

    printf("\nSelect method to add money:\n");
    printf("1. Card\n");
    printf("2. Mobile Wallet (mWallet)\n");
    printf("3. Internet Banking (iBanking)\n");
    printf("Select option: ");
    scanf("%d", &addOption);

    switch (addOption)
    {
    case 1: // Card
    {
        int cardOption;
        printf("\nSelect card type:\n");
        printf("1. Visa\n");
        printf("2. Mastercard\n");
        printf("Select option: ");
        scanf("%d", &cardOption);

        if (cardOption == 1)
        {
            char visaNo[20];
            printf("Enter Visa card account number: ");
            scanf("%s", visaNo);
        }
        else if (cardOption == 2)
        {
            char mastercardNo[20];
            printf("Enter Mastercard account number: ");
            scanf("%s", mastercardNo);
        }
        else
        {
            printf("Invalid card option selected.\n");
            sleep(2);
            addMoney();
            return;
        }
    }
    break;

    case 2: // mWallet
    {
        int mwalletOption;
        printf("\nSelect mobile wallet provider:\n");
        printf("1. Bkash\n");
        printf("2. Nagad\n");
        printf("3. Rocket\n");
        printf("4. Upay\n");
        printf("Select option: ");
        scanf("%d", &mwalletOption);

        if (mwalletOption >= 1 && mwalletOption <= 4)
        {
            char mwalletNo[20];
            printf("Enter mobile wallet account number: ");
            scanf("%s", mwalletNo);
        }
        else
        {
            printf("Invalid mWallet option selected.\n");
            sleep(2);
            addMoney();
            return;
        }
    }
    break;

    case 3: // iBanking
    {
        int ibankOption;
        printf("\nSelect bank:\n");
        printf("1. IBBL\n");
        printf("2. AB Bank\n");
        printf("Select option: ");
        scanf("%d", &ibankOption);

        if (ibankOption == 1)
        {
            char ibblNo[20];
            printf("Enter IBBL account number: ");
            scanf("%s", ibblNo);
        }
        else if (ibankOption == 2)
        {
            char abbankNo[20];
            printf("Enter AB Bank account number: ");
            scanf("%s", abbankNo);
        }
        else
        {
            printf("Invalid iBanking option selected.\n");
            sleep(2);
            addMoney();
            return;
        }
    }
    break;

    default:
        printf("Invalid option selected.\n");
        sleep(2);
        addMoney();
        return;
    }

    printf("Enter the amount to Add Money to your Account: ");
    scanf("%d", &s.addmny);
    int adderIndex = s.userCount - 1;
    s.users[s.userCount - 1].mainBalance += s.addmny;
    addTransaction("Add Money", s.addmny, s.users[s.userCount - 1].mainBalance, note);
    saveUserData(s.users, s.userCount);
    printf("Money added successfully\n=======================\n");
    printf("Your Main Account Balance is: %d BDT right now\n====================\n", s.users[s.userCount - 1].mainBalance);
    sleep(4);

    mainMenu();
}

void billPay()
{
    system("cls");
    int amount, billoption, accno;

    char note[100] = "No note added.";

    printf("                                                                         +-----------------+\n");
    printf("                                                                         |                 |\n");
    printf("                                                                         |     Bill Pay    |\n");
    printf("                                                                         |                 |\n");
    printf("                                                                         +-----------------+\n\n\n\n");

    printf("Enter the bill method:\n1. TV Bill\n2. Water Bill\n3. Electricity Bill\n4. Internet Bill\n ");
    scanf("%d", &billoption);
    if (billoption <= 4)
    {
        printf("Enter your Bill Account number: ");
        scanf("%d", &accno);

        printf("Enter the bill amount to pay: ");
        scanf("%d", &s.billpay);

        int billerIndex = s.userCount - 1;
        if (s.billpay > s.users[billerIndex].mainBalance)
        {
            printf("Insufficient balance\n=======================\n");
            sleep(3);
            mainMenu();
        }
        else
        {

            printf("MindMap-(Enter a note to relate your transaction history)\n (1. YES / 2. NO): ");
            int addNote;
            scanf("%d", &addNote);

            if (addNote == 1)
            {
                printf("Enter a note for this transaction: ");
                getchar();
                fgets(note, sizeof(note), stdin);
                strtok(note, "\n");
            }

            s.users[s.userCount - 1].mainBalance -= s.billpay;
            addTransaction("Bill Pay", s.billpay, s.users[s.userCount - 1].mainBalance, note);
            saveUserData(s.users, s.userCount);
            printf("Bill payment successful\n=======================\n");
            printf("Your Main Account Balance is: %d BDT right now\n====================\n", s.users[s.userCount - 1].mainBalance);
            sleep(4);

            mainMenu();
        }

        // s.mainBalance -= amount;
        // addTransaction("Bill Pay", amount, s.mainBalance, note);
        // printf("Bill payment successful\n=======================\n");
        // printf("Your Main Account Balance is: %d BDT right now\n====================\n", s.mainBalance);
        // sleep(4);

        mainMenu();
    }
    else
    {
        printf("Please enter correct Bill Method again");
        sleep(1);
        billPay();
    }
}

void bankTransfer()
{
    system("cls");
    int amount;
    int bnkAcc, BnkNm;

    char note[100] = "No note added.";

    printf("                                                                         +-----------------+\n");
    printf("                                                                         |                 |\n");
    printf("                                                                         |   Bank Transfer |\n");
    printf("                                                                         |                 |\n");
    printf("                                                                         +-----------------+\n\n\n\n");

    printf("Enter the Bank Serial number you want to transfer: \n1. Islami Bank\n2. Al Arafah Bank\n3. DBBL\n4. Brac Bank\n5. DIU Bank\n6. Phoenix Bank\n7. Premier Bank\n8. City Bank\n");
    scanf("%d", &BnkNm);

    if (BnkNm <= 8)
    {
        printf("Enter the Bank Account number you want to transfer: ");
        scanf("%d", &bnkAcc);

        printf("Enter the bill amount to pay: ");
        scanf("%d", &s.banktrnsfr);

        int bnktrsnfrerIndex = s.userCount - 1;
        if (s.banktrnsfr > s.users[bnktrsnfrerIndex].mainBalance)
        {
            printf("Insufficient balance\n=======================\n");
            sleep(3);
            mainMenu();
        }
        else
        {

            printf("MindMap-(Enter a note to relate your transaction history)\n (1. YES / 2. NO): ");
            int addNote;
            scanf("%d", &addNote);

            if (addNote == 1)
            {
                printf("Enter a note for this transaction: ");
                getchar();
                fgets(note, sizeof(note), stdin);
                strtok(note, "\n");
            }

            s.users[s.userCount - 1].mainBalance -= s.banktrnsfr;
            addTransaction("Bill Pay", s.banktrnsfr, s.users[s.userCount - 1].mainBalance, note);
            saveUserData(s.users, s.userCount);
            printf("Bank transfer successful\n=======================\n");
            printf("Your Main Account Balance is: %d BDT right now\n====================\n", s.users[s.userCount - 1].mainBalance);
            sleep(4);

            mainMenu();

            // printf("Enter the amount to transfer to another bank account: ");
            // scanf("%d", &amount);

            // if (amount > s.mainBalance)
            // {
            //     printf("Insufficient balance\n=======================\n");
            // }
            // else
            // {
            //     s.mainBalance -= amount;
            //     addTransaction("Bank Transfer", amount, s.mainBalance, note);
            //     printf("Bank transfer successful\n=======================\n");
            //     printf("Your Main Account Balance is: %d BDT right now\n====================\n", s.mainBalance);
            //     sleep(4);
            // }
            // mainMenu();
        }
    }
    else
    {
        printf("Correct Bank Number Select korun");
        sleep(2);
        bankTransfer();
    }
}

void ChangePassword()
{
    system("cls");
    char oldPass[50];
    char newPass[50];

    printf("                                                                         +-----------------+\n");
    printf("                                                                         |                 |\n");
    printf("                                                                         | Change Password |\n");
    printf("                                                                         |                 |\n");
    printf("                                                                         +-----------------+\n\n\n\n");

    printf("Enter old password: ");
    scanf("%s", oldPass);

    int currentUserIndex = s.userCount - 1;

    if (strcmp(oldPass, s.users[currentUserIndex].password) == 0)
    {
        printf("Successfully logged in.\n");
        printf("Enter your new Password: ");
        scanf("%s", newPass);

        strcpy(s.users[currentUserIndex].password, newPass);
        saveUserData(s.users, s.userCount);

        printf("Your Password has been successfully changed.\n");
        sleep(3);
        mainMenu();
        return;
    }
    else
    {
        printf("Incorrect old password. Please try again...\n");
        sleep(2);
        ChangePassword();
    }
}

// printf("Enter Your old password here:");
// scanf("%d", &oldpass);

// if (oldpass == s.password || oldpass == 321)
// {
//     printf("Enter your new username here:");
//     scanf("%d", &nuser);
//     s.username == nuser;
//     printf("Enter your new Password here:");
//     scanf("%d", &npass);
//     s.password = npass;
//     printf("your Password succesfully changed");
//     sleep(2);
//     mainMenu();
// }
// else
// {
//     printf("Please enter correct Password");
//     sleep(2);
//     ChangePassword();
// }

void checkBalance()
{
    system("cls");

    int currentUserIndex = s.userCount - 1;

    printf("                                                                         +-----------------+\n");
    printf("                                                                         |                 |\n");
    printf("                                                                         |  Check Balance  |\n");
    printf("                                                                         |                 |\n");
    printf("                                                                         +-----------------+\n\n\n\n");

    printf("Your Main Account Balance is: %d BDT right now\n====================\n", s.users[currentUserIndex].mainBalance);
    sleep(5);
    mainMenu();
}

void viewTransactionHistory()
{
    system("cls");

    printf("Transaction History:\n");

    for (int i = 0; i < s.transactionCount; i++)
    {
        printf("%d. %s: %d (Balance after: %d)\n", i + 1, s.transactions[i].type, s.transactions[i].amount, s.transactions[i].balanceAfter);
        printf("Note: %s\n", s.transactions[i].note);
        printf("--------------------\n");
    }
    printf("Press any key to continue\n");
    getch();
    mainMenu();
}

void addTransaction(char *type, int amount, int balanceAfter, char *note)
{
    if (s.transactionCount < MAX_TRANSACTIONS)
    {
        strcpy(s.transactions[s.transactionCount].type, type);
        s.transactions[s.transactionCount].amount = amount;
        s.transactions[s.transactionCount].balanceAfter = balanceAfter;
        strcpy(s.transactions[s.transactionCount].note, note);
        s.transactionCount++;
    }
    else
    {
        printf("Transaction history is full!\n");
    }
}

void viewUserDetails()
{
    system("cls");

    printf("                                                                         +-----------------+\n");
    printf("                                                                         |                 |\n");
    printf("                                                                         | View UserDetails|\n");
    printf("                                                                         |                 |\n");
    printf("                                                                         +-----------------+\n\n\n\n");

    printf("User  Details: %d Total Users Available right Now\n", s.userCount);
    printf("Select an option:\n");
    printf("1. View All User Details\n");
    printf("2. Search Individual User (1 to %d)\n", s.userCount);
    printf("0. Go to Home Page\n");
    printf("Enter your choice: ");

    int choice;
    scanf("%d", &choice);

    if (choice == 1) // View all user details
    {
        for (int i = 0; i < s.userCount; i++)
        {
            printf("User  %d:\n", i + 1);
            printf("User  ID: %d\n", s.users[i].userID);
            printf("Password: %s\n", s.users[i].password);
            printf("Username: %s\n", s.users[i].username);
            printf("Address: %s\n", s.users[i].address);          // Display address
            printf("Mobile Number: %s\n", s.users[i].mobileNo);   // Display mobile number
            printf("NID: %s\n", s.users[i].nid);                  // Display NID
            printf("Occupation: %s\n", s.users[i].occupation);    // Display occupation
            printf("Main Balance: %d\n", s.users[i].mainBalance); // Display main balance
            printf("--------------------\n");
        }

        // After displaying all user details, ask for further action
        printf("Select an option:\n");
        printf("1. Delete a User\n");
        printf("0. Go to Home Page\n");
        printf("Enter your choice: ");
        int actionChoice;
        scanf("%d", &actionChoice);

        if (actionChoice == 1) // Delete a user
        {
            int userIndex;
            printf("Enter the user index to delete (1 to %d): ", s.userCount);
            scanf("%d", &userIndex);
            userIndex--; // Adjust for zero-based index

            if (userIndex >= 0 && userIndex < s.userCount)
            {
                deleteUser(s.users, &s.userCount, s.users[userIndex].userID);
            }
            else
            {
                printf("Invalid user index.\n");
            }
        }
        else if (actionChoice == 0) // Go to Home Page
        {
            startPage();
        }
        else
        {
            printf("Invalid choice. Returning to Home Page...\n");
            homePage();
        }
    }
    else if (choice == 2) // Search for an individual user
    {
        int userIndex;
        printf("Enter the user index (1 to %d): ", s.userCount);
        scanf("%d", &userIndex);
        userIndex--; // Adjust for zero-based index

        if (userIndex >= 0 && userIndex < s.userCount)
        {
            printf("User  %d:\n", userIndex + 1);
            printf("User  ID: %d\n", s.users[userIndex].userID);
            printf("Password: %s\n", s.users[userIndex].password);
            printf("Username: %s\n", s.users[userIndex].username);
            printf("Address: %s\n", s.users[userIndex].address);          // Display address
            printf("Mobile Number: %s\n", s.users[userIndex].mobileNo);   // Display mobile number
            printf("NID: %s\n", s.users[userIndex].nid);                  // Display NID
            printf("Occupation: %s\n", s.users[userIndex].occupation);    // Display occupation
            printf("Main Balance: %d\n", s.users[userIndex].mainBalance); // Display main balance
        }
        else
        {
            printf("Invalid user index.\n");
        }
    }
    else if (choice == 0) // Go to Home Page
    {
        homePage();
    }
    else
    {
        printf("Invalid choice. Please try again.\n");
        viewUserDetails();
    }

    printf("Press any key to continue...\n");
    getch();
}

void saveUserData(User *users, int userCount)
{
    FILE *file = fopen("users.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < userCount; i++)
    {
        fprintf(file, "%d %s %s %s %s %s %s %d\n",
                users[i].userID,
                users[i].password,
                users[i].username,
                users[i].address,
                users[i].mobileNo,
                users[i].nid,
                users[i].occupation,
                users[i].mainBalance);
    }

    fclose(file);
}

int loadUserData(User *users)
{
    FILE *file = fopen("users.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file for reading.\n");
        return 0;
    }

    int userCount = 0;
    while (fscanf(file, "%d %49s %49s %99s %14s %19s %49s %d\n",
                  &users[userCount].userID,
                  users[userCount].password,
                  users[userCount].username,
                  users[userCount].address,
                  users[userCount].mobileNo,
                  users[userCount].nid,
                  users[userCount].occupation,
                  &users[userCount].mainBalance) == 8)
    {
        userCount++;
    }

    fclose(file);
    return userCount;
}

void deleteUser(User *users, int *userCount, int userID)
{
    int found = 0;
    for (int i = 0; i < *userCount; i++)
    {
        if (users[i].userID == userID)
        {
            found = 1;
            for (int j = i; j < *userCount - 1; j++)
            {
                users[j] = users[j + 1]; // Shift users left
            }
            (*userCount)--; // Decrease user count
            break;
        }
    }

    if (found)
    {
        saveUserData(users, *userCount); // Save updated user list
        printf("User  with ID %d deleted successfully.\n", userID);
    }
    else
    {
        printf("User  with ID %d not found.\n", userID);
    }
}

void BacktoHomePage()
{
    homePage();
}