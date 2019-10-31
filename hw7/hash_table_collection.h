#ifndef HASH_TABLE_COLLECTION_H
#define HASH_TABLE_COLLECTION_H

#include <vector>
#include <algorithm>
#include <functional>
#include "collection.h"

template <typename K, typename V>
class HashTableCollection : public Collection<K, V>
{
public:
  //  Create an empty linked list
  HashTableCollection();

  //  Copy a linked list
  HashTableCollection(const HashTableCollection<K, V>& rhs);

  //  Assign a linked list
  HashTableCollection<K, V>& operator=(const HashTableCollection<K, V>& rhs);

  //  Delete a linked list
  ~HashTableCollection();

  //  Insert a key-value pair into the Collection
  void insert(const K& key, const V& val);

  //  Remove a key-value pair into the collection
  void remove(const K& key);

  //  Find a value associated with the key
  bool find(const K& key, V& val) const;

  //  Find the keys associated with the range
  void find(const K& k1, const K& k2, std::vector<K>& keys) const;

  //  Return all keys in the Collection
  void keys(std::vector<K>& keys) const;

  //  Return collection keys in sorted order
  void sort(std::vector<K>& keys) const;

  //  Return the number of keys in the Collection
  int size() const;

private:

  //  helper to empty entire hash HashTableCollection
  void make_empty();

  //  resize and rehash the hash table
  void resize_and_rehash();

  //  linked list node structure
  struct Node
  {
    K key;
    V value;
    Node* next;
  };

  //  Int number of k-v pairs in the collection
  int collection_size;
  //  Number of hash table buckets (default: 16)
  int table_capacity;
  //  Hash table array load factor (set at 75% for resizing)
  const double load_factor_threshold;
  //  Hash table array
  Node** hash_table;
};


template <typename K, typename V>
HashTableCollection<K, V>::HashTableCollection() :
collection_size(0), table_capacity(16), load_factor_threshold(0.75)
{
  //  dynamically allocates hash table array
  hash_table = new Node*[table_capacity];
  //  initialize the hash table chains
  for (int i = 0; i < table_capacity; ++i)
      hash_table[i] = nullptr;
}

template <typename K, typename V>
void HashTableCollection<K, V>::make_empty()
{
  //  make sure hash table exists
  while (hash_table != nullptr)
  {


    //  Remove each keys
    //  Remove the hash table

    delete hash_table;
  }
}

template <typename K, typename V>
HashTableCollection<K, V>::~HashTableCollection()
{
  make_empty();
}

template<typename K, typename V>
HashTableCollection<K, V>::
HashTableCollection(const HashTableCollection<K,V>& rhs) : hash_table(nullptr)
{
  *this = rhs;
}

template<typename K, typename V>
HashTableCollection<K, V>&
HashTableCollection<K, V>::operator=(const HashTableCollection<K, V>& rhs)
{
  //  check if rhs is current obj.
  if (this == &rhs)
    return *this;

  //  delete current object
  make_empty();
  //  initialize current obj.
  //  create hash table
  //  do the copy
  return *this;
}

template <typename K, typename V>
void HashTableCollection<K, V>::resize_and_rehash()
{
  //  setup new table
  int new_capacity = table_capacity * 2;
  Node** new_table = new Node*[new_capacity];

  //  dynamically allocate new table
  for (int i = 0; i < new_capacity; ++i)
    new_table[i] = nullptr;

  std::vector<K> ks;
  keys(ks);

  //  rehash all keys into the new hash table
  for (K key : ks)
  {
    //  hash the keys
    //  create a new node in new table
  }
  //  clear current data
  make_empty();
  //  set the table and other vars
  hash_table = new_table;
  table_capacity = new_capacity;
}

template<typename K, typename V>
void HashTableCollection<K, V>::insert(const K& key, const V& val)
{
  //  check current load facter vs load_factor_threshold and resize if needed
  //  hash the key
  //  create the new Node
  //  update the size
  collection_size++;
}
