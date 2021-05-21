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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

/* gcc -Wall -Werror -ansi -o main.out main.c -lm */

/*******************************************************************************
 * List preprocessing directives
*******************************************************************************/

#define MAX_TRANSACTION_SIZE 100
#define MAX_NAME_SIZE 25
#define MAX_ACCOUNT_NAME_SIZE 15
#define MAX_ACCOUNT_SIZE 5
#define MAX_STATE_NAME_SIZE 20
#define MAX_STREET_NAME_SIZE 20
#define MAX_SUBURB_NAME_SIZE 30
#define MAX_EMAIL_LEN 20
#define MAX_POSTCODE_LEN 5
#define MAX_CLIENT_ID_LEN 5
#define MAX_PHONE_NUM_LEN 10
#define MAX_USERNAME_LEN 20
#define MIN_PASSWORD_LEN 3
#define MAX_PASSWORD_LEN 20
#define MAX_TRANSACTION_NAME 20



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
	/*unsigned int accBalance;*/
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
customer_t createCustomer(void);          		/* Author: Thomas Good - DONE*/
char* generateId(void);						/* Author: Thomas Good - DONE*/
void deleteCustomer();       /* Author: Thomas Good */
void saveCustomer(customer_t customer);         /* Author: Thomas Good - DONE */
void displayCustomer(customer_t* customerp);      /* Author: Lukas Gaspar - DONE */
void changeCustomerDetails(customer_t *customerp); /* Author: Lukas Gaspar */
int readManagerAnswer(void);        			/* Author: Thomas Good - kinda DONE */
void invalidManagerChoice(void);    			/* Author: Thomas Good - DONE */

/* Customer functions */
void printCustomerMenu(void);       			/* Author: Thomas Good - DONE */

/* Author: Reece Wallace*/
void addAccount(customer_t *customer); 			/* Author: Reece Wallace - DONE */
unsigned long generateAccountNum(customer_t *customer); /* Author: Reece Wallace - DONE */
void displayAccounts(customer_t *customer); 	/* Author: Reece Wallace - DONE */
void displayAccount(account_t *account); 		/* Author: Reece Wallace - DONE */
void deposit(customer_t *customer, account_t *account); /* Author: Reece Wallace, Carter Pisani - DONE */
void withdraw(customer_t *customer, account_t *account); /* Author: Reece Wallace, Carter Pisani - DONE */
void transfer(customer_t *customer); /* Author: Reece Wallace - DONE*/
int readCustomerAnswer(customer_t *customer);   /* Author: Thomas Good - kinda DONE */
void invalidCustomerChoice(customer_t *customer); /* Author: Thomas Good - DONE */

int calcBalance(account_t *account); /* Author: Reece Wallace - DONE */
void printTransaction(transaction_t *transaction, int count); 	

/* Shared */
void printMenu(void);               			/* Author: Thomas Good - DONE */
/*int login(void);*/                   				/* Author: Lukas Gaspar - DONE */
void changePassword(void);          			/* Author: Lukas Gaspar - shouldnt password be customer struct variable? */

void searchTransactions(customer_t *customer); 	/* Author: Reece Wallace */
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
void searchByName(customer_t *customer); /* Author: Reece Wallace */
void authenticate(char *a, char *b);						/* Author: Lukas Gaspar */
int logout;							/* Author: Carter Pisani - Done*/


