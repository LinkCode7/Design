#include <iostream>
#include "Interpreter.h"



namespace InterpreterPattern
{
	void Entry()
	{
		// An example of very simple expression tree
		// that corresponds to expression (A AND B)
		AbstractExpression* A = new TerminalExpression("A");
		AbstractExpression* B = new TerminalExpression("B");
		AbstractExpression* exp = new NonterminalExpression(A, B);

		Context context;
		context.set("A", true);
		context.set("B", false);

		std::cout << context.get("A") << " AND " << context.get("B");
		std::cout << " = " << exp->interpret(&context) << std::endl;

		delete exp;
	}

} // namespace InterpreterPattern