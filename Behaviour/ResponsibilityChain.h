#pragma once
#include <vector>

namespace ResponsibilityChainPattern
{
	// 链表实现
	class Handler
	{
	public:
		void setSuccessor(Handler* successor)
		{
			this->successor = successor;
		}
		void handle()
		{
			bool handled = doHandle();
			if (successor != nullptr && !handled)
				successor->handle();
		}

		virtual ~Handler() { delete successor; }

	protected:
		Handler* successor = nullptr;
		virtual bool doHandle() = 0;
	};

	class HandlerA : public Handler
	{
	public:
		bool doHandle()override
		{
			bool handled = false;
			//...
			return handled;
		}
	};

	class HandlerB : public Handler
	{
	public:
		bool doHandle()override
		{
			bool handled = false;
			//...
			return handled;
		}
	};


	class HandlerChain
	{
	public:
		void addHandler(Handler* handler)
		{
			handler->setSuccessor(nullptr);
			if (head == nullptr)
			{
				head = handler;
				tail = handler;
				return;
			}

			tail->setSuccessor(handler);
			tail = handler;
		}

		void doHandles()
		{
			if (head != nullptr)
				head->handle();
		}

		~HandlerChain() { delete head; }
	private:
		Handler* head = nullptr;
		Handler* tail = nullptr;
	};





	// 容器实现
	class IHandler
	{
	public:
		virtual bool handle() = 0;
	};

	class Handler1 : public IHandler
	{
	public:
		bool handle()override
		{
			bool handled = false;
			//...
			return handled;
		}
	};

	class Handler2 : public IHandler
	{
	public:
		bool handle()override
		{
			bool handled = false;
			//...
			return handled;
		}
	};

	class HandlerChain2
	{
	public:
		void addHandler(IHandler* handler) { handlers.push_back(handler); }

		void doHandles()
		{
			for (const auto& handler : handlers)
			{
				bool handled = handler->handle();
				if (handled)
					break;
			}
		}
		~HandlerChain2()
		{
			for (auto& handler : handlers)
				delete handler;
		}
	private:
		std::vector<IHandler*> handlers;
	};

} // namespace ResponsibilityChainPattern
