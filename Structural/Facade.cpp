#include "Facade.h"

#include <iostream>

namespace FacadePattern
{
	void Entry()
	{
		Facade* facade = new Facade();
		facade->operation1();
		facade->operation2();

		delete facade;
	}

} // namespace FacadePattern
