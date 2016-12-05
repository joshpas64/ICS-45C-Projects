#include "DelLine.hpp"
#include "EditorException.hpp"


void DelLine::execute(EditorModel &model)
{
	boundLen = model.lineCount(); //Check line length for possible exception or having to need the cursor's X-coordinate
	int newLineCount = 2;
	if(newLineCount < boundLen) //If there are more than 1 line in the text editor
		newLineCount = boundLen;
	currX = model.cursorColumn(); //get cursor's coordinates
	currY = model.cursorLine();
	lineData = model.line(currY); //get string at current lineNumber
	if (lineData.length() == 0 && boundLen == 1) //If text Editor is completely, there is nothing to delete, raise 'Already Empty editor Exception'
	{
		throw EditorException("Already Empty");
	}
	int newX, newY;
	if (boundLen > 1) //Not on first AND ONLY line
	{
		int checkLen;
		if(currY == boundLen) //If at last line
		{
			newY = currY - 1; //Cursor will be on line that was previously above it
			checkLen = newY;		//check length of previous line
		}
		else if(currY == 1)
		{
			newY = currY; //When at first line check the length of next, (2ndline)'s string'
			checkLen = 2;
		}
		else
		{
			newY = currY; //If not, leave as is
			checkLen = newY - 1; //Check length of previous line
		}
		newX = model.line(checkLen).length() + 1;//Get length of previous string just in case the current cursor's column is out of bounds
		// The max for a cursor is 1 beyond the string's length
		if(currX <= newX) //If the current X's coordinate is not above that bound, leave as is by setting it back to currX
			newX = currX;
	}
	else //When there is only 1 line with content
	{
		newY = 1; //Go back to origin (1,1)
		newX = 1;
	}
	model.decLine(currY); //Delete Line if no exceptions
	model.setLineCount(newLineCount - 1); //Decrement line count
	model.setCursorCol(newX); //Set cursor to new Coordinates if any changes
	model.setCursorLine(newY);
}

void DelLine::undo(EditorModel &model)
{
	if(boundLen > 1) //If the previous state was one where the there was more than one line, increment lineCount
		model.setLineCount(model.lineCount()  + 1);
	model.incLine(currY, lineData); //Add old line back to its correct row in text editor
	model.setCursorLine(currY); //Reset cursor coordinates
	model.setCursorCol(currX);
}

