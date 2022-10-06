#include "Visitor.h"
#include <string>
#include <vector>


namespace VisitorPattern
{
	void Entry()
	{
		ConcreteElementA elementA;
		ConcreteElementB elementB;

		ConcreteVisitor1 visitor1;
		ConcreteVisitor2 visitor2;

		elementA.accept(visitor1);
		elementA.accept(visitor2);

		elementB.accept(visitor1);
		elementB.accept(visitor2);

		/////////////////////////////////////////////
		VisitorEvolve1::Evolve(std::string());
		VisitorEvolve2::Evolve(std::string());
		VisitorEvolve3::Evolve(std::string());
		VisitorEvolve4::Evolve(std::string());

		VisitorEvolve::Evolve(std::string());

		SingleDispatchLanguage::TestSingleDispatch();
	}

} // namespace VisitorPattern





namespace VisitorEvolve1
{
	void Evolve(const std::string& args)
	{
		std::vector<ResourceFile*> resourceFiles = listAllResourceFiles(args);
		for (ResourceFile* resourceFile : resourceFiles)
		{
			resourceFile->extract2txt();
		}

		for (auto& item : resourceFiles)
			delete item;
	}

	std::vector<ResourceFile*> listAllResourceFiles(const std::string& args)
	{
		std::vector<ResourceFile*> resourceFiles;
		//...根据后缀(pdf/ppt/word)由工厂方法创建不同的类对象(PdfFile/PPTFile/WordFile)
		resourceFiles.push_back(new PdfFile("a.pdf"));
		resourceFiles.push_back(new WordFile("b.word"));
		resourceFiles.push_back(new PPTFile("c.ppt"));
		return resourceFiles;
	}

} // namespace VisitorEvolve1




namespace VisitorEvolve2
{
	void Evolve(const std::string& args)
	{
		//Extractor extractor;

		std::vector<ResourceFile*> resourceFiles = listAllResourceFiles(args);
		for (ResourceFile* resourceFile : resourceFiles)
		{
			// 无构造函数可以接受源类型，或构造函数重载决策不明确
			// 支持双分派（Double Dispatch）的语言可以直接根据resourceFile的具体类型确定调用哪个函数
			//extractor.extract2txt(resourceFile);
		}

		for (auto& item : resourceFiles)
			delete item;
	}

	std::vector<ResourceFile*> listAllResourceFiles(const std::string& args)
	{
		std::vector<ResourceFile*> resourceFiles;
		//...根据后缀(pdf/ppt/word)由工厂方法创建不同的类对象(PdfFile/PPTFile/WordFile)
		resourceFiles.push_back(new PdfFile("a.pdf"));
		resourceFiles.push_back(new WordFile("b.word"));
		resourceFiles.push_back(new PPTFile("c.ppt"));
		return resourceFiles;
	}

} // namespace VisitorEvolve2





namespace VisitorEvolve3
{
	void Evolve(const std::string& args)
	{
		Extractor extractor;

		std::vector<ResourceFile*> resourceFiles = listAllResourceFiles(args);
		for (ResourceFile* resourceFile : resourceFiles)
		{
			// key
			resourceFile->accept(&extractor);
		}

		for (auto& item : resourceFiles)
			delete item;
	}

	std::vector<ResourceFile*> listAllResourceFiles(const std::string& args)
	{
		std::vector<ResourceFile*> resourceFiles;
		//...根据后缀(pdf/ppt/word)由工厂方法创建不同的类对象(PdfFile/PPTFile/WordFile)
		resourceFiles.push_back(new PdfFile("a.pdf"));
		resourceFiles.push_back(new WordFile("b.word"));
		resourceFiles.push_back(new PPTFile("c.ppt"));
		return resourceFiles;
	}

	void PdfFile::accept(Extractor* extractor)
	{
		extractor->extract2txt(this);
	}
	void PPTFile::accept(Extractor* extractor)
	{
		extractor->extract2txt(this);
	}
	void WordFile::accept(Extractor* extractor)
	{
		extractor->extract2txt(this);
	}

} // namespace VisitorEvolve3







namespace VisitorEvolve4
{
	void Evolve(const std::string& args)
	{
#ifndef _USE_VISITOR_OBJECT_
		std::vector<ResourceFile*> resourceFiles = listAllResourceFiles(args);

		Visitor* extractor = new Extractor;
		for (ResourceFile* resourceFile : resourceFiles) {
			resourceFile->accept(extractor);
		}

		Visitor* compressor = new Compressor;
		for (ResourceFile* resourceFile : resourceFiles) {
			resourceFile->accept(compressor);
		}

		delete extractor;
		delete compressor;
		for (auto& item : resourceFiles)
			delete item;
#else
		std::vector<ResourceFile*> resourceFiles = listAllResourceFiles(args);

		Extractor extractor;
		for (ResourceFile* resourceFile : resourceFiles)
			resourceFile->accept(&extractor);

		Compressor compressor;
		for (ResourceFile* resourceFile : resourceFiles)
			resourceFile->accept(&compressor);

		for (auto& item : resourceFiles)
			delete item;
#endif // _USE_VISITOR_OBJECT_
	}

	std::vector<ResourceFile*> listAllResourceFiles(const std::string& args)
	{
		std::vector<ResourceFile*> resourceFiles;
		//...根据后缀(pdf/ppt/word)由工厂方法创建不同的类对象(PdfFile/PPTFile/WordFile)
		resourceFiles.push_back(new PdfFile("a.pdf"));
		resourceFiles.push_back(new WordFile("b.word"));
		resourceFiles.push_back(new PPTFile("c.ppt"));
		return resourceFiles;
	}

	void PdfFile::accept(Visitor* visitor)
	{
		visitor->visit(this);
	}
	void PPTFile::accept(Visitor* visitor)
	{
		visitor->visit(this);
	}
	void WordFile::accept(Visitor* visitor)
	{
		visitor->visit(this);
	}

} // namespace VisitorEvolve4




namespace VisitorEvolve
{
	void Evolve(const std::string& args)
	{
		ExtractorFactory factory;

		std::vector<ResourceFile*> resourceFiles = listAllResourceFiles(args);
		for (ResourceFile* resourceFile : resourceFiles)
		{
			Extractor* extractor = factory.getExtractor(resourceFile->getType());
			extractor->extract2txt(resourceFile);
		}

		for (auto& item : resourceFiles)
			delete item;
	}

	std::vector<ResourceFile*> listAllResourceFiles(const std::string& resourceDirectory)
	{
		std::vector<ResourceFile*> resourceFiles;
		//...根据后缀(pdf/ppt/word)由工厂方法创建不同的类对象(PdfFile/PPTFile/WordFile)
		resourceFiles.push_back(new PdfFile("a.pdf"));
		resourceFiles.push_back(new WordFile("b.word"));
		resourceFiles.push_back(new PPTFile("c.ppt"));
		return resourceFiles;
	}

} // namespace VisitorEvolve

namespace SingleDispatchLanguage
{
	void TestSingleDispatch()
	{
		SingleDispatchClass demo;
		ParentClass* pClass = new ChildClass();
		demo.polymorphismFunction(pClass); // 执行哪个对象的方法，由对象的实际类型决定
		demo.overloadFunction(pClass); // 执行对象的哪个方法，由参数对象的声明类型决定
		delete pClass;
	}

} // namespace SingleDispatchLanguage

