/******************************************************************************
*  Title: Rapid Parser
*  Author: Tyler Knight
*  Date: 7/5/2019
*
*
*
*  Purpose:
*  1) Parses a RAPID source file and extracts the following data ->
*      ! Sweep Patterns
*      ! Dwell Patterns
*      ! Sweep Speeds
*      ! Dwell Times
*      ! Movement type 'j,l,c'
*      ! Movement Precision "zones/fines"
*      ! Total Positions Used
*
*  2) Sets all data from purpose #1 to the sprayPositions structure array
*
*
**********************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "Spray_Positions.h"

#define RAPID_FILEPATH "dependencies\\rapid_src.txt"
#define MAX_STR_LENGTH 1000
#define COVER_HALF 1
#define EJECTOR_HALF 2
#define ARRAY_SIZE(x) (sizeof (x) / sizeof(x)[0])

/* Prototypes */
static void formatStatement(char *string);
static void reverseString(char *input);
static void getDwellTime(char *line, int linePosition, char *dwellTime);
static void getSweepSpeed(char *line, int linePosition, char *sweepSpeed);
static void getDwellPattern(char *line, int linePosition, int side, char*dwellPattern);
static void getSweepPattern(char *line, int linePosition, int side, char
*sweepPattern);
static void getNozzlePattern(int wholeNumber, int side, char *pattern);
static void getAdditionalCommands(char *line);
static void getZoneType(char *line);
static void getMoveType(char *line);
static void updateLineIndex(int counter);
static void readSrcFile(void);
static void openSrcFile(void);
static void closeSrcFile(void);
static void getDataFromSprayPositionsRoutine(char *currentLine);
static void getDataFromSprayFunctionsArray(char *sprayFunctionArray);
static bool checkForReturn(char *line);
static bool findWord(char *string, char *substring);
static bool checkForStatementTerminator(char ch);

/* Global Variables */
/******************************************************************************/
int getTotalPositions(void);
static FILE *fp;

static int totalSprayPositions = 1;         //Keeps track of the total used positions
static int currentLineIndex = 0;            //Used to update line index
static int commandNumberForPosition = 1;    //Keeps up with additional commands per position

//Flags used for the SPRAY_FUNCTION array
static bool foundSprayFunctionArray = false;
static bool doneReadingSprayFunctionArray = false;
//Flags used for the spray_positions() function
static bool foundSprayPositionsRoutine = false;
static bool doneReadingSprayPositionsRoutine = false;
/******************************************************************************/

/*******************************************************************************
 * Parses the Rapid Source file, and gets the spray data from the 80x15 array
 * (SPRAY_FUNCTION)
 * Also parses the SPRAY_POSITIONS function to get move/zone types and
 * additional commands like turning on digital outputs and etc
 ******************************************************************************/
static void readSrcFile()
{
	char currentLine[MAX_STR_LENGTH] = {0};
	char arrayBuffer[5000] = {0};
	char ch;
	int i;
	int arrayBufferIndex = 0;

	while (fgets(currentLine, MAX_STR_LENGTH, fp) != NULL)
	{
		//Convert line to uppercase to simplify string comparison
		toupper(*currentLine);

		//Check line for certain array/function declaration
		if (findWord(currentLine, "PERS NUM SPRAY_FUNCTION{80,15}"))
			foundSprayFunctionArray = true;
		if (findWord(currentLine, "PROC SPRAY_POSITIONS()"))
			foundSprayPositionsRoutine = true;


		//If the sprayFunction array is found, and we haven't already read it, read it
		if (foundSprayFunctionArray && !doneReadingSprayFunctionArray)
		{
			//Loop through the current line, adding each character to the array buffer
			for (i = 0;
			     i < strlen(currentLine); i++, arrayBufferIndex++)
			{
				ch = currentLine[i];
				arrayBuffer[arrayBufferIndex] = currentLine[i];

				//Once ';' is reached, send arrayBuffer to be read
				if (checkForStatementTerminator(ch))
				{
					arrayBuffer[arrayBufferIndex +
						    1] = '\0';
					getDataFromSprayFunctionsArray(
						arrayBuffer);
					doneReadingSprayFunctionArray = true;
					break;
				}
			}
		}

		//If the spray positions routine has been found, but not read, read it
		if (foundSprayPositionsRoutine &&
		    !doneReadingSprayPositionsRoutine)
			getDataFromSprayPositionsRoutine(currentLine);

		//Exit once array and function have been read
		if (doneReadingSprayFunctionArray &&
		doneReadingSprayPositionsRoutine)
			return;
	}
}


