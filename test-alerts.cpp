#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  AlertTarget alertTarget = TO_CONTROLLER;
  BatteryCharacter batteryChar = {PASSIVE_COOLING,"BatteryBrandABC"};
  REQUIRE(checkAndAlert(alertTarget, batteryChar, -1) == TOO_LOW);
  REQUIRE(checkAndAlert(alertTarget, batteryChar, 36 ) == TOO_HIGH);
  alertTarget = TO_EMAIL;
  REQUIRE(checkAndAlert(alertTarget, batteryChar, 0) == NORMAL);
  REQUIRE(checkAndAlert(alertTarget, batteryChar, 35) == NORMAL);
  
   alertTarget = TO_CONTROLLER;
  BatteryCharacter batteryChar2 = {HI_ACTIVE_COOLING,"BatteryBrandABC"};
  REQUIRE(checkAndAlert(alertTarget, batteryChar2, -1) == TOO_LOW);
  REQUIRE(checkAndAlert(alertTarget, batteryChar2, 46 ) == TOO_HIGH);
  alertTarget = TO_EMAIL;
  REQUIRE(checkAndAlert(alertTarget, batteryChar2, 0) == NORMAL);
  REQUIRE(checkAndAlert(alertTarget, batteryChar2, 45) == NORMAL);
  
  alertTarget = TO_CONTROLLER;
  BatteryCharacter batteryChar3 = {MED_ACTIVE_COOLING,"BatteryBrandABC"};
  REQUIRE(checkAndAlert(alertTarget, batteryChar3, -1) == TOO_LOW);
  REQUIRE(checkAndAlert(alertTarget, batteryChar3, 41 ) == TOO_HIGH);
  alertTarget = TO_EMAIL;
  REQUIRE(checkAndAlert(alertTarget, batteryChar3, 0) == NORMAL);
  REQUIRE(checkAndAlert(alertTarget, batteryChar3, 40) == NORMAL);
}
