#pragma once
#include <map>
#include <string>
#include <vector>
#include <iostream>

// 访问者模式

namespace VisitorPattern
{
	void Entry();

	class Element;
	class ConcreteElementA;
	class ConcreteElementB;

	/*
	 * Visitor
	 * declares a Visit operation for each class of ConcreteElement
	 * in the object structure
	 */
	class Visitor
	{
	public:
		virtual ~Visitor() {}

		virtual void visitElementA(ConcreteElementA* const element) = 0;
		virtual void visitElementB(ConcreteElementB* const element) = 0;
	};

	/*
	 * Concrete Visitors
	 * implement each operation declared by Visitor, which implement
	 * a fragment of the algorithm defined for the corresponding class
	 * of object in the structure
	 */
	class ConcreteVisitor1 : public Visitor
	{
	public:
		~ConcreteVisitor1() {}

		void visitElementA(ConcreteElementA* const)
		{
			std::cout << "Concrete Visitor 1: Element A visited." << std::endl;
		}

		void visitElementB(ConcreteElementB* const)
		{
			std::cout << "Concrete Visitor 1: Element B visited." << std::endl;
		}
	};

	class ConcreteVisitor2 : public Visitor
	{
	public:
		~ConcreteVisitor2() {}

		void visitElementA(ConcreteElementA* const)
		{
			std::cout << "Concrete Visitor 2: Element A visited." << std::endl;
		}

		void visitElementB(ConcreteElementB* const)
		{
			std::cout << "Concrete Visitor 2: Element B visited." << std::endl;
		}
	};

	/*
	 * Element
	 * defines an accept operation that takes a visitor as an argument
	 */
	class Element
	{
	public:
		virtual ~Element() {}
		virtual void accept(Visitor& visitor) = 0;
	};

	/*
	 * Concrete Elements
	 * implement an accept operation that takes a visitor as an argument
	 */
	class ConcreteElementA : public Element
	{
	public:
		~ConcreteElementA() {}

		void accept(Visitor& visitor)
		{
			visitor.visitElementA(this);
		}
	};

	class ConcreteElementB : public Element
	{
	public:
		~ConcreteElementB() {}

		void accept(Visitor& visitor)
		{
			visitor.visitElementB(this);
		}
	};

} // namespace VisitorPattern










/*
情景一：
假设我们从网站上爬取了很多资源文件，它们的格式有三种：PDF、PPT、Word。
现在要开发一个工具来处理这批资源文件：把这些资源文件中的文本内容抽取出来放到 txt 文件中
*/
namespace VisitorEvolve1
{
	void Evolve(const std::string& args);

	class ResourceFile
	{
	protected:
		std::string _filePath;

	public:
		ResourceFile(const std::string& filePath) :_filePath(filePath) {}
		virtual ~ResourceFile() {}

		virtual void extract2txt() = 0;
	};

	class PPTFile : public ResourceFile
	{
	public:
		PPTFile(const std::string& filePath) :ResourceFile(filePath) {}

		void extract2txt()override
		{
			//...省略一大坨从PPT中抽取文本的代码...
			//...将抽取出来的文本保存在跟_filePath同名的.txt文件中...
			std::cout << "Extract PPT." << std::endl;
		}
	};

	class PdfFile : public ResourceFile
	{
	public:
		PdfFile(const std::string& filePath) :ResourceFile(filePath) {}

		void extract2txt()override
		{
			//...
			std::cout << "Extract PDF." << std::endl;
		}
	};

	class WordFile : public ResourceFile
	{
	public:
		WordFile(const std::string& filePath) :ResourceFile(filePath) {}

		void extract2txt()override
		{
			//...
			std::cout << "Extract WORD." << std::endl;
		}
	};

	std::vector<ResourceFile*> listAllResourceFiles(const std::string& args);
} // namespace VisitorEvolve1


/*
情景二：
如果工具的功能不停地扩展，不仅要能抽取文本内容，还要支持压缩、提取文件元信息（文件名、大小、更新时间等等）构建索引等一系列的功能，
那如果我们继续按照上面的实现思路，就会存在这样几个问题：违背开闭原则，添加一个新的功能，所有类的代码都要修改；
虽然功能增多，每个类的代码都不断膨胀，可读性和可维护性都变差了；
把所有比较上层的业务逻辑都耦合到 PdfFile、PPTFile、WordFile 类中，导致这些类的职责不够单一，变成了大杂烩。

针对上面的问题，我们常用的解决方法就是拆分解耦，把业务操作跟具体的数据结构解耦，设计成独立的类。
*/
namespace VisitorEvolve2
{
	void Evolve(const std::string& args);

