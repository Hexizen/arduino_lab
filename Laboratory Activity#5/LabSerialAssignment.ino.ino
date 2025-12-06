#include "led_control.h"

void setup() {
  // Initialize Serial Communication
  Serial.begin(9600);
  
  // Initialize LEDs from our header file
  initLEDs();
}

void loop() {
  if (Serial.available() > 0) {
    char input = Serial.read();
    
    // Ignore newline or carriage return characters often sent by terminals
    if(input != '\n' && input != '\r') {
      processInput(input);
    }
  }
}