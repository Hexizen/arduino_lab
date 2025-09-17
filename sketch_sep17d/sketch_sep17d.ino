int ledPins[] = {12,11,10,9,8};

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 5; i++){
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 5; i++){
    digitalWrite(ledPins[i], HIGH);
    delay(1000);
  }
  for (int i = 0; i < 5; i++){
    digitalWrite(ledPins[i], LOW);
    delay(1000);
  }
}
