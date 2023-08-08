#include <SevSeg.h>
#include <Arduino.h>

#define delay 1000

SevSeg Display;

int number = 0;

void setup()
{
 
  byte numDigits = 4;
  byte digitPins[] = {10, 11, 12, 13};
  byte segmentPins[] = {9, 2, 3, 5, 6, 8, 7, 4};
  bool resistorsOnSegments = false;
  bool updateWithDelays = false;
  byte hardwareConfig = COMMON_CATHODE;
  bool leadingZeros = true;
  bool disableDecPoint = true;
  Display.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros, disableDecPoint);
  Display.setBrightness(100);
}
void loop()
{
  number = 0;
  for (int j = 0; j < 10; j++)
  {
    for (int i = 0; i < 3000; i++)
    {
      Display.setNumber(number);
      Display.refreshDisplay();
    }
    number = number + 1111;
  }
}