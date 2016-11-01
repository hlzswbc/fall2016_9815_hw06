// test.cpp
//
// test file for exercise 1 & 2
//
// by Bingcheng Wang and Chendi Zhang
//
// 10/29/16

#include <iostream>
#include <string>
#include "linked_list.hpp"

int main() {
	// test class LinkedList
	std::cout << "========================" << std::endl << std::endl;
	LinkedList<int> ll;
	ll.Push_front(5);  // add from the left
	ll.Push_front(2);
	ll.Push_front(1);
	ll.Add(10);        // add from the right
	ll.Add(12);
	auto it = ll.Iterator();
	while (it) {
		std::cout << *it << " ";  // 1 2 5 10 12
		++it;
	}
	std::cout << std::endl;

	LinkedList<int> ll2(ll);  // copy constructor

	ll.Insert(100, 8);  // insert at the index 8
	it = ll.Iterator();
	while (it) {
		std::cout << *it << " ";  // 1 2 5 10 12 0 0 0 100
		++it;
	}
	std::cout << std::endl;

	ll.Insert(50, 0);  // insert at the index 0
	it = ll.Iterator();
	while (it) {
		std::cout << *it << " ";  // 50 1 2 5 10 12 0 0 0 100
		++it;
	}
	std::cout << std::endl;

	std::cout << ll.Get(5) << std::endl;  // 12
	std::cout << ll.IndexOf(50) << std::endl; // 0
	std::cout << ll.Size() << std::endl; // 10

	std::cout << ll.Remove(5) << std::endl; // 12
	it = ll.Iterator();
	while (it) {
		std::cout << *it << " ";  // 50 1 2 5 10 0 0 0 100
		++it;
	}
	std::cout << std::endl;

	it = ll2.Iterator();     // the copied list remains unchange
	while (it) {
		std::cout << *it << " ";  // 1 2 5 10 12
		++it;
	}
	std::cout << std::endl;

	// test class DoublyLinkedList
	std::cout << "========================" << std::endl << std::endl;

	DoublyLinkedList<double> dll;
	dll.Push_front(0.5);  // add from the left
	dll.Push_front(0.2);
	dll.Push_front(0.1);
	dll.Add(1.0);        // add from the right
	dll.Add(1.2);

	auto dit = dll.Literator();  // from left to right
	while (dit) {
		std::cout << *dit << " ";  // 0.1 0.2 0.5 1 1.2
		++dit;
	}
	std::cout << std::endl;

	dit = dll.Riterator();  // from right to left
	while (dit) {
		std::cout << *dit << " ";  // 1.2 1 0.5 0.2 0.1
		--dit;
	}
	std::cout << std::endl;

	DoublyLinkedList<double> dll2(dll);  // copy constructor

	dll.Insert(100, 8);  // insert at the index 8
	dit = dll.Literator();
	while (dit) {
		std::cout << *dit << " ";  // 0.1 0.2 0.5 1 1.2 0 0 0 100
		++dit;
	}
	std::cout << std::endl;

	dll.Insert(50, 0);  // insert at the index 0
	dit = dll.Literator();
	while (dit) {
		std::cout << *dit << " ";  // 50 0.1 0.2 0.5 1 1.2 0 0 0 100
		++dit;
	}
	std::cout << std::endl;

	std::cout << dll.Get(5) << std::endl;  // 1.2
	std::cout << dll.IndexOf(50) << std::endl; // 0
	std::cout << dll.Size() << std::endl; // 10

	std::cout << dll.Remove(5) << std::endl; // 1.2
	dit = dll.Literator();
	while (dit) {
		std::cout << *dit << " ";  // 50 0.1 0.2 0.5 1 0 0 0 100
		++dit;
	}
	std::cout << std::endl;
	dit = dll.Riterator();  // from right to left
	while (dit) {
		std::cout << *dit << " ";  // 100 0 0 0 1 0.5 0.2 0.1 50
		--dit;
	}
	std::cout << std::endl;

	dit = dll2.Literator();     // the copied list remains unchange
	while (dit) {
		std::cout << *dit << " ";  // 0.1 0.2 0.5 1 1.2
		++dit;
	}
	std::cout << std::endl;
	dit = dll2.Riterator();  // from right to left
	while (dit) {
		std::cout << *dit << " ";  // 1.2 1 0.5 0.2 0.1
		--dit;
	}
	std::cout << std::endl;

	return 0;
}