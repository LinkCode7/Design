#include <queue>
#include "Command.h"


namespace CommandPattern
{
	void Entry()
	{
		GameApplication();

		ConcreteCommand command(new Receiver());

		Invoker invoker;
		invoker.set(&command);
		invoker.confirm();
	}

	void GameApplication()
	{
		int MAX_HANDLED_REQ_COUNT_PER_LOOP = 100;
		std::queue<ICommand*> queue;

		int iCount = 0;
		while (true)
		{
			std::vector<Request> requests;
			//省略从epoll或者select中获取数据，并封装成Request的逻辑，
			//注意设置超时时间，如果很长时间没有接收到请求，就继续下面的逻辑处理。

			for (Request request : requests)
			{
				EventType event = request.getEvent();

				ICommand* command = nullptr;
				if (event == GOT_DIAMOND) {
					command = new GotDiamondCommand(/*数据*/);
				}
				else if (event == GOT_STAR) {
					command = new GotStartCommand(/*数据*/);
				}
				else if (event == HIT_OBSTACLE) {
					command = new HitObstacleCommand(/*数据*/);
				}
				else if (event == ARCHIVE) {
					command = new ArchiveCommand(/*数据*/);
				} // ...一堆else if...
				else {
					continue;
				}

				queue.push(command);
			}

			int handledCount = 0;
			while (handledCount < MAX_HANDLED_REQ_COUNT_PER_LOOP)
			{
				if (queue.empty())
					break;

				ICommand* command = queue.front();
				command->execute();
				++handledCount;
			}

			if (iCount > 100)
				break;
			++iCount;
		}
	}

} // namespace CommandPattern