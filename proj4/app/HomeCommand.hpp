#ifndef HOMECOMMAND_HPP
#define HOMECOMMAND_HPP

#include "Command.hpp"

class HomeCommand : public Command
{
//Move cursor to beginning of line
private:
	static const int NEWX = 1; //Since beginning always same (1) make this a static private constant variable
public:
	virtual void execute(EditorModel &model) override;
	virtual void undo(EditorModel &model) override;
private:
	int currX; //Used for undoing this command
};

#endif