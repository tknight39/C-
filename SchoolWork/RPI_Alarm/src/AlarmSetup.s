

.text 

/**************************************************************
 ! Return value of *loggedIn* integer variable
 **************************************************************/
.global GetLoginStatus
GetLoginStatus:

    LDR R0, =loggedIn
    LDR R0, [R0]
    BX LR
/**************************************************************/



/**************************************************************
 ! If user is not logged in, return
 ! If user is logged in, see if system is armed
 ! If system is armed, disarm it, otherwise arm the system
 ! Return 1/0 as a success/fail flag
 **************************************************************/
.global ArmDisarm
ArmDisarm:

    STMFD SP!, {LR}             // Save LR before branch

    LDR R0, =loggedIn           // R0 = &LoginStatus
    LDR R1, [R0]                // R1 = LoginStatus
    CMP R1, #1                  // LoginStatus == 1?
    BNE E_ArmDisarm             // User not logged in? Return


    LDR R0, =armed              // R0 = &LoginStatus
    LDR R1, [R0]                // R1 = LoginStatus
    CMP R1, #0                  // ArmedStatus = 0?
    BNE DisarmSystem            // ArmedStatus != 0? Disarm 

    ArmSystem:
        MOV R1, #1              // R1 = 1
        STR R1, [R0]            // ArmedStatus = 1

        BL SetupAlarmProcess    // SetupAlarmProcess()
        BAL E_ArmDisarm           // GOTO exit

    DisarmSystem:
        MOV R1, #0              // R1 = 0
        STR R1, [R0]            // ArmedStatus = 0
        BAL E_ArmDisarm
        
    E_ArmDisarm:
    LDR R0, =armed  
    LDR R0, [R0]           
    
    LDMFD SP!, {PC}         // Restore program counter
    MOV PC, LR              // Return
/**************************************************************/


/**************************************************************/
/**************************************************************/
.global StringCpy
StringCpy:
    
/**************************************************************/
/**************************************************************/
/**************************************************************/
/**************************************************************/
/**************************************************************/
/**************************************************************/


/**************************************************************/
.data
    .global armed
        armed: .word 0

    .global loggedIn
        loggedIn: .word 0

/**************************************************************/

.end
