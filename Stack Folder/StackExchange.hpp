#ifndef STACKEXCHANGE_HPP
#define STACKEXCHANGE_HPP

#include <iostream>
#include "Stacks.hpp"
class StackExchange
{
public:
	StackExchange();
	void runStackExchange();
	void undo();
	void redo();
	void add();
	void displayStatus() const;
	int getRedoTotal() const;
	int getUndoTotal() const;
	int getTotal() const;
	void showTotal() const;
private:
	Stacks undoStack;
	Stacks redoStack;
	int nodeTotal;
};
#endif