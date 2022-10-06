#include "TemplateMethod.h"

namespace TemplateMethodPattern
{
	void Entry()
	{
		AbstractClass* tm = new ConcreteClass;
		tm->templateMethod();

		delete tm;
	}

} // namespace TemplateMethodPattern
