#include "Flyweight.h"

namespace FlyweightPattern
{
	void Entry()
	{
		FlyweightFactory* factory = new FlyweightFactory;
		factory->getFlyweight(1)->operation();
		factory->getFlyweight(2)->operation();

		delete factory;
	}

} // namespace FlyweightPattern
