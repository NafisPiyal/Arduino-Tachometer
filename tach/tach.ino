// OLED 0.96" Display:
#include <Adafruit_GFX.h>  // Include core graphics library for the display.
#include <Adafruit_SSD1306.h>  // Include Adafruit_SSD1306 library to drive the display.
Adafruit_SSD1306 display(128, 64);  // Create display.
#include <Fonts/FreeMonoBold12pt7b.h>  // Add a custom font.

int pin = 2; // Hall sensor at pin 2

unsigned long rpm = 0;
unsigned long rev = 0;
unsigned long duration;

void revCount() {
  rev++;
}

void setup() {
  Serial.begin(115200);
  pinMode(pin, INPUT); //Sets sensor as input

  // OLED 0.96" Display:
  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);  // Initialize display with the I2C address of 0x3D.
  display.clearDisplay();  // Clear the buffer.
  display.setTextColor(WHITE);  // Set color of the text to white.
  display.setRotation(0);  // Set orientation. Goes from 0, 1, 2 or 3.
  display.setTextWrap(false);  // By default, long lines of text are set to automatically “wrap” back to the leftmost column.
  // To override this behavior (so text will run off the right side of the display - useful for
  // scrolling marquee effects), use setTextWrap(false). The normal wrapping behavior is restored
  // with setTextWrap(true).
  display.dim(0);  // Set brightness (0 is maximum and 1 is a little dim).
  Wire.setClock(400000L);
}

void loop() {

  duration = pulseIn(pin, FALLING, 2000000); //times the amount of microseconds the motor is not timing IR, Times out after 100000 uS. Raise the timeout for slower RPM readings. .5 second
  rpm = 60000.0 / duration * 1000; //See above

  //  if(digitalRead(pin) == LOW){
  //    rev++;
  //  }
  attachInterrupt(0, revCount, FALLING);

  Serial.print("RPM ");
  Serial.print(rpm);

  Serial.print(" REV ");
  Serial.print(rev);

  Serial.print(" DUR ");
  Serial.println(duration);

  // OLED 0.96" Display:
  // Convert variable into a string, so we can change the text alignment to the right:
  // It can be also used to add or remove decimal numbers.
  char string[10];  // Create a character array of 10 characters
  // Convert float to a string:
  dtostrf(rpm, 6, 0, string);  // (<variable>,<amount of digits we are going to use>,<amount of decimal digits>,<string name>)

  display.clearDisplay();  // Clear the display so we can refresh.
  display.setFont(&FreeMonoBold12pt7b);  // Set a custom font.
  display.setTextSize(0);  // Set text size. We are using a custom font so you should always use the text size of 0.
  display.setCursor(0, 20);  // (x,y).
  display.println("RPM:");  // Text or value to print.

  // Print variable with right alignment:
  display.setCursor(45, 20);  // (x,y).
  display.println(string);  // Text or value to print.

  char string2[10];  // Create a character array of 10 characters
  // Convert float to a string:
  dtostrf(rev, 6, 0, string2);  // (<variable>,<amount of digits we are going to use>,<amount of decimal digits>,<string name>)
  display.setTextSize(0);  // Set text size. We are using a custom font so you should always use the text size of 0.
  display.setCursor(0, 52);  // (x,y).
  display.println("REV:");  // Text or value to print.

  // Print variable with right alignment:
  display.setCursor(45, 52);  // (x,y).
  display.println(string2);  // Text or value to print.

  display.display();
}
