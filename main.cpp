#include "Reactor/Reactor.h"
#include "main.h"

int main()
{
	using namespace std;

	PxDocumentReactor::performSample();

	// 创建型
	system("cls");
	SingletonPattern::Entry();

	FactoryMethodPattern::Entry();
	AbstractFactoryPattern::Entry();

	system("cls");
	BuilderPattern::Entry();

	// 结构型
	system("cls");
	ProxyPattern::Entry();
	BridgePattern::Entry();
	DecoratorPattern::Entry();
	AdapterPattern::Entry();
	FacadePattern::Entry();
	CompositePattern::Entry();
	PrototypePattern::Entry();

	// 行为型
	system("cls");
	ObserverPattern::Entry();
	TemplateMethodPattern::Entry();
	StrategyPattern::Entry();
	ResponsibilityChainPattern::Entry();
	StatePattern::Entry();
	IteratorPattern::Entry();
	VisitorPattern::Entry();
	MementoPattern::Entry();
	CommandPattern::Entry();
	InterpreterPattern::Entry();
	MediatorPattern::Entry();

	return 0;
}

// 手绘设计模式
// https://github.com/gdhucoder/DesignPattern
