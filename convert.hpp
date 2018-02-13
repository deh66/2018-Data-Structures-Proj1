/****************************************
*	Daniel Hollo						*
*	deh66@zips.uakron.edu				*
*	2/7/2018							*
*	0428_316p1.h - header file			*
****************************************/

#ifndef CONVERT_HPP
#define CONVERT_HPP

#include <stack>
#include <list>

class Convert {
private:
	std::stack<char> opStack;
	std::stack<int> intStack;
	std::string outputString;
	std::string tokenString;

	std::list<std::string> tokList;

	//std::string operands;
	//std::string operators;

public:
	Convert();
	~Convert();

	void convertExpression(char*);
	void evaluateExpression(char*);

	int initVariable(char);
	int precedence(char);
	bool testInput(char*);
	//TEST
	//void testInputParse(char*);

};

Convert::Convert(){}

Convert::~Convert() {}


// Converts input only
void Convert::convertExpression(char* input)
{

	for (int i = 0; input[i] != '#'; i++)
	{
		// If scanned character is an operand
		if (isalnum(input[i]))
		{
			// If it's a character
			if (isalpha(input[i]))
			{
				// Append to output string
				outputString += input[i];
			}
			// If its a number
			else
			{
				//Put the number in a string
				std::string tmp = "";
				tmp += input[i];

				// Iterate until the next character is no longer still part of the number
				while (isdigit(input[i+1]))
				{
					i++;
					// Add number character to string
					tmp += input[i];
				}
				/// Add token to list
				//tokList.push_front(tmp);
				outputString += tmp;
			}
		}
		// If scanned character is a '('
		else if (input[i] == '(')
		{
			// Push it to the stack
			opStack.push('(');
		}
		// If scanned character is a ')'
		else if (input[i] == ')')
		{
			// pop from stack onto output string until an '(' is encountered
			while (opStack.top() != '(' && !opStack.empty())
			{
				char c = opStack.top();
				opStack.pop();
				outputString += c;
			}
			if (opStack.top() == '(')
			{
				char c = opStack.top();
				opStack.pop();
			}
		}
		// If an operator is scanned
		else
		{
			// until we find an operator with a lower precedence than the scanned operator
			while (!opStack.empty() && precedence(input[i]) <= precedence(opStack.top()))
			{
				// pop from the stack
				char c = opStack.top();
				opStack.pop();
				outputString += c;
			}
			// Then push the operator to the stack
			opStack.push(input[i]);
		}
	}

	// pop the rest of the stack
	while (!opStack.empty())
	{
		char c = opStack.top();
		opStack.pop();
		outputString += c;
	}

	// Output result to console
	std::cout << "\nInfix representation: " << outputString << std::endl;

}

