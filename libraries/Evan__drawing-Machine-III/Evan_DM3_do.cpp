
#include <EVAN_stepper.cpp>
#include <EVAN_itterator.cpp>
#include <EVAN_Circle-Interface.cpp>
#include <EVAN_Circle-Shape.cpp>
#include <EVAN_Circle-Manager.cpp>
#include <EVAN_Single-Boom.cpp>
#include <EVAN_Boom-integrator.cpp>
#include <EVAN_MD3_working-model.cpp>

const int TIMES = 10000;
const int WIDTH = 4500;
incrementorInterface loopTimes;
dm3WorkingModel MD3;

void setup() {
	loopTimes = new doInc(TIMES);

	circleManager circleOne = new multiCircle( new circle( 0 , new stepperFixed( 0.37 ) , new stepperFixed( 180 ) ) );
	circleOne->initXY( (WIDTH / 2) , (width * 2.5) );
	circleOne->setChildCircle( new multiCircle( new circle( 0 , new stepperFixed( 0.77 ) , new stepperFixed( 219 ) ) ) );

	circleManager circleTwo = new multiCircle( new circle( 0 , new stepperFixed( 0.29 ) , new stepperFixed( 57 ) ) );
	circleTwo->initXY( (width * 2 ) , (WIDTH / 2) );
	circleTwo->setChildCircle( new multiCircle( new circle( 0 , new stepperFixed( 0.83 ) , new stepperFixed( 301 ) ) ) );

	MD3 = new dm3WorkingModel(
		 WIDTH	// width
		,WIDTH	// height
		,new straightBoom( // booms
			 singleBoom( 0 , 0 , new stepperFixed( (width * 1.25) ) )
			,singleBoom( 0 , 0 , new stepperFixed( (width * 1.25) ) )
		 )
		,circleOne	// firstCircle
		,circleTwo	// secondCircle
		,new circle( 0 , new stepperFixed( 0.13 ) , new stepperFixed( (WIDTH / 2) ) ) //tableRotator
	);

}

void loop() {
	while( loopTimes->limitReached == false ) {
		MD3->rotate();
		// output to file somehow
		MD3->getX();
		MD3->getY();
	}
}