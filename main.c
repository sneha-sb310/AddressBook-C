/*
Name : Sneha Bujurke
Project : Address Book 
Description : This is a address book project where we store the details of the contacts
              We can perform create contact, search contact, edit and delete contact.
              List them all and then save them in a text file.
*/

#include <stdio.h>
#include "contact.h"

int main()
{
    int choice;
    int indexAddr;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do
    {
        printf("\n--------------------\n");
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Save and Exit\n");
        printf("\n--------------------\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        printf("\n--------------------\n");

        switch (choice)
        {
        case 1:
            createContact(&addressBook);
            break;
        case 2:
            searchContact(&addressBook, &indexAddr);
            break;
        case 3:
            editContact(&addressBook);
            break;
        case 4:
            deleteContact(&addressBook);
            break;
        case 5:
            // printf("Select sort criteria:\n");
            // printf("1. Sort by name\n");
            // printf("2. Sort by phone\n");
            // printf("3. Sort by email\n");
            // printf("Enter your choice: ");
            int sortChoice = 0;
            // scanf("%d", &sortChoice);
            listContacts(&addressBook, sortChoice);
            break;
        case 6:
            printf("CONTACTS SAVED\n");
            printf("Exiting...\n");
            saveContactsToFile(&addressBook);
            break;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