/**************************************************************
*   Takes the current line read from file as input
*   Reads only the elements inside the brackets of
*   an array, then updates the spray_positions struct
*   !struct location: spray_positions.c
**************************************************************/
static void getDataFromSprayFunctionsArray(char *sprayFunctionArray)
{
	char ch;
	char dwellTime[5] = {0};
	char sweepPattern[10] = {0};
	char dwellPattern[10] = {0};
	char sweepSpeed[5] = {0};

	//Counters
	int i;
	int sprayFunctionArrayDim1 = 0;
	int sprayFunctionArrayDim2 = 0;
	int currentPosition = 0;

	bool insideBrackets = false;

	//Array Indexes for dimension 2
	const int SWEEP_A = 0;
	const int SWEEP_B = 1;
	const int DWELL_A = 5;
	const int DWELL_B = 6;
	const int SWEEP_SPEED = 10;
	const int DWELL_TIME = 11;
	const int LAST_INDEX = 15;

	for (i = 0; i < strlen(sprayFunctionArray); i++)
	{
		ch = sprayFunctionArray[i];

		//Used to tell if we're in an array or not
		if (ch == '[')
			insideBrackets = true;
		else if (ch == ']')
			insideBrackets = false;

		//If we're inside an array, and not at a comma
		if ((insideBrackets) && (ch != '[') && (ch != ']') &&
		    (ch != ','))
		{
			if (sprayFunctionArrayDim2 == SWEEP_A)
				getSweepPattern(sprayFunctionArray, i,
						COVER_HALF, sweepPattern);

			else if (sprayFunctionArrayDim2 == SWEEP_B)
				getSweepPattern(sprayFunctionArray, i,
						EJECTOR_HALF, sweepPattern);

			else if (sprayFunctionArrayDim2 == DWELL_A)
				getDwellPattern(sprayFunctionArray, i,
						COVER_HALF, dwellPattern);

			else if (sprayFunctionArrayDim2 == DWELL_B)
				getDwellPattern(sprayFunctionArray, i,
						EJECTOR_HALF, dwellPattern);

			else if (sprayFunctionArrayDim2 == SWEEP_SPEED)
				getSweepSpeed(sprayFunctionArray, i,
					      sweepSpeed);

			else if (sprayFunctionArrayDim2 == DWELL_TIME)
				getDwellTime(sprayFunctionArray, i, dwellTime);


			sprayFunctionArrayDim2++;   //After an element is read, increment index
			i += currentLineIndex;      //Update i to the line index
			currentLineIndex = 0;       //Reset line index for next iteration of loop

			//If all 15 elements have been read in array
			if (sprayFunctionArrayDim2 == LAST_INDEX)
			{
				//Copy all data to position struct (Location: spray_positions.c)
				setPositionSweepPattern(currentPosition,
							sweepPattern);
				setPositionDwellPattern(currentPosition,
							dwellPattern);
				setPositionSweepSpeed(currentPosition,
						      sweepSpeed);
				setPositionDwellTime(currentPosition,
						     dwellTime);

				//Reset strings
				memset(dwellTime, 0, sizeof(dwellTime));
				memset(sweepSpeed, 0, sizeof(sweepSpeed));
				memset(sweepPattern, 0, sizeof(dwellPattern));
				memset(dwellPattern, 0, sizeof(dwellPattern));

				//Update Current Array position, and reset sprayFunctionArrayDim2
				currentPosition++;
				sprayFunctionArrayDim1++;
				sprayFunctionArrayDim2 = 0;
			}
		}
	}
	return;
}


/*Checks the line for a semicolon to see if the statement/declaration is over*/
static bool checkForStatementTerminator(char ch)
{
	if (ch == ';')
		return true;
	else
		return false;
}


/* Checks each line for RETURN, Move Commands, Zone Precision commands, and additional commands */
static void getDataFromSprayPositionsRoutine(char *currentLine)
{
	//If line isn't commented, read it
	if (!findWord(currentLine, "!"))
	{
		if (checkForReturn(currentLine))
		{
			doneReadingSprayPositionsRoutine = true;
			totalSprayPositions--;
		}
		else
		{
			getMoveType(currentLine);
			getZoneType(currentLine);
			getAdditionalCommands(currentLine);
		}
	}
	return;
}


