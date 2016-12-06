#include "Stacks.hpp"
#include <sstream>
typedef Stacks::Node Node;

Stacks::Stacks()
{
	top = nullptr;
	hasTop = false;
	currentLength = 0;
}

Stacks::Stacks(Node *node)
{
	hasTop = true;
	currentLength = 1;
	makeCopyNode(top, node);
	top->isTop = true;
	top->prev = nullptr;
}

Stacks::~Stacks()
{
	clear();
	delete top;
}

bool Stacks::isEmpty() const
{
	if(top == nullptr && currentLength == 0)
		return true;
	return false;
}
int Stacks::getSize() const
{
	return currentLength;
}

Node* Stacks::getTop() const
{
	return top;
}

std::string Stacks::getTopData()
{
	if(!hasTop)
		return "This is an empty stack";
	return top->someData;
}

int Stacks::getTopDigits() const
{
	if(!hasTop)
		return 0;
	return top->someDigit;
}

Node* Stacks::pop()
{
	if (top == nullptr)
		return nullptr;
	Node* tempNode = top;
	top = tempNode->prev;
	currentLength--;
	if(top == nullptr)
	{
		hasTop = false;
		return tempNode;
	}
	top->isTop = true;
	tempNode->prev = nullptr;
	tempNode->isTop = false;
	return tempNode;
}

void Stacks::push(Node *node)
{
	if(!hasTop)
	{
		top = node;
		top->prev = nullptr;
		top->isTop = true;
		hasTop = true;
		currentLength++;
		return;
	}
	Node* tempNode = top;
	top->isTop = false;
	top = node;
	top->prev = tempNode;
	top->isTop = true;
	currentLength++;
}

void Stacks::push(const std::string &data, int number)
{
	Node* newNode = new Node{data,number,true,nullptr};
	if(!hasTop)
	{
		top = newNode;
		top->prev = nullptr;
		top->isTop = true;
		hasTop = true;
		currentLength++;
		return;
	}
	Node* tempNode = top;
	top->isTop = false;
	top = newNode;
	top->prev = tempNode;
	currentLength++;
}

void Stacks::exchange(Stacks &pushStack, bool order)
{
	if(order)
	{
		Node *tempNode = pop();
		if(tempNode == nullptr)
			return;
		pushStack.push(tempNode);
	}
	else
	{
		Node *tempNode = pushStack.pop();
		if(tempNode == nullptr)
			return;
		push(tempNode);
	}
}

void Stacks::clear()
{
	Node* currNode = pop();
	Node* tempNode = nullptr;
	while(currNode != nullptr)
	{
		tempNode = currNode;
		currNode = pop();
		delete tempNode;
	}
	top = currNode;
}

std::string Stacks::toString() const
{
	std::string stackString = "";
	Node *currNode = getTop();
	if(currNode != nullptr && currNode->isTop)
		stackString += "This Node is top node, meaning it is the first to get popped\n";
	while(currNode != nullptr)
	{
		std::string currString = "Node's Title: " + currNode->someData + " Node's Digits: " + std::to_string(currNode->someDigit) + "\n";
		currString += "This Node will be the next Node to be popped after the above node\nThe node after this node is shown below\n";
		stackString += currString;
		currNode = currNode->prev;
	}
	stackString += "Well I guess that is the end, if you get here you have nothing to pop from an empty Stack!\n";
	return stackString;
}

void Stacks::makeCopyNode(Node *nodeTo, Node *nodeFrom)
{
	nodeTo->someData = nodeFrom->someData;
	nodeTo->someDigit = nodeFrom->someDigit;
}
