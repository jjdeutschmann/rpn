//****************************************************************************************************
//
//     File: rpn.cpp
//     Author: Jennifer Deutschmann
//
//	   This program asks for a Reverse Polish Notation (Post-fix) expression and solves the
//	   equation using a stack, if valid.
//
//	   Other files needed:
//		 1. stack.h
//	
//****************************************************************************************************

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include "stack.h"

//****************************************************************************************************

bool processOperator ( Stack<int> & rpnExp, char oper );
void displayResult ( Stack<int> & rpnExp, bool valid );

//****************************************************************************************************

int main ()
{
	Stack<int> rpnExp;
	string exp;
	string token;
	int popVal1;
	int numExpressions;
	bool valid = true;

	cout << "How many RPN expressions do you want to evaluate? \n(use ';' as delimiter) ";
	cin >> numExpressions;
	cin.ignore();

	for ( int i = 0; i < numExpressions; i++ )
	{
		getline( cin, exp );
		stringstream ss( exp );

		while ( getline(ss, token, ' ') )
		{
			if ( token[0] != ';' )
				cout << token << " ";

			if ( token[0] == ';')
			{
				displayResult ( rpnExp, valid );
				rpnExp.pop( popVal1 );
				valid = true;
			}
			else if ( valid && isdigit(token[0]) )
			{
				rpnExp.push(atoi(token.c_str()));
			}
			else if ( valid && ispunct(token[0]) )
			{
				valid = processOperator ( rpnExp, token[0] );
			}
		}
	}

	return 0;
}

//****************************************************************************************************

bool processOperator ( Stack<int> & rpnExp, char opr )
{
	bool success = false;
	int result;
	int popVal1;
	int popVal2;

	if ( rpnExp.pop(popVal2) && rpnExp.pop(popVal1) )
	{
		switch ( opr )
		{
			case '+': 
				result = popVal2 + popVal1;
				break;
			case '-': 
				result = popVal2 - popVal1;
				break;
			case '*': 
				result = popVal2 * popVal1;
				break;
			case '/': 
				result = popVal2 / popVal1;
				break;
			default: 
				result = popVal2 % popVal1;
				break;
		}

		rpnExp.push(result);
		success = true;
	}

	return success;
}

//****************************************************************************************************

void displayResult ( Stack<int> & rpnExp, bool valid )
{
	int finalResult;

	if ( rpnExp.getSize() != 1 )
		valid = false;

	if ( rpnExp.pop(finalResult) )
	{
		if ( valid )
			cout << " = " << finalResult << endl;
		else
			cout << "\t invalid - too many operands" << endl;
	}
	else
		cout << "\t invalid - not enough operands" << endl;
}

//****************************************************************************************************
