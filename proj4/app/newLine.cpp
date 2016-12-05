#include "newLine.hpp"

void NewLine::execute(EditorModel &model)
{
	currX = model.cursorColumn(); //Get cursor current coordinates
	currY = model.cursorLine();
	oldData = model.line(currY); //Have a record of the lineString before the newline command was executed
	std::string appendString = "";
	if(currX < oldData.length() + 1) //If cursor is not beyond the end of the current lineString
		appendString = oldData.substr(currX - 1,oldData.length()); //Make a string of the all characters from the character at cursor's column position
																	/// All the way to the end of the string
	std::string prevString = "";
	if(currX > 1)//When cursor beyonf the beginning of the string
	{
		prevString = oldData.substr(0, currX - 1); //Make a string of the line from the beginning and up to char in the cursor column position
	}
	newY = currY + 1; //Enter always puts the cursor at the beginning and 1 down
	currentLineCount = model.lineCount(); //Always adds a new line so lineCount must be incremented
	model.setLineCount(currentLineCount + 1);
	model.incLine(newY,appendString); //Add the line with its content,if any
	model.setLine(prevString, currY); //Modify the currentLine if needed
	model.setCursorLine(newY); //Set cursor to new coordinates
	model.setCursorCol(newX);

}

void NewLine::undo(EditorModel &model)
{
	model.decLine(newY); //Remove the new Line and contents
	model.setLineCount(currentLineCount); // Put lineCount to its previous value
	model.setLine(oldData, currY); //Make the contents of the line preceding what was the newLine back to its previous values
	model.setCursorLine(currY);// Set cursor to old coordinates
	model.setCursorCol(currX);
}