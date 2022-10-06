#pragma once
#include <iostream>

namespace ProxyPattern
{
	void Entry();
	void ProxyFrame();

	// 用组合的方式实现代理
	class ISubject
	{
	public:
		virtual ~ISubject() { /* ... */ }
		virtual void request() = 0;
	};

	/*
	* Real ISubject
	* defines the real object that the proxy represents
	*/
	class RealSubject : public ISubject
	{
	public:
		void request()override
		{
			std::cout << "RealSubject::request" << std::endl;
		}
	};

	/*
	* Proxy
	* maintains a reference that lets the proxy access the real subject
	*/
	class Proxy : public ISubject
	{
	public:
		Proxy() { subject = new RealSubject(); }
		~Proxy() { delete subject; }

		void request()override
		{
			std::cout << "Do something begin" << std::endl;
			subject->request();
			std::cout << "Do something end" << std::endl;
		}

	private:
		RealSubject* subject;
	};




	// 用继承的方式实现代理（代理框架中的类）
	class RealSubject2
	{
	public:
		virtual void request()
		{
			std::cout << "RealSubject::request" << std::endl;
		}
	};

	class SubjectProxy : public RealSubject2
	{
	public:
		void request()override
		{
			std::cout << "Do something begin" << std::endl;
			RealSubject2::request();
			std::cout << "Do something end" << std::endl;
		}
	};






	// 动态代理
	class RequestInfo
	{
		//...省略constructor/getter/setter方法...
	};

	class MetricsCollector
	{
	public:
		//MetricsCollector(MetricsStorage metricsStorage) {
		//	this(metricsStorage, DEFAULT_STORAGE_THREAD_POOL_SIZE);
		//}

		//public MetricsCollector(MetricsStorage metricsStorage, int threadNumToSaveData) {
		//	this.metricsStorage = metricsStorage;
		//	this.eventBus = new AsyncEventBus(Executors.newFixedThreadPool(threadNumToSaveData));
		//	this.eventBus.register(new EventListener());
		//}

		void recordRequest(RequestInfo requestInfo)
		{
			//if (requestInfo == null || StringUtils.isBlank(requestInfo.getApiName()))
			//	return;
			//eventBus.post(requestInfo);
		}
	};

	class InvocationHandler
	{
	public:
		//virtual Object invoke(Object proxy, Method method, Object[] args) = 0;
	};

	class MetricsCollectorProxy
	{
	private:
		MetricsCollector* metricsCollector;

	public:
		MetricsCollectorProxy()
		{
			metricsCollector = new MetricsCollector();
		}

		//Object createProxy(Object proxiedObject)
		//{
		//	Class< ? >[] interfaces = proxiedObject.getClass().getInterfaces();
		//	DynamicProxyHandler handler = new DynamicProxyHandler(proxiedObject);
		//	return Proxy.newProxyInstance(proxiedObject.getClass().getClassLoader(), interfaces, handler);
		//}

	private:
		class DynamicProxyHandler : public InvocationHandler
		{
			//private:
			//	Object proxiedObject;

			//public:
			//	DynamicProxyHandler(Object proxiedObject)
			//	{
			//		this.proxiedObject = proxiedObject;
			//	}

			//	Object invoke(Object proxy, Method method, Object[] args)override //throws Throwable
			//	{
			//		long startTimestamp = System.currentTimeMillis();
			//		Object result = method.invoke(proxiedObject, args);
			//		long endTimeStamp = System.currentTimeMillis();

			//		long responseTime = endTimeStamp - startTimestamp;
			//		String apiName = proxiedObject.getClass().getName() + ":" + method.getName();
			//		RequestInfo requestInfo = new RequestInfo(apiName, responseTime, startTimestamp);

			//		metricsCollector.recordRequest(requestInfo);
			//		return result;
			//	}
		};
	};


	//// MetricsCollectorProxy使用举例
	//MetricsCollectorProxy proxy = new MetricsCollectorProxy();
	//IUserController userController = (IUserController)proxy.createProxy(new UserController());

} // namespace ProxyPattern