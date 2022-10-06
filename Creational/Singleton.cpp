#include <iostream>
#include "Singleton.h"


using namespace std;


namespace SingletonPattern
{
	void Entry()
	{
		cout << "SingleOpr.GetId() " << SingleOpr.GetId() << endl; // 1

		SingleOpr.SetId(2);
		cout << "SingleOpr.SetId(2)" << endl; //2

		cout << "SingleOpr.GetId() " << SingleOpr.GetId() << endl; // 2

		Singleton opr = Singleton::Instance(); // 2
		cout << "Singleton::Instance()  GetId() " << opr.GetId() << endl;

		Singleton opr2 = Singleton::Instance(); // 2
		cout << "Singleton::Instance()  GetId() " << opr2.GetId() << endl;
	}

	// 静态对象不放置在class中，因为它可能不会被创建
	Singleton& Singleton::Instance()
	{
		// 属于类的全局对象
		static Singleton opr;
		return opr;
	}

} // SingletonPattern