// Evaluates input
void Convert::evaluateExpression(char* input)
{

	for (int i = 0; input[i] != '#'; i++)
	{
		// If scanned character is an operand
		if (isalnum(input[i]))
		{
			// If operand is a number
			if (isdigit(input[i]))
			{
				//Put the number in a string
				std::string tmp = "";
				tmp += input[i];

				// Iterate until the next character is no longer still part of the number
				while (isdigit(input[i + 1]))
				{
					i++;
					// Add number character to string
					tmp += input[i];
				}
				/// Add token to list
				tokList.push_back(tmp);
				//outputString += tmp;
			}
			// If operand is letter
			else
			{
				// Ask user to input value for variable
				int varValue = 0;
				varValue = initVariable(input[i]);
				
				// then append the value to outputstring
				//outputString += std::to_string(varValue);
				tokList.push_back(std::to_string(varValue));
			}
		}
		// If scanned character is a '('
		else if (input[i] == '(')
		{
			// Push it to the stack
			opStack.push('(');
		}
		// If scanned character is a ')'
		else if (input[i] == ')')
		{
			// pop from stack onto output string until an '(' is encountered
			while (opStack.top() != '(' && !opStack.empty())
			{
				char c = opStack.top();
				opStack.pop();
				//outputString += c;

				std::string tmp = "";
				tmp += c;
				tokList.push_back(tmp);
			}
			if (opStack.top() == '(')
			{
				char c = opStack.top();
				opStack.pop();
			}
		}
		// If an operator is scanned
		else
		{
			// until we find an operator with a lower precedence than the scanned operator
			while (!opStack.empty() && precedence(input[i]) <= precedence(opStack.top()))
			{
				// pop from the stack
				char c = opStack.top();
				opStack.pop();
				//outputString += c;

				std::string tmp = "";
				tmp += c;
				tokList.push_back(tmp);
			}
			// Then push the operator to the stack
			opStack.push(input[i]);
		}
	}

	// pop the rest of the stack
	while (!opStack.empty())
	{
		char c = opStack.top();
		opStack.pop();
		//outputString += c;

		std::string tmp = "";
		tmp += c;
		tokList.push_back(tmp);
	}

	// Test code
	/*
	std::cout << outputString << std::endl;
	std::cout << std::endl;
	for (std::list<std::string>::iterator it = tokList.begin(); it != tokList.end(); it++)
	{
		std::cout << ' ' << *it;
	}
	*/

	// Calculate answer
	std::string comp = outputString;
	outputString = "";

	while (!tokList.empty())
	{
		std::string temp = tokList.front();
		tokList.pop_front();

		if (isdigit(temp[0]))
		{
			std::string::size_type sz;
			intStack.push(std::stoi(temp, &sz));
		}

		else
		{
			// Pop 2 integers from stack, perform operation, then push result to stack
			int op1 = intStack.top();
			intStack.pop();
			int op2 = intStack.top();
			intStack.pop();
			char op = temp[0];

			int ans;
			switch (op) {
			case '+':
				ans = op2 + op1;
				break;
			case '-':
				ans = op2 - op1;
				break;
			case '*':
				ans = op2 * op1;
				break;
			case '/':
				ans = op2 / op1;
				break;
			}
			intStack.push(ans);

		}

	}

	// All Characters have been scanned, pop answer from stack

	outputString = std::to_string(intStack.top());
	intStack.pop();

	std::cout << "\nResult of computation: " << outputString << std::endl;

}

// Asks user for value of Variabe and returns the value entered
int Convert::initVariable(char Variable)
{
	int value;

	std::cout << "Please enter value for " << Variable << ": ";

	std::cin >> value;

	return value;
}

//Function to return precedence of operators
int Convert::precedence(char c)
{
	if (c == '^')
		return 3;
	else if (c == '*' || c == '/')
		return 2;
	else if (c == '+' || c == '-')
		return 1;
	else
		return -1;
}

// Test user input for delim. character
bool Convert::testInput(char* input)
{
		for (int i = 0; i < 255; i++)
		{
			// Iterate through input looking for '#'
			if (input[i] == '#')
				return true;
		}

		std::cout << "\nError: Expression not terminated with a # character.\n";
		return false;
}

/*
////TEST CODE
////test
void Convert::testInputParse(char* input)
{

	// while the current character is not the deliminator
	for (int i = 0; input[i] != '#'; i++)
	{
 		if (isdigit(input[i]))
		{
			// If input[i] is a number
			//operands.append(input[i]);
			operands += input[i];
		}
		else if (isalpha(input[i]))
		{
			//If input[i] is a letter
			
			// insert function call here to have user specify value for variable
			int varValue = 0;
			varValue = initVariable(input[i]);

			operands += input[i];
			operands += "[";
			operands += std::to_string(varValue);
			operands += "]";
		}
		else if (input[i] == ' ')
		{
			// ignore and do nothing
		}
		else
		{
			// VERY bad case to test for operators

			operators += input[i];
		}

	}

	std::cout << "Operands: " << operands << std::endl;
	std::cout << "Operators: " << operators << std::endl;
}
*/
#endif // !0428_316P1_H
