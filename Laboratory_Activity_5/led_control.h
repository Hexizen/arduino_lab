#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include <Arduino.h>

// Define Pins
const int RED_PIN = 8;
const int GREEN_PIN = 9;
const int BLUE_PIN = 10;

// Function to initialize pins
void initLEDs() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  
  // Start with all off
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
}

// Function to toggle a specific pin
void toggleLED(int pin) {
  int state = digitalRead(pin);
  digitalWrite(pin, !state);
}

// Function to turn all LEDs on or off
void setAllLEDs(int state) {
  digitalWrite(RED_PIN, state);
  digitalWrite(GREEN_PIN, state);
  digitalWrite(BLUE_PIN, state);
}

// Main logic handler
void processInput(char command) {
  // Convert to upper case for case-insensitivity
  command = toupper(command);

  switch (command) {
    case 'R':
      toggleLED(RED_PIN);
      break;
    case 'G':
      toggleLED(GREEN_PIN);
      break;
    case 'B':
      toggleLED(BLUE_PIN);
      break;
    case 'A':
      setAllLEDs(HIGH);
      break;
    case 'O':
      setAllLEDs(LOW);
      break;
    default:
      Serial.println("Error: Invalid Input");
      break;
  }
}

#endif