int main(void) {
	do{
	printMenu();
	printManagerMenu();
	readManagerAnswer();
	}while(logout ==0);
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
    printf("\n\n"
    	"-------Welcome to EZY Banking System 1.0-------\n"
        "Please enter your login details to proceed\n"
        "-------------------------------------------\n");
		
		

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
/*void authenticate(void){

}*/
/*******************************************************************************
 * This function logs in the user
 * inputs:
 * - none
 * outputs:
 * - int used to return the user's login status (0 - no authorisation, 1 - customer, 2 - manager)
*******************************************************************************/
/*int login(void) {*/
	/*int loginStatus = 0;*/
	/*char username[MAX_USERNAME_LEN];
	char password[MAX_PASSWORD_LEN];


	for(;;) { 
		printf("Enter \"back\" at any time to go back to the menu\n");
		printf("Enter username> ");
		scanf("%100[^\n]", username);
		printf("Enter password> ");
		scanf("%100[^\n]", password);
		if(authenticate(&username[MAX_USERNAME_LEN], &password[MAX_PASSWORD_LEN]) == 0) {
			printf("incorrect username or password\n");

			for(;;) {
				printf("go back to the menu? (y/N): ");
				char check[100];
				scanf("%100[^\n]", check);
				if(strcmp(check, "y") == 0) {
					return 3;
				}
				if(strcmp(check, "N") == 0) {
					break;
				}
				printf("invalid choice\n");
				continue;
			}
		}
		if(authenticate(&username[MAX_USERNAME_LEN], &password[MAX_PASSWORD_LEN]) == 1) {*/
			/*return 1;*/ /* Authenticated as customer. */
		/*}*/
		/*if(authenticate(&username[MAX_USERNAME_LEN], &password[MAX_PASSWORD_LEN]) == 2) {
			return 2;*/ /* Authenticated as manager. */
		/*}
		printf("unknown authentication return value");
	}
}
*/
/*******************************************************************************
 * This function generates the customerId when created
 * inputs:
 * - none
 * outputs:
 * - char *
*******************************************************************************/
char* generateId(void){
	FILE *fp = fopen("database","r");
    int ch=0;
    int lines=0;
    if (fp == NULL){
    	char *id = "0001";
  		return id;
	} else {
		lines++;
		while ((ch = fgetc(fp)) != EOF)
		{
			if (ch == '\n'){
				lines++;
			}
		}
		fclose(fp);
	}
	char* id = malloc(5);
	sprintf(id, "%04d", lines);
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
			customer_t customer = createCustomer();
			saveCustomer(customer);
		} else if (answer == '2') {

			deleteCustomer();
			/* Delete customer */
		} else if (answer == '3') {
			customer_t customer;
			customer_t* customerp = &customer;
			displayCustomer(customerp);

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
		} else if (answer == '4') {
			/* Search customer transactions */
		} else if (answer == '5') {
			/* Update customer details */
		} else if (answer == '6') {
				logout = 0;
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

			printf("select an account");
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
			logout = 0;
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
		"Enter your choice>");
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

	printf("Enter Name> ");
	scanf("%100[^\n]", customer.name);
	getchar();
	
	while (check == 0) {
		printf("Enter Phone Number> ");
		scanf("%11[^\n]", customer.phone);
		getchar();
		int i, count = 0;
    	for (i = 0; customer.phone[i] != '\0'; ++i){
			count++;
		}
		if (i != 10) {
			printf("Invalid Phone Number\n");
		} else {
			check = 1;
		}
	}
	check = 0;
	while (check == 0) {
		printf("Enter Post Code> ");
		scanf("%5[^\n]", customer.postCode);
		getchar();
		int i, count = 0;
    	for (i = 0; customer.postCode[i] != '\0'; ++i){
			count++;
		}
		if (i != 4) {
			printf("Invalid Post Code\n");
		} else {
			check = 1;
		}
	}
	check = 0;
	printf("Enter Email Address> ");
	scanf("%20[^\n]", customer.email);
	getchar();

	while(check == 0) {
		printf("Enter birthday: day>");
		scanf("%s", &tempDay[0]);
		/* Checks if given value is int */
		val = atoi(tempDay);
		if (val == 0) {
			printf("Invalid day. ");
		} else {
			if (val >= 1 && val <= 31) {
				birthday.day = val;
				check = 1; 
			} else printf("Invalid day. "); 
		}
	}
	/* Resets check */
	check = 0;
	/* Until given month is valid, ask for birthday month */
	while(check == 0) {
		printf("Enter birthday: month>");
		scanf("%s", &tempMonth[0]);
		/* Checks if given value is int */
		val = atoi(tempMonth);
		if (val == 0) {
			printf("Invalid month. ");
		} else {
			if (val >= 1 && val <= 12) {
				birthday.month = val;
				check = 1; 
			} else printf("Invalid month. "); 
		}
	}
	/* Resets check */
	check = 0;
	/* Until given year is valid, ask for birthday year */
	while(check == 0) {
		printf("Enter birthday: year>");
		scanf("%s", &tempYear[0]);
		/* Checks if given value is int */
		val = atoi(tempYear);
		if (val == 0) {
			printf("Invalid year. ");
		} else {
			if (val >= 1800 && val <= 2017) {
				birthday.year = val;
				check = 1; 
			} else printf("Invalid year. "); 
		}
	}
	check = 0;
	getchar();
	customer.birthday = birthday;
	customer.clientId[0] = generateId();
	customer.customerBalance = 5;
	customer.numAccounts = 1;
	return customer;
}

