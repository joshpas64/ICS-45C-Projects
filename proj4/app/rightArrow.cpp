#include "rightArrow.hpp"
#include "EditorException.hpp"


void RightArrow::execute(EditorModel &model)
{
	currX = model.cursorColumn(); //Get cursor's current coordinates
	currY = model.cursorLine();
	int atEnd = model.line(currY).length() + 1; //Determine what number marks the position of the line's end, (length of lineString + 1)
	if(currY == model.lineCount() && currX == atEnd) //If at the last position of text editor, the atEnd of the last line, cannot move right, throw atEnd EditorException
	{
		throw(EditorException("Already at the End"));
	}
	else
	{
		int newX, newY;
		if(currX == atEnd)
		{
			newY = currY + 1; //Move down one line
			newX = 1; //Go to beginning of following line
		}
		else
		{
			newY = currY;
			newX = currX + 1; //Move coordinate to the right one char
		}
		model.setCursorCol(newX); //Set cursor to new coordinates
		model.setCursorLine(newY);
	}
}

void RightArrow::undo(EditorModel &model)
{
	model.setCursorLine(currY); //Set cursor back to old coordinates
	model.setCursorCol(currX);
}