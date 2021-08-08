// File contains the MyNode, MyList, Island, MyFNode and MyFList classes
// These files are used in the archipelago class
#pragma once
#include <cstdio>
#include <string>
using namespace std;
//  Code for the methods is the MyLNode class
//    These are the Node Level operations
//    Contains:
//      2 constructors
//      Getters and Setters for the 2 data members
class MyLNode
{
private:
	int elem;
	MyLNode *next;

public:
	MyLNode();
	MyLNode(int v1);
	MyLNode(int v1, MyLNode *n);
	void setElem(int e);
	int getElem();
	void setNext(MyLNode *n);
	MyLNode *getNext();
};
// default constructor
MyLNode::MyLNode()
{
	elem = -999;
	next = nullptr;
}
// parameterized constructor with int
MyLNode::MyLNode(int v1)
{
	elem = v1;
	next = nullptr;
}
// parameterized constructor with both int and node
MyLNode::MyLNode(int v1, MyLNode *n)
{
	elem = v1;
	next = n;
}
// function to set elem
void MyLNode::setElem(int e)
{
	elem = e;
}
// function to return elem
int MyLNode::getElem()
{
	return elem;
}
// function to set the next node
void MyLNode::setNext(MyLNode *n)
{
	next = n;
}
// function that return the next node
MyLNode *MyLNode::getNext()
{
	return next;
}

// MyList class
// This linked list class is used as a queue and a stack in the archipelago class
// This contains all of the operations and data for the list as a whole
// This class relies heavily on the MyLNode class
class MyList
{
private:
	MyLNode *head;
	void copyNode(MyLNode *pNode);

public:
	MyList();							// default constructor
	MyList(const MyList &p);			// copy constructor
	~MyList();							// destructor
	MyList &operator=(const MyList &p); //overloaded assignment operator

	void show(); // function to print the contents of list
	void insertAtFront(int v1);  // function to insert at front
	void insertAtEnd(int v1);  // function to insert at end of list
	void removeElem(int v1); // function to remove the given element
	void removeAll();  // removes everything from the linked list
	int getListLength();  // function to return the length of the list
	int getNthElem(int n);  // function returns the element at specified location
	bool doesE(int x);  // function checks if the given element is in the list
	int getVal(); // function returns the first element of list
	void removeFromFront(); // function removes from the front of list
	void showPath();  // function to print the path of list
	void makeCopy(const MyList &p);  // function to make copy of the list
	bool isEmpty();  // function to check if the list is empty
};

// MyList constructor
MyList::MyList()
{
	head = NULL;
}
// Copy constructor
MyList::MyList(const MyList &p)
{
	makeCopy(p); // This code does a Deep Copy
}
// MyList destructor
MyList::~MyList()
{
	MyLNode *curr = head;
	//	MyLNode* next = nullptr;
	while (curr != nullptr)
	{
		MyLNode *next = curr;
		curr = curr->getNext();
		delete (next);
	}
	head = nullptr;
	//printf ("In Destructor: ");
}
// the overloaded assignment operator
MyList &MyList::operator=(const MyList &p)
{
	if (this == &p)	  // both operands are the same
		return *this; //   do nothing, just return

	removeAll(); // Deallocate the existing list

	makeCopy(p); // Do a deep copy

	return *this; // allow for "cascading assignments":  a = b = c;
}
// Code to make a copy of a list - doing a Deep Copy
//   This code uses the recursive method of copyNode()
//   copyNode() should be private since it is intended to only
//   be called by makeCopy()
void MyList::makeCopy(const MyList &p)
{
	head = NULL;
	copyNode(p.head);
}
// private helper function to copy nodes
void MyList::copyNode(MyLNode *pNode)
{
	if (pNode != NULL)
	{
		copyNode(pNode->getNext());

		// insert nodes at the front of the list while returning
		//   from the recursive calls  (adds values to the front
		//   in reverse order - this copies the list on O(n) time
		head = new MyLNode(pNode->getElem(), head);
	}
}
// function checks if the list is empty
bool MyList::isEmpty()
{
	if (head == nullptr)
	{
		return true;
	}
	return false;
}
// method to print out all of the values in the list
void MyList::show()
{
	MyLNode *tmp = head;
	// loops through the list
	while (tmp != NULL)
	{
		// prints the elem if it's not nullptr
		if (tmp->getNext() != nullptr)
		{
			printf("%d  ", tmp->getElem());
		}
		else
		{
			printf("%d", tmp->getElem());
		}
		tmp = tmp->getNext();
	}
	printf("\n");
}
// method to print the path taken by an island
void MyList::showPath()
{
	MyLNode *tmp = head;

	while (tmp != NULL)
	{
		// prints the elem with -
		if (tmp->getNext() != nullptr)
		{
			printf("%d - ", tmp->getElem());
		}
		else
		{
			printf("%d", tmp->getElem());
		}
		tmp = tmp->getNext();
	}
	printf("\n");
}
// function returns the first value of list
int MyList::getVal()
{
	// return the element of head
	return head->getElem();
}
// function to insert at the front of list
void MyList::insertAtFront(int v1)
{
	// create a new node
	MyLNode *tmp = new MyLNode(v1);
	// this code just inserts the node at the beginning of the list
	tmp->setNext(head);
	head = tmp;
}
// function to insert at end of list
void MyList::insertAtEnd(int v1)
{
	MyLNode *tmp = new MyLNode(v1);
	MyLNode *curr = head;
	MyLNode *prev = nullptr;
	while (curr != nullptr)
	{
		prev = curr;
		curr = curr->getNext();
	}
	// set next of tmp to curr which is null
	tmp->setNext(curr);
	// make head temp if prev is null
	if (prev == nullptr)
	{
		head = tmp;
	}
	else
	{
		prev->setNext(tmp);
	}
}
// function to remove from the front of linked list
void MyList::removeFromFront()
{
	MyLNode *curr = head;
	head = curr->getNext();
	delete curr;
}
// function to remove given element
void MyList::removeElem(int v1)
{
	MyLNode *curr = head;
	MyLNode *prev = NULL;

	while ((curr != NULL) && (curr->getElem() != v1))
	{
		prev = curr;
		curr = curr->getNext();
	}

	if (curr == NULL) // v1 does not exist in list
		return;

	if (prev == NULL) // v1 is in first/head node in list
	{
		head = curr->getNext();
		delete curr;
	}
	else
	{
		prev->setNext(curr->getNext());
		delete curr;
	}
}

