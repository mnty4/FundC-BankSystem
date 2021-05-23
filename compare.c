/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 3
 * Group Members:
 *
 * Name: Thomas Good
 * Student ID: 13291455
 *
 * Name: Reece Wallace
 * Student ID: 13192505
 *
 * Name: Jeremy Hoy
 * Student ID: 13590942
 *
 * Name: Lukas Gaspar
 * Student ID: 13910676
 *
 * Name: Carter Pisani
 * Student ID: 13536115
 *
 * Date of submission: - 
 
*******************************************************************************/

/*******************************************************************************
 * List header files
*******************************************************************************/
/*to do list functions used*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <sys/stat.h>
#include <time.h>

/* gcc -Wall -Werror -ansi -o main.out main.c -lm */

/*******************************************************************************
 * List preprocessing directives
*******************************************************************************/

#define MAX_SELECTION_LEN 20
#define MAX_TRANSACTION_NAME 20
#define MAX_TRANSACTION_SIZE 100
#define MAX_NAME_SIZE 25
#define MAX_ACCOUNT_NAME_SIZE 15
#define MAX_ACCOUNT_SIZE 5
#define MAX_STATE_NAME_SIZE 20
#define MAX_STREET_NAME_SIZE 20
#define MAX_SUBURB_NAME_SIZE 30
#define MIN_EMAIL_LEN 5
#define MAX_EMAIL_LEN 20
#define MAX_POSTCODE_LEN 5
#define MAX_CLIENT_ID_LEN 5
#define MAX_PHONE_NUM_LEN 10
#define MAX_USERNAME_LEN 20
#define MIN_PASSWORD_LEN 3
#define MAX_PASSWORD_LEN 20
#define BUFFER_SIZE 1000


/*******************************************************************************
 * List structs
*******************************************************************************/

/* Date struct */
struct date { 
	int day, month, year;

};
typedef struct date date_t;

/*transaction struct*/
struct transaction {
	char name[MAX_NAME_SIZE];
	int amount;
};
typedef struct transaction transaction_t;

/* Account struct */
struct account {
    int accNumber;
    char accName[MAX_ACCOUNT_NAME_SIZE];
	transaction_t transactionList[MAX_TRANSACTION_SIZE];
	unsigned int numTransactions;
};
typedef struct account account_t;

/* Manager struct */
struct manager {
    char name[MAX_NAME_SIZE];
};
typedef struct manager manager_t;

/* Customer struct */
struct customer {
    char name[MAX_NAME_SIZE];
	char postCode[MAX_POSTCODE_LEN];
	char phone[MAX_PHONE_NUM_LEN];
	char* clientId[MAX_CLIENT_ID_LEN];
	char email[MAX_EMAIL_LEN];
    account_t accountList [MAX_ACCOUNT_SIZE];
    date_t birthday;
	unsigned int customerBalance;
	unsigned int numAccounts;
};
typedef struct customer customer_t;

/*******************************************************************************
 * Function prototypes
*******************************************************************************/

/* Manager functions */
void printManagerMenu(void);        			/* Author: Thomas Good - DONE */
customer_t createCustomer(void);          		
	/* Author: Thomas Good, Carter Pisani - DONE*/
void createDirectory(customer_t cust);			/* Author: Thomas Good - DONE */
void deleteDirectory(customer_t cust);			/* Author: Thomas Good - DONE */
void removeFromDatabase(customer_t cust);		/* Author: Thomas Good - DONE */
void deleteLine(FILE *srcFile, FILE *tempFile, const int line); 
	/* Author: Thomas Good - DONE */
char* generateId(void);							/* Author: Thomas Good - DONE */
void deleteCustomer(customer_t cust);       	/* Author: Thomas Good - DONE*/
void saveCustomer(customer_t customer);         /* Author: Thomas Good - DONE */
/* void selectCustomer(); 						   Author: Lukas Gaspar */
void displayCustomer(customer_t customer);      /* Author: Lukas Gaspar - DONE */
void changeCustomerDetails(customer_t *customerp); /* Author: Lukas Gaspar */
int readManagerAnswer(void);        	/* Author: Thomas Good - Kinda DONE */
void invalidManagerChoice(void);    			/* Author: Thomas Good - DONE */

/* Customer functions */
void printCustomerMenu(void);       		/* Author: Thomas Good - DONE */

/* Author: Reece Wallace*/
void addAccount(customer_t *customer); 		/* Author: Reece Wallace - DONE */
unsigned long generateAccountNum(customer_t *customer); 
	/* Author: Reece Wallace - DONE */
void displayAccounts(customer_t *customer); 
	/* Author: Reece Wallace, Jeremy Hoy - DONE */
void displayAccount(account_t *account); 	/* Author: Reece Wallace - DONE */
void deposit(customer_t *customer, account_t *account); 
	/* Author: Reece Wallace, Carter Pisani - DONE */
void withdraw(customer_t *customer, account_t *account); 
	/* Author: Reece Wallace, Carter Pisani - DONE */
void transfer(customer_t *customer); /* Author: Reece Wallace - DONE*/
int readCustomerAnswer(customer_t *customer);   /* Author: Thomas Good - kinda DONE */
void invalidCustomerChoice(customer_t *customer); /* Author: Thomas Good - DONE */

int calcBalance(account_t *account); /* Author: Reece Wallace - DONE */
void printTransaction(transaction_t *transaction, int count); 	

/* Shared */
void printMenu(void);               	/* Author: Thomas Good - DONE */
int login(void);                  	/* Author: Lukas Gaspar - DONE */
char *fgets_wrapper(char *buffer, size_t buflen, FILE *fp); /* Author: Lukas Gaspar - DONE */
void changePassword(void);          	/* Author: Lukas Gaspar - shouldnt password be customer struct variable? */

