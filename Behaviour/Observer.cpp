#include <iostream>
#include "Observer.h"




namespace ObserverPattern
{
	void Entry()
	{
		ConcreteObserver observer1(1);
		ConcreteObserver observer2(2);

		std::cout << "Observer 1 state: " << observer1.getState() << std::endl;
		std::cout << "Observer 2 state: " << observer2.getState() << std::endl;

		Subject* subject = new ConcreteSubject();
		subject->attach(&observer1);
		subject->attach(&observer2);

		subject->setState(10);
		subject->notify();

		std::cout << "Observer 1 state: " << observer1.getState() << std::endl;
		std::cout << "Observer 2 state: " << observer2.getState() << std::endl;

		delete subject;
	}

} // namespace ObserverPattern