// remove all elements from the list
void MyList::removeAll()
{
	// loop through the list and delete curr node
	MyLNode *curr = head;
	while (curr != nullptr)
	{
		MyLNode *next = curr;
		curr = curr->getNext();
		delete (next);
	}
	head = nullptr;
}
// function to get the length of list
int MyList::getListLength()
{
	// loop through list and update length
	int length = 0;
	MyLNode *curr = head;

	while (curr != nullptr)
	{
		length++;
		curr = curr->getNext();
	}
	return length;
}
// function to get the Nth elem form the list
int MyList::getNthElem(int n)
{
	// loops through the list until we find the element in n
	MyLNode *curr = head;
	int length = 0;
	while (curr != nullptr)
	{
		if (length == n)
		{
			return curr->getElem();
		}
		length++;
		curr = curr->getNext();
	}
	return -999;
}
// checks if the element x is in the list
bool MyList::doesE(int x)
{
	// loops through the list until we find the elem x
	MyLNode *temp = head;
	while (temp != nullptr)
	{
		if (temp->getElem() == x)
			return true;
		temp = temp->getNext();
	}
	delete temp;
	return false;
}

// ISLAND CLASS
// Class uses the MyList and MyNode class to create an islandlist of edges
// for an island
class Island
{
private:
// variables to hold prev, visited, size and the islandlist
	bool visited;
	int prev;
	int size;
	MyList islandList;

public:
	Island(); // default constructor
	int getPrev(); // function returns the previous island
	void setPrev(int p); // function sets the previous island
	bool getVisited(); // function retuns the visited bool of island
	void setVisited(bool vis); // function to set the visited bool of island
	void insertEdgeTo(int x); // function to insert edge to an island
	void deleteEdgeTo(int x); // function delete edge to an island
	int getSize(); // function returns the size of islandlist
	MyList getList(); // function returns the islandlist
	bool doesExist(int x); // function to check if island exists in islandlist
};
// constructor
Island::Island()
{
	visited = false;
	prev = -1;
	size = 0;
	//islandList = MyList();
}
// getPrev
int Island::getPrev()
{
	return prev;
}
// setPrev
void Island::setPrev(int p)
{
	prev = p;
}
// getVisited
bool Island::getVisited()
{
	return visited;
}
// setVisited
void Island::setVisited(bool v)
{
	visited = v;
}
// insertEdgeTo
void Island::insertEdgeTo(int x)
{
	islandList.insertAtEnd(x);
	size++;
}
// deleteEdgeTo
void Island::deleteEdgeTo(int x)
{
	islandList.removeElem(x);
	size--;
}
// size
int Island::getSize()
{
	return size;
}
// getList
MyList Island::getList()
{
	return islandList;
}
// function to check if island exists in islandlist
bool Island::doesExist(int x)
{
	// calls the doesE function from MyList
	if (islandList.doesE(x))
		return true;
	else
		return false;
}

//  Code for the methods is the MyFLNode class
//    These are the Node Level operations
//    Contains:
//      2 constructors
//      Getters and Setters for the 2 data members
// Class is used for the files in archipelago class
class MyFLNode
{
private:
	string elem;
	MyFLNode *next;

public:
	MyFLNode(string v1); // constructor that sets string elem
	MyFLNode(string v1, MyFLNode *n); // constructor that sets string elem and node

