// Author: Cyberinsane
// Android controlled bot for Deloitte Digital
// Code name: kiDDo

#include <AFMotor.h>

AF_DCMotor motorRight(2);
AF_DCMotor motorLeft(3);

// an array to store the received data
const byte numChars = 11;
char receivedChars[numChars];

boolean newData = false;

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.println("<CyberBot is Ready>");
  motorRight.setSpeed(200);
  motorLeft.setSpeed(200);
  motorRight.run(RELEASE);
  motorLeft.run(RELEASE);
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
    Serial.print("This just in ... ");
    Serial.println(receivedChars);
    processData();
    newData = false;
  }
}

void processData() {
  String input = String(receivedChars);
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
