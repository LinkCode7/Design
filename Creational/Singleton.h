#pragma once


// 单例模式
// 一个类只允许创建唯一一个对象或者实例，那这个类就是一个单例类，这种设计模式就叫作单例设计模式，简称单例模式


namespace SingletonPattern
{
	void Entry();

	// 经典实现方法
	class Singleton
	{
		int m_id;
	public:
		static Singleton& Instance();

		int GetId()
		{
			return m_id;
		}

		void SetId(int id)
		{
			m_id = id;
		}

	protected:
		Singleton() :m_id(1)
		{
			std::cout << "---contructor Singleton---" << std::endl;
		}
	};



	// 饿汉式（着急吃）
	// 在类加载的时候，instance 静态实例就已经创建并初始化好了，instance 实例的创建过程是线程安全的。
	// 缺点：不支持延迟加载（在真正用到 IdGenerator 的时候，再创建实例）
	class IdGenerator
	{
	private:
		int id;
		static IdGenerator* instance;// = new IdGenerator();
		IdGenerator() { id = 0; }
	public:
		static IdGenerator* getInstance() {
			return instance;
		}
		int getId() {
			return id;
		}



	};




	// spring源码
	class SingletonL
	{
		// 当使用volatile声明的变量的值的时候，系统总是重新从它所在的内存读取数据
		// 即使它前面的指令刚刚从该处读取过数据。而且读取的数据立刻被保存
	static SingletonL* volatile instance;

	public:
		static SingletonL* getInstance()
		{
			// 用局部变量接收，只需要访问1次主存，性能更好
			// （volatile修饰的静态变量访问比较慢）
			SingletonL* temp = instance;
			if (nullptr == temp)
			{
				//synchronized(Singleton.class) //对象锁
				{
					temp = instance;
					if (nullptr == temp)
					{
						temp = new SingletonL();
						instance = temp;
					}
				}
			}
			return temp;
		}
	};

} // SingletonPattern


#define SingleOpr SingletonPattern::Singleton::Instance()