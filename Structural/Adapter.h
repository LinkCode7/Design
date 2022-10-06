#pragma once




// 适配器模式
// 将接口转化为客户想要接口类型

namespace AdapterPattern
{
	void Entry();

	// 类适配器: 基于继承
	class ITarget
	{
	public:
		virtual void f1() {}
		virtual void f2() {}
		virtual void fc() {}
	};

	class Adaptee
	{
	public:
		void fa() { /*...*/ }
		void fb() { /*...*/ }
		void fc() { /*...*/ }
	};

	// private继承
	// 通过private继承获得Adaptee的实现效果，不暴露基类成员
	// 基类所有成员变量、成员函数在子类中的访问权限变为private（可以在成员函数中访问基类public成员，不能通过对象访问）
	class Adaptor: public ITarget, private Adaptee
	{
	public:
		void f1()override
		{
			Adaptee::fa();
		}
		void f2()override
		{
			//...重新实现f2()...
		}
		// 这里fc()不需要实现，直接继承自Adaptee，这是跟对象适配器最大的不同点
		void fc()override
		{
			Adaptee::fc();
		}
	};



	// 对象适配器：基于组合
	class Adaptor2: public ITarget
	{
	private:
		Adaptee _adaptee;
  
	public:
		Adaptor2(Adaptee& adaptee) :_adaptee(adaptee) {}
  
		void f1()
		{
			_adaptee.fa(); //委托给Adaptee
		}
  
		void f2()
		{
			//...重新实现f2()...
		}
  
		void fc()
		{
			_adaptee.fc();
		}
	};

} // namespace AdapterPattern


// 泛型

/*
代理、桥接、装饰器、适配器
这 4 种模式是比较常用的结构型设计模式，它们的代码结构非常相似。
笼统来说，它们都可以称为 Wrapper 模式，也就是通过 Wrapper 类二次封装原始类。
但这 4 种设计模式的用意完全不同，也就是说要解决的问题、应用场景不同，这也是它们的主要区别。

代理模式：代理模式在不改变原始类接口的条件下，为原始类定义一个代理类，主要目的是控制访问，而非加强功能，这是它跟装饰器模式最大的不同。
桥接模式：桥接模式的目的是将接口部分和实现部分分离，从而让它们可以较为容易、也相对独立地加以改变。
装饰器模式：装饰者模式在不改变原始类接口的情况下，对原始类功能进行增强，并且支持多个装饰器的嵌套使用。
适配器模式：适配器模式是一种事后的补救策略。适配器提供跟原始类不同的接口，而代理模式、装饰器模式提供的都是跟原始类相同的接口。
*/