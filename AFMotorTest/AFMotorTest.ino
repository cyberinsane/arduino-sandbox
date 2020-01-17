// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>

AF_DCMotor motorRight(2);
AF_DCMotor motorLeft(3);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");

  // turn on motor
  motorRight.setSpeed(200);
  motorLeft.setSpeed(200);
  motorRight.run(RELEASE);
  motorLeft.run(RELEASE);
}

void loop() {
  motorRight.run(FORWARD);
  motorLeft.run(FORWARD);
  motorRight.setSpeed(255);
  motorLeft.setSpeed(255);

  //
  //  Serial.print("tock");
  //
  //  motor.run(BACKWARD);
  //  motor.speed(255)
  //
  //
  //  Serial.print("tech");
  //  motor.run(RELEASE);

}
