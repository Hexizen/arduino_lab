//This code is for our Arduino R4, different from the code of Simulator 
//as the simulator runs in Arduino R3, which only supports some 
//digital pins as pwm for analog while R4 supports
//all the digital pins as pwm for analog

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
      int step = 0;
      while (step <= 100) {
        int brightness = map(step, 0, 100, 0, 255);
        analogWrite(leds[i], brightness);
        delay(10);  // smooth fade (~1s total)
        step++;
      }
    delay(1000);  // 1s delay before next LED
    i++;
  }

  // === Turn OFF LEDs one by one ===
  i = 0;
  while (i < numLeds) {
      int step = 100;
      while (step >= 0) {
        int brightness = map(step, 0, 100, 0, 255);
        analogWrite(leds[i], brightness);
        delay(10);  // smooth fade (~1s total)
        step--;
      }
    delay(1000);  // 1s delay before next LED
    i++;
  }
}