/* Checks to see if a certain substring exists in the line */
static bool findWord(char *string, char *substring)
{
	if (strstr(string, substring) != NULL)
		return true;
	else
		return false;
}


/**********************************************************************
*   Takes a whole number, checks the '1' bits to determine which
*   Nozzles are turned on, then returns it as a string in readable format
*
*   EX: (input)2            (input) 255
*       (byte)00000010      (byte) 11111111
*       (output) 2          (output) 12345678
*
*   @param wholeNumber = The number representing the nozzle pattern
*   @param side = cover or ejector half, to determing the starting nozzle
*   @param pattern = The string that will be transfomed
**********************************************************************/
static void getNozzlePattern(int wholeNumber, int side, char *pattern)
{
	char nozzlePattern[9] = {0};
	int i, j = 0;
	int startingNozzle = 0;

	if (side == EJECTOR_HALF)
		startingNozzle = 2;

	for (i = 8; i > 0; i--)
	{
		if (wholeNumber & 1 << (i - 1))
		{
			nozzlePattern[j] = (i + startingNozzle) + '0';
			j++;
		}
	}

	reverseString(nozzlePattern);

	if (side == COVER_HALF)
		strcpy(pattern, nozzlePattern);
	else
		strcat(pattern, nozzlePattern);

	return;
}


/**********************************************************************
*   Takes a string as input, returns that same string reversed
*   Used to reverse the order a nozzle pattern to read from left to right
*   But also may be used to reverse any string
**********************************************************************/
static void reverseString(char *input)
{
	int i, j;
	int stringSize = strlen(input);
	char *output = malloc(sizeof(char) * stringSize + 1);

	memset(output, 0, stringSize + 1);

	for (i = stringSize, j = 0; i > 0; i--, j++)
		output[j] = input[i - 1];

	strcpy(input, output);
	free(output);

	return;
}


/**********************************************************************
*   Checks current line for 'MOVEJ', 'MOVEL', 'MOVEC' commands
*   If present, sets the movement type for the current spray position
*   Resets extra commands if we find a move command, which also
*   means we have found the next position in the function
**********************************************************************/
static void getMoveType(char *line)
{
	int i;
	char *moveType[] = {"MOVEJ", "MOVEL", "MOVEC"};

	for (i = 0; i < ARRAY_SIZE(moveType);
	i++)
	{
		if (findWord(line, moveType[i]))
		{
			commandNumberForPosition = 1;
			setPositionMoveType(totalSprayPositions - 1,
					    moveType[i]);
			break;
		}
	}

	return;
}


/**********************************************************************
*   Checks the current line for zone/fine commands
*   If present, sets the zone type for the current spray position
*   Since the zone type is the last data type we need on the line
*   I increment the totalSprayPositions counter once this is read
**********************************************************************/
static void getZoneType(char *line)
{
	int i;
	char *zoneType[] = {"FINE", "Z200", "Z150", "Z100", "Z80", "Z60", "Z50",
			    "Z40", "Z30", "Z20", "Z15", "Z10", "Z5", "Z1"};

	for (i = 0; i < ARRAY_SIZE(zoneType);
	i++)
	{
		if (findWord(line, zoneType[i]))
		{
			setPositionZoneType(totalSprayPositions - 1,
					    zoneType[i]);
			totalSprayPositions++;
			break;
		}
	}

	return;
}


/**********************************************************************
*   Checks the current line for other commands such as ->
*   Commands for cores in, blasters, etc
*   If present, it will put that line in the additional commands
*   Attribute for the current position
*   Since we may have more than 1 extra command for position, the
*   commandNumberForPosition will increment each time an extra command is found
**********************************************************************/
static void getAdditionalCommands(char *line)
{
	int i;
	char *otherCommands[] = {"PULSEDO", "SET", "RESET", "WAITDO", "WAITDI"};

	for (i = 0; i < ARRAY_SIZE(otherCommands);
	i++)
	{
		if (findWord(line, otherCommands[i]))
		{
			formatStatement(line);
			setPositionAdditionalCommands(totalSprayPositions - 1,
				line, commandNumberForPosition);
			commandNumberForPosition++;
			break;
		}
	}
	return;
}


/************************************************************************
*   Checks to see if the *RETURN statement is present in the line
*   If it is, decrement the total positions and return true
************************************************************************/
static bool checkForReturn(char *line)
{
	if (findWord(line, "RETURN"))
		return true;
	else
		return false;
}


