#include <iostream>
#include "Factory.h"

using namespace std;



namespace FactoryMethodPattern
{
	void Entry()
	{
		Factory* pFactory = new ConcreteFactory();
		Product* pProduct = pFactory->CreateProduct();

		(pFactory);
		(pProduct);
	}

	Product::~Product()
	{
	}

	ConcreteProduct::ConcreteProduct()
	{
		cout << "ConcreteProduct...." << endl;
	}
	ConcreteProduct::~ConcreteProduct()
	{
	}



	Factory::Factory()
	{
	}
	Factory::~Factory()
	{
	}
	ConcreteFactory::ConcreteFactory()
	{
		cout << "ConcreteFactory....." << endl;
	}
	ConcreteFactory::~ConcreteFactory()
	{
	}
	Product* ConcreteFactory::CreateProduct()
	{
		return new ConcreteProduct();
	}

} // namespace FactoryMethodPattern






namespace AbstractFactoryPattern
{
	void Entry()
	{
		AbstractFactory* pFactory1 = new ConcreteFactory1();
		AbstractProductA* pProductA1 = pFactory1->CreateProductA();
		AbstractProductB* pProductB1 = pFactory1->CreateProductB();

		AbstractFactory* pFactory2 = new ConcreteFactory2();
		AbstractProductA* pProductA2 = pFactory2->CreateProductA();
		AbstractProductB* pProductB2 = pFactory2->CreateProductB();

		(pFactory1);
		(pProductA1);
		(pProductB1);

		(pFactory2);
		(pProductA2);
		(pProductB2);
	}




	ProductA1::ProductA1()
	{
		cout << "ProductA1..." << endl;
	}

	ProductA2::ProductA2()
	{
		cout << "ProductA2..." << endl;
	}

	ProductB1::ProductB1()
	{
		cout << "ProductB1..." << endl;
	}

	ProductB2::ProductB2()
	{
		cout << "ProductB2..." << endl;
	}









	AbstractProductA* ConcreteFactory1::CreateProductA()
	{
		return new ProductA1();
	}
	AbstractProductB* ConcreteFactory1::CreateProductB()
	{
		return new ProductB1();
	}

	AbstractProductA* ConcreteFactory2::CreateProductA()
	{
		return new ProductA2();
	}
	AbstractProductB* ConcreteFactory2::CreateProductB()
	{
		return new ProductB2();
	}

} // namespace AbstractFactoryPattern
