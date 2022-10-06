#pragma once
#include <vector>
#include <iostream>

// 中介模式
namespace MediatorPattern
{
	class Mediator;

	/*
	 * Colleague classes
	 * each colleague communicates with its mediator whenever
	 * it would have otherwise communicated with another colleague
	 */
	class Colleague
	{
	public:
		Colleague(Mediator* const m, const unsigned int i) :
			mediator(m), id(i) {}

		virtual ~Colleague() {}

		unsigned int getID()
		{
			return id;
		}

		virtual void send(std::string) = 0;
		virtual void receive(std::string) = 0;

	protected:
		Mediator* mediator;
		unsigned int id;
	};

	class ConcreteColleague : public Colleague
	{
	public:
		ConcreteColleague(Mediator* const m, const unsigned int i) :
			Colleague(m, i) {}

		~ConcreteColleague() {}

		void send(std::string msg);

		void receive(std::string msg)
		{
			std::cout << "Message '" << msg << "' received by Colleague " << id << std::endl;
		}
	};

	/*
	 * Mediator
	 * defines an interface for communicating with Colleague objects
	 */
	class Mediator
	{
	public:
		virtual ~Mediator() {}

		virtual void add(Colleague* const c) = 0;
		virtual void distribute(Colleague* const sender, std::string msg) = 0;

	protected:
		Mediator() {}
	};

	/*
	 * Concrete Mediator
	 * implements cooperative behavior by coordinating Colleague objects
	 * and knows its colleagues
	 */
	class ConcreteMediator : public Mediator
	{
	public:
		~ConcreteMediator()
		{
			for (unsigned int i = 0; i < colleagues.size(); i++)
			{
				delete colleagues[i];
			}
			colleagues.clear();
		}

		void add(Colleague* const c)
		{
			colleagues.push_back(c);
		}

		void distribute(Colleague* const sender, std::string msg)
		{
			for (unsigned int i = 0; i < colleagues.size(); i++)
			{
				if (colleagues.at(i)->getID() != sender->getID())
				{
					colleagues.at(i)->receive(msg);
				}
			}
		}

	private:
		std::vector<Colleague*> colleagues;
	};

} // namespace MediatorPattern


/*
中介模式、观察者模式（都是为了实现参与者之间的解耦，简化交互关系）
在观察者模式的应用场景中，参与者之间的交互比较有条理，一般都是单向的，一个参与者只有一个身份，要么是观察者，要么是被观察者；
在中介模式的应用场景中，参与者之间的交互关系错综复杂，既可以是消息的发送者、也可以同时是消息的接收者

中介模式、桥接模式
*/