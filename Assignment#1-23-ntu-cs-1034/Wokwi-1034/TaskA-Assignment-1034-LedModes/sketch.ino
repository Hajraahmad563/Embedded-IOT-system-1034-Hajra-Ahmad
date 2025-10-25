//Assingment#1 
//Task: A
//Title: LED MODES (ON,OFF,BLINK,PWM FADE)
//Name: Hajra Ahmad
//REG#: 23-ntu-cs-1034

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pin configuration
#define BUTTON_MODE 25
#define BUTTON_RESET 26
#define LED1 18
#define LED2 19
#define BUZZER 27

int mode = 0;  // 0=OFF, 1=Alternate Blink, 2=Both ON, 3=Fade
unsigned long lastDebounce = 0;
const int debounceDelay = 200;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BUTTON_MODE, INPUT_PULLUP);
  pinMode(BUTTON_RESET, INPUT_PULLUP);

  // Initialize OLED
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("System Ready!");
  display.display();
}

void loop() {
  if (digitalRead(BUTTON_MODE) == LOW && millis() - lastDebounce > debounceDelay) {
    mode = (mode + 1) % 4;
    updateDisplay();
    lastDebounce = millis();
  }

  if (digitalRead(BUTTON_RESET) == LOW) {
    mode = 0;
    updateDisplay();
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    delay(200);
  }

  handleModes();
}

void handleModes() {
  switch (mode) {
    case 0: // Both OFF
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      break;

    case 1: // Alternate Blink
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
      delay(300);
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH);
      delay(300);
      break;

    case 2: // Both ON
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      break;

    case 3: // PWM Fade
      for (int brightness = 0; brightness <= 255; brightness += 5) {
        ledcWrite(0, brightness);
        ledcWrite(1, 255 - brightness);
        delay(20);
      }
      for (int brightness = 255; brightness >= 0; brightness -= 5) {
        ledcWrite(0, brightness);
        ledcWrite(1, 255 - brightness);
        delay(20);
      }
      break;
  }
}

void updateDisplay() {
  display.clearDisplay();
  display.setCursor(0, 10);
  display.print("Mode: ");
  switch (mode) {
    case 0: display.println("Both OFF"); break;
    case 1: display.println("Alternate Blink"); break;
    case 2: display.println("Both ON"); break;
    case 3: display.println("PWM Fade"); break;
  }
  display.display();
}
