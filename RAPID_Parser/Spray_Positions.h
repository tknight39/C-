/*******************************************************************************
*   The functions in this module are used
*   to set data for a spray position struct
*   There are 80 structures created, since
*   there are a max of 80 spray positions.
*
*   @param positionNumber is the current
*   spray position to be updated
*
*   @param movement type is the type of move
*   used in that position, L,J,C
*
*   @param zoneType is the type of zone used
*   in the position, FINE,Z1-100
*
*   @param additionalCommands is used to
*   store other commands associated with a certain
*   position such as SET, RESET, PULSDO etc
*
*   @param sweepPattern is the formatted version
*   of the binary byte that tells us which nozzles
*   are turned on during the sweep function for the
*   specified position.
*   Example: *0011* would translate to *12* and *12*
*   would be the pattern used
*
*   @param dwellPattern is the same as the sweepPattern,
*   but is used to show which nozzles are on during the
*   dwell function of the specified position
*
*   @param sweepSpeed is how fast the robot is moving
*   to the specified position
*
*   @param dwellTime is how long the robot stays
*   at the specified position before moving to the
*   next positon
*******************************************************************************/

void setPositionMoveType(int positionNumber, char* movementType);
void setPositionZoneType(int positionNumber, char* zoneType);
void setPositionAdditionalCommands(int positionNumber, char* additionalCommands, int commandNumber);
void setPositionSweepPattern(int positionNumber, char* sweepPattern);
void setPositionDwellPattern(int positionNumber, char* dwellPattern);
void setPositionSweepSpeed(int positionNumber, char* sweepSpeed);
void setPositionDwellTime(int positionNumber, char* dwellTime);
void writeSprayData(int totalSprayPositions, FILE* fp);


/* Used for debugging only, prints all data for each position that is used */
void printArrayDataByPosition(int position);
