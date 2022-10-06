#include "Bridge.h"

using namespace std;

namespace BridgePattern
{
	void Entry()
	{
		AbstractionImp* pAbstractionImp = new ConcreteAbstractionImpA();
		Abstraction* pAbstraction = new RefinedAbstraction(pAbstractionImp);
		pAbstraction->Operation();

		//(pAbstractionImp);
		(pAbstraction);
	}

} // namespace BridgePattern
