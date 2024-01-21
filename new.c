#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

struct customer
{
    char name[100];
    int year;
    int month;
    int day;
    int qty;
    struct items
    {
        char nam[20];
        int qt;
        float price;
    } ite[50];
} cus;

void billheader(char name[40], int sal, int mahina, int din)
{
    printf("╭──────────────────────────────────────────╮\n");
    printf("│             DOMO DOMO RESTAURANT         │\n");
    printf("│          Invoice for: %-18s │\n", name);
    printf("│             Date: %04d-%02d-%02d             │\n", sal, mahina, din);
    printf("├──────────────────────────────────────────┤\n");
    printf("│ %-20s %8s %4s       │\n", "Item", "Price", "Qty");
    printf("├──────────────────────────────────────────┤\n");
}

void billbody(char iname[30], float iprice, int iqty)
{
    printf("│ %-20s %8.2f %4d       │\n", iname, iprice, iqty);
}

void billfooter(float total)
{
    printf("├──────────────────────────────────────────┤\n");
    printf("│ %-20s %8s %4s       │\n", "Total", "", "");
    printf("│%37.2f %4s│\n", total, "");
    printf("├──────────────────────────────────────────┤\n");
    printf("│               Thank you!                 │\n");
    printf("╰──────────────────────────────────────────╯\n");
}

void creatinginvoice()
{
    FILE *fp;
    char ch;
    float totalAmount = 0;
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    cus.year = timeinfo->tm_year + 1900;
    cus.month = timeinfo->tm_mon + 1;
    cus.day = timeinfo->tm_mday;

    printf("\n--------------------------------------------");
    printf("\n          Create a New Invoice");
    printf("\n--------------------------------------------\n");
    printf("\nCustomer Name: ");
    scanf("%s", cus.name);

    printf("\nEnter the number of items: ");
    scanf("%d", &cus.qty);

    for (int i = 0; i < cus.qty; i++)
    {
        printf("\nItem %d:", i + 1);
        printf("\n   Name: ");
        scanf(" %s", cus.ite[i].nam);
        printf("   Quantity: ");
        scanf("%d", &cus.ite[i].qt);
        printf("   Price per Item: ");
        scanf("%f", &cus.ite[i].price);
        totalAmount += cus.ite[i].qt * cus.ite[i].price;
    }

    billheader(cus.name, cus.year, cus.month, cus.day);

    for (int i = 0; i < cus.qty; i++)
    {
        billbody(cus.ite[i].nam, cus.ite[i].price, cus.ite[i].qt);
    }

    billfooter(totalAmount);

    printf("\nDo you want to save the invoice? (Y/N): ");
    scanf(" %c", &ch);

    if (ch == 'y' || ch == 'Y')
    {
        fp = fopen("Newrecord.txt", "a");
        if (fp == NULL)
        {
            printf("\nCannot open file");
        }
        else
        {
            fwrite(&cus, sizeof(struct customer), 1, fp);
            printf("\nInvoice saved successfully\n");
            // if (fwrite != 0)
            //     printf("\nInvoice saved successfully\n");
            // else
            //     printf("\nError saving invoice");
            fclose(fp);
        }
    }
}

void search()
{
    FILE *fp;
    char srname[40];
    printf("Enter the name of customer that you want to search: ");
    scanf(" %s", srname);
    // gets(srname);

    fp = fopen("Newrecord.txt", "r");
    if (fp == NULL)
    {
        printf("\nCannot open file\n");
        return;
    }

    while (fread(&cus, sizeof(struct customer), 1, fp))
    {
        float tet = 0;
        if (strcmp(srname, cus.name) == 0)
        {
            printf("Found the following invoice:\n");
            billheader(cus.name, cus.year, cus.month, cus.day);
            for (int i = 0; i < cus.qty; i++)
            {
                billbody(cus.ite[i].nam, cus.ite[i].price, cus.ite[i].qt);
                tet += cus.ite[i].qt * cus.ite[i].price;
            }
            billfooter(tet); // Total not displayed here
        }
        else
        {
            printf("Sorry, No person found named %s\n", srname);
        }
    }
    fclose(fp);
}

