// linked_list.cpp
//
// source file for data structure for linked list
//
// 10/28/16
//
// by Bingcheng Wang and Chendi Zhang

#ifndef LINKED_LIST_CPP
#define LINKED_LIST_CPP

#include <stdexcept>
#include "linked_list.hpp"

///////////////////////////////////////////////////////////
// class ListIterator & DlistIterator
///////////////////////////////////////////////////////////

// default ctor
template<typename T>
ListIterator<T>::ListIterator(): _it() {}

template<typename T>
DlistIterator<T>::DlistIterator() : _it() {}

// copy ctor
template<typename T>
ListIterator<T>::ListIterator(const ListIterator<T>& it) : _it(it._it) {}

template<typename T>
DlistIterator<T>::DlistIterator(const DlistIterator<T>& it) : _it(it._it) {}

// ctor with a parameter
template<typename T>
ListIterator<T>::ListIterator(const ptr<T>& it) : _it(it) {}

template<typename T>
DlistIterator<T>::DlistIterator(const Dptr<T>& it) : _it(it) {}

// dtor
template<typename T>
ListIterator<T>::~ListIterator() {}

template<typename T>
DlistIterator<T>::~DlistIterator() {}

// copy assignment
template<typename T>
ListIterator<T>& ListIterator<T>::operator=(const ListIterator<T>& it) {
	if (this != &it)
		_it = it._it;
	return *this;
}

template<typename T>
DlistIterator<T>& DlistIterator<T>::operator=(const DlistIterator<T>& it) {
	if (this != &it)
		_it = it._it;
	return *this;
}

// Return whether there is another element to return in this iterator
template<typename T>
bool ListIterator<T>::HasNext() const {
	return bool(_it->next());
}

template<typename T>
bool DlistIterator<T>::HasNext() const {
	return bool(_it->next());
}

template<typename T>
bool DlistIterator<T>::HasPrev() const {
	return bool(_it->prev());
}

// Return the next element in this iterator
template<typename T>
Node<T> ListIterator<T>::Next() const {
	if (!HasNext()) throw std::out_of_range("Iterator is Out of Range");
	return *(_it->next());
}

template<typename T>
Dnode<T> DlistIterator<T>::Next() const {
	if (!HasNext()) throw std::out_of_range("Iterator is Out of Range");
	return *(_it->next());
}

template<typename T>
Dnode<T> DlistIterator<T>::Prev() const {
	if (!HasPrev()) throw std::out_of_range("Iterator is Out of Range");
	return *(_it->prev());
}

// increase operator (prefix)
template<typename T>
ListIterator<T>& ListIterator<T>::operator++() {
	if (bool(!_it)) throw std::out_of_range("Iterator is Out of Range");
	_it = _it->next();
	return *this;
}

template<typename T>
DlistIterator<T>& DlistIterator<T>::operator++() {
	if (bool(!_it)) throw std::out_of_range("Iterator is Out of Range");
	_it = _it->next();
	return *this;
}

// increase operator (postfix)
template<typename T>
ListIterator<T> ListIterator<T>::operator++(int) {
	if (bool(!_it)) throw std::out_of_range("Iterator is Out of Range");
	ListIterator<T> temp = *this;
	_it = _it->next();
	return temp;
}

template<typename T>
DlistIterator<T> DlistIterator<T>::operator++(int) {
	if (bool(!_it)) throw std::out_of_range("Iterator is Out of Range");
	DlistIterator<T> temp = *this;
	_it = _it->next();
	return temp;
}

// decrease operator (prefix)
template<typename T>
DlistIterator<T>& DlistIterator<T>::operator--() {
	if (bool(!_it)) throw std::out_of_range("Iterator is Out of Range");
	_it = _it->prev();
	return *this;
}

// decrease operator (postfix)
template<typename T>
DlistIterator<T> DlistIterator<T>::operator--(int) {
	if (bool(!_it)) throw std::out_of_range("Iterator is Out of Range");
	DlistIterator<T> temp = *this;
	_it = _it->prev();
	return temp;
}

// judge if two iterators are the same
template<typename T>
bool ListIterator<T>::operator == (const ListIterator& it) const {
	return _it == it._it;
}

template<typename T>
bool DlistIterator<T>::operator == (const DlistIterator& it) const {
	return _it == it._it;
}

// judge if two iterators are the same
template<typename T>
bool ListIterator<T>::operator != (const ListIterator& it) const {
	return _it != (it._it);
}

template<typename T>
bool DlistIterator<T>::operator != (const DlistIterator& it) const {
	return _it != (it._it);
}

// dereference
template<typename T>
Node<T>& ListIterator<T>::operator*() const {
	return *_it;
}

template<typename T>
Dnode<T>& DlistIterator<T>::operator*() const {
	return *_it;
}

// dereference
template<typename T>
Node<T>* ListIterator<T>::operator->() const {
	return &this->operator*();
}

template<typename T>
Dnode<T>* DlistIterator<T>::operator->() const {
	return &this->operator*();
}

