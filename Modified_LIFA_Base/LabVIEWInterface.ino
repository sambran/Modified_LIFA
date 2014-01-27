/*********************************************************************************
 **
 **  LVIFA_Firmware - Provides Functions For Interfacing With The Arduino Uno
 **
 **  Written By:    Sam Kristoff - National Instruments
 **  Written On:    November 2010
 **  Last Updated:  Dec 2011 - Kevin Fort - National Instruments
 **
 **  This File May Be Modified And Re-Distributed Freely. Original File Content
 **  Written By Sam Kristoff And Available At www.ni.com/arduino.
 **
 *********************************************************************************/
 
 // Variables

unsigned int retVal;
int sevenSegmentPins[8];
int currentMode;
unsigned int freq;
unsigned long duration;
int i2cReadTimeouts = 0;
char spiBytesToSend = 0;
char spiBytesSent = 0;
char spiCSPin = 0;
char spiWordSize = 0;
byte customChar[8];
unsigned long IRdata;

int checkForCommand(void)
{  

  int bufferBytes = Serial.available();

  if(bufferBytes >= COMMANDLENGTH) 
  {
    // New Command Ready, Process It  
    // Build Command From Serial Buffer
    for(int i=0; i<COMMANDLENGTH; i++)
    {
      currentCommand[i] = Serial.read();       
    }     
    processCommand(currentCommand);     
    return 1;
  }
  else
  {
    return 0; 
  }
}

// Processes a given command
void processCommand(unsigned char command[])
{  
  // Determine Command
  if(command[0] == 0xFF && checksum_Test(command) == 0)
  {
    switch(command[1])
    {    
    /*********************************************************************************
    ** LIFA Maintenance Commands
    *********************************************************************************/
    case 0x00:     // Sync Packet
      Serial.print("sync");
      Serial.flush();        
      break;
    case 0x01:    // Flush Serial Buffer  
      Serial.flush();
      break;
    //ADDED 1 from
    /*********************************************************************************
    ** Finite Aquisition on Multiple Ports
    *********************************************************************************/
    case 0x35:// Perform Finite Aquisition on Multiple Ports
    {
          int pins[16]={0};//TODO switch to a defined constant
          Serial.write('0');
          finiteAcquisitionMult(pins,(command[3])+(command[4]<<8),command[5]+(command[6]<<8));
       break; 
    }
       
    //ADDED 1 to
    /*********************************************************************************
    ** Unknown Packet
    *********************************************************************************/
    default:      // Default Case
      Serial.flush();
      break;     
    }
  }
  else{  
    // Checksum Failed, Flush Serial Buffer
    Serial.flush(); 
  }   
}
// Synchronizes with LabVIEW and sends info about the board and firmware (Unimplemented)
void syncLV()
{
  Serial.begin(DEFAULTBAUDRATE); 
  i2cReadTimeouts = 0;
  spiBytesSent = 0; 
  spiBytesToSend = 0;
  Serial.flush();
}
// Compute Packet Checksum
unsigned char checksum_Compute(unsigned char command[])
{
  unsigned char checksum;
  for (int i=0; i<(COMMANDLENGTH-1); i++)
  {
    checksum += command[i]; 
  }
  return checksum;
}
// Compute Packet Checksum And Test Against Included Checksum
int checksum_Test(unsigned char command[])
{
  unsigned char checksum = checksum_Compute(command);
  if(checksum == command[COMMANDLENGTH-1])
  {
    return 0; 
  }
  else
  {
    return 1;
  }
}

//ADDED 2 from
void finiteAcquisitionMult(int analogPins[], float acquisitionSpeed, int numberOfSamples)
{
  //want to exit this loop every 8ms
   acquisitionPeriod=1/acquisitionSpeed;
   
  for(int i=0; i<numberOfSamples; i++)
  {
     retVal = analogRead(analogPins[0]);
    
     if(acquisitionSpeed>1000)
     {
       Serial.write( (retVal >> 2));
       delayMicroseconds(acquisitionPeriod*1000000);
     }
     else
     {
       Serial.write( (retVal & 0xFF) );
       Serial.write( (retVal >> 8));
       delay(acquisitionPeriod*1000);
     }
  }
}
//ADDED 2 to

