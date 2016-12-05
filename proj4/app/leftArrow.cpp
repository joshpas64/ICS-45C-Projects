#include "leftArrow.hpp"
#include "EditorException.hpp"

void LeftArrow::execute(EditorModel &model)
{
	currX = model.cursorColumn(); //Get cursor's current coordinates
	currY = model.cursorLine();
	if(currX == 1 && currY == 1) //Cannot move left from origin (1,1) throw alreadyAtBeginning EditorException
	{
		throw(EditorException("Already at the Beginning"));
	}
	else if(currX == 1) //At the beginning and need to move to previous line
	{
		newY = currY - 1; 
		newX = model.line(newY).length() + 1; //Go to previous line's "END", which is 1 char space beyond the last character in the lineString
	}
	else
	{
		newY = currY;
		newX = currX - 1; //Just move back 1 character
	}
	model.setCursorCol(newX); //Set cursor to new coordinates
	model.setCursorLine(newY);
}

void LeftArrow::undo(EditorModel &model)
{
	model.setCursorLine(currY); //Set cursor to old coordinates
	model.setCursorCol(currX);
}