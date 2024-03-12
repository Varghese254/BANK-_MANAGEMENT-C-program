#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

struct customer {
    char fname[50];
    char lname[50];
    int phone_no;
    int adhar_no;
    int password;
    char user_name[50];
    int balance;
    int transaction;
    struct customer *next; // Pointer to the next customer node
};

// Function prototypes
void check_bal(struct customer *current_customer);
void menu(struct customer *current_customer);
void transfer_money(struct customer *current_customer);
void display(struct customer *customers);
void login(struct customer **head); // Updated function prototype

struct customer *head = NULL; // Pointer to the head of the linked list

void add_customer() {
    struct customer *new_customer = (struct customer *)malloc(sizeof(struct customer));
    if (new_customer == NULL) {
        printf("Memory allocation failed. Exiting...\n");
        exit(1);
    }

    printf("Add the Customer Details\n");
    printf("-------------------------\n");
    printf("Enter the first name of customer: ");
    scanf("%s", new_customer->fname);
    printf("Enter the last name: ");
    scanf("%s", new_customer->lname);
    printf("Enter the phone Number: ");
    scanf("%d", &new_customer->phone_no);
    printf("Enter the adhar_no: ");
    scanf("%d", &new_customer->adhar_no);
    printf("Enter the user_name: ");
    scanf("%s", new_customer->user_name);
    printf("Enter the password: ");
    scanf("%d", &new_customer->password);
    printf("Enter initial deposit: ");
    scanf("%d", &new_customer->balance);

    new_customer->transaction = 0;
    new_customer->next = NULL;

    if (head == NULL) {
        head = new_customer;
    } else {
        struct customer *current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_customer;
    }
}

void check_bal(struct customer *current_customer) {
    int amt;
    int n;
    printf("Balance=%d\n", current_customer->balance);
    printf("Do you want to deposit: 1/0\n");
    scanf("%d", &n);
    if (n == 1) {
        printf("Enter the amount:\n");
        scanf("%d", &amt);
        current_customer->balance += amt;
        printf("Balance=%d\n", current_customer->balance);
    }
    menu(current_customer);
}

void transfer_money(struct customer *current_customer) {
    char user[50];
    int amt;
    printf("Enter the username to transfer the money:\n");
    scanf("%s", user);
    printf("Enter the amount to be transferred: ");
    scanf("%d", &amt);

    struct customer *recipient = head;
    while (recipient != NULL && strcmp(recipient->user_name, user) != 0) {
        recipient = recipient->next;
    }

    if (recipient == NULL) {
        printf("Recipient not found. Transaction canceled.\n");
    } else if (current_customer == recipient) {
        printf("You can't transfer money to yourself. Transaction canceled.\n");
    } else if (current_customer->balance < amt) {
        printf("Insufficient balance. Transaction canceled.\n");
    } else {
        current_customer->balance -= amt;
        recipient->balance += amt;
        printf("Transferring money...");
        sleep(2); // Sleep for 2 seconds to simulate the transfer
        printf("Transaction Completed!\n");
    }
    menu(current_customer);
}

void menu(struct customer *current_customer) {
    int ch;
    printf(" HOME ");
    printf("******\n");
    printf(" 1....CHECK BALANCE\n");
    printf(" 2...TRANSFER MONEY\n");
    printf(" 3...LOGOUT\n");
    printf(" 4...MAIN MENU\n"); // Option to go back to the main menu
    printf(" ENTER YOUR CHOICE: ");
    scanf("%d", &ch);
    switch (ch) {
        case 1:
            check_bal(current_customer);
            break;
        case 2:
            transfer_money(current_customer);
            break;
        case 3:
            printf("Logging out...\n");
            return;
        case 4:
            return;
        default:
            printf("Invalid choice\n");
            break;
    }
}

void display_customer(struct customer *customer) {
    printf("Customer Details:\n");
    printf("-----------------\n");
    printf("Name: %s %s\n", customer->fname, customer->lname);
    printf("Phone Number: %d\n", customer->phone_no);
    printf("Adhar Number: %d\n", customer->adhar_no);
    printf("Username: %s\n", customer->user_name);
    printf("Balance: %d\n", customer->balance);
    printf("-----------------\n");
}

void display(struct customer *customers) {
    struct customer *current = customers;
    while (current != NULL) {
        display_customer(current);
        current = current->next;
    }
}

void login(struct customer **head) { // Updated function definition
    char user[50];
    int pass;
    printf("Enter the user_name: ");
    scanf("%s", user);
    printf("Enter the password: ");
    scanf("%d", &pass);

    struct customer *current = *head;
    while (current != NULL) {
        if (strcmp(current->user_name, user) == 0 && current->password == pass) {
            printf("Login successful for %s %s...\n", current->fname, current->lname);
            menu(current);
            return;
        }
        current = current->next;
    }

    printf("Login failed...\n");
}

int main() {
    int choice;
    while (1) {
        printf("Tasks:\n");
        printf("1. Add customer details\n");
        printf("2. Login\n");
        printf("3. Display All Customers\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                add_customer();
                break;
            case 2:
                login(&head); // Pass a pointer to the head
                break;
            case 3:
                display(head);
                break;
            case 4:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice\n");
                break;
        }
    }
    return 0;
}

