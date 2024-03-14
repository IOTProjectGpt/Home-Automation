// Include required libraries
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
// Define LCD and WiFi credentials
LiquidCrystal_I2C lcd(0x27,16,2); 
#define WLAN_SSID "Galaxy"
#define WLAN_PASS "gptmasab"
// Define MQTT server and authentication details
#define MQTT_SERV "io.adafruit.com"
#define MQTT_PORT 1883 
#define MQTT_NAME "AUTOMATION_2344"
#define	MQTT_PASS "aio_QnFH446bAoFlmPiwv3Ebae0pxwJ7"
/////////////////////////////////////////////////Feeds///////////////////////////////////////////////////////////
// Define MQTT server and authentication details
WiFiClient client;	
Adafruit_MQTT_Clientmqtt(&client,MQTT_SERV, MQTT_PORT, MQTT_NAME, MQTT_PASS);
// Define MQTT server and authentication details
Adafruit_MQTT_Publish	flame	= Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/flame");
int flame_sensor=D6;
int buzzer=D8;
int f1 = 0;
int f2 = 0;
void setup() {
lcd.init();
// Print a message to the LCD.
lcd.backlight();
pinMode(flame_sensor,INPUT);
pinMode(buzzer,OUTPUT);
Serial.begin(9600);
Serial.print("Connecting to ");
Serial.println(WLAN_SSID);
lcd.setCursor(0,0);
lcd.print("Fire Detection");
lcd.setCursor(0,1);
lcd.print(" System");

WiFi.begin(WLAN_SSID, WLAN_PASS);
while (WiFi.status() != WL_CONNECTED)
{
delay(500);
Serial.print(".");
}
Serial.println();
Serial.println("WiFi connected");
Serial.println("IP address: ");
Serial.print(WiFi.localIP());

MQTT_connect();
}
void loop() {
int output=digitalRead(flame_sensor);
if (flame.publish(output)) {
Serial.println("flame value updated");
delay(2000);
}
Serial.println(output);
if(output==0){
if(f1 == 0){
f1=1;
f2=0;
lcd.clear();
}
digitalWrite(buzzer,HIGH);
lcd.setCursor(0,0);
lcd.print("fire detected"); 
}
else{
if(f2==0){
f2=1;
f1=0;
lcd.clear();
}
digitalWrite(buzzer,LOW);
lcd.setCursor(0,1);
lcd.print("No fire detected"); 
}
} 
void MQTT_connect()
{
int8_t ret;
if (mqtt.connected())
{
return;
}
Serial.print("Connecting to MQTT... ");
uint8_t retries = 3;
while ((ret = mqtt.connect()) != 0)
{
Serial.println(mqtt.connectErrorString(ret));
Serial.println("Retrying MQTT connection in 5 seconds...");
mqtt.disconnect();
delay(5000);
retries--;
if (retries == 0)
{
while (1);	
}
}
Serial.println("MQTT Connected!");
