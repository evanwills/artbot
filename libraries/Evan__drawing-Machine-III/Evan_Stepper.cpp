
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
