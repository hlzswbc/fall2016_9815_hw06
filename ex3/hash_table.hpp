// hash_table.hpp
//
// header file hash table data structure
//
// 10/30/16
//
// by Bingcheng Wang and Chendi Zhang

#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include "linked_list.hpp"
#include <vector>
#include <stdexcept>

// class Hasher
template<typename K>
class Hasher {
public:
	virtual int operator()(K key) = 0;
};

// derived class ModuloHash
// type K must be able to change to an int
template<typename K>
class ModuloHash :public Hasher<K> {
private:
	int _size;
public:
	ModuloHash(int size) : _size(size) {};
	int operator()(K key) { return int(key) % _size; }
};

// class EqualityPredicate
template<typename K>
class EqualityPredicate {
public:
	virtual bool operator()(K key1, K key2) = 0;
};

// derived class Equality
// use == to judge if two keys are the same
template<typename K>
class Equality :public EqualityPredicate<K> {
public:
	bool operator()(K key1, K key2) { return key1 == key2; }
};

// class Hashtable
template<typename K, typename V>
class Hashtable {
private:
	struct _Node{
		K key;
		V value;
	};

	int _size;                    // size of the hash table
	std::vector<LinkedList<_Node>> _hash;   // hash table
public:
	Hashtable(int size) :_size(size), _hash(size) {  }          // assign the size of the hash table
	Hashtable(const Hashtable<K, V>& ht) : _size(ht._size), _hash(ht._hash) {} // copy constructor
	Hashtable<K, V>& operator=(const Hashtable<K, V>& ht) {                  // assignment operator
		if (this != &ht) {
			_size = ht._size;
			_hash = ht._hash;
		}
		return *this;
	}
	virtual ~Hashtable() {}   // dtor

	int Size() const;     // get the size of the hashtable
	void Insert(const K& key, const V& value);   // insert an item, if the key exists, just change the value
	int Remove(const K& key);                  // Remove an item, if doesn't find, return 0
	V Get(const K& key);                        // get the value
};



/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// get the size of the hashtable
template<typename K, typename V>
inline int Hashtable<K, V>::Size() const {
	return _size;
}

// insert an item
// use class ModuloHash and class Equality
template<typename K, typename V>
inline void Hashtable<K, V>::Insert(const K & key, const V & value) {
	ModuloHash<K> hash(_size);
	Equality<K> eq;
	int id = hash(key);
	auto it = _hash[id].Iterator(); // bug!
	while (it) {
		if (eq(it->data().key, key)) {  // find the key
			it->data().value = value;
			return;
		}
		++it;
	}
	auto pnd = new _Node;
	pnd->key = key;
	pnd->value = value;
	_hash[id].Push_front(*pnd);
}

// Remove an item
template<typename K, typename V>
inline int Hashtable<K, V>::Remove(const K & key) {
	ModuloHash<K> hash(_size);
	Equality<K> eq;
	int id = hash(key);
	auto it = _hash[id].Iterator();
	int i = 0;
	while (it) {
		if (eq(it->data().key, key)) {  // find the key
			_hash[id].Remove(i);  // remove the item
			return 1;
		}
		++it;
		++i;
	}
	return 0;  // failed, return 0
}

// get the value
// if cannot find the item, throw out_of_range
template<typename K, typename V>
inline V Hashtable<K, V>::Get(const K & key) {
	ModuloHash<K> hash(_size);
	Equality<K> eq;
	int id = hash(key);
	auto it = _hash[id].Iterator();
	while (it) {
		if (eq(it->data().key, key)) {  // find the key
			return it->data().value;
		}
		++it;
	}
	throw std::out_of_range("Cannot find the item!");
	return 0;
}


#endif // !HASH_TABLE_HPP