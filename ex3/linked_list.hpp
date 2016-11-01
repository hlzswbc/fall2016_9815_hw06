// linked_list.hpp
//
// data structure for linked list
//
// 10/28/16
//
// by Bingcheng Wang and Chendi Zhang

#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <memory>
#include <iostream>

template<typename T> 
class Node;
template<typename T>
class Dnode;
template<typename T> 
using ptr = std::shared_ptr<Node<T>>;
template<typename T>
using Dptr = std::shared_ptr<Dnode<T>>;

// class Node
template<typename T>
class Node {
private:
	T _data;                   // member data
	ptr<T> _next;              // pointer to next
public:
	Node() {}                                                     // default ctor
	Node(const Node<T>& nd) : _data(nd._data), _next(nd._next){}   // copy ctor
	Node(const T& d) : _data(d) {}                                // ctor with a parameter
	virtual ~Node() {}                                            // dtor
	void data(const T& d) { _data = d; }              // setter for data
	T& data() { return _data; }                       // getter for data
	void next(const ptr<T>& nd) { _next = nd; }              // setter for next
	ptr<T> next() const { return _next; }                // getter for next
	Node<T>& operator=(const Node<T>& nd) {                 // copy assignment
		if (this != &nd) {
			_data = nd.data();
			_next = nd.next();
		}
		return *this;
	}
	Node<T>& operator=(const T& d) {                 // assignment
		_data = d;
		return *this;
	}
	operator T() { return _data; }                  // return data;
};

// class ListIterator
template<typename T>
class ListIterator {
private:
	ptr<T> _it;             // member data
public:
	ListIterator();                             // default ctor
	ListIterator(const ListIterator<T>& it);    // copy ctor
	ListIterator(const ptr<T>& it);              // ctor with a parameter
	virtual ~ListIterator();                         // dtor
	ListIterator<T>& operator=(const ListIterator<T>& it);  // copy assignment
	bool HasNext() const;  // Return whether there is another element to return in this iterator
	Node<T> Next() const;        // Return the next element in this iterator
	ListIterator<T>& operator++();    // increase operator (prefix)
	ListIterator<T> operator++(int);  // increase operator (postfix)
	bool operator == (const ListIterator& it) const;  // judge if two iterators are the same
	bool operator != (const ListIterator& it) const;  // judge if two iterators are the same
	ptr<T> GetPointer() const;               // get the smart pointer
	Node<T>& operator*() const;              // dereference
	Node<T>* operator->() const;             // dereference
	operator bool() const;  // Return whether this iterator is empty
};


// class LinkedList
template<typename T>
class LinkedList {
private:
	ListIterator<T> _head;          // head iterator
public:
	LinkedList();                        // default ctor
	LinkedList(const LinkedList<T>& ll);    // copy ctor
	virtual ~LinkedList();               // dtor
	LinkedList<T>& operator=(const LinkedList<T>& ll);   // copy assignment
	void Add(T value);                       // Add the specified element at the end of the list
	void Push_front(T value);                // Add the specified element at the front of the list
	void Insert(T value, int index);         // Add the specified element at the specified index
	T Get(int index) const;                        // Get the element at the specified index
	int IndexOf(T value) const; // Retrieve the first index of the specified element (-1 if it does not exist in the list)
	T Remove(int index);  // Remove the element at the specified index and return it
	ListIterator<T> Iterator() const;  // Return an iterator on this list
	int Size() const;  // Return the size of the list
};

// class Dnode
template<typename T>
class Dnode : public Node<T> {
private:
	Dptr<T> _prev;              // pointer to prev
	Dptr<T> _next;              // pointer to next
public:
	Dnode():Node<T>() {}                                                             // default ctor
	Dnode(const Dnode<T>& nd) : Node<T>(nd), _next(nd._next), _prev(nd._prev) {}   // copy ctor
	Dnode(const T& d): Node<T>(d) {}                                               // ctor with a parameter
	virtual ~Dnode() {}                                                     // dtor
	void prev(const Dptr<T>& nd) { _prev = nd; }              // setter for prev
	Dptr<T> prev() const { return _prev; }                // getter for prev
	void next(const Dptr<T>& nd) { _next = nd; }              // setter for next
	Dptr<T> next() const { return _next; }                // getter for next
	Dnode<T>& operator=(const Dnode<T>& nd) {                 // copy assignment
		if (this != &nd) {
			Node<T>::operator==(nd);
			this->data(nd.data());
			_next = nd.next();
			_prev = nd.prev();
		}
		return *this;
	}
	Dnode<T>& operator=(const T& d) {                 // assignment
		Node<T>::operator==(d);
		return *this;
	}
};

// class DlistIterator
template<typename T>
class DlistIterator {
private:
	Dptr<T> _it;             // member data
public:
	DlistIterator();                             // default ctor
	DlistIterator(const DlistIterator<T>& it);    // copy ctor
	DlistIterator(const Dptr<T>& it);              // ctor with a parameter
	virtual ~DlistIterator();                         // dtor
	DlistIterator<T>& operator=(const DlistIterator<T>& it);  // copy assignment
	bool HasNext() const;  // Return whether there is next element to return in this iterator
	bool HasPrev() const;  // Return whether there is previous element to return in this iterator
	Dnode<T> Next() const;        // Return the next element in this iterator
	Dnode<T> Prev() const;        // Return the previous element in this iterator
	DlistIterator<T>& operator++();    // increase operator (prefix)
	DlistIterator<T> operator++(int);  // increase operator (postfix)
	DlistIterator<T>& operator--();    // decrease operator (prefix)
	DlistIterator<T> operator--(int);  // decrease operator (postfix)
	bool operator == (const DlistIterator& it) const;  // judge if two iterators are the same
	bool operator != (const DlistIterator& it) const;  // judge if two iterators are the same
	Dptr<T> GetPointer() const;               // get the smart pointer
	Dnode<T>& operator*() const;              // dereference
	Dnode<T>* operator->() const;             // dereference
	operator bool() const;  // Return whether this iterator is empty
};

// class DoublyLinkedList
template<typename T>
class DoublyLinkedList {
private:
	DlistIterator<T> _head;          // head iterator
	DlistIterator<T> _tail;          // tail iterator
public:
	DoublyLinkedList();                                 // default ctor
	DoublyLinkedList(const DoublyLinkedList<T>& ll);    // copy ctor
	virtual ~DoublyLinkedList();               // dtor
	DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& ll);   // copy assignment
	void Add(T value);                       // Add the specified element at the end of the list
	void Push_front(T value);                // Add the specified element at the front of the list
	void Insert(T value, int index);         // Add the specified element at the specified index
	T Get(int index) const;                        // Get the element at the specified index
	int IndexOf(T value) const; // Retrieve the left first index of the specified element (-1 if it does not exist in the list)
	T Remove(int index);  // Remove the element at the specified index and return it
	DlistIterator<T> Literator() const;  // Return a head iterator on this list
	DlistIterator<T> Riterator() const;  // Return a tail iterator on this list
	int Size() const;  // Return the size of the list
};


#ifndef LINKED_LIST_CPP
#include "linked_list.cpp"
#endif // !LINKED_LIST_CPP

#endif // !LINKED_LIST_HPP