#include <SevSeg.h>
#include <AccelStepper.h>
#include <Arduino.h>

//defining the rotary encoder input pins
#define rotaryA A0
#define rotaryB A1
#define rotaryButton A2

//stepper driver pins
#define stepPin A5
#define dirPin A4

SevSeg sevseg;
AccelStepper stepper(1, stepPin, dirPin); 
  
//sevseg required inputs
byte numDigits = 4;
byte digitPins[] = {10, 11, 12, 13};
byte segmentPins[] = {9, 2, 3, 5, 6, 8, 7, 4};
bool resistorsOnSegments = true;
byte hardwareConfig = COMMON_CATHODE;
bool leadingZeros = false;
bool disableDecPoint = false;


//public variables
int cableLength = 0;
int currentState;
int aLastState;  
int rotaryButtonState;
int i = 0;
//function that uses the rotary encoder ouput to change the value of the variable cableLength
int rotaryEncoder ()
{
  currentState = digitalRead(rotaryA); // Reads the "current" state of the outputA
  if (currentState != aLastState)
  {     
    if (digitalRead(rotaryB) != currentState)
    { 
      cableLength = cableLength + 5;  //+ and - 5 bcs the length of the cable is going to be selected by half a meter
    } 
    else 
    {
       cableLength = cableLength - 5;
    }
    Serial.println(cableLength); //debuggging purpose, 
  } 
  aLastState = currentState; // Updates the previous state of the outputA with the current state
  return cableLength;
}

void stepperExecute()
{
  if (digitalRead(rotaryButton) == LOW && stepper.distanceToGo() == 0)
  {
    delay(100);
    stepper.move(cableLength);
    Serial.println("target position changed");
      
  }
  while (stepper.distanceToGo() != 0)
    {
    /*
    if(i == 0){
      sevseg.setChars("jedu");
      sevseg.refreshDisplay();
      Serial.println("ugh");
      i++;
    }     */
    Serial.println("stepper in move"); //debugging purpose
    cableLength = 0;
    stepper.run();

  }
  //i = 0;
}

void sevsegInMove(){
  uint8_t segs[4] = {0, 0x5B, 0x6D, 0x63};
  sevseg.setSegments(segs);
}
void setup()
{
  Serial.begin(9600); //debugging purpose
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(20);
  pinMode(rotaryButton, INPUT_PULLUP); // push button is an input pull up (High when not presses)

  stepper.setMaxSpeed(500);
  stepper.setAcceleration(200);
}
  
void loop()
{
  rotaryEncoder();
  sevseg.setNumber(cableLength, 1);
  sevseg.refreshDisplay();
  stepperExecute();  
}
