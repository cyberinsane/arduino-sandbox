
#include <FastLED.h>

//pin definitions
const int red = 11;
const int green = 10;
const int blue = 9;
const int soundSensor = 3;

int redColor = 0;
int greenColor = 255;
int blueColor = 255;

// an array to store the received data
const byte numChars = 20;
char receivedChars[numChars];

boolean newData = false;
boolean soundSensorEnabled = false;

void setup() {
  pinMode (soundSensor, INPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

  Serial.begin(9600);
  Serial.println("<CyberLED is Ready>");
}

void loop() {
  recvWithEndMarker();
  showNewData();
}

void recvWithEndMarker() {
  static byte ndx = 0;
  char endMarker = '*';
  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();
    Serial.print(rc);
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
    Serial.print("This just in ... ");
    Serial.println(receivedChars);
    processData();
    newData = false;
  } else {
    showData();
  }
}

void processData() {
  String input = String(receivedChars);
  if (input == "st") {
    soundSensorEnabled = true;
    Serial.println("true");
  } else if (input == "sf") {
    soundSensorEnabled = false;
    Serial.println("false");
  } else {
    String red = getValue(input, ':', 0);
    String green = getValue(input, ':', 1);
    String blue = getValue(input, ':', 2);

    redColor = red.toInt();
    greenColor  = green.toInt();
    blueColor = blue.toInt();
  }
  showData();
}

void showData() {
  if (soundSensorEnabled) {
    int statusSensor = digitalRead (soundSensor);
    if (statusSensor == 1) {
      analogWrite(red, redColor);
      analogWrite(green, greenColor);
      analogWrite(blue, blueColor);
      delay(10);
    } else {
      analogWrite(red, 0);
      analogWrite(green, 0);
      analogWrite(blue, 0);
    }
  } else {
    analogWrite(red, redColor);
    analogWrite(green, greenColor);
    analogWrite(blue, blueColor);
  }
}

String getValue(String data, char separator, int index) {
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


