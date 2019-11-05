/*
* Class: CPSC 223-01
* Zac Foteff
* GU Username: zfoteff
* File Name: hw7_tests.cpp
    Definition for HashTableCollection class object
*/

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

  //  prints the list
  void print() const;

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
  const double load_factor_threshold = .75;
  //  Hash table array
  Node** hash_table;
};

template <typename K, typename V>
HashTableCollection<K, V>::HashTableCollection() :
collection_size(0), table_capacity(16)
{
  //  dynamically allocates hash table array
  hash_table = new Node*[table_capacity];
  //  initialize the hash table chains
  for (int i = 0; i < table_capacity; ++i)
      hash_table[i] = nullptr;
}

template<typename K, typename V>
HashTableCollection<K, V>::HashTableCollection(const HashTableCollection<K, V>& rhs)
: hash_table(nullptr), load_factor_threshold(rhs.load_factor_threshold),
  collection_size(rhs.collection_size), table_capacity(rhs.table_capacity)
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
  hash_table = new Node*[rhs.table_capacity];
  for (int i = 0; i < rhs.table_capacity; ++i)
  hash_table[i] = nullptr;

  for (int i = 0; i <= rhs.table_capacity; ++i)
  {
    if (rhs.hash_table[i] != nullptr)
    {
      Node* temp = rhs.hash_table[i];
      while (temp != nullptr)
      {
        insert(temp->key, temp->value);
        temp = temp->next;
      }
    }
  }

  return *this;
}

template <typename K, typename V>
HashTableCollection<K, V>::~HashTableCollection() { make_empty(); }


template <typename K, typename V>
void HashTableCollection<K, V>::resize_and_rehash()
{
  //  setup new table
  int new_capacity = table_capacity * 2;
  int new_collection_size = 0;
  //  dynamically allocate new table
  Node** new_table = new Node*[new_capacity];
  for (int i = 0; i < new_capacity; ++i)
    new_table[i] = nullptr;

  std::vector<K> ks;
  keys(ks);

  //  rehash all keys into the new hash table
  for (K key : ks)
  {
    //  hash the keys
    std::hash<K> hash_key;
    size_t hash_val = hash_key(key);
    size_t index = hash_val % new_capacity;

	//  create a new node in new table
    Node* temp = new_table[index];
    V val;
    find(key, val);
    //  if bucket is empty
    if (temp == nullptr)
    {
      temp = new Node;
      temp->key = key;
      temp->value = val;
      temp->next = nullptr;
      new_table[index] = temp;
    }

    else
    {
      temp = new Node;
      temp->key = key;
      temp->value = val;
      temp->next = new_table[index];
    }

    new_collection_size++;
  }
  //  clear current data
  make_empty();
  //  set the table and other vars
  hash_table = new_table;
  collection_size = new_collection_size;
  table_capacity = new_capacity;
}

template<typename K, typename V>
void HashTableCollection<K, V>::insert(const K& key, const V& val)
{
  //  check current load factor vs load_factor_threshold and resize if needed
  double cur_load_factor = collection_size / table_capacity;
  if (cur_load_factor == 0)
    cur_load_factor = -1;   //  0 > .75 so set it lower if there is empty list

  if (cur_load_factor > load_factor_threshold)
    resize_and_rehash();

  //  hash the key
  std::hash<K> hash_key;
  size_t hash_val = hash_key(key);
  size_t index = hash_val % table_capacity;

  //  collision checks
  if (hash_table[index] == nullptr)
  {
    //  no collision -> fill bucket
    hash_table[index] = new Node;
    hash_table[index]->key = key;
    hash_table[index]->value = val;
    hash_table[index]->next = nullptr;
    collection_size++;
  }

  else
  {
    //  collision
    Node* cur = hash_table[index];
    //  find first empty bucket
    while (cur->next != nullptr)
      cur = cur->next;

    //  fill bucket
    cur->next = new Node;
    cur->next->key = key;
    cur->next->value = val;
    cur->next->next = nullptr;
    collection_size++;
  }
}

