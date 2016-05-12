// ==================================================================
// How it should work:
//		1.	rotate
//		2.	for each child,
//		2.a.	get radiusPointX & radiusPointY
//		2.b.	rotate radiusPointX & radiusPointY around current
//				orginX & orginY
//		2.c.	send new radiusPointX & radiusPointY back to child
//		3.	repeat steps 1 - 3 for each child

// ==================================================================
// START: circleManager family

class circleManager
{
	public:
		virtual double getDepth() = 0;
		virtual bool depthOK() = 0;
		virtual void setChildCircle();
		virtual void setRadiusPointXY();
		virtual void setOriginXY();
		virtual void initialiseXY();
		virtual void rotateCircle();
		virtual void getAngleStep( unsigned int depth );
		virtual double getOriginX();
		virtual double getOriginY();
		virtual double getRadiusPointX( unsigned int depth );
		virtual double getRadiusPointY( unsigned int depth );
		virtual double getX();
		virtual double getY();
		virtual unsigned int getDepth();
}

class singleCircleManager : circleManager
{
	private:
		circleType * _circle;
		double _OriginX = 0;
		double _OriginY = 0;
		double _radiusPointX = 0;
		double _radiusPointY = 0;
		unsigned int _depth = 0;

	public:
		singleCircleManager( circleType circle ) {
			_radius = radius;
			_angleStep = angleStep;
			_currentAngle = initialAngle;

			// set
		}

		double getDepth() {
			return depth;
		}

		bool depthOK() {
			return true;
		}

		void setChildCircle( circleManager * childCircle ) {
			// do nothing singleCirclePoint objects have no child
		}

		void setRadiusPointXY( double x , double y , unsigned int depth ) {
			_radiusPointX = x;
			_radiusPointY = y;

			// ------------------------------------------------------
			// TODO:	set current angle based on originX & originY,
			//			radius and radiusPointX & radiusPointY
			// ------------------------------------------------------
		}

		void setOriginXY( double x , double y ) {
			_OriginX = x;
			_OriginY = y;
		}

		void initialiseXY( double x , double y ) {
			double pointX = 0;
			double pointY = 0;
			setOriginXY( x , y );

			// ------------------------------------------------------
			// TODO:	calculate radiusPointX & radiusPointY
			// ------------------------------------------------------

			setRadiusPointXY( pointX , Pointy );
		}

		void rotateCircle() {
			// rotate circle
		}

		double getAngleStep( unsigned int depth ) {
			return _circle->getAngleStep(depth);
		}

		double getOriginX() {
			return _OriginX;
		}

		double getOriginY() {
			return _OriginY;
		}

		double getRadiusPointX( unsigned int depth ) {
			return _radiusPointX;
		}

		double getRadiusPointY( unsigned int depth ) {
			return _radiusPointY;
		}


		double getX() {
			return _radiusPointX;
		}

		double getY() {
			return _radiusPointY;
		}

		unsigned int getDepth() {
			return _depth;
		}


};

class multiCircleManager : singleCirclePoint
{
	private:
		circleManager * _childCircle;

	public:

		void setChildCircle( circleManager * childCircle ) {
			_depth += 1;
			if( _childCircle ===  null ) {
				_childCircle = childCircle;
			} else {
				_childCircle->setChildCircle(childCircle);
			}
		}

		void rotateCircle() {
			unsigned int tmpDepth = _depth;
			double radiusPointX = 0;
			double radiusPointY = 0;

			for( tmpDepth ; tmpDepth >= 0 ; tmpDepth -= 1 ) {
				radiusPointX = childCircle->getRadiusPointX( tmpDepth );
				radiusPointY = childCircle->getRadiusPointY( tmpDepth );
				_circle
				childCircle->setRadiusPointXY( radiusPointX , radiusPointY , tmpDepth );
			}
			// calculate new radiusPointX & radiusPointY;
			childCircle->setOriginXY( _radiusPointX , _radiusPointY );
			childCircle->rotateCircle();
		}


		/**
		 * @method depthOK() checks whether the hierarchy of nested
		 *			circles is correct
		 */
		bool depthOK() {
			if( _childCircle === null || _childCircle->getDepth() + 1 != _depth ) {
				return false;
			}
			// this looks OK lets see whether the child is OK
			return _childCircle->depthOK();
		}

		void setRadiusPointXY( double x , double y , unsigned int depth ) {
			depth -= 1;
			if( depth == _depth ) {
				_radiusPointX = x;
				_radiusPointY = y;
				// the radius point of this circle is the origin of the child
				_childCircle->setOriginXY( x , y );
			} else {
				_childCircle->setRadiusPointXY( x , y , depth );
			}
		}

		double getAngleStep( unsigned int depth ) {
			depth -= 1;
			if( depth == _depth ) {
				return _circle->getAngleStep(depth);
			} else {
				return _childCircle->getAngleStep(depth);
			}
		}


		double getRadiusPointX( unsigned int depth ) {
			depth -= 1;
			if( depth == _depth ) {
				return _radiusPointX;
			} else {
				return _childCircle->getRadiusPointX( depth );
			}
		}

		double getRadiusPointY( unsigned int depth ) {
			depth -= 1;
			if( depth == _depth ) {
				return _radiusPointY;
			} else {
				return _childCircle->getRadiusPointY( depth );
			}
		}


		double getX() {
			return _childCircle->getX();
		}

		double getY() {
			return _childCircle->getY();
		}
}

//  END: circleManager
// ==================================================================


















// ==================================================================
// START: circleType family

class circleType
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

class circle : circleType
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

class ellipse : circleType
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


















// ==================================================================
// START: stepper

class stepper
{
	protected:
		double _angleStep;
		double _lastAngleStep;

	public:
		virtual double getAngleStep()  = 0;
		virtual double getLastAngleStep() = 0;
		virtual void preLoop(int loops);
}

class stepperFixed : stepper {
	public:
		angleStepperFixed( double angleStep ) {
			_angleStep = angleStep;
			_lastAngleStep = angleStep;
		}

		double getAngleStep() {
			return _angleStep;
		}

		double getLastAngleStep() {
			return _lastAngleStep;
		}

		void preLoop(int loops) {
		}
}

class stepperLinier : stepper {
	protected:
		double _increment;
		double _min;
		double _max;

	public:

		double getAngleStep() {
			_lastAngleStep = _angleStep;
			_angleStep += _increment;
			if( _angleStep > _max ) {
				// bounce _angleStep off max
				_angleStep = _max - ( _angleStep - _max );
				_increment = -_increment;
			} else if( _angleStep < min ) {
				// bounce _angleStep off min
				_angleStep = _min + ( _min - _angleStep );
				_increment = -_increment;
			}
			return _angleStep;
		}

		angleStepperLinier( double angleStep , double increment , double min , double max ) {
			if( min > max ) {
				_min = max;
				_max = min;
			} else {
				_max = max;
				_mmin = min;
			}
			_angleStep = angleStep;
			_increment = increment;
			getAngleStep();
		}

		double getLastAngleStep() {
			return _lastAngleStep
		}

		void preLoop(int loops) {
			double angleStep = _angleStep;
			if( loops < 0 ) {
				angleStep = -angleStep;
			}

			for( loops ; loops >= 0 ; loops -= 1 ) {
				getAngleStep();
			}
		}
}

//  END:  stepper
// ==================================================================
