#define BLYNK_TEMPLATE_ID "TMPL6hLRYw2Ua"
#define BLYNK_TEMPLATE_NAME "Gas Leakage Detector"
#define BLYNK_AUTH_TOKEN "MdNO8UfAYqei6qXmg957RwnDt7DepVNT"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED settings
#define WIDTH 128
#define HEIGHT 64
#define OLED_ADDR 0x3C
Adafruit_SSD1306 display(WIDTH, HEIGHT, &Wire, -1);

// Hardware Pins
#define MQ2_PIN 34        // Analog input
#define RELAY_PIN 26    // Relay control
#define BUZZER_PIN 27     // Buzzer

// Gas threshold
int gasThreshold = 3500;

// WiFi credentials
char ssid[] = "Hajra";
char pass[] = "oooooooo";

void setup() {
  Serial.begin(115200);
  // Initialize Pins
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // Fan OFF
  // Fan OFF
  delay(100); // Fan OFF (correct for active-LOW relay)
  // Fan OFF

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  // OLED Setup
  Wire.begin(21, 22);
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Connect to Blynk
  Serial.println("Connecting to Blynk...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();

  int gasValue = analogRead(MQ2_PIN);

  // Update OLED
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Gas Leakage System");
  display.setCursor(0, 20);
  display.print("Gas: ");
  display.println(gasValue);
  display.display();

  // Send value to Blynk (Virtual Pin V1)
  Blynk.virtualWrite(V1, gasValue);

  Serial.print("Gas Value: ");
  Serial.println(gasValue);

  // GAS HIGH CONDITION
  if (gasValue > gasThreshold) {
    Serial.println("ALARM TRIGGERED");

    digitalWrite(RELAY_PIN, LOW);     // Fan ON
    digitalWrite(BUZZER_PIN, HIGH);   // Buzzer ON

    Blynk.logEvent("gas_alert", "Gas Leakage Detected!");
  } else {
    digitalWrite(RELAY_PIN, HIGH);    // Fan OFF
    digitalWrite(BUZZER_PIN, LOW);
}
  delay(500);
}