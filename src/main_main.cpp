#include <SevSeg.h>
#include <AccelStepper.h>
#include <Arduino.h>

#define rotaryA A0
#define rotaryB A2
#define rotaryButton A4

SevSeg sevseg;
AccelStepper stepper1(1, 0, 1);
  

byte numDigits = 4;
byte digitPins[] = {11, 12, 13, 10};
byte segmentPins[] = {9, 2, 3, 5, 6, 8, 7, 4};
bool resistorsOnSegments = true;
byte hardwareConfig = COMMON_CATHODE;
bool leadingZeros = false;
bool disableDecPoint = false;


//variables
int cableLength = 0;
int currentState;
int aLastState;  
int rotaryButtonState;

int rotaryEncoder () {
   currentState = digitalRead(rotaryA); // Reads the "current" state of the outputA
   if (currentState != aLastState){     
     if (digitalRead(rotaryB) != currentState) { 
       cableLength = cableLength + 5;
     } else {
       cableLength = cableLength - 5;
     }
   } 
   aLastState = currentState; // Updates the previous state of the outputA with the current state
 return cableLength/2;
}

void setup() {

  Serial.begin(9600);

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);


  unsigned long startTimer = millis();

  stepper1.setMaxSpeed(100.0);
  stepper1.setAcceleration(100.0);
}
  
void loop(){
  rotaryEncoder();
  Serial.println(cableLength);
  sevseg.setNumber(cableLength, 1);
  sevseg.refreshDisplay();
  int rotaryButtonState = digitalRead(rotaryButton);
  if (rotaryButtonState == HIGH ){
    

    cableLength = 0;
  }
}

