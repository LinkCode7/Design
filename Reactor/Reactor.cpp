#include "Reactor.h"
#include "EntityModule.h"

#include <iostream>




void PxDocumentReactor::performSample()
{
	{
		PxShape* pItem = new PxShape();
		pItem->setColor(-1);
		delete pItem;
	}

	{
		PxShape* pItem = new PxShape();
		PxShapeFormat format = pItem->getFormat();
		format.setIntValue(666);

		auto fill = format.getFill();
		fill.setValue(123456);
		delete pItem;
	}

	{
		PxShape* pItem = new PxShape();

		PxShapeFormat format;
		format.setIntValue(-1000);
		format.setOwner(pItem); // 指定构造函数的参数
		format.setIntValue(-1000);

		pItem->setFormat(format);
		delete pItem;
	}
}

void PxDocumentReactor::notifyEvent(PxShape* pItem, int flag)
{
	if (!pItem)
		return;

	// 这里可以用专门的类控制响应器开关，可以全关或者只关部分属性
	if (true && flag == 1)
		return;

	// 事件分发...
	for (const auto& pReactor : m_arrReactor)
	{
		pReactor->notify(pItem, flag);
	}
}

void ComponentReactor::notify(PxShape* pItem, int flag)
{
	std::cout << "ComponentReactor::notify:" << std::hex << pItem << std::endl;
}
