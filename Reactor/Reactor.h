#ifndef COMPONENT_REACTOR_H
#define COMPONENT_REACTOR_H
#include <memory>
#include <vector>

class PxShape;

// 响应器基类
class IReactor
{
public:
	virtual ~IReactor() = default;
	virtual void notify(PxShape* pItem, int flag) = 0;
};
using IReactorPtr = std::shared_ptr<IReactor>;



// 监控实体的属性变更，执行响应的复杂处理
class PxDocumentReactor
{
	PxDocumentReactor() {}
public:

	static void performSample();

public:
	static PxDocumentReactor& instance() { static PxDocumentReactor opr; return opr; }

	void notifyEvent(PxShape* pItem, int flag);

	// 注册响应器
	void addReactor(IReactorPtr pReactor) { m_arrReactor.emplace_back(pReactor); }

private:
	std::vector<IReactorPtr> m_arrReactor;
};
#define PxDocumentReactorOpr PxDocumentReactor::instance()

#define assertWriteEnabled(flag) PxDocumentReactorOpr.notifyEvent(this, flag)
#define assertWriteEnabled2(item, flag) PxDocumentReactorOpr.notifyEvent(item, flag)



// 业务响应器，如：一个图形的位置移动后，与之相碰撞的其它图形要做一些处理（避让、拉伸...）
class ComponentReactor : public IReactor
{
public:
	void notify(PxShape* pItem, int flag) override;
};


#endif // !COMPONENT_REACTOR_H