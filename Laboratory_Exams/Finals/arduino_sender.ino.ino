/*
 * Arduino Sketch for IoT Lab
 * Hardware: Push button connected to Pin 2 (Active LOW)
 * Functionality: Sends group number "1" via Serial on valid button press.
 * Features: Software debouncing, Single-shot triggering (no repeat on hold).
 */

const int buttonPin = 2;     // The pin that the pushbutton is attached to
const String groupNum = "2"; // The group number to send

// Variables for debouncing and state tracking
int buttonState;             // The current reading from the input pin
int lastButtonState = HIGH;  // The previous reading from the input pin (High because of Pull-up)

unsigned long lastDebounceTime = 0;  // The last time the output pin was toggled
unsigned long debounceDelay = 50;    // The debounce time; increase if the output flickers

void setup() {
  // Initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  // Initialize the button pin as an input with internal pull-up resistor:
  // Note: Input will be HIGH when open, LOW when pressed.
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // Read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // Reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // Whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // If the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // Only send the signal if the new button state is LOW (Pressed)
      // This ensures we trigger only on the "push" action, not the release.
      if (buttonState == LOW) {
        Serial.println(groupNum);
      }
    }
  }

  // Save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}