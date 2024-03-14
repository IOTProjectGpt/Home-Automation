
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
#define MQTT_PASS "aio_QnFH446bAoFlmPiwv3Ebae0pxwJ7"
/////////////////////////////////////////////////Feeds///////////////////////////////////////////////////////////
// Create WiFi client and Adafruit MQTT client instances
WiFiClient client;	
Adafruit_MQTT_Client mqtt(&client, MQTT_SERV, MQTT_PORT, MQTT_NAME, MQTT_PASS);


// Create MQTT Publish object for gas sensor value
Adafruit_MQTT_Publish flame = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/g/gas");

// Define digital pins for the gas sensor and buzzer
int gas_sensor=D6;
int buzzer=D8;
int f1 = 0;
int f2 = 0;

// Setup function
void setup() {
// Intialize the LCD
lcd.init();
lcd.backlight();

// Set pin modes
pinMode(gas_sensor,INPUT);
pinMode(buzzer,OUTPUT);

// Start serial communication
Serial.begin(9600);
Serial.print("Connecting to ");
Serial.println(WLAN_SSID);
lcd.setCursor(0,0);
lcd.print("Gas Detection");
lcd.setCursor(0,1);
lcd.print(" System");

//Connect to WiFi network
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

//Main Loop
void loop() {
//Read gas sensor value
int output=digitalRead(gas_sensor);

//Publish gas sensor value to MQTT topic
if (flame.publish(output)) {
Serial.println("gas value updated");
delay(2000);
}

//Display gas detection status on the LCD and control the buzzer
Serial.println(output);
if(output==0){
if(f1 == 0){
f1=1;
f2=0;
lcd.clear();
}
digitalWrite(buzzer,HIGH);
lcd.setCursor(0,0);
lcd.print("gas detected"); 
}
else{
if(f2==0){
f2=1;
f1=0;
lcd.clear();
}
digitalWrite(buzzer,LOW);
lcd.setCursor(0,1);
lcd.print("No gas detected"); 
}
} 

//Function to establish MQTT server
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
}