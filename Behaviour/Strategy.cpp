#include "Strategy.h"

namespace StrategyPattern
{
	void Entry()
	{
		Context context(new ConcreteStrategyA());
		context.contextInterface();
	}

} // namespace StrategyPattern
