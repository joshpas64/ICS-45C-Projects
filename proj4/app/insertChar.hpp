#ifndef INSERTCHAR_HPP
#define INSERTCHAR_HPP

#include "Command.hpp"
#include <string>

class InsertChar: public Command
{
public:
	void setChar(char key); //method only available to this Class ONLY not its parent, this is because what a user can enter can obviously vary
	virtual void execute(EditorModel &model) override;
	virtual void undo(EditorModel &model) override;
private:
	std::string oldData; 
	char addkey;//Field to initialize with set char, this is done before calling execute()
	int currX;
	int currY;
};

#endif