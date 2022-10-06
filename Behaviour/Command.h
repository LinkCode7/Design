#pragma once
#include <iostream>

namespace CommandPattern
{
	/*
	 * Receiver
	 * knows how to perform the operations associated
	 * with carrying out a request
	 */
	class Receiver
	{
	public:
		void action()
		{
			std::cout << "Receiver: execute action" << std::endl;
		}
	};

	/*
	 * Command
	 * declares an interface for all commands
	 */
	class Command
	{
	public:
		virtual ~Command() {}
		virtual void execute() = 0;

	protected:
		Command() {}
	};

	/*
	 * Concrete Command
	 * implements execute by invoking the corresponding
	 * operation(s) on Receiver
	 */
	class ConcreteCommand : public Command
	{
	public:
		ConcreteCommand(Receiver* r) : receiver(r) {}

		~ConcreteCommand()
		{
			if (receiver)
				delete receiver;
		}

		void execute()
		{
			receiver->action();
		}

	private:
		Receiver* receiver;
	};

	/*
	 * Invoker
	 * asks the command to carry out the request
	 */
	class Invoker
	{
	public:
		void set(Command* c)
		{
			command = c;
		}

		void confirm()
		{
			if (command)
			{
				command->execute();
			}
		}

	private:
		Command* command;
	};








	void GameApplication();

	class ICommand
	{
	public:
		virtual void execute() = 0;
	};

	class GotDiamondCommand :public ICommand
	{
		// 省略成员变量
	public:
		GotDiamondCommand(/*数据*/) {}

		void execute()override { /*执行相应的逻辑*/ }
	};
	class GotStartCommand :public ICommand
	{
		// 省略成员变量
	public:
		GotStartCommand(/*数据*/) {}

		void execute()override { /*执行相应的逻辑*/ }
	};
	class HitObstacleCommand :public ICommand
	{
		// 省略成员变量
	public:
		HitObstacleCommand(/*数据*/) {}

		void execute()override { /*执行相应的逻辑*/ }
	};
	class ArchiveCommand :public ICommand
	{
		// 省略成员变量
	public:
		ArchiveCommand(/*数据*/) {}

		void execute()override { /*执行相应的逻辑*/ }
	};



	enum EventType
	{
		GOT_DIAMOND,
		GOT_STAR,
		HIT_OBSTACLE,
		ARCHIVE
	};
	class Request
	{
	public:
		EventType getEvent() { return GOT_DIAMOND; }
	};

} // namespace CommandPattern