/**********************************************************************
*   Gets the whole number that represents the *SWEEP* nozzle pattern
*   Breaks it down to binary, then flips it and formats it to read
*   as we would write it '1234'
**********************************************************************/
static void
getSweepPattern(char *line, int linePosition, int side, char *sweepPattern)
{
	int i;
	char temp[5] = {0};

	for (i = 0; line[linePosition + i] != ','; i++)
		temp[i] = line[i + linePosition];

	updateLineIndex(i);

	getNozzlePattern(atoi(temp), side, sweepPattern);

	return;
}


/**********************************************************************
*   Gets the whole number that represents the *DWELL* nozzle pattern
*   Breaks it down to binary, then flips it and formats it to read
*   as we would write it '1234'
**********************************************************************/
static void
getDwellPattern(char *line, int linePosition, int side, char *dwellPattern)
{
	//printf("Getting dwell pattern side %d\n", side);
	int i;
	char temp[5] = {0};

	for (i = 0; line[linePosition + i] != ','; i++)
		temp[i] = line[i + linePosition];

	updateLineIndex(i);

	getNozzlePattern(atoi(temp), side, dwellPattern);

	return;
}


/**********************************************************************
*   Starts at the current line position, reads it until it hits a comma
*   Then sets the sweep speed attribute for the current spray position
*   Updates the line position also
**********************************************************************/
static void getSweepSpeed(char *line, int linePosition, char *sweepSpeed)
{
	//printf("Getting sweep speed\n");
	int i;
	char temp[5] = {0};

	for (i = 0; line[linePosition + i] != ','; i++)
		temp[i] = line[i + linePosition];

	updateLineIndex(i);

	strcpy(sweepSpeed, temp);

	return;
}


/**********************************************************************
*   Starts at the current line position, reads it until it hits a comma
*   Then sets the dwell time attribute for the current spray position
*   Updates the line position also
**********************************************************************/
static void getDwellTime(char *line, int linePosition, char *dwellTime)
{
	//printf("Getting Dwell Time\n");
	int i;
	char temp[5] = {0};

	for (i = 0; line[linePosition + i] != ','; i++)
		temp[i] = line[linePosition + i];

	updateLineIndex(i);

	strcpy(dwellTime, temp);

	return;
}


/**********************************************************************
*   Updates the line position after a function has parsed the line
*   looking for information such as sweep speed, dwell time, etc
*   to keep up with the position in the array
*
*   ex: starting character for sweep speed may be 5,
*       but the value may be 5000, so we would need to update
*       the line position after the other 3 characters were read
**********************************************************************/
static void updateLineIndex(int counter)
{
	currentLineIndex += counter;
	return;
}


/******************************************************************
*   Takes a string as input, reads it, ignores the whitespace
*   until the first letter or number is read, then copies each
*   character into the result string until the either the statement
*   terminating character is read, or cr/lf is read.
*   every statement is terminated with a ';'
*   so should only be used for 1 line statements
******************************************************************/
static void formatStatement(char *string)
{
	int i;
	int j;
	int len = strlen(string);
	char ch;
	char carriageReturn = '\r';
	char lineFeed = '\n';
	char *result = malloc(sizeof(char) * len + 1);
	bool ignoreSpaces = true;

	memset(result, 0, len + 1);

	j = 0;
	for (i = 0; i < len; i++)
	{
		ch = string[i];

		//If for some reason we hit the end of line
		if ((ch == carriageReturn) || (ch == lineFeed))
			break;

		//Ignore whitespace until first character is reached
		if (isalpha(ch) || isdigit(ch))
			ignoreSpaces = false;
		else if (ch == ';')
			break;

		if (!ignoreSpaces)
		{
			result[j] = ch;
			j++;
		}

	}

	result[j] = '\0';

	strcpy(string, result);
	free(result);

	return;
}


int getTotalPositions(void)
{
	return totalSprayPositions;
}


/* Global function that is called by main */
void getDataFromRapidSrcFile(void)
{
	openSrcFile();
	readSrcFile();
	closeSrcFile();
	return;
}

/* Opens the RAPID source file for reading */
static void openSrcFile(void)
{
	fp = fopen(RAPID_FILEPATH, "r");

	if (fp == NULL)
	{
		perror("Error while opening the file\n");
		exit(EXIT_FAILURE);
	}
}


/* Closes the RAPID source file */
static void closeSrcFile()
{
	printf("CLOSING RAPID SOURCE FILE\n");
	fclose(fp);
}