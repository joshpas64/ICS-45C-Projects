#ifndef DOWNARROW_HPP
#define DOWNARROW_HPP

#include "Command.hpp"
#include <string>

class DownArrow : public Command
{
public:
	virtual void execute(EditorModel &model) override;
	virtual void undo(EditorModel &model) override;
private:
	//Only deals with cursor movements, so only four integer fields needed
	int currX;
	int currY;
};

#endif