#pragma once
// 工厂模式
// 用专门的对象管理需要大量创建的对象，用多态创建一组（有多类）相关或依赖的对象
// 大白话：创建对象，Type* t = new Type;

/*
--->使用工厂模式的最本质的参考标准
封装变化：创建逻辑有可能变化，封装成工厂类之后，创建逻辑的变更对调用者透明。
代码复用：创建代码抽离到独立的工厂类之后可以复用。隔离复杂性：封装复杂的创建逻辑，调用者无需了解如何创建对象。
控制复杂度：将创建代码抽离出来，让原本的函数或类职责更单一，代码更简洁。
*/


// 简单工厂
namespace SimpleFactoryPattern
{
	class Product {};
	class Product1 : public Product {};
	class Product2 : public Product {};
	class Product3 : public Product {};
	Product* CreateProduct(int key)
	{
		if (key == 1)
			return new(Product1);
		else if (key == 2)
			return new(Product2);
		else if (key == 3)
			return new(Product3);
		return nullptr;
	}
} // namespace SimpleFactoryPattern


// 工厂方法
namespace FactoryMethodPattern
{
	void Entry();

	class Product
	{
	public:
		// 抽象类，释放子类资源
		virtual ~Product()=0;
	};


	class ConcreteProduct: public Product
	{
	public:
		~ConcreteProduct();
		ConcreteProduct();
	};

	class Factory
	{
	public:
		virtual ~Factory() = 0;
		virtual Product* CreateProduct() = 0; 
	protected:
			Factory();
	};


	class ConcreteFactory :public Factory
	{
	public:
		~ConcreteFactory();
		ConcreteFactory();

		Product* CreateProduct(); protected:
	};

} // namespace FactoryMethodPattern



// 抽象工厂
// 创建大的对象，为创建多个相互依赖的对象提供统一的接口，一般直接返回对象
namespace AbstractFactoryPattern
{
	void Entry();

	class AbstractProductA
	{
	public:
		virtual ~AbstractProductA() {}
	protected:
		AbstractProductA() {}
	};

	class ProductA1 :public AbstractProductA
	{
	public:
		ProductA1();
		~ProductA1() {}
	};

	class ProductA2 :public AbstractProductA
	{
	public:
		ProductA2();
		~ProductA2() {}
	};


	class AbstractProductB
	{
	public:
		virtual ~AbstractProductB() {}
	protected:
		AbstractProductB() {}
	};

	class ProductB1 :public AbstractProductB
	{
	public:
		ProductB1();
		~ProductB1() {}
	};

	class ProductB2 :public AbstractProductB
	{
	public:
		ProductB2();
		~ProductB2() {}
	};




	class AbstractFactory
	{
	public:
		virtual ~AbstractFactory() {}
		virtual AbstractProductA* CreateProductA() = 0;
		virtual AbstractProductB* CreateProductB() = 0;
	protected:
		AbstractFactory() {}
	};

	class ConcreteFactory1 :public AbstractFactory
	{
	public:
		ConcreteFactory1() {}
		~ConcreteFactory1() {}
		AbstractProductA* CreateProductA();
		AbstractProductB* CreateProductB();
	};

	class ConcreteFactory2 :public AbstractFactory
	{
	public:
		ConcreteFactory2() {}
		~ConcreteFactory2() {}
		AbstractProductA* CreateProductA();
		AbstractProductB* CreateProductB();
	};

} // namespace AbstractFactoryPattern