void searchTransactions(customer_t *customer); 	
	/* Author: Reece Wallace, Carter Pisani */
account_t* accountSelect
	(char* prompt, customer_t *customer); /* Author: Reece Wallace - DONE*/
void printSortedTransactions
	(account_t * account); /* Author: Reece Wallace - DONE */
transaction_t transferWithdraw
	(char transName[MAX_ACCOUNT_NAME_SIZE], int transAmount); 
	/* Author: Reece Wallace - DONE */
transaction_t transferDeposit
	(char transName[MAX_ACCOUNT_NAME_SIZE], int transAmount); 
	/* Author: Reece Wallace - DONE */
void sortTransactions(transaction_t* list, unsigned int numTransactions); 
	/* Author: Reece Wallace - DONE */
void searchByName(customer_t *customer);  /* Author: Reece Wallace */
int authenticate(char email[MAX_EMAIL_LEN], char password[MAX_PASSWORD_LEN]);	 /* Author: Lukas Gaspar */
/*int logout;*/							/* Author: Jeremy Hoy - */


int main(void) {
	printMenu();
	printManagerMenu();
	readManagerAnswer();
    return 0;
}

/*******************************************************************************
 * This function prints the initial message when the user starts the program 
 * on how to use this program.
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/
void printMenu(void){
	
    for(;;){
    printf("\n\n"
    	"-----Welcome to EZY Banking System 1.0-----\n"
        "Please enter your login details to proceed\n"
        "-------------------------------------------\n");
		
		int status = login();
		if(status == -1)
		continue;
		if(status == 0)
		return;
		if(status == 1) {
		printf("congratulations you are a customer!");
		return;
		}
		if(status == 2) {
		printf("congratulations you are a manager!");
		return;
		}
	}
		/* readCustomerAnswer(&customer); */
	/*authenticate();*/
}

/*******************************************************************************
 * This function authenticates the user
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/
int authenticate(char email[MAX_EMAIL_LEN], char password[MAX_PASSWORD_LEN]){
	return 1;
}
/*******************************************************************************
 * This function logs in the user
 * inputs:
 * - none
 * outputs:
 * - int used to return the user's login status (0 - no authorisation, 1 - customer, 2 - manager)
*******************************************************************************/
int login(void) {
	char selection[BUFFER_SIZE];
	char email[MAX_EMAIL_LEN];
	char password[MAX_PASSWORD_LEN];

	for(;;) {
		for(;;) {
			printf("select an option:\n"
					"login\n"
					"close\n\n"
					"choice: ");
			if(fgets_wrapper(selection, BUFFER_SIZE, stdin) != 0){
				printf("%s", selection);
				if(strcmp(selection, "close") == 0)
					return 0;
				if(strcmp(selection, "login") != 0) {
					printf("invalid selection\n");
					return -1;
				}
				break;
			}
		}


		for(;;) {
			printf("\nEnter \"back\" at any time to go back to the menu\n");
			printf("Enter email> ");
			if(fgets_wrapper(selection, BUFFER_SIZE, stdin) != 0) {
				if(strcmp(selection, "back") == 0)
					return -1;
				if(strlen(selection) > MAX_EMAIL_LEN || strlen(selection) < MIN_EMAIL_LEN) {
					printf("invalid email length");
					continue;
				}
				strcpy(email, selection);
				break;
			}
		}

		for(;;) {
			printf("\nEnter \"back\" at any time to go back to the menu\n");
			printf("Enter password> ");
			if(fgets_wrapper(selection, BUFFER_SIZE, stdin) != 0) {
				if(strcmp(selection, "back") == 0)
					return -1;
				if(strlen(selection) > MAX_PASSWORD_LEN || strlen(selection) < MIN_PASSWORD_LEN) {
					printf("invalid password length");
					continue;
				}
				strcpy(password, selection);
				break;
			}
		}

		if(authenticate(&email[MAX_EMAIL_LEN], &password[MAX_PASSWORD_LEN]) == 0) {
			printf("incorrect email or password");
			return -1;
		}
		if(authenticate(&email[MAX_EMAIL_LEN], &password[MAX_PASSWORD_LEN]) == 1) {
			return 1; /*Authenticated as customer. */
		}
		if(authenticate(&email[MAX_EMAIL_LEN], &password[MAX_PASSWORD_LEN]) == 2) {
			return 2; /*Authenticated as manager. */
		}
		printf("unknown authentication return value");
		return 0;
	}
}

/*******************************************************************************
 * This function is a wrapper for fgets that removes the new line character and eats any extra chars
 * inputs:
 * - buffer: pointer to an array of chars where we store the string
 * - buflen: max amount of chars read in
 * - fp: file pointer
 * outputs:
 * - the pointer to an array, either returns empty string or the modified buffer
*******************************************************************************/

