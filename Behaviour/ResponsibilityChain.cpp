#include "ResponsibilityChain.h"




namespace ResponsibilityChainPattern
{
	void Entry()
	{
		HandlerChain chain;
		chain.addHandler(new HandlerA());
		chain.addHandler(new HandlerB());
		chain.doHandles();
	}

	void Container()
	{
		HandlerChain2 chain;
		chain.addHandler(new Handler1());
		chain.addHandler(new Handler2());
		chain.doHandles();
	}

} // namespace ResponsibilityChainPattern
