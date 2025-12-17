// --- PIN DEFINITIONS ---
// LEDs
const int BLUE_LED_PIN = 5;
const int GREEN_LED_PIN = 6;
const int RED_LED_PIN = 7;

// Buttons (using internal PULLUP, connected to GND)
const int BUTTON1_PIN = 12; // Sends 'R'
const int BUTTON2_PIN = 11; // Sends 'G'
const int BUTTON3_PIN = 10; // Sends 'B'

// Variables for debounce
long lastDebounceTime[3] = {0, 0, 0};
const long debounceDelay = 50; // ms

// Current and previous button states
int buttonState[3];      
int lastButtonState[3] = {HIGH, HIGH, HIGH}; // HIGH because of PULLUP

// Function to handle serial incoming data and toggle LEDs
void handleInboundSerial() {
  if (Serial.available()) {
    // Read the incoming byte (case-insensitive)
    char incomingChar = Serial.read();
    
    // Convert to lowercase for case-insensitive check
    char command = tolower(incomingChar); 
    
    if (command == '1') {
      // Toggle Red LED
      digitalWrite(RED_LED_PIN, !digitalRead(RED_LED_PIN));
    } else if (command == '2') {
      // Toggle Green LED
      digitalWrite(GREEN_LED_PIN, !digitalRead(GREEN_LED_PIN));
    } else if (command == '3') {
      // Toggle Blue LED
      digitalWrite(BLUE_LED_PIN, !digitalRead(BLUE_LED_PIN));
    }
  }
}

// Function to handle button presses and send signals
void handleOutboundButtons() {
  // Array of pin numbers and characters to send
  const int buttonPins[] = {BUTTON1_PIN, BUTTON2_PIN, BUTTON3_PIN};
  const char signals[] = {'R', 'G', 'B'};

  for (int i = 0; i < 3; i++) {
    int reading = digitalRead(buttonPins[i]);
    
    if (reading != lastButtonState[i]) {
      // Reset the debounce timer
      lastDebounceTime[i] = millis();
    }
    
    if ((millis() - lastDebounceTime[i]) > debounceDelay) {
      // The button state has been stable long enough
      if (reading != buttonState[i]) {
        buttonState[i] = reading;
        
        // Only trigger on the state change from LOW (pressed) to HIGH (released) 
        // or a simple press-to-LOW for 'ONCE' trigger
        if (buttonState[i] == LOW) { // Button is pressed
          Serial.println(signals[i]);
        }
      }
    }
    lastButtonState[i] = reading;
  }
}

void setup() {
  Serial.begin(9600); 

  // Set LED pins as output and ensure they start LOW (OFF)
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(BLUE_LED_PIN, LOW);

  // Set Button pins as input with internal pull-up resistors
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  pinMode(BUTTON3_PIN, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Check for inbound signals from Python
  handleInboundSerial();

  // Check for button presses and send outbound signals to Python
  handleOutboundButtons();

  // A small delay to keep the loop from running too fast (optional, for stability)
  delay(1);
}