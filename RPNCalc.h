//-----------------------------------------------------------------------------
//	File:			RPNCalc.h
//	Class:			CRPNCalc
//-----------------------------------------------------------------------------

#ifndef RPNCALC_H
#define RPNCALC_H

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <string>
#include <new>
#include <sstream>
#include <stack>
#include "textGraphics.h"

using namespace std;

//-----------------------------------------------------------------------------
//	Title:			RPNCalc Class
//	Description:	This file contains the class definition for CRPNCalc
//	Programmer:		Ginger Rabun, Anthony Waddell, Jonathan Duong
//	Date:			06/01/2017
//	Version:		1.03
//	Environment:	Hardware:	PC 
//					Software:   MS Windows 10
//					Compiles under Microsoft Visual C++.Net 2015
//	Class:			RPNCalc
//	Properties:		double m_registers[NUMREGS] -- for storing numeric values
//					string m_buffer -- most recent input from keyboard
//					deque<double> m_stack -- deque for numeric input
//					list<string> m_program -- list of calculator inputs to be 
//						parsed
//					istringstream m_inStrStream -- stream for input from 
//						keyboard or m_program; to be parsed
//					bool m_error -- whether error has been encountered
//					bool m_helpOn -- whether to print help menu
//					bool m_on -- whether to continue running application
//					bool m_programRunning -- whether m_program is running
//	Methods:	
//		Public:		CRPNCalc(bool on = true)
//						Description: Creates the calculator, initializes the 
//							registers, and starts running the calculator
//						Parameter: 
//							bool on; whether the calculator is running
//						Return: N/A
//	
//					void run()
//						Description: Runs calculator until m_on is false
//						Parameter: N/A
//						Return: N/A
//	
//					void print(ostream& ostr)
//						Description: Prints out the calculator screen
//						Parameter: 
//							ostream& ostr; the designated output stream
//						Return: N/A
//	
//					void input(istream& istr)
//						Description: Copies input from istr to m_buffer, 
//							initializes m_instrStream with m_buffer, and calls 
//							parse()
//						Parameter: 
//							istream &istr; the designated input stream
//						Return: N/A
//	
//		Private:	void add()
//						Description: If possible, pops top 2 elements from the 
//							stack, adds them and pushes the result onto the 
//							stack
//						Parameter: N/A
//						Return: N/A
//	
//					void binary_prep(double& d1, double& d2)
//						Description: Checks whether there are two values to 
//							operate on; if there are, pops the top elements 
//							from the stack and sets the args to those values; 
//							otherwise, sets an error state
//						Parameters: 
//							double& d1; will hold first value to operate on
//							double& d2; will hold second value to operate on
//						Return: N/A
//	
//					void clearEntry()
//						Description: If possible, pops the top element from the
//							stack
//						Parameter: N/A
//						Return: N/A
//	
//					void clearAll()
//						Description: Pops all elements from the stack
//						Parameter: N/A
//						Return: N/A
//	
//					void divide()
//						Description: If possible, pops the top two elements off
//							the stack, divides one by the other, and pushes the
//							result back onto the stack
//						Parameter: N/A
//						Return: N/A
//	
//					void exp()
//						Description: If possible, pops the top two elements off
//							the stack, raises one to the power of the other, 
//							and pushes the result back onto the stack
//						Parameter: N/A
//						Return: N/A
//	
//					void getReg(int reg)
//						Description: If possible, pushes the given register's 
//							value onto the stack
//						Parameter: 
//							int reg; the register value to access
//						Return: N/A
//	
//					void loadProgram()
//						Description: Retrieves the filename from the user and 
//							loads it into m_program
//						Parameter: N/A
//						Return: N/A
//		
//					void mod()
//						Description: If possible, pops the top two elements off
//							the stack, mods them, and pushes the result back 
//							onto the stack
//						Parameter: N/A
//						Return: N/A
//	
//					void neg()
//						Description: If possible, multiplies the top element of
//							the stack by -1
//						Parameter: N/A
//						Return: N/A
//	
//					void parse()
//						Description: Reads input from m_instrStream, pushes 
//							input onto stack if it's a valid number, calls a 
//							method if it's a valid command, or displays an 
//							error message if input is invalid
//						Parameter: N/A
//						Return: N/A
//		
//					void recordProgram()
//						Description: Clears current program, takes command-line
//							input and loads it into m_program, until P is 
//							entered
//						Parameter: N/A
//						Return: N/A
//	
//					void rotateUp()
//						Description: If possible, removes the top element of 
//							the stack and adds it to the bottom
//						Parameter: N/A
//						Return: N/A
//	
//					void rotateDown()
//						Description: If possible, removes the bottom element 
//							of the stack and adds it to the top
//						Parameter: N/A
//						Return: N/A
//	
//					void runProgram()
//						Description: If possible, inputs the lines stored in 
//							m_program
//						Parameter: N/A
//						Return: N/A
//	
//					void saveToFile()
//						Description: If possible, saves the lines stored in 
//							m_program to a file
//						Parameter: N/A
//						Return: N/A
//	
//					void setReg(int reg)
//						Description: If possible, gets the value from the top 
//							of the stack and places it into the given register
//						Parameter: 
//							int reg; number of the register to modify
//						Return: N/A
//	
//					void subtract()
//						Description: If possible, pops the top two elements off
//							the stack, subtracts one from the other, and pushes
//							the result back onto the stack
//						Parameter: N/A
//						Return: N/A
//	
//					void unary_prep(double& d)
//						Description: Checks whether there is a value to operate
//							on; if there is, pops the top element from the 
//							stack and sets the arg to that value; otherwise, 
//							sets an error state
//						Parameter: 
//							double& d; will hold element to operate on
//						Return: N/A
//
//					bool validNumber(const string input)
//						Description: Checks to see if the input string is a 
//							valid number
//						Parameter:
//							const string input; string to be checked
//						Return: true if input is valid number; false otherwise
//	
//	History Log:	4/20/03	PB  completed version 1.0
//					5/27/05	PB  minor modifications 1.01
//					5/3/11	PB  minor modifications 1.02
//					6/3/12  PB  minor modifications 1.03
//-----------------------------------------------------------------------------

namespace PB_CALC
{

	const char helpMenu[] = "C clear stack   | CE clear entry  | D rotate down"
		"  | F save program to file\nG0-G9 get reg n | H help on/off   | L loa"
		"d program | M +/- | P program on/off\nR run program   | S0-S9 set reg"
		" n | U rotate up    | X exit\n";

	const unsigned short NUMREGS = 10;

	class CRPNCalc
	{
	public:
		CRPNCalc(bool on = true);
		void run();                                        
		void print(ostream& ostr);  // changes m_error on error, so not const
		void input(istream& istr);

	private:
	// private methods
		void add();
		void binary_prep(double& d1, double& d2);
		void clearEntry();
		void clearAll();
		void divide();
		void exp();
		void getReg(int reg);
		void loadProgram();
		void mod();
		void multiply();
		void neg();
		void parse();
		void recordProgram();
		void rotateUp();
		void rotateDown();
		void runProgram();
		void saveToFile();
		void setReg(int reg);
		void subtract();
		void unary_prep(double& d);
		bool validNumber(const string input);

	// private properties
		double m_registers[NUMREGS];
		string m_buffer;
		deque<double> m_stack;
		list<string> m_program;
		istringstream m_instrStream;
		bool m_error;
		bool m_helpOn;
		bool m_on;
		bool m_programRunning;
	};

	ostream &operator <<(ostream &ostr, CRPNCalc &calc);
	istream &operator >>(istream &istr, CRPNCalc &calc);

} // end namespace PB_CALC

#endif
