#include <iostream>
#include <string>

#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP
class LinkedList
{
private:
	int length;
	struct Node
	{
		std::string data;
		Node* next;
	};
	Node* head;
	Node* tail;

public:
	LinkedList();
	LinkedList(std::string datas);
	LinkedList(Node* node);
	LinkedList(const LinkedList &lists);
	~LinkedList();
	//LinkedList& operator=(const LinkedList &lists);
	int findNodeIndex(std::string datas) const;
	std::string findNodeval(int index) const;
	Node* findNode(int index) const;
	int getLength() const;
	void addNode(Node* node);
	void addNode(std::string data);
	void reverseList(void);
	void removewData(std::string datas);
	void addfrom(const LinkedList &lists);
	void addfrom(const LinkedList &lists, int filter);
	void output() const;
	//void addfrom(const LinkedList &lists, bool move);
	//void addfrom(const LinkedList &lists,int filter, bool move);
};
#endif