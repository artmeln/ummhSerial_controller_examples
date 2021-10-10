#include "ushreserved.h"

char* pDeviceDescriptions[] = 
  { "Name|Shutter-A",
    "Description|An example shutter (A)",
    "Timeout|1000.0",
    "Command|SetOpen|SO",
    "Command|GetOpen|cashed",
    "Command|Fire|not supported",
    "PropertyFloatAction|SetFloat|0.0|false|SF|false|0.0:2.5",
    "PropertyIntegerAction|SetInteger|0|false|SI|false|0:5",
    "PropertyStringAction|SetString|A|false|SS|false|A:B:C:D:E:F",
    "PropertyFloatAction|DelayResetTimeout|0.0|false|DL2|false|0.0:3.0",
    "PropertyFloatAction|ReduceBy0.1|0.0|false|RB0.1|false|0.0:2.5",
    "Name|Shutter-B",
    "Description|An example shutter (B)",
    "Timeout|1000.0",
    "Command|SetOpen|SO",
    "Command|GetOpen|cashed",
    "Command|Fire|not supported",
    "PropertyFloatAction|Voltage|0.0|false|VLT|false|0.0:5.0",
    "Name|State-A",
    "Description|First state device",
    "Timeout|1000.0",
    "PropertyIntegerAction|State|1|false|SST|false|0:5",
    "PropertyInteger|ClosedPosition|3|false|2:5",
    "PropertyStringAction|Label|One|false|LBL|false|0-One:1-Two:2-Three:3-Four:4-Five:5-Six",
    "Name|Stage-A",
    "Description|An example stage (A)",
    "Timeout|1000.0",
    "Command|SetPositionUm|SP",
    "Command|GetPositionUm|cashed",
    "Command|Home|HM",
    "Command|Stop|STOP",
    "PropertyFloatAction|Position|0.0|false|SP|false|0.0:20000.0",
    "PropertyStringAction|Mode|Standard|false|MD|false|Standard:Fast",
    "Name|XYStage-A",
    "Description|An example XYstage (A)",
    "Timeout|1000.0",
    "Command|SetPositionUm|SP",
    "Command|GetPositionUm|cashed",
    "Command|Home|HM",
    "Command|Stop|STOP",
    "PropertyFloatAction|PositionX|0.0|false|SP|false|0.0:30000.0",
    "PropertyFloatAction|PositionY|0.0|false|SP|false|0.0:40000.0",
    "PropertyStringAction|Movement|Slow|false|MD|false|Slow:Normal:Fast",
    "End"
  };

size_t maxLength = 128;
char cmdIn[128];
char strDevice[20];
char strCommand[20];
char strSingleValue[9];
size_t ssCmdIn;
int dd=0; // counter over devices

char* strDefaultTimeout = "1000";

void setup() {
  Serial.begin(115200);
}

void ReadSerialCommand() {
  size_t ss; // counter within a string
  char chIn;
  bool newcmd=false;

  ss = 0;
  while (Serial.available() > 0) {
    chIn = char(Serial.read());
    if (chIn==ushwords::sepEnd) {
      newcmd = true;
      break;
    } else {
      cmdIn[ss] = chIn;
      ss++;
      delay(2);
    }
  }
  if (newcmd) {
    cmdIn[ss] = '\0';
  } else {
    cmdIn[0] = '\0';
  }
  ssCmdIn = 0;
}

void GetDeviceFromCmdIn(char sep)
{
  size_t ssWord=0;
  while (cmdIn[ssCmdIn]!=sep) {
    strDevice[ssWord] =  cmdIn[ssCmdIn];
    ssCmdIn++;
    ssWord++;
  }
  strDevice[ssWord] = '\0';
  ssCmdIn++;
}

void GetCommandFromCmdIn(char sep)
{
  size_t ssWord = 0;
  while (cmdIn[ssCmdIn]!=sep) {
    strCommand[ssWord] =  cmdIn[ssCmdIn];
    ssCmdIn++;
    ssWord++;
  }
  strCommand[ssWord] = '\0';
  ssCmdIn++;
}

