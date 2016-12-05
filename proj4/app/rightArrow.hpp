#ifndef RIGHTARROW_HPP
#define RIGHTARROW_HPP

#include "Command.hpp"
#include <string>

class RightArrow : public Command
{
public:
	virtual void execute(EditorModel &model) override;
	virtual void undo(EditorModel &model) override;
private:
	// Just need coordinate integers to use as fields since this command only deals with cursor movements
	int currX;
	int currY;
};

#endif