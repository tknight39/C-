/*****************************************************
 * Title:       Chapter 4 Homework
 *
 * Author:      Tyler Knight
 *
 * Date:        2/8/2020
 *
 * Class:       CISP1010
 *
 * Description:
 *  ! Prompt user for the percentage of the moon.
 *  ! Calculate the surface area of the illuminated
 *    area using the value given by the user as
 *    a parameter.
 *
 *****************************************************/


#include <fstream>      // For file I/O
#include <iostream>     // For cin, cout, endl
#include <cmath>        // For Pow()
#include <iomanip>      // For formatting number output



using namespace std;



//Prototypes
float GetIllumPercentage(void);
float CalcIllumSurfArea(float percent);
void StoreMoonCalcData(float percent, float result);
float Int2Percent(int val);
int Percent2Int(float val);




int main(void)
{
    float percentIlluminated = 0, surfaceArea = 0;

    percentIlluminated = GetIllumPercentage();
    surfaceArea = CalcIllumSurfArea(percentIlluminated);

    StoreMoonCalcData(percentIlluminated, surfaceArea);

    return 0;
}




/*************************************
 * Prompt the user to enter a float
 * value, then return the value/100
 * ! Div by 100 to shift decimal
 *   2 places left on a whole number
 *   ex: 100% -> 1.00
 ************************************/
float GetIllumPercentage(void)
{
    float output;

    cout << "Enter a whole number for the percentage of the moon that is illuminated\n" <<
        "ex: for 98%, enter 98\nInput: %";
    cin >> output;

    return (Int2Percent(output));
}




/*******************************************
 * Takes a float as input then
 * calculates and returns the surface
 * area of the percentage.
 *
 * Formula used for surface area:
 * S = (2 * (R^2)) * (PI * percent)
 *
 * S = Surface Area
 * R = Radius squared
 * PI = 3.14159
 * R^2 = Radius of moon (1738.3)
 *
 * @ param percent: Percentage of moon that
 *   is illuminated
 ******************************************/
float CalcIllumSurfArea(float percent)
{
    const float PI = 3.14159;
    const float MOON_DIAMETER = pow(1738.3, 2);


    return ((2 * (MOON_DIAMETER)) * (PI * percent));
}




/************************************************
 * Takes percentage and surface area as input
 * and writes them to a file
 ***********************************************/
void StoreMoonCalcData(float percentage, float surfaceArea)
{
    ofstream outData;
    string fileName = "MoonData.out";

    outData.open("MoonData.out");

    outData << "User input for illuminated percentage of moon: %"
        << Percent2Int(percentage) << endl;

    outData << "Surface area of illuminated area: "
        << fixed << setprecision(1) << surfaceArea << "km^2" << endl;

    outData.close();

    return;
}



/******************************************
 * Takes a whole number as input and
 * divides it by 100, moving the decimal
 * 2 positions to the left --> 100 = .1
 *****************************************/
float Int2Percent(int val)
{
    return (val / 100);
}



/********************************************
 * Takes a whole number as input and
 * multiplies it by 100, moving the decimal
 * 2 positions to the right --> .1 = 100
 *******************************************/
int Percent2Int(float val)
{
    return (val * 100);
}
