#include "Iterator.h"

#include <vector>
#include <iostream>

namespace IteratorPattern
{
	void Entry()
	{
		unsigned int size = 5;
		ConcreteAggregate list = ConcreteAggregate(size);

		Iterator* it = list.createIterator();
		for (; !it->isDone(); it->next())
		{
			std::cout << "Item value: " << it->currentItem() << std::endl;
		}

		delete it;


		TestIterator();
		TestVectorErase();
		TestVectorErase2();
	}

	void TestIterator()
	{
		// vector
		std::vector<std::string> names;
		names.push_back("111");
		names.push_back("222");
		names.push_back("333");

		IIterator<std::string>* iterator = new VectorIterator<std::string>(&names);
		while (iterator->hasNext())
		{
			std::cout << iterator->currentItem() << std::endl;
			iterator->next();
		}

		delete iterator;

		// for ѭ������
		for (int i = 0; i < names.size(); i++)
		{
			std::cout << names.at(i) << std::endl;
		}
	}

	void print_container(const std::vector<int>& vec)
	{
		for (auto& i : vec) {
			std::cout << i << " ";
		}
		std::cout << '\n';
	}
	void TestVectorErase()
	{
		using namespace std;

		std::vector<int> vec{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		print_container(vec);

		vec.erase(vec.begin());
		print_container(vec);

		vec.erase(vec.begin() + 2, vec.begin() + 5);
		print_container(vec);

		// Erase all even numbers (C++11 and later)
		for (auto it = vec.begin(); it != vec.end(); )
		{
			if (*it % 2 == 0)
				it = vec.erase(it);
			else
				++it;
		}
		print_container(vec);
	}
	void TestVectorErase2()
	{
		using namespace std;

		std::vector<int> vec{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		print_container(vec);

		int iCount = 0;
		auto it = vec.begin();
		for (; it != vec.end(); )
		{
			if (false)
			{
				vec.erase(it);
				it++;
			}

			if (false)
			{
				vec.insert(it, 100);
				it++;
			}

			++iCount;
			if (iCount == 10)
				break;
		}
		print_container(vec);
	}

} // namespace IteratorPattern