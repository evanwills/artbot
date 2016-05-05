#include <Wire.h>    // these are all the libraries we need for working with our screen.
#include <SPI.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define OLED_RESET 4                  // here we get the screen ready for sending instructions to using the libraries above
Adafruit_SSD1306 display(OLED_RESET);

const int MAX_X = 128;
const int MAX_Y = 64;


class wormCoord
{
	private:
		int point[6] = { 0, 0, 0, 0, 0, 0 };
		int randIncPoint = 7;
		int randPoint = 0;
		int incPoint = 0;
		int maxPoint = 0;

	public:
		virtual int [6]getCoord() {
			int a = 0;
			int b = 0;

			for( a = 6; a >= 0 ; a = -1 ) {
				b = a - 1;
				point[a] = point[b];
			}

			if( point[0] >= maxPoint || point[0] < 0) {
				incPoint = -incPoint;
			}

			if( randPoint == randIncPoint ) {
				randPoint = 0;
				point[0] = point[0] + incPoint;
			}


			point[0] = point[0] + incPoint;

//			display.drawPixel( x[a] , y[a] , 1 );
//			display.drawCircle(x[a] , y[a] , 3 ,1 );
//			display.display();

			randPoint = randPoint + 1;
			return point;
		}


		wormCoord( int coord , int initInc , int randIncExtra , int max ) {
			int a = 0;

			point[0] = coord;
			incPoint = initInc;
			randIncPoint = randIncExtra;
			maxPoint = max;

			for( a = 0 ; a < 6 ; a = a + 1 ) {
				this->getCoord();
			}
		}
};

class worm {
	wormCoord *x;
	wormCoord *y;

	public:
		worm() {
			randomSeed( micros()*analogRead(0) );
			long int tmpInc;

//			randomSeed( micros()*analogRead(0) );
			tmpInc = random( 1 , 5 );
			tmpInc = (int) tmpInc;
			if( random(0,1) == 0 ) {
				tmpInc = -tmpInc;
			}
//			randomSeed( micros()*analogRead(0) );
			x = new wormCoord( (int) random( 0 , MAX_X ) , tmpInc , (int) random( 3 , 27 ) , MAX_X );

//			randomSeed( micros()*analogRead(0) );
			tmpInc = random( 1 , 5 );
			tmpInc = (int) tmpInc;
			if( random(0,1) == 0 ) {
				tmpInc = -tmpInc;
			}
//			randomSeed( micros()*analogRead(0) );
			y = new wormCoord( (int) random( 0 , MAX_Y ) ,  tmpInc , (int) random( 3 , 27 ) , MAX_Y );
		}

		virtual void drawWorm() {
			int a = 0;
			int tmpX[6];
			int tmpY[6];

			tmpX = x->getCoord();
			tmpY = y->getCoord();

//			display.drawPixel(tmpX[0], tmpY[0], 1);

			display.drawCircle( tmpX[0] , tmpY[0] , 3 , 1 );

			for( a = 1 ; a < 6 ; a = a +1 ) {
				display.drawPixel(tmpX[a], tmpY[a], 1);
			}

			display.display();
		}
};

worm * worm1;
worm * worm2;
worm * worm3;
worm * worm4;


// char status = '';
//this is a container that can only fit integers inside of it - an integer is a whole number (the ones we count with)
//this container is called a variable. Variables are central to maths and computing.

void setup() {

	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // tell the Arduino that our little OLED screen is 128 x 64 pixels
	display.clearDisplay();
//	display.setTextColor(WHITE);

	worm1 = new worm();
	worm2 = new worm();
	worm3 = new worm();
	worm4 = new worm();
};


void loop() {
	// screen 128 x 64
	display.setCursor(0,0);  // this moves our cursor right back to the top left pixel.. we should talk about this.
	display.clearDisplay();  // we need to clear our screen ever time we want to draw something new on it - other wise it will just write on top of what was there.

	worm1->drawWorm();
	worm2->drawWorm();
	worm3->drawWorm();
	worm4->drawWorm();

	display.display();
};
