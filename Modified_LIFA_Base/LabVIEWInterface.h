/*********************************************************************************
 **
 **
 **  LVFA_Firmware - Provides Functions For Interfacing With The Arduino Uno
 **
 **  Written By:    Sam Kristoff - National Instruments
 **  Written On:    November 2010
 **  Last Updated:  Dec 2011 - Kevin Fort - National Instruments
 **
 **  This File May Be Modified And Re-Distributed Freely. Original File Content
 **  Written By Sam Kristoff And Available At www.ni.com/arduino.
 **
 *********************************************************************************/


/*********************************************************************************
**  Define Constants
**
**  Define directives providing meaningful names for constant values.
*********************************************************************************/

#define FIRMWARE_MAJOR 02        
#define FIRMWARE_MINOR 00  
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
#define DEFAULTBAUDRATE 9600    // Defines The Default Serial Baud Rate (This must match the baud rate specifid in LabVIEW)
#else
#define DEFAULTBAUDRATE 115200
#endif
#define MODE_DEFAULT 0            // Defines Arduino Modes (Currently Not Used)
#define COMMANDLENGTH 15          // Defines The Number Of Bytes In A Single LabVIEW Command (This must match the packet size specifid in LabVIEW)
#define STEPPER_SUPPORT 1         // Defines Whether The Stepper Library Is Included - Comment This Line To Exclude Stepper Support


// Declare Variables
unsigned char currentCommand[COMMANDLENGTH];    // The Current Command For The Arduino To Process
//Globals for continuous aquisition
unsigned char acqMode;
unsigned char contAcqPin;
float contAcqSpeed;
float acquisitionPeriod;
float iterationsFlt;
int iterations;
float delayTime;


/*********************************************************************************
**  syncLV
**
**  Synchronizes with LabVIEW and sends info about the board and firmware (Unimplemented)
**
**  Input:  None
**  Output: None
*********************************************************************************/
void syncLV();
/*********************************************************************************
**  checkForCommand
**
**  Checks for new commands from LabVIEW and processes them if any exists.
**
**  Input:  None
**  Output: 1 - Command received and processed
**          0 - No new command
*********************************************************************************/
int checkForCommand(void);

/*********************************************************************************
**  processCommand
**
**  Processes a given command
**
**  Input:  command of COMMANDLENGTH bytes
**  Output: 1 - Command received and processed
**          0 - No new command
*********************************************************************************/
void processCommand(unsigned char command[]);

//ADDED 3 from
/*********************************************************************************
**  finiteAcquisitionMult
**
**  Returns the number of samples specified at the rate specified, from the ports specified.
**
**  Input:  pins to sampe on, speed to sample at, number of samples
**  Output: void
*********************************************************************************/
void finiteAcquisitionMult(int analogPins[], float acquisitionSpeed, int numberOfSamples, int pinAmount);
//ADDED 3 to
