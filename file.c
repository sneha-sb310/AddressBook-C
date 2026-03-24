#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fptr = fopen("contacts.txt", "w");    //open the file in write mode to add the list
    if (fptr == NULL)
    {
        printf("File do not exists\n");
        return;
    }
    fprintf(fptr, "#%d\n", addressBook->contactCount);  //print the number of contacts present in list
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fptr, "%s,%s,%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email); //print all the details of contacts in file
    }
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fptr = fopen("contacts.txt", "r");    //open the file in read mode to read from the list
    if (fptr == NULL)
    {
        printf("File do not exists\n");
        return;
    }
    fscanf(fptr, "#%d\n", &(addressBook->contactCount));    //read the number of contacts present in list
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fscanf(fptr, "%[^,],%[^,],%[^\n]\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);    //read all the details of contacts in file
    }
}
