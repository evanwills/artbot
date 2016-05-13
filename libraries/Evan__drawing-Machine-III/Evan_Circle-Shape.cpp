

// ==================================================================
// START: circleType family

class circleShape : circleInterface // interface
{
	private:
		double _initialAngle;
		stepper * _angleStep;
		double tmpX;
		double tmpY;

	public:
		/**
		 * @method	setRadiusPointXY() sets the _radiusPOintX &
		 *			 for the circle object
		 */
		virtual void setRadiusPointXY( double x , double y );

		virtual void rotateXY( double x , double y );

		double getRadiusPointX() {
			return tmpX;
		}

		double getRadiusPointY() {
			return tmpY;
		}

}

class circle : circleShape
{
	private:
		stepper * _radius;

	public:
		circle( double initalAngle , stepper * angleStep , stepper * radius ) {
			_radius = radius;
			_initialAngle = initialAngle;
			_angleStep = angleStep;
		}

		void rotate() {
			rotateXY( _radiusPointX , _radiusPointY );
			_radiusPointX = tmpX;
			_radiusPointY = tmpY;
		}



		void initXY( double originX , double originY ) {
			setOriginXY( originX, originY );
		}
}

class ellipse : circleShape
{
	private:
		stepper * _radiusX;
		stepper * _radiusY;
		stepper * _radiusOffsetX;
		stepper * _radiusOffsetY;
	public:
		circle( double initalAngle , stepper * angleStep ,  stepper * radiusX , stepper * radiusY , stepper * radiusOffsetX , stepper * radiusOffsetY ) {
			_initialAngle = initialAngle;
			_angleStep = angleStep;
			_radiusX = radiusX;
			_radiusY = radiusY;
			_radiusoffsetX = radiusoffsetX;
			_radiusoffsetY = radiusoffsetY;
		}

		void rotate( ) {
		}

		void initXY( double originX , double originY ) {
			setOriginXY( originX, originY );
		}
}

//  END: circleType
// ==================================================================

