char *fgets_wrapper(char *buffer, size_t buflen, FILE *fp)
{
    if (fgets(buffer, buflen, fp) != 0)
    {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n')
            buffer[len-1] = '\0';
        else
        {
             int ch; 
             while ((ch = getc(fp)) != EOF && ch != '\n') /* eats chars */
                ;
        }
        return buffer;
    }
    return 0;
}
/*******************************************************************************
 * This function generates the customerId when created
 * inputs:
 * - none
 * outputs:
 * - char *
*******************************************************************************/
char* generateId(void){
	int a;
    srand ( time(NULL) );
    a = 1000+(rand()%9000);
	char* id = malloc(5);
	sprintf(id, "%04d", a);
  	return id;
} 
/*******************************************************************************
 * This function logs the user out to the main login menu
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/
/*void logout(void){
	login();
	
}
*/
/*******************************************************************************
 * This function reads the managers input and executes the appropriate function
 * inputs:
 * - none
 * outputs:
 * - int
*******************************************************************************/
/*void changePassword(customer_t *customerp) {
	char passwordCheck[100];
	printf("Enter current password");
	scanf("%100[^\n]", passwordCheck);
	if(passwordCheck == customerp->password) {
		for(;;) {
			printf("Enter new password");
			scanf("%100[^\n]", passwordCheck);

			if(passwordCheck < MIN_PASSWORD_LEN || passwordCheck > MAX_PASSWORD_LEN) {
				printf("invalid character length");
				continue;
			}
			strcpy(customerp->password, passwordCheck);
		}
	}
}*/
/*******************************************************************************
 * This function reads the managers input and executes the appropriate function
 * inputs:
 * - none
 * outputs:
 * - int
*******************************************************************************/
int readManagerAnswer(void){
	char answer;
 	answer = getchar();
	if (answer == '\n') {
		invalidManagerChoice();
	} else {
		getchar();	/* Collects the '\n' character after entering answer */
		if (answer == '-') {
			getchar();
			getchar();
			invalidManagerChoice();
		}
		else if (answer == '1') {
			/* Create customer */
			customer_t cust = createCustomer();
    		saveCustomer(cust);
			createDirectory(cust);

		} else if (answer == '2') {
			/* Delete customer - TODO: Select customer to delete ?*/
			
		} else if (answer == '3') {
			/* Display customer - TODO: Select customer to display ?*/
			
		} else if (answer == '4') {
			/* Search customer transactions */
		} else if (answer == '5') {
			/* Update customer details */
		} else if (answer == '6') {
				printMenu();
				
			/* Log out */
		} else {
			invalidManagerChoice();
		}
	}
	return 0;
}

/*******************************************************************************
 * This function reads the customers input and executes the appropriate function
 * inputs:
 * - none
 * outputs:
 * - int
*******************************************************************************/
int readCustomerAnswer(customer_t *customer){
	char answer;
 	answer = getchar();
	if (answer == '\n') {
		invalidCustomerChoice(customer);
	} else {
		getchar();	/* Collects the '\n' character after entering answer */
		if (answer == '-') {
			getchar();
			getchar();
			invalidCustomerChoice(customer);
		}
		else if (answer == '1') {
			unsigned int i;
			char choice[MAX_ACCOUNT_NAME_SIZE];
			displayAccounts(customer);

			printf("select an account\n");
			scanf("%s", choice);
			for(i=0; i<customer->numAccounts; i++){
				if(strcmp(choice, customer->accountList[i].accName) == 0){
					deposit(customer, &customer->accountList[i]);
				}
			}
			/* Make deposit */
		} else if (answer == '2') {
			unsigned int i;
			char choice[MAX_ACCOUNT_NAME_SIZE];
			displayAccounts(customer);

			printf("select an account");
			scanf("%s", choice);
			for(i=0; i<customer->numAccounts; i++){
				if(strcmp(choice, customer->accountList[i].accName) == 0){
					withdraw(customer, &customer->accountList[i]);
				}
			}
			/* Withdraw */
		} else if (answer == '3') {
			/* Transfer */
			transfer(customer);
			printCustomerMenu();
			readCustomerAnswer(customer);
		} else if (answer == '4') {
			addAccount(customer);
			printCustomerMenu();
			readCustomerAnswer(customer);
			/* Create account */
		} else if (answer == '5') {
			searchTransactions(customer);
			searchByName(customer);
			printCustomerMenu();
			readCustomerAnswer(customer);
			/* Search customer transactions */
		} else if (answer == '6') {
			displayAccounts(customer);
			printCustomerMenu();
			readCustomerAnswer(customer);
			/* Display your information */
		} else if (answer == '7') {
			/* Change password */
		} else if (answer == '6') {
			
			/* Log out */
		} else {
			invalidCustomerChoice(customer);
		}
	}
	return 0;
}