	class ResourceFile
	{
	protected:
		std::string _filePath;
	public:
		ResourceFile(const std::string& filePath) : _filePath(filePath) {}
	};

	class PdfFile : public ResourceFile
	{
	public:
		PdfFile(const std::string& filePath) : ResourceFile(filePath) {}
	};
	class PPTFile : public ResourceFile
	{
	public:
		PPTFile(const std::string& filePath) : ResourceFile(filePath) {}
	};
	class WordFile : public ResourceFile
	{
	public:
		WordFile(const std::string& filePath) : ResourceFile(filePath) {}
	};

	class Extractor
	{
	public:
		void extract2txt(PPTFile* pptFile) {
			//...
			std::cout << "Extract PPT." << std::endl;
		}

		void extract2txt(PdfFile* pdfFile) {
			//...
			std::cout << "Extract PDF." << std::endl;
		}

		void extract2txt(WordFile* wordFile) {
			//...
			std::cout << "Extract WORD." << std::endl;
		}
	};

	std::vector<ResourceFile*> listAllResourceFiles(const std::string& args);
} // namespace VisitorEvolve2


/*
解决：无法在编译期根据多态特性（动态绑定）确定调用哪个重载函数
*/
namespace VisitorEvolve3
{
	void Evolve(const std::string& args);

	class Extractor;

	class ResourceFile
	{
	protected:
		std::string _filePath;
	public:
		ResourceFile(const std::string& filePath) : _filePath(filePath) {}

		virtual void accept(Extractor* extractor) = 0;
	};

	class PdfFile : public ResourceFile
	{
	public:
		PdfFile(const std::string& filePath) : ResourceFile(filePath) {}

		void accept(Extractor* extractor)override;
	};
	class PPTFile : public ResourceFile
	{
	public:
		PPTFile(const std::string& filePath) : ResourceFile(filePath) {}

		void accept(Extractor* extractor)override;
	};
	class WordFile : public ResourceFile
	{
	public:
		WordFile(const std::string& filePath) : ResourceFile(filePath) {}

		void accept(Extractor* extractor)override;
	};

	class Extractor
	{
	public:
		void extract2txt(PPTFile* pptFile) {
			//...
			std::cout << "Extract PPT." << std::endl;
		}

		void extract2txt(PdfFile* pdfFile) {
			//...
			std::cout << "Extract PDF." << std::endl;
		}

		void extract2txt(WordFile* wordFile) {
			//...
			std::cout << "Extract WORD." << std::endl;
		}
	};

	std::vector<ResourceFile*> listAllResourceFiles(const std::string& args);

} // namespace VisitorEvolve3




/*
如果要继续添加新的功能，比如前面提到的压缩功能，根据不同的文件类型，使用不同的压缩算法来压缩资源文件，那我们该如何实现呢？
我们需要实现一个类似 Extractor 类的新类 Compressor 类，在其中定义三个重载函数，实现对不同类型资源文件的压缩。
除此之外，我们还要在每个资源文件类中定义新的 accept 重载函数

添加一个新的业务，还是需要修改每个资源文件类，违反了开闭原则。
针对这个问题，我们抽象出来一个 Visitor 接口，包含是三个命名非常通用的 visit() 重载函数，分别处理三种不同类型的资源文件。
具体做什么业务处理，由实现这个 Visitor 接口的具体的类来决定，比如 Extractor 负责抽取文本内容，Compressor 负责压缩。
当我们新添加一个业务功能的时候，资源文件类不需要做任何修改，只需要修改 ToolApplication 的代码就可以了
*/
namespace VisitorEvolve4
{
	void Evolve(const std::string& args);

	class Visitor;

	class ResourceFile
	{
	protected:
		std::string _filePath;
	public:
		ResourceFile(const std::string& filePath) : _filePath(filePath) {}
		virtual void accept(Visitor* vistor) = 0;
	};

	class PdfFile : public ResourceFile
	{
	public:
		PdfFile(const std::string& filePath) : ResourceFile(filePath) {}
		void accept(Visitor* visitor)override;
	};
	class PPTFile : public ResourceFile
	{
	public:
		PPTFile(const std::string& filePath) : ResourceFile(filePath) {}
		void accept(Visitor* visitor)override;
	};
	class WordFile : public ResourceFile
	{
	public:
		WordFile(const std::string& filePath) : ResourceFile(filePath) {}
		void accept(Visitor* visitor)override;
	};

