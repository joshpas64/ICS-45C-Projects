#ifndef ENDOFLINE_HPP
#define ENDOFLINE_HPP

#include "Command.hpp"
#include <string>
// Moves cursor to the end of its line which 1 char space beyond the last character in its lineString
class EndOfLine : public Command
{
public:
	virtual void execute(EditorModel &model) override;
	virtual void undo(EditorModel &model) override;
private:
	//to be able to undo and execute, command needs these three fields
	int currX;
};

#endif