#ifndef NEWLINE_HPP
#define NEWLINE_HPP

#include "Command.hpp"
#include <string>

class NewLine: public Command
{
private:
	static const int newX = 1;
//Standard override syntax when declaring methods that will override or replace methods from an inherited class
public:
	virtual void execute(EditorModel &model) override;
	virtual void undo(EditorModel &model) override;
private:
// Enter can create a newLine after whatever lineNumber its at, and adding to that line, any content that was at and to right of  cursor
// Fields needed to execute and undo an enter or '\n' command in all scenarios it could occur
	int currX;
	int currY;
	int currentLineCount; 
	int newY;
	std::string oldData;
};

#endif