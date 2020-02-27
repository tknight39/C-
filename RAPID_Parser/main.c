/*******************************************************************************
 * Title: Walker Spray Documentor
 *
 * Author: Tyler Knight
 * Date: 6/26/2019
 * Purpose: Document important data from spray program
 *
 * Version: 1.0
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "User_Interface.h"     // getDataFromUser() here
#include "Rapid_Parser.h"       // getDataFromRapidSrcFile() here
#include "CSV_Writer.h"         // writeDataToCsv() here


int main(void)
{
	getDataFromUser();
	getDataFromRapidSrcFile();
	writeDataToCsv();
	return 0;
}

