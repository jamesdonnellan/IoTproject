#include <WiFi.h>
#include "secrets.h"
#include "ThingSpeak.h" 

char ssid[] = SECRET_SSID;   // my network SSID
char pass[] = SECRET_PASS;   // my network password
int keyIndex = 0;            // my network key Index number 
WiFiClient client;
#define DUST_SENSOR_LED_PIN 16 
#define DUST_SENSOR_VO_PIN 34 // Initialising ADC Pin
#define DUST_CONVERSION_RATIO 0.17 // Conversion ratio 
#define VOLTAGE_REF 3.3          // Reference voltage of ESP32
#define ADC_RESOLUTION 4096.0  


unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;
float DustReading;
int number = 0;

void setup() 
{
  Serial.begin(115200);  //Initialize baud for serial monitor //
  while (!Serial) 
  {
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }
  
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Initializes ThingSpeak
}

void loop() 
{
  float pmValue = readDustSensor();

  // Prints the PM2.5 concentration to the Serial Monitor
  Serial.print("PM 2.5 Concentration: ");
  Serial.print(pmValue);
  Serial.println(" ug/m3");

  delay(2000); 
 
  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }

  // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
  // pieces of information in a channel.  Here, we write to field 1.
  int x = ThingSpeak.writeField(myChannelNumber, 2, pmValue, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  
  // change the value of this ----------------------------------------------------------------------- //
  number++;
  if(number > 99){
    number = 0;
  }
  
  delay(20000); // Wait 20 seconds to update the channel again
}
 float readDustSensor() {
  digitalWrite(DUST_SENSOR_LED_PIN, HIGH);    // Turn on the LED (low means on in some sensors)
  delayMicroseconds(280);                  // Wait for stabilization (per datasheet)
  
  int sensorValue = analogRead(DUST_SENSOR_VO_PIN); // Reading analog value from dust sensor
  delayMicroseconds(40);               
  
  digitalWrite(DUST_SENSOR_LED_PIN, LOW);   // Turn off the LED

  // Converts the analog reading to voltage
  float voltage = sensorValue * (VOLTAGE_REF / ADC_RESOLUTION);

  // Converts the voltage to PM2.5 concentration in µg/m3
  float pmConcentration = voltage / DUST_CONVERSION_RATIO;

  return pmConcentration;
}
