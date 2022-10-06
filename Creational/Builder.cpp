#include "Builder.h"


using namespace std;


namespace BuilderPattern
{
	void Entry()
	{
		Builder* pBuilder = new ConcreteBuilder();

		Director* pDirector = new Director(pBuilder);
		pDirector->Construct();

		(pDirector);
	}

	void Entry2()
	{
		// 这段代码会抛出IllegalArgumentException异常，因为minIdle>maxIdle
		ResourcePoolConfig* config = ResourcePoolConfig::Builder().setName("dbconnectionpool").setMaxTotal(16).setMaxIdle(10).setMinIdle(12).build();
	}
} // namespace BuilderPattern