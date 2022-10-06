#pragma once
#include <vector>
#include <iostream>

namespace MementoPattern
{
	void Entry();

	/*
	 * Memento
	 * stores internal state of the Originator object and protects
	 * against access by objects other than the originator
	 */
	class Memento
	{
	private:
		// accessible only to Originator
		friend class Originator;

		Memento(const int s) : _state(s) {}

		void setState(const int s)
		{
			_state = s;
		}

		int getState()
		{
			return _state;
		}

	private:
		int _state;
	};

	/*
	 * Originator
	 * creates a memento containing a snapshot of its current internal
	 * state and uses the memento to restore its internal state
	 */
	class Originator
	{
	public:
		// implemented only for printing purpose
		void setState(const int s)
		{
			std::cout << "Set state to " << s << "." << std::endl;
			_state = s;
		}

		// implemented only for printing purpose
		int getState()
		{
			return _state;
		}

		// restore
		void setMemento(Memento* const m)
		{
			_state = m->getState();
		}

		Memento* createMemento()
		{
			return new Memento(_state);
		}

	private:
		int _state;
	};

	/*
	 * CareTaker
	 * is responsible for the memento's safe keeping
	 */
	class CareTaker
	{
	public:
		CareTaker(Originator* const o) : _originator(o) {}

		~CareTaker()
		{
			for (unsigned int i = 0; i < _history.size(); i++)
				delete _history.at(i);
			_history.clear();
		}

		void save()
		{
			std::cout << "Save state." << std::endl;
			_history.push_back(_originator->createMemento());
		}

		void undo()
		{
			if (_history.empty())
			{
				std::cout << "Unable to undo state." << std::endl;
				return;
			}

			Memento* m = _history.back();
			_originator->setMemento(m);
			std::cout << "Undo state." << std::endl;

			_history.pop_back();
			delete m;
		}

	private:
		Originator* _originator;
		std::vector<Memento*> _history;
	};

} // namespace MementoPattern