class singleBoom
{
	private:
		stepper * _originOffsetX;
		stepper * _originOffsetY;
		stepper * _length;

	public:
		singleBoom( stepper * originOffsetX , stepper * originOffsetY , stepper * length ) {
			_originOffsetX = originOffsetX;
			_originOffsetY = originOffsetY;
			_length = length;
		}

		double getRelativeOriginX( double originX ) {
			return _originOffsetX->getStep() + originX
		}

		double getRelativeOriginY( double originY ) {
			return _originOffsetY->getStep() + originY
		}

		double getRelativeOriginY( double originY ) {
			return _originOffsetY->getStep() + originY
		}
}