template <typename K, typename V>
void HashTableCollection<K, V>::remove(const K& key)
{
  std::hash<K> hash_key;
  size_t hash_val = hash_key(key);
  size_t index = hash_val % table_capacity;

  if (hash_table[index] == nullptr)
    return;

  if (hash_table[index]->key == key)
  {
    Node* cur = hash_table[index];
    hash_table[index] = hash_table[index]->next;
    delete cur;
    collection_size--;
    return;
  }

  else
  {
    Node* last = hash_table[index];
    Node* cur = hash_table[index]->next;

    while (cur != nullptr)
    {
      if (cur->key == key)
      {
        last->next = cur->next;
        delete cur;
        cur = nullptr;
        collection_size--;
        break;
      }

      cur = cur->next;
      last = last->next;
    }
  }
}

template <typename K, typename V>
bool HashTableCollection<K, V>::find(const K& key, V& val) const
{
  std::hash<K> hash_key;
  size_t hash_val = hash_key(key);
  //  bucket the key should be located
  size_t index = hash_val % table_capacity;

  if (hash_table[index] == nullptr)
    return false;

  Node* cur = hash_table[index];
  while (cur != nullptr)
  {
    //  if cur is instance of key
    if (cur->key == key)
    {
      val = cur->value;
      return true;
    }

    cur = cur->next;
  }

  //  return false if the key does not exist in the index or any of its chains
  return false;
}

template <typename K, typename V>
void HashTableCollection<K, V>::
find(const K& k1, const K& k2, std::vector<K>& keys) const
{
  Node* iter;
  for (int i = 0; i < table_capacity; ++i)
  {
    if (hash_table[i] == nullptr)
      continue;

    if (hash_table[i]->key >= k1 && hash_table[i]->key <= k2)
    {
      keys.push_back(hash_table[i]->key);
      iter = hash_table[i]->next;
      //  if there are multiple objects in the bucket, this loop checks them

	    while (iter != nullptr)
      {
        if (iter->key >= k1 && iter->key <= k2)
          keys.push_back(iter->key);

        iter = iter->next;
      }
    }
  }
}

template <typename K, typename V>
void HashTableCollection<K, V>::keys(std::vector<K>& keys) const
{
  Node* iter;
  for (int i = 0; i < table_capacity; ++i)
  {
    if (hash_table[i] == nullptr)
      continue;

    keys.push_back(hash_table[i]->key);
    iter = hash_table[i]->next;

    while (iter != nullptr)
    {
      keys.push_back(iter->key);
      iter = iter->next;
    }
  }
}

template <typename K, typename V>
void HashTableCollection<K, V>::sort(std::vector<K>& keys) const
{
  Node* iter;
  for (int i = 0; i < table_capacity; ++i)
  {
    if (hash_table[i] == nullptr)
      continue;

    keys.push_back(hash_table[i]->key);
    iter = hash_table[i]->next;

    while (iter != nullptr)
    {
      keys.push_back(iter->key);
      iter = iter->next;
    }
  }

  std::sort(keys.begin(), keys.end());
}

template <typename K, typename V>
int HashTableCollection<K, V>::size() const
{
  return collection_size;
}

template <typename K, typename V>
void HashTableCollection<K, V>::make_empty()
{
  if (hash_table != nullptr)
  {
    for (int i = 0; i < table_capacity; ++i)
    {
      Node* cur = hash_table[i];
      while (cur != nullptr)
      {
        Node* temp = cur;
        cur = cur->next;
        delete temp;
        collection_size--;
      }
    }
    delete hash_table;
  }
}

template <typename K, typename V>
void HashTableCollection<K, V>::print() const
{
  for (int i = 0; i < table_capacity; ++i)
  {
    Node* cur = hash_table[i];
    if (cur == nullptr)
      continue;

    while (cur != nullptr)
    {
      std::cout<<cur->key<<" ";
      cur = cur->next;
    }
  }

  std::cout<<std::endl;
}

#endif
