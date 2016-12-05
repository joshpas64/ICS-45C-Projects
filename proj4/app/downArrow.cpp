#include "downArrow.hpp"
#include "EditorException.hpp"

void DownArrow::execute(EditorModel &model)
{
	currX = model.cursorColumn(); //Get current cursor coordinates
	currY = model.cursorLine();
	if(currY == model.lineCount()) //if at last line, cannot go further down so throw Already at bottom EditorException
	{
		throw(EditorException("Already at the Bottom"));
	}
	else
	{
		int newY = currY + 1; //Move cursor down one line
		int newX = model.line(newY).length() + 1; //Check the bounds, meaning check 1 beyond the length of the lineString of the following line
		if(currX <= newX) //if the current column is greater than that bound, make the new cursorColumn equal, or reduce it to that bound
			newX = currX; // if not, leave as is
		model.setCursorLine(newY); //Set cursor to new coordinates
		model.setCursorCol(newX);
	}
}

void DownArrow::undo(EditorModel &model)
{
	model.setCursorCol(currX); //Set cursor back to old coordinates
	model.setCursorLine(currY);
}