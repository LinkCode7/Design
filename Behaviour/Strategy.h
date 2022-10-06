#pragma once
#include <iostream>

// 策略模式
// 解耦策略的定义、创建、使用
namespace StrategyPattern
{
	void Entry();

	/*
	* Strategy
	* declares an interface common to all supported algorithms
	*/
	class Strategy
	{
	public:
		virtual ~Strategy() {}
		virtual void algorithmInterface() = 0;
	};

	/*
	* Concrete Strategies
	* implement the algorithm using the Strategy interface
	*/
	class ConcreteStrategyA : public Strategy
	{
	public:
		~ConcreteStrategyA() {}

		void algorithmInterface()override
		{
			std::cout << "Concrete Strategy A" << std::endl;
		}
	};

	class ConcreteStrategyB : public Strategy
	{
	public:
		~ConcreteStrategyB() {}

		void algorithmInterface()override
		{
			std::cout << "Concrete Strategy B" << std::endl;
		}
	};

	class ConcreteStrategyC : public Strategy
	{
	public:
		~ConcreteStrategyC() {}

		void algorithmInterface()override
		{
			std::cout << "Concrete Strategy C" << std::endl;
		}
	};

	/*
	* Context
	* maintains a reference to a Strategy object
	*/
	class Context
	{
	public:
		Context(Strategy* const s) : strategy(s) {}
		~Context()
		{
			delete strategy;
		}

		void contextInterface()
		{
			strategy->algorithmInterface();
		}

	private:
		Strategy* strategy;
	};

} // namespace StrategyPattern




/*
一提到策略模式，有人就觉得，它的作用是避免 if-else 分支判断逻辑。实际上，这种认识是很片面的。
策略模式主要的作用还是解耦策略的定义、创建和使用，控制代码的复杂度，让每个部分都不至于过于复杂、代码量过多。
对于复杂代码来说，策略模式还能让其满足开闭原则，添加新策略的时候，最小化、集中化代码改动，减少引入bug的风险

策略模式、工厂模式：
策略模式侧重“策略”或“算法”这个特定的应用场景，用来解决根据运行时状态从一组策略中选择不同策略的问题
工厂模式侧重封装对象的创建过程，这里的对象没有任何业务场景的限定，可以是策略，但也可以是其他东西

策略模式、职责链模式

策略模式、命令模式：
在策略模式中，不同的策略具有相同的目的、不同的实现、互相之间可以替换。
比如，BubbleSort、SelectionSort 都是为了实现排序的，只不过一个是用冒泡排序算法来实现的，另一个是用选择排序算法来实现的。
在命令模式中，不同的命令具有不同的目的，对应不同的处理逻辑，并且互相之间不可替换


-> 设计模式之间的主要区别还是在于设计意图，也就是应用场景。不能单纯地看设计思路或者代码实现
*/