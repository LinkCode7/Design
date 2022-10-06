#pragma once
#include <string>
#include <vector>
#include <iostream>

namespace StatePattern
{
	void Entry();

	/*
	* State
	* defines an interface for encapsulating the behavior associated
	* with a particular state of the Context
	*/
	class State
	{
	public:
		virtual ~State() {}
		virtual void handle() = 0;
	};

	/*
	* Concrete States
	* each subclass implements a behavior associated with a state
	* of the Context
	*/
	class ConcreteStateA : public State
	{
	public:
		~ConcreteStateA() {}

		void handle()override
		{
			std::cout << "State A handled." << std::endl;
		}
	};

	class ConcreteStateB : public State
	{
	public:
		~ConcreteStateB() {}

		void handle()override
		{
			std::cout << "State B handled." << std::endl;
		}
	};

	/*
	* Context
	* defines the interface of interest to clients
	*/
	class Context
	{
	public:
		Context() : state() { /* ... */ }
		~Context() { delete state; }

		void setState(State* const s)
		{
			if (state)
				delete state;
			state = s;
		}

		void request()
		{
			state->handle();
		}

	private:
		State* state;
	};







	////////////////////////////////////////Mario////////////////////////////////////////

	enum MarioState
	{
		SMALL,		// 小马里奥
		SUPER,		// 超级马里奥
		FIRE,		// 火焰马里奥
		CAPE,		// 披肩马里奥
	};

	class MarioStateMachine0
	{
		int _score;
		MarioState _currentState;

	public:
		MarioStateMachine0() :_score(0), _currentState(SMALL) {}

		int getScore() { return _score; }
		MarioState getCurrentState() { return _currentState; }

		void obtainMushRoom() {/*TODO*/ }
		void obtainCape() {/*TODO*/ }
		void obtainFireFlower() {/*TODO*/ }
		void meetMonster() {/*TODO*/ }
	};

	// 分支逻辑法（简单状态机）
	class MarioStateMachine1
	{
		int _score;
		MarioState _currentState;

	public:
		MarioStateMachine1() :_score(0), _currentState(SMALL) {}

		int getScore() { return _score; }
		MarioState getCurrentState() { return _currentState; }

		void obtainMushRoom()
		{
			if (_currentState == SMALL)
			{
				_currentState = SUPER;
				_score += 100;
			}
		}

		void obtainCape()
		{
			if (_currentState == SMALL || _currentState == SUPER)
			{
				_currentState = CAPE;
				_score += 200;
			}
		}

		void obtainFireFlower()
		{
			if (_currentState == SMALL || _currentState == SUPER)
			{
				_currentState = FIRE;
				_score += 300;
			}
		}

		void meetMonster()
		{
			if (_currentState == SUPER)
			{
				_currentState = SMALL;
				_score -= 100;
				return;
			}

			if (_currentState == CAPE)
			{
				_currentState = SMALL;
				_score -= 200;
				return;
			}

			if (_currentState == FIRE)
			{
				_currentState = SMALL;
				_score -= 300;
				return;
			}
		}
	};




	// 查表法（对于状态很多、状态转移比较复杂的状态机）
	enum MarioEvent
	{
		GOT_MUSHROOM = 0,
		GOT_CAPE = 1,
		GOT_FIRE = 2,
		MET_MONSTER = 3,
	};

	class MarioStateMachine2
	{
		int _score;
		MarioState _currentState;

		std::vector<std::vector<MarioState>> transitionTable =
		{
			{ SUPER, CAPE, FIRE, SMALL },
			{ SUPER, CAPE, FIRE, SMALL },
			{ CAPE, CAPE, CAPE, SMALL },
			{ FIRE, FIRE, FIRE, SMALL }
		};

		std::vector<std::vector<int>> actionTable =
		{
			{ 100, 200, 300, 0 },
			{ 0, 200, 300, -100 },
			{ 0, 0, 0, -200 },
			{ 0, 0, 0, -300 }
		};

	public:
		MarioStateMachine2() :_score(0), _currentState(MarioState::SMALL) {}
		int getScore() { return _score; }

		void obtainMushRoom() {
			executeEvent(GOT_MUSHROOM);
		}

		void obtainCape() {
			executeEvent(GOT_CAPE);
		}

		void obtainFireFlower() {
			executeEvent(GOT_FIRE);
		}

		void meetMonster() {
			executeEvent(MET_MONSTER);
		}

	private:
		void executeEvent(MarioEvent event)
		{
			int stateValue = _currentState;
			int eventValue = event;
			_currentState = transitionTable[stateValue][eventValue];
			_score += actionTable[stateValue][eventValue];
		}
	};






	// 状态模式（对于状态并不多、状态转移也比较简单，但事件触发执行的动作包含的业务逻辑可能比较复杂的状态机）
	class IMario // 所有状态类的接口
	{
	public:
		virtual MarioState getName() = 0;
		// 以下是定义的事件
		virtual void obtainMushRoom() {}
		virtual void obtainCape() {}
		virtual void obtainFireFlower() {}
		virtual void meetMonster() {}
	};

	class MarioStateMachine
	{
	private:
		int _score;
		IMario* _currentState; // 不再使用枚举来表示状态

	public:
		MarioStateMachine();
		~MarioStateMachine() { delete _currentState; }

		void obtainMushRoom() {
			_currentState->obtainMushRoom();
		}

		void obtainCape() {
			_currentState->obtainCape();
		}

		void obtainFireFlower() {
			_currentState->obtainFireFlower();
		}

		void meetMonster() {
			_currentState->meetMonster();
		}

		int getScore() {
			return _score;
		}

		MarioState getCurrentState() {
			return _currentState->getName();
		}

		void setScore(int score) {
			_score = score;
		}

		void setCurrentState(IMario* currentState) {
			if (_currentState)
				delete _currentState;
			_currentState = currentState;
		}
	};

	class SmallMario : public IMario
	{
	private:
		MarioStateMachine* _stateMachine;

	public:
		SmallMario(MarioStateMachine* stateMachine) { _stateMachine = stateMachine; }

		MarioState getName()override { return SMALL; }

		void obtainMushRoom()override;
		void obtainCape()override;
		void obtainFireFlower()override;
		void meetMonster()override {/*do nothing...*/ }
	};

	class SuperMario : public IMario
	{
	private:
		MarioStateMachine* _stateMachine;

	public:
		SuperMario(MarioStateMachine* stateMachine) { _stateMachine = stateMachine; }

		MarioState getName()override { return SUPER; }

		void obtainMushRoom()override {/*do nothing...*/ }
		void obtainCape()override;
		void obtainFireFlower()override;
		void meetMonster()override;
	};

	// 省略CapeMario、FireMario
	class CapeMario : public IMario
	{
		MarioStateMachine* _stateMachine;
	public:
		CapeMario(MarioStateMachine* stateMachine) { _stateMachine = stateMachine; }

		MarioState getName()override { return CAPE; }
	};
	class FireMario : public IMario
	{
		MarioStateMachine* _stateMachine;
	public:
		FireMario(MarioStateMachine* stateMachine) { _stateMachine = stateMachine; }

		MarioState getName()override { return FIRE; }
	};

} // namespace StatePattern
