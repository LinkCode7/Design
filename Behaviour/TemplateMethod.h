#pragma once
#include <iostream>

/*
模板方法模式：主要解决复用和扩展问题。
复用指的是，所有的子类可以复用父类中提供的模板方法的代码
扩展指的是，框架通过模板模式提供功能扩展点，让框架用户可以在不修改框架源码的情况下，基于扩展点定制化框架的功能

常用在框架开发中，通过提供功能扩展点，让框架用户在不修改框架源码的情况下，基于扩展点定制化框架的功能。
除此之外，模板模式还可以起到代码复用的作用
*/

namespace TemplateMethodPattern
{
	void Entry();

	/*
	* AbstractClass
	* implements a template method defining the skeleton of an algorithm
	*/
	class AbstractClass
	{
	public:
		virtual ~AbstractClass() {}

		void templateMethod()
		{
			// ...
			primitiveOperation1(); // 提供扩展点
			// ...
			primitiveOperation2();
			// ...
		}

		virtual void primitiveOperation1() = 0;
		virtual void primitiveOperation2() = 0;
	};

	/*
	* Concrete Class
	* implements the primitive operations to carry out specific steps
	* of the algorithm, there may be many Concrete classes, each implementing
	* the full set of the required operation
	*/
	class ConcreteClass : public AbstractClass
	{
	public:
		~ConcreteClass() = default;

		void primitiveOperation1()override
		{
			std::cout << "Primitive operation 1" << std::endl;
			// ...
		}

		void primitiveOperation2()override
		{
			std::cout << "Primitive operation 2" << std::endl;
			// ...
		}
	};

} // namespace TemplateMethodPattern

// 模板方法模式、回调、观察者模式
