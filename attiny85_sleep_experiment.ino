

#include "attiny_sleep.h"

const int powerController = 4;
const int powerFailIndicator = 3;
const int blueLED = 1;
const int redLED = 0;
const int moistureSensor = 2;

const int cyclesBeforePowerRefresh = 4;
const int cyclesToRefreshPower = 1;
const int sleepTimer = 9;
const int rechargeTime = 8000;
int cycles = 0;


void setup(){
  pinMode(powerFailIndicator, INPUT);
  pinMode(powerController, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(redLED,  OUTPUT);
  setup_watchdog(sleepTimer);
}

void loop(){
  if (f_wdt == 1) {
    f_wdt = 0;
    
    if(cycles < cyclesToRefreshPower) {
      activatePower();
      activateLights(rechargeTime);
      deactivatePower();
      cycles++;
    }
    else if(cycles >= (cyclesToRefreshPower + cyclesBeforePowerRefresh)) {
      cycles = 0;
    }
    else {
      system_sleep();
      cycles++;
    }
  }
}

void activateLights(int howLong) {
      analogWrite(blueLED, 255);
      analogWrite(redLED, 255);
      delay(howLong);
      analogWrite(blueLED, 0);
      analogWrite(redLED, 0);
  
}

void deactivatePower(){
  digitalWrite(powerController, LOW);
}

void activatePower() {
  digitalWrite(powerController, HIGH);
}

void activatePower(int howLong) {
  digitalWrite(powerController, HIGH);
  delay(howLong);
  digitalWrite(powerController, LOW);
}
