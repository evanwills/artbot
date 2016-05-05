#include <Wire.h>    // these are all the libraries we need for working with our screen.
#include <SPI.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define OLED_RESET 4                  // here we get the screen ready for sending instructions to using the libraries above
Adafruit_SSD1306 display(OLED_RESET);

int x = 0;  // this is an important new step - here we are making a container called X to put a number in.
int y = 1;
//int z = 0;
//bool yMax = false;
int a = 0;
int b = 0;
int incA = 1;
int incB = 1;
// char status = '';
//this is a container that can only fit integers inside of it - an integer is a whole number (the ones we count with)
//this container is called a variable. Variables are central to maths and computing.

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // tell the Arduino that our little OLED screen is 128 x 64 pixels
  display.clearDisplay();
  //  display.setTextColor(WHITE);
}

void loop() {
  // screen 128 x 64
  display.setCursor(0,0);  // this moves our cursor right back to the top left pixel.. we should talk about this.
  display.clearDisplay();  // we need to clear our screen ever time we want to draw something new on it - other wise it will just write on top of what was there.

  if( a > 128 ) {
    incA = -1;
  } else if( a <= 0 ){
    incA = 1;
  }
  a = a + incA;

  if( b > 64 ) {
    incB = -1;
  } else if( b <= 0 ) {
    incB = 1;
  }
  b = b + incB;

  display.drawPixel(a, b, 1);
  display.display();
}