// Return whether this iterator is empty
template<typename T>
ListIterator<T>::operator bool() const {
	return bool(_it);
}

template<typename T>
DlistIterator<T>::operator bool() const {
	return bool(_it);
}

// get the smart pointer
template<typename T>
ptr<T> ListIterator<T>::GetPointer() const {
	return _it;
}

template<typename T>
Dptr<T> DlistIterator<T>::GetPointer() const {
	return _it;
}

///////////////////////////////////////////////////////////
// class LinkedList & DoublyLinkedList
///////////////////////////////////////////////////////////

// default ctor
template<typename T>
LinkedList<T>::LinkedList() {}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() {}

// copy ctor
template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& ll) {
	// build a new list
	auto it = ll._head;
	if (!bool(it)) return;  // null list
	auto sp = std::shared_ptr<Node<T>>(new Node<T>(it->data()));
	auto nit = _head = ListIterator<T>(sp);
	while (it.HasNext()) {
		sp = std::shared_ptr<Node<T>>(new Node<T>(it->next()->data()));
		nit->next(sp);
		++it;
		++nit;
	}
};

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& ll) {
	// build a new list
	auto it = ll._head;
	if (!bool(it)) return; // null list
	auto sp = std::shared_ptr<Dnode<T>>(new Dnode<T>(it->data()));
	auto nit = _head = DlistIterator<T>(sp);
	while (it.HasNext()) {
		sp = std::shared_ptr<Dnode<T>>(new Dnode<T>(it->next()->data()));
		nit->next(sp);
		sp->prev(nit.GetPointer());
		++it;
		++nit;
	}
	_tail = DlistIterator<T>(sp);
};

// dtor
template<typename T>
LinkedList<T>::~LinkedList() {}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {}

// copy assignment
template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& ll) {
	if (this != &ll) {
		auto it = ll._head;
		if (!bool(it)) {
			_head = ListIterator<T>();
			return *this;
		}
		auto sp = std::shared_ptr<Node<T>>(new Node<T>(it->data()));
		auto nit = _head = ListIterator<T>(sp);
		while (it.HasNext()) {
			sp = std::shared_ptr<Node<T>>(new Node<T>(it->next()->data()));
			nit->next(sp);
			++it;
			++nit;
		}
	}
	return *this;
}

template<typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& ll) {
	if (this != &ll) {
		// build a new list
		auto it = ll._head;
		if (!bool(it)) {
			_head = _tail = DlistIterator<T>();
			return *this;
		}
		auto sp = std::shared_ptr<Dnode<T>>(new Dnode<T>(it->data()));
		auto nit = _head = DlistIterator<T>(sp);
		while (it.HasNext()) {
			sp = std::shared_ptr<Dnode<T>>(new Dnode<T>(it->next()->data()));
			nit->next(sp);
			sp->prev(nit.GetPointer());
			++it;
			++nit;
		}
		_tail = DlistIterator<T>(sp);
	}		
	return *this;
}

// Add the specified element at the end of the list
template<typename T>
void LinkedList<T>::Add(T value) {
	ListIterator<T> it = _head;
	auto sp = std::shared_ptr<Node<T>>(new Node<T>(value));
	if (!bool(it)) {  // for a null list
		_head = ListIterator<T>(sp);
		return;
	}
	while (it.HasNext()) {
		++it;
	}
	it->next(sp);
}

template<typename T>
void DoublyLinkedList<T>::Add(T value) {
	auto sp = std::shared_ptr<Dnode<T>>(new Dnode<T>(value));
	sp->prev(_tail.GetPointer());   // backward
	_tail = DlistIterator<T>(sp);
	if (sp->prev())  // if previous node exists
		sp->prev()->next(sp); // farward
	else _head = DlistIterator<T>(sp);
}

// Add the specified element at the front of the list
template<typename T>
void LinkedList<T>::Push_front(T value) {
	auto sp = std::shared_ptr<Node<T>>(new Node<T>(value));
	sp->next(_head.GetPointer());
	_head = ListIterator<T>(sp);
}

template<typename T>
void DoublyLinkedList<T>::Push_front(T value) {
	auto sp = std::shared_ptr<Dnode<T>>(new Dnode<T>(value));
	sp->next(_head.GetPointer());   // forward
	_head = DlistIterator<T>(sp);
	if (bool(sp->next()))  // if next node exists
		sp->next()->prev(sp); // backward
	else _tail = DlistIterator<T>(sp);
}

// Add the specified element at the specified index
// If the index is larger than the size, add default nodes between them.
template<typename T>
void LinkedList<T>::Insert(T value, int index) {
	if(index < 0) throw std::out_of_range("Index is Out of Range");
	auto sp = std::shared_ptr<Node<T>>(new Node<T>(value));
	int i = 0;
	if (index == 0) { // insert at the beginning
		Push_front(value);
		return;
	}
	if (!bool(_head)) { // null list
		_head = ListIterator<T>(std::shared_ptr<Node<T>>(new Node<T>));
	}

	ListIterator<T> it = _head;
	while (it.HasNext() && i < index - 1) {
		++it;
		++i;
	}
	while (!it.HasNext() && i < index - 1) { // insert default nodes
		it->next(std::shared_ptr<Node<T>>(new Node<T>));
		++it;
		++i;
	}
	auto temp = it->next();
	it->next(sp);   // insert after index - 1
	sp->next(temp);
}

