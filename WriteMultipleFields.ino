#include <WiFi.h>
#include <WebServer.h>
#include "secrets.h"
#include "ThingSpeak.h" 
#include "homepage.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>


// Wifi //
char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
WiFiClient  client;
WebServer server(80); // Creates a webserver on port 80

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

// GP2Y1014AU //
#define DUST_SENSOR_LED_PIN 4 // Initialising LED Pin
#define DUST_SENSOR_VO_PIN 34 // Initialising ADC Pin
#define DUST_CONVERSION_RATIO 0.5 // Conversion voltage to dust concentration
#define VOLTAGE_REF 5.0 // Reference voltage of ESP32
#define ADC_RESOLUTION 4096.0  // Used for the 12 - bit ADC used by the esp32

// OLED SCREEN //
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64 
#define OLED_reset -1 //
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_reset); // Initializes OLED display

// DHT11 //
#define DHT11_PIN 25 // GPIO pin example
#define DHTTYPE DHT11 // library needs to have defined dht type
DHT dht(DHT11_PIN, DHTTYPE); // Creating DHT object
float temperature = 0;
float humidity = 0; // globally declared variables

// SN GCJA5 //
float pm10 = 2.0;

// Buzzer //
#define BUZZER 19 

// Buzzer Thresholds //
#define PM10_t 200
#define TempCold_t 10
#define TempHot_t 20
#define HumidityLow_t 20
#define HumidityHigh_t 70
#define PM25_t 50

void setup() 
{
  Serial.begin(115200);  //Initialize serial monitor
  dht.begin(); // Initialize DHT11
  pinMode(DUST_SENSOR_LED_PIN, OUTPUT); // Initialize GP2Y1014AU
  pinMode(BUZZER, OUTPUT); // Initialize buzzer

  // Initializing the OLED screen 
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) // Standard address for OLED screen
  {
    Serial.println(F("OLED allocation failed"));
    for(;;); // Stops further excecution
  }
  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.clearDisplay();
  display.display();
  delay(2000); 
  
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Initialize ThingSpeak with wificlient
  
  // Connect to webserver //
  server.on("/", []()
  {
    server.send(200, "text/html", smartInhalerHomepage); // sends the homepahe html
  }
  );
  server.begin();
  Serial.println("Web Server Started.");
  // gets temperature as JSON
  server.on("/getTemperature", []() 
  {
    float temp = dht.readTemperature();
    server.send(200, "application/json", "{\"temperature\":" + String(temp, 1) + "}");
  }
  );

  server.on("/getHumidity", []()
  {
  float humid = dht.readHumidity();
  server.send(200, "application/json", "{\"humidity\":" + String(humid, 1) + "}");
}
);

  server.on("/getPollen", []()
  {
    float pollen = 0.0;
    server.send(200, "application/json", "{\"pollen\":" + String(pollen, 1) + "}");
  }
  );
    server.on("/getDust", []()
  {
    float dust = readDustSensor();
    server.send(200, "application/json", "{\"dust\":" + String(dust, 1) + "}");
  }
  );
}

void loop() 
{
   server.handleClient(); // Handles HTTP requests
  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected successfully.");
   
  }
 Serial.println("ESP32 IP: " + WiFi.localIP().toString());

  float pm25 = readDustSensor();
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
 
  display.clearDisplay();
  display.setCursor(0, 0);

  // Prints the PM2.5 concentration to the Serial Monitor
  Serial.print("PM 2.5 Concentration: ");
  Serial.print(pm25);
  Serial.println(" ug/m3");
  display.print("\n");
  display.print(" Dust: ");
  display.print(pm25);
  display.println(" ug/m3");
  
  Serial.print("PM 10 Concentration: ");
  Serial.print(pm10);
  Serial.print(" ug/m3\n");
  display.print(" Pollen: "); 
  display.print(pm10); 
  display.println(" ug/m3");
  

  // Checks if dht11 readings are valid //
  if(isnan(humidity) || isnan(temperature)) // if value is not a number error message will appear
  {
    Serial.println("Failed to read from DHT11");
  }
  else
  {
  // Prints the temperature & humidity to the Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");
  display.print(" Temperature: "); 
  display.print(temperature); 
  display.println(" C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");
  display.print(" Humidity:");
  display.print(humidity);
  display.println(" %");
  display.display(); // Updates the screen 
  delay(2000);
  }
  // Buzzer //
  if (pm10 > PM10_t || pm25 > PM25_t || temperature < TempCold_t|| temperature > TempHot_t|| humidity < HumidityLow_t || humidity > HumidityHigh_t) // compare readings against threshold levels
  {
    // if they exceed thresholds, buzzer will be sounded as it is considered a dangerous reading
    digitalWrite(BUZZER,HIGH);
    delay(1000);
    digitalWrite(BUZZER,LOW);
  }
  else
  {
    // otherwise it will be off
    digitalWrite(BUZZER,LOW);
  }

  // set the fields with the values
  ThingSpeak.setField(1, pm10);
  ThingSpeak.setField(2, pm25);
  ThingSpeak.setField(3, temperature);
  ThingSpeak.setField(4, humidity);

  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200)
  {
    Serial.println("Channel update successful.");
  }
  else
  {
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  
  delay(2000); // Wait 2 seconds before updating the channel 
}

// Converting ADC values from GP2Y1014AU //
float readDustSensor() 
{
  digitalWrite(DUST_SENSOR_LED_PIN, HIGH); // turns on infared LED 
  delayMicroseconds(280);
  
  int sensorValue = analogRead(DUST_SENSOR_VO_PIN); // Reads analog value 
  digitalWrite(DUST_SENSOR_LED_PIN, LOW); // Turns off after reading

  float voltage = sensorValue * (VOLTAGE_REF / ADC_RESOLUTION); // Converts ADC to voltage
  float pmConcentration = voltage / DUST_CONVERSION_RATIO; // Converts voltage to dust concentration
  return pmConcentration;
}
