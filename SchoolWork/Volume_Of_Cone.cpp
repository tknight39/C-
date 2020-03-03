/***************************************************************
 * Title:  Chapter 3 Homework
 * Class:  CISP 1010
 * Author: Tyler Knight
 * Date:   1/24/20
 *
 * Description: Compute and output the volume of a cone
 *              given the diameter of it's base and height.
 *              formula: ((1/3)*pi)*radius^2)*height))
 **************************************************************/

#include <iostream>         // For cout, cin, endl
#include <iomanip>          // For showpoint


using namespace std;


// Prototypes
float CalculateVolumeOfCone(float base, float height);
void GetConeData(float* base, float* height);



int main(void)
{
    float base = 0;
    float height = 0;

    GetConeData(&base, &height);
    
    cout << "The volume of a cube with a base of " << base << " and a height of " << height 
         << " is: " << (int)CalculateVolumeOfCone(base, height) << endl;

    return 0;
}



/*********************************************
 * Return the volume of a cone given
 * the base and height of the cone using
 * the formula:
 * V = (1/3) * PI * (Radius^2) * Height
 ********************************************/
float CalculateVolumeOfCone(float base, float height)
{
    const float PI = 3.14159;
    float radius = base / 2;
    return (1.0/3.0) * PI * (radius * radius) * height;
}



/*************************************************
 * Gets the base and height data for a cone from
 * the user.
 * @ param base: Addr to store base value
 * @ param height: Addr to store height value
 ************************************************/
void GetConeData(float *base, float *height)
{
    cout << "Enter the base of the cone: " << endl;
    cin >> *base;

    cout << "Enter the height of the cone: " << endl;
    cin >> *height;
    return;
}
