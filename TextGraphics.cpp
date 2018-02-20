//----------------------------------------------------------------------------
// File:	TextGraphics.cpp
// 
// Functions:
//      boxTop()
//      boxBottom()
//      boxLine()
//----------------------------------------------------------------------------

#include "textGraphics.h"

void line()
{
	cout << DHORIZ;
	for (int i = 0; i < MAX_LINE_LENGTH; i++)
		cout << HORIZ;
	cout << DHORIZ;
}
//---------------------------------------------------------------------------------
// Function:	boxTop()
// Title:	Box Top
// Description:
//		draws a a line for the top of the box
// Programmer:	Paul Bladek
// 
// Date:	10/3/2006
//
// Version:	1.01
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Output:	Formatted line to sout
//
// Called By:	header()
//		endbox()
//
// Parameters:	sout: ostream&;		stream to print to
//		ength: unsigned short;	length of the box
// 
// Returns:	void
//
// History Log:	
//		10/3/2006	PB completed v 1.01
//   
//---------------------------------------------------------------------------------
void boxTop(ostream& sout, unsigned short length)
{
	sout << endl << DUL;
	for (int i = 0; i < length; i++)
		sout << DHORIZ;
	sout << DUR << endl;
}

//---------------------------------------------------------------------------------
// Function:	boxBottom()
// Title:	Box Bottom
// Description:
//		draws a a line for the bottom of the box
// Programmer:	Paul Bladek
// 
// Date:	10/3/2006
//
// Version:	1.01
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Output:	Formatted line to sout
//
// Called By:	header()
//		endbox()
//
// Parameters:	sout: ostream&;		stream to print to
//		ength: unsigned short;	length of the box
// 
// Returns:		void
//
// History Log:	
//		10/3/2006 PB completed v 1.01
//   
//---------------------------------------------------------------------------------
void boxBottom(ostream& sout, unsigned short length)
{
	sout << DLL;
	for (int i = 0; i < length; i++)
		sout << HORIZ;
	sout << DLR << endl;
}

string centerLine(string input, int length)
{
	stringstream tempSS;
	list<string> stringList;

		int size = input.size();

		int leftSize = ((length - size) / 2);
		int rightSize = leftSize;

		if ((rightSize * 2 + size) != length)
		{
			rightSize++;
		}

		for (int i = 0; i < leftSize; i++)
		{
			tempSS << ' ';
		}

		tempSS << input;

		for (int i = 0; i < rightSize; i++)
		{
			tempSS << ' ';

		}
	return tempSS.str();
}

//---------------------------------------------------------------------------------
// Function:	boxLine()
// Title:	Box Line
// Description:
//		draws a a line of text aligned in the middle of the box
// Programmer:	Paul Bladek
// 
// Date:	10/3/2006
//
// Version:	1.01
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2012
//
// Output:	Formatted text to sout
//
// Called By:	header()
//		endbox()
//
// Parameters:	sout: ostream&;	stream to print to
//		text: const string&; text to print
//		length: unsigned short;	length of the box
//		alignment: unsigned char;   'L' (left), 'C'(center),'R'(right)
//		fillc: char; fill character
// 
// Returns:	void
//
// History Log:	
//		10/3/2006 PB completed v 1.01
//   
//---------------------------------------------------------------------------------
void boxLine(ostream& sout, const string &text, int length)
{
	string tempString = text;
	string delimiter = "\n";
	size_t pos = 0;
	stringstream tempSS;
	list<string> stringList;
	bool firstPass = true;
	do
	{
		pos = tempString.find(delimiter);
		if (pos == string::npos)
		{
			/*if (firstPass)
				stringList.push_back(tempString);*/
			break;
		}
		else
			stringList.push_back(tempString.substr(0, pos));
		firstPass = false;
		tempString.erase(0, pos + delimiter.length());
	} while (true);
	stringList.push_back(tempString);

	int counter = stringList.size();
	do
	{
		counter--;
		tempString = stringList.front();
		stringList.pop_front();
		sout << DVERT << centerLine(tempString, length) << DVERT << endl;
	} while (counter);
	};

