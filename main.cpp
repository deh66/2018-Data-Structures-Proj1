/****************************************
*	Daniel Hollo						*
*	deh66@zips.uakron.edu				*
*	2/7/2018							*
*	0428_316p1.cpp - main source file	*
****************************************/

#include <iostream>
#include <string>

#include "convert.hpp"



int main() {
	char userInput[256];
	char menuInput;

	// Initial User Prompt
	std::cout << "Infix to Postfix converter - Daniel Hollo\nPlease enter an option:\n" <<
		"1) Convert Infix to Postfix (returns expression)\n2) Evaluate Infix Expression (returns value)\n3) Exit\n";
	std::cin >> menuInput;

	// While not exit condition
	while (menuInput != '3')
	{	
		if (menuInput == '1')
		{
			std::cout << "Infix Conversion:\nEnter an infix expression terminated by a #: ";
			std::cin.ignore();
			std::cin.getline(userInput, 256, '\n');

			//Create new convert object
			Convert conv;

			//conv.testInputParse(userInput);
			if (conv.testInput(userInput))
				conv.convertExpression(userInput);
		}
		else if (menuInput == '2')
		{
			std::cout << "Infix Evaluation:\nEnter an infix expression terminated by a #: ";
			std::cin.ignore();
			std::cin.getline(userInput, 256, '\n');

			//Create new convert object
			Convert conv;

			//conv.testInputParse(userInput);
			if(conv.testInput(userInput))
				conv.evaluateExpression(userInput);

		}
		else
		{
			std::cout << "Invalid menue input, enter 1,2 or 3.\n";
		}

		std::cout << "\n\nInfix to Postfix converter - Daniel Hollo\nPlease enter an option:\n" <<
			"1) Convert Infix to Postfix (returns expression)\n2) Evaluate Infix Expression (returns value)\n3) Exit\n";
		std::cin >> menuInput;
		
	}

	return 0;
}