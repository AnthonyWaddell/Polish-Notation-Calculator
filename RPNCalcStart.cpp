//-----------------------------------------------------------------------------
//	File:			RPNCalcStart.cpp
//	Functions:		add()
//					binary_prep()
//					clearAll()
//					clearEntry()
//					CRPNCalc() 
//					divide()
//					exp()
//					getReg()
//					input()
//					loadProgram()
//					mod()
//					multiply()
//					neg()
//					parse()
//					print()
//					recordProgram()
//					rotateDown()
//					rotateUp()
//					run()
//					runProgram()
//					saveToFile()
//					setReg()
//					subtract()
//					unary_prep()
//					validNumber()
//-----------------------------------------------------------------------------
#include "RPNCalc.h"
#include <math.h>

//-----------------------------------------------------------------------------
//	Title:			CRPNCalc Class
//  File:			RPNCalc.cpp
//	Description:	This file contains the function definitions for CRPNCalc
//	Programmers:	Anthony Waddell, Ginger Rabun, Jonathan Duong
//	Date:			06/01/2017
//	Version:		1.0 
//	Environment:	Hardware:	PC 
//					Software:   MS Windows 10
//					Compiles under Microsoft Visual C++.Net 2015
//-----------------------------------------------------------------------------

namespace PB_CALC
{
	//-------------------------------------------------------------------------
	//	Class:			CRPNCalc
	//	Method:			constructor(bool on)
	//	Description:	Creates the calculator, initializes the registers, and 
	//					starts running the calculator
	//	Input:			N/A
	//	Output:			N/A
	//	Calls:			run()
	//	Called By:		N/A
	//	Parameter:		bool on; whether the calculator is running
	//	Returns:		N/A
	//	History Log:	06-03-17 PB Completed v 1.0
	//-------------------------------------------------------------------------
	CRPNCalc::CRPNCalc(bool on) : m_on(on), m_error(false), m_helpOn(true),
		m_programRunning(false)
	{
		for (int i = 0; i < NUMREGS; i++)
			m_registers[i] = 0.0;
		if (m_on)
			run();
	}

	//-------------------------------------------------------------------------
	//	Class:			CRPNCalc
	//	Method:			run()
	//	Description:	Runs calculator until m_on is false
	//	Input:			N/A
	//	Output:			N/A
	//	Calls:			print(ostream& ostr), overloaded >> operator
	//	Called By:		CRPNCalc constructor
	//	Parameter:		N/A
	//	Returns:		void
	//	History Log:	06-03-17 JD Completed v 1.0
	//					06-07-17 JD Completed v 1.1
	// ------------------------------------------------------------------------
	void CRPNCalc::run()
	{
		while (m_on)
		{
			print(cout);
			cin >> *this;
			cout << endl << endl;
			system("pause");
			system("cls");
		}
	}

	//-------------------------------------------------------------------------
	//	Class:			RPNCalcStart
	//	Method:			print(ostream& ostr)
	//	Description:	Prints out the calculator screen
	//	Input:			N/A
	//	Output:			the calculator header, help menu, and top stack element
	//	Calls:			N/A
	//	Called By:		run(), overloaded <<operator, methods from textGraphics
	//	Parameter:		ostream& ostr; the designated output stream
	//	Returns:		void
	//	History Log:	06-07-17 JD Completed v 1.0
	// ------------------------------------------------------------------------
	void CRPNCalc::print(ostream& ostr)
	{
		double d = 0.0;

		boxTop(ostr, MAX_LINE_LENGTH);
		boxLine(ostr, "[RPN Programmable Calculator]", MAX_LINE_LENGTH);
		boxLine(ostr, "by Ginger Rabun, Jonathan Duong, Anthony Waddell", MAX_LINE_LENGTH);
		boxBottom(ostr, MAX_LINE_LENGTH);
		
		boxTop(ostr, MAX_LINE_LENGTH);
		if (m_helpOn)
		{
			//print out help menu if on
			boxLine(ostr, helpMenu, MAX_LINE_LENGTH);
		}
		else
		{
			boxLine(ostr, "", MAX_LINE_LENGTH);
			boxLine(ostr, "", MAX_LINE_LENGTH);
			boxLine(ostr, "", MAX_LINE_LENGTH);
			boxLine(ostr, "", MAX_LINE_LENGTH);
		}
			boxBottom(ostr, MAX_LINE_LENGTH);
			//ostr << endl << endl << endl;
		line();

		//print out something if there something on the stack
		if (!m_stack.empty())
		{
			d = m_stack.front();
			string temp = to_string(d);
			boxTop(ostr, MAX_LINE_LENGTH);
			boxLine(ostr, temp, MAX_LINE_LENGTH);
			boxBottom(ostr, MAX_LINE_LENGTH);
		}
		ostr << endl << endl;
		m_error = false;
	}

