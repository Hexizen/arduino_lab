#define THERMISTOR_PIN A0
#define PHOTORESISTOR_PIN A2
#define ALERT_PIN 12     

const float TEMP_THRESHOLD = 50.0;   
const int LIGHT_THRESHOLD = 220;    

void setup() {
  Serial.begin(9600);

  pinMode(ALERT_PIN, OUTPUT);
  digitalWrite(ALERT_PIN, LOW);

  Serial.println("=== FIRE SENSOR SYSTEM INITIALIZED ===");
  Serial.println("Monitoring temperature and brightness...");
}

void loop() {
  float temperature = readTemperatureC();
  int ldrMapped = readLDRValue();
  bool bright = isBright(ldrMapped);

  Serial.print("Temperature (°C): ");
  Serial.print(temperature);
  Serial.print(" | Brightness: ");
  Serial.println(ldrMapped);

  if (temperature >= TEMP_THRESHOLD && ldrMapped >= LIGHT_THRESHOLD) {
    Serial.println("🔥 FIRE DETECTED! Triggering alert...");
    triggerAlert(temperature);
  } else {
    digitalWrite(ALERT_PIN, LOW); 
    noTone(ALERT_PIN);
  }

  delay(500);
}

float readTemperatureC() {
  int analogValue = analogRead(THERMISTOR_PIN);
  float voltage = analogValue * (5.0 / 1023.0);
  float resistance = (5.0 - voltage) * 10000.0 / voltage;

  float steinhart = resistance / 10000.0;
  steinhart = log(steinhart);
  steinhart /= 3950.0;
  steinhart += 1.0 / (25.0 + 273.15);
  steinhart = 1.0 / steinhart;
  steinhart -= 273.15;

  return steinhart;
}

int readLDRValue() {
  int ldrRaw = analogRead(PHOTORESISTOR_PIN);
  int ldrMapped = map(ldrRaw, 200, 500, 100, 220);
  ldrMapped = constrain(ldrMapped, 0, 220);
  return ldrMapped;
}

bool isBright(int ldrMapped) {
  return (ldrMapped >= LIGHT_THRESHOLD);
}

void triggerAlert(float temperature) {
  int delayTime;

  if (temperature < 60) {
    delayTime = 300;
  } else if (temperature < 70) {
    delayTime = 150;
  } else {
    delayTime = 80;
  }

  for (int i = 0; i < 10; i++) {
    digitalWrite(ALERT_PIN, HIGH);
    tone(ALERT_PIN, 10000);
    delay(delayTime);

    digitalWrite(ALERT_PIN, LOW);
    noTone(ALERT_PIN);
    delay(delayTime);
  }
}