/*******************************************************************************
 * This function allows a manager to delete a customer
 * inputs:
 * - customer_t
 * outputs:
 * - none
*******************************************************************************/
void deleteCustomer() {}
/*void deleteCustomer(){
	/* Removes customer details from managers customer file & deletes 
	customers folder */
	/*char* answer = malloc(1);
	printf("Are you sure you want to delete this customer? Y/N> ");
	scanf("%c", answer);
	if (){
		printf("Customer Deleted\n");
	} else if (){
		printf("Customer Not Deleted\n");

	} else {
		printf("Invalid answer\n");
	}
	/* Add a double check prompt */
	/*getchar();
	printManagerMenu();
	readManagerAnswer();
    
}*/

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
void changeCustomerDetails(customer_t *customerp) {
	char choice[100];
	char check[100];
	for(;;) {
		displayCustomer(customerp);
		printf("------------------------------------\n"
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
			"------------------------------------\n", customerp->name);

		printf("Enter what you would like to change (enter c to exit)> ");
		scanf("%100[^\n]", &choice);
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
			if(strlen(check) < 3 || strlen(check) > MAX_NAME_SIZE) {
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
			if(strlen(check) < 3 || strlen(check) > MAX_POSTCODE_LEN) {
				printf("invalid character length");
				continue;
			}
			strcpy(check, customerp->postCode);
			continue;
		}

		if(strcmp(choice, "phone number") == 0) {
			printf("Current phone> %s\n", customerp->phone);
			printf("Enter new phone number> (enter c to cancel)");
			scanf("%100[^\n]", &check);
			if(strcmp(check, "c") == 0) {
				continue;
			}
			if(strlen(check) < 3 || strlen(check) > MAX_PHONE_NUM_LEN) {
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
			if(strlen(check) < 3 || strlen(check) > MAX_CLIENT_ID_LEN) {
				printf("invalid character length");
				continue;
			}
			strcpy(check, customerp->clientId);
			continue;
		}

		if(strcmp(choice, "email") == 0) {
			printf("Current email> %s\n", customerp->email);
			printf("Enter new email> (enter c to cancel)");
			scanf("%100[^\n]", &check);
			if(strcmp(check, "c") == 0) {
				continue;
			}
			if(strlen(check) < 3 || strlen(check) > MAX_EMAIL_LEN) {
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
			if(strlen(check) < 1 || strlen(check) > 2) {
				printf("invalid character length");
				continue;
			}
			strcpy(check, customerp->birthday.day);

			printf("Enter new birthday month> (enter c to cancel)");
			scanf("%100[^\n]", &check);
			if(strcmp(check, "c") == 0) {
				continue;
			}
			if(strlen(check) < 1 || strlen(check) > 2) {
				printf("invalid character length");
				continue;
			}
			strcpy(check, customerp->birthday.month);
			
			printf("Enter new birthday year> (enter c to cancel)");
			scanf("%100[^\n]", &check);
			if(strcmp(check, "c") == 0) {
				continue;
			}
			if(strlen(check) < 1 || strlen(check) > 2) {
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
	}
	
	return;
}

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
void displayCustomer(customer_t* customerp) {

	printf("full name> %s\n", customerp->name);
	printf("postcode> %s\n", customerp->postCode);
	printf("phone number> %s\n", customerp->phone);
	printf("client ID> %s\n", customerp->clientId[0]);
	printf("email> %s", customerp->email);
	printf("birthday> %d/%d/%d", customerp->birthday.day, customerp->birthday.month, 
	customerp->birthday.year);
	printf("balance> %u", customerp->customerBalance);

	displayAccounts(customerp);
}

	/* If this is to be printed, I need an int to pass into fn that representes current account list size or array len is made dynamic */

	/* printf("account list> \n");
	for(i = 0; i < MAX_ACCOUNT_SIZE; i++) {
		printf("--------------------------------");
		printf("Account number: %d\n", customer.accountList[i].accNumber);
		printf("Account name: %s\n", customer.accountList[i].accName);
		printf("--------------------------------");

	} */

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
 * This function resets the menu if the customer chooses an invalid option
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/

unsigned long generateAccountNum(customer_t *customer) {
	unsigned long nextAccount = 10000000 + customer->numAccounts + (rand() % 1000);
	return nextAccount;
}
/*******************************************************************************
 * This function resets the menu if the customer chooses an invalid option
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/

void displayAccounts(customer_t *customer) {
	unsigned int i; 
	for(i = 0; i < customer->numAccounts; i++){
		displayAccount(&customer->accountList[i]);
	}

}
/*******************************************************************************
 * This function resets the menu if the customer chooses an invalid option
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/

void displayAccount(account_t *account){
	printf("\naccount number: %d\naccount name: %s\nbalance: %d\n", 
	account->accNumber, account->accName, calcBalance(account));
	printSortedTransactions(account);
}
/*******************************************************************************
 * This function resets the menu if the customer chooses an invalid option
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/

void deposit(customer_t *customer, account_t *account){
	transaction_t transaction;

	printf("Enter reason for transaction: ");
	scanf("%s", transaction.name);
	printf("enter the amount you would like to deposit: ");
	scanf("%d", &(transaction.amount));

	account->transactionList[account->numTransactions++] = transaction;
	customer->customerBalance = customer->customerBalance + transaction.amount;

/*to do check*/
	printf("account balance: %d", calcBalance(account));
}
/*******************************************************************************
 * This function resets the menu if the customer chooses an invalid option
 * inputs:
 * - none
 * outputs:
 * - none
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
 * This function resets the menu if the customer chooses an invalid option
 * inputs:
 * - none
 * outputs:
 * - none
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

	from = accountSelect("choose an acount to tranfer from: ", customer);
	to = accountSelect("choose an acount to tranfer to: ", customer);

	from->transactionList[from->numTransactions++] = 
		transferWithdraw(reason, transferAmount);

	to->transactionList[to->numTransactions++] = 
		transferDeposit(reason, transferAmount);


	printf("you have sucsessfully tranfered $%d from %s to %s\n", 
	transferAmount, from->accName, to->accName);

}

account_t* accountSelect(char* prompt, customer_t *customer) {
	char accName[MAX_ACCOUNT_NAME_SIZE];
	unsigned int i;
	displayAccounts(customer);
	printf("%s", prompt);
	scanf("%s", accName);
	for(i=0; i<customer->numAccounts; i++){
		if(strcmp(accName, customer->accountList[i].accName) == 0) {
			return &(customer->accountList[i]);
		}
	}
	printf("invalid account name");
	return accountSelect(prompt, customer);
}

/*******************************************************************************
 * This function resets the menu if the customer chooses an invalid option
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/
transaction_t transferWithdraw(char transName[MAX_ACCOUNT_NAME_SIZE], 
int transAmount){
	transaction_t transaction;

	strcpy(transaction.name, transName);
	transaction.amount = -transAmount;



	return transaction;
}

transaction_t transferDeposit(char transName[MAX_ACCOUNT_NAME_SIZE], 
int transAmount){
	transaction_t transaction;

	strcpy(transaction.name, transName);
	transaction.amount = transAmount;

	return transaction;
}

void printTransaction(transaction_t *transaction, int count){
	printf("%d. %s $%d\n", count, transaction->name, transaction->amount);
}
/*******************************************************************************
 * This function resets the menu if the customer chooses an invalid option
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/

int calcBalance(account_t *account){
	int balance = 0;
	unsigned int i;
	for(i=0; i<account->numTransactions; ++i){
		balance += account->transactionList[i].amount;
	}
	return balance;
}
/*******************************************************************************
 * This function resets the menu if the customer chooses an invalid option
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/
void invalidCustomerChoice(customer_t *customer) {
	printf("Invalid choice.\n");
	printCustomerMenu();
	readCustomerAnswer(customer);
}


/*******************************************************************************
 * This function searches customer transactions
 * inputs:
 * - customer_t, transaction_t
 * outputs:
 * - none
*******************************************************************************/
void searchTransactions(customer_t *customer)
{
	int r1, r2;
	int results = 0;
	unsigned int iter, i;
	printf("enter the rannge to search in separated by a space: ");
	scanf("%d %d", &r1, &r2);

	for(i = 0; i<customer->numAccounts; i++){
		for(iter = 0; iter<customer->accountList[i].numTransactions; iter++){
			if(r1 <= customer->accountList[i].transactionList[iter].amount &&
			r2 >= customer->accountList[i].transactionList[iter].amount){
				++results;
				printTransaction(&customer->accountList[i].transactionList[iter]
				, results);
			}
			else{
				continue;
			}
		}
		
	}
	if(results == 0){
		printf("no results found in this range");
	}
}

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
					printTransaction(&customer->accountList[i].transactionList[iter], 
						results);
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


