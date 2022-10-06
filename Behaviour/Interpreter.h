#pragma once
#include <map>

/*
解释器模式
将语法解析的工作拆分到各个小类中，以此来避免大而全的解析类。
一般的做法是，将语法规则拆分一些小的独立的单元，然后对每个单元进行解析，最终合并为对整个语法规则的解析
*/
namespace InterpreterPattern
{
	/*
	* Context
	* contains information that's global to the interpreter
	*/
	class Context
	{
	public:
		void set(const std::string& var, const bool value)
		{
			vars.insert(std::pair<std::string, bool>(var, value));
		}

		bool get(const std::string& exp)
		{
			return vars[exp];
		}

	private:
		std::map<std::string, bool> vars;
	};

	/*
	 * Abstract Expression
	 * declares an abstract Interpret operation that is common to all nodes
	 * in the abstract syntax tree
	 */
	class AbstractExpression
	{
	public:
		virtual ~AbstractExpression() {}

		virtual bool interpret(Context* const)
		{
			return false;
		}
	};

	/*
	 * Terminal Expression
	 * implements an Interpret operation associated with terminal symbols
	 * in the grammar (an instance is required for every terminal symbol
	 * in a sentence)
	 */
	class TerminalExpression : public AbstractExpression
	{
	public:
		TerminalExpression(const std::string& val) : value(val) {}

		~TerminalExpression() {}

		bool interpret(Context* const context)override
		{
			return context->get(value);
		}

	private:
		std::string value;
	};

	/*
	 * Nonterminal Expression
	 * implements an Interpret operation for nonterminal symbols
	 * in the grammar (one such class is required for every rule in the grammar)
	 */
	class NonterminalExpression : public AbstractExpression
	{
	public:
		NonterminalExpression(AbstractExpression* left, AbstractExpression* right) :
			lop(left), rop(right) {}

		~NonterminalExpression()
		{
			delete lop;
			delete rop;
		}

		bool interpret(Context* const context)override
		{
			return lop->interpret(context) && rop->interpret(context);
		}

	private:
		AbstractExpression* lop;
		AbstractExpression* rop;
	};

} // namespace InterpreterPattern
