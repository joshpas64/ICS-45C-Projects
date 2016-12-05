#include "upArrow.hpp"
#include "EditorException.hpp"

void UpArrow::execute(EditorModel &model)
{
	currX = model.cursorColumn(); //Get current cursor coordinates
	currY = model.cursorLine();
	if(currY == 1) //If at first line, cannot move further up, throw atTop EditorException
	{
		throw EditorException("Already at Top");
	}
	int newY = currY - 1; //Move up one line
	int newX = model.line(newY).length() + 1; //Check bounds, which in this case is the preceding line's end Column, one Char space beyond the length of the string
										//that it contains
	if(currX <= newX) //if the current cursor column is above that bounds reset the newX to the bounds
		newX = currX;//if not leave cursor's x-coordinate as is
	model.setCursorLine(newY);//Set cursor to its new coordinates
	model.setCursorCol(newX);
}

void UpArrow::undo(EditorModel &model)
{
	model.setCursorCol(currX); //Set the cursor back to its old stored coordinates
	model.setCursorLine(currY);
}