#include <SevSeg.h>
#include <AccelStepper.h>
#include <Arduino.h>

#define rotaryA A0
#define rotaryB A2
#define rotaryButton A4

SevSeg sevseg;
AccelStepper stepper1(1, 0, 1);
  

byte numDigits = 4;
byte digitPins[] = {10, 11, 12, 13};
byte segmentPins[] = {9, 2, 3, 5, 6, 8, 7, 4};
bool resistorsOnSegments = true;
byte hardwareConfig = COMMON_CATHODE;

//variables
int cableLength = 0;
int currentState;
int aLastState;  
int rotaryButtonState;

int rotaryEncoder () {
   currentState = digitalRead(rotaryA); // Reads the "current" state of the outputA
   if (currentState != aLastState){     
     if (digitalRead(rotaryB) != currentState) { 
       cableLength ++;
     } else {
       cableLength --;
     }
   } 
   aLastState = currentState; // Updates the previous state of the outputA with the current state
 return cableLength;
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
  sevseg.setNumber(cableLength);
  rotaryEncoder();
  int rotaryButtonState = digitalRead(rotaryButton);
  if (rotaryButtonState == HIGH ){
  }
}

