#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

#define MAX_CONTACTS 100

struct Contact {
    char name[50];
    char phone[15];
};

struct Contact phonebook[MAX_CONTACTS];
int contactCount = 0;


void addContact();
void viewContacts();
void searchContact();
void deleteContact();
void displayMenu();


int main() {
    int choice;

    while (1) {
        displayMenu();
        printf("Enter your choice (1-5): ");
        scanf("%d", &choice);
        

        while(getchar() != '\n'); 

        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                viewContacts();
                break;
            case 3:
                searchContact();
                break;
            case 4:
                deleteContact();
                break;
            case 5:
                printf("\nExiting Phonebook. Goodbye! 👋\n");
                return 0; 
            default:
                printf("\nInvalid choice! Please enter a number between 1 and 5.\n");
        }
        printf("\nPress Enter to continue...");
        getchar(); 
    }

    return 0;
}

void displayMenu() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    printf("=================================\n");
    printf("     PHONEBOOK MANAGEMENT\n");
    printf("=================================\n");
    printf("1. Add Contact\n");
    printf("2. View All Contacts\n");
    printf("3. Search Contact\n");
    printf("4. Delete Contact\n");
    printf("5. Exit\n");
    printf("=================================\n");
}


void addContact() {
    if (contactCount >= MAX_CONTACTS) {
        printf("Phonebook is full! Cannot add more contacts.\n");
        return;
    }

    printf("\n--- Add New Contact ---\n");
    printf("Enter Name: ");
    fgets(phonebook[contactCount].name, sizeof(phonebook[contactCount].name), stdin);
    phonebook[contactCount].name[strcspn(phonebook[contactCount].name, "\n")] = 0; 
    printf("Enter Phone Number: ");
    fgets(phonebook[contactCount].phone, sizeof(phonebook[contactCount].phone), stdin);
    phonebook[contactCount].phone[strcspn(phonebook[contactCount].phone, "\n")] = 0; 
    contactCount++;
    printf("\nContact added successfully!\n");
}


void viewContacts() {
    printf("\n--- All Contacts (%d) ---\n", contactCount);
    if (contactCount == 0) {
        printf("No contacts found.\n");
        return;
    }

    printf("----------------------------------\n");
    printf("%-20s | %-15s\n", "Name", "Phone Number");
    printf("----------------------------------\n");
    for (int i = 0; i < contactCount; i++) {
        printf("%-20s | %-15s\n", phonebook[i].name, phonebook[i].phone);
    }
    printf("----------------------------------\n");
}


void searchContact() {
    char searchName[50];
    int found = 0;

    if (contactCount == 0) {
        printf("\nPhonebook is empty. Nothing to search.\n");
        return;
    }
    
    printf("\nEnter the name to search: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = 0; 

    printf("\n--- Search Results ---\n");
    for (int i = 0; i < contactCount; i++) {
        
        if (strstr(phonebook[i].name, searchName) != NULL) {
            if (!found) {
                 printf("----------------------------------\n");
                 printf("%-20s | %-15s\n", "Name", "Phone Number");
                 printf("----------------------------------\n");
            }
            printf("%-20s | %-15s\n", phonebook[i].name, phonebook[i].phone);
            found = 1;
        }
    }

    if (!found) {
        printf("No contact found with that name.\n");
    } else {
        printf("----------------------------------\n");
    }
}

void deleteContact() {
    char deleteName[50];
    int foundIndex = -1;

    if (contactCount == 0) {
        printf("\nPhonebook is empty. Nothing to delete.\n");
        return;
    }

    printf("\nEnter the exact name of the contact to delete: ");
    fgets(deleteName, sizeof(deleteName), stdin);
    deleteName[strcspn(deleteName, "\n")] = 0; 

    for (int i = 0; i < contactCount; i++) {
        if (strcmp(phonebook[i].name, deleteName) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("Contact not found.\n");
    } else {
        for (int i = foundIndex; i < contactCount - 1; i++) {
            phonebook[i] = phonebook[i + 1];
        }
        contactCount--;
        printf("\nContact deleted successfully!\n");
    }
}