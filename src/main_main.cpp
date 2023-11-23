#include <SevSeg.h>
#include <AccelStepper.h>
#include <Arduino.h>

//defining the analog input pins
#define rotaryA A0
#define rotaryB A2
#define rotaryButton A4


//initializing libraries
SevSeg sevseg;
AccelStepper Xaxis(2, 0, 1); // pin 0 = step, pin 1 = direction
  
//sevseg required inputs
byte numDigits = 4;
byte digitPins[] = {10, 11, 12, 13};
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

//function that uses the rotary encoder ouput to modify the variable cableLength
int rotaryEncoder () {
   currentState = digitalRead(rotaryA); // Reads the "current" state of the outputA
   if (currentState != aLastState){     
     if (digitalRead(rotaryB) != currentState) { 
       cableLength = cableLength + 5;
     } else {
       cableLength = cableLength - 5;
     }
     Serial.println(cableLength); //debuggging purpose, 
   } 
   aLastState = currentState; // Updates the previous state of the outputA with the current state
 return cableLength/2;
}

//function that moves the stepper and zeroes out the cableLength variable



void setup() {

  Serial.begin(9600); //debugging purpose

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);


  unsigned long startTimer = millis(); // was experiencing with sevseg display refreshing, figured out different way 

  Xaxis.setMaxSpeed(800);
}
  
void loop(){


  rotaryEncoder();

  sevseg.setNumber(cableLength, 1);
  sevseg.refreshDisplay();
  // next goal is to make the stepper move the required amount of steps, that will require knowing the dimensions of the pulley
  if (analogRead(rotaryButton) == HIGH ){
    while (Xaxis.distanceToGo() == 0){
      delay(100);
      Xaxis.moveTo(cableLength);
      Xaxis.setAcceleration(200);
      Xaxis.setMaxSpeed(400);
      Xaxis.run();
    } 
    Serial.println(cableLength); //debuggging purpose,
    cableLength = 0; 
  }
}