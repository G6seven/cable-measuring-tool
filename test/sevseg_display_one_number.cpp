#include <SevSeg.h>
#include <Arduino.h>

#define delay 1000

SevSeg Display;

int number = 0;

void setup()
{
 
  byte numDigits = 4;
  byte digitPins[] = {11, 12, 13, 10};
  byte segmentPins[] = {9, 2, 3, 5, 6, 8, 7, 4};
  bool resistorsOnSegments = false;
  bool updateWithDelays = false;
  byte hardwareConfig = COMMON_CATHODE;
  bool leadingZeros = false;
  bool disableDecPoint = false;
  Display.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros, disableDecPoint);
  Display.setBrightness(100);
}
void loop()
{
  Display.setNumber(1234,3);
  Display.refreshDisplay();
}