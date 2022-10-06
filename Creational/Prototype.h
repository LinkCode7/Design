#pragma once



// 原型模式
// 通过复制原型（Prototype）而获得新对象创建的功能
// 抽象工厂模式、创建者模式、原型模式都是用专门的类去负责对象的创建

namespace PrototypePattern
{
	void Entry();


	class Prototype
	{
	public:
		virtual ~Prototype();
		virtual Prototype* Clone() const = 0;
	protected:
		Prototype();
	private:
	};


	class ConcretePrototype :public Prototype
	{
	public:
		ConcretePrototype();
		ConcretePrototype(const ConcretePrototype& cp);
		~ConcretePrototype();
		Prototype* Clone() const;
	protected:
	private:
	};

} // namespace PrototypePattern