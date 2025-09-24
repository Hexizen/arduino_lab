int leds[] = {12, 11, 10, 9, 8}; 
int numLeds = 5;

void setup() {
  for (int i = 0; i < numLeds; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
  int i = 0;

  // === Turn ON LEDs one by one ===
  while (i < numLeds) {
    if (leds[i] == 9 || leds[i] == 10 || leds[i] == 11) {
      int step = 0;
      while (step <= 100) {
        int brightness = map(step, 0, 100, 0, 255);
        analogWrite(leds[i], brightness);
        delay(10);  // smooth fade (~1s total)
        step++;
      }
    } else {
      digitalWrite(leds[i], HIGH);
    }
    delay(1000);  // 1s delay before next LED
    i++;
  }

  // === Turn OFF LEDs one by one ===
  i = 0;
  while (i < numLeds) {
    if (leds[i] == 9 || leds[i] == 10 || leds[i] == 11) {
      int step = 100;
      while (step >= 0) {
        int brightness = map(step, 0, 100, 0, 255);
        analogWrite(leds[i], brightness);
        delay(10);  // smooth fade (~1s total)
        step--;
      }
    } else {
      digitalWrite(leds[i], LOW);
    }
    delay(1000);  // 1s delay before next LED
    i++;
  }
}
