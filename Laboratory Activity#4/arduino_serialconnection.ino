#define PHOTORESISTOR_PIN A2
#define LED_PIN 8

const int LIGHT_THRESHOLD = 220;
bool blinkingActive = false;

unsigned long previousMillis = 0;
const unsigned long blinkInterval = 100;
bool ledState = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.println("=== SERIAL CONTROLLED SENSOR SYSTEM ===");
  Serial.println("Type 'stop' to stop blinking.");
}

void loop() {
  int brightness = readLDRValue();

  Serial.print("Brightness: ");
  Serial.println(brightness);

  if (brightness >= LIGHT_THRESHOLD && !blinkingActive) {
    blinkingActive = true;
    Serial.println("Threshold reached! Blinking activated.");
  }

  if (blinkingActive) {
    blinkLED();
  } else {
    digitalWrite(LED_PIN, LOW);
  }

  checkSerialInput();

  delay(500);
}

int readLDRValue() {
  int raw = analogRead(PHOTORESISTOR_PIN);

  int mappedValue = map(raw, 0, 800, 70, 220);
  mappedValue = constrain(mappedValue, 70, 220);

  return mappedValue;
}

void blinkLED() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= blinkInterval) {
    previousMillis = currentMillis;

    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
  }
}

void checkSerialInput() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    input.toLowerCase();

    if (input == "stop") {
      blinkingActive = false;
      digitalWrite(LED_PIN, LOW);
      Serial.println("Blinking stopped.");
    }
  }
}