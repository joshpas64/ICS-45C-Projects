// EditorModel.cpp
//
// ICS 45C Fall 2016
// Project #4: People Just Love to Play with Words
//
// Implementation of the EditorModel class

#include "EditorModel.hpp"
#include "EditorException.hpp"
// *********************************Student : Joshua Comment Begin ************************************************
//Overrided cursorLine, lineCOunt, cursorLine, line, and error message related methods
// Since the 'getter' methods of the EditorModel class were initially constant,
// I changed them to private variables that could be changed through public set methods
// Those fields are the current cursor Column, current error message, current line, the string representing the current line,
// and the total amount of lines in total
// Added a new private field of lines representing all the lines of each line number, used a vector, since it handles dynamic memory
// allocation on its own and has plenty of helpful methods for insert and erasing lines 
// var is std::vector<std::string>lines
EditorModel::EditorModel()
{
	currentLine = currentCol = lineTotals = 1; //Initialize with an empty string with no other lines at top left corner
	currentErrorStatement = "";//Initially there are no errors done, hence no errors to display
	lines.push_back(""); //To make sure the vector always has some Value in it, in this case nothing (empty str)
}


int EditorModel::cursorLine() const
{
    return currentLine; //view uses this line to display on the right line (y - coordinate) of the model being the text editor with EditorModel
    					// being seen as an object representing its current visual state
}


int EditorModel::cursorColumn() const
{
    return currentCol;
    //view uses this line to display on the right column (x - coordinate) of the model
}


int EditorModel::lineCount() const
{
    return lineTotals; //EditorView Class uses this to find the total number of lines and have numbers display to the left for each corresponding
    					//line until the mentioned 'lineTotals' value
}


const std::string& EditorModel::line(int lineNumber) const
{
    static std::string lineString; //Likely because the function must return a constant string reference
    lineString = lines.at(lineNumber - 1); //Take string representing line at the lineNumber and make it that required return type (const std::string&)
    return lineString;
}


const std::string& EditorModel::currentErrorMessage() const
{
    static std::string tempString; //Retrieve errormessage (if any) and use view to display it on the error status section of screen
    tempString.assign(currentErrorStatement); //Use string's built in method to make whatever string it assigns into the needed return type
    return tempString;
}

void EditorModel::setLine(const std::string &str, int lineNumber)
{
	lines.at(lineNumber - 1).assign(str); //Use string's built in method to just make the content of lines[index] equal to the content of the parameter
	// Dont have to worry about reference values or anything like that
}

void EditorModel::decLine(int lineNumber)
{
	int offset = lineNumber - 1; //Account for 0 based indexing
	lines.erase(lines.begin() + offset); //Pops a selected index of the string vector and resizes and reallocates accordingly according to the rules of std::vector
	if(lines.size() == 0) //To ensure the vector is not left empty or in an uninitialized state
		lines.push_back("");// "" denotes an empty line (with NO SPACES )
}

void EditorModel::incLine(int lineNumber, const std::string &str)
{
	int offset = lineNumber - 1; 
	lines.insert(lines.begin() + offset, str); //Insert string at index and resize and restructure accordingly
}
//EditorModel SET methods used by Command base Class

void EditorModel::setCursorLine(int lineNumber)
{
	currentLine = lineNumber; //set cursor y-coordinate
}

void EditorModel::setCursorCol(int colNumber)
{ 
	currentCol = colNumber;//set cursor x-coordinate
}

void EditorModel::setLineCount(int count)
{
	lineTotals = count; //Set current max number of lines
}

void EditorModel::setErrorMessage(const std::string& errorMessage)
{
	currentErrorStatement = errorMessage; //Set a custom error message depending on the command and the state of the EditorModel
}


void EditorModel::clearErrorMessage()
{
	currentErrorStatement = ""; //Clear if a valid command is issued after
}
// ******************************************Commment End **********************************************************
