// test.cpp
//
// test file for excercise 3
//
// 10/31/16
//
// by Bingcheng Wang and Chendi Zhang

#include "hash_table.hpp"
#include <iostream>

int main() {
	Hashtable<int, double> hs(10);  // create a hashtable of size 10
	hs.Insert(30, 10.5);
	hs.Insert(15, 3);
	hs.Insert(1, 100.5);
	hs.Insert(30, 5.2);   // change the value
	hs.Insert(31, 20);
	hs.Insert(100021, 2000);

	std::cout << "The size of the hashtable: " << hs.Size() << std::endl;
	std::cout << hs.Get(30) << std::endl;   // 5.2
	std::cout << hs.Get(1) << std::endl;   // 100.5
	std::cout << hs.Get(31) << std::endl;   // 20
	std::cout << hs.Get(100021) << std::endl;   // 2000

	hs.Remove(100021);
	try {
		std::cout << hs.Get(100021) << std::endl;  // cannot find it
	}
	catch (std::out_of_range& err) {
		std::cout << err.what() << std::endl;
	}

	return 0;
}