/*******************************************************************************
 * This function prints the initial menu for the manager with all instructions 
 * on how to use this program.
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/
void printManagerMenu(void){
    printf("\n\n"
    	"1. Create customer\n"
    	"2. Delete customer\n"
    	"3. Display customer\n"
        "4. Search customer transactions\n"
        "5. Update customer details\n"
    	"6. Log out\n"
		"Enter your choice>\n");
}

/*******************************************************************************
 * This function prints the initial menu for the customer with all instructions 
 * on how to use this program.
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/
void printCustomerMenu(void){
    printf("\n\n"
    	"1. Make deposit\n"
    	"2. Withdraw\n"
    	"3. Transfer\n"
    	"4. Create account\n"
        "5. Search transactions\n"
        "6. Display your information\n"
        "7. Change password\n"
        "8. Log out\n"
		"Enter your choice>");
}

/*******************************************************************************
 * This function allows a manager to create a customer
 * inputs:
 * - none
 * outputs:
 * - cutsomer_t
*******************************************************************************/
customer_t createCustomer(void){
	int check = 0;
	int val;
	customer_t customer;
	date_t birthday;
	char tempDay[20];
	char tempMonth[20];
	char tempYear[20];	
	int b =0;
	
					/**************************** Name ****************************/

	printf("\nEnter Name: ");
	scanf("%100[^\n]", customer.name);
	getchar();
	

					/**************************** Phone number ****************************/
	while (check == 0) {
		printf("\nEnter Phone Number: ");
		scanf("%11[^\n]", customer.phone);
		getchar();
		val = atoi(customer.phone);
			int i, flag=2;
			for(i=0;i<strlen(customer.phone);i++){
			if(customer.phone[i]<48 || customer.phone[i]>57){
			flag=1;}}
			if(flag!=1){
				b=1;}
			else {
				b=0;
				} 
	if(val == 0 || b == 0){
			printf("\nPhone Numbers MUST contain only numbers.");
	} else{

		int i, count = 0;
    	for (i = 0; customer.phone[i] != '\0'; ++i){
			count++;
		}
		if (i != 10) {
			printf("\nPhone Number MUST be 10 digits in length");
		} else {
			check = 1;
			printf("\n\n");
		}
	}
	}
	check = 0;
	
					/**************************** Post Code ****************************/
	while (check == 0) {
		printf("\nEnter Post Code: ");
		scanf("%5[^\n]", customer.postCode);
		getchar();
		val = atoi(customer.postCode);
		int i, flag=2;
			for(i=0;i<strlen(customer.postCode);i++){
			if(customer.postCode[i]<48 || customer.postCode[i]>57){
			flag=1;}}
			if(flag!=1){
				b=1;}
			else b=0;
	if(val == 0 || b == 0){
			printf("\nPost Code MUST contain only numbers.");
	} else{

		int i, count = 0;
    	for (i = 0; customer.postCode[i] != '\0'; ++i){
			count++;
		}
		if (i != 4) {
			printf("\nPost Code MUST be 4 digits in length");
		} else {
			check = 1;
			printf("\n\n");
		}
	}
}
	check = 0;


					/**************************** Email Adress ****************************/
	printf("\nEnter Email Address: ");
	scanf("%20[^\n]", customer.email);
	getchar();


					/**************************** Birthday Day ****************************/
	while(check == 0) {
		printf("\nEnter Birthday (Day): ");
		scanf("%s", &tempDay[0]);
		/* Checks if given value is int */
		val = atoi(tempDay);
			int i, flag=2;
			for(i=0;i<strlen(tempDay);i++){
			if(tempDay[i]<48 || tempDay[i]>57){
			flag=1;}}
			if(flag!=1){
				b=1;}
			else b=0;
	if(val == 0 || b == 0){
			printf("\nBirthday (Day) MUST contain only numbers.");
		} else {
			if (val >= 1 && val <= 31) {
				birthday.day = val;
				check = 1; 
				printf("\n\n");
			} else printf("\nInvalid Day."); 
		}
	}
	check = 0;
	
					/**************************** Birthday Month ****************************/
	while(check == 0) {
		printf("\nEnter Birthday (Month): ");
		scanf("%s", &tempMonth[0]);
		/* Checks if given value is int */
		val = atoi(tempMonth);
			int i, flag=2;
			for(i=0;i<strlen(tempMonth);i++){
			if(tempMonth[i]<48 || tempMonth[i]>57){
			flag=1;}}
			if(flag!=1){
				b=1;}
			else b=0;
	if(val == 0 || b == 0){
			printf("\nBirthday (Month) MUST contain only numbers. ");
		} else {
			if (val >= 1 && val <= 12) {
				birthday.month = val;
				check = 1; 
				printf("\n\n");
			} else printf("\nInvalid Month."); 
		}
	}
	/* Resets check */
	check = 0;
	
					/**************************** Birthday Year ****************************/
	while(check == 0) {
		printf("\nEnter Birthday (Year): \n");
		scanf("%s", &tempYear[0]);
		/* Checks if given value is int */
		val = atoi(tempYear);
		int i, flag=2;
			for(i=0;i<strlen(tempYear);i++){
			if(tempYear[i]<48 || tempYear[i]>57){
			flag=1;}}
			if(flag!=1){
				b=1;}
			else b=0;	
	if(val == 0 || b == 0){
			printf("\nBirthday (Month) MUST contain only numbers. ");
		} else {
			if (val >= 1800 && val <= 2017) {
				birthday.year = val;
				check = 1; 
				printf("\n\n");
			} else printf("Invalid year. "); 
		}
	}
	/* Resets check */
	check = 0;
	getchar();
	customer.birthday = birthday;
	customer.clientId[0] = generateId();
	customer.customerBalance = 0;
	customer.numAccounts = 0;
	return customer;
}

/*******************************************************************************
 * This function initialises the customer directory with savings account
 * inputs:
 * - cutsomer_t
 * outputs:
 * - none
*******************************************************************************/
void createDirectory(customer_t cust) {
	int check = mkdir(*cust.clientId);
	long number = 10000001 + (rand() % 1000);
	char* accNumber = malloc(9);
	sprintf(accNumber, "%ld", number);

	/*char* accNumber = "10000001";*/

    /* check if directory is created or not */
    if (!check) {
		FILE *fp;
		/* Create accounts file */

		char *accountPath = (char *)malloc(20);
		strcpy(accountPath, *cust.clientId);
		strcat(accountPath, "/accounts");

		printf("%s", accountPath);

		fp = fopen(accountPath, "w");
		fprintf(fp, "%s Savings 5\n", accNumber);	
		fclose (fp);

		/* Create transaction file */

		char *transactionPath = (char *)malloc(20);
		strcpy(transactionPath, *cust.clientId);
		strcat(transactionPath, "/transactions");
	
		fp = fopen(transactionPath, "w");


		fprintf(fp, "%s Opening deposit 5\n", accNumber); 
		fclose (fp);

		/* *************************** TODO: *************************** */
		/* Password input for folder encryption */
		/* Create customer data file with data similar to database file to read off when customer logs in */
		/* ************************************************************* */

		printf("Customer directory created\n");
	} else {
        printf("Error: Unable to create customer directory\n");
    }
}

