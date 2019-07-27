// LinkedList.h - template version
// Solution for Lab 2, ICT2421 Advanced Programming
// provided by Edmund CHIU, IVE(TY)

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <cassert>
using namespace std;

template <class Type>
struct node {
	Type data;
	node<Type> *next;
};

template <class Type>
class LinkedList {
	template <class Type>
	friend ostream& operator<< (ostream&, const LinkedList<Type>&);
public:
	const LinkedList<Type>& operator= (const LinkedList<Type>&);
	LinkedList();
	LinkedList(const LinkedList<Type>&);
	~LinkedList();
	void push_front(const Type &);
	void push_back(const Type &);
	void pop_front();
	void pop_back();
	Type front() const;
	Type back() const;
	bool empty() const;
	int size() const;
	void print() const;

	Type get(int n) const;
	void insert(int, const Type &item);
	void erase(int);

private:
	node<Type> *head;
	node<Type> *tail;
	int count;
	void copyList(const LinkedList<Type> &);
	void destroyList();
};

template <class Type>
LinkedList<Type>::LinkedList() { //default constructor
	head = NULL;
	tail = NULL;
	count = 0;
}

template <class Type>
bool LinkedList<Type>::empty() const {
	return count == 0;
}

template <class Type>
int LinkedList<Type>::size() const {
	return count;
}

template <class Type>
void LinkedList<Type>::push_front(const Type& item) {
	node<Type> *newNode = new node<Type>;
	newNode->data = item;
	newNode->next = head;
	if (empty())
		head = tail = newNode;
	else
		head = newNode;

	count++; //increment count
}

template <class Type>
void LinkedList<Type>::push_back(const Type& item) {
	node<Type> *newNode = new node<Type>;
	newNode->data = item;
	newNode->next = NULL;
	if (empty())
		head = tail = newNode;
	else {
		tail->next = newNode;
		tail = newNode;
	}
	count++; //increment count
}

template <class Type>
Type LinkedList<Type>::front() const {
	return head->data;
}//end front

template <class Type>
Type LinkedList<Type>::back() const {
	return tail->data;
}//end back

template <class Type>
void LinkedList<Type>::pop_front() {
	assert(!empty()); // stops program if parameter is false
	node<Type> *temp = head;
	if (count == 1)
		head = tail = NULL;
	else
		head = head->next;
	count--; //decrement count
	delete temp;
}

template <class Type>
void LinkedList<Type>::pop_back() {
	assert(!empty()); // stops program if parameter is false
	node<Type> *temp = tail;
	if (count == 1) {
		head = tail = NULL;
	}
	else {
		node<Type> *current = head;
		while (current->next != tail)
			current = current->next;
		tail = current;
		tail->next = NULL;
	}
	count--; //decrement count
	delete temp;
}

template <class Type>
void LinkedList<Type>::print() const {
	cout << "[ ";
	node<Type> *current; //pointer for traversal
	current = head; //set current to point to head
	while (current != NULL) { // loop till end of list
		cout << current->data << " ";
		current = current->next;
	}
	cout << "]";
} //end print

template <class Type> void LinkedList<Type>::destroyList() {
	node<Type> *temp; // pointer for deallocation
	while (head != NULL) {
		temp = head;
		head = head->next;
		delete temp;
	}
	tail = NULL; // set last to NULL
	count = 0;
}

template <class Type>
LinkedList<Type>::~LinkedList() { destroyList(); }

template <class Type>
void LinkedList<Type>::copyList(const LinkedList<Type>& otherList) {
	node<Type> *newNode; //pointer to create a node
	node<Type> *current; //pointer to traverse the list
	if (head != NULL) destroyList(); // empty the list first
	if (otherList.head == NULL) {//otherList is empty
		head = tail = NULL;
		count = 0;
	}
	else {
		current = otherList.head; //current points to list head
		count = otherList.count; // copy list length
		head = new node<Type>;  //create the node
		head->data = current->data; //copy the data
		head->next = NULL; //set next node to NULL
		tail = head; //set last node to current node
		current = current->next; // move current to next node
		while (current != NULL) { // other nodes in list
			newNode = new node<Type>;  //create a node
			newNode->data = current->data; //copy the data
			newNode->next = NULL; //set next node to NULL
			tail->next = newNode;  //attach newNode at the end
			tail = newNode; //make tail to point to last node
			current = current->next; //move current to next node
		}//end while
	}//end else
}//end copyList

template <class Type>
LinkedList<Type>::LinkedList
(const LinkedList<Type>& otherList) {
	head = NULL;
	copyList(otherList);
}

template <class Type>
const LinkedList<Type>& LinkedList<Type>::operator= (const LinkedList<Type>& otherList) {
	if (this != &otherList) copyList(otherList);
	return *this;
}

template <class Type> Type LinkedList<Type>::get(int n) const {
	if (n < 1 || n > count) {
		return NULL;
	}
	node<Type> *findNode = head->next;
	for (int i = 1; i < n - 1; i++) {
		findNode = findNode->next;
	}
	return findNode->data;
}

template <class Type> void LinkedList<Type>::insert(int n, const Type &item) {
	// special treatment for inserting as the first node (pos <= 1)
	if (n <= 1) {
		push_front(item);
		return;
		// special treatment for inserting as the last node (pos > length)
	}
	else if (n > count) {
		push_back(item);
		return;
	}
	node<Type> *findNode = head->next;
	for (int i = 1; i < n - 2; i++) {
		findNode = findNode->next;
	}
	node<Type> *newNode = new node<Type>;
	newNode->data = item;
	newNode->next = findNode->next;
	findNode->next = newNode;
	count++;
}

template <class Type> void LinkedList<Type>::erase(int n) {
	assert(n > 0 && n <= count);
	node<Type> *findNode = head->next;
	for (int i = 1; i < n - 2; i++) {
		findNode = findNode->next;
	}
	node<Type> *temp = findNode->next;
	findNode->next = findNode->next->next;
	delete temp;
	count--;
}

template <class Type> ostream& operator<< (ostream& os, const LinkedList<Type>& list) {
	os << "[ ";
	node<Type> *current; //pointer for traversal
	current = list.head; //set current to point to head
	while (current != NULL) { // loop till end of list
		os << current->data << " ";
		current = current->next;
	}
	os << "]";
	return os;
}
#endif