	//-------------------------------------------------------------------------
	//	Class:			RPNCalcStart
	//	Function:		parse()
	//	Description:	Reads input from m_instrStream, pushes input onto stack
	//					if it's a valid number, calls a method if it's a valid 
	//					command, or displays an error message if input is 
	//					invalid
	//	Input:			N/A
	//	Output:			error messages, information messages
	//	Calls:			validNumber(string input), clearAll(), rotateDown(), 
	//					saveToFile(), loadProgram(), neg(), recordProgram(), 
	//					runProgram(), rotateUp(), getReg(int reg), 
	//					setReg(int reg), clearEntry(), add(), subtract(), 
	//					multiply(), divide(), mod(), exp()
	//	Called By:		input()
	//	Parameters:		N/A		
	//	Returns:		void
	//	History Log:	06-01-17 AW Completed v 1.0
	//					06-01-17 JD Completed v 1.1
	//					06-05-17 AW Completed v 1.2
	//					06-07-17 GR Completed v 1.3
	//					06-08-17 GR Completed v 1.4
	//-------------------------------------------------------------------------
	void CRPNCalc::parse()
	{
		string temp = m_instrStream.str();
		m_error = false;

		// checks to see if valid number, if it is a number, push onto stack
		// otherwise it's probably a command that will be handled below
		if (validNumber(temp))
		{
			double input = stod(temp);
			cout << "Pushing value onto stack..." << endl;
			m_stack.push_front(input);
		}
		else
		{
			// check if input starts with a letter
			if (isalpha(temp.front()))
			{
				// check if input is 1 character long
				if (temp.size() == 1)
				{
					char thingy = tolower(temp.front());
					switch (thingy)
					{
					case ('c'):
					{
						cout << "Clearing the entire stack..." << endl;
						clearAll();
						break;
					}
					case ('d'):
					{
						cout << "Rotating stack down..." << endl;
						rotateDown();
						break;
					}
					case ('f'):
					{
						cout << "Saving program to file..." << endl;
						saveToFile();
						break;
					}
					case ('h'):
					{
						cout << "Toggling help menu..." << endl;
						m_helpOn = !m_helpOn;
						break;
					}
					case ('l'):
					{
						cout << "Loading program from file..." << endl;
						loadProgram();
						break;
					}
					case ('m'):
					{
						cout << "Multiplying top stack element by -1..."
							<< endl;
						neg();
						break;
					}
					case ('p'):
					{
						cout << "Starting to record program, "
							"or stopping if already recording..." << endl;
						recordProgram();
						break;
					}
					case ('r'):
					{
						cout << "Running program..." << endl;
						runProgram();
						break;
					}
					case ('u'):
					{
						cout << "Rotating stack up..." << endl;
						rotateUp();
						break;
					}
					case ('x'):
					{
						cout << "Exiting calculator..." << endl;
						m_on = false;
						break;
					}
					default:
					{
						cout << "Error - invalid command." << endl;
						m_error = true;
					}
					}
				}
				// check if input is 2 characters long
				else if (temp.size() == 2)
				{
					char secondElement = temp[1];
					// check if second character is a number
					if (isdigit(secondElement))
					{
						switch (temp.front())
						{
						case 'g':
						{
							cout << "Pushing register " <<
								secondElement << " onto the stack..."
								<< endl;
							getReg(static_cast<int>(secondElement) - '0');
							break;
						}
						case 's':
						{
							cout << "Popping element and storing it in "
								"register " << secondElement
								<< "..." << endl;
							setReg(static_cast<int>(secondElement) - '0');
							break;
						}
						default:
						{
							cout << "Error - invalid command." << endl;
							m_error = true;
						}
						}

					}
					else
					{
						if (tolower(temp[0]) == 'c'
							&& tolower(temp[1]) == 'e')
						{
							cout << "Popping top element from the stack..."
								<< endl;
							clearEntry();
						}
						else
						{
							cout << "Error - invalid command." << endl;
							m_error = true;
						}
					}


				}
			}
			// otherwise input starts with operator
			else
			{
				// check if input is one character long
				if (temp.length() == 1)
				{
					switch (temp.front())
					{
					case '+':
					{
						cout << "Adding top two elements..." << endl;
						add();
						break;
					}
					case '-':
					{
						cout << "Subtracting top two elements..." << endl;
						subtract();
						break;
					}
					case '*':
					{
						cout << "Multiplying top two elements..." << endl;
						multiply();
						break;
					}
					case '/':
					{
						cout << "Dividing top two elements..." << endl;
						divide();
						break;
					}
					case '^':
					{
						cout << "Exponentiating top two elements..." << endl;
						exp();
						break;
					}
					case '%':
					{
						cout << "Modding top two elements..." << endl;
						mod();
						break;
					}
					default:
					{
						cout << "Error - invalid operator." << endl;
						m_error = true;
					}
					}
				}
				// otherwise input is invalid
				else
				{
					cout << "Error - invalid input." << endl;
					m_error = true;
				}
			}

		}
	}

