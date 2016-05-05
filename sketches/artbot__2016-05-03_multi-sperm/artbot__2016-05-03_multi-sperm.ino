#include <Wire.h>    // these are all the libraries we need for working with our screen.
#include <SPI.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define OLED_RESET 4                  // here we get the screen ready for sending instructions to using the libraries above
Adafruit_SSD1306 display(OLED_RESET);

const int MAX_X = 128;
const int MAX_Y = 64;

/**
 * @class incrementor steps an increment until the maximum is reach
 *			if max is -1 nothing is incremented and
 *			incrementor::limitReached() will always return false;
 */
class incrementor
{
	private:
		int inc = 0;
		int max = 1;
		bool doInc = true;

	public
		incrementor( int incLimit ) {
			if( incLimit < 0 ) {
				incLimit = -incLimit;
			}
			this->max = incLimit;
			if( this->max < 0 ) {
				this->doInc = false;
				this->max = -1;
			}
		}

		bool limitReached() {
			bool output = false;
			if( this->doInc == true ) {
				if( this->inc == this->max ) {
					output = true;
					this->inc = 0;
				} else {
					this->inc = this->inc + 1;
				}
			}
			return output;
		}

}

class wormCoord
{
	private:
		bool doRandomDirChange = false;
		int incPoint = 1;
		incrementor * loopsPerInc;
		int maxPoint = 0;
		int point = { 0, 0, 0, 0, 0, 0 };
		incrementor * preSetPoint;
		int randIncPointMax = 0;
		int randIncPointMaxThresh = 0;
		bool randomDirChange() {
			if( this->doRandomDirChange == true && random(0, this->randIncPointMax) >= this->randIncPointMaxThresh ) {
				return true;
			}
			return false;
		}

	public:
		// This method returns an array with 6 items
		virtual int *getCoord() {
			int a = 0;
			int b = 0;

			if( this->loopsPerInc->limitReached() == true ) {
				for( a = 6; a >= 0 ; a = -1 ) {
					b = a - 1;
					this->point[a] = this->point[b];
				}

				if( this->point[0] >= this->maxPoint || this->point[0] < 0 || this->randomDirChange() == true ) // || random( 0, randomIncPoint ) >= preSetIncPointMaxThresh ) {
					this->incPoint = -this->incPoint;
				}

				if( this->preSetPoint->limitReached() == true ) {
					this->point[0] = this->point[0] + this->incPoint;
				}

				this->point[0] = this->point[0] + this->incPoint;
			}

			return this->point;
		}


		wormCoord( int coord , int loopsPerIncrement , int randIncExtra , int max ) {
			int a = 0;

			this->point[0] = coord;
			this->loopsPerInc = new incrementor(loopsPerIncrement);
			this->preSetIncPoint = new incrementor( randIncExtra );
			this->maxPoint = max;

			for( a = 0 ; a < 6 ; a = a + 1 ) {
				this->getCoord();
			}
		}

		void setRandDirChange( int max , int threshold ) {
			if( max > 0 ) {
				this->randIncPointMax = max;
				if( threshold > 0 && threshold < max ) {
					this->randIncPointMaxThresh = threshold;
				} else {
					this->randIncPointMaxThresh = int( max * 0.9 );
				}
				this->doRandomDirChange = true;
			}
		}
};

class worm {
	wormCoord *x;
	wormCoord *y;

	public:
		worm( int maxX, int maxY ) {
			randomSeed( micros()*analogRead(0) );

//			randomSeed( micros()*analogRead(0) );
			this->x = new wormCoord( int(random( 0 , maxX )) , int(random( 0 , 10 )) , int(random( 3 , 27 )) , maxX );
			this->x->setRandDirChange(int(random( 13 , 29 )))

//			randomSeed( micros()*analogRead(0) );
			this->y = new wormCoord( int(random( 0 , maxY )) ,  int(random( 0 , 10 )) , int(random( 3 , 27 )) , maxY );
			this->y->setRandDirChange(int(random( 13 , 29 )))
		}

		virtual void drawWorm() {
			int a = 0;
			int tmpX[6];
			int tmpY[6];

			tmpX = this->x->getCoord();
			tmpY = this->y->getCoord();

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

	worm1 = new worm( MAX_X, MAX_Y );
	worm2 = new worm( MAX_X, MAX_Y );
	worm3 = new worm( MAX_X, MAX_Y );
	worm4 = new worm( MAX_X, MAX_Y );
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