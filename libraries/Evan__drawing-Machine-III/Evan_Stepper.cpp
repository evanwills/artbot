
// ==================================================================
// START: stepper

class stepper
{
	protected:
		double _step;
		double _lastStep;
		double _min;
		double _max;

	public:
		virtual double getStep()  = 0;
		virtual double getLastStep() = 0;
//		virtual void preLoop(int loops);

		double getMin() {
			return _min;
		}

		double getMax() {
			return _max;
		}

		bool withinMinMax( double min , double max ) {
			double tmp;
			if( min > max ) {
				tmp = min;
				min = max;
				max = tmp;
			}

			if( _step > max || _step < min || _min < min || _max >= max || _max =< min ) {
				return false;
			}
			return true;
		}
}

class stepperFixed : stepper {
	public:
		stepperFixed( double step ) {
			_step = step;
			_lastStep = step;
			_min = step;
			_max = step;
		}

		double getStep() {
			return _step;
		}

		double getLastStep() {
			return _lastStep;
		}

//		void preLoop(int loops) {
//		}
}

class stepperLinier : stepper {
	protected:
		double _increment;

	public:

		double getStep() {
			_lastStep = _step;
			_step += _increment;
			if( _step > _max ) {
				// bounce _step off max
				_step = _max - ( _step - _max );
				_increment = -_increment;
			} else if( _step < min ) {
				// bounce _step off min
				_step = _min + ( _min - _step );
				_increment = -_increment;
			}
			return _step;
		}

		StepperLinier( double step , double increment , double min , double max ) {
			if( min > max ) {
				_min = max;
				_max = min;
			} else {
				_max = max;
				_min = min;
			}
			_step = step;
			_increment = increment;
			getStep();
		}

		double getLastStep() {
			return _lastStep
		}

//		void preLoop(int loops) {
//			double step = _step;
//			if( loops < 0 ) {
//				step = -step;
//			}
//
//			for( loops ; loops >= 0 ; loops -= 1 ) {
//				getStep();
//			}
//		}
}

//  END:  stepper
// ==================================================================
