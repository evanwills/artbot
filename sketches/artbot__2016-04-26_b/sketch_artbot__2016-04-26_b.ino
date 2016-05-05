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
int b = 1;
int c = 0;
int d = 0;
// char status = '';
//this is a container that can only fit integers inside of it - an integer is a whole number (the ones we count with)
//this container is called a variable. Variables are central to maths and computing.

void setup() {

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // tell the Arduino that our little OLED screen is 128 x 64 pixels
  display.clearDisplay();
  display.setTextColor(WHITE);


}

void loop() {
  display.setCursor(0,0);  // this moves our cursor right back to the top left pixel.. we should talk about this.
  display.clearDisplay();  // we need to clear our screen ever time we want to draw something new on it - other wise it will just write on top of what was there.
  display.setTextSize(1);  // this sets the text size for anything below this point - see what happens when you chnage it.
//  display.println("Enter via the Polygon Door!");
//  display.println("");
  display.setTextSize(2); // this sets the text size for anyhting below this point - see what happens when you chnage it.
  if ( digitalRead(2) == HIGH ) {
    x = 0;
    y = 1;
//    z = 0;
    a = 0;
    b = 1;
    c = 0;
    d = 0;
  }
  if ( x < 23) {
    c = a + b;
    a = b;
    b = c;
//    status = ' - Max';
    d = x;
  }
  display.print("1+_ ");
  display.print(x); // this prints the variable that we set at the top to our displays memory.... the container called X that onlyy fits integrers (numbers);
  display.println("");
  display.print("2+ ");
  display.print(y);
  display.println("");
//  display.print("3 + : ");
//  display.print(z);
//  display.print(status);
//  display.println("");
  display.print("step ");
  display.print(d);
  display.println(": ");
  display.print(a);

  display.display(); // this prints whats in the displays memory to the screen
  x = x + 1;  // this adds one to X every time we run through the 'loop'
  if ( y * 2 > 0) {
    y = y * 2;  // this adds one to y every time we run through the 'loop'
  }
//  z = z + 3;  // this adds one to z every time we run through the 'loop'
//  delay(100);
}
