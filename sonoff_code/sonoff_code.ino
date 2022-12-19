#include <Arduino.h>

#define BLYNK_PRINT Serial
 
 
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <BlynkSimpleEsp8266.h>
#include "power.h"
ESP8266PowerClass power_dev;

//interrupt
#include <Ticker.h>
Ticker periodicTicker;

const char* ssid = "yourSSID";
const char* password = "yourwifipassword";

//Your Domain name with URL path or IP address with path
const char* serverTarget1 = "http://ip:3000/api/control/getled2"; //or without port if already set in server
const char* serverTarget2 = "http://ip:3000/api/telemetry/device2"; //or without port if already set in server

 
//Blynk Device Token
// Go to the Project Settings (nut icon).
char auth[] =  "blynkToken";
 
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "your_ssid";
char pass[] = "your_password";
 
BlynkTimer timer;

int ledPin = 13;
int relayPin = 12;
// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void SEND_POWER_BLYNK();
void POST_POWER();
 
void setup()
{
  pinMode(ledPin,OUTPUT);
  pinMode(relayPin,OUTPUT);
  digitalWrite(ledPin,HIGH);
  delay(1000);
  power_dev.enableMeasurePower();
  power_dev.startMeasure();
  Serial.begin(115200);
  WiFi.begin(ssid, pass);  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());  
  
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  
  while (Blynk.connect() == false) {
    // Wait until connected
  }
  Serial.println("Connected to Blynk server");

  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing.");
  periodicTicker.attach_ms(5000, POST_POWER);
 
 
  // Setup a function to be called every 5 second
  timer.setInterval(5000L, SEND_POWER_BLYNK);
}
 
void loop()
{
  Blynk.run();
  timer.run();
   if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
      WiFiClient client;
      
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverTarget1);

    http.addHeader("Content-Type", "application/json");
    http.addHeader("Accept", "application/json");
    
    // If you used token
    // http.addHeader("Accept", "Bearer yourtoken");
      // Send HTTP GET request
      int httpResponseCode1 = http.GET();
        if (httpResponseCode1>0) {
          Serial.print("HTTP Response code: ");
          Serial.println(httpResponseCode1);
          String payload = http.getString();
          Serial.println(payload);
          if(payload == "1"){
            digitalWrite(ledPin, HIGH);
            digitalWrite(relayPin, HIGH);
          }
          else{
            digitalWrite(ledPin, LOW);
            digitalWrite(relayPin, HIGH);
          }
        }
        
        else {
        Serial.print("HTTP Response code1: ");
        Serial.println(httpResponseCode1);
        }
        http.end();
        }
      else {
        Serial.println("WiFi Disconnected");
      }
}
void SEND_POWER_BLYNK()
{
  float number = power_dev.getPower();
  String h = String(number);
 
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V10, h);
}

void POST_POWER(){
   HTTPClient http;
    WiFiClient client;
    http.begin(client, serverTarget2);

    http.addHeader("Content-Type", "application/json");
    http.addHeader("Accept", "application/json");
    
    // If you used token
    // http.addHeader("Accept", "Bearer yourtoken");
               // Data to send with HTTP POST
      float dataa= random(10.0, 100.0);
      String packet = "{\"data\": \"" + String(dataa) + "\"" + "}";
     
      //packet.concat((",\"TDS\":"));
      //packet.concat(tdsValue);
      
      Serial.println(packet);
      // Send HTTP POST request
      int httpResponseCode2 = http.POST(packet);
      
      Serial.print("HTTP Response code2: ");
      Serial.println(httpResponseCode2);
      
      // Free resources
      http.end();
