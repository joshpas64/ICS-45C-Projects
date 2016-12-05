#include "insertChar.hpp"

void InsertChar::setChar(char key)
{
	addkey = key; //set insertChar's addkey field to the user input (key)
}

void InsertChar::execute(EditorModel &model)
{
	currX = model.cursorColumn(); //get cursor coordinates
	currY = model.cursorLine();
	oldData = model.line(currY); //have a record of the line before the char was added
	std::string newStr;
	if(oldData.compare("") == 0) //Empty line case
	{
		newStr = addkey;
	}
	else
	{
		std::string startStr = oldData.substr(0,currX - 1); //Make a string of the oldLineString from the beginning to the cursor column position 
		//(the minus 1 is because of 0-based indexing)
		std::string endStr = "";
		if(currX < oldData.length() + 1) //If the cursor is on a char in the string and is not beyond it
			endStr = oldData.substr(currX - 1,oldData.length()); //make a string of the oldLineString from where the position where the addKey is about to added up to end of the string
		newStr = startStr + addkey + endStr; //Add them all together with addkey being in the middle
	}
	model.setLine(newStr, currY); //Set Line to the upDatedlineString and cursor to its new coordinates
	model.setCursorCol(currX + 1);
}

void InsertChar::undo(EditorModel &model)
{
	model.setLine(oldData, currY); //Set the lineString at lineNumber back to its old state 
	model.setCursorCol(currX); //Set cursor back to its previous position
}