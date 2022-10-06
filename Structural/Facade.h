#pragma once
#include <iostream>

// 门面模式
// 为子系统提供一组统一的接口，定义一组高层接口让子系统更易用

namespace FacadePattern
{
	void Entry();

	/*
	* Subsystems
	* implement more complex subsystem functionality
	* and have no knowledge of the facade
	*/
	class SubsystemA
	{
	public:
		void suboperation()
		{
			std::cout << "Subsystem A method" << std::endl;
		}
	};

	class SubsystemB
	{
	public:
		void suboperation()
		{
			std::cout << "Subsystem B method" << std::endl;
		}
	};

	class SubsystemC
	{
	public:
		void suboperation()
		{
			std::cout << "Subsystem C method" << std::endl;
			// ...
		}
		// ...
	};

	/*
	* Facade
	* delegates client requests to appropriate subsystem object
	* and unified interface that is easier to use
	*/
	class Facade
	{
	public:
		Facade() : subsystemA(nullptr), subsystemB(nullptr), subsystemC(nullptr) {}

		void operation1()
		{
			subsystemA->suboperation();
			subsystemB->suboperation();
			// ...
		}

		void operation2()
		{
			subsystemC->suboperation();
			// ...
		}

	private:
		SubsystemA* subsystemA;
		SubsystemB* subsystemB;
		SubsystemC* subsystemC;
		// ...
	};

} // namespace FacadePattern





/*
适配器模式、门面模式：
共同点是，将不好用的接口适配成好用的接口

在应用场景上，门面模式侧重接口的易用性，隐藏实现细节与复杂性，还可以通过包装多个接口解决性能问题、分布式事务问题。适配器模式是对不良接口设计的补救
在代码实现上，适配器模式通过组合、继承实现，门面模式通过简单包装实现
在使用阶段上，适配器模式主要在后期维护时，弥补设计缺陷。门面模式是在编码初期，考虑的接口易用的设计问题



隐藏实现复杂性，提供更易用接口这个意图来看，
门面模式有点类似之前讲到的迪米特法则（最少知识原则）和接口隔离原则：两个有交互的系统，只暴露有限的必要的接口。
除此之外，门面模式还有点类似之前提到封装、抽象的设计思想，提供更抽象的接口，封装底层实现细节
*/