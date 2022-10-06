#include "Proxy.h"

namespace ProxyPattern
{
	void Entry()
	{
		Proxy* proxy = new Proxy();
		proxy->request();

		delete proxy;
	}

	void ProxyFrame()
	{
		SubjectProxy* proxy = new SubjectProxy();
		proxy->request();

		delete proxy;
	}

} // namespace ProxyPattern
