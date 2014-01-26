/*********************************************************************************
 **
 ** Includes.
 **
 ********************************************************************************/ 
// Standard includes.  These should always be included.

#include "LabVIEWInterface.h" 

/*********************************************************************************
 **  setup()
 **
 **  Initialize the Arduino and setup serial communication.
 **
 **  Input:  None
 **  Output: None
 *********************************************************************************/
void setup()
{  
  // Initialize Serial Port With The Default Baud Rate
  syncLV();

  // Place your custom setup code here
  
}

/*********************************************************************************
 **  loop()
 **
 **  The main loop.  This loop runs continuously on the Arduino.  It 
 **  receives and processes serial commands from LabVIEW.
 **
 **  Input:  None
 **  Output: None
 *********************************************************************************/
void loop()
{   
  // Check for commands from LabVIEW and process them.   
 
  checkForCommand();
  // Place your custom loop code here (this may slow down communication with LabVIEW)
  
  
  if(acqMode==1)
  {
    //sampleContinously();
  }

}


