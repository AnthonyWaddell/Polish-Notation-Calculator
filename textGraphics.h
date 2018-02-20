//---------------------------------------------------------------------------------
// File:		textGraphics.h
// 
// Description: declarations for utilizing extended ASCII characters
//	
// Programmer:	Paul Bladek
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2012
//---------------------------------------------------------------------------------
#ifndef TEXTGRAPH_H
#define TEXTGRAPH_H
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cctype>
#include <sstream> 
#include <cstdlib>
#include <list>
#include <iterator>
using namespace std;

// char definitions
const unsigned char DUL = 0xc9;		// double upper left
const unsigned char DUR = 0xbb;		// double upper right
const unsigned char DLL = 0xc8;		// double lower left
const unsigned char DLR = 0xbc;		// double lower right
const unsigned char UL = 0xda;		// upper left
const unsigned char UR = 0xbf;		// upper right
const unsigned char LL = 0xc0;		// lower left
const unsigned char LR = 0xd9;		// lower right
const unsigned char DHORIZ = 0xcd;	// double horizontal bar
const unsigned char HORIZ = 0xc4;	// horizontal bar
const unsigned char CR = 0xc3;		// cross to the right
const unsigned char CL = 0xb4;		// cross to the left
const unsigned char CU = 0xc1;		// cross up 
const unsigned char CD = 0xc2;		// cross down
const unsigned char DVERT = 0xba;	// vertical bar
const unsigned char VERT = 0xb3;	// vertical bar
const unsigned char CROSS = 0xc5;	// crosses
const unsigned char MISS = 0xb0;	// screen pattern

const unsigned char LEFT = 'L';		// left alignment
const unsigned char RIGHT = 'R';	// right alignment
const unsigned char CENTER = 'C';	// center alignment

const short MAX_LINE_LENGTH = 80;	// longest line allowed
const int OFFSET = 2;			// number of start & end chars

void line();

// centers line
string centerLine(string input, int length);

// prints the top line of a box
void boxTop(ostream& sout, unsigned short length);

// prints the bottom line of a box
void boxBottom(ostream& sout, unsigned short length);

// prints text line of a box
void boxLine(ostream& sout, const string& text, int length);

#endif