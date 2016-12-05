#ifndef BACKSPACE_HPP
#define BACKSPACE_HPP

#include "Command.hpp"
#include <string>

class BackSpace: public Command
{
	//standard override syntax
public:
	virtual void execute(EditorModel &model) override;
	virtual void undo(EditorModel &model) override;
private:
	//In order to backspace and delete a character and move cursor appropriately and be able to undo them, these fields are needed
	int currX;
	int currY;
	int newY;
	std::string lineData;
	std::string prevLine;
};

#endif