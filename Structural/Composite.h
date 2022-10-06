#pragma once
#include <vector>
#include <iostream>

// 组合模式
namespace CompositePattern
{
	void Entry();

	class Component
	{
	public:
		Component() = default;
		virtual ~Component() = default;
	public:
		virtual void Operation() = 0;
		virtual void Add(const Component&) {}
		virtual void Remove(const Component&) {}
		virtual Component* GetChild(int) { return 0; }
	};

	class Composite :public Component
	{
	public:
		Composite() = default;
		~Composite()
		{
			for (auto& pointer : comVec)
				delete pointer;
		}
	public:
		void Operation()
		{
			std::vector<Component*>::iterator comIter = comVec.begin();
			for (; comIter != comVec.end(); comIter++)
			{
				(*comIter)->Operation();
			}
		}
		void Add(Component* com) { comVec.push_back(com); }
		void Remove(Component* com)
		{
			std::vector<Component*>::iterator iter = std::find(comVec.begin(), comVec.end(), com);
			if (iter != comVec.end())
				comVec.erase(iter);
		}
		Component* GetChild(int index) { return comVec[index]; }
	private:
		std::vector<Component*> comVec;
	};

	class Leaf :public Component
	{
	public:
		Leaf() = default;
		~Leaf() = default;
		void Operation() { std::cout << "Leaf operation....." << std::endl; }
	};

} // namespace CompositePattern