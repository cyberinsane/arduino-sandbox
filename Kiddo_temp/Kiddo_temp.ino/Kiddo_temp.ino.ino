// Author: Cyberinsane
// Android controlled bot for Deloitte Digital
// Code name: kiDDo

#include <AFMotor.h>
#include <FastLED.h>

// LED pin
#define LEDPIN 33
#define NUM_LEDS 64
#define DATA_PIN 50
CRGB leds[NUM_LEDS];

// LED Defaults
int redColor = 0;
int greenColor = 0;
int blueColor = 255;

boolean drawOnLedGrid = false;
String ledInput;

// Motors
AF_DCMotor motorRight(2);
AF_DCMotor motorLeft(3);

// Sound sensor
int sensorPin = A4;
boolean soundSensorEnabled = false;

// An array to store the received data
const byte numChars = 200;
char receivedChars[numChars];
boolean newData = false;

// Inputs
const String inSoundSensorOn = "st";
const String inSoundSensorOff = "sf";
const String inLedValues = "L";
const char inLedCountValueSeparator = ':';
const char inLedValueSeparator = ',';

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.println("<CyberBot is Ready>");

  // Init motors
  motorRight.setSpeed(200);
  motorLeft.setSpeed(200);
  motorRight.run(RELEASE);
  motorLeft.run(RELEASE);

  // Init LEDS
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  fadeall();

  pinMode(LEDPIN, OUTPUT);
}

void loop()
{
  recvWithEndMarker();
  showNewData();
}

void recvWithEndMarker() {
  static byte ndx = 0;
  char endMarker = '*';
  char rc;

  while ((Serial.available() > 0 || Serial1.available() > 0) && newData == false) {

    if (Serial1.available()) {
      rc = Serial1.read();
      Serial1.print(rc);
    } else {
      rc = Serial.read();
      Serial.print(rc);
    }

    if (rc != endMarker) {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    }
    else {
      receivedChars[ndx] = '\0'; // terminate the string
      ndx = 0;
      newData = true;
    }
  }
}

void showNewData() {
  if (newData == true) {
    Serial.print("In: ");
    Serial.println(receivedChars);
    processData();
    newData = false;
  } else {
    showData();
  }
}

// Reset leds
void fadeall() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
}

void processData() {
  String input = String(receivedChars);
  if (input == inSoundSensorOn) {
    soundSensorEnabled = true;
    Serial1.println("true");
  }
  else if (input == inSoundSensorOff) {
    soundSensorEnabled = false;
    Serial1.println("false");
  }
  else if (input.startsWith(inLedValues)) {
    Serial.print("LED input:");
    input.replace(inLedValues, "");
    checkLedCongifuration(input);
  } else {
    processMotor(input);
  }
}

void checkLedCongifuration(String input) {
  Serial.print(input);
  String countStr = getValue(input, inLedCountValueSeparator, 0);
  int count = countStr.toInt();
  if (count == 0) {
    drawOnLedGrid = false;
    Serial.print("LED False:");
  } else {
    drawOnLedGrid = true;
    Serial.print("LED True:");
  }
  Serial.println("Count:" + count);
  ledInput = input;
}

void processMotor(String input) {
  String left = getValue(input, ':', 0);
  String right = getValue(input, ':', 1);

  Serial.println("Left Motor:" + left);
  Serial.println("Right Motor:" + right);

  int leftValue = left.toInt();
  int rightValue = right.toInt();

  if (leftValue >= 0 && rightValue >= 0) {
    motorRight.run(FORWARD);
    motorLeft.run(FORWARD);
  } else {
    motorRight.run(BACKWARD);
    motorLeft.run(BACKWARD);
  }

  motorRight.setSpeed(abs(rightValue) * 255 / 100);
  motorLeft.setSpeed(abs(leftValue) * 255 / 100);
}

void showData() {
//  if (soundSensorEnabled) {
//    int sensorValue = analogRead(sensorPin);
//    if (sensorValue == 1) {
//      Serial.println("Sensor Armed");
//      digitalWrite(LEDPIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//      // drawOnLedGrid("16:0$255$255:18,29,34,45,19,28,35,44,20,27,36,43,21,26,37,42");
//      delay(1000);
//    } else {
//      digitalWrite(LEDPIN, LOW);
//      Serial.println("Sensor Off");
//      delay(1000);
//      // drawOnLedGrid("4:0$255$255:28,35,27,36");
//    }
//    return;
//  }

  if (drawOnLedGrid) {
    String countStr = getValue(ledInput, inLedCountValueSeparator, 0);
    int count = countStr.toInt();

    Serial.print("Count:");
    Serial.println(countStr);

    String colorCodeStr = getValue(ledInput, inLedCountValueSeparator, 1);
    Serial.print("ColorCode:");
    Serial.println(colorCodeStr);
    int red = getValue(colorCodeStr, '$', 0).toInt();
    int green = getValue(colorCodeStr, '$', 1).toInt();
    int blue = getValue(colorCodeStr, '$', 2).toInt();

    String valueStr = getValue(ledInput, inLedCountValueSeparator, 2);
    Serial.print("Values:");
    Serial.println(valueStr);
    int values[count] = {};
    for (int i = 0; i < count; i++) {
      int value = getValue(valueStr, inLedValueSeparator, i).toInt();
      values[i] = value;
      for (int dot = 0; dot < NUM_LEDS; dot++) {
        if (dot == value) {
          leds[dot].setRGB( red, green, blue);
        }
      }
    }
    FastLED.show();
    delay(50);
    return;
  }

  fadeall();
  FastLED.show();

}

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
