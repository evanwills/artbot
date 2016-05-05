#include <Wire.h>    // these are all the libraries we need for working with our screen.
#include <SPI.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define OLED_RESET 4                  // here we get the screen ready for sending instructions to using the libraries above
Adafruit_SSD1306 display(OLED_RESET);


void setup(void) {
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // tell the Arduino that our little OLED screen is 128 x 64 pixels
	display.clearDisplay();
	Serial.begin(9600); // This allows the Arduino to send info back to the computer, for debugging
}

int photocellReading = 0;

void loop(void) {
	photocellReading = analogRead(0); // make sure that your photoresistor is connected to pin 0

	Serial.print("Analog reading = ");
	Serial.println(photocellReading); // the raw analog reading

	display.clearDisplay();
	display.drawCircle(64, 32, photocellReading / 10,1 );

	delay(100);
	display.display();
}