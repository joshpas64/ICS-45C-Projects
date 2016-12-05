#include "endOfLine.hpp"

void EndOfLine::execute(EditorModel &model)
{
	currX = model.cursorColumn(); //get current cursor coordinates
	int currY = model.cursorLine();
	int newX = model.line(currY).length() + 1; //Set cursor to the farthest ending  column possible, depending on the length of the string in the line
	model.setCursorCol(newX);
}

void EndOfLine::undo(EditorModel &model)
{
	model.setCursorCol(currX); //Reset cursor
}