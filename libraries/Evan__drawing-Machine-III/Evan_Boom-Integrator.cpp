class boomIntegratorInterface
{
	private:
		singleBoom * _firstBoom;
		singleBoom * _secondBoom;
		double _endX = 0;
		double _endY = 0;

	public:
		virtual void setEndPoint( double firstOriginX , double firstOriginY , double secondOriginX , double secondOriginY );

		double getX() {
			return _endX;
		}

		double getY() {
			return _endY;
		}
}

class straightBoom : boomIntegratorInterface
{
	private:
		singleBoom * _firstBoom;
		singleBoom * _secondBoom;

	public:
		straightBoom( singleBoom * firstBoom , singleBoom * secondBoom ) {
			_firstBoom = firstBoom;
			_secondBoom = secondBoom;
		}
		void setEndPoint( double firstOriginX , double firstOriginY , double secondOriginX , double secondOriginY ) {

		}
}

class simpleScissorBoom : boomIntegratorInterface
{
	private:
		stepper * _pivotPosition;

	public:
		straightBoom(  singleBoom * firstBoom , singleBoom * secondBoom , stepper * pivotPosition ) {
			_firstBoom = firstBoom;
			_secondBoom = secondBoom;
			if( pivotPosition->withinMinMax(0,1) == false ) {
				// throw error
			}
			_pivotPosition = pivotPosition;
		}
		void setEndPoint( double firstOriginX , double firstOriginY , double secondOriginX , double secondOriginY ) {

		}
}

class asymetricalScissorBoom : boomIntegratorInterface
{
	public:
		straightBoom(  singleBoom * firstBoom , singleBoom * secondBoom , stepper * pivotPosition ) {
			_firstBoom = firstBoom;
			_secondBoom = secondBoom;

			if( pivotPosition->withinMinMax(0,1) == false ) {
				// throw error
			}
			_pivotPosition = pivotPosition;
		}
		void setEndPoint( double firstOriginX , double firstOriginY , double secondOriginX , double secondOriginY ) {

		}
}

class whackyScissorBoom : boomIntegratorInterface
{
	public:
		straightBoom(  singleBoom * firstBoom , singleBoom * secondBoom , stepper * pivotFirstPosition , stepper * pivotSecondPosition ) {
			_firstBoom = firstBoom;
			_secondBoom = secondBoom;

			if( pivotFirstPosition->withinMinMax(0,1) == false ) {
				// throw error
			}
			_pivotFirstPosition = pivotFirstPosition;
			if( pivotSecondPosition->withinMinMax(0,1) == false ) {
				// throw error
			}
			_pivotSecondPosition = pivotSecondPosition;
		}
		void setEndPoint( double firstOriginX , double firstOriginY , double secondOriginX , double secondOriginY ) {

		}
}

class TBoom : boomIntegratorInterface
{
	private:
		stepper * _boomOffset;
	public:
		straightBoom(  singleBoom * firstBoom , singleBoom * secondBoom , stepper * boomOffset ) {
			_firstBoom = firstBoom;
			_secondBoom = secondBoom;

			if( boomOffset->withinMinMax(0,1) == false ) {
				// throw error
			}
		}
		void setEndPoint( double firstOriginX , double firstOriginY , double secondOriginX , double secondOriginY ) {

		}
}