void searchall()
{
    FILE *fp;
    fp = fopen("Newrecord.txt", "r");
    if (fp == NULL)
    {
        printf("\nCannot open file\n");
        return;
    }

    while (fread(&cus, sizeof(struct customer), 1, fp))
    {
        float tet = 0; // Reset the total for each invoice
        printf("Found the following invoice:\n");
        billheader(cus.name, cus.year, cus.month, cus.day);
        for (int i = 0; i < cus.qty; i++)
        {
            tet = tet + cus.ite[i].qt * cus.ite[i].price;
            billbody(cus.ite[i].nam, cus.ite[i].price, cus.ite[i].qt);
        }
        billfooter(tet); // Display the total for the current invoice
        printf("\n");    // Add a newline to separate invoices
    }
    fclose(fp);
}

void calculate()
{
    float alltransaction = 0;
    // Initialize the total to 0

    int styear, stmonth, stday, seyear, semonth, seday;
    printf("Entering the starting date:\n\n");
    printf("Enter the first year: ");
    scanf("%d", &styear);
    printf("Enter the first month: ");
    scanf("%d", &stmonth);
    printf("Enter the first day: ");
    scanf("%d", &stday);
    printf("\n\n");
    printf("Enter the ending date:\n\n");
    printf("Enter the second year: ");
    scanf("%d", &seyear);
    printf("Enter the second month: ");
    scanf("%d", &semonth);
    printf("Enter the second day: ");
    scanf("%d", &seday);

    FILE *fp = fopen("Newrecord.txt", "r");
    if (fp == NULL)
    {
        printf("\nCannot open file");
        return;
    }

    while (fread(&cus, sizeof(struct customer), 1, fp))
    {
        if ((cus.year >= styear && cus.year <= seyear) && (cus.month >= stmonth && cus.month <= semonth) && (cus.day >= stday && cus.day <= seday))
        {
            float total = 0;
            printf("Found the following invoice:\n");
            billheader(cus.name, cus.year, cus.month, cus.day);
            for (int i = 0; i < cus.qty; i++)
            {
                billbody(cus.ite[i].nam, cus.ite[i].price, cus.ite[i].qt);
                total += cus.ite[i].price * cus.ite[i].qt; // Calculate the total
            }
            alltransaction += total;
            billfooter(total); // Display the total after processing all items
            printf("\n\n\n");
        }
    }
    printf("\nThe total sale amount between the time interval is %.2f\n", alltransaction);

    fclose(fp);
}

void customexit()
{
    printf("Existing.....");
    exit(0);
}

int main()
{
    char an = 'y';
    int n;

    while (an == 'Y' || an == 'y')
    {
        printf("\n--------------------------------------------");
        printf("\n      Welcome to Domo Domo Restaurant");
        printf("\n--------------------------------------------");
        printf("\n   What would you like to savor today?\n");
        printf("\n   1. Create an Invoice");
        printf("\n   2. Search for a Specific Invoice");
        printf("\n   3. Browse All Invoices");
        printf("\n   4. Calculate Transactions by Date");
        printf("\n   5. Exit");
        printf("\n\n   Enter your choice: ");
        scanf("%d", &n);

        switch (n)
        {
        case 1:
            system("clear");
            creatinginvoice();
            break;
        case 2:
            system("clear");
            search();
            break;
        case 3:
            system("clear");
            searchall();
            break;
        case 4:
            system("clear");
            calculate();
            // Add code to calculate transactions
            break;
        case 5:
            system("clear");
            customexit();
            break;
        default:
            printf("Please enter the correct option\n");
            break;
        }

        printf("Do you want to perform another operation? (Y/N): ");
        scanf(" %c", &an);
    }

    printf("Thank you");
    return 0;
}
