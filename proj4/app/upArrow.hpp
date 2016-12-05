#ifndef UPARROW_HPP
#define UPARROW_HPP

#include "Command.hpp"
#include <string>

class UpArrow : public Command
{
public:
	virtual void execute(EditorModel &model) override;
	virtual void undo(EditorModel &model) override;
private:
	//Since only dealing with cursor movements, the only fields needed are integers relating to coordinates
	int currX;
	int currY;
};

#endif