/*******************************************************************************
 * This function deletes the customer from the database & directory
 * inputs:
 * - none
 * outputs:
 * - cutsomer_t
*******************************************************************************/
void deleteCustomer(customer_t cust) {
	int check = 0;
	int yResult;
	int nResult;
	char* answer = malloc(1);
	printf("Are you sure you want to delete this customer? Y/N> ");
	while(check == 0) {
		scanf("%s", answer);
		char* yes = "Y";
		char* no = "N";
		yResult = strcmp(answer, yes);
		nResult = strcmp(answer, no);	
		if (yResult == 0){

			removeFromDatabase(cust);
			deleteDirectory(cust);

			printf("Customer Deleted\n");
			check = 1;
		} else if (nResult == 0){
			printf("Customer Not Deleted\n");
			check = 1;
		} else {
			printf("Invalid answer. Please enter 'Y' or 'N'>");
		}
	}
}

/*******************************************************************************
 * This function deletes the customers directory
 * inputs:
 * - none
 * outputs:
 * - cutsomer_t
*******************************************************************************/
void deleteDirectory(customer_t cust) {
	int dataStatus, accStatus, tranStatus, dirStatus;

	char *accountPath = (char *)malloc(20);
	strcpy(accountPath, *cust.clientId);
	strcat(accountPath, "/accounts");

	char *transactionPath = (char *)malloc(20);
	strcpy(transactionPath, *cust.clientId);
	strcat(transactionPath, "/transactions");

	char *dataPath = (char *)malloc(20);
	strcpy(dataPath, *cust.clientId);
	strcat(dataPath, "/data");

	dataStatus = remove(dataPath);

	if (dataStatus == 0) {
		accStatus = remove(accountPath);
		if (accStatus == 0) {
			tranStatus = remove(transactionPath);
			if (tranStatus == 0) {
				dirStatus = remove(*cust.clientId);
				if (dirStatus == 0) {
				} else
				{
					perror("Following error occurred");
				}
			} else
			{
				perror("Following error occurred");
			}
		} else
		{
			perror("Following error occurred");
		}
	} else
	{
		perror("Following error occurred");
	}
	
}

/*******************************************************************************
 * This function removes customer from database file
 * inputs:
 * - cutsomer_t
 * outputs:
 * - none
*******************************************************************************/
void removeFromDatabase(customer_t cust){
	char string[200];
	int line_number = 1;
	int line_to_delete;
	FILE* fp = NULL;
	FILE* tempFile = NULL;
    fp = fopen("database", "r");
	if(fp == NULL) {
        printf("Read error\n");
    } else {
		while (fgets(string, sizeof string, fp)) {
			if (strstr(string, cust.clientId[0])) {
				line_to_delete = line_number;
            	printf("line number is: %d\n", line_number);
        	}	
			if (strchr(string, '\n')) {
				line_number += 1;
			}
    	}
		tempFile = fopen("temp", "w");
		rewind(fp);
		deleteLine(fp, tempFile, line_to_delete);
		fclose(fp);
    	fclose(tempFile);
		remove("database");
    	rename("temp", "database");
	}
}

/*******************************************************************************
 * This function deletes the line in the database file in which 
 * the desired customer occurs.
 * inputs:
 * - FILE *srcFile, FILE *tempFile, const int line
 * outputs:
 * - none
*******************************************************************************/
void deleteLine(FILE *srcFile, FILE *tempFile, const int line) {
    char buffer[BUFFER_SIZE];
    int count = 1;
    while ((fgets(buffer, BUFFER_SIZE, srcFile)) != NULL)
    {
        if (line != count) {
            fputs(buffer, tempFile);
		}
        count++;
    }
}

/*******************************************************************************
 * This function allows a manager to save the customer to the database
 * inputs:
 * - customer_t
 * outputs:
 * - none
*******************************************************************************/
void saveCustomer(customer_t cust) {
	FILE *fp;
	int result;
	char* str = "0001";
	result = strcmp(*cust.clientId, str);
	if(result == 0) {
		fp = fopen("database", "w");
	} else {
		fp = fopen("database", "a");
	}
	fprintf(fp, "%s %s %d %d %d %s %s %s %d %d\n",
	cust.clientId[0], 
	cust.name, 
	cust.birthday.day, 
	cust.birthday.month, 
	cust.birthday.year,
	cust.email,
	cust.phone,
	cust.postCode,
	cust.customerBalance,
	cust.numAccounts);
	fclose (fp);
}
/*******************************************************************************
 * This function allows a manager to change a customer's details
 * inputs:
 * - customer_t
 * outputs:
 * - none
*******************************************************************************/
/*void changeCustomerDetails(customer_t *customerp) {
	char choice[100];
	char check[100];
	for(;;) {
		displayCustomer(customerp);*/
		/*printf("------------------------------------\n"
			"Enter what you would like to change\n"
			"of customer \"%s\":\n"
			"name\n"
			"postcode\n"
			"phone number\n"
			"clientID\n"
			"email\n"
			"birthday\n"
			"customer balance\n"
			"accounts\n"
			"c (to exit)"
			"------------------------------------\n", customerp->name);*/