	//-------------------------------------------------------------------------
	//	Class:			CRPNCalc
	//	Method:			bool validNumber(const string input)
	//	Description:	Checks to see if the input string is a valid number	
	//	Input:			N/A
	//	Output:			N/A
	//	Calls:			N/A
	//	Called By:		parse()
	//	Parameter:		string input; string to be checked
	//	Returns:		true if input is a valid number; false otherwise
	//	History Log:	06-03-17 AW Completed v 1.0
	//					06-07-17 GR Completed v 1.1
	//					06-08-17 AW Completed v 1.2
	//-------------------------------------------------------------------------
	bool CRPNCalc::validNumber(const string input)
	{
		bool valid = false;
		char c = input[0];
		int decimalCount = 0;
		int i = 0;

		// test to see if first char is negative
		if (c == '-')
		{
			if (input.size() == 1)
				return valid;
			else
				i = 1;
		}
		else if (c == ' ')
			return valid;

		//Count the number of negative and decimals, and 
		for (i; i < input.size(); i++)
		{
			c = input[i];
			if (c == '.')
			{
				decimalCount++;
				if (decimalCount > 1)
					return valid;
				if (!isdigit(input[i + 1]))
					return valid;
			}
			else if (!isdigit(c))
				return valid;

		}

		// otherwise, it is a valid number
		valid = true;
		return valid;
	}

	//-------------------------------------------------------------------------
	//	Class:			CRPNCalc
	//	Method:			add()
	//	Description:	If possible, pops top 2 elements from the stack, 
	//					adds them and pushes the result onto the stack
	//	Input:			N/A
	//	Output:			N/A
	//	Calls:			binary_prep(double& d1, double& d2)
	//	Called By:		parse()
	//	Parameter:		N/A
	//	Returns:		N/A
	//	History Log:	06-06-17 JD completed v 1.0
	//-------------------------------------------------------------------------
	void CRPNCalc::add()
	{
		double temp1 = 0;
		double temp2 = 0;
		double result;

		// temp one is first number entered, 
		//temp two is second number entered
		binary_prep(temp1, temp2);

		//push combination of two onto stack
		if (!m_error)
		{
			result = (temp1 + temp2);
			m_stack.push_front(result);
		}
	}

