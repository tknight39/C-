/*******************************************************************************
 * Title: CSV_Writer
 * Author: Tyler D Knight
 * Date: 7/4/2019
 *
 * Purpose: Writes all of the data collected from the user, and the Rapid
 * Source code file to the "sprayData.csv" file.
 ******************************************************************************/


#include <stdio.h>
#include <stdlib.h>

#include "User_Interface.h"
#include "Spray_Positions.h"
#include "Rapid_Parser.h"

#define CSV_FILEPATH "dependencies\\sprayData.csv"

static FILE* fp;

void writeDataToCsv();
static void openCsvFile();
static void closeCsvFile();

void writeDataToCsv()
{
	openCsvFile();
	writeJobInfo(fp);
	writeSprayData(getTotalPositions(), fp);
	closeCsvFile();
}


static void openCsvFile()
{
	fp = fopen (CSV_FILEPATH, "w");

	if (fp == NULL)
	{
		perror ("Error while opening the file\n");
		exit (EXIT_FAILURE);
	}
}

static void closeCsvFile()
{
	fclose(fp);
}