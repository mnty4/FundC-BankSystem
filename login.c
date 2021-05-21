#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_TRANSACTION_SIZE 100
#define MAX_NAME_SIZE 11
#define MAX_ACCOUNT_NAME_SIZE 15
#define MAX_ACCOUNT_SIZE 5
#define MAX_STATE_NAME_SIZE 20
#define MAX_STREET_NAME_SIZE 20
#define MAX_SUBURB_NAME_SIZE 30
#define MAX_EMAIL_LEN 20
#define MAX_POSTCODE_LEN 4
#define MAX_CLIENT_ID_LEN 5
#define MAX_PHONE_NUM_LEN 10
#define MAX_USERNAME_LEN 20
#define MIN_PASSWORD_LEN 3
#define MAX_PASSWORD_LEN 20

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
    char password[MAX_PASSWORD_LEN];
    char username[]
};
typedef struct customer customer_t;

int login(void) {
	int loginStatus = 0;
	char email[MAX_EMAIL_LEN];
	char password[MAX_PASSWORD_LEN];


	for(;;) { 
		printf("Enter \"back\" at any time to go back to the menu\n");
		printf("Enter username> ");
		scanf("%100[^\n]", email);
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
		if(authenticate(&username[MAX_USERNAME_LEN], &password[MAX_PASSWORD_LEN]) == 1) {
			return 1; /* Authenticated as customer. */
		}
		if(authenticate(&username[MAX_USERNAME_LEN], &password[MAX_PASSWORD_LEN]) == 2) {
			return 2; /* Authenticated as manager. */
		}
		printf("unknown authentication return value");
	}
}