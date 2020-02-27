/*******************************************************************************
* Title: spray_positions.c
*
* Author: Tyler Knight
*
* Date: 7/4/2019
*
* Purpose:
*   1) Stores sprayPosition struct/object
*   2) Stores sprayPositions struct array
*   3) Sets all data for spray position objects
*   4) Prints all spray position objects for debugging
*   5) Writes spray position attributes to CSV file
*
*
*
* Note: See the spray_positions.h header file
*       for info about the functions used here
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Data Structure for a spray position
struct sprayPosition
{
    char sweepPattern[10];
    char dwellPattern[10];
    char movementType[7];
    char zoneType[5];
    char additionalCommands1[100];
    char additionalCommands2[100];
    char additionalCommands3[100];
    char additionalCommands4[100];
    char additionalCommands5[100];
    char sweepSpeed[5];
    char dwellTime[5];
};
//Array of 80 spray position structs
struct sprayPosition sprayPositions[80] = {0};


/* Sets the move type of position (moveJ, moveL, moveC */
void setPositionMoveType(int positionNumber, char *movementType)
{
	strcpy(sprayPositions[positionNumber].movementType, movementType);
}

/* Sets the zone type to specified position */
void setPositionZoneType(int positionNumber, char *zoneType)
{
	strcpy(sprayPositions[positionNumber].zoneType, zoneType);
}


/* Updates additional command attribute (used in rapid_parser.c) */
void setPositionAdditionalCommands(int positionNumber, char *additionalCommands,
				   int commandNumber)
{
	switch (commandNumber)
	{
		case 1:
			strcpy(sprayPositions[positionNumber].additionalCommands1,
			       additionalCommands);
			break;
		case 2:
			strcpy(sprayPositions[positionNumber].additionalCommands2,
			       additionalCommands);
			break;
		case 3:
			strcpy(sprayPositions[positionNumber].additionalCommands3,
			       additionalCommands);
			break;
		case 4:
			strcpy(sprayPositions[positionNumber].additionalCommands4,
			       additionalCommands);
			break;
		case 5:
			strcpy(sprayPositions[positionNumber].additionalCommands5,
			       additionalCommands);
			break;
	}
}


/* Sets the nozzle pattern for specified position ex:(1234), (12345678) */
void setPositionSweepPattern(int positionNumber, char *sweepPattern)
{
	strcpy(sprayPositions[positionNumber].sweepPattern, sweepPattern);
}


/* Sets the dwell time for the specified position */
void setPositionDwellPattern(int positionNumber, char *dwellPattern)
{
	strcpy(sprayPositions[positionNumber].dwellPattern, dwellPattern);
}

/* Sets the movement speed of robot to specified position */
void setPositionSweepSpeed(int positionNumber, char *sweepSpeed)
{
	strcpy(sprayPositions[positionNumber].sweepSpeed, sweepSpeed);
}

/* Sets the wait time of robot at specified position */
void setPositionDwellTime(int positionNumber, char *dwellTime)
{
	strcpy(sprayPositions[positionNumber].dwellTime, dwellTime);
}

////////////////////////////////////////////////////////////////////////////////

//Used for debugging
void printArrayDataByPosition(int position)
{
	int i;
	printf("PRINT ARRAY DATA BY POSITION\n");

	for (i = 0; i < position; i++)
	{
		printf("POSITION %d SWEEP PATTERN: %s\n", i + 1,
		       sprayPositions[i].sweepPattern);
		printf("POSITION %d DWELL PATTERN: %s\n", i + 1,
		       sprayPositions[i].dwellPattern);
		printf("POSITION %d MOVE TYPE: %s\n", i + 1,
		       sprayPositions[i].movementType);
		printf("POSITION %d ZONE TYPE: %s\n", i + 1,
		       sprayPositions[i].zoneType);
		printf("POSITION %d SWEEP SPEED: %s\n", i + 1,
		       sprayPositions[i].sweepSpeed);
		printf("POSITION %d DWELL TIME: %s\n", i + 1,
		       sprayPositions[i].dwellTime);
		printf("POSITION %d ADDITIONAL COMMAND 1: %s\n", i + 1,
		       sprayPositions[i].additionalCommands1);
		printf("POSITION %d ADDITIONAL COMMAND 2: %s\n", i + 1,
		       sprayPositions[i].additionalCommands2);
		printf("POSITION %d ADDITIONAL COMMAND 3: %s\n", i + 1,
		       sprayPositions[i].additionalCommands3);
		printf("POSITION %d ADDITIONAL COMMAND 4: %s\n", i + 1,
		       sprayPositions[i].additionalCommands4);
		printf("POSITION %d ADDITIONAL COMMAND 5: %s\n", i + 1,
		       sprayPositions[i].additionalCommands5);
		printf("**********************************\n");
	}
	system("pause");
}


/*******************************************************************************
*   Takes the total number of spray positions in use
*   and the file pointer as input
*   Then writes all of the spray data to a csv file
*******************************************************************************/
void writeSprayData(int totalSprayPositions, FILE *fp)
{
	int i;
	char *currentLine = malloc(sizeof(char) * 1000);

	memset(currentLine, 0, 1000);

	for (i = 0; i < totalSprayPositions; i++)
	{
		fprintf(fp, "POSITION %d,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
			i + 1, sprayPositions[i].sweepPattern,
			sprayPositions[i].dwellPattern,
			sprayPositions[i].sweepSpeed,
			sprayPositions[i].dwellTime,
			sprayPositions[i].movementType,
			sprayPositions[i].zoneType,
			sprayPositions[i].additionalCommands1,
			sprayPositions[i].additionalCommands2,
			sprayPositions[i].additionalCommands3,
			sprayPositions[i].additionalCommands4,
			sprayPositions[i].additionalCommands5);
	}

	free(currentLine);
}