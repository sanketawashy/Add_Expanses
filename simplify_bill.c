#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FRIENDS 10
#define MAX_DESCRIPTION 50

typedef struct {
    char name[20];
    double balance;
} Friend;

typedef struct {
    char description[MAX_DESCRIPTION];
    double amount;
    Friend *payer;
    Friend *payee;
} Expense;

void printMenu();
void addFriend(Friend *friends, int *numFriends);
void displayFriends(Friend *friends, int numFriends);
void addExpense(Friend *friends, int numFriends, Expense *expenses, int *numExpenses);
void settleBalances(Friend *friends, int numFriends);

int main() {
    Friend friends[MAX_FRIENDS];
    Expense expenses[MAX_FRIENDS * MAX_FRIENDS]; // Assume each friend can have an expense with every other friend
    int numFriends = 0;
    int numExpenses = 0;
    int choice;

    do {
        printMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addFriend(friends, &numFriends);
                break;
            case 2:
                displayFriends(friends, numFriends);
                break;
            case 3:
                addExpense(friends, numFriends, expenses, &numExpenses);
                break;
            case 4:
                settleBalances(friends, numFriends);
                break;
            case 5:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

void printMenu() {
    printf("\n--- Splitwise Simulator ---\n");
    printf("1. Add a friend\n");
    printf("2. Display friends\n");
    printf("3. Add an expense\n");
    printf("4. Settle balances\n");
    printf("5. Exit\n");
}

void addFriend(Friend *friends, int *numFriends) {
    if (*numFriends >= MAX_FRIENDS) {
        printf("Cannot add more friends. Maximum limit reached.\n");
        return;
    }

    printf("Enter the name of the friend: ");
    scanf("%s", friends[*numFriends].name);
    friends[*numFriends].balance = 0.0;

    (*numFriends)++;
}

void displayFriends(Friend *friends, int numFriends) {
    printf("\n--- Friends ---\n");
    for (int i = 0; i < numFriends; ++i) {
        printf("%d. %s (Balance: %.2f)\n", i + 1, friends[i].name, friends[i].balance);
    }
}

void addExpense(Friend *friends, int numFriends, Expense *expenses, int *numExpenses) {
    if (numFriends < 2) {
        printf("You need at least two friends to add an expense.\n");
        return;
    }

    printf("Enter a description for the expense: ");
    scanf("%s", expenses[*numExpenses].description);

    printf("Enter the amount: ");
    scanf("%lf", &expenses[*numExpenses].amount);

    displayFriends(friends, numFriends);

    printf("Enter the number of the payer: ");
    int payerIndex;
    scanf("%d", &payerIndex);
    expenses[*numExpenses].payer = &friends[payerIndex - 1];

    printf("Enter the number of the payee: ");
    int payeeIndex;
    scanf("%d", &payeeIndex);
    expenses[*numExpenses].payee = &friends[payeeIndex - 1];

    (*numExpenses)++;
}

void settleBalances(Friend *friends, int numFriends) {
    for (int i = 0; i < numFriends; ++i) {
        for (int j = 0; j < numFriends; ++j) {
            if (i != j) {
                if (friends[i].balance < 0) {
                    double min = friends[i].balance < -friends[j].balance ? friends[i].balance : -friends[j].balance;
                    friends[i].balance += min;
                    friends[j].balance += min;
                    printf("%s pays %.2f to %s\n", friends[i].name, min, friends[j].name);
                }
            }
        }
    }
}