	//-------------------------------------------------------------------------
	//	Class:			CRPNCalc
	//	Method:			binary_prep(double& d1, double& d2)
	//	Description:	Checks whether there are two values to operate on; if 
	//					there are, pops the top elements from the stack and 
	//					sets the args to those values; otherwise, sets an error
	//					state
	//	Input:			N/A
	//	Output:			N/A
	//	Calls:			N/A
	//	Called By:		add(), subtract(), multiply(), divide(), mod(), exp()
	//	Parameter:		double& d1; first value inputted
	//					double& d2; second value inputted
	//	Returns:		N/A
	//	History Log:	06-06-17 GR Completed v 1.0
	//-------------------------------------------------------------------------
	void CRPNCalc::binary_prep(double& d1, double& d2)
	{
		if (m_stack.empty())
		{
			m_error = true;
			cout << "Error - stack is empty." << endl;
		}
		else
		{
			d2 = m_stack.front(); // d2 is the second element entered
			m_stack.pop_front();
			if (m_stack.empty())
			{
				m_error = true;
				cout << "Error - stack only has one value." << endl;
				m_stack.push_front(d2);
			}
			else
			{
				d1 = m_stack.front(); // d1 is the first element entered
				m_stack.pop_front();
			}
		}
	}

	//-------------------------------------------------------------------------
	//	Class:			CRPNCalc
	//	Method:			clearEntry()
	//	Description:	If possible, pops the top element from the stack
	//	Input:			N/A
	//	Output:			N/A
	//	Calls:			N/A
	//	Called By:		parse()
	//	Parameter:		N/A
	//	Returns:		N/A
	//	History Log:	06-06-17 GR Completed v 1.0
	//-------------------------------------------------------------------------
	void CRPNCalc::clearEntry()
	{
		if (m_stack.empty())
		{
			m_error = true;
			cout << "Error - stack is empty." << endl;
		}
		else
			m_stack.pop_front();
	}

	//-------------------------------------------------------------------------
	//	Class:			CRPNCalc
	//	Method:			clearAll()
	//	Description:	Pops all elements from the stack
	//	Input:			N/A
	//	Output:			N/A
	//	Calls:			N/A
	//	Called By:		parse()
	//	Parameter:		N/A
	//	Returns:		N/A
	//	History Log:	06-03-17 PB Completed v 1.0
	//-------------------------------------------------------------------------
	void CRPNCalc::clearAll()
	{
		while (!m_stack.empty())
			m_stack.pop_front();
	}

	//-------------------------------------------------------------------------
	//	Class:			RPNCalcStart
	//	Function:		divide()
	//	Description:	If possible, pops the top two elements off the stack, 
	//					divides one by the other, and pushes the result back 
	//					onto the stack
	//	Input:			N/A
	//	Output:			N/A
	//	Calls:			binary_prep(double& d1, double& d2)
	//	Called By:		parse()
	//	Parameters:		N/A		
	//	Returns:		void
	//	History Log:	06-06-17 AW Completed v 1.0
	//-------------------------------------------------------------------------
	void CRPNCalc::divide()
	{
		double zero = 0;
		double temp1 = 0.0;
		double temp2 = 0.0;
		double result;

		// temp one is first number entered, 
		//temp two is second number entered
		binary_prep(temp1, temp2);

		//push combination of two onto stack
		if (!m_error)
		{
			if (temp2 == zero)
			{
				cout << "Error: cannot divide by zero";
				m_error = true;
				m_stack.push_front(temp1);
			}
			else 
			{
				result = (temp1 / temp2);
				m_stack.push_front(result);
			}
		}
	}

	//-------------------------------------------------------------------------
	//	Class:			RPNCalcStart
	//	Function:		exp()
	//	Description:	If possible, pops the top two elements off the stack, 
	//					raises one to the power of the other, and pushes the 
	//					result back onto the stack
	//	Input:			N/A
	//	Output:			N/A
	//	Calls:			binary_prep(double& d1, double& d2)
	//	Called By:		parse()
	//	Parameters:		N/A		
	//	Returns:		void
	//	History Log:	06-06-17 AW Completed v 1.0
	//-------------------------------------------------------------------------
	void CRPNCalc::exp()
	{
		double temp1 = 0.0;
		double temp2 = 0.0;
		double result;

		// temp one is first number entered, 
		//temp two is second number entered
		binary_prep(temp1, temp2);

		//push combination of two onto stack
		if (!m_error)
		{
			result = powf(temp1, temp2);
			m_stack.push_front(result);
		}

	}
	
