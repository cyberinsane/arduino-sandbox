int analogSensorPin = A0; // select the input pin for the potentiometer
int analogSensorValue = 0; // variable to store the value coming from the sensor

int digitalSensorPin = 3;
int digitalSensorValue = 0;// define numeric variables val
 
void setup () 
{
  Serial.begin (9600);
  pinMode (digitalSensorPin, INPUT);
}
 
void loop () 
{
  analogSensorValue = analogRead(analogSensorPin);
  digitalSensorValue = digitalRead(digitalSensorPin);
  
  delay(300);
  Serial.print("Analog...");
  Serial.println(analogSensorValue, DEC);
  
  Serial.print("Digital...");
  Serial.println(digitalSensorValue, DEC);
}
