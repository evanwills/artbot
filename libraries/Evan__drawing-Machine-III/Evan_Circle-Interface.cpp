// Generic interface for both circleShape and circleManager objects
class circleInterface
{
	private:
		double _originX;
		double _originY;

		double _radiusPointX;
		double _radiusPointY;

	public:
		/**
		 * @method	initialiseXY() puts the _radiusPointX &
		 *			_radiusPointY at their initial location
		 */
		virtual void initXY( double x , double y );

		/**
		 * @method rotate() move the radiusPoint to a new location
		 */
		virtual void rotate();

		/**
		 * @method	setOriginXY() sets the _originX & _originY for
		 *			the circle object
		 */
		void setOriginXY( double x , double y ) {
			_originX = x;
			_originY = y;
		}

		/**
		 * @method	getX() returns the final _radiusPointX in the
		 *			stack (the one that will be used as the origin of
		 *			one drawing arm)
		 */
		double getX() {
			return _radiusPointX;
		}

		/**
		 * @method	getY() like getX() but for the Y value
		 */
		double getY() {
			return _radiusPointY;
		}

		/**
		 * @method	getOriginX() returns the _originX of this
		 *			circleManager object
		 */
		double getOriginX() {
			return _originX;
		}

		/**
		 * @method	getOriginY() returns the _originY of this
		 *			circleManager object
		 */
		double getOriginY() {
			return _originY;
		}
}