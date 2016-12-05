#ifndef COMMANDSTACK_HPP
#define COMMANDSTACK_HPP

#include "Command.hpp"
//******************************************Student Joshua : Comment ***************************************************************
//This is my implementation of the stack data structure needed in Interaction processor.run() to properly keep an ordered FIFO history of undo and redo commands
// Obviously when a new command is inserted during this process redoStack is reset or 'cleared'
class CommandStack
{
private:
	int currentSize; //Length of stack
	struct Node //Command stack pop's commands other attributes are just related to it being part of a stack class
	{
		Command* currCommand; //Comand in Node
		bool isTop; //status as top Node
		Node* prev; //Pointer to previous Node, or Command
	};
	Node* top; //Top node that is returned from a pop
	bool isEmpty; //Checks if it is empty
public:
	CommandStack(); //Initialize all private fields
	~CommandStack(); //Needs a destructor since handles with pointer objects
	void push(Command* command); //Push a command into the Stack, method will make a node with passed Command and push that Node
	// This is because outside programs cannot access Node objects directly or PUBLICLY
	void push(Node* node); //Push into stack, making it the top Node
	Node* pop(); //Return top Node
	Command* getTopCommand(); //Get pointer to command object but to not pop from stack, at least not yet in this case
	void clear(); //Remove all contents of the stack, including commands in  a way that does not leak memory
	void exchange(CommandStack &redoStack, bool toDo);
	int getSize() const; //Get stack's length
	bool isEmptyStack() const; //See if stackk is Empty
};
// **************************************Commend End **********************************************************************************

#endif