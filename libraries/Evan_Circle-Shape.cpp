

// ==================================================================
// START: circleType family

class circleShape
{
	private:
		double _x;
		double _y;
		double _originX;
		double _originY;
		double _initialAngle;
		stepper * _angleStep;

	public:
		virtual bool calculateXY( double radiusX , double radiusY ) = false;

		virtual void initXY( double originX , double originY );

		bool setOriginXY( double originX , double originY ) {
			_originX = originX;
			_originY = originY;
		}

		double getX() {
			return _x;
		}
		double getY() {
			return _y;
		}

		double getOriginX() {
			return _originX;
		}
		double getOriginY() {
			return _originY;
		}
		double getInitialAngle() {
			return _initialAngle;
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

		bool calculateXY( double radiusX , double radiusY ) {
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

		bool calculateXY( double radiusX , double radiusY ) {
		}

		void initXY( double originX , double originY ) {
			setOriginXY( originX, originY );
		}
}

//  END: circleType
// ==================================================================

















