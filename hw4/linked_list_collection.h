#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <vector>
#include <algorithm>
#include "collection.h"


template<typename K, typename V>
class LinkedListCollection : public Collection<K, V>
{
public:

  //  DVC
  LinkedListCollection();

  //  Copy constuctor
  LinkedListCollection(const LinkedListCollection<K, V>& rhs);

  //  Assignment operator
  LinkedListCollection<K, V>& operator=(const LinkedListCollection<K, V>& rhs);

  //  Deleting Linked List
  ~LinkedListCollection();

  //  Insert new key-value pair into the collection
  void insert(const K& key, const V& val);

  //  remove a key-value pair from the collection
  void remove(const K& key);

  //  Find the value associated with the key
  bool find(const K& key, V& val) const;

  //  Find the keys associated with the range
  void find(const K& k1, const K& k2, std::vector<K>& keys) const;

  //  Return all keys in the Collection
  void keys(std::vector<K>& keys) const;

  //  Return the number of keys in the Collection
  int size() const;

private:
  struct Node
  {
    K key;
    V value;
    Node* next;
  };

  Node* head;
  Node* tail;
  int length;
};

template<typename K, typename V>
LinkedListCollection<K, V>::LinkedListCollection()
{
  head = nullptr;
  tail = nullptr;
  length = 0;
}

template<typename K, typename V>
LinkedListCollection<K, V>
::LinkedListCollection(const LinkedListCollection<K, V>& rhs)
{
  Node* cur = new Node;
  cur->value = rhs->head->key;
  cur->value = rhs->head->value;
  cur->next = rhs->head->next;

  for(int i = 0; cur != nullptr; ++i)
  {
    this->insert(cur->key, cur->value);
    cur = cur->next;
  }
}

template<typename K, typename V>
LinkedListCollection<K, V>::~LinkedListCollection()
{
  Node* cur = head;
  while (cur->next != nullptr)
  {
    cur = cur->next;
    delete head;
    head = cur;
  }

  delete cur;
}

template<typename K, typename V>
void LinkedListCollection<K, V>::insert(const K& key, const V& val)
{
  Node* new_insert = new Node;
  new_insert->key = key;
  new_insert->value = value;

  if (length == 0)
  {
    head = new_insert;
    tail = new_insert;
    new_insert->next = nullptr;
    length++;
    return;
  }

  tail->next = new_insert;
  new_insert->next = nullptr;
  tail = new_insert;
  length++;
}

template<typename K, typename V>
void LinkedListCollection<K, V>::remove(const K& key)
{
  Node* last = new Node;
  Node* cur = head;

  if (length == 1)
  {
    delete head;
    return;
  }

  for(int i = 0; cur->next != nullptr; ++i)
  {
    if (cur->key == key)
    {
      last->next = cur->next;
      delete cur;
    }

    last = cur;
    cur = cur->next;
  }
}

template<typename K, typename V>
bool LinkedListCollection<K, V>::find(const K& key, V& val) const
{
  bool r = false;

  for(int i = 0; cur->next != nullptr; ++i)
  {
    if(cur->key == key)
    {
      r = true;
      val = cur->value;
      break;
    }
  }

  return r;
}

template<typename K, typename V>
void LinkedListCollection<K, V>
::find(const K& k1, const K& k2, std::vector<K>& keys) const
{
  for(int i = 0; cur->next != nullptr; ++i)
  {
    if (cur->key >= k1 && cur->key <= k2)
    {
      keys.push_back(cur->key);
    }

    cur = cur->next;
  }
}

template<typename K, typename V>
void LinkedListCollection<K, V>::sort(std::vector<K>& keys) const
{
  Node* cur = head;
  while (cur != nullptr)
  {
    keys.push_back(cur->key);
    cur = cur->next;
  }

  std::sort(keys.begin(), keys.end());
}

template<typename K, typename V>
int LinkedListCollection<K, V>::size() const
{
  unsigned int i;
  for(i = 0; cur->next; ++i)
  {
    cur = cur->next;
  }

  return i;
}

#endif