void GetNextValue(char sep)
{
  size_t ss=0;
  while (ssCmdIn<strlen(cmdIn)) {
    if (cmdIn[ssCmdIn]==sep) {
      break;
    } else {
      strSingleValue[ss] = cmdIn[ssCmdIn];
      ssCmdIn++;
      ss++;
    }
  }
  strSingleValue[ss] = '\0';
  ssCmdIn++;
}

void MakeAndSendOutputCommand(char* deviceName, char* deviceCmd, int err, char* values[], int nvalues) {
  Serial.print(deviceName);
  Serial.print(ushwords::sepIn);
  Serial.print(deviceCmd);
  Serial.print(ushwords::sepIn);
  Serial.print(err);
  if (nvalues>0) {
    Serial.print(ushwords::sepWithin);
    for (int ii=0; ii<nvalues-1; ii++) {
      Serial.print(String(values[ii]));
      Serial.print(ushwords::sepWithin);
    }
    Serial.print(String(values[nvalues-1]));
  }
  Serial.print(ushwords::sepEnd);
}

void loop() {

  if (Serial.available() > 0) {
    
    ReadSerialCommand();

    if (strcmp(ushwords::device_list_start,cmdIn)==0) { // take care of special commands first
      dd = 0;
      Serial.print(pDeviceDescriptions[dd]);
      Serial.print(ushwords::sepEnd);
      dd++;
    } else if (strcmp(ushwords::device_list_continue,cmdIn)==0) {
      Serial.print(pDeviceDescriptions[dd]);
      Serial.print(ushwords::sepEnd);
      if (strcmp(pDeviceDescriptions[dd],ushwords::device_list_end)==0) {
        dd=0;
      } else {
        dd++;
      }
    } else {
      // interpret regular commands
      GetDeviceFromCmdIn(ushwords::sepOut);
      GetCommandFromCmdIn(ushwords::sepOut);
      
      if (strcmp(strDevice,"Shutter-A")==0) {
        GetNextValue(ushwords::sepWithin);
        if (strcmp(strCommand,"SO")==0) {
          // implement functionality here
          // .....
          MakeAndSendOutputCommand(strDevice, strCommand, 0, new char*[1] {strSingleValue}, 1);
        } else if (strcmp(strCommand,"SF")==0) {
          // implement functionality here
          // .....
          MakeAndSendOutputCommand(strDevice, strCommand, 0, new char*[1] {strSingleValue}, 1);
        } else if (strcmp(strCommand,"SI")==0) {
          // implement functionality here
          // .....
          MakeAndSendOutputCommand(strDevice, strCommand, 0, new char*[1] {strSingleValue}, 1);
        } else if (strcmp(strCommand,"SS")==0) {
          // implement functionality here
          // .....
          MakeAndSendOutputCommand(strDevice, strCommand, 0, new char*[1] {strSingleValue}, 1);
        } else if (strcmp(strCommand,"DL2")==0) {
          MakeAndSendOutputCommand(strDevice, ushwords::timeout, 1, new char*[1] {"1600"}, 1);
          delay(1500);
          MakeAndSendOutputCommand(strDevice, strCommand, 0, new char*[1] {strSingleValue}, 1);
          MakeAndSendOutputCommand(strDevice, ushwords::timeout, 0, new char*[1] {strDefaultTimeout}, 1);
        } else if (strcmp(strCommand,"RB0.1")==0) {
          float v = atof(strSingleValue) - 0.1;
          MakeAndSendOutputCommand(strDevice, strCommand, 0, new char*[1] {dtostrf(v,5,3,strSingleValue)}, 1);
        } else {
          MakeAndSendOutputCommand(strDevice, strCommand, usherrors::ctr_device_command_not_recognized, new char*[0], 0);          
        }
      } else if (strcmp(strDevice,"Shutter-B")==0) {
        GetNextValue(ushwords::sepWithin);
        if (strcmp(strCommand,"SO")==0) {
          // implement functionality here
          // .....
          MakeAndSendOutputCommand(strDevice, strCommand, 0, new char*[1] {strSingleValue}, 1);
        } else if (strcmp(strCommand,"VLT")==0) {
          // implement functionality here
          // .....
          MakeAndSendOutputCommand(strDevice, strCommand, 0, new char*[1] {strSingleValue}, 1);
        } else {
          MakeAndSendOutputCommand(strDevice, strCommand, usherrors::ctr_device_command_not_recognized, new char*[0], 0);          
        }
      } else if (strcmp(strDevice,"State-A")==0) {
        GetNextValue(ushwords::sepWithin);
        if (strcmp(strCommand,"SST")==0) {
          // implement functionality here
          // .....
          MakeAndSendOutputCommand(strDevice, strCommand, 0, new char*[1] {strSingleValue}, 1);
        } else {
          MakeAndSendOutputCommand(strDevice, strCommand, usherrors::ctr_device_command_not_recognized, new char*[0], 0);          
        }        
      } else if (strcmp(strDevice,"Stage-A")==0) {
        GetNextValue(ushwords::sepWithin);
        if (strcmp(strCommand,"SP")==0) {
          // implement functionality here
          // .....
          MakeAndSendOutputCommand(strDevice, strCommand, 0, new char*[1] {strSingleValue}, 1);
        } else if (strcmp(strCommand,"HM")==0) {
          // implement functionality here
          // .....
          MakeAndSendOutputCommand(strDevice, strCommand, 0, new char*[1] {"0"}, 1);
        } else if (strcmp(strCommand,"STOP")==0) {
          // implement functionality here
          // .....
          MakeAndSendOutputCommand(strDevice, strCommand, 0, new char*[1] {"123.5"}, 1);
        } else if (strcmp(strCommand,"MD")==0) {
          // implement functionality here
          // .....
          MakeAndSendOutputCommand(strDevice, strCommand, 0, new char*[1] {strSingleValue}, 1);
        } else {
          MakeAndSendOutputCommand(strDevice, strCommand, usherrors::ctr_device_command_not_recognized, new char*[0], 0);          
        }        
      } else if (strcmp(strDevice,"XYStage-A")==0) {
        GetNextValue(ushwords::sepWithin);
        if (strcmp(strCommand,"SP")==0) {
          // implement functionality here
          // .....
          float v1 = atof(strSingleValue);
          char str1[9];
          dtostrf(v1,8,1,str1); 
          GetNextValue(ushwords::sepWithin);
          float v2 = atof(strSingleValue);
          char str2[9];
          dtostrf(v2,8,1,str2); 
          MakeAndSendOutputCommand(strDevice, strCommand, 0, new char*[2] {str1,str2}, 2);
        } else if (strcmp(strCommand,"HM")==0) {
          // implement functionality here
          // .....
          MakeAndSendOutputCommand(strDevice, strCommand, 0, new char*[2] {"0","0"}, 2);
        } else if (strcmp(strCommand,"STOP")==0) {
          // implement functionality here
          // .....
          MakeAndSendOutputCommand(strDevice, strCommand, 0, new char*[2] {"246.8","135.7"}, 2);
        } else if (strcmp(strCommand,"MD")==0) {
          // implement functionality here
          // .....
          MakeAndSendOutputCommand(strDevice, strCommand, 0, new char*[1] {strSingleValue}, 1);
        } else {
          MakeAndSendOutputCommand(strDevice, strCommand, usherrors::ctr_device_command_not_recognized, new char*[0], 0);          
        }        
      } else {
        MakeAndSendOutputCommand(strDevice, strCommand, usherrors::ctr_device_not_recognized, new char*[0], 0);
      }
      
    }
    
  }

}
