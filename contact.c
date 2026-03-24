#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
int validName(AddressBook *addressBook, char *ptrName) //To check name is valid or not
{
    int i = 0;

    while (ptrName[i] != '\0')
    {
        if (!((ptrName[i] >= 'A' && ptrName[i] <= 'Z') || (ptrName[i] >= 'a' && ptrName[i] <= 'z') || ptrName[i] == ' '))
        {
            printf("Name contains characters other than alphabets \n");
            return 0;
        }
        i++;
    }
    return 1;
}
int validPhoneNum(AddressBook *addressBook, char *ptrPhNo) //To check number is valid or not
{
    int i = 0;
    for (int j = 0; j < addressBook->contactCount; j++)
    {
        if (!(strcmp(addressBook->contacts[j].phone, ptrPhNo)))
        {
            printf("Number already exists\n");
            return 0;
        }
    }
    while (ptrPhNo[i] != '\0')
    {
        if (!(ptrPhNo[i] >= '0' && ptrPhNo[i] <= '9'))
        {
            printf("Numbers contains characters other than numbers \n");
            return 0;
        }
        i++;
    }
    if (i == 10)
    {
        return 1;
    }
    else
    {
        printf("Numbers has less than 10 digits\n");
        return 0;
    }
}
int validEmail(AddressBook *addressBook, char *ptrEmail) //To check mail is valid or not
{
    int i = 0;
    char strCom[] = ".com";
    int comFlag = 0;
    int atFlag = 0;
    int atChFlag = 0;
    int dotFlag = 0;
    for (int j = 0; j < addressBook->contactCount; j++)
    {
        if (!(strcmp(addressBook->contacts[j].email, ptrEmail)))
        {
            printf("Email ID already exists\n");
            return 0;
        }
    }
    while (ptrEmail[i] != '\0')
    {
        if (!((ptrEmail[i] >= 'a' && ptrEmail[i] <= 'z') || (ptrEmail[i] >= '0' && ptrEmail[i] <= '9') || ptrEmail[i] == '@' || ptrEmail[i] == '.')) // check if the mail contains other invalid characters 
        {
            printf("Email contains characters other than small letters, numbers, @, and dot\n");
            return 0;
        }
        if (ptrEmail[i] == '@') //to check @ symbol
        {
            atFlag++;
            if (i == 0 || ptrEmail[i + 1] == '\0')
            {
                atChFlag = 1;
                break;
            }
            if (!(((ptrEmail[i + 1] >= 'a' && ptrEmail[i + 1] <= 'z') || (ptrEmail[i + 1] >= '0' && ptrEmail[i + 1] <= '9')) && ((ptrEmail[i - 1] >= 'a' && ptrEmail[i - 1] <= 'z') || (ptrEmail[i - 1] >= '0' && ptrEmail[i - 1] <= '9'))))
            {
                atChFlag = 1;
                break;
            }
        }
        if (ptrEmail[i] == '.') //check dot operator
        {
            dotFlag++;
        }
        int j = 0;
        int k = i;
        while ((ptrEmail[k] == strCom[j]) && strCom[j] != '\0')
        {
            k++;
            j++;
        }
        if (strCom[j] == '\0' && ptrEmail[k] == '\0')
        {
            comFlag = 1;
        }
        i++;
    }
    if (atFlag == 1 && dotFlag == 1 && comFlag == 1)
    {
        return 1;
    }
    else if (atChFlag == 1)
    {
        printf("Email should have one character before and after @\n");
        return 0;
    }
    else if (atFlag > 1)
    {
        printf("Email has more than one '@'\n");
        return 0;
    }
    else if (dotFlag > 1)
    {
        printf("Email has more than one '.'\n");
        return 0;
    }
    else if (comFlag == 0)
    {
        printf(".com should be at last\n");
        return 0;
    }
    else if (atFlag == 0 || dotFlag == 0)
    {
        printf("Email do not have @ or . operator\n");
        return 0;
    }
}
void listContacts(AddressBook *addressBook, int sortCriteria)
{
    // Sort contacts based on the chosen criteria
    int i = 0;
    while (i < addressBook->contactCount) // for listing all the contacts
    {
        printf("%d %s %s %s\n", i, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        i++;
    }
}

void initialize(AddressBook *addressBook)
{

    addressBook->contactCount = 0;
    // populateAddressBook(addressBook);
    loadContactsFromFile(addressBook); //load contacts from contacts.txt
}
void createContact(AddressBook *addressBook)
{
    /* Define the logic to create a Contacts */
    if (addressBook->contactCount >= MAX_CONTACTS) //check whether the number of contacts has reached the maximum buffer
    {
        printf("Reached Maximum number of contacts\n");
        return;
    }
    else
    {
        char strName[50];
        int vName;
        do
        {
            printf("Enter the valid name : ");
            scanf(" %[^\n]s", strName);
            vName = validName(addressBook, strName);    //to validate the name and add create
        } while (vName == 0);
        strcpy(addressBook->contacts[addressBook->contactCount].name, strName);     //copy the user given name to the list

        char strPhNo[20];
        int vPhNo;
        do
        {
            printf("Enter the valid number : ");
            scanf(" %s", strPhNo);
            vPhNo = validPhoneNum(addressBook, strPhNo);    //to validate the number and add create

        } while (vPhNo == 0);
        strcpy(addressBook->contacts[addressBook->contactCount].phone, strPhNo);    //copy the user given number to the list

        char strEmail[50];
        int vEmail;
        do
        {
            printf("Enter the valid email ID : ");
            scanf(" %s", strEmail);
            vEmail = validEmail(addressBook, strEmail);     //to validate the mail and add create
        } while (vEmail == 0);
        strcpy(addressBook->contacts[addressBook->contactCount].email, strEmail);   //copy the user given mail ID to the list

        addressBook->contactCount++;
    }
}

int searchContact(AddressBook *addressBook, int *ptr) // add *ptr = &index head
{
    /* Define the logic for search */
    int option;
    printf("\nSearch contacts menu\n");
    printf("1. Search by name\n");
    printf("2. Search by ph no.\n");
    printf("3. Search by email id\n");
    printf("\n--------------------\n");
    printf("\nEnter the option : ");
    scanf("%d", &option);
    printf("\n--------------------\n");
    switch (option)
    {
    case 1:
        char bName[50];
        printf("Enter the name you want to search : ");
        scanf(" %[^\n]s", bName);
        int i = 0;
        int flagN = 0;
        while (i < addressBook->contactCount)
        {
            if (!(strcasecmp(bName, addressBook->contacts[i].name)))    //to search the name is present or not in the list
            {
                flagN++;    //increase if more than 2 name are present
                *ptr = i;   //store index value into pointer to access in search funtion
                printf("%d %s %s %s\n", i, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            }
            i++;
        }
        if (flagN)
            printf("Contact Found\n");
        else
            printf("Not Found\n");
        return flagN;
        break;

    case 2:
        char bPNo[20];
        printf("Enter the Phone number you want to search : ");
        scanf(" %[^\n]s", bPNo);
        int j = 0;
        int flagPN = 0;
        while (j < addressBook->contactCount)
        {
            if (!(strcmp(bPNo, addressBook->contacts[j].phone)))     //to search the phone no is present or not in the list
            {
                flagPN++;
                *ptr = j;
                printf("%d %s %s %s\n", j, addressBook->contacts[j].name, addressBook->contacts[j].phone, addressBook->contacts[j].email);
            }
            j++;
        }
        if (flagPN)
            printf("Contact Found\n");
        else
            printf("Not Found\n");
        return flagPN;
        break;

    case 3:
        char bEmail[50];
        printf("Enter the mail id you want to search : ");
        scanf(" %[^\n]s", bEmail);
        int k = 0;
        int flagE = 0;
        while (k < addressBook->contactCount)
        {
            if (!(strcmp(bEmail, addressBook->contacts[k].email)))      //to search the email is present or not in the list
            {
                flagE++;
                *ptr = k;
                printf("%d %s %s %s\n", k, addressBook->contacts[k].name, addressBook->contacts[k].phone, addressBook->contacts[k].email);
            }
            k++;
        }
        if (flagE)
            printf("Contact Found\n");
        else
            printf("Not Found\n");
        return flagE;
        break;

    default:
        printf("Invalid option entered\n");
        return 0;
        break;
    }
}

void editContact(AddressBook *addressBook)
{
    /* Define the logic for Editcontact */
    int index = 0;
    int res = searchContact(addressBook, &index);
    if (res == 0)
        return;
    if (res > 1)
    {
        printf("Enter which index you want to edit : ");
        scanf("%d", &index);
    }

    int Eoption;
    // printf("\n--------------------\n");
    printf("\nEdit contacts menu\n");
    printf("1. Edit name\n");
    printf("2. Edit ph no.\n");
    printf("3. Edit email id\n");
    printf("\n--------------------\n");
    printf("\nEnter the option : ");
    scanf("%d", &Eoption);
    printf("\n--------------------\n");
    switch (Eoption)
    {
    case 1:
        char strName[50];
        int vName;
        do
        {
            printf("Enter the valid name : ");
            scanf(" %[^\n]s", strName);
            vName = validName(addressBook, strName);    //to check the valid name or not

        } while (vName == 0);
        strcpy(addressBook->contacts[index].name, strName);     //edit name to the user given name
        printf("Name Edited Successfully\n");
        break;
    case 2:
        char strPhNo[20];
        int vPhNo;
        do
        {
            printf("Enter the valid number : ");
            scanf(" %s", strPhNo);
            vPhNo = validPhoneNum(addressBook, strPhNo);    //to check the valid phone num or not

        } while (vPhNo == 0);
        strcpy(addressBook->contacts[index].phone, strPhNo);    //edit phone num to the user given name
        printf("Number Edited Successfully\n");
        break;
    case 3:
        char strEmail[50];
        int vEmail;
        do
        {
            printf("Enter the valid email ID : ");
            scanf(" %s", strEmail);
            vEmail = validEmail(addressBook, strEmail);     //to check the valid email ID or not
        } while (vEmail == 0);
        strcpy(addressBook->contacts[index].email, strEmail);   //edit email ID to the user given name
        printf("Mail Edited Successfully\n");
        break;

    default:
        printf("Invalid Option\n");
        return ;
        break;
    }
}

void deleteContact(AddressBook *addressBook)
{
    /* Define the logic for deletecontact */
    int index = 0;

    int res = searchContact(addressBook, &index);
    if (res == 0)
        return;
    if (res > 1)
    {
        printf("Enter which index you want to delete : ");
        scanf("%d", &index);
    }

    printf("Deleted contact : ");
    printf("%s %s %s\n", addressBook->contacts[index].name, addressBook->contacts[index].phone, addressBook->contacts[index].email);
    for (int i = index; i < addressBook->contactCount; i++)     //shift the contacts from index to total contacts
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }
    addressBook->contactCount--;    //after deleting reduce the contact count
}
