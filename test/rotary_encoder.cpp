#include <Arduino.h>


 #define rotaryA A0
 #define rotaryB A2

 int counter = 0; 
 int aState;
 int aLastState;  

 void setup() { 
    pinMode (rotaryA,INPUT);
    pinMode (rotaryB,INPUT);
   
    Serial.begin (9600);
   // Reads the initial state of the outputA
    aLastState = analogRead(rotaryA);   
 } 
  void loop() { 
   aState = digitalRead(rotaryA); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState != aLastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(rotaryB) != aState) { 
       counter ++;
     } else {
       counter --;
     }
     Serial.print("Position: ");
     Serial.println(counter);
   } 
   aLastState = aState; // Updates the previous state of the outputA with the current state
 }