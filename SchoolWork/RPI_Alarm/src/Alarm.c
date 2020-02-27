
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "Alarm.h"
#include "ARM.h"



// Private Function Prototypes
static int PasswordIsCorrect(char* pswAttempt);
static void *motion(void *flag);
void SetupAlarmProcess(void);

// Global Variables
extern int armed;
extern int loggedIn;

static const char PASSWORD[] = "123";


/*************************************
 * Checks to see if psw user
 * provided is correct
 ************************************/
static int PasswordIsCorrect(char* pswAttempt)
{
    return(!strcmp(pswAttempt, PASSWORD));    
}



/*******************************
 * ! Takes in string ptr,
 * ! Changes string value
 * ! Used to update system -
 *     status label on GUI
 ******************************/
void GetSysStat(char* sysStatus)
{
    if (armed && loggedIn)
        strcpy(sysStatus, "ARMED, LOGGED IN");
    else if (armed && !loggedIn)
        strcpy(sysStatus, "ARMED, NOT LOGGED IN");
    else if (!armed && loggedIn)
        strcpy(sysStatus, "DISARMED, LOGGED IN");
    else
        strcpy(sysStatus, "DISARMED, NOT LOGGED IN");
    
    return;
}




/********************************
 * Arms/Disarms the system
 * Returns the armed status
 *******************************/
/*int ArmDisarm(void)
{
    armed = (loggedIn && !armed);
    if (armed) SetupAlarmProcess(); 
    printf("Assembly Return: %d\n", AlarmSetup());   
    return armed;
}*/


/*******************************
 * Update and return
 * the loggedIn status
 ******************************/
int LoginLogout(char* pswAttempt)
{
    return (loggedIn = PasswordIsCorrect(pswAttempt));
}

// Return LoginStatus
//int GetLoginStatus(void)
//{
    //return (loggedIn);
//}



/****************************
 * Create a thread to 
 * watch for motion, armed
 * is used as the exit flag
 ***************************/
void SetupAlarmProcess(void)
{
    pthread_t thread1;
    pthread_create(&thread1, NULL, motion, &armed);
    return;
}


/* */
static void *motion(void *flag)
{
    int *exitFlag = (int *) flag;

    while(*exitFlag != 0)
    {
        printf("Status: %d\n", armed);
    }

    printf("Status: %d\n", armed);
    return 0;
}