	//-------------------------------------------------------------------------
	//	Class:			RPNCalcStart
	//	Function:		getReg(int reg)
	//	Title:			accessor for m_registers
	//	Description:	If possible, pushes the given register's value onto the
	//					stack
	//	Input:			N/A
	//	Output:			N/A
	//	Calls:			N/A
	//	Called By:		parse()
	//	Parameters:		int reg; the register value to access
	//	Returns:		void
	//	History Log:	06-03-17 GR Completed v 1.0
	//					06-08-17 GR Completed v 1.1
	//-------------------------------------------------------------------------
	void CRPNCalc::getReg(int reg)
	{
		if (reg >= 0 && reg < NUMREGS)
			m_stack.push_front(m_registers[reg]);
		else
			cout << "Error - register out of range." << endl;
	}

	//-------------------------------------------------------------------------
	//	Class:			RPNCalcStart
	//	Function:		loadProgram()
	//	Description:	Retrieves the filename from the user and loads it 
	//					into m_program
	//	Input:			the file name supplied by user from console
	//	Output:			N/A
	//	Calls:			N/A
	//	Called By:		parse()
	//	Parameters:		N/A
	//	Returns:		void
	//	History Log:	06-07-17 AW Completed v 1.0
	//-------------------------------------------------------------------------
	void CRPNCalc::loadProgram()
	{
		string fileName;
		string fileLine;
		string extension = ".txt";
		ifstream is;

		//	Get the name of the file from the user
		cout << "Please enter the name of the file "
			"you wish to load (without the extension): ";
		cin >> fileName;
		fileName.append(extension);

		//	Try to open the file 
		try
		{
			is.open(fileName.c_str());
			if (!is.is_open())
			{
				cout << endl << "could not open file " << fileName << endl;
				cin.ignore(FILENAME_MAX, '\n');
			}
			else 
			{
				//	Put each line of the user file into m_program
				while (getline(is, fileLine))
				{
					m_program.push_back(fileLine);
				}
				cout << endl << fileName << " successfully loaded." << endl;
			}

			
		}
		catch (exception e)
		{
			cout << "could not open file " << fileName << endl;
			cin.ignore(FILENAME_MAX, '\n');

		}

		//	Close file
		cin.ignore();
		is.close();
	}

	//-------------------------------------------------------------------------
	//	Class:			RPNCalcStart
	//	Function:		mod()
	//	Description:	If possible, pops the top two elements off the stack, 
	//					mods them, and pushes the result back onto the stack
	//	Input:			N/A
	//	Output:			N/A
	//	Calls:			binary_prep(double& d1, double& d2)
	//	Called By:		parse()
	//	Parameters:		N/A		
	//	Returns:		void
	//	History Log:	06-06-17 AW Completed v 1.0
	//-------------------------------------------------------------------------
	void CRPNCalc::mod()
	{
		double temp1 = 0.0, temp2 = 0.0;

		//get first two elements from stack
		binary_prep(temp1, temp2);

		// Get the fmod of the two elements
		if (!m_error)
		{
			double result = fmod(temp1, temp2);
			//push multiplicative of two onto stack
			m_stack.push_front(result);
		}
	}

	//-------------------------------------------------------------------------
	//	Class:			RPNCalcStart
	//	Function:		multiply()
	//	Description:	If possible, pops the top two elements off the stack, 
	//					multiplies them together, and pushes the result back 
	//					onto the stack
	//	Input:			N/A
	//	Output:			N/A
	//	Calls:			binary_prep(double& d1, double& d2)
	//	Called By:		parse()
	//	Parameters:		N/A		
	//	Returns:		void
	//	History Log:	06-06-17 AW Completed v 1.0
	//-------------------------------------------------------------------------
	void CRPNCalc::multiply()
	{
		double temp1 = 0.0;
		double temp2 = 0.0;
		double result;

		// temp one is first number entered, 
		// temp two is second number entered
		binary_prep(temp1, temp2);

		//push combination of two onto stack
		if (!m_error)
		{
			result = (temp1 * temp2);
			m_stack.push_front(result);
		}
	}

