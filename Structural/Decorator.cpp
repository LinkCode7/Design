#include <string>
#include "Decorator.h"

using namespace std;



namespace DecoratorPattern
{
	void Entry()
	{
		Component* pComponent = new ConcreteComponent();
		Decorator* pDecorator = new ConcreteDecorator(pComponent);

		pDecorator->Operation();

		//(pComponent);
		(pDecorator);
	}

} // namespace DecoratorPattern





// 以下是装饰器模式在java IO类库中的应用
// typedef unsigned char byte;

class InputStream
{
protected:
	InputStream() {}
public:
	virtual ~InputStream() {}

	//  throws IOException
	virtual int read() { return -1; }
	virtual int read(byte b[]) { return -1; }
	virtual int read(byte b[], int off, int len) { return -1; }
	virtual long skip(long n) { return -1; }
	virtual int available() { return -1; }
	virtual void close() { /*default implement*/ }

	/*synchronized*/ virtual void mark(int readlimit) { /*default implement*/ }
	/*synchronized*/ virtual void reset() { /*default implement*/ }
	virtual bool markSupported() { return false; }
};

// 默认Wrapper类、缺省Wrapper类（避免重写全部接口）
class FilterInputStream : public InputStream
{
protected:
	InputStream* _in; // 组合 + 继承
public:
	FilterInputStream() {}
	FilterInputStream(InputStream* in) :_in(in) {}
	virtual ~FilterInputStream() { delete _in; }

	virtual int read() { return _in->read(); }
	virtual int read(byte b[]) { return read(b, 0, sizeof(byte)); }
	virtual int read(byte b[], int off, int len) { return _in->read(b, off, len); }

	virtual long skip(long n) { return _in->skip(n); }
	virtual int available() { return _in->available(); }
	virtual void close() { _in->close(); }

	virtual /*synchronized*/ void mark(int readlimit) { _in->mark(readlimit); }
	virtual /*synchronized*/ void reset() { _in->reset(); }
	virtual bool markSupported() { return _in->markSupported(); }
};


class BufferedInputStream : public FilterInputStream
{
public:
	BufferedInputStream(const std::string& str) {}
	BufferedInputStream(InputStream* in) :FilterInputStream(in) {}

	//...实现基于缓存的读数据接口...  
};
class DataInputStream : public FilterInputStream
{
public:
	DataInputStream(const std::string& str) {}
	DataInputStream(InputStream* in) :FilterInputStream(in) {}

	//...实现读取基本类型数据的接口
};
class FileInputStream : public FilterInputStream
{
public:
	FileInputStream(const std::string& str) {}
	FileInputStream(InputStream* in) :FilterInputStream(in) {}

	//...实现读取文件数据的接口

	int read()override
	{
		// 这里可以扩展功能
		int result = _in->read();
		// 这里可以扩展功能
		return result;
	}
};

void HowToUse()
{
	// 装饰器类和原始类继承同样的父类，这样我们可以对原始类“嵌套”多个装饰器类
	// 让它既支持按照基本数据类型来读取数据，又支持缓存读取
	InputStream* in = new DataInputStream("/user/test.txt");
	InputStream* bin = new BufferedInputStream(in);

	byte data[128] = {};// new byte[128];
	while (bin->read(data) != -1) {
		//...
	}
	delete bin;
}
/*
如果 InputStream 只有一个子类 FileInputStream 的话，那我们在 FileInputStream 基础之上，
再设计一个孙子类 BufferedFileInputStream，也算是可以接受的，毕竟继承结构还算简单。
但实际上，继承 InputStream 的子类有很多。我们需要给每一个 InputStream 的子类，再继续派生支持缓存读取的子类
场景：给原先不支持缓存的功能增加缓存，提升特定场景下的效率
*/
