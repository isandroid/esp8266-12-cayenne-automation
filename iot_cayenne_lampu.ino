// This example shows how to connect to Cayenne using an ESP8266 and send/receive sample data.
// Make sure you install the ESP8266 Board Package via the Arduino IDE Board Manager and select the correct ESP8266 board before compiling. 

//#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>
#include "iot_rahasia.h"

// WiFi network info.
char ssid[] = IOT_SSID;
char wifiPassword[] = IOT_SSID_PWD;

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = MQTT_USERNAME;
char password[] = MQTT_PASSWORD;
char clientID[] = MQTT_CLIENT_ID;

//int led=LOW;
unsigned long lastMillis = 0;

void setup() {
	Serial.begin(9600);
  pinMode(2, INPUT);   // button
  pinMode(13, OUTPUT); // relay
	Cayenne.begin(username, password, clientID, ssid, wifiPassword);
}

void loop() {
	Cayenne.loop();

//	//Publish data every 10 seconds (10000 milliseconds). Change this value to publish at a different interval.
//	if (millis() - lastMillis > 10000) {
//		lastMillis = millis();
//		//Write data to Cayenne here. This example just sends the current uptime in milliseconds.
//		//Cayenne.virtualWrite(0, lastMillis);
//		//Some examples of other functions you can use to send data.
//		//Cayenne.celsiusWrite(1, 22.0);
//		//Cayenne.luxWrite(2, 700);
//		//Cayenne.virtualWrite(3, 50, TYPE_PROXIMITY, UNIT_CENTIMETER);
//	}

//  if(digitalRead(2)==HIGH && led==LOW)
//  {
//    digitalWrite(13, HIGH);
//    led=HIGH;
//    Cayenne.virtualWrite(1,"1");
//    while(digitalRead(2)==HIGH)
//    {
//      delay(10);
//    }
//  }
//  
//  if(digitalRead(2)==HIGH && led==HIGH)
//  {
//    digitalWrite(13, LOW);
//    led=LOW;
//    Cayenne.virtualWrite(1,"0");
//    while(digitalRead(2)==HIGH)
//    {
//      delay(10);
//    }
//  }
}

//Default function for processing actuator commands from the Cayenne Dashboard.
//You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.
CAYENNE_IN_DEFAULT()
{
	CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());
	//Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
  if (request.channel = 1)
  {
    String value;
    value = (String)getValue.asString();

    if (value == "1")
    {
      digitalWrite(13, HIGH);
    }
    else
    {
      digitalWrite(13, LOW);
    }
  }
}
