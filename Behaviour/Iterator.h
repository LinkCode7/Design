#pragma once
#include <vector>

// 迭代器模式（游标模式）
namespace IteratorPattern
{
	void Entry();
	void TestIterator();
	void TestVectorErase();
	void TestVectorErase2();

	class Iterator;
	class ConcreteAggregate;

	/*
	 * Aggregate
	 * defines an interface for aggregates and it decouples your
	 * client from the implementation of your collection of objects
	 */
	class Aggregate
	{
	public:
		virtual ~Aggregate() {}
		virtual Iterator* createIterator() = 0;
	};

	/*
	 * Concrete Aggregate
	 * has a collection of objects and implements the method
	 * that returns an Iterator for its collection
	 *
	 */
	class ConcreteAggregate : public Aggregate
	{
	public:
		ConcreteAggregate(const unsigned int size)
		{
			list = new int[size]();
			count = size;
		}

		~ConcreteAggregate()
		{
			delete[] list;
		}

		Iterator* createIterator();

		unsigned int size() const
		{
			return count;
		}

		int at(unsigned int index)
		{
			return list[index];
		}
		// ...

	private:
		int* list;
		unsigned int count;
	};

	/*
	 * Iterator
	 * provides the interface that all iterators must implement and
	 * a set of methods for traversing over elements
	 */
	class Iterator
	{
	public:
		virtual ~Iterator() {}

		virtual void first() = 0;
		virtual void next() = 0;
		virtual bool isDone() const = 0;
		virtual int currentItem() const = 0;
	};

	/*
	 * Concrete Iterator
	 * implements the interface and is responsible for managing
	 * the current position of the iterator
	 */
	class ConcreteIterator : public Iterator
	{
	public:
		ConcreteIterator(ConcreteAggregate* l) :
			list(l), index(0) {}

		~ConcreteIterator() {}

		void first()
		{
			index = 0;
		}

		void next()
		{
			index++;
		}

		bool isDone() const
		{
			return (index >= list->size());
		}

		int currentItem() const
		{
			if (isDone())
			{
				return -1;
			}
			return list->at(index);
		}

	private:
		ConcreteAggregate* list;
		unsigned int index;
	};

	Iterator* ConcreteAggregate::createIterator()
	{
		return new ConcreteIterator(this);
	}







	// 接口定义
	template <typename E>
	class IIterator
	{
	public:
		virtual bool hasNext() = 0;
		virtual void next() = 0;
		virtual E currentItem() = 0;
	};
	template <typename E>
	class IIterator2
	{
	public:
		virtual bool hasNext() = 0;
		virtual E next() = 0;
	};



	template <typename E>
	class VectorIterator :public IIterator<E>
	{
	private:
		int _cursor;
		std::vector<E>* _arrayList;

	public:
		// 依赖注入
		VectorIterator(std::vector<E>* arrayList) : _cursor(0), _arrayList(arrayList) {}

		// 注意这里，_arrayList在指向最后一个元素的时候，hasNext()仍旧返回true
		bool hasNext()override { return _cursor != _arrayList->size(); }

		void next()override { _cursor++; }

		E currentItem()
		{
			if (_cursor >= _arrayList->size())
				throw new std::range_error("out of range");

			return _arrayList->at(_cursor);
		}
	};

} // namespace IteratorPattern


/*
// 为什么需要迭代器
对于类似数组和链表这样的数据结构，遍历方式比较简单，直接使用 for 循环来遍历就足够了。
但是，对于复杂的数据结构（比如树、图）来说，有各种复杂的遍历方式。
比如，树有前中后序、按层遍历，图有深度优先、广度优先遍历等等。
如果由客户端代码来实现这些遍历算法，势必增加开发成本，而且容易写错。
如果将这部分遍历的逻辑写到容器类中，也会导致容器类代码的复杂性

应对复杂性的方法就是拆分。我们可以将遍历操作拆分到迭代器类中。
比如图的遍历，我们就可以定义 DFSIterator、BFSIterator，让它们分别来实现深度优先遍历和广度优先遍历

容器和迭代器都提供了抽象的接口，方便我们在开发的时候，基于接口而非具体的实现编程。
当需要切换新的遍历算法的时候，比如，从前往后遍历链表切换成从后往前遍历链表，
客户端代码只需要将迭代器类从 LinkedIterator 切换为 ReversedLinkedIterator 即可。
除此之外，添加新的遍历算法，我们只需要扩展新的迭代器类，也更符合开闭原则
*/