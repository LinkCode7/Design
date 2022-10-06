#pragma once
#include <iostream>


// 桥接模式
// Bridge模式通过组合的方式将抽象和实现分别独立实现

namespace BridgePattern
{
	void Entry();


	class AbstractionImp;

	class Abstraction
	{
	public:
		Abstraction() {}
		virtual ~Abstraction() {}

		virtual void Operation() = 0;
	};

	class AbstractionImp
	{
	public:
		virtual ~AbstractionImp() {}
		virtual void Operation() = 0;
	};

	class RefinedAbstraction :public Abstraction
	{
	public:
		RefinedAbstraction(AbstractionImp* imp) : _imp(imp) {}
		~RefinedAbstraction() { (_imp); }

		void Operation() { _imp->Operation(); }
	private:
		// 内嵌一个“需求实现基类”，而不是通过继承
		AbstractionImp* _imp;
	};

	class ConcreteAbstractionImpA :public AbstractionImp
	{
	public:
		void Operation() override { std::cout << "AbstractionImp....imp..." << std::endl; }
	};

	class ConcreteAbstractionImpB :public AbstractionImp
	{
	public:
		void Operation() override { std::cout << "ConcreteAbstractionImpB...." << std::endl; }
	};

} // namespace BridgePattern