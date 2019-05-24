//global variables for the PWM pin, the sensorpin and the dark/light thresholds
const int ledPin = 5;
const int sensorPin = A0;
const float darkThreshold = 1.90;
const float lightTreshold = 1.80;

bool isDark = false;

//global variables to store millis for the calculation of the LED on and LED off time
float previousMillis = 0;
float currentMillis = 0;
float millisPassed = 0;
float timePassed = 0;

//global string variable to store the output strings for light on nad light off
String toPrint = "";

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  float sensorValue = analogRead(sensorPin);
  
  // Convert the analog reading (0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  //the dimmer variable to be fed into the PWM pin - not sure if voltage * 51 is the best value
  float dimmer = voltage * 51;

  //if the voltage is above the dark threshold the builtin LED and the LED on pin 5 are switched on.
  //boolean isDark is set to true
  //current time is taken and the previousMillis value is substracted.
  //to give the accurate time for each on/off state previousMillis is set to currentMillis
  //to get seconds timePassed is divided by 1000
  if (voltage > darkThreshold && isDark == false) {
      digitalWrite(LED_BUILTIN, HIGH);
      analogWrite(ledPin, dimmer);
      isDark = true;
      currentMillis = millis();
      millisPassed = currentMillis - previousMillis;
      previousMillis = currentMillis;
      timePassed = millisPassed / 1000;
      toPrint = "dark, seconds it was light: ";
      Serial.println(toPrint + timePassed);
      
  } else if (voltage < lightTreshold && isDark == true) {
    digitalWrite(LED_BUILTIN, LOW);
    analogWrite(ledPin, LOW);
    isDark = false;
     currentMillis = millis();
      millisPassed = currentMillis - previousMillis;
      previousMillis = currentMillis;
      timePassed = millisPassed / 1000;
      toPrint = "light, seconds it was dark: ";
      Serial.println(toPrint + timePassed);
  }
}
