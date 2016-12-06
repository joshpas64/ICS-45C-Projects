#include "StackExchange.hpp"
#include <iostream>
StackExchange::StackExchange()
{
	undoStack = Stacks();
	redoStack = Stacks();
	nodeTotal = 0;
}
void StackExchange::runStackExchange()
{
	std::cout << "Hi there my good friend" << std::endl;
	char continueChar;
	std::cin >> continueChar;
	std::cin.ignore(1);
	char command;
	while(continueChar != 'N')
	{
		std::cout << "Enter a char to do something: U pops from undoStack\nA pushes to undoStack\nP makes a new node to push to undoStack\n" << 
		"T  is to show the totals\n" << "S is to show the stacks' statuses\n" << "N is to exit this program" << std::endl;
		std::cin >> command;
		std::cin.ignore(1);
		switch(command)
		{
			case 'U':
				undo();
				break;
			case 'A':
				redo();
				break;
			case 'P':
				add();
				break;
			case 'S':
				displayStatus();
				break;
			case 'T':
				showTotal();
				break;
			case 'N':
				continueChar = 'N';
				break;
			default:
				std::cout << "I'm afraid that is invalid input for the command" << std::endl;
				break;
		}
		if(continueChar == 'N')
			break;
		std::cout << "Would you like to continue?: ";
		std::cin >> continueChar;
		std::cin.ignore(1);
	}
	std::cout << "Thank you for your time good sir or madame !" << std::endl;
}

void StackExchange::undo()
{
	if(!undoStack.isEmpty())
	{
		undoStack.exchange(redoStack,true);
	}
	else
	{
		std::cout << "Sorry there are no Nodes to undo try again later" << std::endl;
	}
}

void StackExchange::redo()
{
	if(!redoStack.isEmpty())
	{
		undoStack.exchange(redoStack,false);
	}
	else
	{
		std::cout << "Sorry there are no Nodes to redo, try again later" << std::endl;
	}
}

void StackExchange::add()
{
	std::string commandStr;
	int commandDigits;
	std::getline(std::cin, commandStr);
	std::cin >> commandDigits;
	std::cin.ignore(1);
	undoStack.push(commandStr,commandDigits);
	if(!redoStack.isEmpty())
	{
		int redoTotal = redoStack.getSize();
		nodeTotal = nodeTotal - redoTotal;
		redoStack.clear();	
	}
	nodeTotal++;
}

void StackExchange::displayStatus() const
{
	std::cout << "Here is the undoStack below" << std::endl;
	std::cout << undoStack.toString() << std::endl;
	std::cout << "Here is the redoStack below" << std::endl;
	std::cout << redoStack.toString() << std::endl;
	std::cout << "In total there are " << nodeTotal << " UNIQUE Nodes in this current runThrough" << std::endl;
}

int StackExchange::getUndoTotal() const
{
	return undoStack.getSize();
}

int StackExchange::getRedoTotal() const
{
	return redoStack.getSize();
}

int StackExchange::getTotal() const
{
	return nodeTotal;
}

void StackExchange::showTotal() const
{
	std::cout << "The undoStack has " << getUndoTotal() << " nodes" << std::endl;
	std::cout << "The redoStack has " << getRedoTotal() << " nodes" << std::endl;
	std::cout << "In total there are total of " << nodeTotal << " node" << std::endl;
}