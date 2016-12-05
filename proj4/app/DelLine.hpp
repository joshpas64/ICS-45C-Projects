#ifndef DELLINE_HPP
#define DELLINE_HPP

#include "Command.hpp"
#include <string>

class DelLine: public Command
{
public:
	virtual void execute(EditorModel &model) override; //Basic override syntax 
	virtual void undo(EditorModel &model) override;
private:
	//To delete a line of content and undo it and properly move and update cursor the model needs certain information from EditorModel parameter
	int currX; 
	int currY;
	std::string lineData;
	int boundLen;
};
#endif