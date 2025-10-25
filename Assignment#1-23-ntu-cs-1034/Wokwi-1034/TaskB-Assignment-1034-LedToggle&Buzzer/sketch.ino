//Assingment#1 
//Task: B
//Title: LED Toggle and Buzzer
//Name: Hajra Ahmad
//REG#: 23-ntu-cs-1034


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define BUTTON 25
#define LED 18
#define BUZZER 27

bool ledState = false;
unsigned long pressStart = 0;
bool buttonPressed = false;

void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // Initialize OLED
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("Ready for Press");
  display.display();
}

void loop() {
  if (digitalRead(BUTTON) == LOW) {
    if (!buttonPressed) {
      buttonPressed = true;
      pressStart = millis();
    }
  } else if (buttonPressed) {
    buttonPressed = false;
    unsigned long pressDuration = millis() - pressStart;

    if (pressDuration > 1500) {
      // Long press: buzzer tone
      tone(BUZZER, 1000, 500);
      updateDisplay("Long Press - Buzzer");
    } else {
      // Short press: toggle LED
      ledState = !ledState;
      digitalWrite(LED, ledState);
      updateDisplay("Short Press - LED Toggled");
    }
  }
}

void updateDisplay(String msg) {
  display.clearDisplay();
  display.setCursor(0, 10);
  display.println(msg);
  display.display();
}
