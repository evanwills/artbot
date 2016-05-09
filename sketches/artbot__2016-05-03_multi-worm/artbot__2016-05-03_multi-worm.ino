#include <Wire.h>    // these are all the libraries we need for working with our screen.
#include <SPI.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define OLED_RESET 4                  // here we get the screen ready for sending instructions to using the libraries above
Adafruit_SSD1306 display(OLED_RESET);

const unsigned int MAX_X = 128;
const unsigned int MAX_Y = 64;


// ==================================================================
// START: dirChange family of Classes

// dirChange sets interface for noDirChange & randDirChange objects
class dirChange {
	protected:
		/**
		 * @method  dirChange()
		 *
		 * @param [unsigned int] max
		 * @param [unsigned int] threshold
		 */
		dirChange ( unsigned int max , unsigned int threshold ) { }

	public:
		/**
		 * @method dirChange() always returns FALSE for this class
		 * @return [bool] FALSE
		 */
		bool doChange() {
			return false;
		}

		/**
		 * @method getRandDirChange() factory method returns
		 *		   appropriate dirChange object
		 */
//		static dirChange getChanger( unsigned int max , unsigned int threshold ) {
//			if( max > 0 ) {
//				return new randDirChange(max, threshold);
//			} else {
//				return new noDirChange(max, threshold);
//			}
//		}
		static dirChange * getChanger( unsigned int max , unsigned int threshold );

};

class noDirChange : dirChange {
//	protected:
		/**
		 * @method  noDirChange()
		 *
		 * @param [unsigned int] max
		 * @param [unsigned int] threshold
		 */
//		noDirChange ( unsigned int max , unsigned int threshold ) { }

//	public:
		/**
		 * @method dirChange() always returns FALSE for this class
		 * @return [bool] FALSE
		 */
//		bool doChange() {
//			return false;
//		}

};

class randDirChange : dirChange {
	private:
		/**
		 * @var randMax the maximum value for the random number
		 *		(minimum is zero)
		 */
		unsigned int randMax = 0;
		/**
		 * @var randThresh the threshold above which the random
		 *		number generated in doChange should cause doChange()
		 *		to return TRUE
		 */
		unsigned int randThresh = 0;

	protected:

		/**
		 * @method  randDirChange() sets whether random direchanger
		 *			acts or not and if so, what it's parameters are
		 *
		 * @param [unsigned int] max the maximum value of randomness
		 * @param [unsigned int] threshold the value randomness needs to be
		 *				above to be considered worthy
		 */
		randDirChange ( unsigned int max , unsigned int threshold ) {
			this->randMax = max;
			if( threshold < max ) {
				this->randThresh = threshold;
			} else {
				this->randThresh = int( max * 0.9 );
			}
		}


	public:
		/**
		 * @method	dirChange() generates a random number between 0 &
		 *			randDirChange::randIncPointMax. If number is
		 *			greater than or equal to the threshold then true
		 *			is returned
		 * @return [bool] TRUE if threshold is met or passed.
		 *				  FALSE otherwise
		 */
		bool doChange() {
			if( int(random(0, this->randMax)) >= this->randThresh ) {
				return true;
			}
			return false;
		}

};



/**
 * @method getRandDirChange() factory method returns
 *		   appropriate dirChange object
 */
// this is an attempt to make the factory method work.
dirChange dirChange::getChanger( unsigned int max , unsigned int threshold ) {
	if( max > 0 ) {
		return new randDirChange(max, threshold);
	} else {
		return new noDirChange(max, threshold);
	}
}


//  END:  dirChange family of Classes
// ==================================================================
// START: incrementor family of Classes

/**
 * @class incrementor increments a value and returns FALSE until the
 *		  maximum is reached then resets the value to zero and
 *		  returns TRUE. if incrementor::doInc is false nothing is
 *		  incremented and incrementor::limitReached() will always
 *		  return FALSE;
 */
class incrementor
{

	protected:
		/**
		 * @method incrementor constructor
		 * @param [int] incLimit when to reset the increment value
		 */
		incrementor( int incLimit ) { }

