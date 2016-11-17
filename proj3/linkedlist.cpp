#include "linkedlist.hpp"
LinkedList::LinkedList()
{
	length = 0;
	head = tail = nullptr;

}
LinkedList::LinkedList(std::string datas)
{
	head = new LinkedList::Node;
	head->data = datas;
	head->next = nullptr;
	tail = head;
	length =  1;
}
LinkedList::LinkedList(LinkedList::Node * node)
{
	head = node;
	LinkedList::Node *temp = new LinkedList::Node;
	int index = 1;
	temp = node->next;
	while(temp != nullptr)
	{
		temp = temp->next;
		index++;
	}
	length = index;
	tail = temp;
}
int LinkedList::getLength() const
{
	int size = 0;
	LinkedList::Node *node = head;
	while(node != nullptr)
	{
		size++;
		node = node->next;
	}
	return size;
}

void LinkedList::addNode(LinkedList::Node * node)
// Make tail's next value the new node instead of nullptr and make node the new tail
{
	tail->next = node;
	tail = tail->next;
}

void LinkedList::addNode(std::string data)
{
	LinkedList::Node* node = new LinkedList::Node;
	node->data = data;
	if(head == nullptr)
	{
		head = node;
		tail = node;
		tail->next = nullptr;
		head->next = tail->next;

	}
	else
	{
		node->next = nullptr;
		tail->next = node;
		tail = tail->next;

	}
}

std::string LinkedList::findNodeval(int index) const
{
	std::string result = "";
	const LinkedList::Node *start = head;
	int pos = 0;
	while(start != nullptr)
	{
		if(pos != index)
		{
			start = start->next;
			pos++;
		}
		else
			{
				result = start->data;
				return result;
			}
	}
	return result;
}

LinkedList::Node* LinkedList::findNode(int index) const
{
	LinkedList::Node *nodecpy = head;
	int pos = 0;
	if(index == pos)
		return nodecpy;
	while( nodecpy->next != nullptr && pos < index)
	{
		nodecpy = nodecpy->next;
		pos++;
	}
	if( pos < index)
		return nullptr;
	else
		return nodecpy;
}

int LinkedList::findNodeIndex(std::string datas) const
{
	int index = 0;
	const LinkedList::Node *start = head;
	while(start != nullptr)
	{
		if(start->data.compare(datas) == 0)
		{
			return index;
		}
		else
		{
		start = start->next;
		index++;
		}
	}
	return -1;
}

void LinkedList::reverseList(void)
{
	// temp is just some variable NODE not first or necessarily
	if(head == nullptr)
	{
		return;
	}
	LinkedList::Node* temp = head; //Head (1,2) needs to be (1,0)
	LinkedList::Node* temp2 = temp->next;
	if(temp2 == nullptr)
	{
		head = temp;
		tail = temp;
		return;
	} //temp2 is 2 : (2,3)
	temp->next = nullptr; //temp now is (1,0)
	tail = temp;
	LinkedList::Node* temp3 = temp2->next; //temp3 is 2+1=3 (3,4)
	if(temp3 == nullptr)
	{
		temp2->next = temp;
		head = temp2;
		return;
	}
	temp2->next = temp; //temp2 is now (2,1) 1: (1,0)
	temp = temp3; //(3,4)
	while(temp->next != nullptr)
	{
		temp3 = temp2; //temp3 is now temp2 (2,1) 1: (1,0) etc ALREADY SET SINCE JUST POINTERS
		temp2 = temp->next; //temp2  is now 3+1 = 4 : (4,5)
		temp->next = temp3; //temp is now (3,2)  and next which is now temp3 which is was the temp2 at ln 104 2,1,0
		temp3 = temp2->next; //temp3 can be reassigned now being 4+1: (5,6)
		temp2->next = temp; //temp2 is now (4,nxt) nxt is temp which is (3,temp2 at ln 104) so (3,2,1) now (4,3,2,1)
		temp = temp3; //temp3 is 3 : (3,4) temp NOW (5,6) //So end of list can be immediately checked
	}
	temp->next = temp2;
	head = temp;
}

LinkedList::~LinkedList()
{
	if(head == nullptr)
	{
		return;
	}
	LinkedList::Node* ptr = head;
	LinkedList::Node* temp = ptr->next;
	while(ptr != nullptr)
	{
		temp = ptr;
		ptr = ptr->next;
		delete temp;
	}
}

void LinkedList::removewData(std::string datas)
{
	if(head == nullptr)
	{
		return;
	}
	LinkedList::Node *prev = head;
	if(head->data.compare(datas) == 0)
	{
		if(head->next == nullptr)
		{
			delete prev;
			head = tail = nullptr;
			return;
		}
		else
		{
			head = head->next;
			delete prev;
			return;
		}
	}
	LinkedList::Node *node = prev;
	while(node != nullptr)
	{
		if(node->data.compare(datas) == 0)
		{
			if(node->next == nullptr)
			{
				prev->next = node->next;
				tail = prev;
				delete node;
				break;
			}
			else
			{
				prev->next = node->next;
				delete node;
				node = prev->next;
				break;
			}
		}
		else
		{
			prev = node;
			node = node->next;
		}
	}

}

void LinkedList::output(void) const
{
	if(head == nullptr)
	{
		return;
	}
	const LinkedList::Node* node = head;
	do
	{
		std::cout << node->data << std::endl;
		node = node->next;
	}
	while(node != nullptr);
}