	//-------------------------------------------------------------------------
	//	Class:			RPNCalcStart
	//	Function:		neg()
	//	Description:	If possible, multiplies the top element of the stack 
	//					by -1
	//	Input:			N/A
	//	Output:			N/A
	//	Calls:			unary_prep(double& d)
	//	Called By:		parse()
	//	Parameters:		N/A		
	//	Returns:		void
	//	History Log:	06-08-17 GR Completed v 1.0
	//-------------------------------------------------------------------------
	void CRPNCalc::neg()
	{
		double number = 0.0;
		unary_prep(number);
		if (m_error == false)
			m_stack.push_front(number * -1.0);
	}

	//-------------------------------------------------------------------------
	//	Class:			RPNCalcStart
	//	Function:		unary_prep(double& d)
	//	Description:	Checks whether there is a value to operate on; if there
	//					is, pops the top element from the stack and sets the 
	//					arg to that value; otherwise, sets an error state
	//	Input:			N/A
	//	Output:			N/A
	//	Calls:			N/A
	//	Called By:		neg(), setReg(int reg)
	//	Parameters:		double& d; will hold element to operate on
	//	Returns:		void
	//	History Log:	06-06-17 GR Completed v 1.0
	//-------------------------------------------------------------------------
	void CRPNCalc::unary_prep(double& d)
	{
		if (m_stack.empty())
		{
			m_error = true;
			cout << "Error - stack is empty." << endl;
		}
		else
		{
			d = m_stack.front();
			m_stack.pop_front();
		}
	}

	//-------------------------------------------------------------------------
	//	Class:			CRPNCalc
	//	Method:			recordProgram()
	//	Description:	Clears current program, takes command-line input and 
	//					loads it into m_program, until P is entered
	//	Input:			N/A
	//	Output:			N/A
	//	Calls:			N/A
	//	Called By:		parse()
	//	Parameter:		N/A
	//	Returns:		N/A
	//	History Log:	06/07/17 JD Completed v 1.0	
	//-------------------------------------------------------------------------
	void CRPNCalc::recordProgram()
	{
		int counter = 0;

		//empties m_program
		while (!m_program.empty())
			m_program.pop_front();

		//resets buffer
		m_buffer = "";
		m_programRunning = true;
		string STOP = "p";

		//clear buffer
		//while (cin.get() != '\n')
			//cin.ignore(INT_MAX);

		while (m_programRunning)
		{
			cout << counter << "> ";
			getline(cin, m_buffer);
			if (m_buffer == STOP)
			{
				m_programRunning = false;
			}
			else
			{
				m_program.push_back(m_buffer);
			}
			counter++;
		}
	}

	//-------------------------------------------------------------------------
	//	Class:			RPNCalcStart
	//	Function:		rotateDown()
	//	Description:	If possible, removes the bottom element of the stack 
	//					and adds it to the top
	//	Input:			N/A
	//	Output:			N/A
	//	Calls:			N/A
	//	Called By:		parse()
	//	Parameters:		N/A		
	//	Returns:		void
	//	History Log:	06-03-17 GR Completed v 1.0
	//-------------------------------------------------------------------------
	void CRPNCalc::rotateDown()
	{
		if (m_stack.empty())
		{
			m_error = true;
			cout << "Error - stack is empty." << endl;
		}
		else
		{
			m_stack.push_back(m_stack.front());
			m_stack.pop_front();
		}
	}