	public:
		/**
		 * @method  getInc() factory method for providing the correct
		 *			type of incrementor object
		 *
		 * @var [unsigned int] incLimit maximum times a value can be
		 *		incremented before it's reset
		 */
//		static incrementor getInc(unsigned int incLimit) {
//			if( incLimit < 0 ) {
//				return noInc(incLimit);
//			} else {
//				return doInc(incLimit);
//			}
//		}
		static incrementor getInc(unsigned int incLimit);

		/**
		 * @method	limitReached() increments a value each time it's
		 *			called and checks that increment against a
		 *			maximum value.
		 *
		 * NOTE: if incrementor::doInc is FALSE, FALSE is always returned
		 *
		 * @return [bool] always FALSE
		 */
		bool limitReached() {
			return false;
		}

};

class noInc : incrementor
{
//	protected:
		/**
		 * @method incrementor constructor
		 * @param [int] incLimit when to reset the increment value
		 */
//		noInc( int incLimit ) { }

//	public:
		/**
		 * @method	limitReached() increments a value each time it's
		 *			called and checks that increment against a
		 *			maximum value.
		 *
		 * NOTE: if incrementor::doInc is FALSE, FALSE is always returned
		 *
		 * @return [bool] always FALSE
		 */
//		bool limitReached() {
//			return false;
//		}

};

class doInc : incrementor
{
	private:
		/**
		 * @var inc the value incremented each time LimitReached is called
		 */
		unsigned int inc = 0;
		/**
		 * @var max the maximum value inc can reach before it is reset
		 */
		unsigned int max = 1;

	protected:
		/**
		 * @method doInc constructor
		 * @param [int] incLimit when to reset the increment value
		 */
		doInc( int incLimit ) {
			this->max = incLimit;
		}

	public:
		/**
		 * @method	limitReached() increments a value each time it's
		 *			called and checks that increment against a
		 *			maximum value.
		 *
		 * @return [bool] TRUE if the maximum number of increments was reached
		 *				  FALSE otherwise
		 */
		bool limitReached() {
			bool output = false;

			if( this->inc == this->max ) {
				output = true;
				this->inc = 0;
			} else {
				this->inc = this->inc + 1;
			}

			return output;
		}

};


/**
 * @method  getInc() factory method for providing the correct
 *			type of incrementor object
 *
 * @var [unsigned int] incLimit maximum times a value can be
 *		incremented before it's reset
 */
// this is an attempt to make the factory method work.
incrementor * incrementor::getInc(unsigned int incLimit) {
	if( incLimit < 0 ) {
		return noInc(incLimit);
	} else {
		return doInc(incLimit);
	}
}

//  END:  incrementor family of Classes
// ==================================================================
// START: wormCoord

/**
 * @class wormCoord handles all the points on one coordinate axis,
 *		  including moving the coordinates when asked.
 *		  It's primary function is to manage the state of a given
 *		  axix
 */
class wormCoord
{
	private:
		/**
		 * @var incPoint how much to increment the coordinate each
		 *		time.
		 *		  NOTE:	this is necessary because we need to swap the
		 *				sign of the incrementor when we reach the
		 *				limit
		 */
		int incPoint = 1;

		/**
		 * @var loopsPerInc object that manages incrementing over a
		 *		given range. It provides the ability to vary the path
		 *		of the worm so it's not always traveling at
		 *		45 degrees
		 */
		incrementor * loopsPerInc;

		/**
		 * @var maxPoint the maximum value a coordinate can get to
		 *		before incPoint is reversed
		 */
		unsigned int maxPoint = 0;

		/**
		 * @var point an array of points (adjacent/or identical to
		 *		each other) along the axis that this object is
		 *		responsible for
		 */
		unsigned int point[6] = { 0, 0, 0, 0, 0, 0 };

		/**
		 * @var preSetPoint object that manages incrementing over a
		 *		given range. Used to provide an extra variation in
		 *		the movement of the worm
		 */
		incrementor * preSetPoint;

		/**
		 * @var dirChange object to manage randomly changing the
		 *		direction of the worm
		 */
		dirChange * changer;

