int redPin = 7;
int greenPin = 6;
int bluePin = 5;

int redState = LOW;
int greenState = LOW;
int blueState = LOW;

const int btn1 = 12;
const int btn2 = 11;
const int btn3 = 10;

void setup()
{
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);

  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
}

void loop()
{
  if (Serial.available() > 0)
  {
    // Use either String or char (String for reading characters one at a time, char for all characters at once)
    // String incomingText = Serial.readString(); 
    // char cmd = incomingText.charAt(0);

    char cmd = Serial.read(); 
    while(Serial.available() > 0) {
      Serial.read(); 
    }

    cmd = tolower(cmd);

    if (cmd == '1') toggleLED(redPin);
    else if (cmd == '2') toggleLED(greenPin);
    else if (cmd == '3') toggleLED(bluePin);
    else if (cmd == 'o') {
      digitalWrite(redPin, HIGH);
      digitalWrite(greenPin, HIGH);
      digitalWrite(bluePin, HIGH);
    }
    else if (cmd == 'f') {
      digitalWrite(redPin, LOW);
      digitalWrite(greenPin, LOW);
      digitalWrite(bluePin, LOW);
    }
  }

  if (digitalRead(btn1) == HIGH) 
  {
    toggleLED(redPin);
    Serial.println("Button 1 Pressed: Red Toggled"); 
    delay(150); // Debounce
    while(digitalRead(btn1) == HIGH);
  }

  if (digitalRead(btn2) == HIGH)
  {
    toggleLED(greenPin);
    Serial.println("Button 2 Pressed: Green Toggled");
    delay(150);
    while(digitalRead(btn1) == HIGH);
  }

  if (digitalRead(btn3) == HIGH)
  {
    toggleLED(bluePin);
    Serial.println("Button 3 Pressed: Blue Toggled");
    delay(150);
    while(digitalRead(btn1) == HIGH);
  }
}

// Function stays the same
void toggleLED(int pin)
{
  int state = digitalRead(pin);
  digitalWrite(pin, !state);
}