/*		
		printf("Enter what you would like to change (enter c to exit)> ");
		scanf("%100[^\n]", choice);
		if(strcmp(choice, "c") == 0) {
			break;
		}

		if(strcmp(choice, "name") == 0) {
			printf("Current name> %s\n", customerp->name);
			printf("Enter new name> (enter c to cancel)");
			scanf("%100[^\n]", &check);
			if(strcmp(check, "c") == 0) {
				continue;
			}
			if(check.len < 3 || check.len > MAX_NAME_SIZE) {
				printf("invalid character length");
				continue;
			}
			strcpy(check, customerp->name);
			continue;
		}

		if(strcmp(choice, "postcode") == 0) {
			printf("Current postcode> %s\n", customerp->postCode);
			printf("Enter new postcode> (enter c to cancel)");
			scanf("%100[^\n]", &check);
			if(strcmp(check, "c") == 0) {
				continue;
			}
			if(check.len < 3 || check.len > MAX_POSTCODE_LEN) {
				printf("invalid character length");
				continue;
			}
			strcpy(check, customerp->postcode);
			continue;
		}

		if(strcmp(choice, "phone number") == 0) {
			printf("Current phone> %s\n", customerp->phone);
			printf("Enter new phone number> (enter c to cancel)");
			scanf("%100[^\n]", &check);
			if(strcmp(check, "c") == 0) {
				continue;
			}
			if(check.len < 3 || check.len > MAX_PHONE_NUM_LEN) {
				printf("invalid character length");
				continue;
			}
			strcpy(check, customerp->phone);
			continue;
		}

		if(strcmp(choice, "clientID") == 0) {
			printf("Current clientID> %s\n", customerp->clientId);
			printf("Enter new clientID> (enter c to cancel)");
			scanf("%100[^\n]", &check);
			if(strcmp(check, "c") == 0) {
				continue;
			}
			if(check.len < 3 || check.len > MAX_CLIENT_ID_LEN) {
				printf("invalid character length");
				continue;
			}
			strcpy(check, customerp->clientId);
			continue;
		}
		}

		if(strcmp(choice, "email") == 0) {
			printf("Current email> %s\n", customerp->email);
			printf("Enter new email> (enter c to cancel)");
			scanf("%100[^\n]", &check);
			if(strcmp(check, "c") == 0) {
				continue;
			}
			if(check.len < 3 || check.len > MAX_EMAIL_LEN) {
				printf("invalid character length");
				continue;
			}
			strcpy(check, customerp->email);
			continue;
		}

		if(strcmp(choice, "birthday") == 0) {
			printf("Current birthday> %d/%d/%d\n", customerp->birthday.day, customerp->birthday.month, customerp->birthday.year);
			printf("Enter new birthday day> (enter c to cancel)");
			scanf("%100[^\n]", &check);
			if(strcmp(check, "c") == 0) {
				continue;
			}
			if(check.len < 1 || check.len > 2) {
				printf("invalid character length");
				continue;
			}
			strcpy(check, customerp->birthday.day);

			printf("Enter new birthday month> (enter c to cancel)");
			scanf("%100[^\n]", &check);
			if(strcmp(check, "c") == 0) {
				continue;
			}
			if(check.len < 1 || check.len > 2) {
				printf("invalid character length");
				continue;
			}
			strcpy(check, customerp->birthday.month);
			
			printf("Enter new birthday year> (enter c to cancel)");
			scanf("%100[^\n]", &check);
			if(strcmp(check, "c") == 0) {
				continue;
			}
			if(check.len < 1 || check.len > 2) {
				printf("invalid character length");
				continue;
			}
			strcpy(check, customerp->birthday.year);
			continue;
		}
		if(strcmp(choice, "accounts") == 0) {
			printf("Current accounts>");
			displayAccounts(customerp);
			
		}
	
	return;
	
	*/


	/*char name[MAX_NAME_SIZE];
	char postCode[MAX_POSTCODE_LEN];
	char phone[MAX_PHONE_NUM_LEN];
	char clientId[MAX_CLIENT_ID_LEN];
	char email[MAX_EMAIL_LEN];
    account_t accountList [MAX_ACCOUNT_SIZE];
    date_t birthday;
	unsigned int customerBalance;
	unsigned int numAccounts;*/
/*}*/

/*******************************************************************************
 * This function allows a manager or authorised customer to display customer details
 * inputs:
 * - customer: customer's details
 * outputs:
 * - none
*******************************************************************************/
void displayCustomer(customer_t customer) {

	printf("full name> %s\n", customer.name);
	printf("postcode> %s\n", customer.postCode);
	printf("phone number> %s\n", customer.phone);
	printf("client ID> %s\n", customer.clientId[0]);
	printf("email> %s", customer.email);
	printf("birthday> %d/%d/%d", customer.birthday.day, customer.birthday.month, 
	customer.birthday.year);
	printf("balance> %u", customer.customerBalance);

	displayAccounts(&customer);
	
    
	/* If this is to be printed, I need an int to pass into fn that representes current account list size or array len is made dynamic */

	/* printf("account list> \n");
	for(i = 0; i < MAX_ACCOUNT_SIZE; i++) {
		printf("--------------------------------");
		printf("Account number: %d\n", customer.accountList[i].accNumber);
		printf("Account name: %s\n", customer.accountList[i].accName);
		printf("--------------------------------");

	} */

}
/*******************************************************************************
 * This function resets the menu if the manager chooses an invalid option
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/
void invalidManagerChoice(void) {
	printf("Invalid choice.\n");
	printManagerMenu();
	readManagerAnswer();
}

/*******************************************************************************
 * This function allows the customer to create an account
 * inputs:
 * - none
 * outputs:
 * - int
*******************************************************************************/
void addAccount(customer_t *customer){
	account_t account;
	account.accNumber = generateAccountNum(customer);
	printf("Enter account name>");
	scanf("%s", account.accName);
	account.numTransactions = 0;
	customer->accountList[customer->numAccounts++] = account;

}
/*******************************************************************************
 * This function generates an account number that is unique for each account.
 * inputs:
 * - the number of acconts stored in the customer struct.
 * outputs:
 * - an account number (nextAccount).
*******************************************************************************/

unsigned long generateAccountNum(customer_t *customer) {
	unsigned long nextAccount = 
	10000000 + customer->numAccounts + (rand() % 1000);
	return nextAccount;
}
/*******************************************************************************
 * This function dsiplays the account infomation of the customer.
 * inputs:
 * - The number of accounts stored in customer struct.
 * - The list of accounts in the customer struct.
 * outputs:
 * - printed list of accounts.
*******************************************************************************/

