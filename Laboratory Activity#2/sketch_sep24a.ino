int leds[] = {12, 11, 10, 9, 8}; 
int numLeds = 5;

void setup() {
  for (int i = 0; i < numLeds; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
  // Turn ON LEDs one by one (with 1s delay)
  for (int i = 0; i < numLeds; i++) {
    if (leds[i] == 9 || leds[i] == 10 || leds[i] == 11) {
      // PWM pins → fade in
      for (int b = 0; b <= 255; b++) {
        analogWrite(leds[i], b);
        delay(4);  // ~1s total fade
      }
    } else {
      // Non-PWM pins → instant ON
      digitalWrite(leds[i], HIGH);
    }
    delay(1000);  // 1 second before moving to the next LED
  }

  // Turn OFF LEDs one by one (with 1s delay)
  for (int i = 0; i < numLeds; i++) {
    if (leds[i] == 9 || leds[i] == 10 || leds[i] == 11) {
      // PWM pins → fade out
      for (int b = 255; b >= 0; b--) {
        analogWrite(leds[i], b);
        delay(4);  // ~1s total fade
      }
    } else {
      // Non-PWM pins → instant OFF
      digitalWrite(leds[i], LOW);
    }
    delay(1000);  // 1 second before moving to the next LED
  }
}
