#pragma once

#include<iostream>
#include<queue>
#include<stdlib.h>
//#include<pthread.h>
//#include<unistd.h>
#include <mutex>
#include <condition_variable>

#define QUEUE_CAPACITY 8


// 生产者-消费者模型
namespace ProducerConsumerModel
{
	void Entry();
	void _Entry();

	void* producter(void* arg);
	void* consumer(void* arg);
	


	class BlockQueue
	{
	public:
		BlockQueue(int capacity = QUEUE_CAPACITY);
		~BlockQueue();

		void PushData(const int &data);
		void PopData(int &data);

	private:
		void LockQueue()  //队列加锁
		{
			//pthread_mutex_lock(&_mutex);
			//std::unique_lock<std::mutex> lock(_mutex);
		}
		void UnlockQueue()  //队列解锁
		{
			//pthread_mutex_unlock(&_mutex);
		}
		void ProductWait()  //队列满，生产者等待
		{
			//pthread_cond_wait(&_full, &_mutex);
			//_full.wait(_mutex);
		}
		void ConsumeWait()  //队列空，消费者等待
		{
			//pthread_cond_wait(&_empty, &_mutex);
		}
		void NotifyProduct()  //队列不为满时，通知生产者
		{
			//pthread_cond_signal(&_full);
		}
		void NotifyConsume()  //队列不为空时，通知消费者
		{
			//pthread_cond_signal(&_empty);
		}
		bool IsEmpty()
		{
			return (_queue.size() == 0 ? true : false);
		}
		bool IsFull()
		{
			return (_queue.size() == _capacity ? true : false);
		}

	private:
		std::queue<int> _queue;
		int _capacity;
		std::mutex _mutex; // std::lock_guard<std::mutex> guard(g_pages_mutex);
		//std::unique_lock <std::mutex> lck(mtx);

		// pthread_cond_t
		std::condition_variable _full; // wait,notify_one
		std::condition_variable _empty;
	};

} // namespace ProducerConsumerModel