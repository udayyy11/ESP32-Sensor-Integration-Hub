#include <WiFi.h>
#include "ThingSpeak.h"
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

// ----------- WiFi and ThingSpeak Credentials -----------
const char* ssid = "lap";         // Your WiFi network name
const char* password = "Udaykumar"; // Your WiFi password

unsigned long myChannelNumber = 1234567; // CHANGE THIS to your Channel ID
const char* myWriteAPIKey = "2U856PX49VJK4FYI"; // Your ThingSpeak Write API Key

// ----------- Hardware Pin and I2C Address Definitions -----------
#define DHTPIN 4        // The GPIO pin connected to the DHT11's DATA pin
#define DHTTYPE DHT11   // We are using the DHT11 sensor

// Set the LCD address. Common addresses are 0x27 or 0x3F.
int lcdAddress = 0x27;
int lcdColumns = 16;
int lcdRows = 2;

// ----------- Object Initialization -----------
WiFiClient client;
LiquidCrystal_I2C lcd(lcdAddress, lcdColumns, lcdRows);
DHT dht(DHTPIN, DHTTYPE);

// ----------- Global Variables -----------
unsigned long lastUpdateTime = 0;
const int updateInterval = 20000; // ThingSpeak free plan allows updates every ~15 seconds. 20s is safe.

// ===============================================================
// SETUP FUNCTION
// ===============================================================
void setup() {
  Serial.begin(115200);

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");

  // Initialize DHT Sensor
  dht.begin();

  // Connect to WiFi
  connectWiFi();

  // Initialize ThingSpeak
  ThingSpeak.begin(client);
}

// ===============================================================
// MAIN LOOP
// ===============================================================
void loop() {
  // The loop() function should run quickly. We use millis() for timing.
  if (millis() - lastUpdateTime > updateInterval) {
    readSensorAndUpload();
    lastUpdateTime = millis();
  }
}

// ===============================================================
// SUPPORTING FUNCTIONS
// ===============================================================

void connectWiFi() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Connecting WiFi");
  Serial.println("Connecting to WiFi...");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  int counter = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    lcd.setCursor(counter, 1);
    lcd.print(".");
    counter++;
    if (counter > 15) { // If it takes too long, reset the dots on the LCD
        lcd.setCursor(0, 1);
        lcd.print("                ");
        counter = 0;
    }
  }

  Serial.println("\nWiFi Connected!");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi Connected!");
  delay(1000);
}

void readSensorAndUpload() {
  // Read Humidity and Temperature from DHT11
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // Celsius

  // Check if any reads failed and exit early to try again.
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor Read");
    lcd.setCursor(0, 1);
    lcd.print("Error!");
    return;
  }

  // --- Print to Serial Monitor for debugging ---
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C");

  // --- Display on LCD ---
  lcd.clear();
  // Line 0: Temperature
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print((char)223); // Degree symbol
  lcd.print("C");
  // Line 1: Humidity
  lcd.setCursor(0, 1);
  lcd.print("Humi: ");
  lcd.print(humidity);
  lcd.print(" %");

  // --- Send data to ThingSpeak ---
  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, humidity);

  int httpCode = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  if (httpCode == 200) {
    Serial.println("Channel update successful.");
  } else {
    Serial.println("Problem updating channel. HTTP error code " + String(httpCode));
  }
}