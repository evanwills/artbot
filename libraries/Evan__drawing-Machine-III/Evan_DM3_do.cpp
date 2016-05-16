#include <EVAN_stepper.cpp>
#include <EVAN_itterator.cpp>
#include <EVAN_Circle-Interface.cpp>
#include <EVAN_Circle-Shape.cpp>
#include <EVAN_Circle-Manager.cpp>
#include <EVAN_Boom.cpp>
#include <EVAN_MD3_working-model.cpp>

const int TIMES = 10000;
const int WIDTH = 5000;
incrementorInterface loopTimes;
dm3WorkingModel MD3;

const double OFFSET = WIDTH / 2;
const double BOOM_ONE_LEN = WIDTH * 2;
const double BOOM_TWO_LEN = WIDTH * 2;

void setup() {
	loopTimes = new doInc(TIMES);
	circle tableRotator = new circle( 0 , new stepperFixed( 0.13 ) , new stepperFixed( OFFSET ));
	tableRotator->initXY( OFFSET , OFFSET );


	// this one sets
	circleManager circleOne = new multiCircle(
		new circle(
			 180
			,new stepperFixed( 0 )
			,new stepperFixed( BOOM_ONE_LEN )
		)
	);
	circleOne->initXY( OFFSET , OFFSET );
	circleOne->setChildCircle(
		new multiCircle(
			new circle(
				 0
				,new stepperFixed( 0.37 )
				,new stepperFixed( 1613 )
			)
		)
	);
	circleOne->setChildCircle(
		new multiCircle(
			new circle(
				 0
				,new stepperFixed( 0.77 )
				,new stepperFixed( 887 )
			)
		)
	);

	//
	circleManager circleTwo = new multiCircle(
		new circle(
			120
			,new stepperFixed( 0 )
			,new stepperFixed( BOOM_TWO_LEN )
		)
	);
	circleTwo->initXY( OFFSET , OFFSET );
	circleTwo->setChildCircle(
		new multiCircle(
			new circle(
				 0
				,new stepperFixed( 0.29 )
				,new stepperFixed( 1193 )
			)
		)
	);
	circleTwo->setChildCircle(
		new multiCircle(
			new circle(
				 0
				,new stepperFixed( 0.83 )
				,new stepperFixed( 1307 )
			)
		)
	);


	MD3 = new dm3WorkingModel(
		 WIDTH	// width
		,WIDTH	// height
		,new straightBoom( // booms
			 new stepperFixed( BOOM_ONE_LEN )
			,new stepperFixed( BOOM_TWO_LEN )
		 )
		,circleOne	// firstCircle
		,circleTwo	// secondCircle
		,tableRotator //tableRotator
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