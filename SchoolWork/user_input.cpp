/*****************************************************
 * Title:       Chapter 5 Homework
 * Author:      Tyler Knight
 * Date:        2/11/2020
 * Class:       CISP1010
 *
 * Description: 
 *  ! This program prompts the user to enter a number
 *      between 1 and 12, where each number
 *      represents a month in the year.
 *  ! After the user input is 
 *      validated, print the corresponding month
 *      to the console.
 *
 *****************************************************/

#include <iostream>         // For Cout, Cin

using namespace std;        // Get rid of std::


// Prototypes
void GetNumInput(int* ptr);
void DisplayErrMsg(int errNo);
void DisplayInstructions(void);
void DisplayMatchingMonth(int monthNo);
int ValidateNumRange(int min, int max, int value);






int main(void)
{
    int month = 0;

    DisplayInstructions();
    GetNumInput(&month);
    DisplayMatchingMonth(month);
    
    return 0;
}






/**********************************************
 * ! Take in a pointer to an integer
 * ! Get input from user
 * ! Validate that the input is a number
 * ! Check the range of that number
 * ! If input is ok, return. 
 * ! Else, show error msg and try again
 *********************************************/
void GetNumInput(int* ptr)
{
    while (1)
    {
        cout << "Input --->";
        cin >> *ptr;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits <streamsize> ::max(), '\n');
            DisplayErrMsg(1);
        }
        else if (!ValidateNumRange(1, 12, *ptr))
            DisplayErrMsg(2);
        else
            break;
    }

    return;
}





/**************************************
 * ! Take an integer as input,
 * ! Output the corresponding month
 *************************************/
void DisplayMatchingMonth(int monthNo)
{
    const string MONTHS[12] = { "January", "February", "March", "April",
        "May", "June", "July", "August", "September",
        "October", "November", "December" };

    cout << MONTHS[monthNo - 1] << endl;

    return;
}




/***************************************************
 *  ! Return 0 if value isn't in the min/max range
 *  ! Else, return 1 (value is in range)
 **************************************************/
int ValidateNumRange(int min, int max, int value)
{
    return (value < min) || (value > max) ?  0 : 1;
}




/************************************
 * ! Take an error number as input,
 * ! Display corresponding error msg
 ***********************************/
void DisplayErrMsg(int errNo)
{

    switch (errNo)
    {
        case 1:
            cout << "You didn't enter a number" << endl;
            break;
        case 2:
            cout << "Input out of range" << endl;
            break;
        default:
            cout << "Unknown error number" << endl;
    }

    return;
}





/* Show instructions to user */
void DisplayInstructions(void)
{
    string monthList =
        "    ~Example~\n"
        "------------------\n"
        "Jan\t\t1\nFeb\t\t2\n"
        "Mar\t\t3\nApr\t\t4\n"
        "May\t\t5\nJun\t\t6\n"
        "Jul\t\t7\nAug\t\t8\n"
        "Sept\t\t9\nOct\t\t10\n"
        "Nov\t\t11\nDec\t\t12\n"
        "------------------\n";


    cout << "Enter a number between 1 and 12 "
         << "to display the corresponding month\n"
         << monthList << endl;

    return;
}