	//-------------------------------------------------------------------------
	//	Class:			RPNCalcStart
	//	Function:		rotateUp()
	//	Description:	If possible, removes the top element of the stack and 
	//					adds it to the bottom
	//	Input:			N/A
	//	Output:			N/A
	//	Calls:			N/A
	//	Called By:		parse()
	//	Parameters:		N/A		
	//	Returns:		void
	//	History Log:	06-06-17 GR Completed v 1.0
	//-------------------------------------------------------------------------
	void CRPNCalc::rotateUp()
	{
		if (m_stack.empty())
		{
			m_error = true;
			cout << "Error - stack is empty." << endl;
		}
		else
		{
			m_stack.push_front(m_stack.back());
			m_stack.pop_back();
		}
	}

	//-------------------------------------------------------------------------
	//	Class:			CRPNCalc
	//	Method:			void runProgram()
	//	Description:	If possible, inputs the lines stored in m_program
	//	Input:			N/A
	//	Output:			N/A
	//	Calls:			N/A
	//	Called By:		parse()
	//	Parameter:		N/A
	//	Returns:		N/A
	//	History Log:	06-07-17 JD Completed v 1.0	
	//-------------------------------------------------------------------------
	void CRPNCalc::runProgram()
	{
		for (list<string>::iterator strIt = m_program.begin();
			strIt != m_program.end(); strIt++)
		{
			//sets m_instrStream to line of m_program
			m_instrStream.str(*strIt);
			//splits up text in input
			input(m_instrStream);
			m_instrStream.clear();
		}
	}

	//-------------------------------------------------------------------------
	//	Class:			CRPNCalc
	//	Method:			void saveToFile()
	//	Description:	If possible, saves the lines stored in m_program to a 
	//					file
	//	Input:			N/A
	//	Output:			N/A
	//	Calls:			N/A
	//	Called By:		parse()
	//	Parameter:		N/A
	//	Returns:		N/A
	//	History Log:	06-07-17 JD Completed v 1.0
	//-------------------------------------------------------------------------
	void CRPNCalc::saveToFile()
	{
		if (!m_program.empty())
		{
			ofstream ofs;
			string filename;

			cout << "Please enter the name of the file "
				"to save to (ex: \"test\", not \"test.txt\"): ";
			cin >> filename;
			filename += ".txt";
			try
			{
				ofs.open(filename, ofstream::out);
				for (list<string>::iterator strIt = m_program.begin();
					strIt != m_program.end(); strIt++)
				{
					ofs << *strIt << endl;
				}
				cout << endl <<  filename << " saved" << endl;
			}
			catch (exception e)
			{
				cout << "Error! Could not write to file!" << endl;
			}
			ofs.close();
		}
		else
		{
			cout << "Error! Program is empty! Please enter something by "
				"hitting \"P\" to record" << endl;
		}
	}

	//-------------------------------------------------------------------------
	//	Class:			RPNCalcStart
	//	Function:		setReg(int reg)
	//	Description:	If possible, gets the value from the top of the stack
	//					and places it into the given register
	//	Input:			N/A
	//	Output:			N/A
	//	Calls:			unary_prep(double& d)
	//	Called By:		parse()
	//	Parameters:		int reg; number of the register to modify
	//	Returns:		void
	//	History Log:	06-08-17 GR Completed v 1.0
	//-------------------------------------------------------------------------
	void CRPNCalc::setReg(int reg)
	{
		cout << "reg = " << reg << endl;
		if (reg >= 0 && reg < NUMREGS)
		{
			double number = 0.0;
			unary_prep(number);
			if (m_error == false)
			{
				m_registers[reg] = number;
			}
		}
		else
		{
			cout << "Error - register out of range." << endl;
			m_error = true;
		}
	}

	//-------------------------------------------------------------------------
	//	Class:			RPNCalcStart
	//	Function:		subtract()
	//	Description:	If possible, pops the top two elements off the stack, 
	//					subtracts one from the other, and pushes the result 
	//					back onto the stack
	//	Input:			N/A
	//	Output:			N/A
	//	Calls:			binary_prep(double& d1, double& d2)
	//	Called By:		parse()
	//	Parameters:		N/A		
	//	Returns:		void
	//	History Log:	06-06-17 AW Completed v 1.0
	//-------------------------------------------------------------------------
	void CRPNCalc::subtract()
	{
		double temp1 = 0.0;
		double temp2 = 0.0;
		double result;

		// temp one is first number entered, 
		// temp two is second number entered
		binary_prep(temp1, temp2);

		//push combination of two onto stack
		if (!m_error)
		{
			result = (temp1 - temp2);
			m_stack.push_front(result);
		}
	}