void displayAccounts(customer_t *customer) {
	unsigned int i; 
	for(i = 0; i < customer->numAccounts; i++){
		displayAccount(&customer->accountList[i]);
	}

}
/*******************************************************************************
 * This function displays an individual account.
 * inputs:
 * - Account infomation (name, number) from the specific accounts from 
 * - 	displayAccouns function.
 * outputs:
 * - Prints the account infomation (name, number) and its balance.
 * - Prints a sorted list of the transactions within the account.
*******************************************************************************/

void displayAccount(account_t *account){
	printf("\naccount number: %d\naccount name: %s\nbalance: %d\n", 
	account->accNumber, account->accName, calcBalance(account));
	printSortedTransactions(account);
}
/*******************************************************************************
 * This function adds an amount inputed by the customer into a choosen account.
 * inputs:
 * - Number of accounts stored in the customer struct.
 * - A specified account.
 * - User inputed amount and name of transaction.
 * outputs:
 * - Stores the transaction within the transaction list in the account struct.
 * - Increases customer balance by choosen amount.
 * - Outputs the calculated balance using the calcBalance function.
*******************************************************************************/

void deposit(customer_t *customer, account_t *account){
	transaction_t transaction;

	printf("Enter reason for transaction: ");
	scanf("%s", transaction.name);
	printf("enter the amount you would like to deposit: ");
	scanf("%d", &(transaction.amount));

	account->transactionList[account->numTransactions++] = transaction;
	customer->customerBalance = customer->customerBalance + transaction.amount;

	printf("account balance: %d", calcBalance(account));
}
/*******************************************************************************
 * This function subtracts an amount inp[utted by the customer from the choosen 
 * - 	account.
 * inputs:
 * - Number of accounts stored in the customer struct.
 * - A specified account.
 * - User inputed amount and name of transaction.
 * outputs:
 * - Stores the transaction within the transaction list in the account struct.
 * - Decreases customer balance by choosen amount.
 * - Outputs the calculated balance using the calcBalance function.
*******************************************************************************/

void withdraw(customer_t *customer, account_t *account){
	transaction_t transaction;

	printf("Enter reason for transaction: ");
	scanf("%s", transaction.name);
	printf("enter the amount you would like to withdraw: ");
	scanf("%d", &(transaction.amount));
	transaction.amount = abs(transaction.amount) * -1;

	if(calcBalance(account) < -transaction.amount) {
		printf("insufficent funds!");
	} else {
		account->transactionList[account->numTransactions++] = transaction;
		customer->customerBalance = customer->customerBalance + 
		transaction.amount;
	}

	printf("account balance: %d", calcBalance(account));
}
/*******************************************************************************
 * This function withdraws an amount from one account and places it in another.
 * inputs:
 * - The account and transaction details stored in the customer struct:
 * - 	The number of transactions.
 * - 	The account name.
* - The amount and reason for the transfer(transferAmount, reason).
* - From and to stoires the selcted accounts to be transfered from and to.
 * outputs:
 * - The two transactions are stored into the transaction list.
 * - The transaction that has occured is printed amount and accounts.
*******************************************************************************/

void transfer(customer_t *customer){
	account_t *from;
	account_t *to;
	char reason[MAX_NAME_SIZE];
	unsigned int transferAmount;

	printf("Enter the amount you would like to transfer: ");
	scanf("%d", &transferAmount);
	printf("enter reason> ");
	scanf("%s", reason);

	from = accountSelect("choose an account name to tranfer from: ", customer);
	to = accountSelect("choose an account name to tranfer to: ", customer);

	from->transactionList[from->numTransactions++] = 
		transferWithdraw(reason, transferAmount);

	to->transactionList[to->numTransactions++] = 
		transferDeposit(reason, transferAmount);


	printf("you have sucsessfully tranfered $%d from %s to %s\n", 
	transferAmount, from->accName, to->accName);

}

/*******************************************************************************
 * This function promts the user to select an account from the exsisting list.
 * inputs:
 * - A string that prompts the user to select an account.
 * - Account list stored in the customer struct for account name.
 * - The number of accounts stored in the customer struct.
 * outputs:
 * - Returns the selcted account.
*******************************************************************************/

account_t* accountSelect(char* prompt, customer_t *customer) {
	char accName[MAX_ACCOUNT_NAME_SIZE];
	unsigned int i;
	displayAccounts(customer);
	printf("%s", prompt);
	scanf("%s", accName);
	for(i=0; i<customer->numAccounts; i++) {
		if(strcmp(accName, customer->accountList[i].accName) == 0) {
			return &(customer->accountList[i]);
		}
	}
	printf("invalid account name");
	return accountSelect(prompt, customer);
}

/*******************************************************************************
 * This function returns the deatails of the account transfered from (negative). 
 * inputs:
 * - Name of transaction.
 * - The amount in the transaction.
 * outputs:
 * - Returns the details of the transaction to be stored in transaction list.
*******************************************************************************/
transaction_t transferWithdraw(char transName[MAX_ACCOUNT_NAME_SIZE], 
int transAmount) {
	transaction_t transaction;

	strcpy(transaction.name, transName);
	transaction.amount = -transAmount;

	return transaction;
}

/*******************************************************************************
 * This function returns the deatails of the account transfered to (positive). 
 * inputs:
 * - Name of transaction.
 * - The amount in the transaction.
 * outputs:
 * - Returns the details of the transaction to be stored in transaction list.
*******************************************************************************/

transaction_t transferDeposit(char transName[MAX_ACCOUNT_NAME_SIZE], 
int transAmount) {
	transaction_t transaction;

	strcpy(transaction.name, transName);
	transaction.amount = transAmount;

	return transaction;
}

/*******************************************************************************
 * This function prints the details of a transaction.
 * inputs:
 * - The name and amount stored in the choosen transaction.
 * - A count for listing the transactions by number.
 * outputs:
 * - The details of the transaction.
*******************************************************************************/

