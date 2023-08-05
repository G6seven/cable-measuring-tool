/*
  7-Segment Display - Four Digit, directly wired
  7-seg-multi.ino
  Print a number to a 4-digit 7-segment display

  DroneBot Workshop 2022
  https://dronebotworkshop.com
*/

// Include library
#include <SevSeg.h>
#include <Arduino.h>


// Create object
SevSeg sevseg;

byte numDigits = 2;
byte digitPins[] = {11, 12};
byte segmentPins[] = {9, 2, 3, 5, 6, 8, 7, 4};
bool resistorsOnSegments = true;
byte hardwareConfig = COMMON_CATHODE;

unsigned long startMilis;
unsigned long currentMilis;


void setup() {

  // Start display object
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  // Set bright ness
  sevseg.setBrightness(80);

  startMilis = millis();  //initial start time
  
  Serial.begin(9600);
}

void loop() 
{
  unsigned long currentMilis = millis();

  for (int number = 0; number < 100; number++)
  {
  while (currentMilis - startMilis >= 500)
    {
      sevseg.setNumber(number);
      sevseg.refreshDisplay();
      startMilis = currentMilis;
      Serial.println(number);

    }
  }
  
}
