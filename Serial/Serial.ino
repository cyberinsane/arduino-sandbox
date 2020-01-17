
void setup()
{
  Serial.begin(9600);
  pinMode(4, OUTPUT);
}
void loop()
{
  char c;
  if (Serial.available())  {
    c = Serial.read();

    digitalWrite(4, HIGH);
    
    Serial.println(c);
//    if (c == '1') {
//      digitalWrite(4, HIGH);
//    } else {
//      digitalWrite(4, LOW);
//    }
  }
}
