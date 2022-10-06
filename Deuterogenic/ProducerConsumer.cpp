#include <iostream>
#include "ProducerConsumer.h"

#include <thread>


using namespace std;
//std::this_thread::sleep_for(std::chrono::seconds(2));

namespace ProducerConsumerModel
{
	void Entry()
	{
		//BlockQueue bq;
		//pthread_t c, p;_D

		//pthread_create(&c, NULL, consumer, (void*)&bq);
		//pthread_create(&p, NULL, producter, (void*)&bq);

		//pthread_join(c, NULL);
		//pthread_join(p, NULL);

		_Entry();
	}

	void _Entry()
	{
		BlockQueue bq;

		std::thread t1(producter, &bq);
		std::thread t2(consumer, &bq);
		t1.join();
		t2.join();
	}


	// 生产者
	void* producter(void* arg)
	{
		BlockQueue* bqp = (BlockQueue*)arg;
		srand((unsigned long)time(NULL));
		for (;;)
		{
			int data = rand() % 1024;
			bqp->PushData(data);
			std::cout << "Product data done: " << data << std::endl;
			// sleep(1);
		}
	}

	// 消费者
	void* consumer(void* arg)
	{
		BlockQueue* bqp = (BlockQueue*)arg;
		int data;
		for (;;)
		{
			bqp->PopData(data);
			std::cout << "Consume data done: " << data << std::endl;
		}
	}

	void BlockQueue::PushData(const int& data)
	{
		LockQueue();
		while (IsFull()) //队列满
		{
			NotifyConsume();
			std::cout << "queue _full,notify consume data,product stop!!" << std::endl;
			ProductWait();
		}
		//队列不满,生产者插入数据，通知消费者队列中已经有数据了
		_queue.push(data);
		NotifyConsume();
		UnlockQueue();
	}
	void BlockQueue::PopData(int& data)
	{
		LockQueue();
		while (IsEmpty())  //队列为空
		{
			NotifyProduct();
			std::cout << "queue _empty,notify product data,consume stop!!" << std::endl;
			ConsumeWait();
		}
		//队列不为空
		data = _queue.front();
		_queue.pop();
		NotifyProduct();
		UnlockQueue();
	}

	BlockQueue::BlockQueue(int cap) :_capacity(cap)
	{
		//pthread_mutex_init(&_mutex, NULL);
		//pthread_cond_init(&_full, NULL);
		//pthread_cond_init(&_empty, NULL);
	}
	BlockQueue::~BlockQueue()
	{
		//pthread_mutex_destroy(&_mutex);
		//pthread_cond_destroy(&_full);
		//pthread_cond_destroy(&_empty);
	}

} // namespace ProducerConsumerModel