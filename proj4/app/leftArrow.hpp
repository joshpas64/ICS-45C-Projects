#ifndef LEFTARROW_HPP
#define LEFTARROW_HPP

#include "Command.hpp"
#include <string>

class LeftArrow : public Command
{
public:
	//Standard Command method override syntax and declaration
	virtual void execute(EditorModel &model) override;
	virtual void undo(EditorModel &model) override;
private:
	int currX; //Since this only handles the cursor, only integer fields are needed
	int currY;
	int newX;
	int newY;
};

#endif