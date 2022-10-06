#include <iostream>
#include "State.h"

using namespace std;

namespace StatePattern
{
	void Entry()
	{
		Context* context = new Context();

		context->setState(new ConcreteStateA());
		context->request();

		context->setState(new ConcreteStateB());
		context->request();

		delete context;
	}

	void ApplicationDemo()
	{
		MarioStateMachine0* mario = new MarioStateMachine0();
		mario->obtainMushRoom();

		int score = mario->getScore();
		MarioState state = mario->getCurrentState();
		cout << "mario score: " << score << "; state: " << state;

		delete mario;
	}

	MarioStateMachine::MarioStateMachine() : _score(0), _currentState(new SmallMario(this)) {}


	void SmallMario::obtainMushRoom()
	{
		_stateMachine->setCurrentState(new SuperMario(_stateMachine));
		_stateMachine->setScore(_stateMachine->getScore() + 100);
	}
	void SmallMario::obtainCape()
	{
		_stateMachine->setCurrentState(new CapeMario(_stateMachine));
		_stateMachine->setScore(_stateMachine->getScore() + 200);
	}
	void SmallMario::obtainFireFlower()
	{
		_stateMachine->setCurrentState(new FireMario(_stateMachine));
		_stateMachine->setScore(_stateMachine->getScore() + 300);
	}


	void SuperMario::obtainCape()
	{
		_stateMachine->setCurrentState(new CapeMario(_stateMachine));
		_stateMachine->setScore(_stateMachine->getScore() + 200);
	}
	void SuperMario::obtainFireFlower()
	{
		_stateMachine->setCurrentState(new FireMario(_stateMachine));
		_stateMachine->setScore(_stateMachine->getScore() + 300);
	}
	void SuperMario::meetMonster()
	{
		_stateMachine->setCurrentState(new SmallMario(_stateMachine));
		_stateMachine->setScore(_stateMachine->getScore() - 100);
	}

} // namespace StatePattern