/*****************************************************
  Title:       Chapter 6 Homework

  Author:      Tyler Knight

  Date:        2/29/20

  Class:       CISP1010
 
  Description: 
  ! Calculate the standard deviation of all scores 
    in scores.dat. 
 
  ! Print the result to the console.
 
 
 *****************************************************/

#include <fstream>      // For file I/O
#include <iostream>     // For cin, cout, endl
#include <cmath>        // For Pow(), Sqrt()
#include <iomanip>      // For formatting number output

using namespace std;    // Get rid of std::



// Prototypes
static void GetData(float scores[], float* sum, int* sampleSize);
static void CalcSD(float data[], float mean, float* sDev, int arrSize);





int main(void)
{
    float sum = 0, mean = 0, sDev = 0;
    float scores[100] = { 0x0 };
    int sampleSize = 0;
 

    GetData(scores, &sum, &sampleSize);
    CalcSD(scores, mean = (sum / sampleSize), &sDev, sampleSize);

    cout << "Mean =\t\t\t" << setprecision(6) << mean << endl;
    cout << "Standard Deviation =\t" << setprecision(6) << sDev << endl;

    return 0;
}





/*******************************************************************
    ! Get scores from .datfile and update values of 
      scores[], sum, and totalScores

    @param  scores[] Array to hold score values
    @param  *sum = Holds the sum off all scores in file
    @param  *totalScores = Holds the number of scores in file
*******************************************************************/
static void GetData(float scores[], float* sum, int* sampleSize)
{
    const string FP = "scores.dat";
    ifstream inData;
    float currentValue = 0;

    inData.open(FP.c_str());

    *sampleSize = 0;
    while (inData >> currentValue)
    {
        scores[*sampleSize] = currentValue;
        *sum += currentValue;
        *sampleSize += 1;
    }

    inData.close();
    return;
}




/*******************************************************************
    ! Calculate Standard Deviation of values in data array
      and store it int *sDev ptr

    @param  data[]:     Holds all scores from file
    @param  mean:       Average of all scores in data array
    @param  *sDev:      Holds value of standard deviation
    @param  arrSize:    Size of data array, used for looping   
*******************************************************************/
static void CalcSD(float data[], float mean, float* sDev, int arrSize)
{
    for (int i = 0; i < arrSize; i++)
        *sDev += pow((data[i] - mean), 2);
    
    *sDev = sqrt(*sDev / arrSize);
    return;
}


