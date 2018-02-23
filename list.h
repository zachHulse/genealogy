/****************************************
* Module:
*   list.h
* Author:
*   Zachary Hulse
* Summary:
*   This is my implementation of the linked list
*   abstract data type.
*****************************************/
#pragma once

#include <iostream>
#include <cassert>

using namespace std;

// class for a single node in a linked list
template<class T>
class Node
{

public:
	T data;
	Node<T> * pNext;
	Node<T> * pPrevious;
	Node<T> * father;
	Node<T> * mother;
	Node() : pNext(NULL), pPrevious(NULL), father(NULL), mother(NULL), data(T()) { }
	Node(T data) : pNext(NULL), pPrevious(NULL), father(NULL), mother(NULL) { this->data = data; }
};

/***********************************************
* FREE DATA
* Free up the memory allocated for a given linked list
**********************************************/
template<class T>
void freeData(Node<T>*  &first)
{
	if (first != NULL)
	{
		freeData(first->pNext);
		delete first;
		first = NULL;
	}
	else
		return;
}

// forward definition of list iterator
template <class T>
class ListIterator;

// class implementing the concept of a doubly linked list
template<class T>
class List
{
private:
	Node<T>* head;
	Node<T>* tail;
	int numNodes;

public:
	List() :numNodes(0), head(NULL), tail(NULL) {}
	List(const List<T>& rhs);
	~List() { clear(); }
	List<T>& operator=(const List<T>& rhs);
	bool empty() { return numNodes == 0; }
	int size() { return numNodes; }
	void clear() { freeData(head); head = NULL; tail = NULL; numNodes = 0; }
	void remove(ListIterator<T> it) throw(const char *);
	void push_back(T item) throw(const char *);
	void push_front(T item) throw(const char *);
	ListIterator<T> insert(ListIterator<T> it, T item) throw(const char *);
	T& front() throw(const char *);
	T& back() throw(const char *);

	// return an iterator to the beginning of the list
	ListIterator <T> begin() { return ListIterator<T>(head); }

	// return an iterator to the end of the list
	ListIterator <T> end() { return ListIterator<T>(NULL); }

	ListIterator <T> rbegin() { return ListIterator<T>(tail); }
	ListIterator <T> rend() { return ListIterator<T>(NULL); }

};

/**************************************************
* List ITERATOR
* An iterator through list
*************************************************/
template <class T>
class ListIterator
{
public:
	// default constructor
	ListIterator() : p(NULL) {}

	// initialize to direct p to some item
	ListIterator(Node<T> * p) : p(p) {}

	// copy constructor
	ListIterator(const ListIterator<T> & rhs) { *this = rhs; }

	friend ListIterator<T> List<T>::insert(ListIterator<T> it, T item) throw(const char *);
	friend void List<T>::remove(ListIterator<T> it) throw(const char *);

	// assignment operator
	ListIterator & operator = (const ListIterator<T> & rhs)
	{
		this->p = rhs.p;
		return *this;
	}

	// not equals operator
	bool operator != (const ListIterator<T> & rhs) const
	{
		return rhs.p != this->p;
	}

	// dereference operator
	T & operator * ()
	{
		return p->data;
	}

	// prefix increment
	ListIterator <T> & operator ++ ()
	{
		p = p->pNext;
		return *this;
	}

	// postfix increment
	ListIterator <T> operator++(int postfix)
	{
		ListIterator<T> tmp(*this);
		p = p->pNext;
		return tmp;
	}

	// prefix increment
	ListIterator <T> & operator -- ()
	{
		p = p->pPrevious;
		return *this;
	}

	// postfix increment
	ListIterator <T> operator--(int postfix)
	{
		ListIterator<T> tmp(*this);
		p = p->pPrevious;
		return tmp;
	}

public:
	Node<T>* p;
};


/**************************************************
* COPY CONSTRUCTOR
*************************************************/
template<class T>
List<T>::List(const List<T>& rhs)
{
	*this = rhs;
}

