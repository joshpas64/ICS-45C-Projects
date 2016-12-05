#include "CommandStack.hpp"

CommandStack::CommandStack() 
{
	top = nullptr; //Since no commands have been pushed, or might never be pushed have top be nullptr by default
	isEmpty = true; //Since empty has no nodes 
	currentSize = 0;
}

CommandStack::~CommandStack()
{
	clear(); // clear() sets a commandstack to the state it was at in initialization, the one thing is that there is still a pointer left, in case a command is pushed
	// Since we are going out of scope or '~destructing', no commands will ever be pushed and the ptr can be deleted
	delete top;
}

int CommandStack::getSize() const
{
	return currentSize;
}

bool CommandStack::isEmptyStack() const
{
	if(isEmpty && currentSize == 0)
		return true;
	return false;
}

void CommandStack::push(CommandStack::Node* node)
{
	if(!isEmpty) //When not empty
	{
		CommandStack::Node *tempNode = top; //make a new Node ptr that points to top's contents
		top->isTop = false; //Since the current top will now be the second to first Node, it is not the Top node
		top = node; //make top pointer point to contents of node param
		top->prev = tempNode; //have new top point to old top
	}
	else //case of an empty stack
	{
		top = node; //top now points to
		top->prev = nullptr; //This will denote its status as the first Node in the stack, (i.e. last to be popped)
		isEmpty = false; //No longer an empty stack
	}
	currentSize++; //Stack has one more node than before
}
void CommandStack::push(Command* command) //Push a command to stack
{
	CommandStack::Node *newNode = new CommandStack::Node{command,true,nullptr}; //Since stack can only Nodes as iterable objects, make this command into a Node, 
	// since it will be the top node set its isTop attribute to true, since only one command, just have it point to null for now
	push(newNode); 
}

void CommandStack::exchange(CommandStack &redoStack, bool toDo) //The method that will do the real history or command exchange between undo's and redo's
{
	if(toDo) // Undo()
	{
		CommandStack::Node* tempNode = pop(); //Pop a node from """this""" object
		if(tempNode == nullptr) //If it was an empty stack nothing to do, just retun
			return;
		redoStack.push(tempNode); //push the node out of 'this' CommandStack and into the redoStack
	}
	else //Redo() 
	// Essentially the same as undo() but with operands in the reverse order, push a Node from redoStack into 'this' CommandStack
	{
		CommandStack::Node* tempNode = redoStack.pop();
		if(tempNode == nullptr)
			return;
		push(tempNode);
	}
}

Command* CommandStack::getTopCommand() //Used for actual Command execution, mainly to account for cases where the commmand may throw exception
{
	if(top == nullptr)
		return nullptr;
	else
	{
		return top->currCommand; //Get top Node's command attribute
	}
}

CommandStack::Node* CommandStack::pop()
{
	if(top == nullptr) //if null, nothing to do , return
		return nullptr;
	CommandStack::Node* tempNode = top; //Have a newNode object refer to contents of the current top pointer
	top = tempNode->prev; //top will now point to contents of the Node in its prev attribute
	currentSize--; //Stack has one less Node now
	if(top == nullptr) //If there was only Node in the stack
	{
		isEmpty = true; //Now an empty stack now
		return tempNode; //Can just return the Node and exit function call
	}
	//in cases where there are still node left  behind
	top->isTop = true; //Mark new top pointer as the now ACTUAL TOP
	tempNode->prev = nullptr; //For this case the returned node, should have no association anymore with the stack it came from when its returned and exits a scope
	//So have prev attribute be null
	return tempNode; 
}

void CommandStack::clear()
{
	CommandStack::Node *currNode = pop(); //Iteratively pop all Nodes
	CommandStack::Node *prevNode = nullptr; //Have a reference to the current Node before moving to the next node in stack
	if(currNode == nullptr) //When a stack is already empty
	{
		delete prevNode;//need for prevNode is now gone, so delete it
	}

	while(currNode != nullptr)
	{
		prevNode = currNode; //keep a trace to the old Node
		currNode = pop(); //Make a reference to the next node in the stack
		delete prevNode->currCommand; //Since node's also have pointers in them, Command pointers must be deleted before deleting Node
		delete prevNode;
	}
	top = currNode; //top = nullptr making it back to state it had when initialized with CommandStack()
}