template<typename T>
void DoublyLinkedList<T>::Insert(T value, int index) {
	if (index < 0) throw std::out_of_range("Index is Out of Range");
	auto sp = std::shared_ptr<Dnode<T>>(new Dnode<T>(value));
	int i = 0;
	if (index == 0) { // insert at the beginning
		Push_front(value);
		return;
	}
	if (!bool(_head)) { // null list
		_head = _tail = DlistIterator<T>(std::shared_ptr<Dnode<T>>(new Dnode<T>));
	}

	DlistIterator<T> it = _head;
	while (it.HasNext() && i < index - 1) {
		++it;
		++i;
	}
	while (!it.HasNext() && i < index - 1) { // insert default nodes
		it->next(std::shared_ptr<Dnode<T>>(new Dnode<T>));
		_tail = it->next();
		_tail->prev(it.GetPointer());
		++it;
		++i;
	}
	auto temp = it->next();
	it->next(sp);   // insert after index - 1
	sp->prev(it.GetPointer());
	sp->next(temp);
	if (bool(temp)) temp->prev(sp);
	else _tail = DlistIterator<T>(sp);
}

// Get the element at the specified index
template<typename T>
T LinkedList<T>::Get(int index) const {
	if (index < 0) throw std::out_of_range("Index is Out of Range");
	ListIterator<T> it = _head;
	while (index-- && bool(it)) ++it;
	if(!bool(it)) throw std::out_of_range("Index is Out of Range");
	return it->data();
}

template<typename T>
T DoublyLinkedList<T>::Get(int index) const {
	if (index < 0) throw std::out_of_range("Index is Out of Range");
	DlistIterator<T> it = _head;
	while (index-- && bool(it)) ++it;
	if (!bool(it)) throw std::out_of_range("Index is Out of Range");
	return it->data();
}

// Retrieve the left first index of the specified element (-1 if it does not exist in the list)
template<typename T>
int LinkedList<T>::IndexOf(T value) const {
	ListIterator<T> it = _head;
	int index = 0;
	while (bool(it)) {
		if (it->data() == value) return index;
		++index;
		++it;
	}
	return -1;
}

template<typename T>
int DoublyLinkedList<T>::IndexOf(T value) const {
	DlistIterator<T> it = _head;
	int index = 0;
	while (bool(it)) {
		if (it->data() == value) return index;
		++index;
		++it;
	}
	return -1;
}

// Remove the element at the specified index and return it
template<typename T>
T LinkedList<T>::Remove(int index) {
	if (index < 0) throw std::out_of_range("Index is Out of Range");
	if(!bool(_head)) throw std::out_of_range("The list is empty!");
	if (!index) { // if index == 0, remove the first element
		T temp = _head->data();
		_head = _head->next();
		return temp;
	}

	ListIterator<T> it = _head;
	while (--index && bool(it)) ++it;
	if (!bool(it) || !it.HasNext()) throw std::out_of_range("Index is Out of Range");
	T temp = it.Next().data();
	it->next(it->next()->next());
	return temp;
}

template<typename T>
T DoublyLinkedList<T>::Remove(int index) {
	if (index < 0) throw std::out_of_range("Index is Out of Range");
	if (!bool(_head)) throw std::out_of_range("The list is empty!");
	if (!index) { // if index == 0, remove the first element
		auto temp = _head;
		_head = _head->next();
		if (bool(_head)) _head->prev(temp->prev());
		else _tail = DlistIterator<T>(temp->prev());
		return temp->data();
	}

	DlistIterator<T> it = _head;
	while (--index && bool(it)) ++it;
	if (!bool(it) || !it.HasNext()) throw std::out_of_range("Index is Out of Range");
	auto temp = it->next();
	it->next(it->next()->next());
	if (it->next()) it->next()->prev(it.GetPointer());
	else _tail = DlistIterator<T>(it);
	return temp->data();
}

// Return an iterator on this list
template<typename T>
ListIterator<T> LinkedList<T>::Iterator() const {
	return _head;
}

template<typename T>
DlistIterator<T> DoublyLinkedList<T>::Literator() const {
	return _head;
}

template<typename T>
DlistIterator<T> DoublyLinkedList<T>::Riterator() const {
	return _tail;
}

// Return the size of the list
template<typename T>
int LinkedList<T>::Size() const {
	int count = 0;
	ListIterator<T> it = _head;
	while (bool(it)) {
		++it;
		++count;
	}
	return count;
}

template<typename T>
int DoublyLinkedList<T>::Size() const {
	int count = 0;
	DlistIterator<T> it = _head;
	while (bool(it)) {
		++it;
		++count;
	}
	return count;
}


#endif // !LINKED_LIST_CPP