/**************************************************
*ASSIGNMENT OPERATOR
*************************************************/
template<class T>
List<T>& List<T>::operator=(const List<T>& rhs)
{
	clear();
	if (rhs.head != NULL)
	{
		Node<T>* current = rhs.head;

		while (current)
		{
			push_back(current->data);
			current = current->pNext;
		}
	}
	return *this;
}

/**************************************************
* LIST::REMOVE
* Removes a single node from the list
*************************************************/
template<class T>
void List<T>::remove(ListIterator<T> it) throw(const char *)
{
	if (it.p == NULL)
	{
		throw "ERROR: unable to remove from an invalid location in a list";
	}
	else if (it.p == head)
	{
		head = it.p->pNext;
		head->pPrevious = NULL;
		delete it.p;
	}
	else if (it.p == tail)
	{
		tail = it.p->pPrevious;
		tail->pNext = NULL;
		delete it.p;
	}
	else
	{
		it.p->pPrevious->pNext = it.p->pNext;
		it.p->pNext->pPrevious = it.p->pPrevious;
		delete it.p;
	}
	numNodes--;

}

/**************************************************
* LIST::PUSH_BACK
* Insert an item at the back of the list
*************************************************/
template<class T>
void List<T>::push_back(T item) throw(const char *)
{
	try
	{
		Node<T>* temp = new Node<T>(item);
		if (head == NULL)
		{
			head = temp;
			tail = temp;
		}
		else
		{
			tail->pNext = temp;
			temp->pPrevious = tail;
			tail = temp;
		}
		numNodes++;
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: Unable to allocate a new Node for List";
	}

}


/**************************************************
* LIST::PUSH_FRONT
* Insert an item at the front of the list
*************************************************/
template<class T>
void List<T>::push_front(T item) throw(const char *)
{
	try
	{
		Node<T>* temp = new Node<T>(item);
		if (head == NULL)
		{
			head = temp;
			tail = temp;
		}
		else
		{
			head->pPrevious = temp;
			temp->pNext = head;
			head = temp;
		}
		numNodes++;
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: Unable to allocate a new Node for List";
	}
}


/**************************************************
* LIST::INSERT
* Insert an item in the middle of the list
*************************************************/
template<class T>
ListIterator<T> List<T>::insert(ListIterator<T> it, T item) throw(const char *)
{
	try
	{
		Node<T>* temp = new Node<T>(item);
		if (it.p == head)
		{
			push_front(item);
			it = ListIterator<T>(head);
		}
		else if (it.p == NULL)
		{
			push_back(item);
			it = ListIterator<T>(tail);
		}
		else
		{
			temp->pPrevious = it.p->pPrevious;
			temp->pNext = it.p;
			temp->pPrevious->pNext = temp;
			it.p->pPrevious = temp;
			numNodes++;
			it.p = temp;
		}
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: Unable to allocate a new Node for List";
	}
	return it;
}

/**************************************************
* LIST::FRONT
* returns the first item in a list by reference
*************************************************/
template<class T>
T & List<T>::front() throw(const char *)
{
	if (numNodes == 0)
		throw "ERROR: unable to access data from an empty list";
	else
		return head->data;
}

/**************************************************
* LIST::BACK
* returns the last item in a list by reference
*************************************************/
template<class T>
T & List<T>::back() throw(const char *)
{
	if (numNodes == 0)
		throw "ERROR: unable to access data from an empty list";
	else
		return tail->data;
}

/**************************************************
* SORT INSERTION
* inserts an item into an already sorted linked list
*************************************************/
template<class T>
void sortInsertion(List<T>& list, T item)
{
	if (list.empty())
	{
		//cerr << "we have an empty list\n"; 
		list.push_front(item);
		return;
	}
	ListIterator<T> it;
	for (it = list.begin(); it != list.end(); it++)
	{

		if (item < *it)
		{
			//cerr << "we have found where the item goes somewhere before the end\n";
			list.insert(it, item);
			return;
		}
	}
	//cerr << "the item will be inserted at the end\n";
	list.push_back(item);
}


