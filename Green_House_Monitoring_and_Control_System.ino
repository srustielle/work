// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#include "DHT.h"
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
SoftwareSerial s(5,6);
#define DHTPIN 2     // what pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);
float h,t,f,hic,hif;

void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  s.begin(9600);
  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);
  int smoke=analogRead(A0);
  int gas=analogRead(A1);
  int ldr=analogRead(A2);
  int mosi=analogRead(A3);
  Serial.print("smoke=");
  Serial.println(smoke);
  Serial.print("gas=");
  Serial.println(gas);
  Serial.print("ldr=");
  Serial.println(ldr);
Serial.print("mosi=");
  Serial.println(mosi);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\n");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\n");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");
  delay(3000);
  sendAndroidValues();
/*  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["data1"] = smoke;
  root["data2"] = gas;
  root["data3"] = mosi;
  root["data4"] = ldr;
  root["data5"] = t;
  root["data6"] = h;
if(s.available()>0)
{
 root.printTo(s);
} */
}
void sendAndroidValues()
{
  //puts # before the values so our app knows what to do with the data
  s.print('#');
  Serial.print('#');
  //for loop cycles through 2 sensors and sends values via serial
    String payload = "{\"d\":{\"humidity\":";
  payload += h;
  payload+="," "\"tempc\":";
  payload += t;
  payload+="," "\"tempf\":";
  payload += f;
  payload+="," "\"hic\":";
  payload += hic;
  payload+="," "\"hif\":";
  payload += hif;
  payload += "}}";
 Serial.print("Sending payload: ");
 Serial.println(payload);
 s.print(payload);
  s.println('~'); //used as an end of transmission character - used in app for string length
  Serial.println('~');
  delay(3000);        //added a delay to eliminate missed transmissions
}
