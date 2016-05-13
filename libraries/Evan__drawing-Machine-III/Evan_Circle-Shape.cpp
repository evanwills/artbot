

// ==================================================================
// START: circleType family

class circleShape : circleInterface // interface
{
	private:
		double _initialAngle;
		stepper * _angleStep;

	public:
		/**
		 * @method	setRadiusPointXY() sets the _radiusPOintX &
		 *			 for the circle object
		 */
		virtual void setRadiusPointXY( double x , double y );

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

















