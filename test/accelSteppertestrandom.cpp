// Random.pde
// -*- mode: C++ -*-
//
// Make a single stepper perform random changes in speed, position and acceleration
//
// Copyright (C) 2009 Mike McCauley
// $Id: Random.pde,v 1.1 2011/01/05 01:51:01 mikem Exp mikem $
 
#include <AccelStepper.h>
 
// Define a stepper and the pins it will use
AccelStepper stepper (2, 0, 1); // pin 0 = step, pin 1 = direction

void setup()
{  
}
 
void loop()
{
    if (stepper.distanceToGo() == 0)
    {
        // Random change to speed, position and acceleration
        // Make sure we dont get 0 speed or accelerations
        delay(10000);
        stepper.moveTo(12000);
        stepper.setMaxSpeed(400);
        stepper.setAcceleration(200);
    }
    stepper.run();
}
