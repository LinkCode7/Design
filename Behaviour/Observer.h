#pragma once
#include <vector>
#include <iostream>


// 观察者模式
namespace ObserverPattern
{
	void Entry();

	class Subject;

	/*
	* Observer
	* defines an updating interface for objects that should be notified
	* of changes in a subject
	*/
	class Observer
	{
	public:
		virtual ~Observer() {}
		virtual int getState() = 0;
		virtual void update(Subject* subject) = 0;
	};

	/*
	* Concrete Observer
	* stores state of interest to ConcreteObserver objects and
	* sends a notification to its observers when its state changes
	*/
	class ConcreteObserver : public Observer
	{
	public:
		ConcreteObserver(const int state) :observer_state(state) {}
		~ConcreteObserver() = default;

		int getState()
		{
			return observer_state;
		}

		void update(Subject* subject);

	private:
		int observer_state;
	};

	/*
	* Subject
	* knows its observers and provides an interface for attaching
	* and detaching observers
	*/
	class Subject
	{
	public:
		virtual ~Subject() {}

		void attach(Observer* observer)
		{
			observers.push_back(observer);
		}

		void detach(const int index)
		{
			observers.erase(observers.begin() + index);
		}

		void notify()
		{
			// 被观察者同步阻塞，直到所有观察者处理完变更业务
			// ->可以用消息队列实现进程间的消息分发
			// 在观察者的事件处理函数中启动线程来解决同步阻塞的问题，
			// 但频繁地创建和销毁线程比较耗时，并且并发线程数无法控制，创建过多的线程会导致堆栈溢出
			// ->可以用线程池解决频繁创建线程的问题
			// ->如果要在同步阻塞和异步非阻塞之间灵活切换，需要引入框架，如Google Guava EventBus

			// Duilib中的观察者模式、boost中的观察者模式
			for (unsigned int i = 0; i < observers.size(); i++)
			{
				observers.at(i)->update(this);
			}
		}

		virtual int getState() = 0;
		virtual void setState(const int s) = 0;

	private:
		std::vector<Observer*> observers;
	};

	/*
	* Concrete Subject
	* stores state that should stay consistent with the subject's
	*/
	class ConcreteSubject : public Subject
	{
	public:
		~ConcreteSubject() {}

		int getState()
		{
			return subject_state;
		}

		void setState(const int state)
		{
			subject_state = state;
		}

	private:
		int subject_state;
	};

	void ConcreteObserver::update(Subject* subject)
	{
		observer_state = subject->getState();
		std::cout << "Observer state updated." << std::endl;
	}

} // namespace ObserverPattern
