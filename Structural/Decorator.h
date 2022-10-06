#pragma once
#include <iostream>


// 装饰器模式
// Decorator提供了一种给类增加职责的方法，不是通过继承实现的，而是通过组合
namespace DecoratorPattern
{
	void Entry();

	class Component
	{
	public:
		virtual ~Component() {}
		virtual void Operation() {}
	protected:
		Component() {}
	};

	class ConcreteComponent :public Component
	{
	public:
		ConcreteComponent() {}
		~ConcreteComponent() {}
		void Operation() { std::cout << "ConcreteComponent operation..." << std::endl; }
	};


	class Decorator :public Component
	{
	public:
		Decorator(Component* com) :_com(com) {}
		virtual ~Decorator() { delete _com; }
		void Operation() {}
	protected:
		Component* _com;
	};

	class ConcreteDecorator :public Decorator
	{
	public:
		ConcreteDecorator(Component* com) :Decorator(com) {}
		~ConcreteDecorator() {}
		void AddedBehavior() { std::cout << "ConcreteDecorator::AddedBehacior...." << std::endl; }

		void Operation()
		{
			// 先执行基类的Operation
			_com->Operation();

			// 再执行本类的功能，相当于装饰了Component
			this->AddedBehavior();
		}
	};

} // namespace DecoratorPattern



  /*
  装饰器模式、代理模式：
  都是在虚函数前后做扩展（增强），即对功能的增强
  代理模式一般增强的是与功能无关的功能，如：监控、统计、限流
  装饰器模式的增强一般与功能强相关，它还可以嵌套使用多个装饰器

  装饰器模式、职责链模式：
  职责链模式是多个处理器依次处理同一个请求，形成一个链条，强调对请求的分发处理
  装饰器模式既可以嵌套多个装饰器，还可以扩展功能，强调扩展
  */
