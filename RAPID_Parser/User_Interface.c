/*******************************************************************************
* Title: User_Interface.h
* Author: Tyler Knight
* Date: 7/4/2019
*
* Purpose: Get required input from user
*
* Description: Gets all information about machine and run info
* 	from user
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "Spray_Positions.h"

#define MAX_USR_INPUT 50
#define TRUE 1
#define FALSE 0


/* Prototypes */
static void getInput(char *prompt, char *stringBuffer);
static bool dataIsValid(void);
static void getCurrentJobInfo(void);
static void displayInstructions(void);
static void correctData(void);
static void printAscii(void);
static void fullScreen(void);

/* Global Functions */
void getDataFromUser(void);


struct jobInformation
{
    char dieNumber[MAX_USR_INPUT];
    char shopOrderNumber[MAX_USR_INPUT];
    char cavityNumber[MAX_USR_INPUT];
    char partNumber[MAX_USR_INPUT];
    char programName[MAX_USR_INPUT];
    char machineNumber[MAX_USR_INPUT];
    char customerName[MAX_USR_INPUT];
};


//Struct initialization
struct jobInformation endOfRunData = {0};


void getDataFromUser()
{
	displayInstructions();
	getCurrentJobInfo();

	while (TRUE)
	{
		if (dataIsValid())
			break;
		else
			correctData();
	}
}


/****************************************
*   Gets input from the user
*   Input must be at least 1 character
****************************************/
static void getInput(char *prompt, char *stringBuffer)
{
	unsigned long int i;

	strcpy(stringBuffer, "");

	while (1)
	{
		printf("%s\n-->", prompt);
		fflush(stdin);
		fgets(stringBuffer, MAX_USR_INPUT, stdin);
		if (strlen(stringBuffer) > 1 &&
		    strlen(stringBuffer) <= MAX_USR_INPUT)
			break;
	}

	//Capitalize string and remove trailing newline char from fgets()
	for (i = 0; i < strlen(stringBuffer); i++)
	{
		stringBuffer[i] = toupper(stringBuffer[i]);
		if (stringBuffer[i] == '\n')
			stringBuffer[i] = '\0';
	}

	return;
}


/***********************************************************
*   Prompts user to verify that the information they
*   entered is correct, if it is not, the user can
*   opt to re-enter it.
***********************************************************/
static bool dataIsValid(void)
{
	char userInput[MAX_USR_INPUT] = {0};

	memset(userInput, 0, sizeof(userInput));
	strcpy(userInput, "");

	system("cls");
	printf("\nVERIFY THIS INFO IS CORRECT\n\n");
	printf("**************************************\n");
	printf("# MACHINE NUMBER: %s\n\n", endOfRunData.machineNumber);
	printf("# CUSTOMER NAME: %s\n\n", endOfRunData.customerName);
	printf("# DIE NUMBER: %s\n\n", endOfRunData.dieNumber);
	printf("# SHOP ORDER NUMBER: %s\n\n", endOfRunData.shopOrderNumber);
	printf("# CAVITY NUMBER: %s\n\n", endOfRunData.cavityNumber);
	printf("# PART NUMBER: %s\n\n", endOfRunData.partNumber);
	printf("# PROGRAM NAME: %s\n\n", endOfRunData.programName);
	printf("**************************************\n");

	getInput("Enter 1 for yes\nEnter 2 for no\n", userInput);

	if (strcmp(userInput, "1") == 0)
		return TRUE;
	else
		return FALSE;
}

/* Get all job info from user */
static void getCurrentJobInfo(void)
{
	getInput("Enter the machine number", endOfRunData.machineNumber);
	getInput("Enter the customer name", endOfRunData.customerName);
	getInput("Enter the die number", endOfRunData.dieNumber);
	getInput("Enter the shop order number", endOfRunData.shopOrderNumber);
	getInput("Enter the cavity number", endOfRunData.cavityNumber);
	getInput("Enter the part number", endOfRunData.partNumber);
	getInput("Enter the program name", endOfRunData.programName);
}

/* Display instructions to user */
static void displayInstructions(void)
{
	printf("*******************************************************************************************************************\n\n");
	printf("\t ~SPRAYDOC V2 INSTRUCTIONS~\n\n\n");
	printf("# Open the rapid_program.txt file and press the ctrl key *and* the a key (ctrl+a) to select the whole file\n");
	printf("# With the whole file selected, press *del*\n");
	printf("# LEAVE THE RAPID PROGRAM FILE OPEN\n\n\n");

	printf("# Open the program file that you need to document\n");
	printf("# With the program file open, press the ctrl key *and* the a key (ctrl+a) to select the whole file\n");
	printf("# Press (ctr+c) to copy the whole program\n\n");

	printf("# With the whole file selected, click back on the rapid_program.txt file\n");
	printf("# Press the ctrl key and the v key (ctrl+v) to paste the contents into the rapid_program.txt file\n");
	printf("# Close the program that you copied from\n\n");

	printf("# With the rapid_program.txt file selected, press the ctrl key and the s key (ctrl+s) to save the contents\n");
	printf("# Make sure that you close the file after you save\n");
	printf("# DO NOT RENAME THE FILE\n\n\n");

	printf("# Enter the data the prompts ask for, if you mess up the data, you will \n\thave the option to enter it again after the prompts.\n");
	printf("# Report any errors to Tyler\n\n");
	printf("******************************************************************************************************************\n");
}

/* Allows the user to correct info */
static void correctData(void)
{
	char *menu = "What Data do you need to re-enter?\n \
1) Machine Number\n \
2) Customer Name\n \
3) Die Number\n \
4) Shop Order Number\n \
5) Cavity Number\n \
6) Part Number\n \
7) Program Name\n \
8) I need to re-enter everything\n \
9) I accidentally pressed no\n";
	char userInput[20] = {0};
	int userNumberInput = 0;

	getInput(menu, userInput);
	userNumberInput = userInput[0] - '0';

	switch (userNumberInput)
	{
		case 1:
			getInput("Enter the machine number",
				 endOfRunData.machineNumber);
			break;
		case 2:
			getInput("Enter the customer name",
				 endOfRunData.customerName);
			break;
		case 3:
			getInput("Enter the die number",
				 endOfRunData.dieNumber);
			break;
		case 4:
			getInput("Enter the shop order number",
				 endOfRunData.shopOrderNumber);
			break;
		case 5:
			getInput("Enter the cavity number",
				 endOfRunData.cavityNumber);
			break;
		case 6:
			getInput("Enter the part number",
				 endOfRunData.partNumber);
			break;
		case 7:
			getInput("Enter the program name",
				 endOfRunData.programName);
			break;
		case 8:
			getCurrentJobInfo();
			break;
		case 9:
			break;
		default:
			printf("Invalid Selection Enter a number between 1 and 8 only\n");
			printf("You will need to re-enter your selection on the next screen\n");
			system("pause");
			break;
	}
}


/* Writes info to a file */
void writeJobInfo(FILE *fp)
{
	fprintf(fp, "JOB INFO: ,%s,%s,%s,%s,%s,%s,%s\n",
		endOfRunData.machineNumber,
		endOfRunData.dieNumber, endOfRunData.customerName,
		endOfRunData.partNumber, endOfRunData.cavityNumber,
		endOfRunData.shopOrderNumber, endOfRunData.programName);
}

