#include "DHT.h"
#include <WiFi.h>
void handleAutoMode();
/*ALL SERIAL COMMUNICATION DATA STERT*/
void SerialSetup() {
 Serial.begin(115200);
 Serial.println("");
}
/*ALL SERIAL COMMUNICATION DATA ENDS*/
/*ALL TEMPERATURE SENSOR DATA STARTS*/
#de昀椀ne DHTPIN 14 //DHT SENSOR IS CONNECTED TO D14 (DIGITAL PIN 14)
#de昀椀ne DHTTYPE DHT11 //TYPE IS DHT11
/*INITIALIZE DHT11 SENSOR*/
DHT dht(DHTPIN, DHTTYPE);
void DHTsetup() {
 Serial.println("DHTxx test");
 dht.begin();
}
昀氀oat getTemp() {
 //wait a few seconds between measurements
 delay(2000);
 //READING TEMPERATURE OR HUMIDITY TAKES ABOUT 250 ms
 //sensor readings may also be up to 2 sec 'old' (it is very slow sensor)
 昀氀oat h = dht.readHumidity();
 昀氀oat t = dht.readTemperature(); //read temperature as celcious
 昀氀oat f = dht.readTemperature(true); //read temperature as fahrenheit
 //check if any read failed and exit early (to try again)
 if (isnan(h) || isnan(t) || isnan(f))
 {
 Serial.println("Failed to read from DHT11 SENSOR");
 return 0;
 }

 昀氀oat hif = dht.computeHeatIndex(f,h); //compute heat index in fahrenheit
 昀氀oat hic = dht.computeHeatIndex(t,h,false); //compute heat index in celcious (i
fahrenheit - false)
 Serial.println("Temperature: ");
 Serial.println(t);
 Serial.println("°C");
 return t;
}
#de昀椀ne LDR_PIN 33
void LDRsetup()
{
 pinMode(LDR_PIN, INPUT);
}
bool isitLight()
{
 int lightState = digitalRead(LDR_PIN);
 if (lightState == HIGH) {
 Serial.println("it is dark");
 } else {
 Serial.println("it is light");
 }
 return !lightState;
}
const int trigpin = 12;
const int ecopin = 13;
#de昀椀ne sound_speed 0.034
#de昀椀ne CM_TO_INCH 0.393701
long dura琀椀on;
昀氀oat distanceCm;
昀氀oat distanceInch;
void ultraSonicSensorsetup()
{
 pinMode(trigpin, OUTPUT); //sets the trig pin as output
 pinMode(ecopin, INPUT); //stes the echo pin as input
}
昀氀oat getDistance() {
 digitalWrite(trigpin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigpin, LOW);
 //Reads the echo, return the sound wave travel 琀椀me in microseconds
 dura琀椀on = pulseIn(ecopin, HIGH);
 //calculates the distance
 distanceCm = dura琀椀on * sound_speed / 2;
 //CONVERT TO INCH
 distanceInch = distanceCm * CM_TO_INCH;
 //PRINT THE DISTANCE IN THE SERIAL MONITOR
 Serial.print("Distance (Cm): ");
 Serial.println(distanceCm);
 delay(1000);
 return distanceCm;
}
/*all ultrasonic sensor data ends*/
/*ALL Relay data starts*/
const int relay_pin1 = 27; //relay in1
const int relay_pin2 = 26; //relay in2
void relaySetup()
{
 pinMode(relay_pin1, OUTPUT);
 pinMode(relay_pin2, OUTPUT);
 digitalWrite(relay_pin1, HIGH);
 digitalWrite(relay_pin2, HIGH);
}
uint8_t previousRelay1State = 1;
uint8_t previousRelay2State = 1;
void setRelay(uint8_t relay_num, uint8_t val)
{
 if (relay_num == relay_pin1)
 {
 Serial.print("Light Relay:");
 Serial.println(val);
 val = !val;
 if (previousRelay1State != val)
 {
 digitalWrite(relay_pin1, val);
 }
 previousRelay1State = val;
 }
 if (relay_num == relay_pin2)
 {
 Serial.print("Fan Relay: ");
 Serial.println(val);
 val = !val;
 if (previousRelay2State != val)
 {
 digitalWrite(relay_pin2, val);
 }
 previousRelay2State = val;
 }
}
/*all relay data ends*/
/*all WiFi data starts*/
const char* WiFi_name = "Redmi 8"; const char* WiFi_pass = "lucky123";
WiFiServer Server(80); //default Server for WiFi is at port 80
void WiFiSetup()
{
 Serial.print("connec琀椀ng to ");
 Serial.print("WiFi_name");
 WiFi.begin(WiFi_name, WiFi_pass); //connec琀椀ng to the WiFi network
 while (WiFi.status() != WL_CONNECTED) // wai琀椀ng for the respond of WiFi
network
 {
 handleAutoMode();
 delay(500);
 Serial.print(".");
 }
 Serial.println("");
 Serial.print("connec琀椀on successful");
 Serial.print("IP address");
 Serial.println(WiFi.localIP()); //ge琀�ng the IP address
 Serial.println("Type the above IP address in Browser search bar");
 Server.begin(); //star琀椀ng the Server
}
/*all WiFi data ends*/
void handleAutoMode() {
 // Read all seneor data
 昀氀oat distance = getDistance();
 昀氀oat temp = getTemp();
 bool islight = isitLight();
 if (distance <= 10)
 {
 //person is present
 if (temp >= 20)
 {
 setRelay(relay_pin2, HIGH);
 }
 else
 {
 setRelay(relay_pin2, LOW);
 }
 if (islight == true) {
 //Day 琀椀me
 setRelay(relay_pin1, LOW);
 }
 else
 {
 //Night 琀椀me
 setRelay(relay_pin1, HIGH);
 }
 }

 else
 {
 //person is not present
 setRelay(relay_pin1, LOW);
 setRelay(relay_pin2, LOW);
 }
}
void setup() {
 SerialSetup();
 DHTsetup();
 LDRsetup();
 ultraSonicSensorsetup();
 relaySetup();
 WiFiSetup();
}
bool isManualMode = false;
void loop() {
 //handleAutoMode();
 WiFiClient client = Server.available(); //checking if any client request is available
or not
 if (client)
 {
 boolean currentlineisblank = true;
 String bu昀昀er = ""; //String is adata type in c++
 while (client.connected()) {
 if (client.available()) //if there is some client data available
 {
 char c = client.read();
 bu昀昀er+=c; //read a byte
 if (c == '\n' && currentlineisblank)
 ; //chack for new line charector
 {
 client.println("HTTP/1.1 200 OK");
 client.println("content.type: text/html");
 client.println();
 client.print("<HTML><琀椀tlt>ESP32</琀椀tle>");
 client.print("<body><h1>ESP32 standalone ralay control </h1>");
 client.print("<p>Light control</p>");
 client.print("<a href=\"/?lightOn\"\"></bu琀琀on>ON</bu琀琀on></a>");
 client.print("<a href=\"/?lighto昀昀\"\"></bu琀琀on>OFF</bu琀琀on></a>");
 client.print("<p>Fan control</p>");
 client.print("<a href=\"/?fanOn\"\"></bu琀琀on>ON</bu琀琀on></a>");
 client.print("<a href=\"/?fano昀昀\"\"></bu琀琀on>OFF</bu琀琀on></a>");
 client.print("<p>Manual control</p>");
 client.print("<a href=\"/?manualOn\"\"></bu琀琀on>ON</bu琀琀on></a>");
 client.print("<a href=\"/?manualo昀昀\"\"></bu琀琀on>OFF</bu琀琀on></a>");
 client.print("<body></HTML>");
 break; //break out of the whileloop
 }
 if (c == '\n') {
 currentlineisblank = true;
 bu昀昀er = "";
 }
 else if (c == '\n')
 {
 if (bu昀昀er.indexOf("GET /?lighto昀昀") >= 0) //if fails return -1 hence<=0
 {
 setRelay(relay_pin1, LOW);
 }
 if (bu昀昀er.indexOf("GET /?lightOn") >= 0)
 {
 setRelay(relay_pin1, HIGH);
 }
 if (bu昀昀er.indexOf("GET /?fano昀昀") >= 0)
 {
 setRelay(relay_pin2, LOW);
 }
 if (bu昀昀er.indexOf("GET /?fanOn") >= 0)
 {
 setRelay(relay_pin2, HIGH);
 }
 if (bu昀昀er.indexOf("GET /?manualOn") >= 0) {
 isManualMode = true;
 Serial.print("isManualMode: ");
 Serial.println(isManualMode);
 }
 if (bu昀昀er.indexOf("GET /?manualo昀昀") >= 0) {
 isManualMode = false;
 Serial.print("isManualMode: ");
 Serial.println(isManualMode);
 }
 } else {
 currentlineisblank = false;
 }
 } else {
 }
 }
 client.stop();
 }
 delay(2000);
 if (isManualMode == false) {
 Serial.println("AutoMode");
 handleAutoMode();
 } else {
 Serial.println("wai琀椀ng for manual control");
 }
}
