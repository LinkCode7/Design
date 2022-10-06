#pragma once
#include <map>
#include <vector>
#include <iostream>

// 享元模式
namespace FlyweightPattern
{
	void Entry();

	/*
	* Flyweight
	* declares an interface through which flyweights can receive
	* and act on extrinsic state
	*/
	class Flyweight
	{
	public:
		virtual ~Flyweight() {}
		virtual void operation() = 0;
	};

	/*
	* UnsharedConcreteFlyweight
	* not all subclasses need to be shared
	*/
	class UnsharedConcreteFlyweight : public Flyweight
	{
	public:
		UnsharedConcreteFlyweight(const int intrinsic_state) :state(intrinsic_state) {}
		~UnsharedConcreteFlyweight() {}

		void operation()
		{
			std::cout << "Unshared Flyweight with state " << state << std::endl;
		}

	private:
		int state;
	};

	/*
	* ConcreteFlyweight
	* implements the Flyweight interface and adds storage
	* for intrinsic state
	*/
	class ConcreteFlyweight : public Flyweight
	{
	public:
		ConcreteFlyweight(const int all_state) :state(all_state) {}
		~ConcreteFlyweight() {}

		void operation()
		{
			std::cout << "Concrete Flyweight with state " << state << std::endl;
		}

	private:
		int state;
	};

	/*
	* FlyweightFactory
	* creates and manages flyweight objects and ensures
	* that flyweights are shared properly
	*/
	class FlyweightFactory
	{
	public:
		~FlyweightFactory()
		{
			for (auto& it : flies)
				delete it.second;
			flies.clear();
		}

		Flyweight* getFlyweight(const int key)
		{
			if (flies.find(key) != flies.end())
				return flies[key];

			Flyweight* fly = new ConcreteFlyweight(key);
			flies.insert(std::pair<int, Flyweight*>(key, fly));
			return fly;
		}

	private:
		std::map<int, Flyweight*> flies;
	};











	// 文本编辑器的内存占用问题，每个文字都要保存字体、大小、颜色等信息

	class Font
	{
	public:
		bool equal(const Font& oth) const { return true; } // 省略实现代码
	};

	// 文字类（每个文字类包含独立的文字信息）
	class Character
	{
	private:
		char _c;
		Font _font;
		int _size;
		int _colorRGB;
	public:
		Character(char c, Font& font, int size, int colorRGB) :_c(c), _font(font), _size(size), _colorRGB(colorRGB)
		{
		}
	};

	// 编辑器类
	class Editor
	{
	private:
		std::vector<Character*> chars;

	public:
		void appendCharacter(char c, Font& font, int size, int colorRGB) {
			Character* character = new Character(c, font, size, colorRGB);
			chars.push_back(character);
		}
	};



	// 文字信息基本是相同的，用享元模式优化：
	class CharacterStyle
	{
	private:
		Font _font;
		int _size;
		int _colorRGB;

	public:
		CharacterStyle(Font& font, int size, int colorRGB) :_font(font), _size(size), _colorRGB(colorRGB) {}

	public:
		bool equals(CharacterStyle& oth)const
		{
			return (_font.equal(oth._font) && _size == oth._size && _colorRGB == oth._colorRGB);
		}
	};

	// 享元工厂类
	class CharacterStyleFactory
	{
	private:
		static std::vector<CharacterStyle> _styles;

	public:
		static CharacterStyle getStyle(Font font, int size, int colorRGB)
		{
			CharacterStyle newStyle(font, size, colorRGB);
			for (const auto& style : _styles)
			{
				if (style.equals(newStyle))
					return style;
			}
			_styles.push_back(newStyle);
			return newStyle;
		}
	};

	class Character2
	{
	private:
		char _c;
		CharacterStyle _style;
	public:
		Character2(char c, CharacterStyle style) : _c(c), _style(style) {}
	};

	class Editor2
	{
	private:
		std::vector<Character2> chars;

	public:
		void appendCharacter(char c, Font font, int size, int colorRGB)
		{
			Character2 character(c, CharacterStyleFactory::getStyle(font, size, colorRGB));
			chars.push_back(character);
		}
	};

} // namespace FlyweightPattern