	//-------------------------------------------------------------------------
	//	Class:			RPNCalcStart
	//	Function:		input(istream &istr)
	//	Description:	Copies input from istr to m_buffer, initializes 
	//					m_instrStream with m_buffer, and calls parse()
	//	Input:			N/A
	//	Output:			N/A
	//	Calls:			parse()
	//	Called By:		overloaded >> operator
	//	Parameters:		istream &istr; the designated input stream		
	//	Returns:		void
	//	History Log:	06-01-17 JD Completed v 1.0
	//					06-03-17 AW Completed v 1.1
	//					06-07-17 JD Completed v 1.2
	//					06-08-17 JD Completed v 1.3
	//-------------------------------------------------------------------------
	void CRPNCalc::input(istream &istr)
	{
		string temp = "";
		m_buffer = ""; //reset buffer
		//get line input
		getline(istr, m_buffer);

		string delimiter = " ";
		size_t pos = 0;

		//seperates everything in line if there is a space
		while ((pos = m_buffer.find(delimiter)) != string::npos)
		{
			//substring from beginning to char before space
			temp = m_buffer.substr(0, pos);
			cout << temp << endl;
			m_instrStream.str(temp);
			//ignores empty input
			if (temp != "")
				parse();
			//prints out first thing on the stack
			//if (!m_stack.empty())
			//{
			//	double d = m_stack.front();
			//	//convert double to string to input to boxLine()
			//	string temp = to_string(d);
			//	//puts out answer in a box
			//	boxTop(cout, MAX_LINE_LENGTH);
			//	boxLine(cout, temp, MAX_LINE_LENGTH);
			//	boxBottom(cout, MAX_LINE_LENGTH);
			//}
			//erase everything up to the space
			m_buffer.erase(0, pos + delimiter.length());
		}
		//checks the last digit
		cout << m_buffer << endl;
		m_instrStream.str(m_buffer);
		
		if (m_buffer != "")
		{
			parse();
			if (!m_stack.empty())
			{
				double d = m_stack.front();
				string temp = to_string(d);
				boxTop(cout, MAX_LINE_LENGTH);
				boxLine(cout, temp, MAX_LINE_LENGTH);
				boxBottom(cout, MAX_LINE_LENGTH);
			}
		}
	}

	//-------------------------------------------------------------------------
	//	Class:			RPNCalcStart
	//	Function:		ostream &operator <<(ostream &ostr, CRPNCalc &calc)
	//	Description:	Overloaded output operator for RPNCalc class
	//	Input:			N/A
	//	Output:			calculator screen
	//	Calls:			print()
	//	Called By:		N/A
	//	Parameters:		ostream &ostr; the designated output stream	
	//					CRPNCalc &calc; the running calculator 
	//	Returns:		a reference to ostr
	//	History Log:	06-03-17 PB Completed v 1.0
	//-------------------------------------------------------------------------
	ostream &operator << (ostream &ostr, CRPNCalc &calc)
	{
		calc.print(ostr);
		return ostr;
	}

	//-------------------------------------------------------------------------
	//	Class:			RPNCalcStart
	//	Function:		istream &operator >> (istream &istr, CRPNCalc &calc)
	//	Description:	Overloaded input operator for RPNCalc class
	//	Input:			user supplied information from console
	//	Output:			N/A
	//	Calls:			input()
	//	Called By:		run()
	//	Parameters:		istream &istr; the designated input stream	
	//					CRPNCalc &calc; the running calculator 
	//	Returns:		a reference to istr
	//	History Log:	06-03-17 PB Completed v 1.0
	//-------------------------------------------------------------------------
	istream &operator >> (istream &istr, CRPNCalc &calc)
	{
		calc.input(istr);
		return istr;
	}

} // end namespace PB_CALC
