#include <iostream>
#include "Memento.h"



namespace MementoPattern
{
	void Entry()
	{
		Originator* originator = new Originator();
		CareTaker* caretaker = new CareTaker(originator);

		originator->setState(1);
		caretaker->save();

		originator->setState(2);
		caretaker->save();

		originator->setState(3);
		caretaker->undo();

		std::cout << "Actual state is " << originator->getState() << "." << std::endl;

		delete originator;
		delete caretaker;
	}

} // namespace MementoPattern