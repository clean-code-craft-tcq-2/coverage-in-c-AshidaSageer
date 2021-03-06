#include "typewise-alert.h"
#include <stdio.h>
#include <string.h>

TemperatureLimits temperaturelimits[] =     {{PASSIVECOOLING_LOWERLIMIT,PASSIVECOOLING_UPPERLIMIT },
                                               {HI_ACTIVECOOLING_LOWERLIMIT,HI_ACTIVECOOLING_UPPERLIMIT},
                                               {MED_ACTIVECOOLING_LOWERLIMIT,MED_ACTIVECOOLING_UPPERLIMIT}
                                              };

const  char* BreachStatus[] = {"normal","too low","too high"};


void (*alertTarget_FuncPtr[])(BreachType)={sendToController,sendToEmail};

/*void printToConsole(char message[])
{
printf(" %s",message);
  return;
}*/

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
  int lowerLimit = temperaturelimits[coolingType].lowerLimit;
  int upperLimit = temperaturelimits[coolingType].upperLimit;

  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

BreachType checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC
  );

  alertTarget_FuncPtr[alertTarget](breachType);
  
  return breachType;
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  /*char messageToController[100];
  sprintf(messageToController,"%x : %x\n", header, breachType);
  printToConsole(messageToController);*/
   printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  //char recepientaddress[50]  ;
  //char messageTomail[100];
     
      /*sprintf (recepientaddress, "To: %s\n", recepient);
    printToConsole(recepientaddress);
      sprintf (messageTomail, "Hi, the temperature is %s \n",BreachStatus[breachType]);
    printToConsole(messageTomail);*/
  
  printf ("To: %s\n", recepient);
  printf ( "Hi, the temperature is %s \n",BreachStatus[breachType]);
}
