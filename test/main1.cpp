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

#define delay 1000

// Create object
SevSeg sevseg;

byte numDigits = 2;
byte digitPins[] = {11, 12};
byte segmentPins[] = {9, 2, 3, 5, 6, 8, 7, 4};
bool resistorsOnSegments = true;
byte hardwareConfig = COMMON_CATHODE;

unsigned long startMilis;
unsigned long timer = millis() - delay;

void setup() {

  // Start display object
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  // Set bright ness
  sevseg.setBrightness(80);

  startMilis = millis();  //initial start time
  
  Serial.begin(9600);
}

void loop (){

    for (int number = 0; number <= 99; number++){
        Serial.println(number);
        sevseg.setNumber(number);

        if (millis() > (timer + delay)) {
            sevseg.refreshDisplay();
            timer = millis();
        }

    }

}