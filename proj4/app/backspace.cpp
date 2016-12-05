#include "backspace.hpp"
#include "EditorException.hpp"


void BackSpace::execute(EditorModel &model)
{
	currX = model.cursorColumn(); //Get current cursor coordinates
	currY = model.cursorLine();
	lineData = model.line(currY); //Get current line
	int currentLineCount = model.lineCount(); //Get current lineCount, in the case of having to move to a previous line
	prevLine = ""; //The position will determine values of these three following strings so inititalize them to empty strings at the beginning
	std::string nextLine = "";
	std::string combineLine = "";
	if(currX == 1 && currY == 1) //Throw atBeginning EditorException when at origin (1,1)
	{
		throw EditorException("Already at the Beginning");
	}
	else
	{
		int newX;
		if(currX == 1) //When at tehe beginning of line, this means you must move to the previous line along with any contents that lay after the cursor
		{
			newY = currY - 1; //cursor will be at previous line
			prevLine = model.line(newY); //Get the lineString of previous liine
			newX = prevLine.length() + 1; //Get max bound of previous line
			combineLine = prevLine + lineData; //the new string on the preceding line will now be its original contents as well as what was
			// the following line's contents appended to the end
			model.setLine(combineLine, newY); 
			model.decLine(currY);//Remove and reset the contents of the string of the line at currY, the currentline
			model.setLineCount(currentLineCount - 1); //Doing this takes 1 line off the line total
		}
		else
		{
			newY = currY; //keep cursor y-coordinate the same
			newX = currX - 1; //move cursor back by 1 char
			if(currX <= lineData.length())  //When not beyond the scope of the string
			{
				prevLine = lineData.substr(0,currX - 2); //Make a string going from the beginning and up to (NOT INCLUDING) the char to be deleted
				nextLine = lineData.substr(newX, lineData.length()); //Make a string from 1 char beyond the deleted char to the end of the string
			}
			else
			{
				prevLine = lineData.substr(0, lineData.length() - 1); //Just make a string of the oldString up to but not including its LAST Char
			}
			combineLine = prevLine + nextLine; //Add strings together, in else case , nextLine stays at ""
			model.setLine(combineLine,newY); //Make line at the lineNumber equal this summed string
		}
		model.setCursorCol(newX); //Set new cursor coordinates
		model.setCursorLine(newY);
	}
}

void BackSpace::undo(EditorModel &model)
{
	//Both will reset cursor coordinates
	if(currY == newY && currX > 1)
	{
		model.setLine(lineData, currY); //In case where the cursor was just previously in the middle of a line, reset the string to its old state
		model.setCursorCol(currX); 
		model.setCursorLine(currY);
	}
	else if(currY > 1 && currY != newY) //In the case where backspace moved back a line and made a new line being the summed string of the previous and following lines
	{
		model.setLine(prevLine,newY); //Set the previous line's content back to its old state
		model.setLineCount(model.lineCount() + 1); //A line will soon be addded so inc. lineCount
		model.incLine(currY, lineData); //Reset the following line to its old state
		model.setCursorCol(currX);
		model.setCursorLine(currY);
	}
}
