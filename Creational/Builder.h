#pragma once
#include <string>
#include <iostream>

// 创建者模式
// 创建大的复杂的对象，通过相同的创建过程可以获得不同的结果对象，
// Builder模式强调一步步创建对象，一般不直接返回对象


namespace BuilderPattern
{
	void Entry();

	class Product;

	class Builder
	{
	public:
		virtual ~Builder() {}
		virtual void BuildPartA(const std::string& buildPara) = 0;
		virtual void BuildPartB(const std::string& buildPara) = 0;
		virtual void BuildPartC(const std::string& buildPara) = 0;

		virtual Product* GetProduct() = 0;
	protected:
		Builder() {}
	};

	class Product
	{
	public:
		Product()
		{
			ProducePart();
			std::cout << "return a product" << std::endl;
		}
		~Product();
		void ProducePart() { std::cout << "build part of product.." << std::endl; }
	};

	class Director
	{
	public:
		Director(Builder* bld) :_bld(bld) {}
		~Director() { delete _bld; }

		void Construct()
		{
			_bld->BuildPartA("user-defined");
			_bld->BuildPartB("user-defined");
			_bld->BuildPartC("user-defined");
		}
	private:
		Builder* _bld;
	};

	class ConcreteBuilder :public Builder
	{
	public:
		ConcreteBuilder() {}
		~ConcreteBuilder() {}
		void BuildPartA(const std::string& buildPara) { std::cout << "Step1:Build PartA..." << buildPara << std::endl; }
		void BuildPartB(const std::string& buildPara) { std::cout << "Step1:Build PartB..." << buildPara << std::endl; }
		void BuildPartC(const std::string& buildPara) { std::cout << "Step1:Build PartC..." << buildPara << std::endl; }

		Product* GetProduct() override
		{
			BuildPartA("pre-defined");
			BuildPartB("pre-defined");
			BuildPartC("pre-defined");
			return new Product();
		}
	};

	//class ProductPart
	//{
	//public:
	//	ProductPart() {/*cout<<"build productpart.."<<endl;*/}
	//	~ProductPart() {}
	//	ProductPart* BuildPart() { return new ProductPart; }
	//};










	// 类的创建过程需要做属性检验等，根据不同的参数创建类
	class ResourcePoolConfig
	{
		std::string name;
		int maxTotal;
		int maxIdle;
		int minIdle;
	public:
		class Builder;
		ResourcePoolConfig(Builder* builder)
		{
			this->name = builder->name;
			this->maxTotal = builder->maxTotal;
			this->maxIdle = builder->maxIdle;
			this->minIdle = builder->minIdle;
		}
		//...省略getter方法...

		// 我们将Builder类设计成了ResourcePoolConfig的内部类。
		// 也可以将Builder类设计成独立的非内部类ResourcePoolConfigBuilder。
		class Builder
		{
		public:
			const int DEFAULT_MAX_TOTAL = 8;
			const int DEFAULT_MAX_IDLE = 8;
			const int DEFAULT_MIN_IDLE = 0;

			std::string name;
			int maxTotal = DEFAULT_MAX_TOTAL;
			int maxIdle = DEFAULT_MAX_IDLE;
			int minIdle = DEFAULT_MIN_IDLE;

			bool isBlank(const std::string& name) { return false; } // mock
			ResourcePoolConfig* build()
			{
				// 校验逻辑放到这里来做，包括必填项校验、依赖关系校验、约束条件校验等
				if (isBlank(name)) {
					//throw new IllegalArgumentException("...");
				}
				if (maxIdle > maxTotal) {
					//throw new IllegalArgumentException("...");
				}
				if (minIdle > maxTotal || minIdle > maxIdle) {
					//throw new IllegalArgumentException("...");
				}

				return new ResourcePoolConfig(this);
			}

			Builder& setName(const std::string& name) {
				if (isBlank(name)) {
					//throw new IllegalArgumentException("...");
				}
				this->name = name;
				return *this;
			}

			Builder& setMaxTotal(int maxTotal) {
				if (maxTotal <= 0) {
					//throw new IllegalArgumentException("...");
				}
				this->maxTotal = maxTotal;
				return *this;
			}

			Builder& setMaxIdle(int maxIdle) {
				if (maxIdle < 0) {
					//throw new IllegalArgumentException("...");
				}
				this->maxIdle = maxIdle;
				return *this;
			}

			Builder& setMinIdle(int minIdle) {
				if (minIdle < 0) {
					//throw new IllegalArgumentException("...");
				}
				this->minIdle = minIdle;
				return *this;
			}
		};
	};

} // namespace BuilderPattern
