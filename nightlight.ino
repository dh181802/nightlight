//global variables for the PWM pin, the sensorpin and the dark/light thresholds
const int ledPin = 5;
const int sensorPin = A0;
const float darkThreshold = 1.90;
const float lightTreshold = 1.80;

//boolean 
bool isDark = false;

//global variables to store millis for the calculation of the LED on and LED off time
float previousMillis;
float currentMillis;
float millisPassed;
float timePassed;

//global string variable to store the output strings for light on and light off
String toPrint;

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

//function to do the switch and to calculate the on/off time
//current time is taken and the previousMillis value is substracted.
//to give the accurate time for each on/off state previousMillis is set to currentMillis
//to get seconds timePassed is divided by 1000
void switchState() {
  isDark =!isDark;
  currentMillis = millis();
  millisPassed = currentMillis - previousMillis;
  previousMillis = currentMillis;
  timePassed = millisPassed / 1000;
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  float sensorValue = analogRead(sensorPin);
  
  // Convert the analog reading (0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  //the dimmer variable to be fed into the PWM pin - not sure if sensorValue/3 is the best value
  float dimmer = sensorValue / 3;

  //if the voltage is above the dark threshold the builtin LED and the LED on pin 5 are switched on.
  //boolean isDark is set to true
  //the function switchState is called for the calculation of the on/off time
  if (voltage > darkThreshold && isDark == false) {
    digitalWrite(LED_BUILTIN, HIGH);
    analogWrite(ledPin, dimmer);
  //isDark = true;
    switchState();
    toPrint = "dark, seconds it was light: ";
    Serial.println(toPrint + timePassed);
      
  } else if (voltage < lightTreshold && isDark == true) {
    digitalWrite(LED_BUILTIN, LOW);
    analogWrite(ledPin, LOW);
  //isDark = false;
    switchState();
    toPrint = "light, seconds it was dark: ";
    Serial.println(toPrint + timePassed);
  }
}
