#include <SPI.h>

#include <WiFi.h>

char ssid[] = "wolverine"; // your network SSID (name)

char pass[] = "facebook"; // your network password (use for WPA, or use as key for WEP)

int keyIndex = 0; // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

char server[] = "www.theengineeringprojects.com"; // name address for Google (using DNS)

String location = "/Examples/data.txt HTTP/1.0";

char inString[500]; // string for incoming serial data

int stringPos = 0; // string index counter

byte statusLed = 0;

char c;

int led1 = 3;

int led2 = 4;

WiFiClient client;

unsigned long lastConnectionTime = 0; // last time you connected to the server, in milliseconds

boolean lastConnected = false; // state of the connection last time through the main loop

const unsigned long postingInterval = 10*1000; // delay between updates, in milliseconds

void setup() {

//Initialize serial and wait for port to open:

Serial.begin(9600);

pinMode(led1,OUTPUT);

pinMode(led2,OUTPUT);

digitalWrite(led1, LOW);

digitalWrite(led2, LOW);

// check for the presence of the shield:

if (WiFi.status() == WL_NO_SHIELD) {

Serial.println("WiFi shield not present");

// don’t continue:

while(true);

}

// attempt to connect to Wifi network:

while ( status != WL_CONNECTED) {

Serial.print("Attempting to connect to SSID: ");

Serial.println(ssid);

// Connect to WPA/WPA2 network. Change this line if using open or WEP network:

status = WiFi.begin(ssid, pass);

// wait 10 seconds for connection:

delay(10000);

}

Serial.println("Connected to wifi");

printWifiStatus();

Serial.println("nStarting connection to server…");

// if you get a connection, report back via serial:

if (client.connect(server, 80)) {

Serial.println("connected to server");

// Make a HTTP request:

client.print("GET ");

client.println(location);

client.println("Host: theengineeringprojects.com");

// client.println("Connection: close");

client.println();

//readPage();

}else{

Serial.println("connection failed");

}

}

void loop(){

while (client.available()) {

c = client.read();

Serial.write(c);

CheckingStatus();

}

if (!client.connected() && lastConnected) {

Serial.println();

Serial.println("disconnecting.");

client.stop();

}

if(!client.connected() && (millis() – lastConnectionTime > postingInterval)) {

PingRequest();

}

lastConnected = client.connected();

}

void PingRequest(){

if (client.connect(server, 80)) {

// Serial.println("connected to server");

// Make a HTTP request:

client.print("GET ");

client.println(location);

client.println("Host: theengineeringprojects.com");

client.println("Connection: close");

client.println();

//readPage();

lastConnectionTime = millis();

}else{

//Serial.println("connection failed");

client.stop();

}

}

void CheckingStatus(){

inString[stringPos] = c;

if(c == '*')

{

statusLed = inString[stringPos – 1];

stringPos = 0;

// Serial.write(statusLed);

delay(500);

UpdatingStatus();

// delay(500);

// client.flush();

// delay(10000);

//PingServer();

}

stringPos ++;

}

void UpdatingStatus(){

if(statusLed == '1')

{

digitalWrite(led1, HIGH);

// Serial.write(‘OK’);

}

if(statusLed == '2')

{

digitalWrite(led1, LOW);

}

if(statusLed == '3')

{

digitalWrite(led2, HIGH);

}

if(statusLed == '4')

{

digitalWrite(led2, LOW);

}

}

void printWifiStatus() {

// print the SSID of the network you’re attached to:

Serial.print("SSID: ");

Serial.println(WiFi.SSID());

// print your WiFi shield’s IP address:

IPAddress ip = WiFi.localIP();

Serial.print("IP Address: ");

Serial.println(ip);

// print the received signal strength:

long rssi = WiFi.RSSI();

Serial.print("signal strength (RSSI):");

Serial.print(rssi);

Serial.println(" dBm");

}
