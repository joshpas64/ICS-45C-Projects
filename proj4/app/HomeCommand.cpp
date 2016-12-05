#include "HomeCommand.hpp"

void HomeCommand::execute(EditorModel &model)
{
	currX = model.cursorColumn(); //Get cursor col
	model.setCursorCol(NEWX); //Move to 1
}

void HomeCommand::undo(EditorModel &model)
{
	model.setCursorCol(currX); //Move cursor back to its old column
}