void printTransaction(transaction_t *transaction, int count) {
	printf("%d. %s $%d\n", count, transaction->name, transaction->amount);
}
/*******************************************************************************
 * This function calculates the balance in a choosen account.
 * inputs:
 * - The account choosen for the number of transactions and amount stored in the
 * - 	transaction list.
 * outputs:
 * - Returns the balance of the account.
*******************************************************************************/

int calcBalance(account_t *account) {
	int balance = 0;
	unsigned int i;
	for(i=0; i<account->numTransactions; ++i) {
		balance += account->transactionList[i].amount;
	}
	return balance;
}
/*******************************************************************************
 * This function is used for inccorect user inputs in the main menu.
 * inputs:
 * - Details stored in customer.
 * outputs:
 * - Prints invalid choice.
 * - 	Recursive function:
 * - Executes the customer menu function.
 * - Executes the read customer answer function. 
*******************************************************************************/
void invalidCustomerChoice(customer_t *customer) {
	printf("Invalid choice.\n");
	printCustomerMenu();
	readCustomerAnswer(customer);
}

/*******************************************************************************
 * This function searches customer transactions by amount range.
 * inputs:
 * - Choice of range to search in.
 * - The number of transactions.
 * - The number of accounts.
 * - The amounts stored in account transaction lists.
 * outputs:
 * -  printed list of the transactions that are within the choosen range.
*******************************************************************************/
void searchTransactions(customer_t *customer){
	int choice;
	char tempchoice[20];
	int check =0;
	int r1,r2;
	int results =0;
	unsigned int iter, i;

	
	while (check ==0){	
	printf(
		"Select either 1,2,3,4 or 5:\n"
		"1) $0 - $99\n"
		"2) $100 - $999\n"
		"3) $1000 - $99,999\n"
		"4) $100,000 - $999,999\n"
		"5) $1,000,000 and above\n");
		scanf("%s", &tempchoice[0]);
		choice = atoi(tempchoice);
		if(choice == 0){
			printf("Invalid Answer. ");
		} else{
			if (choice >=1 && choice <= 5){
				check = 1;
			} else printf("Invalid Answer. ");
		}
	}
	
	if (choice ==1) {
		r1 = 0;
		r2 = 99;
	} else if (choice ==2) {
		r1 = 100;
		r2 = 999;
	} else if (choice ==3) {
		r1 = 1000;
		r2 = 99999;
	} else if (choice ==4) {
		r1 = 100000;
		r2 = 999999;
	} else if (choice ==5) {
		r1 = 1000000;
		r2 = 999999999;
	}

	for(i = 0; i<customer->numAccounts; i++) {
		for(iter = 0; iter<customer->accountList[i].numTransactions; iter++) {
			if(r1 <= customer->accountList[i].transactionList[iter].amount &&
				r2 >= customer->accountList[i].transactionList[iter].amount) {
					++results;
					printTransaction(&customer->
						accountList[i].transactionList[iter], results);
			}
			else {
				continue;
			}
		}	
	}
	if(results == 0) {
		printf("no results found in this range\n");
	}
}

/*******************************************************************************
 * This function search customer transactions by name.
 * inputs:
 * - The name of transaction the user is searching for.
 * - The number of accounts.
 * - The number of transactions.
 * - The name of transactions stored in the transaction lists.
 * outputs:
 * - Prints the transaction details of transactions with the choosen name. 
*******************************************************************************/

void searchByName(customer_t *customer) {
	int results = 0;
	unsigned int i, iter;
	char searchName[MAX_TRANSACTION_NAME];

	printf("enter transaction name you would like to search for: ");
	scanf("%s", searchName);

	for(i = 0; i<customer->numAccounts; i++) {
		for(iter = 0; iter<customer->accountList[i].numTransactions; iter++) {
			if(strcmp((searchName), 
				(customer->accountList[i].transactionList[iter].name)) == 0) {
					++results;
					printTransaction(&customer->
						accountList[i].transactionList[iter], results);
			}
			else {
				continue;
			}
		}
	}
	if(results == 0) {
		printf("no results with that name found");
	}
}

/*******************************************************************************
 * This function sorts the transactions from lowest to highest amounts.
 * inputs:
 * - The list of transactions stored within a copy 
 * - 	(so actual list is not affected).
 * - The number of tranactions.
 * outputs:
 * - Creates a list of sorted trnasactions from lowest to highest.
*******************************************************************************/

void sortTransactions(transaction_t* list, unsigned int numTransactions) {
	unsigned int i,j;
	transaction_t temp;

	for(i=0; i<numTransactions; ++i) {
		for(j=0; j<numTransactions-i-1; ++j){
			if(abs(list[j].amount) > abs(list[j+1].amount)) {
				temp = list[j];
				list[j] = list[j+1];
				list[j+1] = temp;
			}
		}
	}
}

/*******************************************************************************
 * This function prints the list of sorted transactions.
 * inputs:
 * - Number of transactions.
 * - A temporary list.
 * - The list of transactions.
 * outputs:
 * - Stores the list of transactions in a temporary list.
 * - Prints a sorted list of transactions using the print transaction function.
*******************************************************************************/

void printSortedTransactions(account_t * account) {
	transaction_t sortedList[MAX_TRANSACTION_SIZE];
	unsigned int i;
	for(i=0; i<account->numTransactions; ++i) {
		sortedList[i] = account->transactionList[i];
	}
	sortTransactions(sortedList, account->numTransactions);
	for(i=0; i<account->numTransactions; ++i) {
		printTransaction(&sortedList[i], i+1);
	}

}
/*******************************************************************************
 * - End of program.
*******************************************************************************/