	class Visitor
	{
	public:
		virtual void visit(PdfFile* pdfFile) = 0;
		virtual void visit(PPTFile* pdfFile) = 0;
		virtual void visit(WordFile* pdfFile) = 0;
	};

	// 抽取文件
	class Extractor : public Visitor
	{
	public:
		void visit(PPTFile* pptFile)override {
			//...
			std::cout << "Extract PPT." << std::endl;
		}

		void visit(PdfFile* pdfFile)override {
			//...
			std::cout << "Extract PDF." << std::endl;
		}

		void visit(WordFile* wordFile)override {
			//...
			std::cout << "Extract WORD." << std::endl;
		}
	};

	// 压缩文件
	class Compressor : public Visitor
	{
	public:
		void visit(PPTFile* pptFile)override {
			//...
			std::cout << "Compress PPT." << std::endl;
		}

		void visit(PdfFile* pdfFile)override {
			//...
			std::cout << "Compress PDF." << std::endl;
		}

		void visit(WordFile* wordFile)override {
			//...
			std::cout << "Compress WORD." << std::endl;
		}
	};

	std::vector<ResourceFile*> listAllResourceFiles(const std::string& args);

} // namespace VisitorEvolve4


// 类型判定，iterator catlog，萃取类型


// 策略模式 + 工厂模式
namespace VisitorEvolve
{
	void Evolve(const std::string& args);

	enum ResourceFileType
	{
		PDF,
		PPT,
		WORD,
	};

	class ResourceFile
	{
	protected:
		std::string _filePath;
	public:
		ResourceFile(const std::string& filePath) : _filePath(filePath) {}
		virtual ResourceFileType getType() = 0;
	};

	class PdfFile : public ResourceFile
	{
	public:
		PdfFile(const std::string& filePath) : ResourceFile(filePath) {}

		ResourceFileType getType()override { return PDF; }
	};
	class PPTFile : public ResourceFile
	{
	public:
		PPTFile(const std::string& filePath) : ResourceFile(filePath) {}

		ResourceFileType getType()override { return PPT; }
	};
	class WordFile : public ResourceFile
	{
	public:
		WordFile(const std::string& filePath) : ResourceFile(filePath) {}

		ResourceFileType getType()override { return WORD; }
	};



	class Extractor
	{
	public:
		virtual void extract2txt(ResourceFile* resourceFile) = 0;
	};

	class PdfExtractor : public Extractor
	{
	public:
		void extract2txt(ResourceFile* resourceFile)override
		{
			//...
		}
	};
	class PPTExtractor : public Extractor
	{
	public:
		void extract2txt(ResourceFile* resourceFile)override
		{
			//...
		}
	};
	class WordExtractor : public Extractor
	{
	public:
		void extract2txt(ResourceFile* resourceFile)override
		{
			//...
		}
	};

	class ExtractorFactory
	{
	private:
		std::map<ResourceFileType, Extractor*> extractors = { {PDF, new PdfExtractor},{PPT, new PPTExtractor},{WORD, new WordExtractor} };

	public:
		Extractor* getExtractor(ResourceFileType type)
		{
			std::map<ResourceFileType, Extractor*>::iterator it = extractors.find(type);
			if (it == extractors.end())
				throw new std::invalid_argument("not found type");
			return it->second;
		}

		~ExtractorFactory()
		{
			for (auto& it : extractors)
				delete it.second;
		}
	};

	std::vector<ResourceFile*> listAllResourceFiles(const std::string& resourceDirectory);

} // namespace VisitorEvolve



















// 单分派语言特性
namespace SingleDispatchLanguage
{
	void TestSingleDispatch();

	class ParentClass
	{
	public:
		virtual void f() {
			std::cout << "I am ParentClass's f()." << std::endl;
		}
	};
	class ChildClass :public ParentClass
	{
	public:
		void f()override {
			std::cout << "I am ChildClass's f()." << std::endl;
		}
	};

	class SingleDispatchClass
	{
	public:
		void polymorphismFunction(ParentClass* p) {
			p->f();
		}

		void overloadFunction(ParentClass* p) {
			std::cout << "I am overloadFunction(ParentClass p)." << std::endl;
			p->f();
		}

		void overloadFunction(ChildClass* c) {
			std::cout << "I am overloadFunction(ChildClass p)." << std::endl;
			c->f();
		}
	};

} // namespace SingleDispatchLanguage