	public:
		/**
		 * @method  getCoord() returns an array with 6 (sequential
		 *		 	and/or identical) integers to be used when
		 *			rendering the worm
		 *
		 * @return unsigned int[6]
		 */
		virtual unsigned int  getCoord() {
			unsigned int a = 0;
			unsigned int b = 0;

			// Have enough loops been passed to change the coordinate?
			if( this->loopsPerInc->limitReached() == true ) {
				// Yes!!!

				// Move all the coordinates down the line to make way
				// for the new one.
				for( a = 6; a >= 0 ; a = -1 ) {
					b = a - 1;
					this->point[a] = this->point[b];
				}

				// Should we change direction of the worm along this
				// axis?
				if( this->point[0] >= this->maxPoint || this->point[0] < 0 || this->changer->doChange() == true ) {
					this->incPoint = -this->incPoint;
				}

				// Should we bump the location by one, just for the
				// hell of it?
				if( this->preSetPoint->limitReached() == true ) {
					this->point[0] = this->point[0] + this->incPoint;
				}

				// Bump the location by 1 because that's what we do
				this->point[0] = this->point[0] + this->incPoint;
			}

			// return the array of coordinates on this axis
			return this->point;
		}


		/**
		 * @method  constructor
		 *
		 * @param [int] coord initial point the worm is to start from
		 * @param [int] loopsPerIncrement how many loops before we
		 *				increment the position o fthis coordinate.
		 * @param [int] SetIncPoint how many loops before the
		 *				location is bumped by increment value.
		 *
		 * @param [int] max the maximum value the coordinate can move
		 *				to before the incrementor is reversed.
		 */
		wormCoord( unsigned int coord , unsigned int loopsPerIncrement , unsigned int SetIncPoint , unsigned int max ) {
			unsigned int a = 0;

			this->point[0] = coord;
			this->loopsPerInc = incrementor::getInc(loopsPerIncrement);
			this->preSetIncPoint = incrementor::getInc( SetIncPoint );
			this->maxPoint = max;

			// pre-populate the coordinates array
			for( a = 0 ; a < 6 ; a = a + 1 ) {
				this->getCoord();
			}
		}

		/**
		 * @method  setRandDirChange() sets whether random direchanger
		 *			acts or not and if so, what it's parameters are
		 *
		 * @param [int] max the maximum value of randomness
		 * @param [int] threshold the value randomness needs to be
		 *				above to be considered worthy
		 */
		void setRandDirChange( unsigned int max , unsigned int threshold ) {
			randomDirChange = dirChange::getChanger(max, threshold);
		}


};

//  END:  wormCoord
// ==================================================================
// START: worm

/**
 * @class worm handles rendering the whole worm based on the X & Y
 *		  wormCoord objects it manages
 */
class worm
{
	wormCoord *x;
	wormCoord *y;

	public:
		worm( unsigned int maxX, unsigned int maxY ) {
			randomSeed( micros()*analogRead(0) );

//			randomSeed( micros()*analogRead(0) );
			// get the Y coordinate manager object
			this->x = new wormCoord( int(random( 0 , maxX )) , int(random( 0 , 10 )) , int(random( 3 , 27 )) , maxX );
			this->x->setRandDirChange(int(random( 13 , 29 )))

//			randomSeed( micros()*analogRead(0) );
			// get the Y coordinate manager object
			this->y = new wormCoord( int(random( 0 , maxY )) ,  int(random( 0 , 10 )) , int(random( 3 , 27 )) , maxY );
			this->y->setRandDirChange(int(random( 13 , 29 )))
		}

		virtual void drawWorm() {
			unsigned int a = 0;
			unsigned int tmpX[6];
			unsigned int tmpY[6];

			// get the X & Y coordinates
			tmpX = this->x->getCoord();
			tmpY = this->y->getCoord();

//			display.drawPixel(tmpX[0], tmpY[0], 1);

			// draw the head of the worm
			display.drawCircle( tmpX[0] , tmpY[0] , 3 , 1 );

			for( a = 1 ; a < 6 ; a = a +1 ) {
				// draw the next point on the worm
				display.drawPixel(tmpX[a], tmpY[a], 1);
			}

			// render the output to screen
			display.display();
		}
};

//  END:  worm
// ==================================================================









// ==================================================================
// START: doin' the do

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