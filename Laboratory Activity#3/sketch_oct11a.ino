// =====================================================
// FIRE SENSOR SIMULATION PROJECT
// =====================================================
// Components:
// - Thermistor (A0)        -> Temperature detection (analog)
// - Photoresistor (A2)     -> Light detection (digital-like)
// - LED (D12)              -> Visual alert
// - Buzzer (D13)           -> Audible alert
// =====================================================

// --- Pin Definitions ---
#define THERMISTOR_PIN A0
#define PHOTORESISTOR_PIN A2
#define LED_PIN 12
#define BUZZER_PIN 13

// --- Threshold Values ---
const float TEMP_THRESHOLD = 50.0;   // Temperature threshold in °C
const int LIGHT_THRESHOLD = 220;     // Brightness threshold (0–1023)

// --- Function Declarations ---
float readTemperatureC();
bool isBright();
void triggerAlert(float temperature);

// =====================================================
// Setup
// =====================================================
void setup() {
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  Serial.println("=== FIRE SENSOR SYSTEM INITIALIZED ===");
  Serial.println("Monitoring temperature and brightness...");
}

// =====================================================
// Main Loop
// =====================================================
void loop() {
  float temperature = readTemperatureC(); // read from thermistor
  bool bright = isBright();               // convert LDR to digital-like signal

  // Print sensor readings
  Serial.print("Temperature (°C): ");
  Serial.print(temperature);
  Serial.print(" | Brightness: ");
  Serial.println(bright ? "BRIGHT (1)" : "DARK (0)");

  // Fire is detected when:
  // - Temperature ≥ 50°C
  // - AND area is bright (light detected)
  if (temperature >= TEMP_THRESHOLD && bright) {
    Serial.println("🔥 FIRE DETECTED! Triggering alert...");
    triggerAlert(temperature);
  } else {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }

  delay(500);
}

// =====================================================
// Function: Read Temperature from Thermistor
// =====================================================
float readTemperatureC() {
  int analogValue = analogRead(THERMISTOR_PIN);

  // Convert analog reading (0–1023) to voltage (0–5V)
  float voltage = analogValue * (5.0 / 1023.0);

  // Calculate resistance of thermistor (assuming 10k series resistor)
  float resistance = (5.0 - voltage) * 10000.0 / voltage;

  // Apply Steinhart-Hart approximation for a 10k thermistor (B = 3950)
  float steinhart;
  steinhart = resistance / 10000.0;        // (R/Ro)
  steinhart = log(steinhart);              // ln(R/Ro)
  steinhart /= 3950.0;                     // 1/B * ln(R/Ro)
  steinhart += 1.0 / (25.0 + 273.15);      // + (1/To)
  steinhart = 1.0 / steinhart;             // Invert
  steinhart -= 273.15;                     // Convert to °C

  return steinhart;
}

// =====================================================
// Function: Read Brightness from Photoresistor (digital-like)
// =====================================================
bool isBright() {
  int brightnessValue = analogRead(PHOTORESISTOR_PIN);
  // Convert analog value to digital-like HIGH or LOW
  return (brightnessValue >= LIGHT_THRESHOLD);
}

// =====================================================
// Function: Trigger Alert (LED + Buzzer with intensity)
// =====================================================
void triggerAlert(float temperature) {
  int delayTime;

  // Adjust blink/beep speed based on temperature level
  if (temperature < 60) {
    delayTime = 300;   // mild warning
  } else if (temperature < 70) {
    delayTime = 150;   // danger
  } else {
    delayTime = 80;    // critical fire
  }

  // Blink LED and beep buzzer 10 times
  for (int i = 0; i < 10; i++) {
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, 1000); // buzzer sound (1 kHz)
    delay(delayTime);

    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
    delay(delayTime);
  }
}