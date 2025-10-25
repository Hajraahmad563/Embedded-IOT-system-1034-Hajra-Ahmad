// Hajra Ahmad 1034
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// --- Smiley face bitmap (16x16) ---
const unsigned char PROGMEM smiley_bmp[] = {
  0b00000111, 0b11100000,
  0b00011111, 0b11111000,
  0b00111111, 0b11111100,
  0b01111111, 0b11111110,
  0b01110000, 0b00001110,
  0b11100111, 0b11100111,
  0b11101111, 0b11110111,
  0b11101111, 0b11110111,
  0b11100111, 0b11100111,
  0b11110000, 0b00011111,
  0b01111100, 0b00111110,
  0b00111111, 0b11111100,
  0b00011111, 0b11111000,
  0b00001111, 0b11110000,
  0b00000111, 0b11100000,
  0b00000011, 0b11000000
};

void setup() {
  Wire.begin(21, 22);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    for (;;);
  }

  display.clearDisplay();

  // Draw smiley face
  display.drawBitmap(56, 24, smiley_bmp, 16, 16, SSD1306_WHITE);
  display.display();
  delay(2000);
  display.clearDisplay();

  // Display name
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 10);
  display.println("Hello from:");
  display.display();

  display.setTextSize(2);
  display.setCursor(5, 30);
  display.println("Hajra :)");
  display.display();
}

void loop() {
  // Keep static display
}
