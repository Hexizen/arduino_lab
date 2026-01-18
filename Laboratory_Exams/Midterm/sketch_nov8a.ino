#define PHOTORESISTOR_PIN A0
#define GREEN_PIN 11
#define YELLOW_PIN 12
#define RED_PIN 13

// Default Manual Thresholds (Also used for display in Auto Mode)
int LOW_THRESHOLD = 40;
int HIGH_THRESHOLD = 70;

// Mode Control
bool isAutomatic = false;

// For LED State Tracking
String activeLED = "None";
String environment = "N/A";

void setup() {
  Serial.begin(9600);

  pinMode(GREEN_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);

  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(RED_PIN, LOW);

  Serial.println("=== SERIAL CONTROLLED LIGHT SENSOR SYSTEM ===");
  Serial.println("Default Mode: MANUAL");
  Serial.println("Commands:");
  Serial.println("MODE AUTO / MODE MANUAL");
  Serial.println("SET LOW XX / SET HIGH XX (Manual Mode Only)");
}

void loop() {
  int sensorValue = analogRead(PHOTORESISTOR_PIN);
  // Map the 0-1023 sensor reading to a 0-100 percentage
  int intensity = map(sensorValue, 0, 1023, 0, 100);
  intensity = constrain(intensity, 0, 100);

  // Update environment description if in automatic mode
  if (isAutomatic) {
    updateAutomaticThresholds(intensity);
  }

  // Determine active LED (Now handles both modes correctly)
  setLED(intensity);

  // Display info on Serial
  Serial.print("Light Intensity: ");
  Serial.print(intensity);
  Serial.println("%");

  Serial.print("Active LED: ");
  Serial.println(activeLED);

  Serial.print("Current Mode: ");
  Serial.println(isAutomatic ? "Automatic" : "Manual");

  // Serial.print("Current Thresholds (Low/High): ");
  // Serial.print(LOW_THRESHOLD);
  // Serial.print("% / ");
  // Serial.print(HIGH_THRESHOLD);
  // Serial.println("%");
  
  if (isAutomatic) {
    Serial.print("Environment: ");
    Serial.println(environment);
  }

  Serial.println("----------------------------------");

  // Check for commands
  checkSerialInput();

  delay(1000);
}

// 💡 Separated Logic: Controls the LED based on the active mode.
void setLED(int intensity) {
  // Turn off all LEDs first
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(RED_PIN, LOW);

  if (isAutomatic) {
    // Automatic Logic uses hardcoded breakpoints (40% and 70%)
    if (intensity <= 40) {
      digitalWrite(GREEN_PIN, HIGH);
      activeLED = "Green"; // Low Light (Cloudy)
    } 
    else if (intensity <= 70) {
      digitalWrite(YELLOW_PIN, HIGH);
      activeLED = "Yellow"; // Normal Light
    } 
    else {
      digitalWrite(RED_PIN, HIGH);
      activeLED = "Red"; // High Light (Bright Sunlight)
    }
  } 
  else {
    // Manual Logic uses the user-settable LOW_THRESHOLD and HIGH_THRESHOLD
    if (intensity <= LOW_THRESHOLD) {
      digitalWrite(GREEN_PIN, HIGH);
      activeLED = "Green";
    } 
    else if (intensity > LOW_THRESHOLD && intensity <= HIGH_THRESHOLD) {
      digitalWrite(YELLOW_PIN, HIGH);
      activeLED = "Yellow";
    } 
    else {
      digitalWrite(RED_PIN, HIGH);
      activeLED = "Red";
    }
  }
}

void checkSerialInput() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    input.toUpperCase();

    if (input == "MODE AUTO") {
      isAutomatic = true;
      Serial.println("Switched to AUTOMATIC mode."); 
      // Thresholds now display static breakpoints (40/70).");
      // Set thresholds back to the auto breakpoints for display consistency
      LOW_THRESHOLD = 41;
      HIGH_THRESHOLD = 70;
    } 
    else if (input == "MODE MANUAL") {
      isAutomatic = false;
      Serial.println("Switched to MANUAL mode. Thresholds are now user-controlled.");
      LOW_THRESHOLD = 40;
      HIGH_THRESHOLD = 70;
    } 
    else if (input.startsWith("SET LOW ")) {
      if (!isAutomatic) {
        int newLow = input.substring(8).toInt();
        // Ensure low threshold is reasonable (e.g., must be less than current high)
        LOW_THRESHOLD = constrain(newLow, 0, HIGH_THRESHOLD - 1); 
        Serial.print("Manual LOW threshold set to ");
        Serial.print(LOW_THRESHOLD);
        Serial.println("%");
      } else {
        Serial.println("Error: Cannot set thresholds in AUTOMATIC mode.");
      }
    } 
    else if (input.startsWith("SET HIGH ")) {
      if (!isAutomatic) {
        int newHigh = input.substring(9).toInt();
        // Ensure high threshold is reasonable (e.g., must be greater than current low)
        HIGH_THRESHOLD = constrain(newHigh, LOW_THRESHOLD + 1, 100);
        Serial.print("Manual HIGH threshold set to ");
        Serial.print(HIGH_THRESHOLD);
        Serial.println("%");
      } else {
        Serial.println("Error: Cannot set thresholds in AUTOMATIC mode.");
      }
    } 
    else {
      Serial.println("Error: Wrong Command");
    }
  }
}

// 🌍 Simplified: Only updates the environment description in Auto Mode.
void updateAutomaticThresholds(int intensity) {
  if (intensity <= 40) {
    environment = "Cloudy";
  } 
  else {
    environment = "Clear";
  }
  
  // Note: LOW_THRESHOLD and HIGH_THRESHOLD are set to 40 and 70 in MODE AUTO 
  // command for consistent display, but they are not used for control here.
}