	void setElem(string e); // function to set string elem
	string getElem(); // function to return the string elem
	void setNext(MyFLNode *n); // function the sets the next of node
	MyFLNode *getNext(); // function returns the next of node
};
// constructor
MyFLNode::MyFLNode(string v1)
{
	elem = v1;
	next = NULL;
}
// constructor that sets string elem and node
MyFLNode::MyFLNode(string v1, MyFLNode *n)
{
	elem = v1;
	next = n;
}
// function to set string elem
void MyFLNode::setElem(string e)
{
	elem = e;
}
// function to return the string elem
string MyFLNode::getElem()
{
	return elem;
}
// function the sets the next of node
void MyFLNode::setNext(MyFLNode *n)
{
	next = n;
}
// function returns the next of node
MyFLNode *MyFLNode::getNext()
{
	return next;
}

// MyFList 
// the list class for the linked list
//  This contains all of the operations and data for the
//  list as a whole
//  This class relies heavily on the MyFLNode class
// List class for the files
class MyFList
{
private:
	MyFLNode *head;
	void copyNode(MyFLNode *pNode);

public:
	MyFList();							  // default constructor
	MyFList(const MyFList &p);			  // copy constructor
	~MyFList();							  // destructor
	MyFList &operator=(const MyFList &p); //overloaded assignment operator

	void insertAtEnd(string v1); // function to insert file at end of list
	void remove(string v1);  // function to remove the file
	void removeAll(); // function to remove all the files from list
	int getListLength(); // function to get length of list
	bool doesE(string x); // function to check is file exists in list
	string getVal(); // function that returns the string element
	void makeCopies(const MyFList &p);  // function to make copy of list
	bool isEmpty(); // function to check if list is empty
};

//  Methods for the MyList class
//    These are the List Level operations
MyFList::MyFList()
{
	head = NULL;
}
// copy constructor
MyFList::MyFList(const MyFList &p) //LINE 99
{
	makeCopies(p); // This code does a Deep Copy
}

// Code to make a copy of a list - doing a Deep Copy
//   This code uses the recursive method of copyNode()
//   copyNode() should be private since it is intended to only
//   be called by makeCopy()
void MyFList::makeCopies(const MyFList &p)
{
	head = NULL;
	copyNode(p.head);
}
// copy node function
void MyFList::copyNode(MyFLNode *pNode)
{
	if (pNode != NULL)
	{
		copyNode(pNode->getNext());

		// insert nodes at the front of the list while returning
		//   from the recursive calls  (adds values to the front
		//   in reverse order - this copies the list on O(n) time
		head = new MyFLNode(pNode->getElem(), head);
	}
}
// function the checks if list is empty
bool MyFList::isEmpty()
{
	if (head == nullptr)
	{
		return true;
	}
	return false;
}
// function to return the first elem in list
string MyFList::getVal()
{
	return head->getElem();
}
// function to insert at end of list
void MyFList::insertAtEnd(string v1)
{
	// loops till the end of list and adds it to end
	MyFLNode *tmp = new MyFLNode(v1);
	MyFLNode *curr = head;
	MyFLNode *prev = nullptr;
	while (curr != nullptr)
	{
		prev = curr;
		curr = curr->getNext();
	}
	tmp->setNext(curr);
	if (prev == nullptr)
	{
		head = tmp;
	}
	else
	{
		prev->setNext(tmp);
	}
}
// function removes the elem from list
void MyFList::remove(string v1)
{
	MyFLNode *curr = head;
	MyFLNode *prev = NULL;

	while ((curr != NULL) && (curr->getElem() != v1))
	{
		prev = curr;
		curr = curr->getNext();
	}
	if (curr == NULL) // v1 does not exist in list
		return;
	if (prev == NULL) // v1 is in first/head node in list
	{
		head = curr->getNext();
		delete curr;
	}
	else
	{
		prev->setNext(curr->getNext());
		delete curr;
	}
}
// function removes everything from the list
void MyFList::removeAll()
{
	MyFLNode *curr = head;
	MyFLNode *next = nullptr;
	while (curr != nullptr)
	{
		next = curr->getNext();
		delete (curr);
		curr = next;
	}
	head = nullptr;
}
// destructor
MyFList::~MyFList()
{
	MyFLNode *curr = head;
	while (curr != nullptr)
	{
		MyFLNode *next = curr;
		curr = curr->getNext();
		delete (next);
	}
	head = nullptr;
}
// function that returns the length of list
int MyFList::getListLength()
{
	int length = 0;
	MyFLNode *curr = head;

	while (curr != nullptr)
	{
		length++;
		curr = curr->getNext();
	}
	return length;
}
// function checks if the file exists in list
bool MyFList::doesE(string x)
{
	MyFLNode *temp = head;
	while (temp != nullptr)
	{
		if (temp->getElem().compare(x) == 0)
		{
			//printf("hidoese ");
			return true;
		}
		temp = temp->getNext();
	}
	return false;
}