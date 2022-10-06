#include <iostream>
#include "Prototype.h"


using namespace std;



namespace PrototypePattern
{
	void Entry()
	{
		Prototype* pPrototype = new ConcretePrototype();
		// C++的拷贝构造可实现原型模式，注意浅拷贝、深拷贝问题
		Prototype* pPrototypeClone = pPrototype->Clone();

		(pPrototype);
		(pPrototypeClone);
	}



	Prototype::Prototype()
	{
	}
	Prototype::~Prototype()
	{
	}
	Prototype* Prototype::Clone() const
	{
		return 0;
	}
	ConcretePrototype::ConcretePrototype()
	{
	}
	ConcretePrototype::~ConcretePrototype()
	{
	}
	ConcretePrototype::ConcretePrototype(const ConcretePrototype& cp)
	{
		cout << "ConcretePrototype copy ..." << endl;
	}
	Prototype* ConcretePrototype::Clone() const
	{
		return new ConcretePrototype(*this);
	}
} // namespace PrototypePattern